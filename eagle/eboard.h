#ifndef EBOARD_H
#define EBOARD_H

#include "ecommon.h"
#include "edesignrules.h"
#include "eelement.h"
#include "eplain.h"
#include "esignal.h"

class EBoard {
public:
    EBoard();
    void appendElement(EElement eElement);
    QVector<EElement> getElements() { return eElements; }
    void appendSignal(ESignal eSignal);
    QVector<ESignal> getSignals() { return eSignals; }
    void setPlain(EPlain ePlain);
    EPlain getPlain() { return ePlain; }

private:
    QVector<EElement> eElements;
    QVector<ESignal> eSignals;
    EPlain ePlain;
};

#endif // EBOARD_H
