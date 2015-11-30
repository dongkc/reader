import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.3

Item {
  width: 640
  height: 480

  property alias group2: groupBox2
  property alias rowlayout: rowLayout1

  RowLayout {
    id: rowLayout1
    anchors.fill: parent

    GroupBox {
      id: groupBox1
      width: 320
      height: 480
      anchors.left: parent.left
      anchors.leftMargin: 10
      anchors.bottom: parent.bottom
      anchors.bottomMargin: 10
      anchors.top: parent.top
      anchors.topMargin: 10
      visible: true
      title: qsTr("Group Box")

      Column {
        id: column1
        x: 40
        width: 180
        height: 250
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Row {
          id: row1
          width: 150
          height: 30
          spacing: 10

          Label {
            id: label1
            height: 30
            text: qsTr("国别代码")
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
          }

              TextField {
                  id: textField1
                  height: 30
                  text: "CN"
              }
        }

        Row {
          id: row2
          width: 200
          height: 30
          spacing: 10

          Label {
            id: label2
            height: 30
            text: qsTr("生产商ID")
            verticalAlignment: Text.AlignVCenter
          }

              TextField {
                  id: textField2
                  height: 30
                  text: "NT"
              }
        }

        Row {
          id: row3
          width: 200
          height: 30
          spacing: 10

          Label {
            id: label3
            height: 30
            text: qsTr("自然序列号")
            verticalAlignment: Text.AlignVCenter
          }

              TextField {
                id: textField3
                x: 58
                height: 30
              }
        }

        Row {
          id: row4
          width: 200
          height: 30
          spacing: 10

          Label {
            id: label4
            height: 30
            text: qsTr("锁类型")
            verticalAlignment: Text.AlignVCenter
          }

              TextField {
                  id: textField4
                  x: 58
                  height: 30
              }
        }

        Button {
          id: button1
          x: 40
          height: 30
          text: qsTr("Button")
        }

        Row {
          id: row5
          width: 200
          height: 50

          Label {
            id: label5
            text: qsTr("Label")
          }

              Text {
                  id: text1
                  text: qsTr("Text")
                  font.pixelSize: 12
              }
          }
      }
    }

    GroupBox {
      id: groupBox2
      width: 360
      anchors.left: groupBox1.right
      anchors.leftMargin: 10
      anchors.bottom: parent.bottom
      anchors.bottomMargin: 10
      anchors.top: parent.top
      anchors.topMargin: 10
      title: qsTr("Group Box")

        ColumnLayout {
            id: columnLayout1
            x: 0
            y: 1
            width: 100
            height: 100
        }
    }
  }
}

