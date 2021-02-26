#ifndef ESEGMENT_H
#define ESEGMENT_H

#include "../common/ecommon.h"
#include "../common/etext.h"
#include "../common/ewire.h"
#include "settings.h"
#include <QPainter>

struct Junction
{
    qreal x;
    qreal y;
};

class ESegment : public ECoreElement
{
public:
    ESegment() { }
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, QString netName, Settings *settings);

private:
    QVector<EWire> mWires;
    QVector<Junction> mJunction;
    QVector<ELabel> mLabels;
};

#endif // ESEGMENT_H
