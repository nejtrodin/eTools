#ifndef EBOARD_H
#define EBOARD_H

#include "common/ecommon.h"
#include "brd/edesignrules.h"
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
    void setPlain(EBrdPlain ePlain);
    EBrdPlain getPlain() { return ePlain; }

private:
    QVector<EElement> eElements;
    QVector<ESignal> eSignals;
    EBrdPlain ePlain;
};

#endif // EBOARD_H
