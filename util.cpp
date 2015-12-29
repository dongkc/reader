#include "util.h"
#include <string>

using namespce std;

void hex2ASCII(char c, char ascii[2])
{
  ascii[0] = c >> 4 + '0';
  ascii[1] = c & 0x0F + '0';
}

void ASCII2hex(char ascii[2], char& c)
{
  c = (ascii[0] - '0' << 4) | (ascii[1] - '0');
}

string format(char* hex, int32_t len)
{
  char ascii[2];
  string content;
  for (int i = 0; i < len; ++i) {
    hex2ASCII(hex[i], ascii);
    content += string(ascii, 2) + " ";
  }
  content += "\n";

  return content;
}
