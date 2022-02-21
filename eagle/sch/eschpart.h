#ifndef ESCHPART_H
#define ESCHPART_H

#include "../ecommon.h"
#include "../evalueattribute.h"
#include "schSettings.h"

class ESchPart : public ECoreElement
{
public:
    ESchPart() { }
    void setDomElement(QDomElement rootElement) override;
    QString name() { return m_name; }
    QString library() { return m_library; }
    QString libraryUrn() { return m_libraryUrn; }
    QString deviceset() { return m_devicesetName; }
    QString device() { return m_deviceName; }
    QString value() { return m_value; }
    QString technology() { return m_technology; }
    QString getAttribute(QString attributeName);
    QList<EValueAttribute> getAttributes() { return m_valueAttributes.values(); }

private:
    QString m_name;
    QString m_library;
    QString m_libraryUrn;
    QString m_devicesetName;
    QString m_deviceName;
    QString m_value;
    QString m_technology;
    QMap<QString, EValueAttribute> m_valueAttributes;
};

#endif // ESCHPART_H
