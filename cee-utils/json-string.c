#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "json-actor.h"

char *
json_string_escape(size_t *output_len_p, char *input, size_t input_len)
{
  int extra_bytes = 0;
  char * const input_start = input, * const input_end = input + input_len;
  char * output_start = NULL, * output = NULL;
  char * escaped = NULL, buf[8] = "\\u00";
  char * s;

  /*
   * 1st iteration, output is NULL and count extra_bytes needed for escaping
   * 2st iteration, output is not NULL, and does escaing.
   */
  second_iter:
  for (s = input_start; s < input_end; s++) {
    escaped = NULL;
    unsigned char c = * s;
    switch (c) {
      case 0x22: escaped = "\\\""; break;
      case 0x5C: escaped = "\\\\"; break;
      case '\b': escaped = "\\b"; break;
      case '\f': escaped = "\\f"; break;
      case '\n': escaped = "\\n"; break;
      case '\r': escaped = "\\r"; break;
      case '\t': escaped = "\\t"; break;
      default:
        if(c<=0x1F) {
          static char const tohex[]="0123456789abcdef";
          buf[4]=tohex[c >>  4];
          buf[5]=tohex[c & 0xF];
          buf[6]=0;
          escaped = buf;
        }
    }
    if (escaped) {
      int i;
      for (i = 0; escaped[i]; i++) {
        if (NULL == output_start)
          /* count how many extra bytes are needed */
          continue;

        *output = escaped[i];
        output ++;
      }
      extra_bytes += (i - 1 /* c */);
    }
    else if (output_start) {
      *output = c;
      output++;
    }
  }

  if (output_start)
    return output_start;

  /*
   * 1 iteration reach here
   */
  *output_len_p = input_len + extra_bytes;
  if (0 == extra_bytes) { /* no need to escape */
    return input_start;
  }
  else {
    output_start = (char *)malloc(*output_len_p);
    output = output_start;
    extra_bytes = 0;
    goto second_iter;
  }
}

static const uint32_t utf_illegal = 0xFFFFFFFFu;
static bool
utf_valid(uint32_t v)
{
  if(v>0x10FFFF)
    return false;
  if(0xD800 <=v && v<= 0xDFFF) /* surrogates */
    return false;
  return true;
}

static
bool utf8_is_trail(char ci)
{
  unsigned char c=ci;
  return (c & 0xC0)==0x80;
}

static int
utf8_trail_length(unsigned char c)
{
  if(c < 128)
    return 0;
  if(c < 194)
    return -1;
  if(c < 224)
    return 1;
  if(c < 240)
    return 2;
  if(c <=244)
    return 3;
  return -1;
}

static int
utf8_width(uint32_t value)
{
  if(value <=0x7F) {
    return 1;
  }
  else if(value <=0x7FF) {
    return 2;
  }
  else if(value <=0xFFFF) {
    return 3;
  }
  else {
    return 4;
  }
}

/* See RFC 3629
   Based on: http://www.w3.org/International/questions/qa-forms-utf-8
*/
static uint32_t
next(char ** p, char * e, bool html)
{
  if(*p==e)
    return utf_illegal;

  unsigned char lead = **p;
  (*p)++;

  /* First byte is fully validated here */
  int trail_size = utf8_trail_length(lead);

  if(trail_size < 0)
    return utf_illegal;

  /*
    Ok as only ASCII may be of size = 0
    also optimize for ASCII text
  */
  if(trail_size == 0) {
    if(!html || (lead >= 0x20 && lead!=0x7F) || lead==0x9 || lead==0x0A || lead==0x0D)
      return lead;
    return utf_illegal;
  }

  uint32_t c = lead & ((1<<(6-trail_size))-1);

  /* Read the rest */
  unsigned char tmp;
  switch(trail_size) {
    case 3:
      if(*p==e)
        return utf_illegal;
      tmp = **p;
      (*p)++;
      if (!utf8_is_trail(tmp))
        return utf_illegal;
      c = (c << 6) | ( tmp & 0x3F);
    case 2:
      if(*p==e)
        return utf_illegal;
      tmp = **p;
      (*p)++;
      if (!utf8_is_trail(tmp))
        return utf_illegal;
      c = (c << 6) | ( tmp & 0x3F);
    case 1:
      if(*p==e)
        return utf_illegal;
      tmp = **p;
      (*p)++;
      if (!utf8_is_trail(tmp))
        return utf_illegal;
      c = (c << 6) | ( tmp & 0x3F);
  }

  /* Check code point validity: no surrogates and
     valid range */
  if(!utf_valid(c))
    return utf_illegal;

  /* make sure it is the most compact representation */
  if(utf8_width(c)!=trail_size + 1)
    return utf_illegal;

  if(html && c<0xA0)
    return utf_illegal;
  return c;
} /* valid */


