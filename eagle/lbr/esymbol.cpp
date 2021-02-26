#include "esymbol.h"

void ESymbol::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;
    mWires.clear();
    mTexts.clear();
    mPins.clear();
    mRectangles.clear();
    mCircles.clear();

    if (!mElement.isNull() && mElement.tagName() == "symbol") {
        mValidFlag = true;
        mName = mElement.attribute("name");

        QDomElement circleElement = mElement.firstChildElement("circle");
        while (!circleElement.isNull()) {
            ECircle circle;
            circle.setDomElement(circleElement);
            if (!circle.isValid())
                mValidFlag = false;
            mCircles.append(circle);

            circleElement = circleElement.nextSiblingElement("circle");
        }

        QDomElement pinElement = mElement.firstChildElement("pin");
        while (!pinElement.isNull()) {
            EPin pin;
            pin.setDomElement(pinElement);
            if (!pin.isValid())
                mValidFlag = false;
            mPins.append(pin);

            pinElement = pinElement.nextSiblingElement("pin");
        }

        QDomElement rectangleElement = mElement.firstChildElement("rectangle");
        while (!rectangleElement.isNull()) {
            ERectangle rectangle;
            rectangle.setDomElement(rectangleElement);
            if (!rectangle.isValid())
                mValidFlag = false;
            mRectangles.append(rectangle);

            rectangleElement = rectangleElement.nextSiblingElement("rectangle");
        }

        QDomElement textElement = mElement.firstChildElement("text");
        while (!textElement.isNull()) {
            EText text;
            text.setDomElement(textElement);
            if (!text.isValid())
                mValidFlag = false;
            mTexts.append(text);

            textElement = textElement.nextSiblingElement("text");
        }

        QDomElement wireElement = mElement.firstChildElement("wire");
        while (!wireElement.isNull()) {
            EWire wire;
            wire.setDomElement(wireElement);
            if (!wire.isValid())
                mValidFlag = false;
            mWires.append(wire);

            wireElement = wireElement.nextSiblingElement("wire");
        }
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

void ESymbol::paint(QPainter *painter, Settings *settings)
{
    QVector<ECircle>::iterator iCircle;
    for (iCircle = mCircles.begin(); iCircle != mCircles.end(); ++iCircle) {
        iCircle->paint(painter, settings);
    }

    // pin draw by instance

    QVector<ERectangle>::iterator iRectangle;
    for (iRectangle = mRectangles.begin(); iRectangle != mRectangles.end(); ++iRectangle) {
        iRectangle->paint(painter, settings);
    }

    // text draw by instance

    QVector<EWire>::iterator iWire;
    for (iWire = mWires.begin(); iWire != mWires.end(); ++iWire) {
        iWire->paint(painter, settings);
    }
}
