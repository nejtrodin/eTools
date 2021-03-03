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

void ECircle::paint(QPainter *painter, Settings *settings)
{
    if (settings->layers.contains(mLayer) && settings->layers[mLayer].visible) {
        painter->save();
        if (mValidFlag) {
            QPen pen = painter->pen();
            pen.setColor(settings->getColor(mLayer));
            pen.setWidth(mWidth * settings->schScale);
            painter->setPen(pen);

            // fill circle if width == 0
            if (mWidth == 0) {
                QBrush brush = painter->brush();
                brush.setColor(settings->getColor(mLayer));
                brush.setStyle(Qt::SolidPattern);
                painter->setBrush(brush);
            }

            painter->drawEllipse(QPointF(mX * settings->schScale, -mY * settings->schScale),
                                 mRadius * settings->schScale, mRadius * settings->schScale);
        }
        painter->restore();
    }
}
