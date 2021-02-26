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

void EPin::paint(QPainter *painter, QString padName, Settings *settings)
{
    painter->save();
    painter->translate(QPointF(mX * settings->schScale, -mY * settings->schScale));
    painter->rotate(-mAngle);

    QPen pen = painter->pen();
    pen.setColor(settings->getColor(94));
    // TODO: add default pin width in settings
    //    pen.setWidth(iWire->width*settings->schScale);
    painter->setPen(pen);
    painter->drawLine(QPointF(0, 0), QPointF(mLength * settings->schScale, 0));

    painter->drawText(0, 0, padName);

    painter->restore();
}

qreal EPin::parseLengthAttribute(QString lengthValue)
{
    if (lengthValue == "long")
        return 7.62;
    else if (lengthValue == "middle")
        return 5.08;
    else if (lengthValue == "short")
        return 2.54;
    else /* point and other */
        return 0;
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
