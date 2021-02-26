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
        iLabel->paint(painter, settings, netName);
    }
}
