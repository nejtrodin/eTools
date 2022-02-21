#include "elibrary.h"

void ELibrary::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = true;

    mDevicesets.clear();
    mPackages.clear();
    mSymbols.clear();

    if (!m_domElement.isNull() && m_domElement.tagName() == "library") {
        mLibraryName = m_domElement.attribute("name");
        mUrn = m_domElement.attribute("urn");
        emptyFlag = false;

        // packages
        QDomElement packagesElement = m_domElement.firstChildElement("packages");
        if (!packagesElement.isNull()) {
            QDomElement packageElement = packagesElement.firstChildElement("package");
            while (!packageElement.isNull()) {
                EPackage package;
                package.setDomElement(packageElement);
                mPackages.insert(package.name(), package);

                packageElement = packageElement.nextSiblingElement("package");
            }
        }

        // symbols
        QDomElement symbolsElement = m_domElement.firstChildElement("symbols");
        if (!symbolsElement.isNull()) {
            QDomElement symbolElement = symbolsElement.firstChildElement("symbol");
            while (!symbolElement.isNull()) {
                ESymbol symbol;
                symbol.setDomElement(symbolElement);
                if (!symbol.isValid()) {
                    m_validFlag = false;
                }
                mSymbols.insert(symbol.name(), symbol);

                symbolElement = symbolElement.nextSiblingElement("symbol");
            }
        }

        // devicesets
        QDomElement devicesetsElement = m_domElement.firstChildElement("devicesets");
        if (!devicesetsElement.isNull()) {
            QDomElement devicesetElement = devicesetsElement.firstChildElement("deviceset");
            while (!devicesetElement.isNull()) {
                EDeviceset deviceset;
                deviceset.setDomElement(devicesetElement);
                if (!deviceset.isValid())
                    m_validFlag = false;
                mDevicesets.insert(deviceset.name(), deviceset);

                devicesetElement = devicesetElement.nextSiblingElement("deviceset");
            }
        }
    }

    if (!m_validFlag) {
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
    }
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

EPackage ELibrary::getPackage(QString package)
{
    if(mPackages.contains(package)) {
        return mPackages.value(package);
    }
    else {
        return EPackage();
    }
}
