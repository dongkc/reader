import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
  visible: true
  width: 640
  height: 480
  title: qsTr("关锁测试")

  TabView {
    Tab {
      title: "阅读器测试"
      LockReader {
      }

    }
    Tab {
      //title: "关锁号计算器"
      title: "关锁号计算器"
      LockId {
      }
    }
    Tab {
      title:"关锁GPRS测试"
    }
    anchors.fill: parent
  }
}

