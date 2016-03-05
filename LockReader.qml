import QtQuick 2.4

LockReaderForm {
  btn_con.onClicked: {
    if (state == "") {
      reader.connect(txt_ip.text, txt_port.text)
    } else {
      reader.disconnect()
      state = ""
    }

  }

  Connections {
    target: reader
    onConn: {
      console.log("socked connected")
      state = "connected"
    }
    onDisConn: {
      reader.disconnect()
      state = ""
    }
    onMessagePost: {
      console.log("---------------------------------------")
      txt_log.text = txt_log.text + msg
    }
  }

  btn_lock.onClicked: {
    reader.lock(txt_lockid.text, qsTr("0000000000"));
  }

  btn_unlock.onClicked: {
    reader.unlock(txt_lockid.text, qsTr("0000000000"));
  }

  btn_verify.onClicked: {
    reader.check(txt_lockid.text, qsTr("0000000000"));
  }

  btn_clear_warn.onClicked: {
    reader.clear_warn(txt_lockid.text, qsTr("0000000000"));
  }

  btn_data_write.onClicked: {
    reader.write_data(txt_lockid.text, qsTr("0000000000"), txtarea_data.text);
  }

  btn_data_read.onClicked: {
    reader.read_data(txt_lockid.text, qsTr("0000000000"));
  }
  btn_gateway.onClicked: {
    reader.modify_apn(txt_lockid.text,
                      qsTr("0000000000"),
                      txt_apn.text,
                      txt_phone.text,
                      txt_gateway_ip.text,
                      txt_gateway_port.text,
                      txt_interval.text,
                      txt_pass.text);
  }
}

