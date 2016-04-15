#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMessageLogContext>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QString>
#include <QMutex>

#include "reader.h"
#include "lockid.h"

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("DEBUG:");
        break;

    case QtWarningMsg:
        text = QString("WARN:");
        break;

    case QtCriticalMsg:
        text = QString("CRITICAL:");
        break;

    case QtFatalMsg:
        text = QString("FATAL:");
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString current_date = QString("%1").arg(current_date_time);
    QString message = QString("%1 %2 %3").arg(text).arg(current_date).arg(msg);

    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  qInstallMessageHandler(outputMessage);

  QQmlApplicationEngine engine;
  Reader reader;
  LockId lockid;

  engine.rootContext()->setContextProperty("reader", &reader);
  engine.rootContext()->setContextProperty("lockid", &lockid);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return app.exec();
}

