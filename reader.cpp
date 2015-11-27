#include "reader.h"
#include "message.h"

Reader::Reader(QObject *parent) : QObject(parent)
{
  socket = new QTcpSocket(this);
  QObject::connect(socket, SIGNAL(connected()), this, SLOT(connected()));
  QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
}

bool Reader::connect(QString ip, int port)
{
  qDebug() << "CONNECT TO " << ip << " port: " << port;
  socket->connectToHost(QHostAddress(ip), port);
  qDebug("Connect ...");

  return true;
}

void Reader::connected()
{
  qDebug("connected");
  emit conn();
}

void Reader::error(QAbstractSocket::SocketError socketError)
{
  //switch (socketError) {
  //  case QAbstractSocket::RemoteHostCloseError:
  qDebug() << "NETWORK ERROR: " << socketError;
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
}
