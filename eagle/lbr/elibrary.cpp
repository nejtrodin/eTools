#include "elibrary.h"
#include "../eparser.h"

void ELibrary::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = true;

    mDevicesets.clear();
    mPackages.clear();
    mSymbols.clear();

    if (!mElement.isNull() && mElement.tagName() == "library") {
        mLibraryName = mElement.attribute("name");
        mUrn = mElement.attribute("urn");
        emptyFlag = false;

        // packages
        QDomElement packagesElement = mElement.firstChildElement("packages");
        if (!packagesElement.isNull()) {
            QDomElement packageElement = packagesElement.firstChildElement("package");
            while (!packageElement.isNull()) {
                bool _ok;
                auto package = EParser::parsePackage(packageElement, mLibraryName, &_ok);
                if (_ok)
                    mPackages.append(package);
                else
                    mValidFlag = false;
                packageElement = packageElement.nextSiblingElement("package");
            }
        }

        // symbols
        QDomElement symbolsElement = mElement.firstChildElement("symbols");
        if (!symbolsElement.isNull()) {
            QDomElement symbolElement = symbolsElement.firstChildElement("symbol");
            while (!symbolElement.isNull()) {
                ESymbol symbol;
                symbol.setDomElement(symbolElement);
                if (!symbol.isValid())
                    mValidFlag = false;
                mSymbols.insert(symbol.name(), symbol);

                symbolElement = symbolElement.nextSiblingElement("symbol");
            }
        }

        // devicesets
        QDomElement devicesetsElement = mElement.firstChildElement("devicesets");
        if (!devicesetsElement.isNull()) {
            QDomElement devicesetElement = devicesetsElement.firstChildElement("deviceset");
            while (!devicesetElement.isNull()) {
                EDeviceset deviceset;
                deviceset.setDomElement(devicesetElement);
                if (!deviceset.isValid())
                    mValidFlag = false;
                mDevicesets.insert(deviceset.name(), deviceset);

                devicesetElement = devicesetElement.nextSiblingElement("deviceset");
            }
        }
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

EDeviceset ELibrary::getDeviceset(QString devicesetName)
{
    if (mDevicesets.contains(devicesetName)) {
        return mDevicesets[devicesetName];
    } else
        return EDeviceset();
}

ESymbol ELibrary::getSymbol(QString symbolName)
{
    if (mSymbols.contains(symbolName)) {
        return mSymbols[symbolName];
    } else
        return ESymbol();
}
