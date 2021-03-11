#include "eschnet.h"
#include "../eparser.h"

void ESchNet::setDomElement(QDomElement rootElement)
{
    mElement = rootElement;
    mValidFlag = false;
    mSegments.clear();

    if (!mElement.isNull() /*&& mElement.tagName() == "net"*/) {
        mValidFlag = true;
        mName = mElement.attribute("name");

        QDomElement segmentElement = mElement.firstChildElement("segment");
        while (!segmentElement.isNull()) {
            ESegment segment;
            segment.setDomElement(segmentElement);
            if (!segment.isValid())
                mValidFlag = false;
            mSegments.append(segment);

            segmentElement = segmentElement.nextSiblingElement("segment");
        }
    }

    if (!mValidFlag)
        qDebug() << "Parse error. Line:" << mElement.lineNumber();
}

void ESchNet::paint(QPainter *painter, SchSettings *settings)
{
    QVector<ESegment>::iterator iSegment;
    for (iSegment = mSegments.begin(); iSegment != mSegments.end(); ++iSegment) {
        iSegment->paint(painter, mName, settings);
    }
}
