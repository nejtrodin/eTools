#include "esegment.h"
#include "../eparser.h"

const int junctionSize = 1;

void ESegment::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;
    mWires.clear();

    if (!mElement.isNull() && mElement.tagName() == "segment") {
        mValidFlag = true;

        QDomElement wireElement = mElement.firstChildElement("wire");
        while (!wireElement.isNull()) {
            EWire wire;
            wire.setDomElement(wireElement);
            if (wire.isValid())
                mWires.append(wire);
            else
                mValidFlag = false;

            wireElement = wireElement.nextSiblingElement("wire");
        }

        QDomElement junctionElement = mElement.firstChildElement("junction");
        while (!junctionElement.isNull()) {
            Junction junction;
            junction.x = junctionElement.attribute("x").toDouble();
            junction.y = junctionElement.attribute("y").toDouble();
            mJunction.append(junction);

            junctionElement = junctionElement.nextSiblingElement("junction");
        }

        QDomElement labelElement = mElement.firstChildElement("label");
        while (!labelElement.isNull()) {
            ELabel label;
            label.setDomElement(labelElement);
            if (!label.isValid())
                mValidFlag = false;
            mLabels.append(label);

            labelElement = labelElement.nextSiblingElement("label");
        }
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

void ESegment::paint(QPainter *painter, QString netName, Settings *settings)
{
    QVector<EWire>::iterator iWire;
    for (iWire = mWires.begin(); iWire != mWires.end(); ++iWire) {
        iWire->paint(painter, settings);
    }

    painter->save();
    // junction не имеет назначенного слоя, всегда берется 91-Nets
    painter->setPen(settings->getColor(91));
    painter->setBrush(settings->getColor(91));
    QVector<Junction>::iterator iJunction;
    for (iJunction = mJunction.begin(); iJunction != mJunction.end(); ++iJunction) {
        QPointF center(iJunction->x * settings->schScale, -iJunction->y * settings->schScale);
        painter->drawEllipse(center, junctionSize * settings->schScale,
                             junctionSize * settings->schScale);
    }
    painter->restore();

    QVector<ELabel>::iterator iLabel;
    for (iLabel = mLabels.begin(); iLabel != mLabels.end(); ++iLabel) {
        DrawingText text = iLabel->getDrawingText();
        QPointF labelPos = text.pos();
        text.setText(netName);
        // find wire on which the Label is located
        bool labelOnHWire = false;
        bool labelOnVWire = false;
        QPointF wireP1, wireP2;
        for (iWire = mWires.begin(); iWire != mWires.end(); ++iWire) {
            wireP1.setX(iWire->x1());
            wireP1.setY(iWire->y1());
            wireP2.setX(iWire->x2());
            wireP2.setY(iWire->y2());

            // horizontal line
            if ((wireP1.y() == wireP2.y()) && (wireP1.y() == labelPos.y())) {
                if ((wireP1.x() < wireP2.x()) && (wireP1.x() <= labelPos.x()) && (labelPos.x() <= wireP2.x())) {
                    labelOnHWire = true;
                    break;
                }
                if ((wireP1.x() > wireP2.x()) && (wireP2.x() <= labelPos.x()) && (labelPos.x() <= wireP1.x())) {
                    labelOnHWire = true;
                    break;
                }
            }

            // vertical line
            if ((wireP1.x() == wireP2.x()) && (wireP1.x() == labelPos.x())) {
                if ((wireP1.y() < wireP2.y()) && (wireP1.y() <= labelPos.y()) && (labelPos.y() <= wireP2.y())) {
                    labelOnVWire = true;
                    break;
                }
                if ((wireP1.y() > wireP2.y()) && (wireP2.y() <= labelPos.y()) && (labelPos.y() <= wireP1.y())) {
                    labelOnVWire = true;
                    break;
                }
            }
        }

        if (labelOnHWire) {
            int angle = text.angle();
            if (angle > 315 ||  (angle >= 0 && angle <= 135)) {
                text.move(QPointF(0, settings->labelUpOffset));
            } else {
                text.move(QPointF(0, -settings->labelUpOffset));
            }
        } else if (labelOnVWire) {
            int angle = text.angle();
            if (text.mirrored())
                angle = (angle + 180) % 360;
            if (angle >= 90 && angle < 270) {
                text.move(QPointF(-settings->labelUpOffset, 0));
            } else {
                text.move(QPointF(settings->labelUpOffset, 0));
            }
        }
        text.paint(painter, settings);
    }
}
