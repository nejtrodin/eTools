#include "drawingtext.h"

DrawingText::DrawingText(QPointF position, qreal size, int angle, EAlign align, int layer,
                         QString text, int distance)
    : mText(text),
      mPosition(position),
      mSize(size),
      mAngle(angle),
      mAlign(align),
      mLayer(layer),
      mDistance(distance)
{
}

void DrawingText::move(QPointF position)
{
    mPosition += position;
}

void DrawingText::rotate(int angle)
{
    mAngle += angle;
    mAngle %= 360;

    if (mAngle != 0)
        mPosition = ECommon::rotatePoint(mPosition, angle);
}

void DrawingText::mirror()
{
    if (mAngle <= 45 || (mAngle > 135 && mAngle <= 225) || mAngle > 315) {
        if (mAlign == AlignBottomLeft)
            mAlign = AlignBottomRight;
        else if (mAlign == AlignBottomRight)
            mAlign = AlignBottomLeft;
        else if (mAlign == AlignCenterLeft)
            mAlign = AlignCenterRight;
        else if (mAlign == AlignCenterRight)
            mAlign = AlignCenterLeft;
        else if (mAlign == AlignTopLeft)
            mAlign = AlignTopRight;
        else if (mAlign == AlignTopRight)
            mAlign = AlignTopLeft;
    } else {
        if (mAlign == AlignBottomLeft)
            mAlign = AlignTopLeft;
        else if (mAlign == AlignBottomCenter)
            mAlign = AlignTopCenter;
        else if (mAlign == AlignBottomRight)
            mAlign = AlignTopRight;
        else if (mAlign == AlignTopLeft)
            mAlign = AlignBottomLeft;
        else if (mAlign == AlignTopCenter)
            mAlign = AlignBottomCenter;
        else if (mAlign == AlignTopRight)
            mAlign = AlignBottomRight;
    }
    mPosition.rx() *= -1;
    mMirrorFlag = !mMirrorFlag;
}

void DrawingText::paint(QPainter *painter, SchSettings *settings, bool readable)
{
    if (settings->layerIsVisible(mLayer)) {
        painter->save();

        painter->setPen(settings->getLayerColor(mLayer));
        QFont font = settings->font();
        font.setPixelSize(settings->sizeToPx(mSize) * settings->scale());
        painter->setFont(font);

        QPointF paintPosition = mPosition * settings->scale();
        paintPosition.ry() *= -1;
        painter->translate(paintPosition);

        auto lines = mText.split("\n");
        qreal textHeight = painter->fontMetrics().boundingRect('A').height();

        int drawAngle = mAngle;
        EAlign drawAlign = mAlign;
        if (readable) {
            if (mAngle > 135 && mAngle <= 315) {
                drawAngle = (drawAngle + 180) % 360;
                if (drawAlign == AlignBottomLeft)
                    drawAlign = AlignTopRight;
                else if (drawAlign == AlignBottomCenter)
                    drawAlign = AlignTopCenter;
                else if (drawAlign == AlignBottomRight)
                    drawAlign = AlignTopLeft;
                else if (drawAlign == AlignCenterLeft)
                    drawAlign = AlignCenterRight;
                else if (drawAlign == AlignCenterRight)
                    drawAlign = AlignCenterLeft;
                else if (drawAlign == AlignTopLeft)
                    drawAlign = AlignBottomRight;
                else if (drawAlign == AlignTopCenter)
                    drawAlign = AlignBottomCenter;
                else if (drawAlign == AlignTopRight)
                    drawAlign = AlignBottomLeft;
            }
        }
        painter->rotate(-drawAngle);

        // point for vertical alight
        qreal textVOffset = 0;
        int linesCount = lines.length();
        if (drawAlign == AlignBottomLeft || drawAlign == AlignBottomCenter
            || drawAlign == AlignBottomRight)
            textVOffset = (linesCount - 1) * (1 + 0.01 * mDistance) * textHeight;
        else if (drawAlign == AlignCenterLeft || drawAlign == AlignCenter
                 || drawAlign == AlignCenterRight)
            textVOffset = ((linesCount - 1) * textHeight * (1 + 0.01 * mDistance)) / 2;

        qreal yOffset = 0;
        foreach (QString line, lines) {
            qreal lineWidth = painter->fontMetrics().horizontalAdvance(line);
            QPointF linePos = ECommon::getDrawPosition(textHeight, lineWidth, drawAlign);
            linePos.ry() += -textVOffset + yOffset;
            painter->drawText(linePos, line);
            yOffset += textHeight + textHeight * mDistance / 100;
        }

        painter->restore();
    }
}
