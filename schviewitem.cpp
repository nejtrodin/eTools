#include "schviewitem.h"

#include <QPainter>
#include <QFontDatabase>
#include "schSettings.h"

SchViewItem::SchViewItem(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    mpESchematic = new ESchematic;
    mEmptyFlag = true;
    mPaintOffset = QPoint(0, 0);

    mSettings.setScale(2);

    setFillColor(Qt::black);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptTouchEvents(true);
}

bool SchViewItem::openFile(QString path)
{
    bool ok = mpESchematic->openFile(path, &mSettings);
    if (ok) {
        mEmptyFlag = false;
        mSheetList = mpESchematic->sheetList();
    } else {
        mEmptyFlag = true;
        mSheetList.clear();
    }

    mCurrentSheet = 0;
    emit sheetListChanged();

    return ok;
}

void SchViewItem::paint(QPainter *painter)
{
    if (!mEmptyFlag) {
        QPen mainPen(QColor::fromRgb(141, 141, 141), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter->setPen(mainPen);
        painter->translate(mPaintOffset + QPoint(0, height()));

        mpESchematic->paint(painter, &mSettings, mCurrentSheet);
    }
}

QStringList SchViewItem::sheetList() const
{
    return mSheetList;
}

void SchViewItem::selectSheet(int sheetNumber)
{
    mCurrentSheet = sheetNumber;
    update();
}

void SchViewItem::mousePressEvent(QMouseEvent *event)
{
    mPrevMousePoint = event->pos();
}

void SchViewItem::mouseMoveEvent(QMouseEvent *event)
{
    auto curPos = event->pos();
    auto offsetPos = curPos - mPrevMousePoint;
    mPrevMousePoint = curPos;

    mPaintOffset += offsetPos;
    update();
}

void SchViewItem::wheelEvent(QWheelEvent *event)
{
    auto y = event->angleDelta().y();
    QPointF eventPosition = event->position();
    auto oldScale = mSettings.scale();
    auto scale = oldScale;

    if (y > 0) {
        scale *= 1.2;
    } else if (y < 0 && scale > 1) {
        scale /= 1.2;
    }

    qreal offsetX = eventPosition.x()
            - (-mPaintOffset.x() + eventPosition.x()) * scale / oldScale;
    mPaintOffset.rx() = static_cast<int>(offsetX);
    qreal offsetY = eventPosition.y() - height()
            - (eventPosition.y() - mPaintOffset.y() - height()) * scale / oldScale;
    mPaintOffset.ry() = static_cast<int>(offsetY);

    mSettings.setScale(scale);
    update();
}

void SchViewItem::touchEvent(QTouchEvent *touchEvent)
{
    QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();

    if (touchPoints.count() == 1) {
        const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();

        switch (touchEvent->type()) {
        case QTouchEvent::TouchBegin:
            mPrevMousePoint = touchPoint0.pos().toPoint();
            break;
        case QTouchEvent::TouchUpdate: {
            auto curPos = touchPoint0.pos().toPoint();
            auto offsetPos = curPos - mPrevMousePoint;
            mPrevMousePoint = curPos;
            mPaintOffset += offsetPos;
            update();
        } break;
        default:
            break;
        }
    }
}
