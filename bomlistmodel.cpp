#include "bomlistmodel.h"

#include "eagle/sch/eschematic.h"
#include "tools/bom/bomparser.h"


BomListModel::BomListModel(QObject *parent) : QAbstractListModel(parent) { }

BomListModel::~BomListModel()
{
    foreach (auto part, parts)
        delete part;
}

void BomListModel::setSchematicPath(QString path)
{
    foreach (auto part, parts)
        delete part;
    parts.clear();

    ESchematic eSchematic;
    eSchematic.readFile(path);
    BomParser bomParser;
    bomParser.setSchematic(&eSchematic);

    beginResetModel();
    auto bom = bomParser.getBomSortedByPosition();
    foreach (auto bomItem, bom) {
        QString partNumber = QString("%1%2").arg(bomItem.prefix).arg(bomItem.position);
        bool partExist = false;
        foreach (PartItem *part, parts) {
            if (part->partName == bomItem.name && part->specification == bomItem.specification) {
                part->qty += 1;
                part->positions.append(QString(", %1").arg(partNumber));
                partExist = true;
            }
        }
        if (!partExist) {
            PartItem *item = new PartItem;
            item->partName =  bomItem.name;
            item->positions = partNumber;
            item->qty = 1;
            item->specification = bomItem.specification;
            parts.append(item);
        }
    }
    endResetModel();
}

QVariant BomListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= parts.count())
        return QVariant();

    const PartItem *part = parts.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return part->partName;
    case PositionRole:
        return part->positions;
    case QtyRole:
        return part->qty;
    default:
        return QVariant();
    }
}

int BomListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return parts.size();
}
