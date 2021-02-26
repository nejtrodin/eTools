#include "eschsheet.h"

void ESchSheet::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;
    mNets.clear();

    if (!mElement.isNull() && mElement.tagName() == "sheet") {
        mValidFlag = true;

        QDomElement descriptionElement = mElement.firstChildElement("description");
        if (!descriptionElement.isNull())
            mDescription = descriptionElement.text();

        QDomElement instancesElement = mElement.firstChildElement("instances");
        if (!instancesElement.isNull()) {
            QDomElement instanceElement = instancesElement.firstChildElement("instance");
            while (!instanceElement.isNull()) {
                ESchInstance instance;
                instance.setDomElement(instanceElement);
                if (!instance.isValid())
                    mValidFlag = false;
                mInstances.append(instance);

                instanceElement = instanceElement.nextSiblingElement("instance");
            }
        }

        QDomElement netsElement = mElement.firstChildElement("nets");
        if (!netsElement.isNull()) {
            QDomElement netElement = netsElement.firstChildElement("net");
            while (!netElement.isNull()) {
                ESchNet net;
                net.setDomElement(netElement);
                if (!net.isValid())
                    mValidFlag = false;
                mNets.append(net);

                netElement = netElement.nextSiblingElement("net");
            }
        }

        // FIX: create class for bus
        QDomElement busesElement = mElement.firstChildElement("busses");
        if (!busesElement.isNull()) {
            QDomElement busElement = busesElement.firstChildElement("bus");
            while (!busElement.isNull()) {
                ESchNet bus;
                bus.setDomElement(busElement);
                if (!bus.isValid())
                    mValidFlag = false;
                mNets.append(bus);

                busElement = busElement.nextSiblingElement("bus");
            }
        }

        QDomElement plainElement = mElement.firstChildElement("plain");
        if (!plainElement.isNull()) {
            mPlain.setDomElement(plainElement);
            if (!mPlain.isValid())
                mValidFlag = false;
        }
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

void ESchSheet::paint(QPainter *painter, Settings *settings, ESchCore *schCore)
{
    mPlain.paint(painter, settings);

    QVector<ESchNet>::iterator iNet;
    for (iNet = mNets.begin(); iNet != mNets.end(); ++iNet) {
        iNet->paint(painter, settings);
    }

    QVector<ESchInstance>::iterator iInstance;
    for (iInstance = mInstances.begin(); iInstance != mInstances.end(); ++iInstance) {
        iInstance->paint(painter, settings, schCore);
    }
}
