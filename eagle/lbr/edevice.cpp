#include "edevice.h"

void EDevice::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = true;
    mConnects.clear();

    if (!mElement.isNull() && mElement.tagName() == "device") {
        mName = mElement.attribute("name");
        mPackageName = mElement.attribute("package");

        // connects
        QDomElement connectsElement = mElement.firstChildElement("connects");
        if (!connectsElement.isNull()) {
            QDomElement connectElement = connectsElement.firstChildElement("connect");
            while (!connectElement.isNull()) {
                EConnect connect;
                connect.gate = connectElement.attribute("gate");
                connect.pin = connectElement.attribute("pin");
                connect.pad = connectElement.attribute("pad");
                mConnects.insert(connect.gate, connect);

                connectElement = connectElement.nextSiblingElement("connect");
            }
        }

        // technologies
        QDomElement technologiesElement = mElement.firstChildElement("technologies");
        if (!technologiesElement.isNull()) {
            QDomElement technologyElement = technologiesElement.firstChildElement("technology");
            while (!technologyElement.isNull()) {
                ETechnology technology;
                technology.setDomElement(technologyElement);
                if (!technology.isValid())
                    mValidFlag = false;
                mTechnologies.insert(technology.name(), technology);

                technologyElement = technologyElement.nextSiblingElement("technology");
            }
        }
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

QList<EConnect> EDevice::getConnects(QString gateName)
{
    return mConnects.values(gateName);
}

QList<EValueAttribute> EDevice::getAttributes(QString technologyName)
{
    if (mTechnologies.contains(technologyName))
        return mTechnologies[technologyName].getAttributes();
    else {
        QList<EValueAttribute> emptyList;
        return emptyList;
    }
}

QString EDevice::getAttribute(QString technologyName, QString attributeName)
{
    if (mTechnologies.contains(technologyName)) {
        return mTechnologies[technologyName].getAttribute(attributeName);
    }
    else {
        return QString();
    }
}
