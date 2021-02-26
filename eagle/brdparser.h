#ifndef BRDPARSER_H
#define BRDPARSER_H

#include "eboard.h"
#include "eparser.h"
#include "brd/ebrdvia.h"
#include <QDomDocument>
#include <QString>

class ELibrary;
class EPackage;
class EElement;
class ESignal;
class EBrdPlain;

class BrdParser : EParser {
public:
    BrdParser();
    bool parse(QString filePath, ELibrary* library, EBoard* board);

private:
    EBrdPlain parsePlain(QDomElement plainElement);
//    EElement parseElement(QDomElement elementElement, ELibrary* library);
    ESignal parseSignal(QDomElement signalElement);

    EBrdVia parseVia(QDomElement viaElement, bool* ok);
};

#endif // BRDPARSER_H
