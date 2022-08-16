import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Qt.labs.settings 1.1
import QtQuick.Layouts 1.15
import ETools 1.0

ColumnLayout {
    id: fileManager
    signal selectFile(var type, var path, var info)
    signal openFile(var type, var path, var info)

    // info about selecteed file
    Item {
        id: currentFile
        property string name: ''
        property string path: ''
        property string url: ''
        property string info: ''
        property var type: EFileInfo.NotFound
    }

    Settings {
        id: settings
        category: "FileManager"
        property var recentFileList: []
    }

    Frame {
        Layout.fillWidth: true
        Layout.margins: 5
        Material.elevation: 6

        Label {
            anchors.centerIn: parent
            wrapMode: "WordWrap"
            text: qsTr("Directories")
        }
    }

    ScrollView {
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.preferredHeight: 300
        Layout.margins: 5
        clip: true
        DocumentTree {
            id: documentTree
            onSelectFile: {
                setCurrentFile(path)
                fileManager.selectFile(currentFile.type, currentFile.path, currentFile.info)
            }
            onOpenFile: {
                setCurrentFile(path)
                currentFileToRecent()
                fileManager.openFile(currentFile.type, currentFile.path, currentFile.info)
            }
        }
    }

    Frame {
        Layout.fillWidth: true
        Layout.margins: 5
        Material.elevation: 6

        Label {
            anchors.centerIn: parent
            wrapMode: "WordWrap"
            text: qsTr("Recent files")
        }
    }

    ListView {
        id: recentFilesView
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.preferredHeight: 100
        Layout.margins: 5
        model: recentFilesModel
        clip: true

        property var recentFileList: []

        highlight: Rectangle { color: "lightslategrey" }
        highlightFollowsCurrentItem: true

        delegate: Item {
            width: recentFilesView.width
            height: 32

            Label {
                anchors.centerIn: parent
                renderType: Text.NativeRendering
                text: model.text
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    recentFilesView.currentIndex = model.index
                    setCurrentFile(model.url)
                    selectFile(currentFile.type, currentFile.path, currentFile.info)
                }
                onDoubleClicked: {
                    recentFilesView.currentIndex = model.index
                    setCurrentFile(model.url)
                    openFile(currentFile.type, currentFile.path, currentFile.info)
                }
            }
        }
    }

    ListModel {
        id: recentFilesModel
        dynamicRoles: true

        property var fileList: []

        Component.onCompleted: {
            var fileList = settings.recentFileList

            fileList.forEach(function(item, i, arr) {
                setCurrentFile(item)
                currentFileToRecent()
                // select last file
                if (i === (arr.length - 1))
                    selectFile(currentFile.type, currentFile.path, currentFile.info)
            })
        }

        Component.onDestruction: {
            var fileList = []
            for (var i = recentFilesModel.count - 1; i >= 0; --i) {
                fileList.push(recentFilesModel.get(i).url)
            }
            settings.recentFileList = fileList
        }
    }

    function setCurrentFile(fileUrl) {
        if (currentFile.url !== fileUrl) {
            eFileInfo.checkFile(fileUrl)

            currentFile.url = fileUrl
            currentFile.type = eFileInfo.getType()
            currentFile.path = eFileInfo.getFilePath()
            currentFile.name = currentFile.path.slice(
                        Math.max(currentFile.path.lastIndexOf('/'),
                                 currentFile.path.lastIndexOf('\\')) + 1)
            currentFile.info = eFileInfo.getInfo()
        }
    }

    function currentFileToRecent() {
        recentFilesModel.insert(0, {text: currentFile.name,
                                    url: currentFile.url}
                                )
        recentFilesView.currentIndex = 0;
        if (recentFilesModel.count > 10)
            recentFilesModel.remove(10, 1)
    }

    function selectCurrentFile() {
        fileSelected(eFileInfo.getType(), filePath, eFileInfo.getInfo())
    }

    function setProjectPathList(pathList) {
        documentTree.setProjectPathList(pathList)
    }

    EFileInfo {
        id: eFileInfo
    }
}
