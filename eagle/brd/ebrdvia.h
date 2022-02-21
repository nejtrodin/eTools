#ifndef EBRDVIA_H
#define EBRDVIA_H

#include <QtCore>
#include "../ecommon.h"

class EBrdVia : public ECoreElement
{
public:
    EBrdVia() {}
    void setDomElement(QDomElement rootElement) override;
    void update();

    QPointF getPosition() const {return m_position;}
    double getDrill() const {return m_drill;}
    double getOuterDiameter() const {return m_outerDiameter;}
    double getInnerDiameter() const {return m_innerDiameter;}

private:
    QPointF m_position;
    double m_drill;
    double m_diameter;
    double m_outerDiameter;
    double m_innerDiameter;
};

#endif // EBRDVIA_H
