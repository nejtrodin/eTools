#ifndef ESCHPART_H
#define ESCHPART_H

#include "../common/ecommon.h"
#include "../common/evalueattribute.h"
#include "schSettings.h"

class ESchPart : public ECoreElement
{
public:
    ESchPart() { }
    void setDomElement(QDomElement rootElement) override;
    QString name() { return mName; }
    QString library() { return mLibrary; }
    QString libraryUrn() { return mLibraryUrn; }
    QString deviceset() { return mDevicesetName; }
    QString device() { return mDeviceName; }
    QString value() { return mValue; }
    QString technology() { return mTechnology; }
    QString getAttribute(QString attributeName);
    QList<EValueAttribute> getAttributes() { return mValueAttributes.values(); }

private:
    QString mName;
    QString mLibrary;
    QString mLibraryUrn;
    QString mDevicesetName;
    QString mDeviceName;
    QString mValue;
    QString mTechnology;
    QMap<QString, EValueAttribute> mValueAttributes;
};

#endif // ESCHPART_H
