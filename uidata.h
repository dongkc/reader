#ifndef UIDATA_H
#define UIDATA_H

#include <QObject>

class UiData : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString ReaderIP READ ReaderIP WRITE setReaderIP)
  Q_PROPERTY(u_int32_t ReaderPort READ ReaderPort WRITE setReaderPort)
  Q_PROPERTY(QString LockId READ LockId WRITE setLockId)
  Q_PROPERTY(u_int32_t Count READ Count WRITE setCount)
public:
  explicit UiData(QObject *parent = 0);

  void setReaderIP(const QString& ip);
  void setReaderPort(u_int32_t port);
  void setLockId(const QString& id);
  void setCount(u_int32_t count);

  QString ReaderIP();
  u_int32_t ReaderPort();
  QString LockId();
  u_int32_t Count();

private:
  QString reader_ip;
  u_int32_t reader_port;
  QString lock_id;
  u_int32_t count;
};

#endif // UIDATA_H
