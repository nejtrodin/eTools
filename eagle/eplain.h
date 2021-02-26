#ifndef EPLAIN_H
#define EPLAIN_H

#include "common/ecommon.h"

class EBrdPlain {
public:
    EBrdPlain();
    void appendHole(Hole hole);
    QVector<Hole> getHoles() { return eHoles; }

private:
    QVector<Hole> eHoles;
};

#endif // EPLAIN_H
