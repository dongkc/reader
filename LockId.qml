import QtQuick 2.4

LockIdForm {
  group2.width: rowlayout.width / 2

  btn_cal.onClicked: {
    lock_id.text =  lockid.calculate(country_id.text,
                                   maker_id.text,
                                   serial_id.text,
                                   lock_type.text)
  }
}

