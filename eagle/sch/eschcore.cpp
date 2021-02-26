#include "eschcore.h"

void ESchCore::clear()
{
    mLibraries.clear();
    mParts.clear();
}

void ESchCore::appendLibrary(ELibrary library)
{
    mLibraries.insert(library.name(), library);
}

ELibrary ESchCore::getLibrary(QString libraryName)
{
    if (mLibraries.contains(libraryName))
        return mLibraries[libraryName];
    else
        return ELibrary();
}

void ESchCore::appendPart(ESchPart part)
{
    mParts.insert(part.name(), part);
}

ESchPart ESchCore::getPart(QString partName)
{
    if (mParts.contains(partName))
        return mParts[partName];
    else
        return ESchPart();
}

QVector<ESchPart> ESchCore::getParts()
{
    auto parts = mParts.values();
    return parts.toVector();
}
