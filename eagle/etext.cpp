#include "etext.h"

void ELabel::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    if (!m_domElement.isNull() && m_domElement.tagName() == "label") {
        bool ok = false;
        m_validFlag = true;

        mX = m_domElement.attribute("x").toDouble(&ok);
        if (!ok) m_validFlag = false;

        mY = m_domElement.attribute("y").toDouble(&ok);
        if (!ok) m_validFlag = false;

        mSize = m_domElement.attribute("size").toDouble(&ok);
        if (!ok) m_validFlag = false;

        mLayer = m_domElement.attribute("layer").toInt(&ok);
        if (!ok) m_validFlag = false;

        ok = ECommon::parseRotAttribute(m_domElement.attribute("rot"), &angle, &mMirror);
        if (!ok) m_validFlag = false;

        mAlign = ECommon::parseAlignAttribute(m_domElement.attribute("align"));
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
}

void ELabel::drawText(QPainter *painter, QPointF position, QString text, qreal size, int angle,
                      EAlign align, int layer, SchSettings *settings)
{
    painter->save();

    painter->setPen(settings->getLayerColor(layer));
    QFont font = settings->font();
    font.setPixelSize(settings->sizeToPx(size) * settings->scale());
    painter->setFont(font);

    painter->translate(position);
    painter->rotate(-angle);

    qreal textHeight = painter->fontMetrics().boundingRect('A').height();
    qreal textWidth = painter->fontMetrics().horizontalAdvance(text);
    painter->drawText(ECommon::getDrawPosition(textHeight, textWidth, align), text);

    painter->restore();
}

DrawingText ELabel::getDrawingText()
{
    DrawingText drawingText(QPointF(), mSize, angle, mAlign, mLayer);
    if (mMirror)
        drawingText.mirror();
    drawingText.move(QPointF(mX, mY));
    return drawingText;
}


void EText::setDomElement(QDomElement rootElement)
{
    m_domElement = rootElement;
    m_validFlag = false;

    if (!m_domElement.isNull() && m_domElement.tagName() == "text") {
        bool ok = false;
        m_validFlag = true;

        mX = m_domElement.attribute("x").toDouble(&ok);
        if (!ok) m_validFlag = false;

        mY = m_domElement.attribute("y").toDouble(&ok);
        if (!ok) m_validFlag = false;

        mSize = m_domElement.attribute("size").toDouble(&ok);
        if (!ok) m_validFlag = false;

        mLayer = m_domElement.attribute("layer").toInt(&ok);
        if (!ok) m_validFlag = false;

        mDistance = m_domElement.attribute("distance", "50").toInt(&ok);
        if (!ok) m_validFlag = false;

        ok = ECommon::parseRotAttribute(m_domElement.attribute("rot"), &angle, &mMirror);
        if (!ok) m_validFlag = false;

        mAlign = ECommon::parseAlignAttribute(m_domElement.attribute("align"));

        mText = m_domElement.text();
    }

    if (!m_validFlag)
        qDebug() << "Parse error. Line:" << m_domElement.lineNumber();
}

DrawingText EText::getDrawingText()
{
    DrawingText drawingText(QPointF(), mSize, angle, mAlign, mLayer, mText, mDistance);
    if (mMirror)
        drawingText.mirror();
    drawingText.move(QPointF(mX, mY));
    return drawingText;
}

