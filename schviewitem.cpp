#include "schviewitem.h"

#include <QPainter>
#include <QFontDatabase>
#include "settings.h"

SchViewItem::SchViewItem(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    mpESchematic = new ESchematic;
    mEmptyFlag = true;
    mPaintOffset = QPoint(0, 0);

    int id = QFontDatabase::addApplicationFont(":/fonts/gost_b.ttf");
    QString gost_b = QFontDatabase::applicationFontFamilies(id).at(0);
    mSettings.schFont = QFont(gost_b);

    mSettings.schScale = 2;

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
    auto oldScale = mSettings.schScale;

    if (y > 0) {
        mSettings.schScale *= 1.2;
    } else if (y < 0 && mSettings.schScale > 1) {
        mSettings.schScale /= 1.2;
    }

    qreal offsetX = eventPosition.x()
            - (-mPaintOffset.x() + eventPosition.x()) * mSettings.schScale / oldScale;
    mPaintOffset.rx() = static_cast<int>(offsetX);
    qreal offsetY = eventPosition.y() - height()
            - (eventPosition.y() - mPaintOffset.y() - height()) * mSettings.schScale / oldScale;
    mPaintOffset.ry() = static_cast<int>(offsetY);

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
