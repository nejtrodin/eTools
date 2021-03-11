#include "eschplain.h"

void ESchPlain::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;
    mTexts.clear();

    if (!mElement.isNull() && mElement.tagName() == "plain") {
        mValidFlag = true;

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
}

void ESchPlain::paint(QPainter *painter, SchSettings *settings)
{
    QVector<EText>::iterator iText;
    for (iText = mTexts.begin(); iText != mTexts.end(); ++iText) {
        auto drawingText = iText->getDrawingText();
        drawingText.paint(painter, settings);
    }

    QVector<EWire>::iterator iWire;
    for (iWire = mWires.begin(); iWire != mWires.end(); ++iWire) {
        iWire->paint(painter, settings);
    }
}
