#include "erectangle.h"


void ERectangle::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;

    if (!mElement.isNull() && mElement.tagName() == "rectangle") {
        mValidFlag = true;
        mX1 = mElement.attribute("x1").toDouble();
        mY1 = mElement.attribute("y1").toDouble();
        mX2 = mElement.attribute("x2").toDouble();
        mY2 = mElement.attribute("y2").toDouble();
        mLayer = mElement.attribute("layer").toInt();
        mAngle = mElement.attribute("angle", "0").toDouble();
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

void ERectangle::paint(QPainter *painter, Settings *settings)
{
    if (settings->layers.contains(mLayer) && settings->layers[mLayer].visible) {
        painter->save();

        QPen pen = painter->pen();
        pen.setColor(settings->getColor(mLayer));
        painter->setPen(pen);
        QBrush brush = painter->brush();
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(settings->getColor(mLayer));
        painter->setBrush(brush);

        QPointF center = QPointF((mX1 + mX2) / 2 * settings->schScale,
                                 -(mY1 + mY2) / 2 * settings->schScale);
        QPointF p1 = QPointF(mX1, -mY1) * settings->schScale - center;
        QPointF p2 = QPointF(mX2, -mY2) * settings->schScale - center;

        painter->translate(center);
        painter->rotate(-mAngle);
        painter->drawRect(QRectF(p1, p2));

        painter->restore();
    }
}
