import QtQuick 2.4

LockReaderForm {
  btn_con.onClicked: {
    btn_con.text = "connecting"
    reader.connect(txt_ip.text, txt_port.text)
  }

  Connections {
    target: reader
    onConn: {
      console.log("socked connected")
      state = "connected"
    }
  }
}

