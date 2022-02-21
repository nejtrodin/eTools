#ifndef EPACKAGE_H
#define EPACKAGE_H

#include "QtCore"
#include "../ecommon.h"
#include "../ewire.h"
#include "../lbr/epad.h"

class EPackage : public ECoreElement
{
public:
    EPackage();
    void setDomElement(QDomElement rootElement) override;

    QPointF getTopLeft() const { return QPointF(m_boundX1, m_boundY2); }
    QPointF getBottomRight() const { return QPointF(m_boundX2, m_boundY1); }
    QVector<EWire> getWires() const { return m_wires; }
    QVector<EPad> getPads() const { return m_pads; }
    QVector<Hole> getHoles() const { return m_holes; }

    QString name() const {return mName;}
    void setName(const QString &value) {mName = value;}

private:
    QString mName;
    qreal m_boundX1;
    qreal m_boundX2;
    qreal m_boundY1;
    qreal m_boundY2;
    QVector<EWire> m_wires;
    QVector<EPad> m_pads;
    QVector<Hole> m_holes;
};

#endif // EPACKAGE_H
