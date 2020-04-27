#ifndef EVIA_H
#define EVIA_H

#include "QtCore"

class Via {
public:
    Via() { }
    Via(double x, double y, double drill, double diameter);

    QPointF getPosition() const { return position; }
    double getDrill() const { return drill; }
    double getOuterDiameter() const { return outerDiameter; }
    double getInnerDiameter() const { return innerDiameter; }

private:
    QPointF position;
    double drill;
    double diameter;
    double outerDiameter;
    double innerDiameter;
};

class Hole {
public:
    Hole() { }
    Hole(double x, double y, double drill);

    QPointF pos;
    double drill;
};

class Pad {
public:
    Pad() { }
    Pad(double x, double y, double drill, double diameter);

    QPointF getPosition() const { return position; }
    double getDrill() const { return drill; }
    double getTopDiameter() const { return topDiameter; }
    double getInnerDiameter() const { return innerDiameter; }
    double getBottomDiameter() const { return bottomDiameter; }

private:
    QPointF position;
    double drill;
    double diameter;
    double topDiameter;
    double innerDiameter;
    double bottomDiameter;
};

struct Wire {
    QPointF start, finish;
    double width;
    int layer;
};

double convertSizeTextToMilimeters(QString text, bool* ok = nullptr);

#endif // EVIA_H
