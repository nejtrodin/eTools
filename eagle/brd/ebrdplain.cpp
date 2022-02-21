#include "ebrdplain.h"

void EBrdPlain::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    if (!m_domElement.isNull() && m_domElement.tagName() == "plain") {
        m_validFlag = true;

        QDomElement holeElement = rootElement.firstChildElement("hole");
        while (!holeElement.isNull()) {
            QString stX = holeElement.attribute("x");
            QString stY = holeElement.attribute("y");
            QString stDrill = holeElement.attribute("drill");

            bool xParseResult;
            double x = stX.toDouble(&xParseResult);
            if (!xParseResult) {
                qDebug() << "Error: EBrdPlain. Can't parse x in hole element";
            }

            bool yParseResult;
            double y = stY.toDouble(&yParseResult);
            if (!yParseResult) {
                qDebug() << "Error: EBrdPlain. Can't parse y in hole element";
            }

            bool drillParseResult;
            double drill = stDrill.toDouble(&drillParseResult);
            if (!drillParseResult) {
                qDebug() << "Error: EBrdPlain. Can't parse drill in hole element";
            }

            if (xParseResult && yParseResult && drillParseResult) {
                Hole hole(x, y, drill);
                eHoles.append(hole);
            }
            else {
                m_validFlag = false;
            }

            holeElement = holeElement.nextSiblingElement("hole");
        }
    }

    if (!m_validFlag) {
        qDebug() << "Parse error. EBrdPlain. Line:" << m_domElement.lineNumber();
    }
}

void EBrdPlain::appendHole(Hole hole)
{
    eHoles.append(hole);
}
