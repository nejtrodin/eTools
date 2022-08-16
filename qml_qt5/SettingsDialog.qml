import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15


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
                GroupBox {
                    id: pinGroupBox
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Image {
                        id: pinImage
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/images/pin_sizes.svg"
                    }
                    Grid {
                        anchors.top: parent.top
                        anchors.left: pinImage.right
                        columns: 2

                        Label {
                            text: qsTr("Pin text size:")
                            verticalAlignment: Text.AlignVCenter
                        }
                        SpinBox {
                            id: pinTextSizeSpinBox
                            from: 100
                            to: 1000
                            stepSize: 10
                            editable: true

                            property real realValue: value / 100

                            validator: DoubleValidator {
                                bottom: Math.min(pinTextSizeSpinBox.from,
                                                 pinTextSizeSpinBox.to)
                                top: Math.max(pinTextSizeSpinBox.from,
                                              pinTextSizeSpinBox.to)
                            }

                            textFromValue: function (value, locale) {
                                return Number(value / 100).toLocaleString(
                                            locale, 'f', 2)
                            }

                            valueFromText: function (text, locale) {
                                return Number.fromLocaleString(locale,
                                                               text) * 100
                            }
                        }
                    }
                }
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
