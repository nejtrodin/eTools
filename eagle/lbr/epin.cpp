#include "epin.h"
#include "../eparser.h"

void EPin::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;

    if (!mElement.isNull() && mElement.tagName() == "pin") {
        mValidFlag = true;
        mName = mElement.attribute("name");
        mX = mElement.attribute("x").toDouble();
        mY = mElement.attribute("y").toDouble();
        mLength = parseLengthAttribute(mElement.attribute("length"));
        mVisible = parseVisibleAttribute(mElement.attribute("visible"));
        QString rot = mElement.attribute("rot");
        ECommon::parseRotAttribute(rot, &mAngle, &mMirrorFlag);
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

qreal EPin::parseLengthAttribute(QString lengthValue)
{
    if (lengthValue == "middle")
        return 5.08;
    else if (lengthValue == "short")
        return 2.54;
    else if (lengthValue == "point")
        return 0;
    else /* long */
        return 7.62;
}

EPin::PinVisible EPin::parseVisibleAttribute(QString visibleValue)
{
    PinVisible visible = VisibleBoth;
    if (visibleValue == "pin")
        visible = VisiblePin;
    else if (visibleValue == "pad")
        visible = VisiblePad;
    if (visibleValue == "off")
        visible = VisibleOff;

    return visible;
}
