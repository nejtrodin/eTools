#ifndef BOMPARSER_H
#define BOMPARSER_H

#include <QtCore>
#include "eagle/sch/eschematic.h"
#include "tools/bom/bomentry.h"

class BomParser : public QObject
{
    Q_OBJECT

public:
    BomParser(QObject *parent = nullptr);
    void setSchematic(ESchematic *schematic);
    QList<BomEntry> getBomSortedByPosition();

private:
    ESchematic *schematic;
    QList<BomEntry> bomList;

    void createBomFromSchematic();
    QString formatString(const QString &input);
};

#endif // BOMPARSER_H
