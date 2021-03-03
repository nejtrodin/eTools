#ifndef EPIN_H
#define EPIN_H

#include "../common/ecommon.h"
#include "settings.h"
#include <QPainter>

class EPin : public ECoreElement
{
public:
    enum PinVisible {
        VisibleOff,
        VisiblePad,
        VisiblePin,
        VisibleBoth,
    };

    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, QString padName, Settings *settings);
    QString name() { return mName; }
    qreal x() { return mX; }
    qreal y() { return mY; }
    qreal length() { return mLength; }
    int angle() { return mAngle; }
    PinVisible visible() { return mVisible; }

private:
    qreal parseLengthAttribute(QString lengthValue);
    PinVisible parseVisibleAttribute(QString visibleValue);

    QString mName;
    qreal mX = 0;
    qreal mY = 0;
    qreal mLength = 0;
    int mAngle = 0;
    bool mMirrorFlag = false;
    PinVisible mVisible = VisibleBoth;
};

#endif // EPIN_H
