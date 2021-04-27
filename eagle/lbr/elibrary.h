#ifndef ELIBRARY_H
#define ELIBRARY_H

#include "../common/ecommon.h"
#include "../epackage.h"
#include "edeviceset.h"
#include "esymbol.h"

class ELibrary : public ECoreElement
{
public:
    ELibrary() { }
    void setDomElement(QDomElement rootElement) override;
    QString name() { return mLibraryName; }
    QString urn() { return mUrn; }
    bool isEmpty() { return emptyFlag; }
    EDeviceset getDeviceset(QString devicesetName);
    ESymbol getSymbol(QString symbolName);
    //    EPackage getpackage(QString library, QString package);

private:
    bool emptyFlag = true;
    QString mLibraryName;
    QString mUrn;
    QMap<QString, EDeviceset> mDevicesets;
    QVector<EPackage> mPackages;
    QMap<QString, ESymbol> mSymbols;
};

#endif // ELIBRARY_H
