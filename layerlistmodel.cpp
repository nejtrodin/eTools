#include "layerlistmodel.h"
#include <QColor>

LayerListModel::LayerListModel(QObject *parent) : QAbstractTableModel(parent)
{
    mpSettings = nullptr;
}

QVariant LayerListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mLayers.size())
        return QVariant();

    Layer layer = mLayers.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
    case NumberRole:
        return layer.number;
    case ColorRole:
        return mpSettings->themeColors[layer.colorNumber];
    case NameRole:
        return layer.name;
    case VisibleRole:
        return layer.visible;
    default:
        return QVariant();
    }
}

bool LayerListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    int row = index.row();
    switch (role) {
    case VisibleRole:
        mLayers[row].visible = value.toBool();
        break;
    default:
        return false;
    }

    return true;
}

int LayerListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mLayers.size();
}

void LayerListModel::setSettings(Settings *settings)
{
    beginResetModel();
    mpSettings = settings;
    mLayers = mpSettings->layers.values();
    endResetModel();
}

void LayerListModel::updateSettings(Settings *settings)
{
    settings->layers.clear();
    foreach(Layer layer, mLayers)
        settings->layers.insert(layer.number, layer);
}
