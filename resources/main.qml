import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.1
import Vbor.wordcount.fileanalizer 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Words counter")
    flags: Qt.Dialog
    property bool alreadyAsked: false

    Connections{
        target: fileAnalizer
        onFinished:{
            messageFinished.open()
        }
    }

    function onYes(){
        fileAnalizer.cancel();
        alreadyAsked = true
        Qt.quit()
    }

    onClosing:{
        if(!alreadyAsked && fileAnalizer.isRunning())
        {
            close.accepted = false
            messageDialog.caller = applicationWindow
            messageDialog.open()
        }
        else{
            close.accepted = true
        }
    }

    MessageDialog {
        id: messageDialog
        title: "Confirm"
        standardButtons: StandardButton.Yes | StandardButton.No
        text: "Process is in progress. Do you want cancel operation?"
        property var caller: undefined
        onYes:{
            if(caller && caller.onYes)
            {
                caller.onYes()
                caller = undefined
            }
        }
    }

    MessageDialog {
        id: messageFinished
        text: "Counting completed!"
    }

    header: Pane{
        anchors.left: parent.left
        anchors.right: parent.right
        visible: stackView.currentItem.headerText ? true : false
        Text{
            text: stackView.currentItem.headerText
        }
    }

    StackView {
        id: stackView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: applicationWindow.header.bottom
        anchors.bottom: applicationWindow.footer.top
        initialItem: InitPage{}
    }

    footer: Pane {
        height: 48
        bottomPadding: 0
        topPadding: 0
        anchors.right: parent.right
        anchors.left: parent.left
        Button{
            id: btnBack
            height: 36
            text: qsTr("<< Back")
            visible: stackView.depth > 1
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 25
            anchors.right: btnNext.left
            onClicked: {
                if(stackView.currentItem.onBackBtnClick){
                    stackView.currentItem.onBackBtnClick()
                } else {
                    stackView.pop()
                }
            }
        }
        Button{
            id: btnNext
            height: 36
            text: qsTr("Next >>")
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            visible: stackView.currentItem.onNextBtnClick ? true : false
            enabled: stackView.currentItem.nextAllowed ? true : false
            onClicked: {
                stackView.currentItem.onNextBtnClick()
            }
        }
        Button{
            id: btnFinish
            height: 36
            text: qsTr("Finish")
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            visible: stackView.currentItem.onFinishBtnClick ? true : false
            onClicked: {
                stackView.currentItem.onFinishBtnClick()
            }
        }

        Rectangle {
            id: rectangle
            height: 1
            color: "#66000000"
            anchors.leftMargin: -2
            anchors.rightMargin: -2
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
        }
    }
}
