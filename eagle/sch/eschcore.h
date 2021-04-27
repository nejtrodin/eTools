#ifndef ESCHCORE_H
#define ESCHCORE_H

#include "../lbr/elibrary.h"
#include "eschpart.h"

/**
 * @brief The ESchCore class contains an internal structure of sch file
 */
class ESchCore
{
public:
    ESchCore() { }
    void clear();
    void appendLibrary(ELibrary library);
    ELibrary getLibrary(QString name, QString urn);
    void appendPart(ESchPart part);
    ESchPart getPart(QString partName);
    QVector<ESchPart> getParts();

private:
    QMultiMap<QString, ELibrary> mLibraries;
    QMap<QString, ESchPart> mParts; // key: part name
};

#endif // ESCHCORE_H
