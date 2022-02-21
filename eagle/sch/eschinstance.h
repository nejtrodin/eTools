#ifndef ESCHINSTANCE_H
#define ESCHINSTANCE_H

#include "../eattribute.h"
#include "eschcore.h"
#include "schSettings.h"
#include <QPicture>

class ESchInstance : public ECoreElement
{
public:
    ESchInstance() { }
    void setDomElement(QDomElement rootElement) override;
    void paint(QPainter *painter, SchSettings *settings, ESchCore *schCore);

private:
    QString m_partName;
    QString m_gate;
    qreal m_x = 0;
    qreal m_y = 0;
    bool m_smashed = false;
    bool m_mirrorFlag = false;
    int m_angle = 0;

    QPicture m_instancePicture;
    QVector<EAttribute> m_attributes;
};

#endif // ESCHINSTANCE_H
