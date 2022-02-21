#include "etechnology.h"

void ETechnology::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    if (!m_domElement.isNull() && m_domElement.tagName() == "technology") {
        m_validFlag = true;
        mName = m_domElement.attribute("name");

        // attributes
        QDomElement attributeElement = m_domElement.firstChildElement("attribute");
        while (!attributeElement.isNull()) {
            EValueAttribute valueAttribute;
            valueAttribute.setDomElement(attributeElement);
            if (!valueAttribute.isValid())
                m_validFlag = false;
            mValueAttributes.insert(valueAttribute.name(), valueAttribute);

            attributeElement = attributeElement.nextSiblingElement("attribute");
        }
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
}

QString ETechnology::getAttribute(QString attributeName)
{
    if (mValueAttributes.contains(attributeName))
        return mValueAttributes[attributeName].value();
    else
        return QString();
}
