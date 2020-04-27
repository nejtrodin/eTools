#include "brdparser.h"

#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <QIODevice>

#include "edesignrules.h"
#include "eelement.h"
#include "elibrary.h"
#include "epackage.h"
#include "eplain.h"
#include "esignal.h"

BrdParser::BrdParser()
{
}

bool BrdParser::parse(QString filePath, ELibrary* library, EBoard* board)
{
    QDomDocument boardDoc;
    QFile boardFile(filePath);

    if (!boardFile.open(QIODevice::ReadOnly)) {
        boardFile.close();
        return false;
    }

    if (!boardDoc.setContent(&boardFile)) {
        return false;
    }

    bool result = true;

    if (boardDoc.isNull()) {
        qDebug() << "Error: BoardParser::parse. Document is null";
        result = false;
    }

    QDomElement rootElement;
    if (result) {
        rootElement = boardDoc.documentElement();
        if (rootElement.isNull()) {
            qDebug() << "Error: BoardParser::parse. domElement is null";
            result = false;
        }
    }

    if (result) {
        if (rootElement.tagName() != "eagle") {
            qDebug() << "Error: BoardParser::parse. Document is not eagle file";
            result = false;
        } else {
            QDomElement drawingElement = rootElement.firstChildElement("drawing");
            if (!drawingElement.isNull()) {
                QDomElement boardElement = drawingElement.firstChildElement("board");
                if (!boardElement.isNull()) {
                    QDomElement designrulesElement = boardElement.firstChildElement("designrules");
                    if (!designrulesElement.isNull()) {
                        EDesignRules* designrules = EDesignRules::instance();
                        designrules->parse(designrulesElement);
                    }

                    QDomElement plainElement = boardElement.firstChildElement("plain");
                    if (!plainElement.isNull()) {
                        EPlain plain = parsePlain(plainElement);
                        board->setPlain(plain);
                    }

                    QDomElement librariesElement = boardElement.firstChildElement("libraries");
                    if (!librariesElement.isNull()) {
                        QDomElement libraryElement = librariesElement.firstChildElement("library");
                        while (!libraryElement.isNull()) {
                            parseLibrary(libraryElement, library);
                            libraryElement = libraryElement.nextSiblingElement("library");
                        }
                    }

                    QDomElement elementsElement = boardElement.firstChildElement("elements");
                    if (!elementsElement.isNull()) {
                        QDomElement elementElement = elementsElement.firstChildElement("element");
                        while (!elementElement.isNull()) {
                            EElement element = parseElement(elementElement, library);
                            board->appendElement(element);
                            elementElement = elementElement.nextSiblingElement("element");
                        }

                    } // elements

                    QDomElement signalsElement = boardElement.firstChildElement("signals");
                    if (!signalsElement.isNull()) {
                        QDomElement signalElement = signalsElement.firstChildElement("signal");
                        while (!signalElement.isNull()) {
                            ESignal signal = parseSignal(signalElement);
                            board->appendSignal(signal);
                            signalElement = signalElement.nextSiblingElement("signal");
                        }
                    } // signals

                } // board
            } // drawing
        } // eagle
    }

    return result;
}

bool BrdParser::parseLibrary(QDomElement libraryElement, ELibrary* library)
{
    bool result = true;

    QString libraryName = libraryElement.attribute("name");

    QDomElement packagesElement = libraryElement.firstChildElement("packages");
    if (!packagesElement.isNull()) {
        QDomElement packageElement = packagesElement.firstChildElement("package");
        while (!packageElement.isNull()) {
            library->appendPackage(parsePackage(packageElement, libraryName));
            packageElement = packageElement.nextSiblingElement("package");
        }
    }

    return result;
}

EPlain BrdParser::parsePlain(QDomElement plainElement)
{
    EPlain plain;

    QDomElement holeElement = plainElement.firstChildElement("hole");
    while (!holeElement.isNull()) {
        QString stX = holeElement.attribute("x");
        QString stY = holeElement.attribute("y");
        QString stDrill = holeElement.attribute("drill");

        bool xParseResult;
        double x = stX.toDouble(&xParseResult);
        if (!xParseResult)
            qDebug() << "Error: BoardParser::parsePlain. Can't parse x in hole element";

        bool yParseResult;
        double y = stY.toDouble(&yParseResult);
        if (!yParseResult)
            qDebug() << "Error: BoardParser::parsePlain. Can't parse y in hole element";

        bool drillParseResult;
        double drill = stDrill.toDouble(&drillParseResult);
        if (!drillParseResult)
            qDebug() << "Error: BoardParser::parsePlain. Can't parse drill in hole element";

        Hole hole(x, y, drill);
        if (xParseResult && yParseResult && drillParseResult)
            plain.appendHole(hole);

        holeElement = holeElement.nextSiblingElement("hole");
    }

    return plain;
}

EElement BrdParser::parseElement(QDomElement elementElement, ELibrary* library)
{
    QString name = elementElement.attribute("name");
    QString stLibrary = elementElement.attribute("library");
    QString stPackage = elementElement.attribute("package");
    QString stX = elementElement.attribute("x");
    QString stY = elementElement.attribute("y");
    QString stRot = elementElement.attribute("rot", "R0");

    bool ok;
    qreal x = stX.toDouble(&ok);
    if (!ok)
        x = 0;
    qreal y = stY.toDouble(&ok);
    if (!ok)
        y = 0;

    bool mirrorFlag = false;
    if (!stRot.isEmpty() && stRot.startsWith('M')) {
        mirrorFlag = true;
        stRot = stRot.left(1);
    }

    if (!stRot.isEmpty() && stRot.startsWith('R'))
        stRot = stRot.left(1);

    qreal angle = stRot.toDouble(&ok);
    if (!ok)
        angle = 0;

    EPackage package = library->getpackage(stLibrary, stPackage);

    EElement element(name, package, x, y, angle, mirrorFlag);
    return element;
}

