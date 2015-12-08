import QtQuick 2.4
import QtQuick.Controls 1.3

Item {
  id: item1
  width: 600
  height: 400

  Grid {
    id: grid1
    width: 550
    height: 200
    spacing: 10
    rows: 4
    columns: 2
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter

    Label {
      id: label1
      text: qsTr("版本:")
      verticalAlignment: Text.AlignVCenter
      font.pointSize: 18
    }

    Label {
      id: label2
      text: qsTr("0.9")
      verticalAlignment: Text.AlignVCenter
      font.pointSize: 18
    }

    Label {
      id: label7
      text: qsTr("git:")
      verticalAlignment: Text.AlignVCenter
      font.pointSize: 18
    }

    Label {
      id: label8
      text: qsTr("b62e05a6d8016cf0a35255ddbee18ecfdbc91847")
      verticalAlignment: Text.AlignVCenter
      font.pointSize: 18
    }

    Label {
      id: label3
      text: qsTr("作者:")
      verticalAlignment: Text.AlignVCenter
      font.pointSize: 18
    }

    Label {
      id: label4
      text: qsTr("dongkechang")
      verticalAlignment: Text.AlignVCenter
      font.pointSize: 18
    }

    Label {
      id: label5
      text: qsTr("邮箱:")
      verticalAlignment: Text.AlignVCenter
      font.pointSize: 18
    }

    Label {
      id: label6
      text: qsTr("dongkechang@nuctech.com")
      verticalAlignment: Text.AlignVCenter
      font.pointSize: 18
    }
  }
}

