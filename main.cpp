#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "eagle/eboard.h"
#include "tools/drillreporter.h"
#include "tools/efileinfo.h"

#include "documenttreemodel.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    DrillReporter drillReporter;
    DocumentTreeModel documentTreeModel;

    QGuiApplication app(argc, argv);
    app.setOrganizationName("SVD Company");
    app.setOrganizationDomain("svdcompany.com");
    app.setApplicationName("eTools");
    app.setWindowIcon(QIcon("://images/eTools.png"));

    qmlRegisterType<EFileInfo>("eFileInfo", 1, 0, "EFileInfo");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("drillReporter", &drillReporter);
    engine.rootContext()->setContextProperty("documentTreeModel", &documentTreeModel);

    const QUrl url(QStringLiteral("qrc:/EToolsDesktop.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
