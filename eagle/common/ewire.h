#ifndef EWIRE_H
#define EWIRE_H

#include <QtCore>
#include "ecommon.h"
#include "settings.h"
#include <QPainter>

class EWire : public ECoreElement
{
public:
    EWire() { }
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, Settings *settings);

private:
    qreal mX1 = 0;
    qreal mY1 = 0;
    qreal mX2 = 0;
    qreal mY2 = 0;
    qreal mWidth = 0;
    int mLayer = 0;
    qreal mCurve = 0;
};

#endif // EWIRE_H
