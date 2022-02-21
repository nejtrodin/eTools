#include "eschsheet.h"

void ESchSheet::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;
    m_nets.clear();

    if (!m_domElement.isNull() && m_domElement.tagName() == "sheet") {
        m_validFlag = true;

        QDomElement descriptionElement = m_domElement.firstChildElement("description");
        if (!descriptionElement.isNull())
            m_description = descriptionElement.text();

        QDomElement instancesElement = m_domElement.firstChildElement("instances");
        if (!instancesElement.isNull()) {
            QDomElement instanceElement = instancesElement.firstChildElement("instance");
            while (!instanceElement.isNull()) {
                ESchInstance instance;
                instance.setDomElement(instanceElement);
                if (!instance.isValid())
                    m_validFlag = false;
                m_instances.append(instance);

                instanceElement = instanceElement.nextSiblingElement("instance");
            }
        }

        QDomElement netsElement = m_domElement.firstChildElement("nets");
        if (!netsElement.isNull()) {
            QDomElement netElement = netsElement.firstChildElement("net");
            while (!netElement.isNull()) {
                ESchNet net;
                net.setDomElement(netElement);
                if (!net.isValid())
                    m_validFlag = false;
                m_nets.append(net);

                netElement = netElement.nextSiblingElement("net");
            }
        }

        // FIX: create class for bus
        QDomElement busesElement = m_domElement.firstChildElement("busses");
        if (!busesElement.isNull()) {
            QDomElement busElement = busesElement.firstChildElement("bus");
            while (!busElement.isNull()) {
                ESchNet bus;
                bus.setDomElement(busElement);
                if (!bus.isValid())
                    m_validFlag = false;
                m_nets.append(bus);

                busElement = busElement.nextSiblingElement("bus");
            }
        }

        QDomElement plainElement = m_domElement.firstChildElement("plain");
        if (!plainElement.isNull()) {
            m_plain.setDomElement(plainElement);
            if (!m_plain.isValid())
                m_validFlag = false;
        }
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
}

void ESchSheet::paint(QPainter *painter, SchSettings *settings, ESchCore *schCore)
{
    m_plain.paint(painter, settings);

    QVector<ESchNet>::iterator iNet;
    for (iNet = m_nets.begin(); iNet != m_nets.end(); ++iNet) {
        iNet->paint(painter, settings);
    }

    QVector<ESchInstance>::iterator iInstance;
    for (iInstance = m_instances.begin(); iInstance != m_instances.end(); ++iInstance) {
        iInstance->paint(painter, settings, schCore);
    }
}
