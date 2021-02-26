#ifndef ECIRCLE_H
#define ECIRCLE_H

#include <QtCore>
#include "ecommon.h"
#include "settings.h"
#include <QPainter>

class ECircle : public ECoreElement
{
public:
    ECircle() { }
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, Settings *settings);

private:
    qreal mX = 0;
    qreal mY = 0;
    qreal mRadius = 0;
    qreal mWidth = 0;
    int mLayer = 0;
};

#endif // ECIRCLE_H
