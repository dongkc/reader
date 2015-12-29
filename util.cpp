#include "util.h"
#include <string>

void hex2ASCII(uint8_t c, uint8_t ascii[2])
{
  ascii[0] = c >> 4 + '0';
  ascii[1] = c & 0x0F + '0';
}

void ASCII2hex(uint8_t ascii[2], uint8_t& c)
{
  c = (ascii[0] - '0' << 4) | (ascii[1] - '0');
}
