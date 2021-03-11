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

void ERectangle::paint(QPainter *painter, SchSettings *settings)
{
    if (isValid() && settings->layerIsVisible(mLayer)) {
        painter->save();

        QPen pen = painter->pen();
        pen.setColor(settings->getLayerColor(mLayer));
        painter->setPen(pen);
        QBrush brush = painter->brush();
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(settings->getLayerColor(mLayer));
        painter->setBrush(brush);

        qreal scale = settings->scale();
        QPointF center = QPointF((mX1 + mX2) / 2 * scale, -(mY1 + mY2) / 2 * scale);
        QPointF p1 = QPointF(mX1, -mY1) * scale - center;
        QPointF p2 = QPointF(mX2, -mY2) * scale - center;

        painter->translate(center);
        painter->rotate(-mAngle);
        painter->drawRect(QRectF(p1, p2));

        painter->restore();
    }
}
