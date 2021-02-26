#ifndef ESCHEMATIC_H
#define ESCHEMATIC_H

#include "../common/ecommon.h"
#include "../lbr/elibrary.h"
#include "eschcore.h"
#include "eschpart.h"
#include "eschsheet.h"
#include "settings.h"
#include <QDomDocument>

class ESchematic
{
public:
    ESchematic() { }
    bool openFile(QString filePath);
    void paint(QPainter *painter, Settings *settings, int sheetNumber = 0);
    ESchCore getSchCore() { return mSchCore; }
    QStringList sheetList();

private:
    QString mPath;
    QVector<ESchSheet> mSheets;
    ESchCore mSchCore;

    QDomDocument mSchDoc;
};

#endif // ESCHEMATIC_H
