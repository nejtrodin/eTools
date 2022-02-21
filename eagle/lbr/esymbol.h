#ifndef ESYMBOL_H
#define ESYMBOL_H

#include "epin.h"
#include "../ecircle.h"
#include "../erectangle.h"
#include "../etext.h"
#include "../ewire.h"
#include "schSettings.h"
#include <QPainter>

class ESymbol : public ECoreElement
{
public:
    ESymbol() { }
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, SchSettings *settings);
    QString name() { return m_name; }
    QVector<EPin> getPins() { return m_pins; }
    QVector<EText> getTexts() { return m_texts; }

private:
    QString m_name;
    QVector<EWire> m_wires;
    QVector<EText> m_texts;
    QVector<ECircle> m_circles;
    QVector<EPin> m_pins;
    QVector<ERectangle> m_rectangles;
};

#endif // ESYMBOL_H
