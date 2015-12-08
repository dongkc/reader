import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.1

LockIdForm {
  group2.width: rowlayout.width / 2
  serial_id.focus: true
  MessageDialog {
    id: input_dialog
    title: "Input error"
    text: "关锁贴牌号输入错误!"
    icon: StandardIcon.Critical
  }

  btn_cal.onClicked: {
    var text =  lockid.calculate(country_id.text,
                                   maker_id.text,
                                   serial_id.text,
                                   lock_type.text)
    var check = lockid.check_code()
    if (text) {
      lock_id.text = text
      lbl_check.text = check
    }
  }

  btn_cal2.onClicked: {
    if (txt_lock_id.text.length != 14) {
      lbl_country_code.text = "----"
      lbl_manufacturer.text = "----"
      lbl_serial_id.text = "----"
      lbl_lock_type.text = "----"
      lbl_check_code.text = "----"

      input_dialog.visible = true
      return
    }

    lockid.init(txt_lock_id.text)
    if (!lockid.validate()) {
      lbl_country_code.text = "----"
      lbl_manufacturer.text = "----"
      lbl_serial_id.text = "----"
      lbl_lock_type.text = "----"
      lbl_check_code.text = "----"

      input_dialog.text = "贴牌号校验出错"
      input_dialog.visible = true
      return
    }

    var cn = lockid.cal_country_code()
    var nt = lockid.cal_manufacturer()
    var serial_id = lockid.cal_serial_id()
    var lock_type = lockid.cal_lock_type()
    var check_code = lockid.cal_check_code()

    lbl_country_code.text = cn
    lbl_manufacturer.text = nt
    lbl_serial_id.text = serial_id
    lbl_lock_type.text = lock_type
    lbl_check_code.text = check_code
  }
}

