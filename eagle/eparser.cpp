#include "eparser.h"

EParser::EParser() {}


EPackage EParser::parsePackage(QDomElement packageElement, QString libraryName, bool *ok)
{
    bool packageParseResult = true;
    EPackage package;
    package.setLibraryName(libraryName);

    if (!packageElement.isNull() && packageElement.tagName() == "package") {
        package.setName(packageElement.attribute("name"));

//        // wire
//        QDomElement wireElement = packageElement.firstChildElement("wire");
//        while (!wireElement.isNull()) {
//            bool _ok;
//            auto wire = parseWire(wireElement, &_ok);
//            if (_ok)
//                package.appendWire(wire);
//            else {
//                qDebug() << "Error: EParser::parsePackage. Can't parse wire element\n  "
//                         << wireElement.text();
//                packageParseResult = false;
//            }

//            wireElement = wireElement.nextSiblingElement("wire");
//        } // while "wire" element

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
//            QString stFirst = wireElement.attribute("first");

            bool _ok;
            double x = stX.toDouble(&_ok);
            if (!_ok) {
                qDebug() << "Error: BoardParser::parsePackages. Can't parse x in pad element\n  "
                         << padElement.text();
                padParseResult = false;
            }

            double y = stY.toDouble(&_ok);
            if (!_ok) {
                qDebug() << "Error: BoardParser::parsePackages. Can't parse y in pad element\n  "
                         << padElement.text();
                padParseResult = false;
            }

            double drill = stDrill.toDouble(&_ok);
            if (!_ok) {
                qDebug() << "Error: BoardParser::parsePackages. Can't parse drill in pad element\n  "
                         << padElement.text();
                padParseResult = false;
            }

            double diameter = stDiameter.toDouble(&_ok);
            if (!_ok)
                diameter = 0;

            if (padParseResult)
                package.appendPad(x, y, drill, diameter);
            else
                packageParseResult = false;

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
                qDebug() << "Error: BoardParser::parsePackages. Can't parse x in hole element\n  "
                         << holeElement.text();
                holeParseResult = false;
            }

            double y = stY.toDouble(&ok);
            if (!ok) {
                qDebug() << "Error: BoardParser::parsePackages. Can't parse y in hole element\n  "
                         << holeElement.text();;
                holeParseResult = false;
            }

            double drill = stDrill.toDouble(&ok);
            if (!ok) {
                qDebug() << "Error: BoardParser::parsePackages. Can't parse drill in hole element\n  "
                         << holeElement.text();;
                holeParseResult = false;
            }

            if (holeParseResult)
                package.appendHole(x, y, drill);
            else
                packageParseResult = false;

            holeElement = holeElement.nextSiblingElement("hole");
        } // while "hole" element

    } else
        packageParseResult = false;

    if (ok != nullptr)
        *ok = packageParseResult;

    return package;
}
