#include "epackage.h"

EPackage::EPackage()
{
    m_boundX1 = 0;
    m_boundY1 = 0;
    m_boundX2 = 0;
    m_boundY2 = 0;
}

void EPackage::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    // clear all
    m_wires.clear();
    m_pads.clear();
    m_holes.clear();

    if (!rootElement.isNull() && rootElement.tagName() == "package") {
        m_validFlag = true;
        mName = rootElement.attribute("name");

        // wire
        QDomElement wireElement = rootElement.firstChildElement("wire");
        while (!wireElement.isNull()) {
            EWire wire;
            wire.setDomElement(wireElement);
            m_wires.append(wire);

            if (!wire.isValid()) {
                qDebug() << "Error: EPackage. Can't parse wire element\n  " << wireElement.text();
                m_validFlag = false;
            }

            wireElement = wireElement.nextSiblingElement("wire");
        } // while "wire" element

        // pad
        QDomElement padElement = rootElement.firstChildElement("pad");
        while (!padElement.isNull()) {
            EPad pad;
            pad.setDomElement(padElement);
            m_pads.append(pad);

            if (!pad.isValid()) {
                qDebug() << "Error: EPackage. Can't parse pad element\n  " << wireElement.text();
                m_validFlag = false;
            }

            padElement = padElement.nextSiblingElement("pad");
        } // while "pad" element

        // hole
        QDomElement holeElement = rootElement.firstChildElement("hole");
        while (!holeElement.isNull()) {
            bool holeParseResult = true;
            QString stX = holeElement.attribute("x");
            QString stY = holeElement.attribute("y");
            QString stDrill = holeElement.attribute("drill");

            bool ok = false;
            double x = stX.toDouble(&ok);
            if (!ok) {
                qDebug() << "Error: EPackage. Can't parse x in hole element\n  "
                         << holeElement.text();
                holeParseResult = false;
            }

            double y = stY.toDouble(&ok);
            if (!ok) {
                qDebug() << "Error: EPackage. Can't parse y in hole element\n  "
                         << holeElement.text();;
                holeParseResult = false;
            }

            double drill = stDrill.toDouble(&ok);
            if (!ok) {
                qDebug() << "Error: EPackage. Can't parse drill in hole element\n  "
                         << holeElement.text();;
                holeParseResult = false;
            }

            if (holeParseResult) {
                Hole hole(x, y, drill);
                m_holes.append(hole);
            }
            else {
                m_validFlag = false;
            }

            holeElement = holeElement.nextSiblingElement("hole");
        } // while "hole" element

    }

    if (!m_validFlag) {
        qDebug() << "Parse EPackage error. Line:" << m_domElement.lineNumber();
    }
}
