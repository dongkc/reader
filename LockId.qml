import QtQuick 2.4

LockIdForm {
  group2.width: rowlayout.width / 2
  serial_id.focus: true

  btn_cal.onClicked: {
    var text =  lockid.calculate(country_id.text,
                                   maker_id.text,
                                   serial_id.text,
                                   lock_type.text)
    if (text) {
      lock_id.text = text
    }
  }
}

