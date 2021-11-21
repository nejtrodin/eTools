#ifndef BOMLISTMODEL_H
#define BOMLISTMODEL_H

#include <QAbstractListModel>

struct PartItem
{
    QString positions;
    int qty;
    QString partName;
    QString specification;
};

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
        PositionRole,
        NameRole,
        QtyRole,
    };

    explicit BomListModel(QObject *parent = nullptr);
    ~BomListModel();

    QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> roles;
        roles[TypeRole] = "type";
        roles[PositionRole] = "positions";
        roles[NameRole] = "name";
        roles[QtyRole] = "quantity";
        return roles;
    }

    Q_INVOKABLE void setSchematicPath(QString path);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

private:
    QList<PartItem *> parts;
};

#endif // BOMLISTMODEL_H
