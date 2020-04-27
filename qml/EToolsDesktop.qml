import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0
import QtQuick.Dialogs 1.2

import eFileInfo 1.0


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

    FileDialog {
        id: openFileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        selectMultiple: false
        nameFilters: [ "Eagle files (*.sch *.brd)", "All files (*)" ]
        onAccepted: {
            fileManager.appendFile(openFileDialog.fileUrls[0]);
        }
    }

    function setTheme(theme) {
        if (theme === "light") {
            mainWindow.Material.theme = Material.Light
            openButton.icon.color = Material.foreground
            settingsButton.icon.color = Material.foreground
            themeButton.icon.source = "qrc:///images/open-iconic/svg/moon.svg"
            themeButton.icon.color = Material.foreground
        }
        else if (theme === "dark") {
            mainWindow.Material.theme = Material.Dark
            openButton.icon.color = Material.foreground
            settingsButton.icon.color = Material.foreground
            themeButton.icon.source = "qrc:///images/open-iconic/svg/sun.svg"
            themeButton.icon.color = Material.foreground
        }
    }

    Component.onCompleted: setTheme(mainWindow.theme)

    header: ToolBar {
        contentHeight: settingsButton.implicitHeight
        RowLayout {
            ToolButton {
                id: openButton
                icon.source: "qrc:///images/open-iconic/svg/file.svg"
                visible: true
                hoverEnabled: true
                ToolTip.delay: 500
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Open file")
                onClicked: openFileDialog.open()
            }
            ToolButton {
                id: settingsButton
                icon.source: "qrc:///images/open-iconic/svg/cog.svg"
                visible: true
                hoverEnabled: true
                ToolTip.delay: 500
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Settings")
                onClicked: {
                    settingsDialog.projectPath = generalSettings.projectPath
                    settingsDialog.open()
                }
            }
            ToolButton {
                id: themeButton
                visible: true
                hoverEnabled: true
                ToolTip.delay: 500
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Theme")
                onClicked: {
                    if (mainWindow.theme === "light") {
                        mainWindow.theme = "dark"
                        setTheme("dark")
                    }
                    else if (mainWindow.theme === "dark") {
                        mainWindow.theme = "light"
                        setTheme("light")
                    }
                }
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        FileManager {
            id: fileManager
            Layout.minimumWidth: 100
            Layout.preferredWidth: parent.width * 0.3
            Layout.maximumWidth: 400
            Layout.fillHeight: true

            Component.onCompleted: {
                fileManager.setProjectPaths(generalSettings.projectPath)
            }
        }

        Rectangle {
            width: 1
            Layout.fillHeight: true
            color: Material.foreground
        }

        Loader {
            id: mainLoader
            Layout.fillHeight: true
            Layout.minimumWidth: 400
            Layout.fillWidth: true

            property int fileType: EFileInfo.NotFound

            sourceComponent: emptyPage
            Component {
                id: emptyPage
                Label {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("Select Eagle file")
                }
            }
            Component {
                id: notSupportedFilepage
                Label {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("File not supported")
                }
            }

            Connections {
                target: drillReporter
                onSignalReport: {
                    if (mainLoader.fileType === EFileInfo.Board) {
                        mainLoader.item.setDrillReport(report)
                    }
                }                               
            }

            Component.onCompleted: {
                fileManager.fileSelect.connect(mainLoader.loadFile)
            }

            function loadFile(type, path, info) {
                fileType = type
                if (fileType === EFileInfo.Board) {
                    mainLoader.setSource("BrdManager.qml", {"filePath" : path, "info" : info})
                    drillReporter.getReport(path)
                }
                else {
                    mainLoader.sourceComponent = notSupportedFilepage
                }
            }
        }

    }
}
