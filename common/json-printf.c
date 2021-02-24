#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#include "json-scanf.h"
#include "orka-debug.h"

#include "ntl.h"

// include jsmn to do post json validation
#define JSMN_STATIC  // dont expose jsmn symbols
#define JSMN_STRICT  // parse json in strict mode
#include "jsmn.h"

static char *
normalize_fmt (char *fmt)
{
  char *fmt1 = malloc(strlen(fmt) + 1);
  char *s = fmt, *d = fmt1;

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

struct specifier {
  enum {
    IS_STR_NULLABLE = 1,
    IS_BOOL_NULLABLE,
    IS_INT_NULLABLE,
    IS_LONG_NULLABLE,
    IS_FLOAT_NULLABLE,
    IS_DOUBLE_NULLABLE,
    IS_STR,
    IS_BOOL,
    IS_INT,
    IS_LONG,
    IS_LONG_LONG,
    IS_FLOAT,
    IS_DOUBLE,
    IS_FUNPTR,
  } type;
  char specifier[10];
  bool has_print_size;
  union {
    void * p;
    bool b;
    int i;
    float f;
    double d;
  } provider;
  extractor *funptr;
  size_t print_size;
  int start;
  int end;
  int after_specifier_pos;
};



static void
format_analyze(char *format, int *num_keys)
{
  /* find % occurrence */
  while (*format) {
    if ('%' == *format) {
      ++*num_keys;
    }
    ++format;
  }
}

//d|ld|lld|f|lf
static struct specifier*
parse_format_specifiers (char * format, int n)
{
  struct specifier * s = calloc(n, sizeof (struct specifier));
  int start = 0;
  const char * start_ptr = format, * end_ptr = format + strlen(format) + 1;

  int i = 0;
  while(format < end_ptr) {
    if ('%' == *format) {
      s[i].start = start;
      s[i].end = format - start_ptr;
      format ++; // eat up '%'
      switch(*format)
      {
        case 's':
          s[i].type = IS_STR;
          strcpy(s[i].specifier, "%.*s");
          break;
        case 'S':
          s[i].type = IS_STR_NULLABLE;
          strcpy(s[i].specifier, "\"%.*s\"");
          break;
        case '.':
          format ++; // eat up '.'
          if ('*' == * format && ('s' == *(format +1) || 'S' == *(format + 1))){
            if ('s' == *(format + 1)) {
              s[i].type = IS_STR;
              strcpy(s[i].specifier, "%.*s");
            }
            else {
              s[i].type = IS_STR_NULLABLE;
              strcpy(s[i].specifier, "\"%.*s\"");
            }
            format ++; // eat up 's';
            s[i].has_print_size = true;
          }
          break;
        case 'd':
          s[i].type = IS_INT;
          strcpy(s[i].specifier, "%d");
          break;
        case 'l':
          format ++; // eat up 'l'
          if ('d' == *format) {
            s[i].type = IS_LONG;
            strcpy(s[i].specifier, "%ld");
          }
          else if ('l' == *format && 'd' == *(format + 1)) {
            format ++; // eat up 'l'
            s[i].type = IS_LONG_LONG;
            strcpy(s[i].specifier, "%lld");
          }
          else if ('f' == *format) {
            s[i].type = IS_DOUBLE;
            strcpy(s[i].specifier, "%lf");
          }
          else {
            abort();
          }
          break;
        case 'f':
          s[i].type = IS_FLOAT;
          strcpy(s[i].specifier, "%f");
          break;
        case 'b':
          s[i].type = IS_BOOL;
          break;
        case 'F':
          s[i].type = IS_FUNPTR;
          break;
        case 'c':
          s[i].type = IS_INT; // promoted to int
          strcpy(s[i].specifier, "%c");
          break;
        default:
          ERR("Unsupported format specifier %c)\n", *format);
      }
      format ++; // eat up format specifier
      start = format - start_ptr;
      s[i].after_specifier_pos = start;
      i++;
    }
    format ++;
  }
  return s;
}


static struct specifier*
format_parse(char *format, int *n)
{
  format_analyze(format, n);
  return parse_format_specifiers(format, *n);
}


/*
 *
 *  To improve the clarity of json format string,
 *  it treats |  as ", and | can be escaped as \|
 *
 *  supported format strings:
 *
 *  |a|:|%s|  |a|:|abc|
 *  |a|:%S    |a|:null or |a|:|abc|
 *  |a|:%b    |a|:true |a|:false
 *  |a|:%d    |a|:10
 *
 */
int
json_vsnprintf(char * str, size_t len, char * fmt, va_list ap)
{
  int number_of_specifiers = 0;
  char * format = normalize_fmt(fmt);
  struct specifier * sp = format_parse(format, &number_of_specifiers);

  int i = 0;
  for (i = 0; i < number_of_specifiers; i++) {
    if (sp[i].type == IS_FUNPTR) {
      sp[i].funptr = va_arg(ap, extractor*);
    }
    else if (sp[i].has_print_size) {
      sp[i].print_size = (size_t)va_arg(ap, int);
    }
    switch(sp[i].type)
    {
      case IS_BOOL:
        sp[i].provider.b = va_arg(ap, int); // integer promotion
        break;
      case IS_INT:
        sp[i].provider.i = va_arg(ap, int);
        break;
      case IS_FLOAT:
        sp[i].provider.f = va_arg(ap, double); // double promotion
        break;
      case IS_DOUBLE:
        sp[i].provider.d = va_arg(ap, double);
        break;
      default:
        sp[i].provider.p = va_arg(ap, void *);
        break;
    }
  }

#define ASSIGN_IF_NOT_ZERO(lhs, exp)   if (lhs) { lhs = exp; }
  char * cur_ptr = str, * ep = NULL;
  int slen = 0, total_size = 0;
  for (i = 0; i < number_of_specifiers; i++) {
    slen = sp[i].end - sp[i].start;
    if (cur_ptr)
      memcpy(cur_ptr, format + sp[i].start, slen);
    //cur_ptr += slen;
    ASSIGN_IF_NOT_ZERO(cur_ptr, (cur_ptr + slen));
    //len -= slen;
    ASSIGN_IF_NOT_ZERO(len, (len - slen));
    total_size += slen;
    switch (sp[i].type)
    {
      case IS_STR:
      case IS_STR_NULLABLE:
        if (NULL == sp[i].provider.p) {
          if (IS_STR_NULLABLE == sp[i].type) {
            slen = snprintf(cur_ptr, len, "null");
          }
          else {
            *cur_ptr = '\0';
            slen = len;
          }
        }
        else {
          size_t new_len = 0, old_len;
          old_len = sp[i].has_print_size ? sp[i].print_size :
                    strlen((char *)sp[i].provider.p);
          ep = json_string_escape(&new_len, sp[i].provider.p, old_len);
          slen = snprintf(cur_ptr, len, sp[i].specifier, new_len, ep);
          if (new_len != old_len) free(ep);
        }
        break;
      case IS_BOOL:
        if (sp[i].provider.b)
          slen = snprintf(cur_ptr, len, "true");
        else
          slen = snprintf(cur_ptr, len, "false");
        break;
      case IS_INT:
        slen = snprintf(cur_ptr, len,  sp[i].specifier, sp[i].provider.i);
        break;
      case IS_FLOAT:
        slen = snprintf(cur_ptr, len, sp[i].specifier, sp[i].provider.f);
        break;
      case IS_DOUBLE:
        slen = snprintf(cur_ptr, len, sp[i].specifier, sp[i].provider.d);
        break;
      case IS_FUNPTR:
        slen = (sp[i].funptr)(cur_ptr, len, sp[i].provider.p);
        break;
      default:
        ERR("unexpected case\n");
    }
    //cur_ptr += slen;
    ASSIGN_IF_NOT_ZERO(cur_ptr, (cur_ptr + slen));
    //len -= slen;
    ASSIGN_IF_NOT_ZERO(len, (len - slen));
    total_size += slen;
  }
  if (number_of_specifiers) {
    slen = snprintf(cur_ptr, len, "%s", format + sp[i - 1].after_specifier_pos);
    total_size += slen;
  }
  else {
    if (cur_ptr)
      strcpy(cur_ptr, format);
    total_size = strlen(format);
  }
  free(format);
  free(sp);
  return total_size;
}

int
json_asprintf(char **buf, char *json_fmt, ...)
{
  va_list ap;
  va_start(ap, json_fmt);
  int ret = json_vsnprintf(NULL, 0, json_fmt, ap);
  va_end(ap);

  if (ret > 0) {
    char *b = malloc(ret + 1);
    * buf = b;
    va_start(ap, json_fmt);
    ret = json_vsnprintf(b, ret+1, json_fmt, ap);
    va_end(ap);
  }
  else
    *buf = NULL;
  return ret;
}

int
json_snprintf(char *buf, size_t len, char *json_fmt, ...)
{
  va_list ap;
  va_start(ap, json_fmt);
  int ret = json_vsnprintf(buf, len, json_fmt, ap);
  va_end(ap);

  if (buf) {
    jsmn_parser parser;
    jsmn_init(&parser);
    int num_tok = jsmn_parse(&parser, buf, ret, NULL, 0);
    if (num_tok < 0) {
      ERR("illegal json %.*s", ret, buf);
    }
  }
  return ret;
}
