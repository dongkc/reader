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

}

