#ifndef EATTRIBUTE_H
#define EATTRIBUTE_H

#include <QtCore>
#include "ecommon.h"

class EAttribute : public ECoreElement
{
public:
    EAttribute() { }
    void setDomElement(QDomElement rootElement) override;
    QString name() { return mName; }
    qreal size() { return mSize; }
    int layer() { return mLayer; }
    QPointF position() { return QPointF(mX, mY); }
    int angle() { return mAngle; }
    bool mirror() { return mMirror; }
    EAlign align() { return mAlign; }

private:
    QString mName;
    qreal mX = 0;
    qreal mY = 0;
    qreal mSize = 0;
    int mLayer = 0;
    int mAngle = 0;
    bool mMirror = false;
    EAlign mAlign = AlignBottomLeft;
};

#endif // EATTRIBUTE_H
