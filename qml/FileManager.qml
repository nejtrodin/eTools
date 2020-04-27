import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0
import Qt.labs.settings 1.0
import QtQuick.Layouts 1.12

import eFileInfo 1.0

ColumnLayout {

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
            onOpenFile: appendFile(path)
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

        highlight: Rectangle { color: Material.accent }
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
                    fileSelect(model.type, model.path, model.info)
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
            fileList.forEach(function(item, i, arr) { appendFile(item) })
        }

        Component.onDestruction: {
            var fileList = []
            var i;
            for (i = 0; i < recentFilesModel.count; i++) {
                fileList.push(recentFilesModel.get(i).url)
            }
            settings.recentFileList = fileList
        }
    }

    signal fileSelect(var type, var path, var info)

    function appendFile(fileUrl) {
        eFileInfo.checkFile(fileUrl)

        var filePath = eFileInfo.getFilePath()
        var name = filePath.slice(
                    Math.max(filePath.lastIndexOf('/'), filePath.lastIndexOf('\\')) + 1)
        recentFilesModel.insert(0,
                                {text: name,
                                 type: eFileInfo.getType(),
                                 path: filePath,
                                 url: fileUrl,
                                 info: eFileInfo.getInfo()}
                                )
        recentFilesView.currentIndex = 0;
        if (recentFilesModel.count > 10)
            recentFilesModel.remove(10, 1)        

        fileSelect(eFileInfo.getType(), filePath, eFileInfo.getInfo())
    }

    function setProjectPaths(paths) {
        documentTree.setProjectPaths(paths)
    }

    EFileInfo {
        id: eFileInfo
    }
}
