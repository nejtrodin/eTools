#ifndef EPLAIN_H
#define EPLAIN_H

#include "ecommon.h"

class EPlain {
public:
    EPlain();
    void appendHole(Hole hole);
    QVector<Hole> getHoles() { return eHoles; }

private:
    QVector<Hole> eHoles;
};

#endif // EPLAIN_H
