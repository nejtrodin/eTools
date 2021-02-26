import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0
import ETools 1.0

Frame {
    function setSchematicPath(paths) {
        bomListModel.setSchematicPath(paths)
    }

    ListView {
        id: bomListView
        anchors.fill: parent
        clip: true

        model:bomListModel

        delegate: Item {
            id: wrapper
            height: 32
            width: bomListView.width

            //Полоска для отделения элементов друг от друга
            Rectangle {
                height: 1
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                color: "#d0d0d0"
            }

            Label {
                id: partNumberElement
                text: partNumber
                verticalAlignment: "AlignVCenter"
                width: 50
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }

            Label {
                id: partNameElement
                text: partName
                verticalAlignment: "AlignVCenter"
                anchors.left: partNumberElement.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
            }
        }
    }

    BomListModel {
        id: bomListModel
    }
}
