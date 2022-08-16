#include "eschnet.h"

void ESchNet::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;
    m_segments.clear();

    // TODO: have bug with "bus". Create bus class.
    if (!m_domElement.isNull() /*&& m_domElement.tagName() == "net"*/) {
        m_validFlag = true;
        m_name = m_domElement.attribute("name");

        QDomElement segmentElement = m_domElement.firstChildElement("segment");
        while (!segmentElement.isNull()) {
            ESegment segment;
            segment.setDomElement(segmentElement);
            if (!segment.isValid())
                m_validFlag = false;
            m_segments.append(segment);

            segmentElement = segmentElement.nextSiblingElement("segment");
        }
    }

    if (!m_validFlag) {
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
    }
}

void ESchNet::paint(QPainter *painter, SchSettings *settings)
{
    QVector<ESegment>::iterator iSegment;
    for (iSegment = m_segments.begin(); iSegment != m_segments.end(); ++iSegment) {
        iSegment->paint(painter, m_name, settings);
    }
}
