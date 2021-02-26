#ifndef ENET_H
#define ENET_H

#include "esegment.h"
#include "settings.h"
#include <QPainter>

class ESchNet : public ECoreElement
{
public:
    ESchNet() { }
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, Settings *settings);

private:
    QString mName;

    QVector<ESegment> mSegments;
};

#endif // ENET_H
