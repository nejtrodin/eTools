#include "schexport.h"
#include <QtPrintSupport/QPrinter>
#include <QFontDatabase>

SheetSettingsModel::SheetSettingsModel(QObject *parent) : QAbstractTableModel(parent) { }

QVariant SheetSettingsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mSheetSettings.size())
        return QVariant();

    SheetSetting item = mSheetSettings.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return item.name;
    case SizeIdxRole:
        return item.size;
    case SizeListRole:
        return pageSizeList;
    case OrientationIdxRole:
        return item.orientation;
    case OrientationListRole:
        return pageOrientationList;
    case UsedRole:
        return item.used;
    default:
        return QVariant();
    }
}

bool SheetSettingsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    int row = index.row();
    switch (role) {
    case SizeIdxRole:
        mSheetSettings[row].size = static_cast<PageSize>(value.toInt());
        break;
    case OrientationIdxRole:
        mSheetSettings[row].orientation = static_cast<PageOrientation>(value.toInt());
        break;
    case UsedRole:
        mSheetSettings[row].used = value.toBool();
        break;
    default:
        return false;
    }

    return true;
}

int SheetSettingsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mSheetSettings.size();
}

void SheetSettingsModel::setSettings(QList<SheetSetting> settings)
{
    beginResetModel();
    mSheetSettings = settings;
    endResetModel();
}

SchExport::SchExport(QObject *parent) : QObject(parent)
{
    mpSheetSettingsModel = new SheetSettingsModel(this);
}

void SchExport::openFile(QString path)
{
    mValid = mESchematic.openFile(path);

    QList<SheetSetting> sheetSettings;
    if (mValid) {
        QStringList sheetList = mESchematic.sheetList();
        for (int i = 0; i < sheetList.size(); i++) {
            SheetSetting settingsItem;
            settingsItem.id = i;
            settingsItem.name = sheetList.at(i);
            settingsItem.size = PageSizeA4;
            settingsItem.orientation = PagePortrait;
            settingsItem.used = true;
            sheetSettings.append(settingsItem);
        }
    }
    mpSheetSettingsModel->setSettings(sheetSettings);
}

void SchExport::exportToPdf(QString filePath, bool colorAsBlack)
{
    QPrinter printer(QPrinter::HighResolution);
    QPainter painter;

    qreal scale = printer.resolution() / 25.4;
    Settings printSettings;
    printSettings.schScale = scale;

    if (colorAsBlack)
        for (int i = 0; i < 64; i++)
            printSettings.themeColors[i] = Qt::black;

    int id = QFontDatabase::addApplicationFont(":/fonts/gost_b.ttf");
    QString gost_b = QFontDatabase::applicationFontFamilies(id).at(0);
    printSettings.schFont = QFont(gost_b);

    QList<SheetSetting> sheetSettings = mpSheetSettingsModel->getSettings();
    QList<SheetSetting>::iterator iSettings;
    int sheetPage = 0;
    int printPage = 0;
    for (iSettings = sheetSettings.begin(); iSettings != sheetSettings.end(); ++iSettings) {
        if (iSettings->used) {
            switch (iSettings->size) {
            case PageSizeA4:
                printer.setPageSize(QPageSize(QPageSize::A4));
                break;
            case PageSizeA3:
                printer.setPageSize(QPageSize(QPageSize::A3));
                break;
            case PageSizeA2:
                printer.setPageSize(QPageSize(QPageSize::A2));
                break;
            case PageSizeA1:
                printer.setPageSize(QPageSize(QPageSize::A1));
                break;
            }

            switch (iSettings->orientation) {
            case PagePortrait:
                printer.setPageOrientation(QPageLayout::Portrait);
                break;
            case PageLandscape:
                printer.setPageOrientation(QPageLayout::Landscape);
                break;
            }

            if (printPage == 0) {
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName(filePath);
                printer.setFontEmbeddingEnabled(true);
                printer.setFullPage(true);

                painter.begin(&printer);
            } else
                printer.newPage();

            painter.save();
            // Use the painter to draw on the page.
            QRect r(painter.viewport());
            painter.translate(0, r.height());
            mESchematic.paint(&painter, &printSettings, sheetPage);

            painter.restore();

            printPage++;
        }
        sheetPage++;
    }

    painter.end();
}
