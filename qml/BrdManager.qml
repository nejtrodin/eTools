import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.4
import ETools 1.0

Item {
    property string filePath: ""
    property string info: ""

    function setFilePath (path) {
        filePath = path
        drillReporter.getReport(path)
    }

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent

        Frame {
            Layout.fillWidth: true
            Layout.margins: 5

            Label {
                anchors.centerIn: parent
                width: parent.width
                wrapMode: Text.Wrap
                horizontalAlignment: "AlignHCenter"
                text: info
            }
        }

        DrillReport {
            id: drillReportItem
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 5
        }
    }

    DrillReporter {
        id: drillReporter
        onSignalReport: drillReportItem.report = report
    }
}
