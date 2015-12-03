#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "reader.h"
#include "lockid.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QQmlApplicationEngine engine;
  Reader reader;
  LockId lockid;

  engine.rootContext()->setContextProperty("reader", &reader);
  engine.rootContext()->setContextProperty("lockid", &lockid);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return app.exec();
}

