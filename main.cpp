#include <QApplication>
#include <QQuickStyle>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "eagle/eboard.h"
#include "tools/drillreporter.h"
#include "tools/efileinfo.h"
#include "tools/schexport.h"
#include "tools/bom/bomprinter.h"

#include "documenttreemodel.h"
#include "bomlistmodel.h"
#include "schviewitem.h"
#include "layerlistmodel.h"
#include "folderlistmodel.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("SVD Company");
    app.setOrganizationDomain("svdcompany.com");
    app.setApplicationName("eTools");
    app.setWindowIcon(QIcon("://images/eTools.png"));

    QQuickStyle::setStyle("Material"); // Включение Material Design

    qmlRegisterType<BomListModel>       ("ETools", 1, 0, "BomListModel");
    qmlRegisterType<DocumentTreeModel>  ("ETools", 1, 0, "DocumentTreeModel");
    qmlRegisterType<DrillReporter>      ("ETools", 1, 0, "DrillReporter");
    qmlRegisterType<EFileInfo>          ("ETools", 1, 0, "EFileInfo");
    qmlRegisterType<SchExport>          ("ETools", 1, 0, "SchExport");
    qmlRegisterType<SchViewItem>        ("ETools", 1, 0, "SchViewItem");
    qmlRegisterType<SheetSettingsModel> ("ETools", 1, 0, "SheetSettingsModel");
    qmlRegisterType<LayerListModel>     ("ETools", 1, 0, "LayerListModel");
    qmlRegisterType<FolderListModel>    ("FolderList", 1, 0, "FolderListModel");
    qmlRegisterType<BomPrinter>         ("ETools", 1, 0, "BomPrinter");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ETools.qml"));
//    const QUrl url(QStringLiteral("qrc:/EToolsTest.qml"));
    QObject::connect(
            &engine, &QQmlApplicationEngine::objectCreated, &app,
            [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
