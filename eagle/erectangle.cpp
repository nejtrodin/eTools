#include "erectangle.h"


void ERectangle::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    if (!m_domElement.isNull() && m_domElement.tagName() == "rectangle") {
        m_validFlag = true;
        mX1 = m_domElement.attribute("x1").toDouble();
        mY1 = m_domElement.attribute("y1").toDouble();
        mX2 = m_domElement.attribute("x2").toDouble();
        mY2 = m_domElement.attribute("y2").toDouble();
        mLayer = m_domElement.attribute("layer").toInt();
        mAngle = m_domElement.attribute("angle", "0").toDouble();
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
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
