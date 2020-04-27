#ifndef ESIGNAL_H
#define ESIGNAL_H

#include "QtCore"
#include "ecommon.h"

class ESignal {
public:
    ESignal();
    ESignal(QString name);
    void appendVia(Via via);
    QVector<Via> getVias() { return vias; }

private:
    QVector<Via> vias;
    QString name;
};

#endif // ESIGNAL_H
