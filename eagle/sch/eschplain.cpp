#include "eschplain.h"

void ESchPlain::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;
    m_texts.clear();

    if (!m_domElement.isNull() && m_domElement.tagName() == "plain") {
        m_validFlag = true;

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
}

void ESchPlain::paint(QPainter *painter, SchSettings *settings)
{
    QVector<EText>::iterator iText;
    for (iText = m_texts.begin(); iText != m_texts.end(); ++iText) {
        auto drawingText = iText->getDrawingText();
        drawingText.paint(painter, settings);
    }

    QVector<EWire>::iterator iWire;
    for (iWire = m_wires.begin(); iWire != m_wires.end(); ++iWire) {
        iWire->paint(painter, settings);
    }
}
