#include "eschpart.h"

void ESchPart::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    if (!m_domElement.isNull() && m_domElement.tagName() == "part") {
        m_validFlag = true;
        m_name = m_domElement.attribute("name");
        m_library = m_domElement.attribute("library");
        m_libraryUrn = m_domElement.attribute("library_urn");
        m_devicesetName = m_domElement.attribute("deviceset");
        m_deviceName = m_domElement.attribute("device");
        m_value = m_domElement.attribute("value", "");
        m_technology = m_domElement.attribute("technology", "");

        // attributes
        QDomElement attributeElement = m_domElement.firstChildElement("attribute");
        while (!attributeElement.isNull()) {
            EValueAttribute valueAttribute;
            valueAttribute.setDomElement(attributeElement);
            if (!valueAttribute.isValid())
                m_validFlag = false;
            m_valueAttributes.insert(valueAttribute.name(), valueAttribute);

            attributeElement = attributeElement.nextSiblingElement("attribute");
        }
    }

    if (!m_validFlag) {
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
    }
}

QString ESchPart::getAttribute(QString attributeName)
{
    if (m_valueAttributes.contains(attributeName))
        return m_valueAttributes[attributeName].value();
    else
        return QString();
}
