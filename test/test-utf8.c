#include "utf8.h"
#include <stdio.h>
#include <string.h>

int get_utf8(const char *js, size_t len, char *val8, size_t val8_len) {
  const char *pos_start;
  const char *pos_cursor;
  const char *pos_stop;

  wchar_t  q32[1024];
  wchar_t *q32_start;
  wchar_t *q32_cursor_out;
  wchar_t *q32_cursor_in;
  wchar_t *q32_stop;

  wchar_t  val32[1024];
  wchar_t *val32_start;
  wchar_t *val32_cursor_out;
  wchar_t *val32_cursor_in;
  wchar_t *val32_stop;

  char *val8_start;
  char *val8_cursor;
  char *val8_stop;

  pos_start  = js;
  pos_cursor = pos_start;
  pos_stop   = js + len;

  q32_start = q32;
  q32_cursor_out = q32_start;
  q32_cursor_in  = q32_start;
  q32_stop       = q32_start + 1024;

  val32_start      = val32;
  val32_cursor_out = val32_start;
  val32_cursor_in  = val32_start;
  val32_stop       = val32_start + 1024;

  val8_start  = val8;
  val8_cursor = val8_start;
  val8_stop   = val8_start + val8_len;

  while (pos_cursor < pos_stop && val8_cursor < val8_stop) {
    UTF8_DECODE(pos_cursor, pos_stop, q32_cursor_out, q32_stop);

    JSMN_UNQUOTE(q32_cursor_in, q32_cursor_out, val32_cursor_out, val32_stop);

    UTF8_ENCODE(val32_cursor_in, val32_cursor_out, val8_cursor, val8_stop);

    q32_cursor_out = q32_start;
    q32_cursor_in  = q32_start;

    val32_cursor_out = val32_start;
    val32_cursor_in  = val32_start;
  }

  if (val8_cursor < val8_stop) {
    *val8_cursor = '\0';
  } else if (val8_cursor == val8_stop) {
    *(--val8_cursor) = '\0';
  } else {
    return -1;
  }

  return val8_cursor - val8_start;
}

int main ()
{

  char s [100] = {'\\', 'u', 'd', '8', '3', 'd',
                  '\\', 'u', 'd', 'c', 'a', 'c',
                  0};

  fprintf (stderr, "%s\n", s);

  char out[1024];


  get_utf8(s, strlen(s), out, 1024);

  fprintf(stderr, "%s\n", out);

  return 0;
}
