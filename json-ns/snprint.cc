/* JSON snprintf
   C reimplementation of
     Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>'s orca_json.cpp
*/
#ifndef ORCA_JSON_AMALGAMATION
#include "json.h"
#include <string.h>
#endif

namespace cee {
  namespace json {

struct counter {
  uintptr_t next;
  vect::data * array;
  map::data  * object;
  char tabs;
  char more_siblings;
};

static struct counter * push(uintptr_t tabs, bool more_siblings, 
                             stack::data * sp, json::data * j) {
  struct counter * p = NULL;
  if (j == NULL) {
    p = (struct counter *)block::mk(sizeof(struct counter));
    p->tabs = 0;
  }
  else {
    switch(j->t) {
      case type_is_object:
        {
          p = (struct counter *) block::mk(sizeof(struct counter));
          map::data * mp = to_object(j);
          p->array = map::keys(mp);
          p->object = to_object(j);
          p->tabs = tabs;
          p->next = 0;
          p->more_siblings = 0;
        }
        break;
      case type_is_array:
        {
          p = (struct counter *)block::mk(sizeof(struct counter));
          p->array = to_array(j);
          p->tabs = tabs;
          p->next = 0;
          p->more_siblings = 0;
        }
        break;
      default:  
        {
          p = (struct counter *)block::mk(sizeof(struct counter));
          p->array = NULL;
          p->tabs = tabs;
          p->next = 0;
          p->more_siblings = 0;
        }
        break;
    }
    p->more_siblings = more_siblings;
  }
  enum del_policy o[2] = { dp_del, dp_noop };
  stack::push(sp, tuple::mk_e(o, p, j));
  return p;
}

static void pad (uintptr_t * offp, char * buf, struct counter * cnt, enum format f) 
{
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

static void delimiter (uintptr_t * offp, char * buf, enum format f, 
                       struct counter * cnt, char c) 
{
  uintptr_t offset = *offp;
	if (!f) {
    if (buf) buf[offset] = c;
    offset ++; // only count one
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
        buf[4]=tohex[c >>  4];
        buf[5]=tohex[c & 0xF];
        buf[6]=0;
        addon = buf;
      }
    };
    if(addon) {
      //a.append(last,i-last);
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

/*
 * compute how many bytes are needed to serialize orca_json as a string
 */
size_t snprint (char * buf, size_t size, json::data * j, enum format f) {
  tuple::data * cur;
  json::data * cur_orca_json;
  struct counter * ccnt;
  uintptr_t incr = 0;
  
  stack::data * sp = stack::mk_e(dp_noop, 500);
  push (0, false, sp, j);
  
  uintptr_t offset = 0;
  while (!stack::empty(sp) && !stack::full(sp)) {
    cur = (tuple::data *) stack::top(sp, 0);
    cur_orca_json = (json::data *)(cur->_[1]);
    ccnt = (struct counter *)(cur->_[0]);
    
    switch(cur_orca_json->t) {
      case type_is_null:
        {
          pad(&offset, buf, ccnt, f);
          if (buf)
            memcpy(buf + offset, "null", 4);
          offset += 4;
          if (ccnt->more_siblings)
            delimiter(&offset, buf, f, ccnt, ',');
          del(stack::pop(sp));
        }
        break;
      case type_is_boolean:
        {
          pad(&offset, buf, ccnt, f);
          char * s = "false";			
          if (to_bool(cur_orca_json))
            s = "true";
          if (buf) 
            memcpy(buf + offset, s, strlen(s));
          offset += strlen(s);
          if (ccnt->more_siblings)
            delimiter(&offset, buf, f, ccnt, ',');
          del(stack::pop(sp));
        }
        break;
      case type_is_undefined:
        {
          pad(&offset, buf, ccnt, f);
          if (buf)
            memcpy(buf + offset, "undefined", 9);
          offset += 9;
          if (ccnt->more_siblings)
            delimiter(&offset, buf, f, ccnt, ',');
          del(stack::pop(sp));
        }
        break;
      case type_is_string:
        {
          char * str = (char *)to_string(cur_orca_json);
          pad(&offset, buf, ccnt, f);
          str_append(buf, &offset, str, strlen(str));
          if (ccnt->more_siblings)
            delimiter(&offset, buf, f, ccnt, ',');
          del(stack::pop(sp));
        }
        break;
      case type_is_number:
        {
          pad(&offset, buf, ccnt, f);
          incr = box::snprint(NULL, 0, to_number(cur_orca_json));
          if (buf) {
            box::snprint(buf+offset, incr, to_number(cur_orca_json));
          }
          offset+=incr;
          if (ccnt->more_siblings)
            delimiter(&offset, buf, f, ccnt, ',');
          del(stack::pop(sp));
        }
        break;
      case type_is_array: 
        { 
          uintptr_t i = ccnt->next;
          if (i == 0) 
            delimiter(&offset, buf, f, ccnt, '[');
          
          uintptr_t n = vect::size(ccnt->array);
          if (i < n) {
            bool more_siblings = false;
            if (1 < n && i+1 < n)
              more_siblings = true;
            ccnt->next++;
            push (ccnt->tabs + 1, more_siblings, sp, (json::data *)(ccnt->array->_[i]));
          }
          else {
            delimiter(&offset, buf, f, ccnt, ']');
            if (ccnt->more_siblings)
          		delimiter(&offset, buf, f, ccnt, ',');
            del(stack::pop(sp));
          }
        }
        break;
      case type_is_object:
        {
          uintptr_t i = ccnt->next;
          if (i == 0)
            delimiter(&offset, buf, f, ccnt, '{');
          
          uintptr_t n = vect::size(ccnt->array);
          if (i < n) {
            bool more_siblings = false;
            if (1 < n && i+1 < n)
              more_siblings = true;

            ccnt->next++;
            char * key = (char *)ccnt->array->_[i];
            json::data * j1 = (json::data *)map::find(ccnt->object, ccnt->array->_[i]);
            unsigned klen = strlen(key);
            pad(&offset, buf, ccnt, f);
            str_append(buf, &offset, key, klen);
            delimiter(&offset, buf, f, ccnt, ':');
            push (ccnt->tabs + 1, more_siblings, sp, j1);
          }
          else {
            delimiter(&offset, buf, f, ccnt, '}');
            if (ccnt->more_siblings)
          		delimiter(&offset, buf, f, ccnt, ',');
            del(ccnt->array);
            del(stack::pop(sp));
          }
        }
        break;
    }
  }
  del (sp);
  if (buf)
    buf[offset] = '\0';
  return offset;
}
    
  }
}