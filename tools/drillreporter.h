#ifndef DRILLREPORTER_H
#define DRILLREPORTER_H

#include "eagle/eboard.h"
#include <QtCore>

struct DrillEntry
{
    double hole;
    double border;
    bool plate;
    int count;
    QVector<QPointF> positions;
};

class DrillReporter : public QObject
{
    Q_OBJECT

public:
    DrillReporter(QObject *parent = nullptr);
    QVector<DrillEntry> getDrillTable(EBoard board);

signals:
    void signalReport(QString report);

public slots:
    void getReport(QString brdFilePath);

private:
    QVector<DrillEntry> drillTable;

    void appendDrill(double hole, double border, bool plate, QPointF position);
};

#endif // DRILLREPORTER_H
