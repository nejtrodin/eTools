#ifndef BOMENTRY_H
#define BOMENTRY_H

#include <QtCore>

struct BomEntry
{
    QString prefix;
    int position;
    QString type;
    QString name;
    QString suffix;
    QString specification;
    QString note;
};

#endif // BOMENTRY_H
