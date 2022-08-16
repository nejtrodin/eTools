import QtQuick 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1
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

    Menu {
        id: contextMenu

        MenuItem {
            text: qsTr("Copy")
            enabled: bomTextArea.selectedText
            onTriggered: bomTextArea.copy()
        }
    }
}
