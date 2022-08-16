#ifndef SCHSETTINGS_H
#define SCHSETTINGS_H

#include <QtCore>
#include <QColor>
#include <QFont>
#include "layer.h"

/* Настройки цветов
 * В Eagle хранятся значения 64 цветов. Для каждого слоя назначается номер соответствующего ему
 * цвета: от 0 до 63.
 */

class SchSettings
{
public:
    enum {
        netsLayer = 91,
        bussesLayer = 92,
        symbolsLayer = 94,
        namesLayer = 95,
        valuesLayer = 96,
        };

    SchSettings();

    QFont font();
    qreal sizeToPx(qreal size);
    qreal scale();
    void setScale(qreal scale);

    QColor getLayerColor(int layerNumber) const;
    bool layerIsVisible(int layerNumber);
    QList<Layer> layers();
    void setLayers(QList<Layer> layers);
    void setColorsAsBlack(bool colorsAsBlack);

    qreal pinXOffset() const;
    qreal pinTextSize() const;
    void setPinTextSize(qreal size);
    qreal padXOffset() const;
    qreal padYOffset() const;
    qreal padTextSize() const;
    qreal labelUpOffset() const;

private:
    QFont mFont;
    qreal mScale = 1;
    QColor mErrorColor = QColor::fromRgb(255, 255, 0);
    // dark theme from eagle 9
    QColor mThemeColors[64] = {
        // 0..7
        QColor::fromRgb(0, 0, 0),
        QColor::fromRgb(50, 50, 200),
        QColor::fromRgb(50, 200, 50),
        QColor::fromRgb(50, 200, 200),
        QColor::fromRgb(200, 50, 50),
        QColor::fromRgb(200, 50, 200),
        QColor::fromRgb(200, 200, 50),
        QColor::fromRgb(200, 200, 200),
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
    QMap<int, Layer> mLayers;
    qreal mPinXOffset = 1;
    qreal mPinTextSize = 2;
    qreal mPadXOffset = 1;
    qreal mPadYOffset = 1;
    qreal mPadTextSize = 2;
    qreal mLabelUpOffset = 1;

    bool mColorAsBlack = false;
};

#endif // SCHSETTINGS_H
