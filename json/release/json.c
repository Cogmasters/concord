#ifndef ORCA_JSON_ONE
#define ORCA_JSON_ONE
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include "cee.h"
 
#ifndef ORCA_JSON_H
#define ORCA_JSON_H
#ifndef ORCA_JSON_AMALGAMATION
#include "cee.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#endif

#define MAX_JSON_DEPTH 500

struct json_null {};
struct json_undefined {};

enum json_type {
  is_undefined,	///< Undefined value
  is_null,	///< null value
  is_boolean,	///< boolean value
  is_number,	///< numeric value
  is_string,	///< string value
  is_object,	///< object value 
  is_array	///< array value
};

struct json {
	enum json_type t;
  union {
    struct cee_singleton * null;
    struct cee_singleton * undefined;
    struct cee_singleton * boolean;
    struct cee_box       * number;
    struct cee_str       * string;
    struct cee_vect      * array;
    struct cee_map       * object;
  } value;
};

enum json_format {
  compact = 0,
  readable = 1
};

extern enum json_type json_type  (struct json *);
extern bool json_is_undefined (struct json *);
extern bool json_is_null (struct json *);
extern bool json_to_bool (struct json *);

extern struct json * json_find (struct json *, char *);
extern struct json * json_get(struct json *, char *, struct json * def);

extern bool json_save (struct json *, FILE *, int how);
extern struct json * json_load_from_file (FILE *, bool force_eof, int * error_at_line);
extern struct json * json_load_from_buffer (int size, char *, int line);
extern int json_cmp (struct json *, struct json *);

extern struct cee_vect * json_to_array (struct json *);
extern struct cee_map * json_to_object (struct json *);
extern struct cee_box * json_to_number (struct json *);
extern struct cee_str * json_to_string (struct json *);

extern struct json * json_true();
extern struct json * json_false();
extern struct json * json_undefined ();
extern struct json * json_null ();
extern struct json * json_object();
extern struct json * json_number (double d);
extern struct json * json_string(struct cee_str * s);
extern struct json * json_array(int s);

extern void json_object_set (struct json *, char *, struct json *);
extern void json_object_set_bool (struct json *, char *, bool);
extern void json_object_set_string (struct json *, char *, char *);
extern void json_object_set_number (struct json *, char *, double);

extern void json_array_append (struct json *, struct json *);
extern void json_array_append_bool (struct json *, bool);
extern void json_array_append_string (struct json *, char *);
extern void json_array_append_number (struct json *, double);

extern size_t json_snprintf(char * buf, size_t size, struct json *, 
                                 enum json_format);

extern bool json_parse(char * buf, uintptr_t len, 
                       struct json **out, bool force_eof,
                       int *error_at_line);

#endif // ORCA_JSON_H 
#ifndef ORCA_JSON_TOK_H
#define ORCA_JSON_TOK_H
enum token {
  tock_eof = 255,
  tock_err,
  tock_str,
  tock_number,
  tock_true,
  tock_false,
  tock_null
};

struct tokenizer {
  int line;
  char * buf;
  char * buf_end;
  struct cee_str * str;
  double real;
};

extern enum token json_next_token(struct tokenizer * t);
#endif // ORCA_JSON_TOK_H
 
/* convert to C */
///////////////////////////////////////////////////////////////////////////////
//                                                                             
//  Copyright (C) 2008-2012  Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>     
//                                                                             
//  See accompanying file COPYING.TXT file for licensing details.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ORCA_JSON_UTF8_H
#define ORCA_JSON_UTF8_H
#ifndef ORCA_JSON_AMALGAMATION
#include <stdint.h>
#include <stdbool.h>
#endif

static const uint32_t utf_illegal = 0xFFFFFFFFu;
static bool utf_valid(uint32_t v)
{
  if(v>0x10FFFF)
    return false;
  if(0xD800 <=v && v<= 0xDFFF) // surragates
    return false;
  return true;
}

//namespace utf8 {
static bool utf8_is_trail(char ci)
{
  unsigned char c=ci;
  return (c & 0xC0)==0x80;
}


static int utf8_trail_length(unsigned char c) 
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

static int utf8_width(uint32_t value)
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
static uint32_t next(char ** p, char * e, bool html)
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


/*
bool validate_with_count(char * p, char * e, size_t *count,bool html)
{
  while(p!=e) {
    if(next(p,e,html)==utf_illegal)
      return false;
    (*count)++;
  }
  return true;
}
*/

