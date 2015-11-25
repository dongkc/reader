import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.3

Item {
  width: 500
  height: 500
  anchors.fill: parent

  RowLayout {
    id: rowLayout1
    anchors.fill: parent


    Column {
      id: column1
      width: 150
      height: 500
      spacing: 10
      anchors.top: parent.top
      anchors.topMargin: 0

      GroupBox {
        id: groupBox1
        width: 150
        height: 300
        title: qsTr("Settings")

        Column {
          id: column2
          width: 200
          height: 400
          spacing: 5

          Label {
            id: label1
            height: 20
            text: "阅读器IP地址"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
          }

            TextField {
              id: textField1
              placeholderText: qsTr("Text Field")
            }

            Label {
              id: label2
              height: 20
              text: qsTr("阅读器端口")
              horizontalAlignment: Text.AlignLeft
              verticalAlignment: Text.AlignVCenter
            }

            TextField {
              id: textField2
              placeholderText: qsTr("Text Field")
            }

            Button {
                id: button1
                width: 104
                text: qsTr("连接")
            }
        }
      }

        GroupBox {
            id: groupBox2
            width: 360
            height: 300
            title: qsTr("Group Box")
        }
    }

    ColumnLayout {
      id: columnLayout1
      anchors.right: parent.right
      anchors.rightMargin: 10
      anchors.left: parent.left
      anchors.leftMargin: 230
      anchors.bottom: parent.bottom
      anchors.bottomMargin: 10
      anchors.top: parent.top
      anchors.topMargin: 10

      TextArea {
        id: textArea1
        text: "1234567"
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        readOnly: true
      }
    }
  }
}

