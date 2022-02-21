#include "esignal.h"

void ESignal::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    m_vias.clear();

    if (!m_domElement.isNull() && m_domElement.tagName() == "signal") {
        m_validFlag = true;
        m_name = m_domElement.attribute("name");

        // via
        QDomElement viaElement = m_domElement.firstChildElement("via");
        while (!viaElement.isNull()) {
            EBrdVia via;
            via.setDomElement(viaElement);
            m_vias.append(via);

            viaElement = viaElement.nextSiblingElement("via");
        } // while "via" element
    }

    if (!m_validFlag) {
        qDebug() << "Parse error. ESignal. Line:" << m_domElement.lineNumber();
    }
}

void ESignal::appendVia(EBrdVia via)
{
    m_vias.append(via);
}