EPackage BrdParser::parsePackage(QDomElement packageElement, QString libraryName)
{
    QString name = packageElement.attribute("name");

    EPackage package(name, libraryName);

    // wire
    QDomElement wireElement = packageElement.firstChildElement("wire");
    while (!wireElement.isNull()) {
        bool wireParseResult = true;
        QString stX1 = wireElement.attribute("x1");
        QString stY1 = wireElement.attribute("y1");
        QString stX2 = wireElement.attribute("x2");
        QString stY2 = wireElement.attribute("y2");
        QString stWidth = wireElement.attribute("width");
        QString stLayer = wireElement.attribute("layer");

        bool ok = false;
        double x1 = stX1.toDouble(&ok);
        if (!ok) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse x1 in wire element";
            wireParseResult = false;
        }
        double y1 = stY1.toDouble(&ok);
        if (!ok) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse y1 in wire element";
            wireParseResult = false;
        }
        double x2 = stX2.toDouble(&ok);
        if (!ok) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse x2 in wire element";
            wireParseResult = false;
        }
        double y2 = stY2.toDouble(&ok);
        if (!ok) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse y2 in wire element";
            wireParseResult = false;
        }
        double width = stWidth.toDouble(&ok);
        if (!ok) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse width in wire element";
            wireParseResult = false;
        }
        int layer = stLayer.toInt(&ok);
        if (!ok) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse layer in wire element";
            wireParseResult = false;
        }

        if (wireParseResult)
            package.appendWire(x1, y1, x2, y2, width, layer);

        wireElement = wireElement.nextSiblingElement("wire");
    } // while "wire" element

    // pad
    QDomElement padElement = packageElement.firstChildElement("pad");
    while (!padElement.isNull()) {
        bool padParseResult = true;
        QString stX = padElement.attribute("x");
        QString stY = padElement.attribute("y");
        QString stName = padElement.attribute("name");
        QString stDrill = padElement.attribute("drill");
        QString stDiameter = padElement.attribute("diameter");
        QString stShape = padElement.attribute("shape");
        QString stFirst = wireElement.attribute("first");

        bool ok = false;
        double x = stX.toDouble(&ok);
        if (!ok) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse x in pad element";
            padParseResult = false;
        }

        double y = stY.toDouble(&ok);
        if (!ok) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse y in pad element";
            padParseResult = false;
        }

        double drill = stDrill.toDouble(&ok);
        if (!ok) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse drill in pad element";
            padParseResult = false;
        }

        double diameter = stDiameter.toDouble(&ok);
        if (!ok)
            diameter = 0;

        if (padParseResult)
            package.appendPad(x, y, drill, diameter);

        padElement = padElement.nextSiblingElement("pad");
    } // while "pad" element

    // hole
    QDomElement holeElement = packageElement.firstChildElement("hole");
    while (!holeElement.isNull()) {
        bool holeParseResult = true;
        QString stX = holeElement.attribute("x");
        QString stY = holeElement.attribute("y");
        QString stDrill = holeElement.attribute("drill");

        bool ok = false;
        double x = stX.toDouble(&ok);
        if (!ok) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse x in hole element";
            holeParseResult = false;
        }

        double y = stY.toDouble(&ok);
        if (!ok) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse y in hole element";
            holeParseResult = false;
        }

        double drill = stDrill.toDouble(&ok);
        if (!ok) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse drill in hole element";
            holeParseResult = false;
        }

        if (holeParseResult)
            package.appendHole(x, y, drill);

        holeElement = holeElement.nextSiblingElement("hole");
    } // while "hole" element

    return package;
}

ESignal BrdParser::parseSignal(QDomElement signalElement)
{
    QString name = signalElement.attribute("name");
    ESignal element(name);

    // via
    QDomElement viaElement = signalElement.firstChildElement("via");
    while (!viaElement.isNull()) {
        bool ok;
        Via via = parseVia(viaElement, &ok);
        if (ok)
            element.appendVia(via);

        viaElement = viaElement.nextSiblingElement("via");
    } // while "via" element

    return element;
}

Via BrdParser::parseVia(QDomElement viaElement, bool* ok)
{
    QString stX = viaElement.attribute("x");
    QString stY = viaElement.attribute("y");
    QString stExtent = viaElement.attribute("extent");
    QString stDrill = viaElement.attribute("drill");
    QString stDiameter = viaElement.attribute("diameter");

    bool xParseResult;
    double x = stX.toDouble(&xParseResult);
    if (!xParseResult)
        qDebug() << "Error: BoardParser::parsePackages. Can't parse x in pad element";

    bool yParseResult;
    double y = stY.toDouble(&yParseResult);
    if (!yParseResult)
        qDebug() << "Error: BoardParser::parsePackages. Can't parse y in pad element";

    bool drillParseResult;
    double drill = stDrill.toDouble(&drillParseResult);
    if (!drillParseResult)
        qDebug() << "Error: BoardParser::parsePackages. Can't parse drill in pad element";

    bool diameterParseResult;
    double diameter = stDiameter.toDouble(&diameterParseResult);
    if (!diameterParseResult)
        diameter = 0;

    Via via(x, y, drill, diameter);
    *ok = xParseResult && yParseResult && drillParseResult;

    return via;
}
