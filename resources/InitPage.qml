import QtQuick 2.7
import QtQuick.Dialogs 1.2
import Vbor.wordcount.fileanalizer 1.0
import Vbor.wordcount.utils 1.0

InitPageForm {
    property string headerText: qsTr("Initialization")
    property bool nextAllowed: fileAnalizer.fileChecked

    btnOpenFile.onClicked: {
        openFileDialog.open()
    }

    onTextInputTextChanged: {
        fileAnalizer.checkFile(textInputText);
    }

    FileDialog {
        id: openFileDialog
        title: qsTr("Please choose a file")
        folder: shortcuts.home
        onAccepted: {
            textInputText = Utils.UrlToPath(fileUrl)
        }
    }

    function onNextBtnClick(){
        stackView.push("qrc:/ProgressPage.qml", {fileName: textInputText})
    }

}
