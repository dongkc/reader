import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.3

Item {
  width: 800
  height: 600
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
  property alias txt_log: txt_log

  RowLayout {
    id: rowLayout1
    anchors.fill: parent

    Column {
      id: column1
      x: 0
      width: 150
      height: 590
      spacing: 5
      anchors.top: parent.top
      anchors.topMargin: 0

      GroupBox {
        id: groupBox1
        x: 5
        width: 150
        height: 150
        title: qsTr("Connect")

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
            text: "192.168.10.254"
            inputMask: "000.000.000.000;_"
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
            text: "8071"
            inputMask: "00000000"
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
        title: "Commands"
        checked: true
        checkable: false
        flat: false
        visible: true

        Column {
          id: column3
          x: 5
          width: 150
          height: 300
          spacing: 5

          Label {
            id: label3
            height: 20
            text: qsTr("关锁号:")
            verticalAlignment: Text.AlignVCenter
          }

          TextField {
            id: txt_lockid
            text: "CNNT0000001560"
            readOnly: true
          }

          Row {
            id: row2
            width: 120
            height: 25
            spacing: 3

            Button {
              id: btn_lock
              width: 104
              text: qsTr("施封")
              enabled: false
            }

            CheckBox {
              id: checkBox1
              height: 23
              text: qsTr("")
            }
          }


          Row {
            id: row3
            width: 120
            height: 25
            spacing: 3

            Button {
              id: btn_unlock
              width: 104
              text: qsTr("解封")
              enabled: false
            }

            CheckBox {
              id: checkBox2
              height: 23
            }
          }



          Row {
            id: row4
            width: 120
            height: 25
            spacing: 3

            Button {
              id: btn_verify
              width: 104
              text: qsTr("验封")
              enabled: false
            }

            CheckBox {
              id: checkBox3
              height: 23
            }
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

          Button {
            id: button1
            width: 104
            text: qsTr("Button")
            enabled: false
          }





        }
      }

      GroupBox {
          id: groupBox3
          x: 5
          width: 150
          height: 150
          title: qsTr("Connect")
          Column {
              id: column4
              x: 5
              width: 150
              height: 140
              spacing: 3
              Label {
                  id: lbl_ip1
                  height: 20
                  text: "IP地址:"
                  horizontalAlignment: Text.AlignLeft
                  verticalAlignment: Text.AlignVCenter
              }

              TextField {
                  id: txt_ip1
                  text: "192.168.10.254"
                  inputMask: "000.000.000.000;_"
                  placeholderText: qsTr("192.168.1.100")
              }

              Label {
                  id: label5
                  height: 20
                  text: qsTr("端口:")
                  horizontalAlignment: Text.AlignLeft
                  verticalAlignment: Text.AlignVCenter
              }

              TextField {
                  id: txt_port1
                  text: "8071"
                  inputMask: "00000000"
                  placeholderText: qsTr("8000")
              }

              Button {
                  id: btn_connect1
                  width: 104
                  text: qsTr("confirm")
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
        id: txt_log
        height: 400
        anchors.bottom: rowLayout2.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 5
        anchors.leftMargin: 0
        anchors.bottomMargin: 10
        anchors.topMargin: 5
        readOnly: true
      }

      RowLayout {
        id: rowLayout2
        height: 30
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        TextArea {
          id: textArea1
          anchors.top: parent.top
          anchors.topMargin: 0
          anchors.right: columnLayout2.left
          anchors.rightMargin: 5
          anchors.left: parent.left
          anchors.leftMargin: 0
          anchors.bottom: parent.bottom
          anchors.bottomMargin: 0
        }

        ColumnLayout {
          id: columnLayout2
          width: 100
          anchors.right: parent.right
          anchors.rightMargin: 0
          anchors.bottom: parent.bottom
          anchors.bottomMargin: 0
          anchors.top: parent.top
          anchors.topMargin: 0

          Button {
            id: btn_data_write
            width: 104
            text: qsTr("write")
            enabled: false
          }

          Button {
            id: btn_data_read
            text: qsTr("data send")
            enabled: false
            anchors.right: parent.right
            anchors.bottom: parent.bottom
          }

        }

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
        target: btn_connect
        text: "断开"
      }

      PropertyChanges {
        target: txt_lockid
        placeholderText: qsTr("")
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

      PropertyChanges {
        target: txt_ip
        readOnly: true
      }

      PropertyChanges {
        target: txt_port
        readOnly: true
      }

      PropertyChanges {
        target: btn_connect1
        enabled: true
      }

      PropertyChanges {
        target: button1
        enabled: true
      }

      PropertyChanges {
        target: btn_data_write
        enabled: true
      }

      PropertyChanges {
        target: btn_data_read
        enabled: true
      }

    }
  ]
}

