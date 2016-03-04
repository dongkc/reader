#ifndef __UTIL_H
#define __UTIL_H
#include <string>
#include <stdint.h>

void hex2ASCII(char c, char* ascii);

void ASCII2hex(char ascii[2], char& c);

std::string format(const char* hex, int len);
#endif
