#ifndef ELAYER_H
#define ELAYER_H

#include "ecommon.h"
#include "layer.h"

class ELayer : public ECoreElement
{
public:
    ELayer() { }
    void setDomElement(QDomElement rootElement) override;
    Layer getLayer() { return mLayer; }

private:
    Layer mLayer;
//    int mNumber;
//    QString mName;
//    int mColor;
//    int mFill;
//    bool mVisible;
//    bool mActive;
};

#endif // ELAYER_H
