#ifndef EDEVICESET_H
#define EDEVICESET_H

#include "../ecommon.h"
#include "edevice.h"
#include "egate.h"

class EDeviceset : public ECoreElement
{
public:
    EDeviceset() { }
    void setDomElement(QDomElement rootElement) override;

    QString name() const { return mName; }
    void setName(const QString &name) { this->mName = name; }
    QString getPrefix() const { return mPrefix; }
    void setPrefix(const QString &prefix) { this->mPrefix = prefix; }
    QString getDescription() const { return mDescription; }
    void setDescription(const QString &description) { this->mDescription = description; }
    bool hasUservalue() { return this->mUservalue; }
    void appendDevice(const EDevice &device);
    EDevice getDevice(const QString &deviceName);
    EGate getGate(const QString &gateName);

private:
    QString mName;
    QString mPrefix;
    bool mUservalue;
    QString mDescription;
    QMap<QString, EDevice> mDevices;
    QMap<QString, EGate> mGates;
};

#endif // EDEVICESET_H
