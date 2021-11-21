#include "etechnology.h"

void ETechnology::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;

    if (!mElement.isNull() && mElement.tagName() == "technology") {
        mValidFlag = true;
        mName = mElement.attribute("name");

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

QString ETechnology::getAttribute(QString attributeName)
{
    if (mValueAttributes.contains(attributeName))
        return mValueAttributes[attributeName].value();
    else
        return QString();
}
