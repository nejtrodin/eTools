#include "etext.h"
#include "../eparser.h"

void ELabel::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;

    if (!mElement.isNull() && mElement.tagName() == "label") {
        bool ok = false;
        mValidFlag = true;

        mX = mElement.attribute("x").toDouble(&ok);
        if (!ok) mValidFlag = false;

        mY = mElement.attribute("y").toDouble(&ok);
        if (!ok) mValidFlag = false;

        mSize = mElement.attribute("size").toDouble(&ok);
        if (!ok) mValidFlag = false;

        mLayer = mElement.attribute("layer").toInt(&ok);
        if (!ok) mValidFlag = false;

        ok = ECommon::parseRotAttribute(mElement.attribute("rot"), &angle, &mMirror);
        if (!ok) mValidFlag = false;

        mAlign = ECommon::parseAlignAttribute(mElement.attribute("align"));
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

void ELabel::drawText(QPainter *painter, QPointF position, QString text, qreal size, int angle,
                      EAlign align, int layer, SchSettings *settings)
{
    painter->save();

    painter->setPen(settings->getLayerColor(layer));
    QFont font = settings->font();
    font.setPixelSize(settings->sizeToPx(size) * settings->scale());
    painter->setFont(font);

    painter->translate(position);
    painter->rotate(-angle);

    qreal textHeight = painter->fontMetrics().boundingRect('A').height();
    qreal textWidth = painter->fontMetrics().horizontalAdvance(text);
    painter->drawText(ECommon::getDrawPosition(textHeight, textWidth, align), text);

    painter->restore();
}

DrawingText ELabel::getDrawingText()
{
    DrawingText drawingText(QPointF(), mSize, angle, mAlign, mLayer);
    if (mMirror)
        drawingText.mirror();
    drawingText.move(QPointF(mX, mY));
    return drawingText;
}


void EText::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;

    if (!mElement.isNull() && mElement.tagName() == "text") {
        bool ok = false;
        mValidFlag = true;

        mX = mElement.attribute("x").toDouble(&ok);
        if (!ok) mValidFlag = false;

        mY = mElement.attribute("y").toDouble(&ok);
        if (!ok) mValidFlag = false;

        mSize = mElement.attribute("size").toDouble(&ok);
        if (!ok) mValidFlag = false;

        mLayer = mElement.attribute("layer").toInt(&ok);
        if (!ok) mValidFlag = false;

        mDistance = mElement.attribute("distance", "50").toInt(&ok);
        if (!ok) mValidFlag = false;

        ok = ECommon::parseRotAttribute(mElement.attribute("rot"), &angle, &mMirror);
        if (!ok) mValidFlag = false;

        mAlign = ECommon::parseAlignAttribute(mElement.attribute("align"));

        mText = mElement.text();
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

DrawingText EText::getDrawingText()
{
    DrawingText drawingText(QPointF(), mSize, angle, mAlign, mLayer, mText, mDistance);
    if (mMirror)
        drawingText.mirror();
    drawingText.move(QPointF(mX, mY));
    return drawingText;
}

