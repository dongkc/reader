import QtQuick 2.4

LockIdForm {
  group2.width: rowlayout.width / 2
  serial_id.focus: true

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
    var cn = lockid.cal_country_code(txt_lock_id.text)
    var nt = lockid.cal_manufacturer(txt_lock_id.text)
    var serial_id = lockid.cal_serial_id(txt_lock_id.text)
    var lock_type = lockid.cal_lock_type(txt_lock_id.text)
    var check_code = lockid.cal_check_code(txt_lock_id.text)

    lbl_country_code.text = cn
    lbl_manufacturer.text = nt
    lbl_serial_id.text = serial_id
    lbl_lock_type.text = lock_type
    lbl_check_code.text = check_code
  }
}

