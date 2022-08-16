import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import Qt.labs.settings 1.1
import ETools 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("eagleTools")
    property string theme: "light"
    property bool vertical : height > width

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
        category: "Directories"
        property variant projectPathList: []
    }

    SettingsDialog {
        id: settingsDialog
        onSettingsChanged: {
            generalSettings.projectPathList = settingsDialog.projectPathList
            fileManager.setProjectPathList(settingsDialog.projectPathList)
        }
    }

    function setTheme(theme) {
        if (theme === "light") {
            mainWindow.Material.theme = Material.Light
            themeButton.icon.source = "qrc:///images/open-iconic/svg/moon.svg"
        }
        else if (theme === "dark") {
            mainWindow.Material.theme = Material.Dark
            themeButton.icon.source = "qrc:///images/open-iconic/svg/sun.svg"
        }

        backButton.icon.color = Material.foreground
        settingsButton.icon.color = Material.foreground
        themeButton.icon.color = Material.foreground
    }

    Component.onCompleted: setTheme(mainWindow.theme)

    // --- header ---
    header: ToolBar {
        contentHeight: settingsButton.implicitHeight
        RowLayout {
            anchors.fill: parent
            ToolButton {
                id: backButton
                icon.source: "qrc:///images/open-iconic/svg/arrow-circle-left.svg"
                visible: mainStackView.depth > 1
                hoverEnabled: true
                ToolTip.delay: 500
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Back")
                onClicked: mainStackView.pop()

            }
            Item { Layout.fillWidth: true } // spacer
            ToolButton {
                id: settingsButton
                icon.source: "qrc:///images/open-iconic/svg/cog.svg"
                visible: true
                hoverEnabled: true
                ToolTip.delay: 500
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Settings")
                onClicked: {
                    console.log(generalSettings.projectPathList)
                    settingsDialog.projectPathList = generalSettings.projectPathList
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
    }  // ToolBar

    // --- global functions ---
    function openFile(type, path) {
        if (type === EFileInfo.Schematic) {
            schViewer.openFile(path)
            mainStackView.push(schViewer)
        }
    }

    // --- main item ---
    StackView {
        id: mainStackView
        initialItem: controlPanel
        anchors.fill: parent
    }

    // --- control panel ---
    Item {
        id: controlPanel

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
                    fileManager.setProjectPathList(generalSettings.projectPathList)
                }

                onSelectFile: {
                    if (type === EFileInfo.Board) {
                        brdManager.info = info
                        brdManager.setFilePath(path)
                        if(fileInfoStackView.currentItem !== brdManager)
                            fileInfoStackView.replace(brdManager)
                    }
                    else if (type === EFileInfo.Schematic) {
                        schManager.info = info
                        schManager.setFilePath(path)
                        if(fileInfoStackView.currentItem !== schManager)
                            fileInfoStackView.replace(schManager)
                    }
                    else {
                        fileInfoStackView.replace(notSupportedFilePageItem)
                    }
                }

                onOpenFile: mainWindow.openFile(type, path)
            }

            Rectangle {
                width: 1
                Layout.fillHeight: true
                color: Material.foreground
            }

            StackView {
                id: fileInfoStackView
                Layout.fillHeight: true
                Layout.minimumWidth: 400
                Layout.fillWidth: true
                clip: true
                initialItem: emptyPageItem
            }

            Item {
                id: emptyPageItem
                Label {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("Select Eagle file")
                }
            }

            Item {
                id: notSupportedFilePageItem
                visible: false
                Label {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("File not supported")
                }
            }

            SchManager {
                id: schManager
                visible: false
                onOpenFile: mainWindow.openFile(EFileInfo.Schematic, path)
                onExportFile: {
                    mainStackView.push(schExportDialog)
                    schExportDialog.exportFile(path)
                }
                onOpenBom: {
                    mainStackView.push(bomView)
                    bomView.openFile(path)
                }
            }

            BrdManager {
                id: brdManager
                visible: false
            }
        }
    }

    // --- sch view ---
    SchViewer {
        id: schViewer
        visible: false
//        anchors.fill: parent
    }

    SchExportDialog {
        id: schExportDialog
        visible: false
    }

    BomView {
        id: bomView
        visible: false
    }
}
