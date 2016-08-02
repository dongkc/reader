#ifndef READER_H
#define READER_H

#include <QObject>
#include <QtNetwork>
#include "uidata.h"


class Reader : public QObject
{
  Q_OBJECT
public:
  explicit Reader(QObject *parent = 0);

  Q_INVOKABLE bool connect(QString ip, int port);

  Q_INVOKABLE void disconnect();

  Q_INVOKABLE void lock(QString lock_id, QString password);

  Q_INVOKABLE void unlock(QString lock_id, QString password);

  Q_INVOKABLE void check(QString lock_id, QString password);

  Q_INVOKABLE void clear_warn(QString lock_id, QString password);

  Q_INVOKABLE void write_data(QString lock_id, QString password, int blockid, QString data);

  Q_INVOKABLE void read_data(QString lock_id, QString password, int blockid);

  Q_INVOKABLE void read_lockid(QString lock_id, QString password);

  Q_INVOKABLE void modify_apn(QString lock_id,
                              QString password,
                              QString apn,
                              QString phone_num,
                              QString gateway_ip,
                              QString gateway_port,
                              QString interval,
                              QString pass);

  Q_INVOKABLE void read_apn(QString lock_id, QString password);

signals:
  void conn();

  void disConn();

  void messagePost(const QString &msg);

  void lockUnlock();

public slots:
  void connected();

  void read();

  void error(QAbstractSocket::SocketError);

private:
  QTcpSocket *socket;
};

#endif // READER_H
