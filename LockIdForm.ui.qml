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
            width: 320
            height: 150
            spacing: 10
            rows: 4
            columns: 2

            Label {
              id: label1
              height: 20
              text: qsTr("COUNTRY CODE:")
              horizontalAlignment: Text.AlignRight
              verticalAlignment: Text.AlignVCenter
            }

            TextField {
              id: textField1
              height: 20
              text: "CN"
            }

            Label {
              id: label2
              height: 20
              text: qsTr("MAKER ID:")
              wrapMode: Text.NoWrap
              verticalAlignment: Text.AlignVCenter
              horizontalAlignment: Text.AlignRight
            }

            TextField {
              id: textField2
              text: "NT"
            }

            Label {
              id: label3
              height: 20
              text: qsTr("SERIAL ID:")
              verticalAlignment: Text.AlignVCenter
              horizontalAlignment: Text.AlignRight
            }

            TextField {
              id: textField3
            }

            Label {
              id: label4
              height: 20
              text: qsTr("LOCK TYPE:")
              verticalAlignment: Text.AlignVCenter
              horizontalAlignment: Text.AlignRight
            }

            TextField {
              id: textField4
            }
        }

        Button {
          id: button1
          height: 20
          text: qsTr("calculate")
          anchors.horizontalCenter: parent.horizontalCenter
        }

        Label {
          id: label5
          height: 50
          color: "#1b26ed"
          text: qsTr("UNKNOWN")
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
      anchors.right: parent.right
      anchors.rightMargin: 10
      anchors.left: groupBox1.right
      anchors.leftMargin: 10
      anchors.bottom: parent.bottom
      anchors.bottomMargin: 10
      anchors.top: parent.top
      anchors.topMargin: 10
      title: qsTr("Group Box")

      Column {
          id: column2
          width: 200
          height: 250
          spacing: 10
          anchors.horizontalCenter: parent.horizontalCenter
          anchors.verticalCenter: parent.verticalCenter

          Row {
            id: row1
            width: 170
            height: 60
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            Label {
              id: label6
              height: 20
              text: qsTr("LOCK ID")
              verticalAlignment: Text.AlignVCenter
            }

              TextField {
                  id: textField5
                  height: 20
              }
          }

          Button {
            id: button2
            y: 60
            height: 20
            text: qsTr("calculate")
            anchors.horizontalCenter: parent.horizontalCenter
          }

          Grid {
              id: grid2
              y: 76
              width: 150
              height: 150
              anchors.horizontalCenter: parent.horizontalCenter
              flow: Grid.LeftToRight
              layoutDirection: Qt.LeftToRight
              spacing: 5
              rows: 4
              columns: 2

              Label {
                id: label7
                height: 30
                text: qsTr("COUNTRY CODE:")
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
              }

              Label {
                id: label8
                height: 30
                color: "#1b26ed"
                text: qsTr("UNKNOWN")
                wrapMode: Text.NoWrap
                verticalAlignment: Text.AlignVCenter
              }

              Label {
                id: label9
                height: 30
                text: qsTr("MAKER ID:")
                verticalAlignment: Text.AlignVCenter
              }

              Label {
                id: label10
                height: 30
                color: "#1b26ed"
                text: qsTr("UNKNOWN")
                verticalAlignment: Text.AlignVCenter
              }

              Label {
                id: label11
                height: 30
                text: qsTr("SERIAL ID:")
                verticalAlignment: Text.AlignVCenter
              }

              Label {
                id: label12
                height: 30
                color: "#1b26ed"
                text: qsTr("UNKNOWN")
                verticalAlignment: Text.AlignVCenter
              }

              Label {
                id: label13
                height: 30
                text: qsTr("LOCK TYPE:")
                verticalAlignment: Text.AlignVCenter
              }

              Label {
                  id: label14
                  height: 30
                  color: "#1b26ed"
                  text: qsTr("UNKNOWN")
                  verticalAlignment: Text.AlignVCenter
              }
          }
      }
    }
  }
}

