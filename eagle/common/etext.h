#ifndef ETEXT_H
#define ETEXT_H

#include "ecommon.h"
#include "drawingtext.h"
#include "settings.h"
#include <QPainter>

class ELabel : public ECoreElement
{
public:
    ELabel() { }
    void setDomElement(QDomElement rootElement) override;
    static void drawText(QPainter *painter, QPointF position, QString text, qreal size, int angle,
                         EAlign align, int layer, Settings *settings);
    void paint(QPainter *painter, Settings *settings, QString text);

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
    void paint(QString text, QPainter *painter, Settings *settings);
    void paint(QPainter *painter, Settings *settings);

    DrawingText getDrawingText();
    QString text() { return mText; }

private:
    QString mText;
    int distance = 50;
};

#endif // ETEXT_H
