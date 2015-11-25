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
      x: 0
      width: 150
      height: 500
      spacing: 10
      anchors.top: parent.top
      anchors.topMargin: 0

      GroupBox {
        id: groupBox1
        x: 5
        width: 150
        height: 150
        title: qsTr("Settings")

        Column {
          id: column2
          x: 5
          width: 150
          height: 140
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
        x: 5
        width: 150
        height: 280
        title: qsTr("Group Box")

        Column {
          id: column3
          x: 5
          width: 150
          height: 280
          spacing: 10



          Label {
            id: label3
            height: 20
            text: qsTr("关锁号:")
            verticalAlignment: Text.AlignVCenter
          }



          TextField {
            id: textField3
            placeholderText: qsTr("Text Field")
          }

          Button {
            id: button2
            width: 104
            text: qsTr("施封")
          }



          Button {
            id: button3
            width: 104
            text: qsTr("解封")
          }



          Button {
            id: button4
            width: 104
            text: qsTr("验封")
          }



          Row {
            id: row1
            width: 120
            height: 25
            spacing: 5

            Label {
              id: label4
              height: 20
              text: qsTr("连续次数")
              horizontalAlignment: Text.AlignLeft
              verticalAlignment: Text.AlignVCenter
            }

            SpinBox {
              id: spinBox1
              minimumValue: 1
              decimals: 0
              maximumValue: 10000
            }
          }



          Button {
            id: button5
            width: 104
            text: qsTr("连续发送")
          }



          Button {
            id: button6
            width: 104
            text: qsTr("停止")
          }


        }
      }
    }

    ColumnLayout {
      id: columnLayout1
      anchors.leftMargin: 170
      anchors.fill: parent

      TextArea {
        id: textArea1
        text: "1234567"
        anchors.rightMargin: 5
        anchors.leftMargin: 0
        anchors.bottomMargin: 5
        anchors.topMargin: 5
        anchors.fill: parent
        readOnly: true
      }
    }
  }
}

