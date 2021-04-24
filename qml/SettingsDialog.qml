import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Controls.Material 6.0
import QtQuick.Layouts 6.0

Popup {
    id: settingsDialog
    visible: false
    width: Math.min(parent.width * 0.8, 600)
    height: parent.height * 0.8
    modal: true
    focus: true
    parent: Overlay.overlay
    x: Math.round((parent.width - width) / 2)
    y: Math.round((parent.height - height) / 2)
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    signal settingsChanged

    property alias projectPathList: projectsFolderList.pathList

    contentItem: Item {
        anchors.fill: parent

        TabBar {
            id: tabBar
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            TabButton {
                text: qsTr("Directories")
                font.capitalization: Font.MixedCase
            }
            TabButton {
                text: qsTr("Schematic")
                font.capitalization: Font.MixedCase
            }
        }

        StackLayout {
            anchors.top: tabBar.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: dialogButtons.top
            currentIndex: tabBar.currentIndex
            Item {
                id: directoriesTab
                GroupBox {
                    title: qsTr("Projects")
                    anchors.fill: parent
                    anchors.margins: 5

                    ScrollView {
                        anchors.fill: parent
                        clip: true
                        contentHeight: projectsFolderList.height

                        FolderList {
                            id: projectsFolderList
                            anchors.left: parent.left
                            anchors.right: parent.right
                        }
                    }
                }
            }
            Item {
                id: schematicTab
            }
        }

        Row {
            id: dialogButtons
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            spacing: 10

            Button {
                text: qsTr("Save")
                onClicked: {
                    settingsChanged()
                    settingsDialog.close()
                }
            }

            Button {
                text: qsTr("Cancel")
                onClicked: settingsDialog.close()
            }
        }
    }
}
