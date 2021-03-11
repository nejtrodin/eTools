#ifndef EWIRE_H
#define EWIRE_H

#include <QtCore>
#include "ecommon.h"
#include "schSettings.h"
#include <QPainter>

class EWire : public ECoreElement
{
public:
    EWire() { }
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, SchSettings *settings);
    qreal x1() { return mX1; }
    qreal y1() { return mY1; }
    qreal x2() { return mX2; }
    qreal y2() { return mY2; }

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
