#include "ewire.h"
#include <cmath>

void EWire::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = true;

    if (!mElement.isNull() && mElement.tagName() == "wire") {
        bool _ok = false;

        mX1 = mElement.attribute("x1").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;

        mY1 = mElement.attribute("y1").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;

        mX2 = mElement.attribute("x2").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;

        mY2 = mElement.attribute("y2").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;

        mWidth = mElement.attribute("width").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;

        mLayer = mElement.attribute("layer").toInt(&_ok);
        if (!_ok)
            mValidFlag = false;

        mCurve = mElement.attribute("curve", "0").toDouble(&_ok);
        if (!_ok)
            mValidFlag = false;
    }
}

const qreal pi = 3.141592653589793;

void EWire::paint(QPainter *painter, Settings *settings)
{
    if (settings->layers.contains(mLayer) && settings->layers[mLayer].visible) {
        painter->save();
        if (mValidFlag) {
            QPen pen = painter->pen();
            pen.setColor(settings->getColor(mLayer));
            pen.setWidth(mWidth * settings->schScale);
            painter->setPen(pen);

            if (mCurve == 0) {
                painter->drawLine(QPointF(mX1 * settings->schScale, -mY1 * settings->schScale),
                                  QPointF(mX2 * settings->schScale, -mY2 * settings->schScale));
            } else {
                // arc
                qreal length = sqrt(pow((mX2 - mX1), 2) + pow((mY2 - mY1), 2));
                qreal alpha = abs(mCurve * pi / 180.0 / 2);
                qreal r = abs(length / 2 / sin(alpha));
                qreal beta = atan2((mY2 - mY1), (mX2 - mX1));
                qreal a1 = 0;
                if (mCurve < 0) {
                    a1 = static_cast<int>(90 + (beta - alpha) * 180 / pi) % 360;
                } else {
                    a1 = static_cast<int>(270 + (beta + alpha) * 180 / pi) % 360;
                }

                // from kicad eagle parser
                qreal dist = length / (2 * tan(mCurve * pi / 180.0 / 2));
                qreal cX = (mX1 + mX2) / 2 + dist * (mY2 - mY1) / length;
                qreal cY = (mY1 + mY2) / 2 + dist * (mX2 - mX1) / length;

                QRectF arcRect = QRectF((cX - r) * settings->schScale, (-cY + r) * settings->schScale,
                                        2 * r * settings->schScale, -2 * r * settings->schScale);
                painter->drawArc(arcRect, a1 * 16, -mCurve * 16);
            }
        }
        painter->restore();
    }
}
