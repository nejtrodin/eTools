#ifndef EBRDPAD_H
#define EBRDPAD_H

#include <QtCore>

class EBrdPad
{
public:
    EBrdPad() {}
    EBrdPad(double x, double y, double drill, double diameter);

    QPointF getPosition() const {return position;}
    double getDrill() const {return drill;}
    double getTopDiameter() const {return topDiameter;}
    double getInnerDiameter() const {return innerDiameter;}
    double getBottomDiameter() const {return bottomDiameter;}

private:
    QPointF position;
    double drill;
    double diameter;
    double topDiameter;
    double innerDiameter;
    double bottomDiameter;
};

#endif // EBRDPAD_H
