#include "reader.h"

Reader::Reader(QObject *parent) : QObject(parent)
{
  socket = new QTcpSocket(this);
}

bool Reader::connect(QString& ip, int port)
{
  socket->connectToHost(ip, port);
  qDebug("Connect ...");
}

