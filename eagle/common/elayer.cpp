#include "elayer.h"


void ELayer::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;

    if (!mElement.isNull() && mElement.tagName() == "layer") {
        mValidFlag = true;

        bool ok = false;

        int number = mElement.attribute("number").toInt(&ok);
        if (ok)
            mLayer.number = number;
        else
            mValidFlag = false;


        QString name = mElement.attribute("name");
        if (name.isEmpty())
            mValidFlag = false;
        else
            mLayer.name = name;

        int color = mElement.attribute("color").toInt(&ok);
        if (ok)
            mLayer.colorNumber = color;
        else
            mValidFlag = false;

        int fill = mElement.attribute("fill").toInt(&ok);
        if (ok)
            mLayer.fill = fill;
        else
            mValidFlag = false;

        QString visibleSt = mElement.attribute("visible");
        if (visibleSt == "yes")
            mLayer.visible = true;
        else if (visibleSt == "no")
            mLayer.visible = false;
        else
            mValidFlag = false;

        QString activeSt = mElement.attribute("active");
        if (activeSt == "yes")
            mLayer.active = true;
        else if (activeSt == "no")
            mLayer.active = false;
        else
            mValidFlag = false;
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}
