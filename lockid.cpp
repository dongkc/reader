#include "lockid.h"
#include <stdint.h>
#include <string>
#include <vector>
#include <QtGlobal>
#include <QDebug>
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

QString LockId::calculate(string cn,
                          string nt,
                          string serial_id,
                          string type)
{
  serial_id.erase(5, 1);
  serial_id.erase(2, 1);

  string str(cn + nt + serial_id + type);
  qDebug("INPUT DATA: %s", str.c_str());

  uint32_t res = 0;
  for(int i = 0; i < 11; ++i) {
    res += str[i] << i;
  }
  uint8_t check = (res % 11) % 10;

  string data(serial_id + type);
  data.push_back(check + 0x30);

  unsigned int num = 0;
  if (NumberParser::tryParseHex(data, num)) {
    qDebug("Error: %s", data.c_str());
  };
  string ret(cn + nt + NumberFormatter::format0(num, 10));

  return QString(ret.c_str());
}
