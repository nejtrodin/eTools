#include "edevice.h"

void EDevice::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = true;
    mConnects.clear();

    if (!m_domElement.isNull() && m_domElement.tagName() == "device") {
        mName = m_domElement.attribute("name");
        mPackageName = m_domElement.attribute("package");

        // connects
        QDomElement connectsElement = m_domElement.firstChildElement("connects");
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
        QDomElement technologiesElement = m_domElement.firstChildElement("technologies");
        if (!technologiesElement.isNull()) {
            QDomElement technologyElement = technologiesElement.firstChildElement("technology");
            while (!technologyElement.isNull()) {
                ETechnology technology;
                technology.setDomElement(technologyElement);
                if (!technology.isValid())
                    m_validFlag = false;
                mTechnologies.insert(technology.name(), technology);

                technologyElement = technologyElement.nextSiblingElement("technology");
            }
        }
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
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
