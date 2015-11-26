#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "reader.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QQmlApplicationEngine engine;
  Reader reader;

  engine.rootContext()->setContextProperty("reader", &reader);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return app.exec();
}

