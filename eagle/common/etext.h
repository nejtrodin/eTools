#ifndef ETEXT_H
#define ETEXT_H

#include "ecommon.h"
#include "drawingtext.h"
#include "schSettings.h"
#include <QPainter>

class ELabel : public ECoreElement
{
public:
    ELabel() { }
    void setDomElement(QDomElement rootElement) override;
    static void drawText(QPainter *painter, QPointF position, QString text, qreal size, int angle,
                         EAlign align, int layer, SchSettings *settings);
    DrawingText getDrawingText();

protected:
    qreal mX = 0;
    qreal mY = 0;
    qreal mSize = 1;
    int angle = 0;
    bool mMirror = false;
    int mLayer = -1;
    EAlign mAlign = AlignBottomLeft;
};


class EText : public ELabel
{
public:
    EText() { }
    void setDomElement(QDomElement rootElement) override;
    DrawingText getDrawingText();
    QString text() { return mText; }

private:
    QString mText;
    int mDistance = 50;
};

#endif // ETEXT_H
