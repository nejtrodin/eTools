#ifndef EPACKAGE_H
#define EPACKAGE_H

#include "QtCore"
#include "ecommon.h"

class EPackage {
public:
    EPackage();
    EPackage(QString name, QString libraryName);
    bool isNull() { return m_nullFlag; }
    QString name() const { return m_name; }
    QString libraryName() const { return m_libraryName; }
    QPointF getTopLeft() const { return QPointF(m_boundX1, m_boundY2); }
    QPointF getBottomRight() const { return QPointF(m_boundX2, m_boundY1); }
    QVector<Wire> getWires() const { return wireVector; }
    QVector<Pad> getPads() const { return padVector; }
    QVector<Hole> getHoles() const { return holesVector; }

    void appendWire(double x1, double y1, double x2, double y2, double width, int layer);
    void appendPad(double x, double y, double drill, double diameter);
    void appendHole(double x, double y, double drill);

private:
    bool m_nullFlag;
    QString m_name;
    QString m_libraryName;
    qreal m_boundX1;
    qreal m_boundX2;
    qreal m_boundY1;
    qreal m_boundY2;
    QVector<Wire> wireVector;
    QVector<Pad> padVector;
    QVector<Hole> holesVector;
};

#endif // EPACKAGE_H
