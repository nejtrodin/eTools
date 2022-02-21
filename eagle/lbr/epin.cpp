#include "epin.h"

void EPin::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    if (!m_domElement.isNull() && m_domElement.tagName() == "pin") {
        m_validFlag = true;
        m_name = m_domElement.attribute("name");
        m_x = m_domElement.attribute("x").toDouble();
        m_y = m_domElement.attribute("y").toDouble();
        m_length = parseLengthAttribute(m_domElement.attribute("length"));
        m_visible = parseVisibleAttribute(m_domElement.attribute("visible"));
        QString rot = m_domElement.attribute("rot");
        ECommon::parseRotAttribute(rot, &m_angle, &m_mirrorFlag);
    }

    if (!m_validFlag) {
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
    }
}

qreal EPin::parseLengthAttribute(QString lengthValue)
{
    if (lengthValue == "middle")
        return 5.08;
    else if (lengthValue == "short")
        return 2.54;
    else if (lengthValue == "point")
        return 0;
    else /* long */
        return 7.62;
}

EPin::PinVisible EPin::parseVisibleAttribute(QString visibleValue)
{
    PinVisible visible = VisibleBoth;
    if (visibleValue == "pin")
        visible = VisiblePin;
    else if (visibleValue == "pad")
        visible = VisiblePad;
    if (visibleValue == "off")
        visible = VisibleOff;

    return visible;
}
