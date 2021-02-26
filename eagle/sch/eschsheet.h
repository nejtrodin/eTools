#ifndef ESCHSHEET_H
#define ESCHSHEET_H

#include "../common/ecommon.h"
#include "eschnet.h"
#include "eschplain.h"
#include "eschinstance.h"
#include "eschcore.h"
#include "settings.h"
#include <QPainter>

class ESchSheet : public ECoreElement
{
public:
    ESchSheet() { }
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, Settings *settings, ESchCore *schCore);
    QString description() { return mDescription; }

private:
    QString mDescription;
    QVector<ESchNet> mNets;
    QVector<ESchInstance> mInstances;
    ESchPlain mPlain;
};

#endif // ESCHSHEET_H
