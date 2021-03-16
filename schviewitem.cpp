#include "schviewitem.h"

#include <QPainter>
#include <QFontDatabase>
#include "schSettings.h"

SchViewItem::SchViewItem(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    mpESchematic = new ESchematic;
    mEmptyFlag = true;

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

        mViewSettings.clear();
        for (int i = 0; i < mSheetList.size(); ++i)
            mViewSettings.append(ViewSettings { .offset = QPoint(0, 0), .scale = 1 });
    } else {
        mEmptyFlag = true;
        mSheetList.clear();
    }

    mCurrentSheet = 0;
    mSettings.setScale(1);
    emit sheetListChanged();

    return ok;
}

void SchViewItem::paint(QPainter *painter)
{
    if (!mEmptyFlag) {
        QPen mainPen(QColor::fromRgb(141, 141, 141), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter->setPen(mainPen);
        painter->translate(mViewSettings.at(mCurrentSheet).offset + QPoint(0, height()));

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
    mSettings.setScale(mViewSettings.at(mCurrentSheet).scale);
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

    mViewSettings[mCurrentSheet].offset += offsetPos;
    update();
}

void SchViewItem::wheelEvent(QWheelEvent *event)
{
    auto y = event->angleDelta().y();
    QPointF eventPosition = event->position();
    auto oldScale = mViewSettings.at(mCurrentSheet).scale;
    auto scale = oldScale;

    if (y > 0) {
        scale *= 1.2;
    } else if (y < 0 && scale > 1) {
        scale /= 1.2;
    }

    qreal offsetX = eventPosition.x()
            - (-mViewSettings.at(mCurrentSheet).offset.x() + eventPosition.x()) * scale / oldScale;
    mViewSettings[mCurrentSheet].offset.rx() = static_cast<int>(offsetX);
    qreal offsetY = eventPosition.y() - height()
            - (eventPosition.y() - mViewSettings.at(mCurrentSheet).offset.y() - height()) * scale / oldScale;
    mViewSettings[mCurrentSheet].offset.ry() = static_cast<int>(offsetY);

    mViewSettings[mCurrentSheet].scale = scale;
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
            mViewSettings[mCurrentSheet].offset += offsetPos;
            update();
        } break;
        default:
            break;
        }
    }
}
