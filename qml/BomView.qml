import QtQuick 2.0
import QtQuick.Controls.Material 2.0
import Qt.labs.platform as Platform
import ETools 1.0

Item {
    function openFile(path) {
        bomPrinter.openFile(path)
    }

    BomPrinter {
        id: bomPrinter
    }

    property int selectStart
    property int selectEnd
    property int curPos

    Flickable {
        id: bomTextFlickable
        flickableDirection: Flickable.VerticalFlick
        anchors.fill: parent

        TextArea.flickable: TextArea {
            id: bomTextArea
            textFormat: Text.RichText
            readOnly: true
            selectByMouse: true
            padding: 6
            background: null
            text: bomPrinter.richText

            MouseArea {
                acceptedButtons: Qt.RightButton
                anchors.fill: parent
                onClicked: contextMenu.open()
            }
        }
    }

    Platform.Menu {
        id: contextMenu

        Platform.MenuItem {
            text: qsTr("Copy")
            enabled: bomTextArea.selectedText
            onTriggered: bomTextArea.copy()
        }
    }
}
