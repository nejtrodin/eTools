#include "epad.h"
#include "edesignrules.h"


void EPad::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    if (!rootElement.isNull() && rootElement.tagName() == "pad") {
        m_validFlag = true;
        QString stX = rootElement.attribute("x");
        QString stY = rootElement.attribute("y");
        QString stName = rootElement.attribute("name");
        QString stDrill = rootElement.attribute("drill");
        QString stDiameter = rootElement.attribute("diameter");
        QString stShape = rootElement.attribute("shape");
        QString stFirst = rootElement.attribute("first");

        bool xParseResult;
        bool yParseResult;
        m_position.setX(stX.toDouble(&xParseResult));
        if (!xParseResult) {
            qDebug() << "Error: EPad. Can't parse x\n  " << rootElement.text();
        }
        m_position.setY(stY.toDouble(&yParseResult));
        if (!yParseResult) {
            qDebug() << "Error: EPad. Can't parse y\n  " << rootElement.text();
        }

        bool drillParseResult;
        m_drill = stDrill.toDouble(&drillParseResult);
        if (!drillParseResult) {
            qDebug() << "Error: EPad. Can't parse drill\n  " << rootElement.text();
        }

        // If the diameter is empty then it is zero - correct situation
        m_diameter = stDiameter.toDouble();

        update();
        m_validFlag = xParseResult && yParseResult && drillParseResult;
    }

    if (!m_validFlag) {
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
    }
}

void EPad::update()
{
    EDesignRules* designRules = EDesignRules::instance();
    double topDiameter = m_diameter;
    double innerDiameter = m_diameter;
    double bottomDiameter = m_diameter;

    // DRC for Min preferred over fixed diameter
    if (designRules->isValid()) {
        if (m_diameter <= 0) {
            topDiameter = m_drill + 2 * m_drill * designRules->getRvPadTop();
            innerDiameter = m_drill + 2 * m_drill * designRules->getRvPadInner();
            bottomDiameter = m_drill + 2 * m_drill * designRules->getRvPadBottom();

            double maxTopDiameter = m_drill + 2 * designRules->getRlMaxPadTop();
            if (topDiameter > maxTopDiameter)
                topDiameter = maxTopDiameter;

            double maxBottomDiameter = m_drill + 2 * designRules->getRlMaxPadBottom();
            if (bottomDiameter > maxBottomDiameter)
                bottomDiameter = maxBottomDiameter;

            double maxInnerDiameter = m_drill + 2 * designRules->getRlMaxPadInner();
            if (innerDiameter > maxInnerDiameter)
                innerDiameter = maxInnerDiameter;
        }

        double minTopDiameter = m_drill + 2 * designRules->getRlMinPadTop();
        if (topDiameter < minTopDiameter)
            topDiameter = minTopDiameter;

        double minBottomDiameter = m_drill + 2 * designRules->getRlMinPadBottom();
        if (bottomDiameter < minBottomDiameter)
            bottomDiameter = minBottomDiameter;

        double minInnerDiameter = m_drill + 2 * designRules->getRlMinPadInner();
        if (innerDiameter < minInnerDiameter)
            innerDiameter = minInnerDiameter;
    }

    m_topDiameter = topDiameter;
    m_bottomDiameter = bottomDiameter;
    m_innerDiameter = innerDiameter;
}
