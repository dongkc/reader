import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.3

Item {
  width: 500
  height: 500

  RowLayout {
    id: rowLayout1
    anchors.rightMargin: 0
    anchors.bottomMargin: 0
    anchors.leftMargin: 0
    anchors.topMargin: 0
    anchors.fill: parent

    Column {
      id: column1
      width: 200
      height: 400

      GroupBox {
        id: groupBox1
        width: 200
        height: 200
        title: qsTr("Group Box")

        Button {
          id: button1
          x: 24
          y: 485
          text: qsTr("Button")
        }
      }

      GroupBox {
        id: groupBox2
        width: 200
        height: 300
        title: qsTr("Group Box")
      }
    }

    TextArea {
      id: textArea1
      text: "1234567"
      readOnly: true
    }

  }
}

