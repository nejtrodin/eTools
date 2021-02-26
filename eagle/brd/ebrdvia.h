#ifndef EBRDVIA_H
#define EBRDVIA_H

#include <QtCore>

class EBrdVia
{
public:
    EBrdVia() {}
    EBrdVia(double x, double y, double drill, double diameter);

    QPointF getPosition() const {return position;}
    double getDrill() const {return drill;}
    double getOuterDiameter() const {return outerDiameter;}
    double getInnerDiameter() const {return innerDiameter;}

private:
    QPointF position;
    double drill;
    double diameter;
    double outerDiameter;
    double innerDiameter;
};

#endif // EBRDVIA_H
