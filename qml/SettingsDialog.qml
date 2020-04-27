import QtQuick 2.4
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.2

Popup {
    id: settingsDialog
    visible: false
    width: 600
    modal: true
    focus: true
    parent: Overlay.overlay
    x: Math.round((parent.width - width) / 2)
    y: Math.round((parent.height - height) / 2)
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    signal settingsChanged()

    property alias projectPath: settingsDialog.projectPath
    property string projectPath: ""

    contentItem: ColumnLayout {
        Frame {
            Layout.fillWidth: true
            Layout.margins: 5
            Material.elevation: 6
            Label {
                anchors.centerIn: parent
                text: qsTr("Settings")
            }
        }

        RowLayout {
            Layout.margins: 5
            Label {
                text: qsTr("Projects: ")
            }
            TextField {
                Layout.fillWidth: true
                text: projectPath
                onTextChanged: projectPath = text
            }
        }

        Row {
            Layout.margins: 5
            Layout.alignment: Qt.AlignHCenter
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
