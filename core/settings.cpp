#include "settings.h"

Settings::Settings() { }

QColor Settings::getColor(int layerNumber)
{
    if (layers.contains(layerNumber))
        return themeColors[layers[layerNumber].colorNumber];
    else
        return defaultColor;
}
