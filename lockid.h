#ifndef LOCKID_H
#define LOCKID_H

#include <stdint.h>
#include <string>
#include <QString>
#include <QObject>

class LockId : public QObject
{
  Q_OBJECT
public:
  explicit LockId(QObject *parent = 0);

  Q_INVOKABLE QString calculate(QString cn,
                                QString nt,
                                QString serial_id,
                                QString type);

  Q_INVOKABLE QString check_code();

  Q_INVOKABLE QString cal_country_code(QString id);

  Q_INVOKABLE QString cal_manufacturer(QString id);

  Q_INVOKABLE QString cal_serial_id(QString id);

  Q_INVOKABLE QString cal_lock_type(QString id);

  Q_INVOKABLE QString cal_check_code(QString id);

signals:

public slots:

private:
  std::string cal_hex(const std::string& id);

private:
  uint8_t check;
};

#endif // LOCKID_H
