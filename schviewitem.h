#ifndef SCHVIEWITEM_H
#define SCHVIEWITEM_H

#include <QtQuick/QQuickPaintedItem>
#include <QtQuick/QQuickItem>
#include <QTouchEvent>

#include "eagle/sch/eschematic.h"
#include "schSettings.h"

class SchViewItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QStringList sheetList READ sheetList NOTIFY sheetListChanged)

public:
    SchViewItem(QQuickItem *parent = nullptr);
    Q_INVOKABLE bool openFile(QString path);
    void paint(QPainter *painter) override;
    QStringList sheetList() const;
    Q_INVOKABLE void selectSheet(int sheetNumber);

signals:
    void sheetListChanged();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void touchEvent(QTouchEvent *touchEvent) override;

private:
    typedef struct {
        QPoint offset;
        qreal scale;
    } ViewSettings;

    bool mEmptyFlag;
    ESchematic *mpESchematic;
    SchSettings mSettings;

    QPoint mPrevMousePoint; // for moveEvent
    QStringList mSheetList;
    QVector<ViewSettings> mViewSettings;
    int mCurrentSheet;
};

#endif // SCHVIEWITEM_H
