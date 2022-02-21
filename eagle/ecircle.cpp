#include "ecircle.h"

void ECircle::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = true;

    if (!m_domElement.isNull() && m_domElement.tagName() == "circle") {
        bool _ok = false;

        mX = m_domElement.attribute("x").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;

        mY = m_domElement.attribute("y").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;

        mRadius = m_domElement.attribute("radius").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;

        mWidth = m_domElement.attribute("width").toDouble(&_ok);
        if (!_ok)
            m_validFlag = false;

        mLayer = m_domElement.attribute("layer").toInt(&_ok);
        if (!_ok)
            m_validFlag = false;
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
}

void ECircle::paint(QPainter *painter, SchSettings *settings)
{
    if (settings->layerIsVisible(mLayer)) {
        painter->save();
        if (m_validFlag) {
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
