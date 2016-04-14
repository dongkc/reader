import QtQuick 2.4

LockReaderForm {

  property int success_counter: 0;
  property int counter: 0

  Timer {
    id: timer;
    interval:spinbox_send_interval.value * 1000;
    running: false;
    repeat: true;

    onTriggered: {
      counter++;

      if (counter % 2) {
        reader.unlock(txt_lockid.text, txt_rfid_pass.text);
      } else {
        reader.lock(txt_lockid.text, txt_rfid_pass.text);
      }

      txt_send_counter.text = counter;
    }
  }

  btn_con.onClicked: {
    if (state == "") {
      reader.connect(txt_ip.text, txt_port.text)
    } else {
      reader.disconnect()
      state = ""
    }

  }
  btn_multi_send.onClicked: {
    txt_send_counter.text = 0;
    txt_success_counter.text = 0;
    counter = 0;
    success_counter = 0;

    state = "multi_test"

    btn_multi_send.cl = btn_multi_send.cl ? false : true;
    timer.running = true;
  }

  btn_stop.onClicked: {
    state = "connected"
    btn_multi_send.cl = false;

    timer.running = false;
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
      txt_log.text = txt_log.text + msg
    }

    onLockUnlock: {
      if (!btn_multi_send.cl)
      return;

      success_counter++;
      txt_success_counter.text = success_counter;

      if (counter >= spinbox_count.value) {
        console.log("--- " + counter)
        state = "connected"
        btn_multi_send.cl = false;
        timer.running = false;
      }

    }
  }

  btn_lock.onClicked: {
    reader.lock(txt_lockid.text, txt_rfid_pass.text);
  }

  btn_unlock.onClicked: {
    reader.unlock(txt_lockid.text, txt_rfid_pass.text);
  }

  btn_verify.onClicked: {
    reader.check(txt_lockid.text, txt_rfid_pass.text);
  }

  btn_clear_warn.onClicked: {
    reader.clear_warn(txt_lockid.text, txt_rfid_pass.text);
  }

  btn_data_write.onClicked: {
    reader.write_data(txt_lockid.text, txt_rfid_pass.text, txtarea_data.text);
  }

  btn_data_read.onClicked: {
    reader.read_data(txt_lockid.text, txt_rfid_pass.text);
  }
  btn_gateway.onClicked: {
    reader.modify_apn(txt_lockid.text,
                      txt_rfid_pass.text,
                      txt_apn.text,
                      txt_phone.text,
                      txt_gateway_ip.text,
                      txt_gateway_port.text,
                      txt_interval.text,
                      txt_pass.text);
  }
}

