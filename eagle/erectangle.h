#ifndef ERECTANGLE_H
#define ERECTANGLE_H

#include <QPainter>
#include "ecommon.h"
#include "schSettings.h"

class ERectangle : public ECoreElement
{
public:
    ERectangle() { }
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, SchSettings *settings);

private:
    qreal mX1 = 0;
    qreal mY1 = 0;
    qreal mX2 = 0;
    qreal mY2 = 0;
    int mLayer = 0;
    qreal mAngle = 0;
};

#endif // ERECTANGLE_H
