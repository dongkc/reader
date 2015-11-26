#include "reader.h"

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
