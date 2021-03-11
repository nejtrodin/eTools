#include "eschinstance.h"
#include "../eparser.h"
#include "../common/ecommon.h"
#include "../common/drawingtext.h"
#include "../common/etext.h"
#include "../common/evalueattribute.h"
#include <cmath>

const qreal pinWidth = 0.1524;

void ESchInstance::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;
    mAttributes.clear();
    mInstancePicture = QPicture();

    if (!mElement.isNull() && mElement.tagName() == "instance") {
        bool ok = false;
        mValidFlag = true;

        mPartName = mElement.attribute("part");
        mGate = mElement.attribute("gate");

        mX = mElement.attribute("x").toDouble(&ok);
        if (!ok)
            mValidFlag = false;

        mY = mElement.attribute("y").toDouble(&ok);
        if (!ok)
            mValidFlag = false;

        QString smashed = mElement.attribute("smashed");
        mSmashed = smashed == "yes" ? true : false;

        QString rot = mElement.attribute("rot");
        ok = ECommon::parseRotAttribute(rot, &mAngle, &mMirrorFlag);
        if (!ok)
            mValidFlag = false;

        // attributes
        QDomElement attributeElement = mElement.firstChildElement("attribute");
        while (!attributeElement.isNull()) {
            EAttribute attribute;
            attribute.setDomElement(attributeElement);
            if (!attribute.isValid())
                mValidFlag = false;
            mAttributes.append(attribute);

            attributeElement = attributeElement.nextSiblingElement("attribute");
        }
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

void ESchInstance::paint(QPainter *painter, SchSettings *settings, ESchCore *schCore)
{
    ESchPart part = schCore->getPart(mPartName);
    ELibrary library = schCore->getLibrary(part.library());
    EDeviceset deviceset = library.getDeviceset(part.deviceset());
    QString technologyName = part.technology();
    EGate gate = deviceset.getGate(mGate);
    ESymbol symbol = library.getSymbol(gate.symbol());
    EDevice device = deviceset.getDevice(part.device());
    QList<EConnect> connects = device.getConnects(gate.name());

    // --- draw pins
    painter->save();
    qreal scale = settings->scale();
    QVector<EPin> pins = symbol.getPins();
    QVector<EPin>::iterator iPin;
    for (iPin = pins.begin(); iPin != pins.end(); ++iPin) {
        QPointF pinSymStartPoint =
                QPointF(iPin->x() * scale, iPin->y() * scale);
        // draw pin line on Symbols layer - 94
        if (settings->layerIsVisible(settings->pinLayer)) {
            QPointF pinSymFinishPoint = pinSymStartPoint
                    + ECommon::rotatePoint(QPointF(iPin->length() * scale, 0), iPin->angle());

            QPointF pinInstStartPoint = ECommon::rotatePoint(pinSymStartPoint, mAngle);
            QPointF pinInstFinishPoint = ECommon::rotatePoint(pinSymFinishPoint, mAngle);
            if (mMirrorFlag) {
                pinInstStartPoint.setX(-pinInstStartPoint.x());
                pinInstFinishPoint.setX(-pinInstFinishPoint.x());
            }
            pinInstStartPoint.setX(pinInstStartPoint.x() + mX * scale);
            pinInstStartPoint.setY(-pinInstStartPoint.y() - mY * scale);
            pinInstFinishPoint.setX(pinInstFinishPoint.x() + mX * scale);
            pinInstFinishPoint.setY(-pinInstFinishPoint.y() - mY * scale);

            QPen pen = painter->pen();
            pen.setColor(settings->getLayerColor(settings->pinLayer));
            pen.setWidth(pinWidth * scale);
            painter->setPen(pen);
            painter->drawLine(pinInstStartPoint, pinInstFinishPoint);
        }

        // draw pin & pad text on Names layer - 95
        if (settings->layerIsVisible(settings->pinTextLayer)) {
            int pinAngle = iPin->angle() + mAngle;
            while (pinAngle < 0)
                pinAngle += 360;
            if (mMirrorFlag && (mAngle <= 45 || mAngle > 315 || (mAngle > 135 && mAngle <= 225)))
                pinAngle += 180;
            pinAngle = pinAngle % 360;
            qreal textAngle = 0;
            if ((pinAngle > 45 && pinAngle <= 135) || (pinAngle > 225 && pinAngle <= 315))
                textAngle = 90;

            // pin Text
            if (iPin->visible() == EPin::VisiblePin || iPin->visible() == EPin::VisibleBoth) {
                EAlign pinTextAlign = AlignCenterLeft;
                if (pinAngle > 135 && pinAngle <= 315)
                    pinTextAlign = AlignCenterRight;

                QPointF pinTextSymPoint =
                        pinSymStartPoint
                        + ECommon::rotatePoint(
                                QPointF((iPin->length() + settings->pinXOffset()) * scale, 0),
                                iPin->angle());
                QPointF pinTextInstPoint = ECommon::rotatePoint(pinTextSymPoint, mAngle);
                if (mMirrorFlag)
                    pinTextInstPoint.setX(-pinTextInstPoint.x());
                pinTextInstPoint.setX(pinTextInstPoint.x() + mX * scale);
                pinTextInstPoint.setY(-pinTextInstPoint.y() - mY * scale);
                QString pinName = iPin->name().split("@").first();
                ELabel::drawText(painter, pinTextInstPoint, pinName, settings->pinTextSize(),
                                 textAngle, pinTextAlign, settings->pinTextLayer, settings);
            }

            // pad Text
            if (iPin->visible() == EPin::VisiblePad || iPin->visible() == EPin::VisibleBoth) {
                QString padName;
                // find pad value
                QList<EConnect>::Iterator iConnect;
                for (iConnect = connects.begin(); iConnect != connects.end(); ++iConnect) {
                    if (iConnect->pin == iPin->name()) {
                        padName = iConnect->pad;
                        break;
                    }
                }

                EAlign padTextAlign = AlignBottomRight;
                if (pinAngle > 135 && pinAngle <= 315)
                    padTextAlign = AlignBottomLeft;

                QPointF padTextSymPoint =
                        pinSymStartPoint
                        + ECommon::rotatePoint(
                                QPointF((iPin->length() - settings->padXOffset()) * scale, 0),
                                iPin->angle());
                QPointF padTextInstPoint = ECommon::rotatePoint(padTextSymPoint, mAngle);
                if (mMirrorFlag)
                    padTextInstPoint.setX(-padTextInstPoint.x());
                padTextInstPoint.setX(padTextInstPoint.x() + mX * scale);
                padTextInstPoint.setY(-padTextInstPoint.y() - mY * scale);

                if (textAngle == 0)
                    padTextInstPoint.ry() -= settings->padYOffset() * scale;
                else
                    padTextInstPoint.rx() -= settings->padYOffset() * scale;

                ELabel::drawText(painter, padTextInstPoint, padName, settings->padTextSize(),
                                 textAngle, padTextAlign, settings->pinTextLayer, settings);
            }
        }  // end drawing pin & pad text
    }
    painter->restore();

    // --- draw attributes from instance
    QList<EValueAttribute> deviceValueAttributes = device.getAttributes(technologyName);
    QList<EValueAttribute> partValueAttributes = part.getAttributes();
    QMap<QString, QString> attributes;
    foreach (EValueAttribute valueAttribute, deviceValueAttributes) {
        attributes.insert(valueAttribute.name(), valueAttribute.value());
    }
    foreach (EValueAttribute valueAttribute, partValueAttributes) {
        attributes.insert(valueAttribute.name(), valueAttribute.value());
    }
    QString gateName = gate.name();
    if (gateName.startsWith("G$"))
        gateName = "";
    QString name = part.name() + gateName;
    name = name.split("@").first();
    name = name.split("#").first();
    name = name.split("'").first();
    name = name.split("|").first();
    attributes["NAME"] = name;
    if (part.value().isEmpty())
        attributes["VALUE"] = device.name() + deviceset.name();
    else
        attributes["VALUE"] = part.value();

    if (mSmashed) {
        foreach (EAttribute attribute, mAttributes) {
            DrawingText attributeText(QPointF(0, 0), attribute.size(), attribute.angle(),
                                      attribute.align(), attribute.layer(),
                                      attributes[attribute.name()]);
            if (attribute.mirror())
                attributeText.mirror();
            attributeText.move(attribute.position());
            attributeText.paint(painter, settings, false);
        }
    }

    // --- draw symbol
    // --- draw text & attributes from symbol
    QVector<EText> texts = symbol.getTexts();
    QVector<EText>::iterator iText;
    for (iText = texts.begin(); iText != texts.end(); ++iText) {
        DrawingText drawingText = iText->getDrawingText();

        drawingText.rotate(mAngle);
        if (mMirrorFlag)
            drawingText.mirror();
        drawingText.move(QPointF(mX, mY));

        QString textValue = drawingText.text();
        if (textValue.startsWith('>')) {
            if (!mSmashed) {
                QString attributeName = textValue.mid(1);
                if (attributes.contains(attributeName))
                    drawingText.setText(attributes[attributeName]);

                drawingText.paint(painter, settings, false);
            }
        } else {
            // not started from '>'
            drawingText.paint(painter, settings, false);
        }
    }

    painter->save();
    painter->translate(mX * scale, -mY * scale);
    if (mMirrorFlag)
        painter->scale(-1.0, 1.0);
    painter->rotate(-mAngle);
    symbol.paint(painter, settings);

    painter->restore();
}
