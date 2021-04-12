#include "bomlistmodel.h"

#include "eagle/sch/eschematic.h"
#include "tools/bommanager.h"

class BomListItem
{
public:
    BomListItem(QString partNumber, QString partName, QString specification, QString note)
        : partNumber(partNumber), partName(partName), specification(specification), note(note)
    {
    }

    QString partNumber;
    QString partName;
    QString specification;
    QString note;
};

BomListModel::BomListModel(QObject *parent) : QAbstractListModel(parent) { }

BomListModel::~BomListModel()
{
    foreach (auto item, items)
        delete item;
}

void BomListModel::setSchematicPath(QString path)
{
    foreach (auto item, items)
        delete item;
    items.clear();

    ESchematic eSchematic;
    eSchematic.readFile(path);
    BomManager bomManager;
    bomManager.setSchematic(&eSchematic);

    beginResetModel();
    auto bom = bomManager.getBomSortedByPosition();
    foreach (auto bomItem, bom) {
        QString partNumber = QString("%1%2").arg(bomItem.positionPrefix).arg(bomItem.position);
        BomListItem *item =
                new BomListItem(partNumber, bomItem.name, bomItem.specification, bomItem.note);
        items.append(item);
    }
    endResetModel();
}

QVariant BomListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();

    const BomListItem *item = items.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return item->partName;
    case PartNumberRole:
        return item->partNumber;
    default:
        return QVariant();
    }
}

int BomListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return items.size();
}
