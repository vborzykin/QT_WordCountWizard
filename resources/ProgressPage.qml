import QtQuick 2.7
import Vbor.wordcount.fileanalizer 1.0

ProgressPageForm {
    id: progressPageForm
    readonly property string headerText: qsTr("Results")
    property string fileName
    property bool finishing: false
    tableModel: fileAnalizer.isSorting ? null : fileAnalizer.sortedModel
    rowsCountText: fileAnalizer.progressStatus.rowsCount
    wordsCountText: fileAnalizer.progressStatus.wordsCount
    uniqueWordsCountText: fileAnalizer.progressStatus.uniqWordsCount
    progressBarFrom: fileAnalizer.progressStatus.minimum
    progressBarTo: fileAnalizer.progressStatus.maximum
    progressBarValue: fileAnalizer.progressStatus.value

    onFileNameChanged: {
        fileAnalizer.fileProcess(fileName)
    }

    function onYes(){
        fileAnalizer.cancel()
        if(finishing)
        {
            finishing = false
            applicationWindow.alreadyAsked = true;
            Qt.quit()
        }
        else
        {
            stackView.pop()
        }
    }

    function onBackBtnClick(){
        if(fileAnalizer.isRunning())
        {
            messageDialog.caller = progressPageForm
            messageDialog.open()
        } else {
            stackView.pop()
        }
   }

    function onFinishBtnClick(){
        if(fileAnalizer.isRunning())
        {
            finishing = true
            messageDialog.caller = progressPageForm
            messageDialog.open()
        }
        else
        {
            Qt.quit()
        }
    }
}
