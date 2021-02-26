#include "ebrdpad.h"
#include "edesignrules.h"

EBrdPad::EBrdPad(double x, double y, double drill, double diameter)
{
    this->position = QPointF(x, y);
    this->drill = drill;
    this->diameter = diameter;

    EDesignRules* designRules = EDesignRules::instance();
    double topDiameter = diameter;
    double innerDiameter = diameter;
    double bottomDiameter = diameter;

    if (designRules->isValid()) {
        if (diameter <= 0) {
            topDiameter = drill + 2 * drill * designRules->getRvPadTop();
            innerDiameter = drill + 2 * drill * designRules->getRvPadInner();
            bottomDiameter = drill + 2 * drill * designRules->getRvPadBottom();

            double minTopDiameter = drill + 2 * designRules->getRlMinPadTop();
            double maxTopDiameter = drill + 2 * designRules->getRlMaxPadTop();
            if (topDiameter < minTopDiameter)
                topDiameter = minTopDiameter;
            else if (topDiameter > maxTopDiameter)
                topDiameter = maxTopDiameter;

            double minBottomDiameter = drill + 2 * designRules->getRlMinPadBottom();
            double maxBottomDiameter = drill + 2 * designRules->getRlMaxPadBottom();
            if (bottomDiameter < minBottomDiameter)
                bottomDiameter = minBottomDiameter;
            else if (bottomDiameter > maxBottomDiameter)
                bottomDiameter = maxBottomDiameter;
        }

        double minInnerDiameter = drill + 2 * designRules->getRlMinPadInner();
        double maxInnerDiameter = drill + 2 * designRules->getRlMaxPadInner();
        if (innerDiameter < minInnerDiameter)
            innerDiameter = minInnerDiameter;
        else if (innerDiameter > maxInnerDiameter)
            innerDiameter = maxInnerDiameter;
    }

    this->topDiameter = topDiameter;
    this->bottomDiameter = bottomDiameter;
    this->innerDiameter = innerDiameter;
}
