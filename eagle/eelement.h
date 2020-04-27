#ifndef EELEMENT_H
#define EELEMENT_H

#include "epackage.h"
#include <QtCore>

class EElement {
public:
    EElement(); // !!!
    EElement(QString name, EPackage package, qreal xPos, qreal yPos, qreal angle = 0,
        bool mirror = false);
    const QPointF position() { return m_position; }
    const EPackage package() { return m_package; }

private:
    QString m_name;
    QPointF m_position;
    bool m_mirror;
    qreal m_angle;
    EPackage m_package;
};

#endif // EELEMENT_H
