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
        x: 100
        width: 200
        height: 250
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Grid {
            id: grid1
            width: 200
            height: 150
            spacing: 10
            rows: 4
            columns: 2

            Label {
              id: label1
              height: 30
              text: qsTr("COUNTRY CODE:")
              horizontalAlignment: Text.AlignRight
              verticalAlignment: Text.AlignVCenter
            }

            TextField {
              id: textField1
              height: 30
              text: "CN"
            }

            Label {
              id: label2
              text: qsTr("MAKER ID:")
              horizontalAlignment: Text.AlignRight
            }

            TextField {
              id: textField2
              text: "NT"
            }

            Label {
              id: label3
              text: qsTr("SERIAL ID:")
              horizontalAlignment: Text.AlignRight
            }

            TextField {
              id: textField3
            }

            Label {
              id: label4
              text: qsTr("LOCK TYPE:")
              horizontalAlignment: Text.AlignRight
            }

            TextField {
              id: textField4
            }
        }

        Button {
          id: button1
          height: 30
          text: qsTr("calculate")
          anchors.horizontalCenter: parent.horizontalCenter
        }

        Label {
          id: label5
          height: 50
          color: "#1b26ed"
          text: qsTr("Label")
          style: Text.Normal
          font.bold: true
          font.pointSize: 18
          font.family: "Verdana"
          verticalAlignment: Text.AlignVCenter
          anchors.horizontalCenter: parent.horizontalCenter
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

