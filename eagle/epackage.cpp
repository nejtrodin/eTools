#include "epackage.h"

EPackage::EPackage()
{
    m_nullFlag = true;
    m_boundX1 = 0;
    m_boundY1 = 0;
    m_boundX2 = 0;
    m_boundY2 = 0;
}

EPackage::EPackage(QString name, QString libraryName)
    : EPackage()
{
    m_name = name;
    m_libraryName = libraryName;
    if (!m_name.isEmpty() || !m_libraryName.isEmpty())
        m_nullFlag = false;
}

void EPackage::appendWire(double x1, double y1, double x2, double y2, double width, int layer)
{
    Wire wire;
    wire.start = QPointF(x1, y1);
    wire.finish = QPointF(x2, y2);
    wire.width = width;
    wire.layer = layer;

    wireVector.append(wire);
    m_nullFlag = false;

    // calculate bound
    qreal leftX = x1 < x1 ? x1 : x2;
    qreal leftY = y1 < y2 ? y1 : y2;
    if (m_boundX1 > leftX)
        m_boundX1 = leftX;
    if (m_boundY1 > leftY)
        m_boundY1 = leftY;

    qreal rightX = x1 > x1 ? x1 : x2;
    qreal rightY = y1 > y2 ? y1 : y2;
    if (m_boundX2 < rightX)
        m_boundX2 = rightX;
    if (m_boundY2 < rightY)
        m_boundY2 = rightY;
}

void EPackage::appendPad(double x, double y, double drill, double diameter)
{
    Pad pad(x, y, drill, diameter);
    padVector.append(pad);
}

void EPackage::appendHole(double x, double y, double drill)
{
    Hole hole(x, y, drill);
    holesVector.append(hole);
}
