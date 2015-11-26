#include "reader.h"

Reader::Reader(QObject *parent) : QObject(parent)
{
  socket = new QTcpSocket(this);
  QObject::connect(socket, SIGNAL(connected()), this, SLOT(connected()));
}

bool Reader::connect(QString& ip, int port)
{
  socket->connectToHost(ip, port);
  qDebug("Connect ...");

  return true;
}

void Reader::connected()
{
  qDebug("connected");
  emit conn();
}

