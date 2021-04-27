#include "eschpart.h"

void ESchPart::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;

    if (!mElement.isNull() && mElement.tagName() == "part") {
        mValidFlag = true;
        mName = mElement.attribute("name");
        mLibrary = mElement.attribute("library");
        mLibraryUrn = mElement.attribute("library_urn");
        mDevicesetName = mElement.attribute("deviceset");
        mDeviceName = mElement.attribute("device");
        mValue = mElement.attribute("value", "");
        mTechnology = mElement.attribute("technology", "");

        // attributes
        QDomElement attributeElement = mElement.firstChildElement("attribute");
        while (!attributeElement.isNull()) {
            EValueAttribute valueAttribute;
            valueAttribute.setDomElement(attributeElement);
            if (!valueAttribute.isValid())
                mValidFlag = false;
            mValueAttributes.insert(valueAttribute.name(), valueAttribute);

            attributeElement = attributeElement.nextSiblingElement("attribute");
        }
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

QString ESchPart::getAttribute(QString attributeName)
{
    if (mValueAttributes.contains(attributeName))
        return mValueAttributes[attributeName].value();
    else
        return QString();
}
