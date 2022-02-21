#include "eattribute.h"

void EAttribute::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    if (!m_domElement.isNull() && m_domElement.tagName() == "attribute") {
        m_validFlag = true;
        bool _ok = false;

        mName = m_domElement.attribute("name");

        mX = m_domElement.attribute("x").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;

        mY = m_domElement.attribute("y").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;

        mSize = m_domElement.attribute("size").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;

        mLayer = m_domElement.attribute("layer").toInt(&_ok);
        if (!_ok)
            m_validFlag = false;

        _ok = ECommon::parseRotAttribute(m_domElement.attribute("rot"), &mAngle, &mMirror);
        if (!_ok)
            m_validFlag = false;

        mAlign = ECommon::parseAlignAttribute(m_domElement.attribute("align"));
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
}
