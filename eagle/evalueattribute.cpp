#include "evalueattribute.h"

void EValueAttribute::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = true;

    if (!m_domElement.isNull() && m_domElement.tagName() == "attribute") {
        mName = m_domElement.attribute("name");
        mValue = m_domElement.attribute("value");
        QString constantValue = m_domElement.attribute("constant");
        if (constantValue.isEmpty())
            mConstant = true;
        else if (constantValue == "no")
            mConstant = false;
        else
            m_validFlag = false;
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
}
