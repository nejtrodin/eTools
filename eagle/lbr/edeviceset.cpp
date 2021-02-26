#include "edeviceset.h"

void EDeviceset::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = true;
    mGates.clear();
    mDevices.clear();

    if (!mElement.isNull() && mElement.tagName() == "deviceset") {
        mName = mElement.attribute("name");
        mPrefix = mElement.attribute("prefix");
        QDomElement descriptionElement = mElement.firstChildElement("description");
        mDescription = descriptionElement.text();

        // gates
        QDomElement gatesElement = mElement.firstChildElement("gates");
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
        QDomElement devicesElement = mElement.firstChildElement("devices");
        if (!devicesElement.isNull()) {
            // device
            QDomElement deviceElement = devicesElement.firstChildElement("device");
            while (!deviceElement.isNull()) {
                EDevice device;
                device.setDomElement(deviceElement);
                if (!device.isValid())
                    mValidFlag = false;
                mDevices.insert(device.name(), device);

                deviceElement = deviceElement.nextSiblingElement("device");
            }
        }
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
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
