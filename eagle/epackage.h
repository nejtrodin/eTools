#ifndef EPACKAGE_H
#define EPACKAGE_H

#include "QtCore"
#include "common/ecommon.h"
#include "brd/ebrdpad.h"

class EPackage {
public:
    EPackage();
    EPackage(const QString &name, const QString &libraryName);
    QPointF getTopLeft() const { return QPointF(m_boundX1, m_boundY2); }
    QPointF getBottomRight() const { return QPointF(m_boundX2, m_boundY1); }
//    QVector<Wire> getWires() const { return wireVector; }
    QVector<EBrdPad> getPads() const { return mPads; }
    QVector<Hole> getHoles() const { return mHoles; }

//    void appendWire(Wire wire);
    void appendPad(double x, double y, double drill, double diameter);
    void appendHole(double x, double y, double drill);

    QString getName() const {return mName;}
    void setName(const QString &value) {mName = value;}

    QString getLibraryName() const {return mLibraryName;}
    void setLibraryName(const QString &value) {mLibraryName = value;}

private:
    QString mName;
    QString mLibraryName;
    qreal m_boundX1;
    qreal m_boundX2;
    qreal m_boundY1;
    qreal m_boundY2;
//    QVector<Wire> wireVector;
    QVector<EBrdPad> mPads;
    QVector<Hole> mHoles;
};

#endif // EPACKAGE_H
