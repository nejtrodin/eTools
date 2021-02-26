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
                      EAlign align, int layer, Settings *settings)
{
    painter->save();

    painter->setPen(settings->getColor(layer));
    QFont font = settings->schFont;
    font.setPixelSize(size * settings->textScale * settings->schScale);
    painter->setFont(font);

    painter->translate(position);
    painter->rotate(-angle);

    qreal textHeight = painter->fontMetrics().boundingRect('A').height();
    qreal textWidth = painter->fontMetrics().horizontalAdvance(text);
    painter->drawText(ECommon::getDrawPosition(textHeight, textWidth, align), text);

    painter->restore();
}

void ELabel::paint(QPainter *painter, Settings *settings, QString text)
{
    painter->save();

    painter->setPen(settings->getColor(mLayer));
    QFont font = settings->schFont;
    font.setPixelSize(mSize * settings->textScale * settings->schScale);
    painter->setFont(font);

    painter->translate(QPointF(mX * settings->schScale, -mY * settings->schScale));
    painter->rotate(-angle);

    qreal textHeight = painter->fontMetrics().boundingRect('A').height();
    qreal textWidth = painter->fontMetrics().horizontalAdvance(text);
    EAlign drawAlign = mMirror ? ECommon::mirrorAlign(mAlign) : mAlign;
    painter->drawText(ECommon::getDrawPosition(textHeight, textWidth, drawAlign), text);

    painter->restore();
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

        distance = mElement.attribute("distance", "50").toInt(&ok);
        if (!ok) mValidFlag = false;

        ok = ECommon::parseRotAttribute(mElement.attribute("rot"), &angle, &mMirror);
        if (!ok) mValidFlag = false;

        mAlign = ECommon::parseAlignAttribute(mElement.attribute("align"));

        mText = mElement.text();
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

void EText::paint(QString text, QPainter *painter, Settings *settings)
{
    painter->save();

    painter->setPen(settings->getColor(mLayer));
    QFont font = settings->schFont;
    font.setPixelSize(mSize * settings->textScale * settings->schScale);
    painter->setFont(font);

    // перемещение в точку относительно которой будет поворот
    painter->translate(QPointF(mX * settings->schScale, -mY * settings->schScale));
    painter->rotate(-angle);

    auto lines = text.split("\n");
    qreal textHeight = painter->fontMetrics().boundingRect('A').height();
    EAlign drawAlign = mMirror ? ECommon::mirrorAlign(mAlign) : mAlign;

    // point for vertical alight
    qreal textVOffset = 0;
    int linesCount = lines.length();
    if (mAlign == AlignBottomLeft || mAlign == AlignBottomCenter || mAlign == AlignBottomRight)
        textVOffset = (linesCount - 1) * (1 + 0.01 * distance) * textHeight;
    else if  (mAlign == AlignCenterLeft || mAlign == AlignCenter || mAlign == AlignCenterRight)
        textVOffset = ((linesCount - 1) * textHeight * (1 + 0.01 * distance)) / 2;

    qreal yOffset = 0;
    foreach (QString line, lines) {
        qreal lineWidth = painter->fontMetrics().horizontalAdvance(line);
        QPointF linePos = ECommon::getDrawPosition(textHeight, lineWidth, drawAlign);
        linePos.setY(linePos.y() - textVOffset + yOffset);
        painter->drawText(linePos, line);
        yOffset += textHeight + textHeight * distance / 100;
    }

    painter->restore();
}

void EText::paint(QPainter *painter, Settings *settings)
{
    paint(mText, painter, settings);
}

DrawingText EText::getDrawingText()
{
    DrawingText drawingText(mText, QPointF(mX, mY), mSize, angle, mAlign, mLayer, distance);
    if (mMirror)
        drawingText.mirror();
    return drawingText;
}

