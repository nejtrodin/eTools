#ifndef BRDPARSER_H
#define BRDPARSER_H

#include "eboard.h"
#include <QDomDocument>
#include <QString>

class ELibrary;
class EPackage;
class EElement;
class ESignal;
class EPlain;

class BrdParser {
public:
    BrdParser();
    bool parse(QString filePath, ELibrary* library, EBoard* board);

private:
    bool parseLibrary(QDomElement libraryElement, ELibrary* library);
    EPlain parsePlain(QDomElement plainElement);
    EElement parseElement(QDomElement elementElement, ELibrary* library);
    EPackage parsePackage(QDomElement packageElement, QString libraryName);
    ESignal parseSignal(QDomElement signalElement);

    Via parseVia(QDomElement viaElement, bool* ok);
};

#endif // BRDPARSER_H
