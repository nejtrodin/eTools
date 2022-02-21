#ifndef EPAD_H
#define EPAD_H

#include <QtCore>
#include "../ecommon.h"

class EPad : public ECoreElement
{
public:
    EPad() { }
    void setDomElement(QDomElement rootElement) override;
    void update();

    QPointF position() const {return m_position;}
    double drill() const {return m_drill;}
    double topDiameter() const {return m_topDiameter;}
    double innerDiameter() const {return m_innerDiameter;}
    double bottomDiameter() const {return m_bottomDiameter;}

private:
    QPointF m_position;
    double m_drill;
    double m_diameter;
    double m_topDiameter;
    double m_innerDiameter;
    double m_bottomDiameter;
    bool m_first;
};

#endif // EPAD_H
