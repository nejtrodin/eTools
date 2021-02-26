import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.0

import ETools 1.0

Item {
    function openFile(path) {
        schViewItem.openFile(path)
    }

    SchViewItem {
        id: schViewItem
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width - 100
    }

    Pane {
        id: sheetsItem
        anchors.left: schViewItem.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        Label {
            id: sheetsItemHeader
            text: qsTr("Sheets")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.bottomMargin: 5
            horizontalAlignment: Text.AlignHCenter
        }



        ListView {
            id: sheetListView
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: sheetsItemHeader.bottom
            anchors.bottom: parent.bottom
            spacing: 2

            model: schViewItem.sheetList

            highlight: Rectangle { color: Qt.tint(Material.background, "lightslategrey") }
            highlightFollowsCurrentItem: true

            delegate: Item {
                id: sheetSelectRect
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 2
                height: textField.paintedHeight

                Label {
                    id: textField
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 2
                    text: modelData
                    elide: Text.ElideRight
                }

                ToolTip {
                     text: modelData
                     delay: 500
                     visible: sheetSelectMouseArea.containsMouse
                 }

                MouseArea {
                    id: sheetSelectMouseArea
                    anchors.fill: parent
                    onClicked: {
                        sheetListView.currentIndex = model.index
                        schViewItem.selectSheet(model.index)
                    }

                    hoverEnabled: true
                }
            }
        }

    }
}
