#include "eattribute.h"
#include "../eparser.h"

void EAttribute::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;

    if (!mElement.isNull() && mElement.tagName() == "attribute") {
        mValidFlag = true;
        bool _ok = false;

        mName = mElement.attribute("name");

        mX = mElement.attribute("x").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;

        mY = mElement.attribute("y").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;

        mSize = mElement.attribute("size").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;

        mLayer = mElement.attribute("layer").toInt(&_ok);
        if (!_ok)
            mValidFlag = false;

        _ok = ECommon::parseRotAttribute(mElement.attribute("rot"), &mAngle, &mMirror);
        if (!_ok)
            mValidFlag = false;

        mAlign = ECommon::parseAlignAttribute(mElement.attribute("align"));
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}
