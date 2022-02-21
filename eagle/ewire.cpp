#include "ewire.h"
#include <cmath>

void EWire::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = true;

    if (!m_domElement.isNull() && m_domElement.tagName() == "wire") {
        bool _ok = false;

        mX1 = m_domElement.attribute("x1").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;

        mY1 = m_domElement.attribute("y1").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;

        mX2 = m_domElement.attribute("x2").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;

        mY2 = m_domElement.attribute("y2").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;

        mWidth = m_domElement.attribute("width").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;

        mLayer = m_domElement.attribute("layer").toInt(&_ok);
        if (!_ok)
            m_validFlag = false;

        mCurve = m_domElement.attribute("curve", "0").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;
    }
}

const qreal pi = 3.141592653589793;

void EWire::paint(QPainter *painter, SchSettings *settings)
{
    if (settings->layerIsVisible(mLayer)) {
        painter->save();
        if (m_validFlag) {
            QPen pen = painter->pen();
            qreal scale = settings->scale();
            pen.setColor(settings->getLayerColor(mLayer));
            pen.setWidth(mWidth * scale);
            painter->setPen(pen);

            if (mCurve == 0) {
                painter->drawLine(QPointF(mX1 * scale, -mY1 * scale),
                                  QPointF(mX2 * scale, -mY2 * scale));
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

                QRectF arcRect =
                        QRectF((cX - r) * scale, (-cY + r) * scale, 2 * r * scale, -2 * r * scale);
                painter->drawArc(arcRect, a1 * 16, -mCurve * 16);
            }
        }
        painter->restore();
    }
}
