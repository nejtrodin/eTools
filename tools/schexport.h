#ifndef SCHEXPORT_H
#define SCHEXPORT_H

#include <QtCore>
#include <QAbstractTableModel>
#include "eagle/sch/eschematic.h"
#include "layerlistmodel.h"
#include "settings.h"

typedef enum {
    PageSizeA4,
    PageSizeA3,
    PageSizeA2,
    PageSizeA1,
} PageSize;

const QStringList pageSizeList = { "A4", "A3", "A2", "A1" };

typedef enum {
    PagePortrait,
    PageLandscape,
} PageOrientation;

const QStringList pageOrientationList = { QT_TR_NOOP("Portrait"), QT_TR_NOOP("Landscape") };

typedef struct
{
    int id;
    QString name;
    PageSize size;
    PageOrientation orientation;
    bool used;
} SheetSetting;

class SheetSettingsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum ItemRoles {
        NameRole = Qt::UserRole + 1,
        SizeIdxRole,
        SizeListRole,
        OrientationIdxRole,
        OrientationListRole,
        UsedRole,
    };

    explicit SheetSettingsModel(QObject *parent = nullptr);
    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[SizeIdxRole] = "sizeIdx";
        roles[SizeListRole] = "sizeList";
        roles[OrientationIdxRole] = "orientationIdx";
        roles[OrientationListRole] = "orientationList";
        roles[UsedRole] = "used";
        return roles;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override { return 4; }

    void setSettings(QList<SheetSetting> settings);
    QList<SheetSetting> getSettings() { return mSheetSettings; }

private:
    QList<SheetSetting> mSheetSettings;
};


class SchExport : public QObject
{
    Q_OBJECT

public:
    SchExport(QObject *parent = nullptr);
    Q_INVOKABLE void openFile(QString path);
    Q_INVOKABLE SheetSettingsModel *getSheetSettingsModel() { return mpSheetSettingsModel; }
    Q_INVOKABLE LayerListModel *getLayerListModel() { return mpLayerListModel; }
    Q_INVOKABLE void exportToPdf(QString filePath, bool colorAsBlack, bool addBorder);

private:
    bool mValid = false;
    SheetSettingsModel *mpSheetSettingsModel;
    LayerListModel *mpLayerListModel;
    ESchematic mESchematic;
    Settings mSettings;
};

#endif // SCHEXPORT_H
