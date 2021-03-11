#include "ecircle.h"

void ECircle::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = true;

    if (!mElement.isNull() && mElement.tagName() == "circle") {
        bool _ok = false;

        mX = mElement.attribute("x").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;

        mY = mElement.attribute("y").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;

        mRadius = mElement.attribute("radius").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;

        mWidth = mElement.attribute("width").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;

        mLayer = mElement.attribute("layer").toInt(&_ok);
        if (!_ok)
            mValidFlag = false;
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

void ECircle::paint(QPainter *painter, SchSettings *settings)
{
    if (settings->layerIsVisible(mLayer)) {
        painter->save();
        if (mValidFlag) {
            QPen pen = painter->pen();
            qreal scale = settings->scale();
            pen.setColor(settings->getLayerColor(mLayer));
            pen.setWidth(mWidth * scale);
            painter->setPen(pen);

            // fill circle if width == 0
            if (mWidth == 0) {
                QBrush brush = painter->brush();
                brush.setColor(settings->getLayerColor(mLayer));
                brush.setStyle(Qt::SolidPattern);
                painter->setBrush(brush);
            }

            painter->drawEllipse(QPointF(mX * scale, -mY * scale), mRadius * scale,
                                 mRadius * scale);
        }
        painter->restore();
    }
}
