#ifndef ETECHNOLOGY_H
#define ETECHNOLOGY_H

#include "../ecommon.h"
#include "../evalueattribute.h"

class ETechnology : public ECoreElement
{
public:
    ETechnology() { }
    void setDomElement(QDomElement rootElement) override;
    QString name() { return mName; }
    QString getAttribute(QString attributeName);
    QList<EValueAttribute> getAttributes() { return mValueAttributes.values(); }

private:
    QString mName;
    QMap<QString, EValueAttribute> mValueAttributes;
};

#endif // ETECHNOLOGY_H
