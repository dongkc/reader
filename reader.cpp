#include <QMessageBox>
#include <string>

#include "reader.h"
#include "message.h"
#include "util.h"
#include "msg.h"

#define MAX_BUF_SIZE 1024

using namespace std;

Reader::Reader(QObject *parent) : QObject(parent)
{
  socket = new QTcpSocket(this);
  QObject::connect(socket, SIGNAL(connected()), this, SLOT(connected()));
  QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
  QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
}

bool Reader::connect(QString ip, int port)
{
  qDebug() << "CONNECT TO " << ip << " port: " << port;
  socket->connectToHost(QHostAddress(ip), port);

  return true;
}

void Reader::connected()
{
  qDebug("connected");
  emit conn();
}

void Reader::disconnect()
{
  socket->abort();
  socket->disconnectFromHost();
  qDebug() << "Disconnect from host";
}

void Reader::error(QAbstractSocket::SocketError socketError)
{
  qDebug() << "NETWORK ERROR: " << socketError;
  QMessageBox msg;
  msg.setText("NETWORK ERROR");
  msg.exec();

  emit disConn();
}

void Reader::lock(QString lock_id, QString pass)
{
  unsigned char buf[64];
  unsigned int len = sizeof(buf);
  memset(buf, 64, 0);
  char *begin = (char*)buf;
  CreateSealingReq(lock_id.toStdString(),
                   pass.toStdString(),
                   &buf[0],
                   len);

  socket->write(begin, len);
  qDebug() << "Send out seal data";
  qDebug() << "Send out:" << format(begin, len).c_str();
}

void Reader::unlock(QString lock_id, QString pass)
{
  unsigned char buf[64];
  unsigned int len = sizeof(buf);
  memset(buf, 64, 0);
  char *begin = (char*)buf;
  CreateUnSealingReq(lock_id.toStdString(),
                     pass.toStdString(),
                     &buf[0],
                     len);

  socket->write(begin, len);
  qDebug() << "Send out unlock data";
  qDebug() << "Send out:" << format(begin, len).c_str();
}

void Reader::check(QString lock_id, QString pass)
{
  unsigned char buf[64];
  unsigned int len = sizeof(buf);
  memset(buf, 64, 0);
  char *begin = (char*)buf;
  CreateCheckSealingReq(lock_id.toStdString(),
                        pass.toStdString(),
                        &buf[0],
                        len);

  socket->write(begin, len);
  qDebug() << "Send out check data";
  qDebug() << "Send out:" << format(begin, len).c_str();
}

void Reader::clear_warn(QString lock_id, QString pass)
{
  unsigned char buf[64];
  unsigned int len = sizeof(buf);
  memset(buf, 64, 0);
  char *begin = (char*)buf;
  CreateRemoveWarnReq(lock_id.toStdString(),
                        pass.toStdString(),
                        &buf[0],
                        len);

  socket->write(begin, len);
  qDebug() << "Send out:" << format(begin, len).c_str();
}

void Reader::write_data(QString lock_id,
                        QString pass,
                        QString data)
{
  unsigned char buf[64];
  unsigned int len = sizeof(buf);
  memset(buf, 64, 0);
  char *begin = (char*)buf;
  string data_write = data.toStdString();
  CreateWriteDataReq(lock_id.toStdString(),
                     pass.toStdString(),
                     data_write.data(),
                     data_write.size(),
                     &buf[0],
                     len);

  socket->write(begin, len);
  qDebug() << "Send out:" << format(begin, len).c_str();
}

void Reader::read_data(QString lock_id, QString pass)
{
  unsigned char buf[64];
  unsigned int len = sizeof(buf);
  memset(buf, 64, 0);
  char *begin = (char*)buf;
  CreateReadDataReq(lock_id.toStdString(),
                    pass.toStdString(),
                    &buf[0],
                    len);

  qDebug() << "Send out:" << format(begin, len).c_str();
  socket->write(begin, len);

}

void Reader::read()
{
  char recv_buf[MAX_BUF_SIZE];
  qint64 len = socket->read(recv_buf, MAX_BUF_SIZE);
  string msg(format(recv_buf, len));
  qDebug() << "Received data:" << msg.c_str();

  Message message;
  if (!parse(recv_buf, len, &message)) {
    qDebug() << "Parse error";
  };

  string ret(serialize(message));
  emit  messagePost(QString(ret.c_str()));
}
