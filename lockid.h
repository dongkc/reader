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

  Q_INVOKABLE QString calculate(std::string cn,
                                std::string nt,
                                std::string serial_id,
                                std::string type);

signals:

public slots:

private:
};

#endif // LOCKID_H
