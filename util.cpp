#include "util.h"
#include <string>
#include <iostream>

using namespace std;

inline char helper(char c)
{
  if (c < 10) {
    return c + '0';
  }

  return c - 10 + 'A';
}
void hex2ASCII(char c, char* ascii)
{
  char high = (c & 0xF0) >> 4;
  char low = c & 0x0F;
  ascii[0] = helper(high);
  ascii[1] = helper(low);
}

void ASCII2hex(char ascii[2], char& c)
{
  c = ((ascii[0] - '0') << 4) | (ascii[1] - '0');
}

string format(const char* hex, int32_t len)
{
  char ascii[2];
  string content;
  for (int i = 0; i < len; ++i) {
    hex2ASCII(hex[i], (char*)&ascii);
    content = content + string(ascii, 2) + " ";
  }
  content += "\n";

  return content;
}
