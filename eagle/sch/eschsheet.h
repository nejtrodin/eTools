#ifndef ESCHSHEET_H
#define ESCHSHEET_H

#include "../ecommon.h"
#include "eschnet.h"
#include "eschplain.h"
#include "eschinstance.h"
#include "eschcore.h"
#include "schSettings.h"
#include <QPainter>

class ESchSheet : public ECoreElement
{
public:
    ESchSheet() { }
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, SchSettings *settings, ESchCore *schCore);
    QString description() { return m_description; }

private:
    QString m_description;
    QVector<ESchNet> m_nets;
    QVector<ESchInstance> m_instances;
    ESchPlain m_plain;
};

#endif // ESCHSHEET_H
