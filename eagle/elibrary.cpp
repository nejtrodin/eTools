#include "elibrary.h"

ELibrary::ELibrary()
{
}

void ELibrary::appendPackage(EPackage package)
{
    m_packages.append(package);
}

EPackage ELibrary::getpackage(QString library, QString package)
{
    for (int i = 0; i < m_packages.size(); i++) {
        if (m_packages.at(i).libraryName() == library && m_packages.at(i).name() == package)
            return m_packages[i];
    }

    return EPackage();
}
