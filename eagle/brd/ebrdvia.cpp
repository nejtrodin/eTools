#include "ebrdvia.h"
#include "edesignrules.h"

EBrdVia::EBrdVia(double x, double y, double drill, double diameter)
{
    this->position = QPointF(x, y);
    this->drill = drill;
    this->diameter = diameter;

    EDesignRules* designRules = EDesignRules::instance();
    double innerDiameter = diameter;
    double outerDiameter = diameter;

    if (designRules->isValid()) {
        if (diameter <= 0) {
            innerDiameter = drill + 2 * drill * designRules->getRvViaInner();
            outerDiameter = drill + 2 * drill * designRules->getRvViaOuter();

            double minOuterDiameter = drill + 2 * designRules->getRlMinViaOuter();
            double maxOuterDiameter = drill + 2 * designRules->getRlMaxViaOuter();
            if (outerDiameter < minOuterDiameter)
                outerDiameter = minOuterDiameter;
            else if (outerDiameter > maxOuterDiameter)
                outerDiameter = maxOuterDiameter;
        }

        double minInnerDiameter = drill + 2 * designRules->getRlMinViaInner();
        double maxInnerDiameter = drill + 2 * designRules->getRlMaxViaInner();
        if (innerDiameter < minInnerDiameter)
            innerDiameter = minInnerDiameter;
        else if (innerDiameter > maxInnerDiameter)
            innerDiameter = maxInnerDiameter;
        this->innerDiameter = innerDiameter;
    }

    this->outerDiameter = outerDiameter;
    this->innerDiameter = innerDiameter;
}