static bool
utf8_validate(char * p, char * e)
{
  while(p!=e)
    if(next(&p, e, false)==utf_illegal)
      return false;
  return true;
}


struct utf8_seq {
  char c[4];
  unsigned len;
};

static void
utf8_encode(uint32_t value, struct utf8_seq *out)
{
  /*struct utf8_seq out={0}; */
  if(value <=0x7F) {
    out->c[0]=value;
    out->len=1;
  }
  else if(value <=0x7FF) {
    out->c[0]=(value >> 6) | 0xC0;
    out->c[1]=(value & 0x3F) | 0x80;
    out->len=2;
  }
  else if(value <=0xFFFF) {
    out->c[0]=(value >> 12) | 0xE0;
    out->c[1]=((value >> 6) & 0x3F) | 0x80;
    out->c[2]=(value & 0x3F) | 0x80;
    out->len=3;
  }
  else {
    out->c[0]=(value >> 18) | 0xF0;
    out->c[1]=((value >> 12) & 0x3F) | 0x80;
    out->c[2]=((value >> 6) & 0x3F) | 0x80;
    out->c[3]=(value & 0x3F) | 0x80;
    out->len=4;
  }
}

static bool
read_4_digits(char ** str_p, char * const buf_end, uint16_t *x)
{
  char * str = * str_p;
  if (buf_end - str < 4)
    return false;

  char buf[5] = { 0 };
  int i;
  for(i=0; i<4; i++) {
    char c=str[i];
    buf[i] = c;
    if(isxdigit(c))
      continue;

    return false;
  }
  unsigned v;
  sscanf(buf,"%x",&v);
  *x=v;
  *str_p = str + 4;
  return true;
}

static int utf16_is_first_surrogate(uint16_t x)
{
  return 0xD800 <=x && x<= 0xDBFF;
}

static int utf16_is_second_surrogate(uint16_t x)
{
  return 0xDC00 <=x && x<= 0xDFFF;
}

static uint32_t utf16_combine_surrogate(uint16_t w1,uint16_t w2)
{
  return ((((uint32_t)w1 & 0x3FF) << 10) | (w2 & 0x3FF)) + 0x10000;
}

static void * append (uint32_t x, char *d)
{
  unsigned i;
  struct utf8_seq seq = { {0}, 0 };
  utf8_encode(x, &seq);
  for (i = 0; i < seq.len; ++i, d++)
    *d = seq.c[i];
  return d;
}

