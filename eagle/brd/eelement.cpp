#include "eelement.h"

void EElement::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    if (!m_domElement.isNull() && m_domElement.tagName() == "element") {
        m_validFlag = true;
        m_name = rootElement.attribute("name");
        m_libraryName = rootElement.attribute("library");
        m_packageName = rootElement.attribute("package");
        QString stX = rootElement.attribute("x");
        QString stY = rootElement.attribute("y");
        QString stRot = rootElement.attribute("rot", "R0");

        bool xParseResult;
        bool yParseResult;
        qreal x = stX.toDouble(&xParseResult);
        if (!xParseResult) {
            qDebug() << "Error: EElement::setDomElement. Can't parse 'x'";
        }
        qreal y = stY.toDouble(&yParseResult);
        if (!yParseResult) {
            qDebug() << "Error: EElement::setDomElement. Can't parse 'y'";
        }
        m_position = QPointF(x, y);

        // process of "rot" paremeter. May be empty or [M]R<angle>
        bool angleParseResult = ECommon::parseRotAttribute(stRot, &m_angle, &m_mirror);
        if (!angleParseResult) {
            qDebug() << "Error: EElement::setDomElement. Can't parse 'rot' angle";
        }

        if(!xParseResult || !yParseResult || !angleParseResult) {
            m_validFlag = false;
        }
    }

    if (!m_validFlag) {
        qDebug() << "Parse error. EElement. Line:" << m_domElement.lineNumber();
    }
}

const QString &EElement::libraryName() const
{
    return m_libraryName;
}

const QString &EElement::packageName() const
{
    return m_packageName;
}
