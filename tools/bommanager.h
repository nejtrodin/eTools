#ifndef BOMMANAGER_H
#define BOMMANAGER_H

#include <QtCore>
#include "eagle/sch/eschematic.h"

class BomManager : public QObject
{
public:
    struct BomEntry
    {
        QString positionPrefix;
        int position;
        QString name;
        QString specification;
        QString note;
    };

    enum SortType { SortByPosition, SortByName };

    BomManager(QObject *parent = nullptr);
    void setSchematic(ESchematic *schematic);
    QList<BomEntry> getBomSortedByPosition();

private:
    ESchematic *schematic;
    QList<BomEntry> bomList;

    void createBomFromSchematic();
    QString formatString(const QString &input);
};

#endif // BOMMANAGER_H
