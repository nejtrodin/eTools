#include "evalueattribute.h"

void EValueAttribute::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = true;

    if (!mElement.isNull() && mElement.tagName() == "attribute") {
        mName = mElement.attribute("name");
        mValue = mElement.attribute("value");
        QString constantValue = mElement.attribute("constant");
        if (constantValue.isEmpty())
            mConstant = true;
        else if (constantValue == "no")
            mConstant = false;
        else
            mValidFlag = false;
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}
