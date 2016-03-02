import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
  visible: true
  width: 800
  height: 600
  minimumWidth: 800
  minimumHeight: 600
  title: qsTr("关锁测试")

  TabView {
    Tab {
      title: "阅读器测试"
      LockReader {
      }

    }
    Tab {
      title: "关锁号计算器"
      LockId {
      }
    }
    Tab {
      title:"关锁GPRS测试"
    }
    Tab {
      title:"关于本测试工具"
      About {
      }
    }
    anchors.fill: parent
  }
}

