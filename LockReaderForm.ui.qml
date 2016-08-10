import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.3

Item {
  id: item1
  width: 1200
  height: 600
  anchors.fill: parent

  property alias btn_con: btn_connect
  property alias txt_ip: txt_ip
  property alias txt_port: txt_port
  property alias txt_lockid: txt_lockid
  property alias btn_lock: btn_lock
  property alias btn_unlock: btn_unlock
  property alias btn_verify: btn_verify
  property alias txt_log: txt_log
  property alias btn_read_lockid: btn_read_lockid

  property alias btn_data_write: btn_data_write
  property alias btn_data_read: btn_data_read
  property alias btn_clear_warn: btn_clear_warn
  property alias spinbox_blockid: spinbox_blockid

  property alias txt_gateway_ip: txt_gateway_ip
  property alias txt_gateway_port: txt_gateway_port
  property alias txt_apn: txt_apn
  property alias txt_phone: txt_phone
  property alias txt_interval: txt_interval
  property alias txt_pass: txt_pass
  property alias btn_gateway: btn_gateway
  property alias btn_gateway_read: btn_gateway_read

  property alias txtarea_data: txtarea_data
  property alias btn_clear_info: btn_clear_info

  property alias txt_success_counter: txt_success_counter
  property alias txt_send_counter: txt_send_counter
  property alias btn_multi_send: btn_multi_send
  property alias btn_stop: btn_stop
  property alias spinbox_count: spinbox_count
  property alias spinbox_send_interval: spinbox_send_interval
  property alias txt_rfid_pass: txt_rfid_pass

  RowLayout {
    id: rowLayout1
    width: 1200
    height: 600
    anchors.rightMargin: 0
    anchors.bottomMargin: 0
    anchors.leftMargin: 0
    anchors.topMargin: 0
    anchors.fill: parent

    Column {
      id: column1
      x: 0
      width: 150
      height: 590
      anchors.top: parent.top
      anchors.topMargin: 0
      spacing: 5

      GroupBox {
        id: groupBox1
        x: 5
        width: 150
        height: 140
        title: qsTr("阅读器")

        Column {
          id: column2
          x: 5
          width: 150
          height: 130
          spacing: 3

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
        height: 250
        title: "操作命令"
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
            text: "CNNT0000003607"
            readOnly: true
          }

          Button {
            id: btn_read_lockid
            width: 104
            height: 20
            text: qsTr(" 上报锁号")
            enabled: false
          }

          Label {
            id: lbl_rfid_pass
            text: qsTr("通讯密码:")
          }


          TextField {
            id: txt_rfid_pass
            text: "0000000000"
            placeholderText: qsTr("")
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
          }

















          Button {
            id: btn_clear_warn
            width: 104
            text: qsTr("清除报警")
            enabled: false
          }








        }
      }

      GroupBox {
        id: groupBox4
        x: 5
        width: 150
        height: 180
        title: qsTr("连续操作命令")

        Column {
          id: column6
          spacing: 5
          anchors.fill: parent

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
              suffix: qsTr("")
              activeFocusOnPress: true
              selectByMouse: true
              minimumValue: 1
              decimals: 0
              maximumValue: 100000
            }
          }

          Row {
            id: row5
            width: 120
            height: 25
            spacing: 5

            Label {
              id: label6
              text: qsTr("间隔时间")
            }

            SpinBox {
              id: spinbox_send_interval
              width: 64
              suffix: qsTr("秒")
            }
          }


          Row {
            id: row6
            y: 77
            width: 120
            height: 15
            spacing: 10

            Label {
              id: label7
              height: 12
              text: qsTr("发送次数")
            }

            Text {
              id: txt_send_counter
              text: qsTr("0")
              font.pixelSize: 12
            }
          }


          Row {
            id: row7
            width: 120
            height: 15
            spacing: 10

            Label {
              id: label8
              text: qsTr("成功次数")
            }

            Text {
              id: txt_success_counter
              text: qsTr("0")
              font.pixelSize: 12
            }
          }

          Button {
            id: btn_multi_send
            x: 0
            width: 104
            text: qsTr("连续发送")
            enabled: false

            property bool cl: false
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

    Column {
      id: column5
      width: 200
      height: 400
      anchors.left: column1.right
      anchors.leftMargin: 10
      anchors.top: parent.top
      anchors.topMargin: 0

      GroupBox {
        id: groupBox3
        width: 150
        height: 340
        title: qsTr("网关配置")
        Column {
          id: column4
          x: 5
          width: 150
          height: 320
          spacing: 3
          Label {
            id: lbl_ip1
            height: 20
            text: "IP地址:"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
          }

          TextField {
            id: txt_gateway_ip
            text: "114.251.120.120"
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
            id: txt_gateway_port
            text: "8067"
            inputMask: "00000000"
            placeholderText: qsTr("8000")
          }


          Label {
            id: lbl_apn
            text: qsTr("APN:")
          }


          TextField {
            id: txt_apn
            text: "CMNET"
          }


          Label {
            id: lbl_interval
            text: qsTr("INTERVAL:")
          }


          TextField {
            id: txt_interval
            text: "0030"
          }



          Label {
            id: label1
            text: qsTr("PHONE")
          }

          TextField {
            id: txt_phone
            text: "13612345678"
          }

          Label {
            id: lbl_pass
            text: qsTr("PASSWORD:")
          }





          TextField {
            id: txt_pass
            text: "12345678"
          }





          Button {
            id: btn_gateway
            width: 104
            text: qsTr("写配置")
            enabled: false
          }

          Button {
              id: btn_gateway_read
              width: 104
              text: qsTr("读配置")
              enabled: false
          }



        }
      }

      Button {
        id: btn_clear_info
        width: 150
        height: 40
        text: qsTr("清除收到的信息")
      }
    }

    ColumnLayout {
      id: columnLayout1
      anchors.leftMargin: 320
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
          id: txtarea_data
          height: 50
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

          Label {
            id: label9
            height: 15
            text: qsTr("数据块序号:")
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
          }

          SpinBox {
            id: spinbox_blockid
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            maximumValue: 255
          }

          Button {
            id: btn_data_write
            width: 104
            text: qsTr("写业务数据")
            enabled: false
          }



          Button {
            id: btn_data_read
            text: qsTr("读业务数据")
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
        height: 250
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
        target: btn_gateway
        enabled: true
      }

      PropertyChanges {
        target: btn_clear_warn
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

      PropertyChanges {
        target: groupBox3
        title: qsTr("Gateway")
      }

      PropertyChanges {
        target: btn_gateway
        enabled: true
      }

      PropertyChanges {
        target: item1
        width: 1200
        height: 600
      }

      PropertyChanges {
        target: groupBox4
        title: qsTr("连续施解封")
      }

      PropertyChanges {
        target: btn_read_lockid
        width: 104
        height: 23
        enabled: true
      }

      PropertyChanges {
        target: button1
        width: 150
        height: 40
        opacity: 1
      }

      PropertyChanges {
        target: btn_gateway_read
        enabled: true
      }

    },
    State {
      name: "multi_test"
      PropertyChanges {
        target: groupBox2
        height: 220
        checkable: false
        checked: true
      }

      PropertyChanges {
        target: btn_connect
        text: "断开"
        enabled: false
      }

      PropertyChanges {
        target: txt_lockid
        placeholderText: qsTr("")
        readOnly: false
      }

      PropertyChanges {
        target: btn_lock
        enabled: false
      }

      PropertyChanges {
        target: btn_unlock
        enabled: false
      }

      PropertyChanges {
        target: btn_verify
        enabled: false
      }

      PropertyChanges {
        target: btn_multi_send
        enabled: false
      }

      PropertyChanges {
        target: btn_stop
        enabled: true
      }

      PropertyChanges {
        target: spinbox_count
        selectByMouse: true
        activeFocusOnPress: true
      }

      PropertyChanges {
        target: txt_ip
        text: "192.168.10.254"
        readOnly: true
      }

      PropertyChanges {
        target: txt_port
        text: "8071"
        readOnly: true
      }

      PropertyChanges {
        target: btn_gateway
        enabled: false
      }

      PropertyChanges {
        target: btn_clear_warn
        enabled: false
      }

      PropertyChanges {
        target: btn_data_write
        enabled: false
      }

      PropertyChanges {
        target: btn_data_read
        enabled: false
      }

      PropertyChanges {
        target: groupBox3
        title: qsTr("Gateway")
      }

      PropertyChanges {
        target: btn_gateway
        enabled: true
      }

      PropertyChanges {
        target: item1
        width: 1200
        height: 600
      }

      PropertyChanges {
        target: groupBox4
        title: qsTr("连续施解封")
      }

      PropertyChanges {
        target: btn_gateway_read
        enabled: false
      }
    }
  ]
}

