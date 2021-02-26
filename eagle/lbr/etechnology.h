#ifndef ETECHNOLOGY_H
#define ETECHNOLOGY_H

#include "../common/ecommon.h"
#include "../common/evalueattribute.h"

class ETechnology : public ECoreElement
{
public:
    ETechnology() { }
    void setDomElement(QDomElement rootElement) override;
    QString name() { return mName; }
    QList<EValueAttribute> getValueAttributes() { return mValueAttributes.values(); }

private:
    QString mName;
    QMap<QString, EValueAttribute> mValueAttributes;
};

#endif // ETECHNOLOGY_H
