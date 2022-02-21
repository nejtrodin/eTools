#include "esymbol.h"

void ESymbol::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;
    m_wires.clear();
    m_texts.clear();
    m_pins.clear();
    m_rectangles.clear();
    m_circles.clear();

    if (!m_domElement.isNull() && m_domElement.tagName() == "symbol") {
        m_validFlag = true;
        m_name = m_domElement.attribute("name");

        QDomElement circleElement = m_domElement.firstChildElement("circle");
        while (!circleElement.isNull()) {
            ECircle circle;
            circle.setDomElement(circleElement);
            if (!circle.isValid())
                m_validFlag = false;
            m_circles.append(circle);

            circleElement = circleElement.nextSiblingElement("circle");
        }

        QDomElement pinElement = m_domElement.firstChildElement("pin");
        while (!pinElement.isNull()) {
            EPin pin;
            pin.setDomElement(pinElement);
            if (!pin.isValid())
                m_validFlag = false;
            m_pins.append(pin);

            pinElement = pinElement.nextSiblingElement("pin");
        }

        QDomElement rectangleElement = m_domElement.firstChildElement("rectangle");
        while (!rectangleElement.isNull()) {
            ERectangle rectangle;
            rectangle.setDomElement(rectangleElement);
            if (!rectangle.isValid())
                m_validFlag = false;
            m_rectangles.append(rectangle);

            rectangleElement = rectangleElement.nextSiblingElement("rectangle");
        }

        QDomElement textElement = m_domElement.firstChildElement("text");
        while (!textElement.isNull()) {
            EText text;
            text.setDomElement(textElement);
            if (!text.isValid())
                m_validFlag = false;
            m_texts.append(text);

            textElement = textElement.nextSiblingElement("text");
        }

        QDomElement wireElement = m_domElement.firstChildElement("wire");
        while (!wireElement.isNull()) {
            EWire wire;
            wire.setDomElement(wireElement);
            if (!wire.isValid())
                m_validFlag = false;
            m_wires.append(wire);

            wireElement = wireElement.nextSiblingElement("wire");
        }
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
}

void ESymbol::paint(QPainter *painter, SchSettings *settings)
{
    QVector<ECircle>::iterator iCircle;
    for (iCircle = m_circles.begin(); iCircle != m_circles.end(); ++iCircle) {
        iCircle->paint(painter, settings);
    }

    // pin draw by instance

    QVector<ERectangle>::iterator iRectangle;
    for (iRectangle = m_rectangles.begin(); iRectangle != m_rectangles.end(); ++iRectangle) {
        iRectangle->paint(painter, settings);
    }

    // text draw by instance

    QVector<EWire>::iterator iWire;
    for (iWire = m_wires.begin(); iWire != m_wires.end(); ++iWire) {
        iWire->paint(painter, settings);
    }
}
