#include "elayer.h"


void ELayer::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    if (!m_domElement.isNull() && m_domElement.tagName() == "layer") {
        m_validFlag = true;

        bool ok = false;

        int number = m_domElement.attribute("number").toInt(&ok);
        if (ok)
            mLayer.number = number;
        else
            m_validFlag = false;


        QString name = m_domElement.attribute("name");
        if (name.isEmpty())
            m_validFlag = false;
        else
            mLayer.name = name;

        int color = m_domElement.attribute("color").toInt(&ok);
        if (ok)
            mLayer.colorNumber = color;
        else
            m_validFlag = false;

        int fill = m_domElement.attribute("fill").toInt(&ok);
        if (ok)
            mLayer.fill = fill;
        else
            m_validFlag = false;

        QString visibleSt = m_domElement.attribute("visible");
        if (visibleSt == "yes")
            mLayer.visible = true;
        else if (visibleSt == "no")
            mLayer.visible = false;
        else
            m_validFlag = false;

        QString activeSt = m_domElement.attribute("active");
        if (activeSt == "yes")
            mLayer.active = true;
        else if (activeSt == "no")
            mLayer.active = false;
        else
            m_validFlag = false;
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
}
