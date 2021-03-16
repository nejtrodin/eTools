#ifndef LAYERLISTMODEL_H
#define LAYERLISTMODEL_H

#include <QtCore>
#include <QAbstractTableModel>
#include "schSettings.h"
#include "layer.h"

class LayerListModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList pressetList READ pressetList NOTIFY pressetListChanged)

public:
    enum ItemRoles {
        NumberRole = Qt::UserRole + 1,
        ColorRole,
        NameRole,
        VisibleRole,
    };

    explicit LayerListModel(QObject *parent = nullptr);
    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[NumberRole] = "layerNumber";
        roles[ColorRole] = "layerColor";
        roles[NameRole] = "layerName";
        roles[VisibleRole] = "layerVisible";
        return roles;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override { return 4; }

    void setSettings(const SchSettings &settings);
    void updateSettings(SchSettings *settings);

    QStringList pressetList();
    Q_INVOKABLE void selectPresset(QString pressetName);

signals:
    void pressetListChanged();

private:
    typedef struct {
        QString name;
        QVector<int> visibleLayers;
    } LayerPresset;

    QList<Layer> mLayers;
    SchSettings mSettings;
    QMap<QString, LayerPresset> mLayerPressets;
};

#endif // LAYERLISTMODEL_H
