import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.qmlmodels 1.0
import ETools 1.0

Item {
    property int sheetNumber: 5

    function exportFile(path) {
        schExport.openFile(path)
        outFilePath.text = path.slice(0, path.lastIndexOf('.')) + ".pdf"
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 5
        columns: 1

        // file name
        Frame {
            Layout.fillWidth: true
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
                    font.capitalization: Font.MixedCase
                }

            }
        }

        // sheets settings
        Frame {
            id: sheetSettingsFrame
//            Layout.fillWidth: true
            Layout.fillHeight: true
            implicitWidth: 300
            implicitHeight: 400
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

                    delegate:
                    Frame {
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
                                CheckBox {
                                    text: qsTr("Print")
                                    checked: used
                                    onCheckedChanged: used = checked
                                }
                            }
                        }

                        Component.onCompleted: sheetSettingsFrame.implicitWidth = width
                                               + sheetSettingsFrame.padding * 2
                    }
                }  // ListView
            }
        }  // sheet settings

        Button {
            Layout.fillWidth: true
            text: qsTr("Export")
            font.capitalization: Font.MixedCase
            onClicked: schExport.exportToPdf(outFilePath.text)
        }
    }

    SchExport {
        id: schExport
    }
}
