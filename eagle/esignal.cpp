#include "esignal.h"

ESignal::ESignal()
{
}

ESignal::ESignal(QString name)
{
    this->name = name;
}

void ESignal::appendVia(EBrdVia via)
{
    vias.append(via);
}
