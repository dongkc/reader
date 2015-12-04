#ifndef LOCKID_H
#define LOCKID_H

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

signals:

public slots:

private:
};

#endif // LOCKID_H
