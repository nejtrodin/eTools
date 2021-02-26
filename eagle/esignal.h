#ifndef ESIGNAL_H
#define ESIGNAL_H

#include "QtCore"
#include "common/ecommon.h"
#include "brd/ebrdvia.h"

class ESignal {
public:
    ESignal();
    ESignal(QString name);
    void appendVia(EBrdVia via);
    QVector<EBrdVia> getVias() { return vias; }

private:
    QVector<EBrdVia> vias;
    QString name;
};

#endif // ESIGNAL_H
