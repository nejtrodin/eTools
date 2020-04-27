import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.12

// За основу взят код из http://qt-way-notes.blogspot.com/2010/07/tree-model-qml.html?m=1

ListView {
    signal openFile(var path)

    id: documentTree
    implicitWidth: 100
    implicitHeight: 100

    model: documentTreeModel

    highlight: Rectangle { color: Material.accent  }
    highlightFollowsCurrentItem: true

    delegate: Item {
        id: wrapper
        height: 32
        width: documentTree.width

        //Полоска для отделения элементов друг от друга
        Rectangle {
            height: 1
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            color: "#d0d0d0"
        }

        //"Отбой" слева элементов-потомков
        Item {
            id: levelMarginElement
            //Начиная с 6 уровня вложенности не сдвигаем потомков,
            //так как иначе можно получить очень широкое окно
            width: (level>5?6:level)*32 + 5
            anchors.left: parent.left
        }

        //Область для открытия/закрытия потомков.
        //На листьях не виден
        Item {
            id: nodeOpenElement
            anchors.left: levelMarginElement.right
            anchors.verticalCenter: wrapper.verticalCenter
            height: 20
            state: "leafNode"
            Image {
                id: triangleOpenImage
                sourceSize.width: parent.height
                sourceSize.height: parent.height

                //Отлавливаем нажатие мышкой и открываем/закрываем элемент
                MouseArea {
                    anchors.fill: parent
                    onClicked: { (isOpened) ?
                                 documentTreeModel.closeItem(index) :
                                 documentTreeModel.openItem(index) }
                }
            }

            ColorOverlay {
                anchors.fill: triangleOpenImage
                source: triangleOpenImage
                color: Material.theme == Material.Dark ? "#ffffffff" : "#00000000"
            }

            states: [
                // Лист - Область не видна
                State {
                        name: "leafNode"
                        when: !hasChildren
                        PropertyChanges {
                            target: nodeOpenElement
                            visible: false
                            width: 0
                        }
                    },
                // Открытый элемент - Область видна и отображена соответствующая иконка
                State {
                    name: "openedNode"
                    when: (hasChildren)&&(isOpened)
                    PropertyChanges {
                        target: nodeOpenElement
                        visible: true
                        width: 24
                    }
                    PropertyChanges {
                        target: triangleOpenImage
                        source: "qrc:///images/open-iconic/svg/chevron-bottom.svg"
                    }
                },
                // Закрытый элемент - Область видна и отображена соответствующая иконка
                State {
                    name: "closedNode"
                    when: (hasChildren)&&(!isOpened)
                    PropertyChanges {
                        target: nodeOpenElement
                        visible: true
                        width: 24
                    }
                    PropertyChanges {
                        target: triangleOpenImage
                        source: "qrc:///images/open-iconic/svg/chevron-right.svg"
                    }
                }
            ]
         }

        //Область для отображения данных элемента
        Label {
            id: nameTextElement
            text: name
            verticalAlignment: "AlignVCenter"
            anchors.left: nodeOpenElement.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            MouseArea {
                anchors.fill: parent
                onClicked: documentTree.currentIndex = model.index
                onDoubleClicked: openFile(path)
            }
        }
    }

    function setProjectPaths(paths) {
        documentTreeModel.setProjectPaths(paths)
    }
}
