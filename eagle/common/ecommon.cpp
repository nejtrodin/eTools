#include "ecommon.h"

Hole::Hole(double x, double y, double drill)
{
    this->pos = QPointF(x, y);
    this->drill = drill;
}

EAlign ECommon::parseAlignAttribute(QString value)
{
    EAlign result = AlignBottomLeft;
    if (value == "bottom-left")
        result = AlignBottomLeft;
    else if (value == "bottom-center")
        result = AlignBottomCenter;
    else if (value == "bottom-right")
        result = AlignBottomRight;
    else if (value == "center-left")
        result = AlignCenterLeft;
    else if (value == "center")
        result = AlignCenter;
    else if (value == "center-right")
        result = AlignCenterRight;
    else if (value == "top-left")
        result = AlignTopLeft;
    else if (value == "top-center")
        result = AlignTopCenter;
    else if (value == "top-right")
        result = AlignTopRight;

    return result;
}

bool ECommon::parseRotAttribute(QString value, int *angle, bool *mirror)
{
    if (value.isEmpty()) {
        *angle = 0;
        *mirror = false;
        return true;
    }

    if (value.size() > 0 && value.at(0) == 'M') {
        *mirror = true;
        value.remove(0, 1);
    } else {
        *mirror = false;
    }

    bool ok = false;
    if (value.size() > 1 && value.at(0) == 'R') {
        value.remove(0, 1);
        *angle = value.toInt(&ok);
    }
    return ok;
}

EAlign ECommon::mirrorAlign(EAlign align, qreal angle)
{
    if (angle <= 45 || (angle > 135 && angle <= 225) || angle > 315) {
        if (align == AlignBottomLeft)
            return AlignBottomRight;
        else if (align == AlignBottomRight)
            return AlignBottomLeft;
        else if (align == AlignCenterLeft)
            return AlignCenterRight;
        else if (align == AlignCenterRight)
            return AlignCenterLeft;
        else if (align == AlignTopLeft)
            return AlignTopRight;
        else if (align == AlignTopRight)
            return AlignTopLeft;
        else
            return align;
    } else {
        if (align == AlignBottomLeft)
            return AlignTopLeft;
        else if (align == AlignBottomCenter)
            return AlignTopCenter;
        else if (align == AlignBottomRight)
            return AlignTopRight;
        else if (align == AlignTopLeft)
            return AlignBottomLeft;
        else if (align == AlignTopCenter)
            return AlignBottomCenter;
        else if (align == AlignTopRight)
            return AlignBottomRight;
        else
            return align;
    }
}

QPointF ECommon::getDrawPosition(qreal height, qreal width, EAlign align)
{
    qreal dx = 0, dy = 0;
    switch (align) {
    case AlignBottomLeft:
        break;
    case AlignBottomCenter:
        dx = -width / 2;
        break;
    case AlignBottomRight:
        dx = -width;
        break;
    case AlignCenterLeft:
        dy += height / 2;
        break;
    case AlignCenter:
        dx = -width / 2;
        dy += height / 2;
        break;
    case AlignCenterRight:
        dx = -width;
        dy += height / 2;
        break;
    case AlignTopLeft:
        dy += height;
        break;
    case AlignTopCenter:
        dx = -width / 2;
        dy += height;
        break;
    case AlignTopRight:
        dx = -width;
        dy += height;
        break;
    }

    return QPointF(dx, dy);
}

double ECommon::textSizeToMilimeters(QString text, bool *ok)
{
    double result = 0;

    if (text.right(2) == "mm") {
        result = text.leftRef(text.size() - 2).toDouble(ok);
    } else if (text.right(3) == "mil") {
        result = 0.0254 * text.leftRef(text.size() - 3).toDouble(ok);
    } else {
        *ok = false;
    }

    return result;
}

QPointF ECommon::rotatePoint(const QPointF &point, const qreal &angle)
{
    qreal _angle = angle * 3.141592653589793 / 180.0;
    qreal x = point.x() * cos(_angle) - point.y() * sin(_angle);
    qreal y = point.x() * sin(_angle) + point.y() * cos(_angle);
    return QPointF(x, y);
}
