import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import ETools 1.0

Item {
    property int sheetNumber: 5

    function exportFile(path) {
        schExport.openFile(path)
        outFilePath.text = path.slice(0, path.lastIndexOf('.')) + ".pdf"
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        // file name
        Frame {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            RowLayout {
                anchors.fill: parent
                spacing: 5
                Label {
                    text: qsTr("Output file:")
                    Layout.alignment: Qt.AlignVCenter
                }
                TextField {
                    id: outFilePath
                    Layout.fillWidth: true
                    selectByMouse: true
                }
                Button {
                    text: qsTr("Select")
                    onClicked: {
                        if (Qt.platform.os == "linux")
                            outFilePath.text = schExport.selectOutputFile(outFilePath.text)
                        else
                            fileDialog.open()
                    }
                }

                Button {
                    text: qsTr("Export")
                    font.capitalization: Font.MixedCase
                    onClicked: schExport.exportToPdf(outFilePath.text, colorAsBlackSwitch.checked,
                                                     pageBorderSwitch.checked)
                }
            }
        }

        // All settings
        GridLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            columns: mainWindow.vertical ? 1 : 3

            // sheets settings
            Frame {
                id: sheetSettingsFrame
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter
                implicitWidth: 100
                implicitHeight: 100
                ColumnLayout {
                    anchors.fill: parent
                    spacing: 5
                    Label {
                        text: qsTr("Sheets")
                        Layout.alignment: Qt.AlignHCenter
                    }

                    ListView {
                        id: sheetSettingsTableView
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: 5
                        clip: true

                        model: schExport.getSheetSettingsModel()

                        delegate: Item {
                            width: sheetSettingsTableView.width
                            height: sheetSettingsDelegate.height
                            Frame {
                                anchors.horizontalCenter: parent.horizontalCenter
                                id: sheetSettingsDelegate
                                ColumnLayout {
                                    Label {
                                        id: namelabel
                                        Layout.alignment: Qt.AlignHCenter
                                        text: name
                                    }
                                    RowLayout {
                                        spacing: 5
                                        ComboBox {
                                            id: sizeComboBox
                                            model: sizeList
                                            currentIndex: sizeIdx
                                            onCurrentIndexChanged: sizeIdx = currentIndex
                                        }
                                        ComboBox {
                                            model: orientationList
                                            currentIndex: orientationIdx
                                            onCurrentIndexChanged: orientationIdx = currentIndex
                                        }
                                        Switch {
                                            text: qsTr("Used")
                                            checked: used
                                            onCheckedChanged: used = checked
                                        }
                                    }
                                }
                            }
                        }
                    }  // ListView
                }
            }  // sheet settings Frame

            LayerManager {
                Layout.fillWidth: true
                Layout.fillHeight: true
                implicitWidth: 100
                implicitHeight: 100

                layoutModel: schExport.getLayerListModel()
            }

            Frame {
                Layout.alignment: Qt.AlignTop
                ColumnLayout {
                    Label {
                        text: qsTr("Settings")
                        Layout.alignment: Qt.AlignHCenter
                    }
                    Switch {
                        id: colorAsBlackSwitch
                        text: qsTr("All colors as black")
                        checked: true
                    }
                    Switch {
                        id: pageBorderSwitch
                        text: qsTr("Draw border")
                        checked: true
                    }
                }
            }
        }
    }  // root ColumnLayout

    SchExport {
        id: schExport
    }

    FileDialog {
        id: fileDialog
        title: "Select file"
        currentFile: "file:///" + outFilePath.text.replace(/^.*[\\\/]/, "")
        fileMode: FileDialog.SaveFile
        folder: "file:///" + outFilePath.text.replace(/[\\\/]+[^\\\/]*$/, "")
        nameFilters: ["Pdf files (*.pdf)"]
        onAccepted: outFilePath.text = String(fileDialog.file).replace(/file:\/\/\//, "")
    }
}
