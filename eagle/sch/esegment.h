#ifndef ESEGMENT_H
#define ESEGMENT_H

#include "../ecommon.h"
#include "../etext.h"
#include "../ewire.h"
#include "schSettings.h"
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
    void paint(QPainter *painter, QString netName, SchSettings *settings);

private:
    QVector<EWire> m_wires;
    QVector<Junction> m_junction;
    QVector<ELabel> m_labels;
};

#endif // ESEGMENT_H
