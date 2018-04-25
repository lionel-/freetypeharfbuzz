#include <stddef.h>

char* utf8_next_char(const char* str) {
  ++str;
  while ((*str & 0xc0) == 0x80) {
    ++str;
  }
  return (char*) str;
}

size_t utf8_strlen(const char* str) {
  size_t len = 0;
  while (*str) {
    str = utf8_next_char(str);
    ++len;
  }
  return len;
}
