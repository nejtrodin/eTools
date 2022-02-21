#ifndef ELIBRARY_H
#define ELIBRARY_H

#include "../ecommon.h"
#include "epackage.h"
#include "edeviceset.h"
#include "esymbol.h"

class ELibrary : public ECoreElement
{
public:
    ELibrary() { }
    void setDomElement(QDomElement rootElement) override;

    QString name() { return mLibraryName; }
    void setName(const QString &value) {mLibraryName = value;}

    QString urn() { return mUrn; }
    void setUrn(const QString &value) {mUrn = value;}

    bool isEmpty() { return emptyFlag; }
    void setEmpty(const bool value) { emptyFlag = value; }

    EDeviceset getDeviceset(QString devicesetName);
    ESymbol getSymbol(QString symbolName);
    EPackage getPackage(QString package);

private:
    bool emptyFlag = true;
    QString mLibraryName;
    QString mUrn;
    QMap<QString, EDeviceset> mDevicesets;
    QMap<QString, EPackage> mPackages;
    QMap<QString, ESymbol> mSymbols;
};

#endif // ELIBRARY_H
