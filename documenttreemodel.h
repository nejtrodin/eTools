#ifndef DOCUMENTTREEMODEL_H
#define DOCUMENTTREEMODEL_H

#include <QAbstractListModel>

class DocumentTreeItem;

class DocumentTreeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum NodeType {
        ProjectSectionNode,
        ProjectFolderNode,
        LibrarySectionNode,
        FolderNode,
        BoardNode,
        SchematicNode,
        LibraryNode,
    };
    Q_ENUM(NodeType)

    enum ListMenuItemRoles {
        NameRole = Qt::UserRole + 1,
        PathRole,
        TypeRole,
        HasChildrenRole,
        IsOpenedRole,
        LevelRole,
    };

    explicit DocumentTreeModel(QObject *parent = nullptr);
    QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[PathRole] = "path";
        roles[TypeRole] = "type";
        roles[HasChildrenRole] = "hasChildren";
        roles[IsOpenedRole] = "isOpened";
        roles[LevelRole] = "level";
        return roles;
    }

    Q_INVOKABLE void setProjectPathList(QStringList pathList);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

public slots:
    void openItem(int numIndex);
    void closeItem(int numIndex);

private:
    void resetItems();

    QList<DocumentTreeItem *> items;
    QStringList mProjectPathList;
};

#endif // DOCUMENTTREEMODEL_H