int
json_string_unescape(char **output_p, size_t *output_len_p,
                     char *input, size_t input_len)
{
  unsigned char c;
  char * const input_start = input, * const input_end = input + input_len;
  char * out_start = NULL, * d = NULL, * s = NULL;
  uint16_t first_surrogate;
  int second_surrogate_expected;


  enum state {
    TESTING = 1,
    ALLOCATING,
    UNESCAPING,
  } state = TESTING;

second_iter:
  first_surrogate = 0;
  second_surrogate_expected = 0;
  for (s = input_start; s < input_end;) {
    c = * s;
    s ++;

    if (second_surrogate_expected && c != '\\')
      goto return_err;

    if (0<= c && c <= 0x1F)
      goto return_err;

    if('\\' == c) {
      if (TESTING == state) {
        state = ALLOCATING;
        break; /* break the while loop */
      }

      if (s == input_end) {
        /*input is not a well-formed json string*/
        goto return_err;
      }

      c = * s;
      s ++;

      if (second_surrogate_expected && c != 'u')
        goto return_err;

      switch(c) {
      case	'"':
      case	'\\':
      case	'/':
          *d = c; d++; break;
      case	'b': *d = '\b'; d ++;  break;
      case	'f': *d = '\f'; d ++;  break;
      case	'n': *d = '\n'; d ++;  break;
      case	'r': *d = '\r'; d ++;  break;
      case	't': *d = '\t'; d ++;  break;
      case	'u': {
          uint16_t x;
          if (!read_4_digits(&s, input_end, &x))
            goto return_err;
          if (second_surrogate_expected) {
            if (!utf16_is_second_surrogate(x))
              goto return_err;
            d = append(utf16_combine_surrogate(first_surrogate, x), d);
            second_surrogate_expected = 0;
          } else if (utf16_is_first_surrogate(x)) {
            second_surrogate_expected = 1;
            first_surrogate = x;
          } else {
            d = append(x, d);
          }
          break; }
      default:
          goto return_err;
      }
    }
    else if (UNESCAPING == state) {
      *d = c;
      d++;
    }
  }

  switch (state) {
  case UNESCAPING:
      if (!utf8_validate(out_start, d))
        goto return_err;
      else
      {
        *output_p = out_start;
        *output_len_p = d - out_start;
        return 1;
      }
  case ALLOCATING:
      out_start = calloc(1, input_len);
      d = out_start;
      state = UNESCAPING;
      goto second_iter;
  case TESTING:
      *output_p = input_start;
      *output_len_p = input_len;
      return 1;
  default:
      break;
  }

return_err:
  if (UNESCAPING == state)
    free(out_start);
  return 0;
}

/* Converts a hex character to its integer value */
static char from_hex(char ch) {
  return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

/* Converts an integer value to its hex character*/
static char to_hex(char code) {
  static char hex[] = "0123456789abcdef";
  return hex[code & 15];
}

/* Returns a url-encoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char *url_encode(char *str) {
  char *pstr = str, *buf = malloc(strlen(str) * 3 + 1), *pbuf = buf;
  while (*pstr) {
    if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~')
      *pbuf++ = *pstr;
    else if (*pstr == ' ') {
      /**pbuf++ = '+';*/
      *pbuf++ = '%', *pbuf++ = '2', *pbuf++ = '0';
    }
    else
      *pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
    pstr++;
  }
  *pbuf = '\0';
  return buf;
}

/* Returns a url-decoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char *url_decode(char *str) {
  char *pstr = str, *buf = malloc(strlen(str) + 1), *pbuf = buf;
  while (*pstr) {
    if (*pstr == '%') {
      if (pstr[1] && pstr[2]) {
        *pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);
        pstr += 2;
      }
    } else if (*pstr == '+') {
      *pbuf++ = ' ';
    } else {
      *pbuf++ = *pstr;
    }
    pstr++;
  }
  *pbuf = '\0';
  return buf;
}

char * url_encode_ext(char * pos, size_t size)
{
  char * str = malloc(size+1);
  memcpy(str, pos, size);
  str[size] = '\0';
  char * encoded = url_encode(str);
  free(str);
  return encoded;
}

char * url_decode_ext(char * pos, size_t size)
{
  char * str = malloc(size+1);
  memcpy(str, pos, size);
  str[size] = '\0';
  char * decoded = url_decode(str);
  free(str);
  return decoded;
}
