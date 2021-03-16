#include "layerlistmodel.h"
#include <QColor>

LayerListModel::LayerListModel(QObject *parent) : QAbstractTableModel(parent)
{
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
        return mSettings.getLayerColor(layer.number);
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

void LayerListModel::setSettings(const SchSettings &settings)
{
    beginResetModel();
    mSettings = settings;
    mLayers = mSettings.layers();
    endResetModel();

    // fill layer presset
    mLayerPressets.clear();
    emit pressetListChanged();  // duct-tape for calling selectPresset() from qml

    LayerPresset defaultPresset;
    defaultPresset.name = tr("From schematic");
    foreach(Layer layer, mLayers) {
        if (layer.visible)
            defaultPresset.visibleLayers.append(layer.number);
    }
    mLayerPressets.insert(defaultPresset.name, defaultPresset);

    LayerPresset printPresset;
    printPresset.name = tr("For print");
    printPresset.visibleLayers << settings.netsLayer
                               << settings.bussesLayer
                               << settings.symbolsLayer
                               << settings.namesLayer;
    mLayerPressets.insert(printPresset.name, printPresset);
    emit pressetListChanged();
}

void LayerListModel::updateSettings(SchSettings *settings)
{
    settings->setLayers(mLayers);
}

QStringList LayerListModel::pressetList()
{
    return mLayerPressets.keys();
}

void LayerListModel::selectPresset(QString pressetName)
{
    if (mLayerPressets.contains(pressetName)) {
        LayerPresset presset = mLayerPressets[pressetName];
        beginResetModel();
        QVector<Layer>::iterator iLayer = mLayers.begin();
        for(; iLayer != mLayers.end(); ++iLayer) {
            if (presset.visibleLayers.contains(iLayer->number))
                iLayer->visible = true;
            else
                iLayer->visible = false;
        }
        endResetModel();
    }
}
