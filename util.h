#ifndef __UTIL_H
#define __UTIL_H
#include <string>
#include <stdint>

void hex2ASCII(uint8_t c, uint8_t ascii[2]);

void ASCII2hex(uint8_t ascii[2], uint8_t& c);
#endif
