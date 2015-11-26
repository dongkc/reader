import QtQuick 2.4

LockReaderForm {
  btn_con.onClicked: {
    btn_con.text = "connecting"
  }

  Connections {
    target: reader
    onConn: {
      console.log("socked connected")
      btn_con.text = "connected"
    }
  }
}

