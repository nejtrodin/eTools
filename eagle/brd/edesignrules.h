#ifndef EDESIGNRULES_H
#define EDESIGNRULES_H

#include <QDomDocument>
#include <QtCore>

#include "../ecommon.h"

class EDesignRules {
public:
    static EDesignRules* instance();

    bool parse(QDomElement element);
    bool isValid() { return valid; }

    // via
    double getRvViaInner() { return rvViaInner; }
    double getRlMinViaInner() { return rlMinViaInner; }
    double getRlMaxViaInner() { return rlMaxViaInner; }
    double getRvViaOuter() { return rvViaOuter; }
    double getRlMinViaOuter() { return rlMinViaOuter; }
    double getRlMaxViaOuter() { return rlMaxViaOuter; }
    // pad
    double getRvPadTop() { return rvPadTop; }
    double getRvPadInner() { return rvPadInner; }
    double getRvPadBottom() { return rvPadBottom; }
    double getRlMinPadTop() { return rlMinPadTop; }
    double getRlMaxPadTop() { return rlMaxPadTop; }
    double getRlMinPadInner() { return rlMinPadInner; }
    double getRlMaxPadInner() { return rlMaxPadInner; }
    double getRlMinPadBottom() { return rlMinPadBottom; }
    double getRlMaxPadBottom() { return rlMaxPadBottom; }

private:
    EDesignRules();
    static EDesignRules* pInstance;

    bool valid;
    QString name;
    // via
    double rvViaOuter;
    double rlMinViaOuter;
    double rlMaxViaOuter;
    double rvViaInner;
    double rlMinViaInner;
    double rlMaxViaInner;
    // pad
    double rvPadTop;
    double rvPadInner;
    double rvPadBottom;
    double rlMinPadTop;
    double rlMaxPadTop;
    double rlMinPadInner;
    double rlMaxPadInner;
    double rlMinPadBottom;
    double rlMaxPadBottom;
};

#endif // EDESIGNRULES_H
