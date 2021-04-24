import QtQuick 6.0
import QtQuick.Controls 6.0
import Qt.labs.platform 1.1
import FolderList 1.0

Item {
    property int currentIndex: 0
    height: listView.childrenRect.height

    property alias pathList: folderListModel.pathList

    ListView {
        id: listView
        anchors.fill: parent

        delegate: Item {
            id: item
            width: listView.width
            height: pathTextField.implicitHeight

            TextField {
                id: pathTextField
                text: path
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: selectButton.left
                anchors.margins: 2
                onTextChanged: path = text
                selectByMouse: true
            }

            Button {
                id: selectButton
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: deleteButton.left
                anchors.margins: 2
                text: "\uD83D\uDD0D"
                height: 40
                onClicked: {
                    currentIndex = index
                    folderDialog.open()
                }
            }

            Button {
                id: deleteButton
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 2
                text: "\u2573"
                height: 40
                onClicked: folderListModel.remove(index)
                enabled: last ? false : true
            }
        }

        model: FolderListModel {
            id: folderListModel
        }
    }

    FolderDialog {
        id: folderDialog
        title: qsTr("Please choose a folder")
        folder: shortcuts.home
        visible: false
        onAccepted: {
            folderListModel.change(currentIndex, folderDialog.folder)
        }
    }
}
