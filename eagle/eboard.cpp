#include "eboard.h"

EBoard::EBoard()
{
}

void EBoard::appendElement(EElement eElement)
{
    eElements.append(eElement);
}

void EBoard::appendSignal(ESignal eSignal)
{
    eSignals.append(eSignal);
}

void EBoard::setPlain(EBrdPlain ePlain)
{
    this->ePlain = ePlain;
}
