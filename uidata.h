#ifndef UIDATA_H
#define UIDATA_H

#include <stdint.h>
#include <QObject>

class UiData : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString ReaderIP READ ReaderIP WRITE setReaderIP)
  Q_PROPERTY(uint32_t ReaderPort READ ReaderPort WRITE setReaderPort)
  Q_PROPERTY(QString LockId READ LockId WRITE setLockId)
  Q_PROPERTY(uint32_t Count READ Count WRITE setCount)
public:
  explicit UiData(QObject *parent = 0);

  void setReaderIP(const QString& ip);
  void setReaderPort(uint32_t port);
  void setLockId(const QString& id);
  void setCount(uint32_t count);

  QString ReaderIP();
  uint32_t ReaderPort();
  QString LockId();
  uint32_t Count();

private:
  QString reader_ip;
  uint32_t reader_port;
  QString lock_id;
  uint32_t count;
};

#endif // UIDATA_H
