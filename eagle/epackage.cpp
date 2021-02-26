#include "epackage.h"

EPackage::EPackage()
{
    m_boundX1 = 0;
    m_boundY1 = 0;
    m_boundX2 = 0;
    m_boundY2 = 0;
}

EPackage::EPackage(const QString &name, const QString &libraryName)
    : EPackage()
{
    this->mName = name;
    this->mLibraryName = libraryName;
}

//void EPackage::appendWire(Wire wire)
//{
//    wireVector.append(wire);

    // calculate bound
//    QPointF p1 = wire.getP1();
//    QPointF p2 = wire.getP2();

//    qreal leftX = wire.x1 < wire.x2 ? wire.x1 : wire.x2;
//    qreal leftY = wire.y1 < wire.y2 ? wire.y1 : wire.y2;
//    if (m_boundX1 > leftX)
//        m_boundX1 = leftX;
//    if (m_boundY1 > leftY)
//        m_boundY1 = leftY;

//    qreal rightX = wire.x1 > wire.x2 ? wire.x1 : wire.x2;
//    qreal rightY = wire.y1 > wire.y2 ? wire.y1 : wire.y2;
//    if (m_boundX2 < rightX)
//        m_boundX2 = rightX;
//    if (m_boundY2 < rightY)
//        m_boundY2 = rightY;
//}

void EPackage::appendPad(double x, double y, double drill, double diameter)
{
    EBrdPad pad(x, y, drill, diameter);
    mPads.append(pad);
}

void EPackage::appendHole(double x, double y, double drill)
{
    Hole hole(x, y, drill);
    mHoles.append(hole);
}
