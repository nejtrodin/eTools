#ifndef EDEVICE_H
#define EDEVICE_H

#include "../ecommon.h"
#include "etechnology.h"
#include <QtCore>

class EDevice : public ECoreElement
{
public:
    EDevice() { }
    void setDomElement(QDomElement rootElement) override;
    QString name() const { return mName; }
    QString packageName() const { return mPackageName; }
    QList<EConnect> getConnects(QString gateName);
    QList<EValueAttribute> getAttributes(QString technologyName);
    QString getAttribute(QString technologyName, QString attributeName);

private:
    QString mName;
    QString mPackageName;
    QMultiMap<QString, EConnect> mConnects; // key: gate
    QMap<QString, ETechnology> mTechnologies;
};

#endif // EDEVICE_H
