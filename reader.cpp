﻿#include <QMessageBox>
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

  timer = new QTimer(this);
  timer->setSingleShot(true);
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

void Reader::timeout()
{
  QMessageBox msg;
  msg.setText(QString::fromLocal8Bit("响应超时!"));
  msg.exec();
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
  unsigned char buf[MAX_BUF_SIZE];
  unsigned int len = sizeof(buf);
  memset(buf, MAX_BUF_SIZE, 0);
  char *begin = (char*)buf;
  CreateSealingReq(lock_id.toStdString(),
                   pass.toStdString(),
                   &buf[0],
                   len);

  socket->write(begin, len);
  qDebug() << ">>" << format(begin, len).c_str();

  this->cmd_current = ELOCK_SEALING_REQ;
  timer->start(6000);
}

void Reader::unlock(QString lock_id, QString pass)
{
  unsigned char buf[MAX_BUF_SIZE];
  unsigned int len = sizeof(buf);
  memset(buf, MAX_BUF_SIZE, 0);
  char *begin = (char*)buf;
  CreateUnSealingReq(lock_id.toStdString(),
                     pass.toStdString(),
                     &buf[0],
                     len);

  socket->write(begin, len);
  qDebug() << ">>" << format(begin, len).c_str();
  this->cmd_current = ELOCK_UNSEALING_REQ;
  timer->start(6000);
}

void Reader::check(QString lock_id, QString pass)
{
  unsigned char buf[MAX_BUF_SIZE];
  unsigned int len = sizeof(buf);
  memset(buf, MAX_BUF_SIZE, 0);
  char *begin = (char*)buf;
  CreateCheckSealingReq(lock_id.toStdString(),
                        pass.toStdString(),
                        &buf[0],
                        len);

  socket->write(begin, len);
  qDebug() << ">>" << format(begin, len).c_str();
  this->cmd_current = ELOCK_CHECK_SEALING_REQ;
  timer->start(6000);
}

void Reader::clear_warn(QString lock_id, QString pass)
{
  unsigned char buf[MAX_BUF_SIZE];
  unsigned int len = sizeof(buf);
  memset(buf, MAX_BUF_SIZE, 0);
  char *begin = (char*)buf;
  CreateRemoveWarnReq(lock_id.toStdString(),
                        pass.toStdString(),
                        &buf[0],
                        len);

  socket->write(begin, len);
  qDebug() << ">>" << format(begin, len).c_str();
  this->cmd_current = ELOCK_REMOVE_WARN_REQ;
  timer->start(6000);
}

void Reader::modify_apn(QString lock_id,
                        QString password,
                        QString apn,
                        QString phone_num,
                        QString gateway_ip,
                        QString gateway_port,
                        QString interval,
                        QString pass)
{
  unsigned char buf[MAX_BUF_SIZE];
  unsigned int len = sizeof(buf);
  memset(buf, 256, 0);
  char *begin = (char*)buf;
  CreateAPNReq(lock_id.toStdString(),
               pass.toStdString(),
               apn.toStdString(),
               phone_num.toStdString(),
               gateway_ip.toStdString(),
               gateway_port.toStdString(),
               interval.toStdString(),
               pass.toStdString(),
               &buf[0],
               len);

  socket->write(begin, len);
  qDebug() << ">>" << format(begin, len).c_str();
  this->cmd_current = ELOCK_APN_REQ;
  timer->start(6000);
}

void Reader::read_apn(QString lock_id, QString pass)
{
  unsigned char buf[MAX_BUF_SIZE];
  unsigned int len = sizeof(buf);
  memset(buf, MAX_BUF_SIZE, 0);
  char *begin = (char*)buf;
  CreateReadAPNReq(lock_id.toStdString(),
                   pass.toStdString(),
                   &buf[0],
                   len);

  socket->write(begin, len);
  qDebug() << ">>" << format(begin, len).c_str();
  this->cmd_current = ELOCK_READ_APN_REQ;
  timer->start(6000);
}

void Reader::write_data(QString lock_id,
                        QString pass,
                        int blockid,
                        QString data)
{
  unsigned char buf[MAX_BUF_SIZE];
  unsigned int len = sizeof(buf);
  memset(buf, MAX_BUF_SIZE, 0);
  char *begin = (char*)buf;
  string data_write = data.toStdString();
  CreateWriteDataReq(lock_id.toStdString(),
                     pass.toStdString(),
                     blockid,
                     data_write.data(),
                     data_write.size(),
                     &buf[0],
                     len);

  socket->write(begin, len);
  qDebug() << ">>" << format(begin, len).c_str();
  this->cmd_current = ELOCK_WRITE_EXTENSION_DATA_REQ;
  timer->start(6000);
}

void Reader::read_data(QString lock_id, QString pass, int blockid)
{
  unsigned char buf[MAX_BUF_SIZE];
  unsigned int len = sizeof(buf);
  memset(buf, MAX_BUF_SIZE, 0);
  char *begin = (char*)buf;
  CreateReadDataReq(lock_id.toStdString(),
                    pass.toStdString(),
                    blockid,
                    &buf[0],
                    len);

  qDebug() << ">>" << format(begin, len).c_str();
  socket->write(begin, len);

  this->cmd_current = ELOCK_READ_EXTENSION_DATA_REQ;
  timer->start(6000);
}

void Reader::read_lockid(QString lock_id, QString pass)
{
  unsigned char buf[MAX_BUF_SIZE];
  unsigned int len = sizeof(buf);
  memset(buf, MAX_BUF_SIZE, 0);
  char *begin = (char*)buf;
  CreateReadLockidReq(lock_id.toStdString(),
                    pass.toStdString(),
                    &buf[0],
                    len);

  qDebug() << ">>" << format(begin, len).c_str();
  this->cmd_current = ELOCK_READ_LOCKID_REQ;
  socket->write(begin, len);
}

void Reader::read()
{

  // stop the counting timer first
  timer->stop();

  char recv_buf[MAX_BUF_SIZE];
  qint64 len = socket->read(recv_buf, MAX_BUF_SIZE);
  string msg(format(recv_buf, len));
  qDebug() << "<<" << msg.c_str();

  Message message;
  if (parse(recv_buf, len, &message)) {
    qDebug() << "Parse error";
    msg = "Unknown msg received: " + string(recv_buf, len)+ "\r\n";
    emit  messagePost(QString::fromLocal8Bit(msg.c_str()));

    return;
  };

  emit  messagePost(serialize(message));

  // multi lock and unlock success notifications
  if ((message.cmd_id == ELOCK_SEALING_RES &&
       message.body.seal_p.success_flag != 0xFF ) ||
      (message.cmd_id == ELOCK_UNSEALING_RES &&
       message.body.unseal_p.success_flag != 0xFF)) {
    emit lockUnlock();
  }

  if (message.cmd_id != cmd_current + 1) {
    QMessageBox msg;
    msg.setText(QString::fromLocal8Bit("接收到的消息与发送的命令不匹配!"));
    msg.exec();
  }

}
