#ifndef ESCHPLAIN_H
#define ESCHPLAIN_H

#include "../ecommon.h"
#include "../etext.h"
#include "../ewire.h"
#include "schSettings.h"
#include <QPainter>

class ESchPlain : public ECoreElement
{
public:
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, SchSettings *settings);

private:
    QVector<EText> m_texts;
    QVector<EWire> m_wires;
};

#endif // ESCHPLAIN_H
