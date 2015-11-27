#include "uidata.h"

UiData::UiData(QObject *parent) : QObject(parent)
{
}

void UiData::setReaderIP(const QString& ip)
{
  reader_ip = ip;
}

void UiData::setReaderPort(uint32_t port)
{
  reader_port = port;
}

void UiData::setLockId(const QString& id)
{
  lock_id = id;
}

void UiData::setCount(uint32_t num)
{
  count = num;
}

QString UiData::ReaderIP()
{
  return reader_ip;
}

uint32_t UiData::ReaderPort()
{
  return reader_port;
}

QString UiData::LockId()
{
  return lock_id;
}

uint32_t UiData::Count()
{
  return count;
}

