#ifndef EPIN_H
#define EPIN_H

#include "../ecommon.h"
#include "schSettings.h"
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
    QString name() { return m_name; }
    qreal x() { return m_x; }
    qreal y() { return m_y; }
    qreal length() { return m_length; }
    int angle() { return m_angle; }
    PinVisible visible() { return m_visible; }

private:
    qreal parseLengthAttribute(QString lengthValue);
    PinVisible parseVisibleAttribute(QString visibleValue);

    QString m_name;
    qreal m_x = 0;
    qreal m_y = 0;
    qreal m_length = 0;
    int m_angle = 0;
    bool m_mirrorFlag = false;
    PinVisible m_visible = VisibleBoth;
};

#endif // EPIN_H
