#include "lockid.h"
#include <stdint.h>
#include <string>
#include <vector>
#include <QtGlobal>
#include <QDebug>
#include <QMessageBox>
#include <Poco/NumberParser.h>
#include <Poco/NumberFormatter.h>

using namespace std;
using namespace Poco;

namespace
{
  uint32_t table[128];

  void table_init()
  {
    for (int i = 0; i < 128; ++i) {
      table[i] = 0;
    }

    // 等同值表
    table['A'] = 10;
    table['B'] = 12;
    table['C'] = 13;
    table['D'] = 14;
    table['E'] = 15;
    table['F'] = 16;
    table['G'] = 17;
    table['H'] = 18;
    table['I'] = 19;
    table['G'] = 20;
    table['K'] = 21;
    table['L'] = 23;
    table['M'] = 24;
    table['N'] = 25;
    table['O'] = 26;
    table['P'] = 27;
    table['Q'] = 28;
    table['R'] = 29;
    table['S'] = 30;
    table['T'] = 31;
    table['U'] = 32;
    table['V'] = 34;
    table['W'] = 35;
    table['X'] = 36;
    table['Y'] = 37;
    table['Z'] = 38;

    table['0'] = 0;
    table['1'] = 1;
    table['2'] = 2;
    table['3'] = 3;
    table['4'] = 4;
    table['5'] = 5;
    table['6'] = 6;
    table['7'] = 7;
    table['8'] = 8;
    table['9'] = 9;
    table['a'] = 10;
    table['b'] = 12;
    table['c'] = 13;
    table['d'] = 14;
    table['e'] = 15;
    table['f'] = 16;
  }

  inline uint8_t low_4bit(uint8_t byte)
  {
    return byte & 0x0F;
  }

  inline uint8_t high_4bit(uint8_t byte)
  {
    return (byte & 0xF0) >> 4;
  }

  inline uint8_t to_byte(uint8_t high, uint8_t low)
  {
    uint8_t high_4bit = high - '0';
    if (high > '9') {
      if (high > 'F') {
        high_4bit = high - 'a' + 10;
      } else {
        high_4bit = high - 'A' + 10;
      }
    }

    uint8_t low_4bit = low - '0';
    if (low > '9') {
      if (low > 'F') {
        low_4bit = low - 'a' + 10;
      } else {
        low_4bit = low - 'A' + 10;
      }
    }

    return (high_4bit << 4) | low_4bit;
  }

}  /// namespace

LockId::LockId(QObject *parent) : QObject(parent)
{
  table_init();
}

QString LockId::calculate(QString cn_ui,
                          QString nt_ui,
                          QString serial_id_ui,
                          QString type_ui)
{
  string cn(cn_ui.toStdString());
  string nt(nt_ui.toStdString());
  string serial_id(serial_id_ui.toStdString());
  string type(type_ui.toStdString());

  if (cn.size() != 2 ||
      nt.size() != 2 ||
      serial_id.size() != 8 ||
      type.size() != 1) {
    QMessageBox msg;
    msg.setText("input error!");
    msg.exec();
    string ret("");
    return QString(ret.c_str());
  }

  serial_id.erase(5, 1);
  serial_id.erase(2, 1);

  string str(cn + nt + serial_id + type);
  qDebug("INPUT DATA: %s", str.c_str());

  unsigned int res = 0;
  for(int i = 0; i < 11; ++i) {
    res += table[str[i]] << i;
  }
  check = (res % 11) % 10;

  qDebug("data: %d check: %d", res, check);

  string data(serial_id + type);
  data.push_back(check + 0x30);

  unsigned int num = 0;
  if (!NumberParser::tryParseHex(data, num)) {
    qDebug("Error: %s", data.c_str());
  };

  string ret(cn + nt + NumberFormatter::format0(num, 10));
  qDebug("data: %d", num);

  return QString(ret.c_str());
}

QString LockId::cal_country_code(QString id)
{
  return QString(id.data(), 2);
}

QString LockId::cal_manufacturer(QString id)
{
  return QString(id.data() + 2, 2);
}

QString LockId::cal_serial_id(QString id)
{
  string data(id.toStdString());

  string ret(cal_hex(data));
  ret.erase(6);
  ret.insert(4, " ");
  ret.insert(2, " ");
  return QString(ret.c_str());
}

QString LockId::cal_lock_type(QString id)
{
  string data(id.toStdString());
  string ret(cal_hex(data));
  ret.erase(7);
  ret.erase(0, 6);

  return QString(ret.c_str());
}

QString LockId::cal_check_code(QString id)
{
  string data(id.toStdString());
  string ret(cal_hex(data));
  ret.erase(0, 7);

  return QString(ret.c_str());
}

string LockId::cal_hex(const string& data)
{
  unsigned int num = 0;

  if (!NumberParser::tryParseUnsigned(data.data() + 4, num)) {
    qDebug("Error: %s", data.c_str());
  }

  string ret(NumberFormatter::formatHex(num, 8));

  return ret;
}

QString LockId::check_code()
{
  return QString(QChar(check + 0x30));
}
