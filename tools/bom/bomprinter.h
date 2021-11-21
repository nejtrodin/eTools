#ifndef BOMPRINTER_H
#define BOMPRINTER_H

#include <QtCore>
#include "tools/bom/bomentry.h"


struct ReportLine{
    QString pos;
    QString desc;
    int qty;
    QString comment;
    // hidden
    QString type;
    bool showType;
};

class BomPrinter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString richText READ richText NOTIFY textChanged)

public:
    // Group of elements with identical prefix and type
    struct TypeGroup {
        QString prefix;
        QString type;
        QList<ReportLine> lines;
    };


    BomPrinter(QObject *parent = nullptr);
    Q_INVOKABLE void openFile(QString filePath);
    QString richText() { return m_richText; }

signals:
    void textChanged(const QString &newText);

private:
    QString m_richText;

    QList<TypeGroup> typeGroups;
    TypeGroup group;
    void addEntry(const BomEntry &entry, const bool &showType);
};

#endif // BOMPRINTER_H
