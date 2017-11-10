import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    id: item1
    property alias btnOpenFile: btnOpenFile
    property alias textInputText: textInput.text
    Rectangle {
        id: rectangle
        y: 24
        height: 30
        border.color: "black"
        border.width: 1
        anchors.right: btnOpenFile.left
        anchors.rightMargin: 12
        anchors.verticalCenter: btnOpenFile.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 24

        TextInput {
            id: textInput
            height: 20
            clip: true
            anchors.verticalCenterOffset: 2
            anchors.rightMargin: 4
            anchors.leftMargin: 4
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 12
        }
    }
    Button {
        id: btnOpenFile
        width: 100
        height: 40
        text: qsTr("Select file")
        anchors.rightMargin: 24
        anchors.top: textRules.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
    }

    Text {
        id: textRules
        y: 24
        width: 592
        height: 43
        text: qsTr("This application counts the number of unique words in the text. To continue, specify the file and click continue.")
        wrapMode: Text.WordWrap
        anchors.left: parent.left
        anchors.leftMargin: 24
        font.pixelSize: 12
    }
}
