#include "ecommon.h"

#include "edesignrules.h"

Via::Via(double x, double y, double drill, double diameter)
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

Hole::Hole(double x, double y, double drill)
{
    this->pos = QPointF(x, y);
    this->drill = drill;
}

Pad::Pad(double x, double y, double drill, double diameter)
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

double convertSizeTextToMilimeters(QString text, bool* ok)
{
    double result = 0;

    if (text.right(2) == "mm") {
        result = text.left(text.size() - 2).toDouble(ok);
    } else if (text.right(3) == "mil") {
        result = 0.0254 * text.left(text.size() - 3).toDouble(ok);
    } else {
        *ok = false;
    }

    return result;
}
