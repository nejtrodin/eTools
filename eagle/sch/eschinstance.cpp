#include "eschinstance.h"
#include "../ecommon.h"
#include "../drawingtext.h"
#include "../etext.h"
#include "../evalueattribute.h"
#include <cmath>

const qreal pinWidth = 0.1524;

void ESchInstance::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;
    m_attributes.clear();
    m_instancePicture = QPicture();

    if (!m_domElement.isNull() && m_domElement.tagName() == "instance") {
        bool ok = false;
        m_validFlag = true;

        m_partName = m_domElement.attribute("part");
        m_gate = m_domElement.attribute("gate");

        m_x = m_domElement.attribute("x").toDouble(&ok);
        if (!ok)
            m_validFlag = false;

        m_y = m_domElement.attribute("y").toDouble(&ok);
        if (!ok)
            m_validFlag = false;

        QString smashed = m_domElement.attribute("smashed");
        m_smashed = smashed == "yes" ? true : false;

        QString rot = m_domElement.attribute("rot");
        ok = ECommon::parseRotAttribute(rot, &m_angle, &m_mirrorFlag);
        if (!ok)
            m_validFlag = false;

        // attributes
        QDomElement attributeElement = m_domElement.firstChildElement("attribute");
        while (!attributeElement.isNull()) {
            EAttribute attribute;
            attribute.setDomElement(attributeElement);
            if (!attribute.isValid())
                m_validFlag = false;
            m_attributes.append(attribute);

            attributeElement = attributeElement.nextSiblingElement("attribute");
        }
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
}

void ESchInstance::paint(QPainter *painter, SchSettings *settings, ESchCore *schCore)
{
    ESchPart part = schCore->getPart(m_partName);
    ELibrary library = schCore->getLibrary(part.library(), part.libraryUrn());
    EDeviceset deviceset = library.getDeviceset(part.deviceset());
    QString technologyName = part.technology();
    EGate gate = deviceset.getGate(m_gate);
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
        if (settings->layerIsVisible(settings->symbolsLayer)) {
            QPointF pinSymFinishPoint = pinSymStartPoint
                    + ECommon::rotatePoint(QPointF(iPin->length() * scale, 0), iPin->angle());

            QPointF pinInstStartPoint = ECommon::rotatePoint(pinSymStartPoint, m_angle);
            QPointF pinInstFinishPoint = ECommon::rotatePoint(pinSymFinishPoint, m_angle);
            if (m_mirrorFlag) {
                pinInstStartPoint.setX(-pinInstStartPoint.x());
                pinInstFinishPoint.setX(-pinInstFinishPoint.x());
            }
            pinInstStartPoint.setX(pinInstStartPoint.x() + m_x * scale);
            pinInstStartPoint.setY(-pinInstStartPoint.y() - m_y * scale);
            pinInstFinishPoint.setX(pinInstFinishPoint.x() + m_x * scale);
            pinInstFinishPoint.setY(-pinInstFinishPoint.y() - m_y * scale);

            QPen pen = painter->pen();
            pen.setColor(settings->getLayerColor(settings->symbolsLayer));
            pen.setWidth(pinWidth * scale);
            painter->setPen(pen);
            painter->drawLine(pinInstStartPoint, pinInstFinishPoint);
        }

        // draw pin & pad text on Names layer - 95
        if (settings->layerIsVisible(settings->namesLayer)) {
            int pinAngle = iPin->angle() + m_angle;
            while (pinAngle < 0) {
                pinAngle += 360;
            }
            if (m_mirrorFlag &&
                    (m_angle <= 45 || m_angle > 315 || (m_angle > 135 && m_angle <= 225))) {
                pinAngle += 180;
            }
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
                QPointF pinTextInstPoint = ECommon::rotatePoint(pinTextSymPoint, m_angle);
                if (m_mirrorFlag)
                    pinTextInstPoint.setX(-pinTextInstPoint.x());
                pinTextInstPoint.setX(pinTextInstPoint.x() + m_x * scale);
                pinTextInstPoint.setY(-pinTextInstPoint.y() - m_y * scale);
                QString pinName = iPin->name().split("@").first();
                ELabel::drawText(painter, pinTextInstPoint, pinName, settings->pinTextSize(),
                                 textAngle, pinTextAlign, settings->namesLayer, settings);
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
                QPointF padTextInstPoint = ECommon::rotatePoint(padTextSymPoint, m_angle);
                if (m_mirrorFlag)
                    padTextInstPoint.setX(-padTextInstPoint.x());
                padTextInstPoint.setX(padTextInstPoint.x() + m_x * scale);
                padTextInstPoint.setY(-padTextInstPoint.y() - m_y * scale);

                if (textAngle == 0)
                    padTextInstPoint.ry() -= settings->padYOffset() * scale;
                else
                    padTextInstPoint.rx() -= settings->padYOffset() * scale;

                ELabel::drawText(painter, padTextInstPoint, padName, settings->padTextSize(),
                                 textAngle, padTextAlign, settings->namesLayer, settings);
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
        attributes["VALUE"] = deviceset.name() + device.name();
    else
        attributes["VALUE"] = part.value();

    if (m_smashed) {
        foreach (EAttribute attribute, m_attributes) {
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

        drawingText.rotate(m_angle);
        if (m_mirrorFlag)
            drawingText.mirror();
        drawingText.move(QPointF(m_x, m_y));

        QString textValue = drawingText.text();
        if (textValue.startsWith('>')) {
            if (!m_smashed) {
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
    painter->translate(m_x * scale, -m_y * scale);
    if (m_mirrorFlag)
        painter->scale(-1.0, 1.0);
    painter->rotate(-m_angle);
    symbol.paint(painter, settings);

    painter->restore();
}
