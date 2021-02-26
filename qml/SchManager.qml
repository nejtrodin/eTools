import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.4

Item {
    property string filePath: ""
    property string info: ""

    function setFilePath (path) {
        filePath = path
        bomList.setSchematicPath(filePath)
    }

    signal openFile(string path)
    signal exportFile(string path)

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

        Frame {
            Layout.fillWidth: true
            Layout.margins: 5

            GridLayout {
                Button {
                    text: "View"
                    font.capitalization: Font.MixedCase
                    onClicked: openFile(filePath)
                }

                Button {
                    text: "Export to PDF"
                    font.capitalization: Font.MixedCase
                    onClicked: exportFile(filePath)
                }
            }
        }

        BomList {
            id: bomList
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 5
        }

    }
}
