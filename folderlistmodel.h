#ifndef FOLDERLISTMODEL_H
#define FOLDERLISTMODEL_H

#include <QAbstractTableModel>

class FolderListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList pathList READ pathList WRITE setPathList)

public:
    enum ItemRoles {
        PathRole = Qt::UserRole + 1,
        LastRole,
    };

    explicit FolderListModel(QObject *parent = nullptr);
    Q_INVOKABLE void setPathList(QStringList paths);
    Q_INVOKABLE QStringList pathList();

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[PathRole] = "path";
        roles[LastRole] = "last";
        return roles;
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void change(int row, QString path);

private:
    QString getNativePath(QString path);
    QStringList mPathList;
};

#endif // FOLDERLISTMODEL_H
