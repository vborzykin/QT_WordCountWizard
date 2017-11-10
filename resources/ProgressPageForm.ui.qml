import QtQuick 2.7
import QtQuick.Controls 1.4 as Old
import QtQuick.Controls 2.2

Item {
    id: item1
    property alias progressBarValue: progressBar.value
    property alias progressBarFrom: progressBar.from
    property alias progressBarTo: progressBar.to
    property alias tableModel: tableView.model
    property alias rowsCountText: rowsCount.text
    property alias wordsCountText: wordsCount.text
    property alias uniqueWordsCountText: uniqueWordsCount.text
    property alias tableView: tableView

    Text {
        id: text1
        x: 23
        text: qsTr("Rows count:")
        anchors.top: progressBar.bottom
        anchors.topMargin: 20
        font.pixelSize: 12
    }

    Text {
        id: rowsCount
        y: 49
        text: qsTr("0")
        anchors.left: text1.right
        anchors.leftMargin: 10
        anchors.verticalCenter: text1.verticalCenter
        font.pixelSize: 12
    }

    ProgressBar {
        id: progressBar
        height: 8
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        value: 0
    }

    Old.TableView {
        id: tableView
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: progressBar.right
        anchors.rightMargin: 0
        anchors.left: progressBar.left
        anchors.leftMargin: 0
        anchors.top: text1.bottom
        anchors.topMargin: 20
        Old.TableViewColumn {
            role: "word"
            title: "Word"
        }
        Old.TableViewColumn {
            role: "count"
            title: "Count"
        }
    }

    Text {
        id: text2
        x: 257
        y: 49
        text: qsTr("Words count:")
        anchors.verticalCenter: text1.verticalCenter
        anchors.horizontalCenterOffset: -30
        anchors.horizontalCenter: progressBar.horizontalCenter
        font.pixelSize: 12
    }

    Text {
        id: wordsCount
        y: 49
        text: qsTr("0")
        anchors.left: text2.right
        anchors.leftMargin: 10
        anchors.verticalCenter: text2.verticalCenter
        font.pixelSize: 12
    }

    Text {
        id: text3
        x: 418
        y: 49
        text: qsTr("Unique words count:")
        anchors.verticalCenter: text1.verticalCenter
        anchors.right: uniqueWordsCount.left
        anchors.rightMargin: 10
        font.pixelSize: 12
    }

    Text {
        id: uniqueWordsCount
        x: 548
        y: 49
        text: qsTr("0")
        anchors.verticalCenter: text3.verticalCenter
        anchors.right: progressBar.right
        anchors.rightMargin: 0
        font.pixelSize: 12
    }
}
