#ifndef EELEMENT_H
#define EELEMENT_H

#include "../ecommon.h"
#include "../lbr/epackage.h"
#include <QtCore>
#include <QPainter>

class EElement : public ECoreElement {
public:
    EElement() { }
    void setDomElement(QDomElement rootElement) override;
    const QPointF position() { return m_position; }

    const QString &libraryName() const;
    void setLibraryName(const QString &newLibraryName);

    const QString &packageName() const;
    void setPackageName(const QString &newPackageName);

private:
    QString m_name;
    QPointF m_position;
    bool m_mirror;
    qreal m_angle;

    QString m_libraryName;
    QString m_packageName;
};

#endif // EELEMENT_H
