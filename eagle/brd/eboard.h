#ifndef EBOARD_H
#define EBOARD_H

#include "../ecommon.h"
#include "../lbr/elibrary.h"
#include "ebrdplain.h"
#include "edesignrules.h"
#include "eelement.h"
#include "esignal.h"

class EBoard {
public:
    EBoard() { }
    bool readFile(QString filePath);
    void appendElement(EElement eElement);
    QVector<EElement> getElements() { return eElements; }
    void appendSignal(ESignal eSignal);
    QVector<ESignal> getSignals() { return eSignals; }
    void setPlain(EBrdPlain ePlain);
    EBrdPlain getPlain() { return ePlain; }
    ELibrary getLibrary(QString libraryName);

private:
    QString m_path;

    QMultiMap<QString, ELibrary> m_libraries;
    QVector<EElement> eElements;
    QVector<ESignal> eSignals;
    EBrdPlain ePlain;

    QDomDocument m_boardDoc;
};

#endif // EBOARD_H
