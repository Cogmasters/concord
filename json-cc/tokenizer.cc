#ifndef ORCA_JSON_AMALGAMATION
#include "cee.h"
#include "json.h"
#include "utf8.h"
#include <stdlib.h>
#include "tokenizer.h"
#endif

namespace cee {
  namespace json {
    
static bool check(char * buf, char * s, char **ret)
{
  char * next = buf;
  
  for (next = buf; *s && *next == *s; next++, s++);
  if (*s==0) {
    *ret = next;
    return true;
  }
  else {
    *ret = buf;
  	return false;
  }
  return false;
}

static bool read_4_digits(struct tokenizer * t, uint16_t *x)
{
  char *buf;
  if (t->buf_end - t->buf >= 5) {
    buf = t->buf;
  } 
  else
    return false;
  int i;
  for(i=0; i<4; i++) {
    char c=buf[i];
    if(	('0'<= c && c<='9') || ('A'<= c && c<='F') || ('a'<= c && c<='f') ) {
      continue;
    }
    return false;
  }
  unsigned v;
  sscanf(buf,"%x",&v);
  *x=v;
  return true;
}

static bool parse_string(struct tokenizer * t) {
  char c;
  // we should use a more efficient stretchy buffer here
  t->str = str::mk_e(128, "");
  
  if (t->buf == t->buf_end)
    return false;
  c=t->buf[0];
  t->buf++;
  
  if (c != '"') return false;
  bool second_surragate_expected=false;
  uint16_t first_surragate = 0;
  
  for(;;) {
    if(t->buf == t->buf_end)
      return false;
    c = t->buf[0];
    t->buf ++;
    
    if(second_surragate_expected && c!='\\')
      return false;
    if(0<= c && c <= 0x1F)
      return false;
    if(c=='"')
      break;
    if(c=='\\') {
      if(t->buf == t->buf_end)
        return false;
      if(second_surragate_expected && c!='u')
        return false;
      switch(c) {
      case	'"':
      case	'\\':
      case	'/':
        t->str = str::add(t->str, c);
        break;
      case	'b': t->str = str::add(t->str, '\b'); break;
      case	'f': t->str = str::add(t->str, '\f'); break;
      case	'n': t->str = str::add(t->str, '\n'); break;
      case	'r': t->str = str::add(t->str, '\r'); break; 
      case	't': t->str = str::add(t->str, '\t'); break;
      case	'u': 
        {
          // don't support utf16
          uint16_t x;
          if (!read_4_digits(t, &x)) 
            return false;
        	struct utf8_seq s = { 0 };
          utf8_encode(x, &s);
          t->str = str::ncat(t->str, s.c, s.len);
        }
        break;
      default:
        return false;
      }
    }
    else {
      t->str = str::add(t->str, c);
    }
  }
  if(!utf8_validate(t->str->_, str::end(t->str)))
    return false;
  return true;
}


static bool parse_number(struct tokenizer *t) {
  int x = sscanf(t->buf, "%lf", &t->real);
  return x == 1;
}

enum token next_token(struct tokenizer * t) {
  for (;;t->buf++) {
    if (t->buf == t->buf_end)
      return tock_eof;
    char c = t->buf[0];
    t->buf ++;
    switch (c) {
      case '[':
      case '{':
      case ':':
      case ',':
      case '}':
      case ']':
        return (enum token)c;
      case ' ':
      case '\t':
      case '\r':
        break;
      case '\n':
        t->line++;
        break;
      case '"':
        t->buf --;
        if(parse_string(t))
          return tock_str;
        return tock_err;
      case 't':
        if(check(t->buf, "rue", &t->buf))
          return tock_true;
        return tock_err;
      case 'n':
        if(check(t->buf, "ull", &t->buf))
          return tock_null;
        return tock_err;
      case 'f':
        if(check(t->buf, "alse", &t->buf))
          return tock_false;
        return tock_err;
      case '-':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        t->buf --;
        if(parse_number(t))
          return tock_number;
        return tock_err;
      case '/':
        if(check(t->buf + 1, "/", &t->buf)) {
          for (;t->buf < t->buf_end && (c = t->buf[0]) && c != '\n'; t->buf++);

          if(c=='\n')
            break;
          return tock_eof;
        }
        return tock_err;
      default:
        return tock_err;
    }
  }
}
  }
}