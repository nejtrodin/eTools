#ifndef BOMLISTMODEL_H
#define BOMLISTMODEL_H

#include <QAbstractListModel>

class BomListItem;

class BomListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum NodeType {
        GroupNode,
        ItemNode,
    };
    Q_ENUM(NodeType)

    enum ListItemRoles {
        TypeRole = Qt::UserRole + 1,
        PartNumberRole,
        NameRole,
    };

    explicit BomListModel(QObject *parent = nullptr);
    ~BomListModel();

    QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> roles;
        roles[TypeRole] = "type";
        roles[PartNumberRole] = "partNumber";
        roles[NameRole] = "partName";
        return roles;
    }

    Q_INVOKABLE void setSchematicPath(QString path);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

private:
    QList<BomListItem *> items;
};

#endif // BOMLISTMODEL_H
