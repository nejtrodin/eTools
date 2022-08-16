import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
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

        delegate: ColumnLayout {
            id: wrapper
            width: bomListView.width

            //Полоска для отделения элементов друг от друга
            Rectangle {
                height: 1
                Layout.fillWidth: true
                color: "#d0d0d0"
            }

            Label {
                id: partNameElement
                text: name
                font.bold: true
            }

            RowLayout {
                Label {
                    id: partQtyElement
                    text: quantity + ":"
                    Layout.alignment: Qt.AlignVCenter
                }

                Label {
                    id: partPositionsElement
                    text: positions
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    wrapMode: Text.WordWrap
                }
            }
        }  // delegate
    }

    BomListModel {
        id: bomListModel
    }
}
