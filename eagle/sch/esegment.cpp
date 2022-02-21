#include "esegment.h"

const qreal junctionSize = 0.6;

void ESegment::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;
    m_wires.clear();

    if (!m_domElement.isNull() && m_domElement.tagName() == "segment") {
        m_validFlag = true;

        QDomElement wireElement = m_domElement.firstChildElement("wire");
        while (!wireElement.isNull()) {
            EWire wire;
            wire.setDomElement(wireElement);
            if (wire.isValid())
                m_wires.append(wire);
            else
                m_validFlag = false;

            wireElement = wireElement.nextSiblingElement("wire");
        }

        QDomElement junctionElement = m_domElement.firstChildElement("junction");
        while (!junctionElement.isNull()) {
            Junction junction;
            junction.x = junctionElement.attribute("x").toDouble();
            junction.y = junctionElement.attribute("y").toDouble();
            m_junction.append(junction);

            junctionElement = junctionElement.nextSiblingElement("junction");
        }

        QDomElement labelElement = m_domElement.firstChildElement("label");
        while (!labelElement.isNull()) {
            ELabel label;
            label.setDomElement(labelElement);
            if (!label.isValid())
                m_validFlag = false;
            m_labels.append(label);

            labelElement = labelElement.nextSiblingElement("label");
        }
    }

    if (!m_validFlag) {
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
    }
}

void ESegment::paint(QPainter *painter, QString netName, SchSettings *settings)
{
    qreal scale = settings->scale();

    QVector<EWire>::iterator iWire;
    for (iWire = m_wires.begin(); iWire != m_wires.end(); ++iWire) {
        iWire->paint(painter, settings);
    }

    painter->save();
    painter->setPen(settings->getLayerColor(settings->netsLayer));
    painter->setBrush(settings->getLayerColor(settings->netsLayer));
    QVector<Junction>::iterator iJunction;
    for (iJunction = m_junction.begin(); iJunction != m_junction.end(); ++iJunction) {
        QPointF center(iJunction->x * scale, -iJunction->y * scale);
        painter->drawEllipse(center, junctionSize * scale, junctionSize * scale);
    }
    painter->restore();

    QVector<ELabel>::iterator iLabel;
    for (iLabel = m_labels.begin(); iLabel != m_labels.end(); ++iLabel) {
        DrawingText text = iLabel->getDrawingText();
        QPointF labelPos = text.pos();
        text.setText(netName);
        // find wire on which the Label is located
        bool labelOnHWire = false;
        bool labelOnVWire = false;
        QPointF wireP1, wireP2;
        for (iWire = m_wires.begin(); iWire != m_wires.end(); ++iWire) {
            wireP1.setX(iWire->x1());
            wireP1.setY(iWire->y1());
            wireP2.setX(iWire->x2());
            wireP2.setY(iWire->y2());

            // horizontal line
            if ((wireP1.y() == wireP2.y()) && (wireP1.y() == labelPos.y())) {
                if ((wireP1.x() < wireP2.x()) && (wireP1.x() <= labelPos.x())
                    && (labelPos.x() <= wireP2.x())) {
                    labelOnHWire = true;
                    break;
                }
                if ((wireP1.x() > wireP2.x()) && (wireP2.x() <= labelPos.x())
                    && (labelPos.x() <= wireP1.x())) {
                    labelOnHWire = true;
                    break;
                }
            }

            // vertical line
            if ((wireP1.x() == wireP2.x()) && (wireP1.x() == labelPos.x())) {
                if ((wireP1.y() < wireP2.y()) && (wireP1.y() <= labelPos.y())
                    && (labelPos.y() <= wireP2.y())) {
                    labelOnVWire = true;
                    break;
                }
                if ((wireP1.y() > wireP2.y()) && (wireP2.y() <= labelPos.y())
                    && (labelPos.y() <= wireP1.y())) {
                    labelOnVWire = true;
                    break;
                }
            }
        }

        if (labelOnHWire) {
            int angle = text.angle();
            if (angle > 315 ||  (angle >= 0 && angle <= 135)) {
                text.move(QPointF(0, settings->labelUpOffset()));
            } else {
                text.move(QPointF(0, -settings->labelUpOffset()));
            }
        } else if (labelOnVWire) {
            int angle = text.angle();
            if (text.mirrored())
                angle = (angle + 180) % 360;
            if (angle >= 90 && angle < 270) {
                text.move(QPointF(-settings->labelUpOffset(), 0));
            } else {
                text.move(QPointF(settings->labelUpOffset(), 0));
            }
        }
        text.paint(painter, settings);
    }
}
