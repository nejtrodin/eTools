#ifndef EPARSER_H
#define EPARSER_H

#include <QDomDocument>

#include "common/ecommon.h"
#include "epackage.h"

class EParser
{
public:
    EParser();
    static EPackage parsePackage(QDomElement packageElement, QString libraryName, bool *ok = nullptr);
};

#endif // EPARSER_H
