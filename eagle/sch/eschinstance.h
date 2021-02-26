#ifndef ESCHINSTANCE_H
#define ESCHINSTANCE_H

#include "../common/eattribute.h"
#include "eschcore.h"
#include "settings.h"
#include <QPicture>

class ESchInstance : public ECoreElement
{
public:
    ESchInstance() { }
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, Settings *settings, ESchCore *schCore);

private:
    QString mPartName;
    QString mGate;
    qreal mX = 0;
    qreal mY = 0;
    bool mSmashed = false;
    bool mMirrorFlag = false;
    int mAngle = 0;

    QPicture mInstancePicture;
    QVector<EAttribute> mAttributes;
};

#endif // ESCHINSTANCE_H
