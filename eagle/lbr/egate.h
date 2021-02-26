#ifndef EGATE_H
#define EGATE_H

#include <QtCore>

class EGate
{
public:
    EGate() { }
    EGate(const QString &name, const QString &symbolName);
    QString name() { return mName; }
    QString symbol() { return mSymbolName; }

private:
    QString mName;
    QString mSymbolName;
};

#endif // EGATE_H
