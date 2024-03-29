#ifndef ECOMMON_H
#define ECOMMON_H

#include <QtCore>
#include <QDomElement>
#include <QPainter>

class ECoreElement
{
public:
    ECoreElement() { }
    virtual ~ECoreElement() { }
    virtual void setDomElement(QDomElement rootElement) = 0;
    bool isValid() { return m_validFlag; }

protected:
    QDomElement m_domElement;
    bool m_validFlag = false;
};

typedef enum {
    AlignBottomLeft,
    AlignBottomCenter,
    AlignBottomRight,
    AlignCenterLeft,
    AlignCenter,
    AlignCenterRight,
    AlignTopLeft,
    AlignTopCenter,
    AlignTopRight,
} EAlign;

class ECommon
{
public:
    static EAlign parseAlignAttribute(QString value);
    static bool parseRotAttribute(QString value, int *angle, bool *mirror);
    static bool parseRotAttribute(QString value, qreal *angle, bool *mirror);
    static EAlign mirrorAlign(EAlign align, qreal angle = 0); // for text
    static QPointF getDrawPosition(qreal height, qreal width, EAlign align);
    static double textSizeToMilimeters(QString text, bool *ok = nullptr);
    static QPointF rotatePoint(const QPointF &point, const qreal &angle);
};

class Hole
{
public:
    Hole() { }
    Hole(double x, double y, double drill);

    QPointF pos;
    double drill;
};

struct EConnect
{
    QString gate;
    QString pin;
    QString pad;
};

#endif // ECOMMON_H
