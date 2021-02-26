#include "eelement.h"

EElement::EElement(QString name, EPackage package, qreal xPos, qreal yPos, qreal angle, bool mirror)
{
    m_name = name;
    m_package = package;
    m_position = QPointF(xPos, yPos);
    m_mirror = mirror;
    m_angle = angle;
}
