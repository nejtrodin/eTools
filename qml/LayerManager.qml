import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.qmlmodels 1.0
import ETools 1.0

Frame {
    property var layoutModel    

    ColumnLayout {
        anchors.fill: parent
        spacing: 5

        Label {
            text: qsTr("Layers")
            Layout.alignment: Qt.AlignHCenter
        }

        ComboBox {
            id: pressetComboBox
            Layout.fillWidth: true
            model: layoutModel.pressetList
            onCurrentTextChanged: layoutModel.selectPresset(currentText);
        }

        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true

            TableView {
                id: sheetSettingsTableView
                anchors.fill: parent
                implicitWidth: 200
                implicitHeight: 300
                columnSpacing: 5
                rowSpacing: 5
                clip: true

                model: layoutModel

                delegate:
                    DelegateChooser {
                            DelegateChoice {
                                column: 0
                                delegate: Switch {
                                    checked: layerVisible
                                    onCheckedChanged: layerVisible = checked
                                }
                            }
                            DelegateChoice {
                                column: 1
                                delegate: Label {
                                    text: layerNumber
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                            DelegateChoice {
                                column: 2
                                delegate: Item {
                                    implicitWidth: 32
                                    Rectangle {
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        height: 24
                                        width: 24
                                        color: layerColor
                                    }
                                }
                            }
                            DelegateChoice {
                                column: 3
                                delegate: Label {
                                    text: layerName
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                        }
            }  // TableView
        }
    }
}
