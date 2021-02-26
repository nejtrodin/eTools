#include "documenttreemodel.h"
#include "tools/efileinfo.h"
#include <QDir>

#include <QDebug>

class DocumentTreeItem
{
public:
    DocumentTreeItem(QString path, DocumentTreeModel::NodeType type, int level)
        : path(path), type(type), level(level)
    {
        if (type == DocumentTreeModel::LibrarySectionNode
            || type == DocumentTreeModel::ProjectSectionNode
            || type == DocumentTreeModel::FolderNode)
            hasChildren = true;
        else
            hasChildren = false;

#ifdef Q_OS_WIN
        path.replace("\\", "/");
#endif

        while (path.back() == '/')
            path.chop(1);

        name = path.mid(path.lastIndexOf('/') + 1);
        isOpened = false;
    }

    QString name;
    QString path;
    DocumentTreeModel::NodeType type;
    bool hasChildren;
    bool isOpened;
    int level; // уровень вложенности. Используется для расчета сдвига элементов в дереве
};

DocumentTreeModel::DocumentTreeModel(QObject *parent) : QAbstractListModel(parent)
{
    resetItems();
}

void DocumentTreeModel::setProjectPaths(QString paths)
{
#ifdef Q_OS_UNIX
    paths.replace(':', ';');
    paths.replace("$HOME", qgetenv("HOME"));
#endif

    projectPathList = paths.split(';', Qt::SkipEmptyParts);

    beginResetModel();
    resetItems();
    endResetModel();
}

QVariant DocumentTreeModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();

    DocumentTreeItem *item = items.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return item->name;
    case PathRole:
        return item->path;
    case TypeRole:
        return item->type;
    case HasChildrenRole:
        return item->hasChildren;
    case IsOpenedRole:
        return item->isOpened;
    case LevelRole:
        return item->level;
    default:
        return QVariant();
    }
}

int DocumentTreeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return items.size();
}

void DocumentTreeModel::openItem(int numIndex)
{
    if (numIndex > (items.size() - 1))
        return;

    DocumentTreeItem *parentItem = items[numIndex];
    int row = numIndex + 1;

    if (parentItem->isOpened)
        return;

    QModelIndex modelIndex = index(numIndex);
    parentItem->isOpened = true;
    emit dataChanged(modelIndex, modelIndex);

    if (parentItem->type == DocumentTreeModel::ProjectSectionNode) {
        foreach (QString path, projectPathList) {
            auto childrenItem = new DocumentTreeItem(path, DocumentTreeModel::FolderNode,
                                                     parentItem->level + 1);
            beginInsertRows(QModelIndex(), row, row);
            items.insert(row++, childrenItem);
            endInsertRows();
        }
    }
    // explore folder
    else if (parentItem->type == DocumentTreeModel::FolderNode) {
        QDir dir(parentItem->path);
        if (dir.exists()) {
            QFileInfoList dirList = dir.entryInfoList(QDir::Dirs | QDir::AllDirs | QDir::NoSymLinks
                                                      | QDir::NoDotAndDotDot);
            foreach (QFileInfo dirInfo, dirList) {
                auto childrenItem = new DocumentTreeItem(
                        dirInfo.filePath(), DocumentTreeModel::FolderNode, parentItem->level + 1);
                beginInsertRows(QModelIndex(), row, row);
                items.insert(row++, childrenItem);
                endInsertRows();
            }

            QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);
            EFileInfo eFileInfo;
            foreach (QFileInfo fileInfo, fileList) {
                eFileInfo.checkFilePath(fileInfo.filePath());
                if (eFileInfo.getType() == EFileInfo::Board) {
                    auto childrenItem =
                            new DocumentTreeItem(fileInfo.filePath(), DocumentTreeModel::BoardNode,
                                                 parentItem->level + 1);
                    beginInsertRows(QModelIndex(), row, row);
                    items.insert(row++, childrenItem);
                    endInsertRows();
                } else if (eFileInfo.getType() == EFileInfo::Schematic) {
                    auto childrenItem = new DocumentTreeItem(fileInfo.filePath(),
                                                             DocumentTreeModel::SchematicNode,
                                                             parentItem->level + 1);
                    beginInsertRows(QModelIndex(), row, row);
                    items.insert(row++, childrenItem);
                    endInsertRows();
                } else if (eFileInfo.getType() == EFileInfo::Library) {
                    auto childrenItem = new DocumentTreeItem(fileInfo.filePath(),
                                                             DocumentTreeModel::LibraryNode,
                                                             parentItem->level + 1);
                    beginInsertRows(QModelIndex(), row, row);
                    items.insert(row++, childrenItem);
                    endInsertRows();
                }
            }
        }
    }
}

void DocumentTreeModel::closeItem(int numIndex)
{
    if (numIndex > (items.size() - 1))
        return;

    if (!items[numIndex]->isOpened)
        return;

    QModelIndex modelIndex = index(numIndex);
    items[numIndex]->isOpened = false;
    emit dataChanged(modelIndex, modelIndex);

    int row = numIndex + 1;
    // delete all elements with level > current level
    for (; row < items.size() && (items[row]->level > items[numIndex]->level);) {
        beginRemoveRows(QModelIndex(), row, row);
        DocumentTreeItem *item = items[row];
        items.removeAt(row);
        delete item;
        endRemoveRows();
    }
}

void DocumentTreeModel::resetItems()
{
    items.clear();
    items << new DocumentTreeItem(tr("Libraries"), DocumentTreeModel::LibrarySectionNode, 0);
    items << new DocumentTreeItem(tr("Projects"), DocumentTreeModel::ProjectSectionNode, 0);
}
