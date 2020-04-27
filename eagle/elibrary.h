#ifndef ELIBRARY_H
#define ELIBRARY_H

#include "epackage.h"
#include <QVector>
#include <QtCore>

class ELibrary {
public:
    ELibrary();
    void appendPackage(EPackage package);
    EPackage getpackage(QString library, QString package);

private:
    QVector<EPackage> m_packages;
};

#endif // ELIBRARY_H
