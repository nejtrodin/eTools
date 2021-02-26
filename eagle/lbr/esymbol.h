#ifndef ESYMBOL_H
#define ESYMBOL_H

#include "epin.h"
#include "../common/ecircle.h"
#include "../common/erectangle.h"
#include "../common/etext.h"
#include "../common/ewire.h"
#include "settings.h"
#include <QPainter>

class ESymbol : public ECoreElement
{
public:
    ESymbol() { }
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, Settings *settings);
    QString name() { return mName; }
    QVector<EPin> getPins() { return mPins; }
    QVector<EText> getTexts() { return mTexts; }

private:
    QString mName;
    QVector<EWire> mWires;
    QVector<EText> mTexts;
    QVector<ECircle> mCircles;
    QVector<EPin> mPins;
    QVector<ERectangle> mRectangles;
};

#endif // ESYMBOL_H
