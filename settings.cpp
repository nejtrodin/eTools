#include "settings.h"

Settings::Settings()
{
    layersColor[91] = 2;  // net
    layersColor[92] = 1;  // busses
    layersColor[94] = 4;  // symbols
    layersColor[95] = 7;  // names
}

QColor Settings::getColor(int layer)
{
    if (layersColor.contains(layer))
        return themeColors[layersColor[layer]];
    else
        return defaultColor;
}
