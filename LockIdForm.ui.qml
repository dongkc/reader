import QtQuick 2.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

Item {
  width: 640
  height: 480

  property alias group2: groupBox2
  property alias rowlayout: rowLayout1
  property alias country_id: country_id
  property alias maker_id: maker_id
  property alias serial_id: serial_id
  property alias lock_type: lock_type
  property alias lbl_check: lbl_check
  property alias lock_id: lock_id
  property alias btn_cal: btn_cal
  property alias btn_cal2: btn_cal2
  property alias txt_lock_id: txt_lock_id
  property alias lbl_country_code: lbl_country_code
  property alias lbl_manufacturer: lbl_manufacturer
  property alias lbl_serial_id: lbl_serial_id
  property alias lbl_lock_type: lbl_lock_type
  property alias lbl_check_code: lbl_check_code


  RowLayout {
    id: rowLayout1
    anchors.fill: parent

    GroupBox {
      id: groupBox1
      height: 480
      anchors.right: parent.right
      anchors.rightMargin: 320
      anchors.left: parent.left
      anchors.leftMargin: 10
      anchors.bottom: parent.bottom
      anchors.bottomMargin: 10
      anchors.top: parent.top
      anchors.topMargin: 10
      visible: true
      title: qsTr("正算")

      Column {
        id: column1
        x: 100
        width: 200
        height: 250
        anchors.verticalCenterOffset: 1
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Grid {
          id: grid1
          width: 240
          height: 150
          transformOrigin: Item.Center
          horizontalItemAlignment: Grid.AlignRight
          spacing: 10
          rows: 5
          columns: 2

          Label {
            id: label1
            height: 20
            text: qsTr("国家代码:")
            transformOrigin: Item.Right
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
          }

          TextField {
            id: country_id
            height: 20
            text: "CN"
            inputMask: qsTr("AA")
          }

          Label {
            id: label2
            height: 20
            text: qsTr("制造商代码:")
            wrapMode: Text.NoWrap
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
          }

          TextField {
            id: maker_id
            text: "NT"
            inputMask: qsTr("AA")
          }

          Label {
            id: label3
            height: 20
            text: qsTr("生产序列号:")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
          }

          TextField {
            id: serial_id
            text: ""
            placeholderText: qsTr("00 01 23")
            inputMask: qsTr("HH HH HH; ")
          }

          Label {
            id: label4
            height: 20
            text: qsTr("关锁类型:")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
          }

          TextField {
            id: lock_type
            placeholderText: qsTr("1")
            inputMask: qsTr("H")
          }

          Label {
            id: label8
            height: 30
            text: qsTr("校验码:")
          }

          Label {
            id: lbl_check
            height: 30
            color: "#0d3ebf"
              text: qsTr("-")
          }
        }

        Button {
          id: btn_cal
          height: 20
          text: qsTr("计算贴牌号")
          anchors.top: parent.top
          anchors.topMargin: 180
          anchors.horizontalCenter: parent.horizontalCenter
        }

        TextEdit {
          id: lock_id
          y: 250
          width: 150
          height: 30
          color: "#0d3ebf"
          text: qsTr("----")
          anchors.top: parent.top
          anchors.topMargin: 250
          cursorVisible: false
          readOnly: true
          clip: true
          font.bold: true
          horizontalAlignment: Text.AlignHCenter
          anchors.horizontalCenter: parent.horizontalCenter
          font.pixelSize: 18
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
      title: qsTr("反算")

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
            text: qsTr("关锁贴牌号:")
            verticalAlignment: Text.AlignVCenter
          }

          TextField {
            id: txt_lock_id
            height: 20
            inputMask: qsTr("AAAA9999999999")
            font.bold: true
            font.pointSize: 8
          }
        }

        Button {
          id: btn_cal2
          y: 60
          height: 20
          text: qsTr("计算")
          anchors.horizontalCenter: parent.horizontalCenter
        }

        Grid {
          id: grid2
          y: 76
          width: 100
          height: 170
          anchors.horizontalCenter: parent.horizontalCenter
          horizontalItemAlignment: Grid.AlignRight
          flow: Grid.LeftToRight
          spacing: 5
          rows: 5
          columns: 2

          Label {
            id: label7
            height: 30
            text: qsTr("国家代码:")
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
          }

          Label {
            id: lbl_country_code
            height: 30
            color: "#1b26ed"
            text: qsTr("----")
            wrapMode: Text.NoWrap
            verticalAlignment: Text.AlignVCenter
          }

          Label {
            id: label9
            height: 30
            text: qsTr("制造商代码:")
            verticalAlignment: Text.AlignVCenter
          }

          Label {
            id: lbl_manufacturer
            height: 30
            color: "#1b26ed"
            text: qsTr("----")
            verticalAlignment: Text.AlignVCenter
          }

          Label {
            id: label11
            height: 30
            text: qsTr("生产序列号:")
            verticalAlignment: Text.AlignVCenter
          }

          Label {
            id: lbl_serial_id
            height: 30
            color: "#1b26ed"
            text: qsTr("----")
            verticalAlignment: Text.AlignVCenter
          }

          Label {
            id: label13
            height: 30
            text: qsTr("关锁类型:")
            verticalAlignment: Text.AlignVCenter
          }

          Label {
            id: lbl_lock_type
            height: 30
            color: "#1b26ed"
            text: qsTr("----")
            verticalAlignment: Text.AlignVCenter
          }

          Label {
            id: label5
            height: 30
            text: qsTr("校验码:")
            verticalAlignment: Text.AlignVCenter
          }

          Label {
              id: lbl_check_code
              height: 30
              color: "#1b26ed"
              text: qsTr("----")
              verticalAlignment: Text.AlignVCenter
          }
        }
      }
    }
  }
}

