#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *
json_escape_string (size_t * new_len, char * input, size_t len)
{
  int extra_bytes = 0;
  char * const start = input, * const end = input + len;
  char * output_start = NULL, * output = NULL;
  char * escaped = NULL, buf[8] = "\\u00";

  /*
   * 1st iteration, output is NULL and count extra_bytes needed for escaping
   * 2st iteration, output is not NULL, and does escaping.
   */
  second_iter:
  for (char * s = start; s < end; s++) {
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
        if (NULL == output_start) continue;

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
  *new_len = len + extra_bytes;
  if (0 == extra_bytes) { // no need to escape
    return start;
  }
  else {
    output_start = (char *)malloc(*new_len);
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
  if(0xD800 <=v && v<= 0xDFFF) // surragates
    return false;
  return true;
}

//namespace utf8 {
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

// See RFC 3629
// Based on: http://www.w3.org/International/questions/qa-forms-utf-8
static uint32_t
next(char ** p, char * e, bool html)
{
  if(*p==e)
    return utf_illegal;

  unsigned char lead = **p;
  (*p)++;

  // First byte is fully validated here
  int trail_size = utf8_trail_length(lead);

  if(trail_size < 0)
    return utf_illegal;

  //
  // Ok as only ASCII may be of size = 0
  // also optimize for ASCII text
  //
  if(trail_size == 0) {
    if(!html || (lead >= 0x20 && lead!=0x7F) || lead==0x9 || lead==0x0A || lead==0x0D)
      return lead;
    return utf_illegal;
  }

  uint32_t c = lead & ((1<<(6-trail_size))-1);

  // Read the rest
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

  // Check code point validity: no surrogates and
  // valid range
  if(!utf_valid(c))
    return utf_illegal;

  // make sure it is the most compact representation
  if(utf8_width(c)!=trail_size + 1)
    return utf_illegal;

  if(html && c<0xA0)
    return utf_illegal;
  return c;
} // valid


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
  //struct utf8_seq out={0};
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
    if(	('0'<= c && c<='9') || ('A'<= c && c<='F') || ('a'<= c && c<='f') )
      continue;

    return false;
  }
  unsigned v;
  sscanf(buf,"%x",&v);
  *x=v;
  *str_p = str + 4;
  return true;
}

int
json_unescape_string (char ** new_str, size_t * new_len,
                      char * buf, size_t len)
{
  unsigned char c;
  char * const start = buf, * const buf_end = buf + len;
  char * out_start = NULL, * d = NULL;

  enum state {
    TESTING = 1,
    ALLOCATING,
    UNESCAPING,
  } state = TESTING;

second_iter:
  for (buf = start; buf < buf_end;) {
    c = * buf;
    buf ++;

    if('\\' == c) {
      if (TESTING == state) {
        state = ALLOCATING;
        break; // break the while loop
      }

      if (buf == buf_end) {
        //input is not a well-formed json string
        goto return_err;
      }

      c = * buf ;
      buf ++;

      switch(c) {
        case	'"':
        case	'\\':
        case	'/':
          if (UNESCAPING == state) {
            *d = c;
            d++;
          }
          break;
        case	'b': if (UNESCAPING == state) { d[0] = '\b'; d ++; } break;
        case	'f': if (UNESCAPING == state) { d[0] = '\f'; d ++; } break;
        case	'n': if (UNESCAPING == state) { d[0] = '\n'; d ++; } break;
        case	'r': if (UNESCAPING == state) { d[0] = '\r'; d ++; } break;
        case	't': if (UNESCAPING == state) { d[0] = '\t'; d ++; } break;
        case	'u':
        {
          // don't support utf16
          uint16_t x;
          if (!read_4_digits(&buf, buf_end, &x))
            goto return_err;
          struct utf8_seq s = { {0}, 0 };
          utf8_encode(x, &s);
          if (UNESCAPING == state) {
            for (unsigned i = 0; i < s.len; ++i, d++)
              * d = s.c[i];
          }
        }
          break;
        default:
          if(0<= c && c <= 0x1F) /* report errors */
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
    {
      if (!utf8_validate(out_start, d))
        goto return_err;
      else
      {
        *new_str = out_start;
        *new_len = d - out_start;
        goto return_ok;
      }
    }
    case ALLOCATING:
    {
      out_start = calloc(1, len);
      d = out_start;
      state = UNESCAPING;
      goto second_iter;
    }
    default:
      break;
  }

return_err:
  return 0;

return_ok:
  return 1;

}
