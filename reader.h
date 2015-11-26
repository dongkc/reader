#ifndef READER_H
#define READER_H

#include <QObject>
#include "uidata.h"

class Reader : public QObject
{
  Q_OBJECT
public:
  explicit Reader(QObject *parent = 0);

  Q_INVOKABLE bool connect(QString& ip, int port);

signals:

public slots:
};

#endif // READER_H