static bool utf8_validate(char * p, char * e)
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

static void utf8_encode(uint32_t value, struct utf8_seq *out) {
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
#endif 
struct json * json_true () {
  static char b[CEE_SINGLETON_SIZE];
  return (struct json *) cee_singleton_init ((uintptr_t)is_boolean, b);
}
struct json * json_false () {
  static char b[CEE_SINGLETON_SIZE];
  return (struct json *) cee_singleton_init ((uintptr_t)is_boolean, b);
}
struct json * json_bool(bool b) {
  if (b)
    return json_true();
  else
    return json_false();
}
struct json * json_undefined () {
  static char b[CEE_SINGLETON_SIZE];
  return (struct json *)cee_singleton_init ((uintptr_t)is_undefined, b);
}
struct json * json_null () {
  static char b[CEE_SINGLETON_SIZE];
  return (struct json *)cee_singleton_init ((uintptr_t)is_null, b);
}
struct cee_map * json_to_object (struct json * p) {
  if (p->t == is_object) {
    return p->value.object;
  }
  return NULL;
}
struct cee_vect * json_to_array (struct json * p) {
  if (p->t == is_array) {
    return p->value.array;
  }
  return NULL;
}
struct cee_str * json_to_string (struct json * p) {
  if (p->t == is_string) {
    return p->value.string;
  }
  return NULL;
}
struct cee_box * json_to_number (struct json * p) {
  if (p->t == is_number) {
    return p->value.number;
  }
  return NULL;
}
bool json_to_bool (struct json * p) {
  if (p == json_true())
    return true;
  else if (p == json_false())
    return false;
  cee_segfault();
  return false;
}
struct json * json_number (double d) {
  struct cee_box *p = cee_box_double (d);
  struct cee_tagged * t = cee_tag (is_number, p);
  return (struct json *)t;
}
struct json * json_string(struct cee_str *s) {
  struct cee_tagged * t = cee_tag(is_string, s);
  return (struct json *)t;
}
struct json * json_array(int s) {
  struct cee_vect * v = cee_vect (s);
  struct cee_tagged * t = cee_tag(is_array, v);
  return (struct json *)t;
}
struct json * json_object() {
  struct cee_map * m = cee_map ((cee_cmp_fun)strcmp);
  struct cee_tagged * t = cee_tag(is_object, m);
  return (struct json *)t;
}
void json_object_set(struct json * j, char * key, struct json * v) {
  struct cee_map * o = json_to_object(j);
  if (!o)
    cee_segfault();
  cee_map_add(o, cee_str("%s", key), v);
}
void json_object_set_bool(struct json * j, char * key, bool b) {
  struct cee_map * o = json_to_object(j);
  if (!o)
    cee_segfault();
  cee_map_add(o, cee_str("%s", key), json_bool(b));
}
void json_object_set_string (struct json * j, char * key, char * str) {
  struct cee_map * o = json_to_object(j);
  if (!o)
    cee_segfault();
  cee_map_add(o, cee_str("%s", key), json_string(cee_str("%s", str)));
}
void json_object_set_number (struct json * j, char * key, double real) {
  struct cee_map * o = json_to_object(j);
  if (!o)
    cee_segfault();
  cee_map_add(o, cee_str("%s", key), json_number(real));
}
void json_array_append (struct json * j, struct json *v) {
  struct cee_vect * o = json_to_array(j);
  if (!o)
    cee_segfault();
  cee_vect_append(o, v);
}
void json_array_append_bool (struct json * j, bool b) {
  struct cee_vect * o = json_to_array(j);
  if (!o)
    cee_segfault();
  cee_vect_append(o, json_bool(b));
}
void json_array_append_string (struct json * j, char * x) {
  struct cee_vect * o = json_to_array(j);
  if (!o)
    cee_segfault();
  cee_vect_append(o, json_string(cee_str("%s", x)));
}
struct json * json_load_from_file (FILE * f, bool force_eof,
                                   int * error_at_line) {
  int fd = fileno(f);
  struct stat buf;
  fstat(fd, &buf);
  off_t size = buf.st_size;
  char * b = malloc(size);
  if (!b)
    cee_segfault();
  int line = 0;
  struct json * j;
  if (!json_parse(b, size, &j, true, &line)) {
  }
  return j;
}
bool json_save(struct json * j, FILE *f, int how) {
  size_t s = json_snprintf(NULL, 0, j, how);
  char * p = malloc(s+1);
  json_snprintf(p, s+1, j, how);
  if (fwrite(p, s+1, 1, f) != 1) {
    fprintf(stderr, "%s", strerror(errno));
    return false;
  }
  return true;
}
enum state_type {
  st_init = 0,
  st_object_or_array_or_value_expected = 0 ,
  st_object_key_or_close_expected,
  st_object_colon_expected,
  st_object_value_expected,
  st_object_close_or_comma_expected,
  st_array_value_or_close_expected,
  st_array_close_or_comma_expected,
  st_error,
  st_done
} state_type;
static const uintptr_t json_max_depth = 512;
bool json_parse(char * buf, uintptr_t len, struct json **out, bool force_eof,
                int *error_at_line)
{
  struct tokenizer tock = {0};
  tock.buf = buf;
  tock.buf_end = buf + len;
  *out = NULL;
  enum state_type state = st_init;
  struct cee_str * key = NULL;
  struct cee_stack * sp = cee_stack_e(cee_dp_noop, json_max_depth);
  struct cee_tuple * top = NULL;
  struct cee_tuple * result = NULL;
  cee_stack_push(sp, cee_tuple_e((enum cee_del_policy [2]){cee_dp_noop, cee_dp_noop}, (void *)st_done, NULL));
  while(!cee_stack_empty(sp) && !cee_stack_full(sp) &&
        state != st_error && state != st_done) {
    if (result) {
      cee_del(result);
      result = NULL;
    }
    int c= json_next_token(&tock);
    top = (struct cee_tuple *)cee_stack_top(sp, 0);
    switch(state) {
    case st_object_or_array_or_value_expected:
      if(c=='[') {
        top->_[1]=json_array(10);
        state=st_array_value_or_close_expected;
      }
      else if(c=='{') {
        top->_[1]=json_object();
        state=st_object_key_or_close_expected;
      }
      else if(c==tock_str) {
        top->_[1]=json_string(tock.str);
        tock.str = NULL;
        state=(enum state_type)(top->_[0]);
        { result = (struct cee_tuple *)cee_stack_pop(sp); };
      }
      else if(c==tock_true) {
        top->_[1]=json_true();
        state=(enum state_type)(top->_[0]);
        { result = (struct cee_tuple *)cee_stack_pop(sp); };
      }
      else if(c==tock_false) {
        top->_[1]=json_false();
        state=(enum state_type)(top->_[0]);
        { result = (struct cee_tuple *)cee_stack_pop(sp); };
      }
      else if(c==tock_null) {
        top->_[1]=json_null();
        state=(enum state_type)(top->_[0]);
        { result = (struct cee_tuple *)cee_stack_pop(sp); };
      }
      else if(c==tock_number) {
        top->_[1] = json_number (tock.real);
        state=(enum state_type)(top->_[0]);
        { result = (struct cee_tuple *)cee_stack_pop(sp); };
      }
      else
        state = st_error;
      break;
    case st_object_key_or_close_expected:
      if(c=='}') {
        state=(enum state_type)(top->_[0]);
        { result = (struct cee_tuple *)cee_stack_pop(sp); };
      }
      else if (c==tock_str) {
        key = tock.str;
        tock.str = NULL;
        state = st_object_colon_expected;
      }
      else
        state = st_error;
      break;
    case st_object_colon_expected:
      if(c!=':')
        state=st_error;
      else
        state=st_object_value_expected;
      break;
    case st_object_value_expected:
      {
        struct cee_map * obj = json_to_object(top->_[1]);
        if(c==tock_str) {
          cee_map_add(obj, key, json_string(tock.str));
          tock.str = NULL;
          state=st_object_close_or_comma_expected;
        }
        else if(c==tock_true) {
          cee_map_add(obj, key, json_true());
          state=st_object_close_or_comma_expected;
        }
        else if(c==tock_false) {
          cee_map_add(obj, key, json_false());
          state=st_object_close_or_comma_expected;
        }
        else if(c==tock_null) {
          cee_map_add(obj, key, json_null());
          state=st_object_close_or_comma_expected;
        }
        else if(c==tock_number) {
          cee_map_add(obj, key, json_number(tock.real));
          state=st_object_close_or_comma_expected;
        }
        else if(c=='[') {
          struct json * a = json_array(10);
          cee_map_add(obj, key, a);
          state=st_array_value_or_close_expected;
          cee_stack_push(sp, cee_tuple_e((enum cee_del_policy [2]){cee_dp_noop, cee_dp_noop}, (void *)st_object_close_or_comma_expected, a));
        }
        else if(c=='{') {
          struct json * o = json_object();
          cee_map_add(obj, key, o);
          state=st_object_key_or_close_expected;
          cee_stack_push(sp, cee_tuple_e((enum cee_del_policy [2]){cee_dp_noop, cee_dp_noop}, (void *)st_object_close_or_comma_expected, o));
        }
        else
          state=st_error;
      }
      break;
    case st_object_close_or_comma_expected:
      if(c==',')
        state=st_object_key_or_close_expected;
      else if(c=='}') {
        state=(enum state_type)(top->_[0]);
        { result = (struct cee_tuple *)cee_stack_pop(sp); };
      }
      else
        state=st_error;
      break;
    case st_array_value_or_close_expected:
      {
        if(c==']') {
          state=(enum state_type)(top->_[0]);
          { result = (struct cee_tuple *)cee_stack_pop(sp); };
          break;
        }
        struct cee_vect * ar = json_to_array(top->_[1]);
        if(c==tock_str) {
          cee_vect_append(ar, json_string(tock.str));
          state=st_array_close_or_comma_expected;
        }
        else if(c==tock_true) {
          cee_vect_append(ar, json_true());
          state=st_array_close_or_comma_expected;
        }
        else if(c==tock_false) {
          cee_vect_append(ar, json_false());
          state=st_array_close_or_comma_expected;
        }
        else if(c==tock_null) {
          cee_vect_append(ar, json_null());
          state=st_array_close_or_comma_expected;
        }
        else if(c==tock_number) {
          cee_vect_append(ar, json_number(tock.real));
          state=st_array_close_or_comma_expected;
        }
        else if(c=='[') {
          struct json * a = json_array(10);
          state=st_array_value_or_close_expected;
          cee_stack_push(sp, cee_tuple_e((enum cee_del_policy [2]){cee_dp_noop, cee_dp_noop}, (void *)st_array_close_or_comma_expected, a));
        }
        else if(c=='{') {
          struct json * o = json_object();
          state=st_object_key_or_close_expected;
          cee_stack_push(sp, cee_tuple_e((enum cee_del_policy [2]){cee_dp_noop, cee_dp_noop}, (void *)st_array_close_or_comma_expected, o));
        }
        else
          state=st_error;
        break;
      }
    case st_array_close_or_comma_expected:
      if(c==']') {
        state=(enum state_type)(top->_[0]);
        { result = (struct cee_tuple *)cee_stack_pop(sp); };
      }
      else if(c==',')
        state=st_array_value_or_close_expected;
      else
        state=st_error;
      break;
    case st_done:
    case st_error:
      break;
    };
  }
  cee_del(sp);
  if(state==st_done) {
    if(force_eof) {
      if(json_next_token(&tock)!=tock_eof) {
        *error_at_line=tock.line;
        return false;
      }
    }
    *out = (struct json *)(result->_[1]);
    cee_del(result);
    return true;
  }
  *error_at_line=tock.line;
  return false;
}
struct counter {
  uintptr_t next;
  struct cee_vect * array;
  struct cee_map * object;
  char tabs;
  char more_siblings;
};
static struct counter * push(uintptr_t tabs, bool more_siblings,
                             struct cee_stack * sp, struct json * j) {
  struct counter * p = NULL;
  if (j == NULL) {
    p = cee_block(sizeof(struct counter));
    p->tabs = 0;
  }
  else {
    switch(j->t) {
      case is_object:
        {
          p = cee_block(sizeof(struct counter));
          struct cee_map * mp = json_to_object(j);
          p->array = cee_map_keys(mp);
          p->object = json_to_object(j);
          p->tabs = tabs;
          p->next = 0;
          p->more_siblings = 0;
        }
        break;
      case is_array:
        {
          p = cee_block(sizeof(struct counter));
          p->array = json_to_array(j);
          p->tabs = tabs;
          p->next = 0;
          p->more_siblings = 0;
        }
        break;
      default:
        {
          p = cee_block(sizeof(struct counter));
          p->array = NULL;
          p->tabs = tabs;
          p->next = 0;
          p->more_siblings = 0;
        }
        break;
    }
    p->more_siblings = more_siblings;
  }
  enum cee_del_policy o[2] = { cee_dp_del, cee_dp_noop };
  cee_stack_push(sp, cee_tuple_e(o, p, j));
  return p;
}
static void pad (uintptr_t * offp, char * buf, struct counter * cnt,
                 enum json_format f) {
  if (!f) return;
  uintptr_t offset = *offp;
  if (buf) {
    int i;
    for (i = 0; i < cnt->tabs; i++)
      buf[offset + i] = '\t';
  }
  offset += cnt->tabs;
  *offp = offset;
  return;
}
static void delimiter (uintptr_t * offp, char * buf, enum json_format f,
                       struct counter * cnt, char c)
{
  uintptr_t offset = *offp;
 if (!f) {
    if (buf) buf[offset] = c;
    offset ++;
    *offp = offset;
    return;
  }
  switch (c) {
    case '[':
    case '{':
      pad(offp, buf, cnt, f);
      if (buf) {
       buf[offset] = c;
        buf[offset+1] = '\n';
      }
      offset +=2;
      break;
    case ']':
    case '}':
      if (buf) buf[offset] = '\n';
      offset ++;
      pad(&offset, buf, cnt, f);
      if (buf) buf[offset] = c;
      offset ++;
      if (buf) buf[offset] = '\n';
      offset ++;
      break;
    case ':':
      if (buf) {
        buf[offset] = ' ';
        buf[offset+1] = ':';
        buf[offset+2] = '\t';
      }
      offset +=3;
      break;
    case ',':
      if (buf) {
        buf[offset] = ',';
        buf[offset+1] = '\n';
      }
      offset +=2;
      break;
  }
  *offp = offset;
}
static void str_append(char * out, uintptr_t *offp, char *begin, unsigned len) {
  uintptr_t offset = *offp;
  if (out) out[offset] = '"';
  offset ++;
  char *i,*last;
  char buf[8] = "\\u00";
  for(i=begin,last = begin;i < begin + len;) {
    char *addon = 0;
    unsigned char c=*i;
    switch(c) {
    case 0x22: addon = "\\\""; break;
    case 0x5C: addon = "\\\\"; break;
    case '\b': addon = "\\b"; break;
    case '\f': addon = "\\f"; break;
    case '\n': addon = "\\n"; break;
    case '\r': addon = "\\r"; break;
    case '\t': addon = "\\t"; break;
    default:
      if(c<=0x1F) {
        static char const tohex[]="0123456789abcdef";
        buf[4]=tohex[c >> 4];
        buf[5]=tohex[c & 0xF];
        buf[6]=0;
        addon = buf;
      }
    };
    if(addon) {
      if (out) memcpy(out+offset, last, i-last);
      offset += i-last;
      if (out) memcpy(out+offset, addon, strlen(addon));
      offset += strlen(addon);
      i++;
      last = i;
    }
    else {
      i++;
    }
  }
  if (out) memcpy(out+offset, last, i-last);
  offset += i-last;
  if (out) out[offset] = '"';
  offset++;
  *offp = offset;
}
size_t json_snprintf (char * buf, size_t size, struct json * j,
                      enum json_format f) {
  struct cee_tuple * cur;
  struct json * cur_json;
  struct counter * ccnt;
  uintptr_t incr = 0;
  struct cee_stack * sp = cee_stack_e(cee_dp_noop, 500);
  push (0, false, sp, j);
  uintptr_t offset = 0;
  while (!cee_stack_empty(sp) && !cee_stack_full(sp)) {
    cur = cee_stack_top(sp, 0);
    cur_json = (struct json *)(cur->_[1]);
    ccnt = (struct counter *)(cur->_[0]);
    switch(cur_json->t) {
      case is_null:
        {
          pad(&offset, buf, ccnt, f);
          if (buf)
            memcpy(buf + offset, "null", 4);
          offset += 4;
          if (ccnt->more_siblings)
            delimiter(&offset, buf, f, ccnt, ',');
          cee_del(cee_stack_pop(sp));
        }
        break;
      case is_boolean:
        {
          pad(&offset, buf, ccnt, f);
          char * s = "false";
          if (json_to_bool(cur_json))
            s = "true";
          if (buf)
            memcpy(buf + offset, s, strlen(s));
          offset += strlen(s);
          if (ccnt->more_siblings)
            delimiter(&offset, buf, f, ccnt, ',');
          cee_del(cee_stack_pop(sp));
        }
        break;
      case is_undefined:
        {
          pad(&offset, buf, ccnt, f);
          if (buf)
            memcpy(buf + offset, "undefined", 9);
          offset += 9;
          if (ccnt->more_siblings)
            delimiter(&offset, buf, f, ccnt, ',');
          cee_del(cee_stack_pop(sp));
        }
        break;
      case is_string:
        {
          char * str = (char *)json_to_string(cur_json);
          pad(&offset, buf, ccnt, f);
          str_append(buf, &offset, str, strlen(str));
          if (ccnt->more_siblings)
            delimiter(&offset, buf, f, ccnt, ',');
          cee_del(cee_stack_pop(sp));
        }
        break;
      case is_number:
        {
          pad(&offset, buf, ccnt, f);
          incr = cee_box_snprintf(NULL, 0, json_to_number(cur_json));
          if (buf) {
            cee_box_snprintf(buf+offset, incr, json_to_number(cur_json));
          }
          offset+=incr;
          if (ccnt->more_siblings)
            delimiter(&offset, buf, f, ccnt, ',');
          cee_del(cee_stack_pop(sp));
        }
        break;
      case is_array:
        {
          uintptr_t i = ccnt->next;
          if (i == 0)
            delimiter(&offset, buf, f, ccnt, '[');
          uintptr_t n = cee_vect_size(ccnt->array);
          if (i < n) {
            bool more_siblings = false;
            if (1 < n && i+1 < n)
              more_siblings = true;
            ccnt->next++;
            push (ccnt->tabs + 1, more_siblings, sp,
                  (struct json *)(ccnt->array->_[i]));
          }
          else {
            delimiter(&offset, buf, f, ccnt, ']');
            if (ccnt->more_siblings)
            delimiter(&offset, buf, f, ccnt, ',');
            cee_del(cee_stack_pop(sp));
          }
        }
        break;
      case is_object:
        {
          uintptr_t i = ccnt->next;
          if (i == 0)
            delimiter(&offset, buf, f, ccnt, '{');
          uintptr_t n = cee_vect_size(ccnt->array);
          if (i < n) {
            bool more_siblings = false;
            if (1 < n && i+1 < n)
              more_siblings = true;
            ccnt->next++;
            char * key = (char *)ccnt->array->_[i];
            struct json * j1 = cee_map_find(ccnt->object, ccnt->array->_[i]);
            unsigned klen = strlen(key);
            pad(&offset, buf, ccnt, f);
            str_append(buf, &offset, key, klen);
            delimiter(&offset, buf, f, ccnt, ':');
            push(ccnt->tabs + 1, more_siblings, sp, j1);
          }
          else {
            delimiter(&offset, buf, f, ccnt, '}');
            if (ccnt->more_siblings)
            delimiter(&offset, buf, f, ccnt, ',');
            cee_del(ccnt->array);
            cee_del(cee_stack_pop(sp));
          }
        }
        break;
    }
  }
  cee_del (sp);
  if (buf)
    buf[offset] = '\0';
  return offset;
}
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
    if( ('0'<= c && c<='9') || ('A'<= c && c<='F') || ('a'<= c && c<='f') ) {
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
  t->str = cee_str_n(128, "");
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
      case '"':
      case '\\':
      case '/':
        t->str = cee_str_add(t->str, c);
        break;
      case 'b': t->str = cee_str_add(t->str, '\b'); break;
      case 'f': t->str = cee_str_add(t->str, '\f'); break;
      case 'n': t->str = cee_str_add(t->str, '\n'); break;
      case 'r': t->str = cee_str_add(t->str, '\r'); break;
      case 't': t->str = cee_str_add(t->str, '\t'); break;
      case 'u':
        {
          uint16_t x;
          if (!read_4_digits(t, &x))
            return false;
         struct utf8_seq s = { 0 };
          utf8_encode(x, &s);
          t->str = cee_str_ncat(t->str, s.c, s.len);
        }
        break;
      default:
        return false;
      }
    }
    else {
      t->str = cee_str_add(t->str, c);
    }
  }
  if(!utf8_validate(t->str->_, cee_str_end(t->str)))
    return false;
  return true;
}
static bool parse_number(struct tokenizer *t) {
  int x = sscanf(t->buf, "%lf", &t->real);
  return x == 1;
}
enum token json_next_token(struct tokenizer * t) {
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
        return c;
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
#endif
