#include "ebrdvia.h"
#include "edesignrules.h"

void EBrdVia::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    if (!m_domElement.isNull() && m_domElement.tagName() == "via") {
        QString stX = m_domElement.attribute("x");
        QString stY = m_domElement.attribute("y");
        QString stExtent = m_domElement.attribute("extent");
        QString stDrill = m_domElement.attribute("drill");
        QString stDiameter = m_domElement.attribute("diameter");

        bool xParseResult;
        m_position.setX(stX.toDouble(&xParseResult));
        if (!xParseResult) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse x in pad element";
        }

        bool yParseResult;
        m_position.setY(stY.toDouble(&yParseResult));
        if (!yParseResult) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse y in pad element";
        }

        bool drillParseResult;
        m_drill = stDrill.toDouble(&drillParseResult);
        if (!drillParseResult) {
            qDebug() << "Error: BoardParser::parsePackages. Can't parse drill in pad element";
        }

        bool diameterParseResult;
        m_diameter = stDiameter.toDouble(&diameterParseResult);
        if (!diameterParseResult) {
            m_diameter = 0;
        }

        m_validFlag = xParseResult && yParseResult && drillParseResult;
        update();
    }

    if (!m_validFlag) {
        qDebug() << "Parse error. EBrdVia. Line:" << m_domElement.lineNumber();
    }
}

void EBrdVia::update()
{
    EDesignRules* designRules = EDesignRules::instance();
    double innerDiameter = m_diameter;
    double outerDiameter = m_diameter;

    // DRC for Min preferred over fixed diameter
    if (designRules->isValid()) {
        if (m_diameter <= 0) {
            innerDiameter = m_drill + 2 * m_drill * designRules->getRvViaInner();
            outerDiameter = m_drill + 2 * m_drill * designRules->getRvViaOuter();

            double maxOuterDiameter = m_drill + 2 * designRules->getRlMaxViaOuter();
            if (outerDiameter > maxOuterDiameter)
                outerDiameter = maxOuterDiameter;

            double maxInnerDiameter = m_drill + 2 * designRules->getRlMaxViaInner();
            if (innerDiameter > maxInnerDiameter)
                innerDiameter = maxInnerDiameter;
        }

        double minOuterDiameter = m_drill + 2 * designRules->getRlMinViaOuter();
        if (outerDiameter < minOuterDiameter)
            outerDiameter = minOuterDiameter;

        double minInnerDiameter = m_drill + 2 * designRules->getRlMinViaInner();
        if (innerDiameter < minInnerDiameter)
            innerDiameter = minInnerDiameter;
    }

    m_innerDiameter = innerDiameter;
    m_outerDiameter = outerDiameter;
}
