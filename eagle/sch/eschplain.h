#ifndef ESCHPLAIN_H
#define ESCHPLAIN_H

#include "../common/ecommon.h"
#include "../common/etext.h"
#include "../common/ewire.h"
#include "schSettings.h"
#include <QPainter>

class ESchPlain : public ECoreElement
{
public:
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, SchSettings *settings);

private:
    QVector<EText> mTexts;
    QVector<EWire> mWires;
};

#endif // ESCHPLAIN_H
