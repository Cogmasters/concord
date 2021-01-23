#include <stdarg.h>
#include <stddef.h> // size_t
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


static char * normalize_fmt (char * fmt) {
  char * fmt1 = malloc(strlen(fmt) + 1);
  char * s = fmt, * d = fmt1;

  while (*s) {
    if ('\\' == *s && '|' == *(s+1)) {
      *d = *(s+1);
      s += 2, d ++;
    }
    else if ('|' == *s) {
      *d = '"';
      s++, d++;
    }
    else {
      *d = *s;
      s++, d++;
    }
  }
  *d = '\0';
  return fmt1;
}

/*
 *
 *  To improve the clarity of json format string,
 *  it treats |  as ", and | can be escaped as \|
 *
 */
int json_asprintf(char ** buf, char * json_fmt, ...) {
  va_list ap;
  va_start(ap, json_fmt);
  char * fmt1 = normalize_fmt(json_fmt);
  int ret = vasprintf(buf, fmt1, ap);
  va_end(ap);
  free(fmt1);
  return ret;
}

int json_snprintf(char *str, size_t size, const char * json_fmt, ...) {
  va_list ap;
  va_start(ap, json_fmt);
  char * fmt1 = normalize_fmt(json_fmt);
  int ret = vsnprintf (str, size, fmt1, ap);
  va_end(ap);
  free(fmt1);
  return ret;
}

