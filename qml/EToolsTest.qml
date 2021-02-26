import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0
//import QtQuick.Dialogs 1.2

import ETools 1.0


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("eagleTools")
    property string theme: "light"

    Settings {
        category: "MainWindow"
        property alias x: mainWindow.x
        property alias y: mainWindow.y
        property alias width: mainWindow.width
        property alias height: mainWindow.height
        property alias theme: mainWindow.theme
    }

    Settings {
        id: generalSettings
        category: "General"
        property string projectPath: ""
    }

    SettingsDialog {
        id: settingsDialog
        onSettingsChanged: {
            generalSettings.projectPath = settingsDialog.projectPath
            fileManager.setProjectPaths(settingsDialog.projectPath)
        }
    }

    Component.onCompleted: schViewItem.openFile("/home/worker/workspace/eagle/work_projects/111/RELAY_SW/RELAY_SW.sch")

    SchViewItem {
        id: schViewItem
        anchors.fill: parent
    }

}
