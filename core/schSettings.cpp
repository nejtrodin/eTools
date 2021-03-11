#include "schSettings.h"
#include <QFontDatabase>

SchSettings::SchSettings()
{
    int id = QFontDatabase::addApplicationFont(":/fonts/gost_b.ttf");
    QString gost_b = QFontDatabase::applicationFontFamilies(id).at(0);
    mFont = QFont(gost_b);
}

QFont SchSettings::font()
{
    return mFont;
}

QColor SchSettings::getLayerColor(int layerNumber) const
{
    if (mLayers.contains(layerNumber)) {
        int colorNumber = mLayers[layerNumber].colorNumber;
        if (colorNumber >= 0 && colorNumber < 64) {
            if (mColorAsBlack)
                return QColor(Qt::black);
            else
                return mThemeColors[mLayers[layerNumber].colorNumber];
        }
    }

    return mErrorColor;
}

qreal SchSettings::sizeToPx(qreal size)
{
    // коэффициент перевода размера текста в пиксели. FIXME: нужно рассчитывать
    const qreal textScale = 1.4;
    return size * textScale;
}

qreal SchSettings::scale()
{
    return mScale;
}

void SchSettings::setScale(qreal scale)
{
    mScale = scale;
}

bool SchSettings::layerIsVisible(int layerNumber)
{
    if ((mLayers.contains(layerNumber) && mLayers[layerNumber].visible))
        return true;
    return false;
}

QList<Layer> SchSettings::layers()
{
    return mLayers.values();
}

void SchSettings::setLayers(QList<Layer> layers)
{
    mLayers.clear();
    foreach (Layer layer, layers)
        mLayers.insert(layer.number, layer);
}

void SchSettings::setColorsAsBlack(bool colorsAsBlack)
{
    mColorAsBlack = colorsAsBlack;
}

qreal SchSettings::pinXOffset() const
{
    return mPinXOffset;
}

qreal SchSettings::pinTextSize() const
{
    return mPinTextSize;
}

qreal SchSettings::padXOffset() const
{
    return mPadXOffset;
}

qreal SchSettings::padYOffset() const
{
    return mPadYOffset;
}

qreal SchSettings::padTextSize() const
{
    return mPadTextSize;
}

qreal SchSettings::labelUpOffset() const
{
    return mLabelUpOffset;
}
