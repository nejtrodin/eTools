import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Frame {
    property alias report: reportText.text

    Label {
        id: reportHeader
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Drill Table")
        font.bold: true
    }

    TextEdit {
        id: reportText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: reportHeader.bottom
        anchors.topMargin: 10
        textFormat: Text.RichText
        readOnly: true
        selectByMouse: true
        width: parent.width
        wrapMode: Text.Wrap
        text: qsTr("text")
        color: Material.foreground
        horizontalAlignment: Text.AlignHCenter
    }
}
