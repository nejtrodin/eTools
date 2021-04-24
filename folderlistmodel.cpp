#include "folderlistmodel.h"
#include <QUrl>
#include <QDir>

FolderListModel::FolderListModel(QObject *parent) : QAbstractListModel(parent) { }

void FolderListModel::setPathList(QStringList paths)
{
    beginResetModel();
    mPathList = paths;
    endResetModel();
}

QStringList FolderListModel::pathList()
{
    QStringList result = mPathList;
    result.removeDuplicates();
    result.removeAll(QString(""));
    return result;
}

QVariant FolderListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    switch (role) {
    case Qt::DisplayRole:
    case PathRole:
        if (row < mPathList.size())
            return mPathList.at(index.row());
        else
            return QString();
    case LastRole:
        if (row == mPathList.size())
            return true;
        else
            return false;
    default:
        return QVariant();
    }
}

bool FolderListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    int row = index.row();
    switch (role) {
    case PathRole:
        if (row < mPathList.size())
            mPathList.replace(row, value.toString());
        else {
            beginResetModel();
            mPathList.append(value.toString());
            endResetModel();
        }
        break;
    default:
        return false;
    }

    return true;
}

int FolderListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mPathList.size() + 1;
}

void FolderListModel::remove(int index)
{
    beginResetModel();
    mPathList.remove(index);
    endResetModel();
}

void FolderListModel::change(int row, QString path)
{
    beginResetModel();
    if (row == mPathList.size())
        mPathList.append(getNativePath(path));
    else
        mPathList.replace(row, getNativePath(path));
    endResetModel();
}

QString FolderListModel::getNativePath(QString path)
{
    QUrl url(path);
    if (url.isValid() && url.isLocalFile())
        return QDir::toNativeSeparators(url.toLocalFile());
    else
        return QDir::toNativeSeparators(path);
}
