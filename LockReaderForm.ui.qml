import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.3

Item {
  width: 500
  height: 500
  anchors.fill: parent

  property alias btn_con: btn_connect
  property alias txt_ip: txt_ip
  property alias txt_port: txt_port
  property alias txt_lockid: txt_lockid
  property alias btn_lock: btn_lock
  property alias btn_unlock: btn_unlock
  property alias btn_verify: btn_verify
  property alias btn_multi_send: btn_multi_send
  property alias btn_stop: btn_stop
  property alias spinbox_count: spinbox_count

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
            id: lbl_ip
            height: 20
            text: "阅读器IP地址:"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
          }

          TextField {
            id: txt_ip
            text: "220.181.112.244"
            placeholderText: qsTr("192.168.1.100")
          }

          Label {
            id: label2
            height: 20
            text: qsTr("阅读器端口:")
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
          }

          TextField {
            id: txt_port
            text: "80"
            inputMask: qsTr("")
            placeholderText: qsTr("8000")
          }

          Button {
            id: btn_connect
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
        checked: true
        checkable: false
        flat: false
        visible: true
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
            id: txt_lockid
            readOnly: true
            placeholderText: qsTr("Text Field")
          }

          Button {
            id: btn_lock
            width: 104
            text: qsTr("施封")
            enabled: false
          }

          Button {
            id: btn_unlock
            width: 104
            text: qsTr("解封")
            enabled: false
          }

          Button {
            id: btn_verify
            width: 104
            text: qsTr("验封")
            enabled: false
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
              id: spinbox_count
              activeFocusOnPress: false
              selectByMouse: false
              minimumValue: 1
              decimals: 0
              maximumValue: 10000
            }
          }



          Button {
            id: btn_multi_send
            width: 104
            text: qsTr("连续发送")
            enabled: false
          }



          Button {
            id: btn_stop
            width: 104
            text: qsTr("停止")
            checkable: false
            enabled: false
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
        anchors.rightMargin: 5
        anchors.leftMargin: 0
        anchors.bottomMargin: 5
        anchors.topMargin: 5
        anchors.fill: parent
        readOnly: true
      }
    }
  }

  states: [
    State {
      name: "connected"

      PropertyChanges {
        target: groupBox2
        checkable: false
        checked: true
      }

      PropertyChanges {
        target: txt_port
        text: "80"
      }

      PropertyChanges {
          target: btn_connect
          text: qsTr("已连接")
      }

      PropertyChanges {
        target: txt_lockid
        readOnly: false
      }

      PropertyChanges {
        target: btn_lock
        enabled: true
      }

      PropertyChanges {
        target: btn_unlock
        enabled: true
      }

      PropertyChanges {
        target: btn_verify
        enabled: true
      }

      PropertyChanges {
        target: btn_multi_send
        enabled: true
      }

      PropertyChanges {
        target: btn_stop
        enabled: true
      }

      PropertyChanges {
        target: spinbox_count
        activeFocusOnPress: true
        selectByMouse: true
      }
    },
    State {
        name: "running"
    }
  ]
}

