#ifndef EVALUEATTRIBUTE_H
#define EVALUEATTRIBUTE_H

#include <QtCore>
#include "ecommon.h"

class EValueAttribute : public ECoreElement
{
public:
    void setDomElement(QDomElement rootElement) override;
    QString name() { return mName; }
    QString value() { return mValue; }

private:
    QString mName;
    QString mValue;
    bool mConstant;
};

#endif // EVALUEATTRIBUTE_H
