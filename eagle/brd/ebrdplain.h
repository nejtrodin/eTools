#ifndef EBRDPLAIN_H
#define EBRDPLAIN_H

#include "../ecommon.h"

class EBrdPlain : public ECoreElement
{
public:
    EBrdPlain() { }
    void setDomElement(QDomElement rootElement) override;

    void appendHole(Hole hole);
    QVector<Hole> getHoles() { return eHoles; }

private:
    QVector<Hole> eHoles;
};

#endif // EBRDPLAIN_H
