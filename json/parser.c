/* JSON parser
   C reimplementation of 
     Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>'s json.cpp
*/
#ifndef ORCA_JSON_AMALGAMATION
#include "json.h"
#include "cee.h"
#include "tokenizer.h"
#include <string.h>
#include <stdlib.h>
#endif

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

#define SPI(st, j)  cee_tuple_e((enum cee_del_policy [2]){cee_dp_noop, cee_dp_noop}, (void *)st, j)

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

#define TOPS         (enum state_type)(top->_[0])
#define POP(sp)      { result = (struct cee_tuple *)cee_stack_pop(sp); }
  
  cee_stack_push(sp, SPI(st_done, NULL));

  while(!cee_stack_empty(sp) && !cee_stack_full(sp) &&
        state != st_error && state != st_done) {

    if (result) {
      cee_del(result);
      result = NULL;
    }

    int c= json_next_token(&tock);
#ifdef DEBUG_PARSER
    printf ("token %c\n", c);
#endif
    
    top = (struct cee_tuple *)cee_stack_top(sp, 0);
    switch(state) {
    case st_object_or_array_or_value_expected:
      if(c=='[')  {
        top->_[1]=json_array(10);
        state=st_array_value_or_close_expected;
      }
      else if(c=='{') {
        top->_[1]=json_object();
        state=st_object_key_or_close_expected;
      }
      else if(c==tock_str)  {
        top->_[1]=json_string(tock.str);
        tock.str = NULL;
        state=TOPS;
        POP(sp);
      }
      else if(c==tock_true) {
        top->_[1]=json_true();
        state=TOPS;
        POP(sp);
      }
      else if(c==tock_false) {
        top->_[1]=json_false();
        state=TOPS;
        POP(sp);
      }
      else if(c==tock_null) {
        top->_[1]=json_null();
        state=TOPS;
        POP(sp);
      }
      else if(c==tock_number) {
        top->_[1] = json_number (tock.real);
        state=TOPS;
        POP(sp);
      }
      else
        state = st_error;
      break;

    case st_object_key_or_close_expected:
      if(c=='}') {
        state=TOPS;
        POP(sp);
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
          cee_stack_push(sp, SPI(st_object_close_or_comma_expected, a));
        }
        else if(c=='{') {
          struct json * o = json_object();
          cee_map_add(obj, key, o);
          state=st_object_key_or_close_expected;
          cee_stack_push(sp, SPI(st_object_close_or_comma_expected, o));
        }
        else 
          state=st_error;
      }
      break;
    case st_object_close_or_comma_expected:
      if(c==',')
        state=st_object_key_or_close_expected;
      else if(c=='}') {
        state=TOPS;
        POP(sp);
      }
      else
        state=st_error;
      break;
    case st_array_value_or_close_expected:
      {
        if(c==']') {
          state=TOPS;
          POP(sp);
          break;
        }
        struct cee_vect * ar = json_to_array(top->_[1]);
        
        if(c==tock_str)  {
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
          cee_stack_push(sp, SPI(st_array_close_or_comma_expected,a));
        }
        else if(c=='{') {
          struct json * o = json_object();
          state=st_object_key_or_close_expected;
          cee_stack_push(sp, SPI(st_array_close_or_comma_expected,o));
        }
        else 
          state=st_error;
        break;
      }
    case st_array_close_or_comma_expected:
      if(c==']') {
        state=TOPS;
        POP(sp);
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