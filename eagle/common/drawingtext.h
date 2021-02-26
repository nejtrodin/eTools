#ifndef DRAWINGTEXT_H
#define DRAWINGTEXT_H

#include "ecommon.h"
#include "settings.h"
#include <QPainter>

class DrawingText
{
public:
    DrawingText(QString text, QPointF position, qreal size, int angle, EAlign align, int layer,
                int distance = 50);
    void setText(QString text) { mText = text; }
    QString text() { return mText; }
    void move(QPointF position);
    void rotate(int angle);
    void mirror();
    void paint(QPainter *painter, Settings *settings, bool readable = true);

private:
    QString mText;
    QPointF mPosition;
    qreal mSize;
    int mAngle;
    EAlign mAlign;
    int mLayer;
    int mDistance;
};

#endif // DRAWINGTEXT_H
