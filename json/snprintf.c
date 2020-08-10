/* JSON snprintf
   C reimplementation of
     Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>'s json.cpp
*/
#ifndef ORCA_JSON_AMALGAMATION
#include "json.h"
#include <string.h>
#endif

struct counter {
  uintptr_t next;
  struct cee_vect * array;
  struct cee_map  * object;
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
 * compute how many bytes are needed to serialize json as a string
 */
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