#include "edeviceset.h"

void EDeviceset::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = true;
    mGates.clear();
    mDevices.clear();

    if (!m_domElement.isNull() && m_domElement.tagName() == "deviceset") {
        mName = m_domElement.attribute("name");
        mPrefix = m_domElement.attribute("prefix");
        QDomElement descriptionElement = m_domElement.firstChildElement("description");
        mDescription = descriptionElement.text();

        QString uservalueString = m_domElement.attribute("uservalue");
        if (uservalueString == "yes")
            mUservalue = true;
        else
            mUservalue = false;

        // gates
        QDomElement gatesElement = m_domElement.firstChildElement("gates");
        if (!gatesElement.isNull()) {
            QDomElement gateElement = gatesElement.firstChildElement("gate");
            while (!gateElement.isNull()) {
                QString gateName = gateElement.attribute("name");
                QString gateSymbol = gateElement.attribute("symbol");
                EGate gate(gateName, gateSymbol);
                mGates.insert(gateName, gate);

                gateElement = gateElement.nextSiblingElement("gate");
            }
        }

        // devices
        QDomElement devicesElement = m_domElement.firstChildElement("devices");
        if (!devicesElement.isNull()) {
            // device
            QDomElement deviceElement = devicesElement.firstChildElement("device");
            while (!deviceElement.isNull()) {
                EDevice device;
                device.setDomElement(deviceElement);
                if (!device.isValid())
                    m_validFlag = false;
                mDevices.insert(device.name(), device);

                deviceElement = deviceElement.nextSiblingElement("device");
            }
        }
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
}

EDevice EDeviceset::getDevice(const QString &deviceName)
{
    if (mDevices.contains(deviceName))
        return mDevices[deviceName];
    else
        return EDevice();
}

EGate EDeviceset::getGate(const QString &gateName)
{
    if (mGates.contains(gateName))
        return mGates[gateName];
    else
        return EGate();
}
