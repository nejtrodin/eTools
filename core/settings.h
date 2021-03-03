#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore>
#include <QColor>
#include <QFont>
#include "layer.h"

/* Настройки цветов
 * В Eagle хранятся значения 64 цветов. Для каждого слоя назначается номер соответствующего ему
 * цвета: от 0 до 63.
 */

class Settings
{
public:
    Settings();
    QColor getColor(int layerNumber);

    QFont schFont;
    qreal schScale = 1;
    QColor defaultColor = QColor::fromRgb(127, 127, 127, 180);
    // dark theme from eagle 9
    QColor themeColors[64] = {
        // 0..7
        QColor::fromRgb(0, 0, 0),
        QColor::fromRgb(50, 50, 200),
        QColor::fromRgb(50, 200, 50),
        QColor::fromRgb(50, 200, 200),
        QColor::fromRgb(200, 50, 50),
        QColor::fromRgb(200, 50, 200),
        QColor::fromRgb(200, 200, 50),
        QColor::fromRgb(200, 200, 200),
        // with alpha channel
//        QColor::fromRgb(50, 50, 200, 180),
//        QColor::fromRgb(50, 200, 50, 180),
//        QColor::fromRgb(50, 200, 200, 180),
//        QColor::fromRgb(200, 50, 50, 180),
//        QColor::fromRgb(200, 50, 200, 180),
//        QColor::fromRgb(200, 200, 50, 180),
//        QColor::fromRgb(200, 200, 200, 180),
        // 8..15
        QColor::fromRgb(100, 100, 100, 100),
        QColor::fromRgb(0, 0, 255, 180),
        QColor::fromRgb(0, 255, 0, 180),
        QColor::fromRgb(0, 255, 255, 180),
        QColor::fromRgb(255, 0, 0, 180),
        QColor::fromRgb(255, 0, 255, 180),
        QColor::fromRgb(255, 255, 0, 180),
        QColor::fromRgb(255, 255, 255, 180),
        // 16..23
        QColor::fromRgb(238, 32, 32),
        QColor::fromRgb(0, 0, 0),
        QColor::fromRgb(68, 68, 68),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        // 24..31
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        // 32..39
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        // 40..47
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        // 48..55
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        // 56..63
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
        QColor::fromRgb(127, 127, 127, 180),
    };

    QMap<int, Layer> layers;

    // коэффициент перевода размера текста в пиксели. FIXME: нужно рассчитывать
    const qreal textScale = 1.4;

    qreal pinXOffset = 1;  // смещение текста от конца линии пина
    qreal pinTextSize = 2;
    qreal padXOffset = 1;  // смещение текста от конца линии пина
    qreal padYOffset = 1;
    qreal padTextSize = 2;
    const int pinLayer = 94;
    const int pinTextLayer = 95;
    qreal labelUpOffset = 1;
};

#endif // SETTINGS_H
