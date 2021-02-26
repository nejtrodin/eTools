#include "brdparser.h"

#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <QIODevice>

#include "brd/edesignrules.h"
#include "eelement.h"
#include "lbr/elibrary.h"
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
                        EBrdPlain plain = parsePlain(plainElement);
                        board->setPlain(plain);
                    }

//                    QDomElement librariesElement = boardElement.firstChildElement("libraries");
//                    if (!librariesElement.isNull()) {
//                        QDomElement libraryElement = librariesElement.firstChildElement("library");
//                        while (!libraryElement.isNull()) {
//                            bool _ok;
//                            ELibrary library;
//                            library.setDomElement(libraryElement);
//                            auto _library = parseLibrary(libraryElement, &_ok);
//                            if (_ok)
//                                *library = _library;
//                            libraryElement = libraryElement.nextSiblingElement("library");
//                        }
//                    }

//                    QDomElement elementsElement = boardElement.firstChildElement("elements");
//                    if (!elementsElement.isNull()) {
//                        QDomElement elementElement = elementsElement.firstChildElement("element");
//                        while (!elementElement.isNull()) {
//                            EElement element = parseElement(elementElement, library);
//                            board->appendElement(element);
//                            elementElement = elementElement.nextSiblingElement("element");
//                        }

//                    } // elements

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

EBrdPlain BrdParser::parsePlain(QDomElement plainElement)
{
    EBrdPlain plain;

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

//EElement BrdParser::parseElement(QDomElement elementElement, ELibrary* library)
//{
//    QString name = elementElement.attribute("name");
//    QString stLibrary = elementElement.attribute("library");
//    QString stPackage = elementElement.attribute("package");
//    QString stX = elementElement.attribute("x");
//    QString stY = elementElement.attribute("y");
//    QString stRot = elementElement.attribute("rot", "R0");

//    bool ok;
//    qreal x = stX.toDouble(&ok);
//    if (!ok)
//        x = 0;
//    qreal y = stY.toDouble(&ok);
//    if (!ok)
//        y = 0;

//    bool mirrorFlag = false;
//    if (!stRot.isEmpty() && stRot.startsWith('M')) {
//        mirrorFlag = true;
//        stRot = stRot.left(1);
//    }

//    if (!stRot.isEmpty() && stRot.startsWith('R'))
//        stRot = stRot.left(1);

//    qreal angle = stRot.toDouble(&ok);
//    if (!ok)
//        angle = 0;

////    EPackage package = library->getpackage(stLibrary, stPackage);

//    EElement element(name, package, x, y, angle, mirrorFlag);
//    return element;
//}

ESignal BrdParser::parseSignal(QDomElement signalElement)
{
    QString name = signalElement.attribute("name");
    ESignal element(name);

    // via
    QDomElement viaElement = signalElement.firstChildElement("via");
    while (!viaElement.isNull()) {
        bool ok;
        EBrdVia via = parseVia(viaElement, &ok);
        if (ok)
            element.appendVia(via);

        viaElement = viaElement.nextSiblingElement("via");
    } // while "via" element

    return element;
}

EBrdVia BrdParser::parseVia(QDomElement viaElement, bool* ok)
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

    EBrdVia via(x, y, drill, diameter);
    *ok = xParseResult && yParseResult && drillParseResult;

    return via;
}
