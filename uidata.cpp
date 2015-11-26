#include "uidata.h"

UiData::UiData(QObject *parent) : QObject(parent)
{
}

void UiData::setReaderIP(const QString& ip)
{
  reader_ip = ip;
}

void UiData::setReaderPort(u_int32_t port)
{
  reader_port = port;
}

void UiData::setLockId(const QString& id)
{
  lock_id = id;
}

void UiData::setCount(u_int32_t num)
{
  count = num;
}

QString UiData::ReaderIP()
{
  return reader_ip;
}

u_int32_t UiData::ReaderPort()
{
  return reader_port;
}

QString UiData::LockId()
{
  return lock_id;
}

u_int32_t UiData::Count()
{
  return count;
}

