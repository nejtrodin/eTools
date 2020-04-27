#include "drillreporter.h"

#include <QUrl>

#include "eagle/brdparser.h"
#include "eagle/ecommon.h"
#include "eagle/eelement.h"
#include "eagle/elibrary.h"
#include "eagle/esignal.h"

bool compare(double value1, double value2, quint8 precision)
{
    return std::abs(value1 - value2) < std::pow(10, -precision);
}

DrillReporter::DrillReporter(QObject* parent)
    : QObject(parent)
{
}

QVector<DrillEntry> DrillReporter::getDrillTable(EBoard board)
{
    drillTable.clear();

    EElement element;
    foreach (element, board.getElements()) {
        QVector<Pad> pads = element.package().getPads();
        QVector<Pad>::const_iterator padIterator;
        for (padIterator = pads.begin(); padIterator != pads.end(); ++padIterator)
            appendDrill(padIterator->getDrill(), padIterator->getTopDiameter(), true,
                padIterator->getPosition());

        QVector<Hole> holes = element.package().getHoles();
        QVector<Hole>::const_iterator holeIterator;
        for (holeIterator = holes.begin(); holeIterator != holes.end(); ++holeIterator)
            appendDrill(holeIterator->drill, 0, false, holeIterator->pos);
    }

    ESignal eSignal;
    foreach (eSignal, board.getSignals()) {
        QVector<Via> vias = eSignal.getVias();
        QVector<Via>::const_iterator viaIterator;
        for (viaIterator = vias.begin(); viaIterator != vias.end(); ++viaIterator)
            appendDrill(viaIterator->getDrill(), viaIterator->getOuterDiameter(), true,
                viaIterator->getPosition());
    }

    EPlain ePlain = board.getPlain();
    QVector<Hole> holes = ePlain.getHoles();
    QVector<Hole>::const_iterator holeIterator;
    for (holeIterator = holes.begin(); holeIterator != holes.end(); ++holeIterator)
        appendDrill(holeIterator->drill, 0, false, holeIterator->pos);

    return drillTable;
}

void DrillReporter::getReport(QString schFilePath)
{
    EBoard board;
    ELibrary library;
    BrdParser parser;

    QString report;

    bool parseResult = parser.parse(schFilePath, &library, &board);
    if (parseResult) {
        DrillReporter drillReporter;
        QVector<DrillEntry> table = drillReporter.getDrillTable(board);

        report = "<style type=\"text/css\">"
                 "table, th, td { border: 1px solid black; border-collapse: collapse;}"
                 "</style>"
                 "<div><center><table border='1' cellpadding='5' align='center'>"
                 "<tr><th>Диам. отв. мм</th><th>Размер конт. площадки</th><th>Наличие металлизации</th><th>Кол.</th></tr>";

        DrillEntry row;
        foreach (row, table) {
            QString rowString = "<tr>"
                                "<td align=\"center\">%1</td>"
                                "<td align=\"center\">%2</td>"
                                "<td align=\"center\">%3</td>"
                                "<td align=\"center\">%4</td>"
                                "</tr>";
            rowString = rowString.arg(row.hole);
            if (row.border > 0)
                rowString = rowString.arg(row.border);
            else
                rowString = rowString.arg("-");
            rowString = rowString.arg(row.plate ? "Да" : "Нет");
            rowString = rowString.arg(row.count);
            report.append(rowString);
        }

        report.append("</table></center></div>");
    } else {
        report = QString("Can't parse file: %1").arg(schFilePath);
    }

    emit signalReport(report);
}

void DrillReporter::appendDrill(double hole, double border, bool plate, QPointF position)
{
    DrillEntry row;
    bool findRowFlag = false;
    QVector<DrillEntry>::iterator i;
    for (i = drillTable.begin(); i != drillTable.end(); ++i) {
        if (compare(i->hole, hole, 3) && compare(i->border, border, 3) && i->plate == plate) {
            findRowFlag = true;
            i->count++;
            i->positions.append(position);
            break;
        }
    }

    if (!findRowFlag) {
        row.hole = hole;
        row.border = border;
        row.plate = plate;
        row.count = 1;
        row.positions.append(position);
        drillTable.append(row);
    }
}
