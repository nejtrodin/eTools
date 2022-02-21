#ifndef ESIGNAL_H
#define ESIGNAL_H

#include "QtCore"
#include "../ecommon.h"
#include "ebrdvia.h"

class ESignal : public ECoreElement
{
public:
    ESignal() { }
    void setDomElement(QDomElement rootElement) override;

    void appendVia(EBrdVia via);
    QVector<EBrdVia> getVias() { return m_vias; }

private:
    QVector<EBrdVia> m_vias;
    QString m_name;
};

#endif // ESIGNAL_H
