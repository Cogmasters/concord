/* JSON parser
   C reimplementation of 
     Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>'s orca_json.cpp
*/
#ifndef ORCA_JSON_AMALGAMATION
#include "json.h"
#include "cee.h"
#include "tokenizer.h"
#include <string.h>
#include <stdlib.h>
#endif

namespace cee {
  namespace json {

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


static const uintptr_t orca_json_max_depth = 512;


bool parse(char * buf, uintptr_t len, json::data **out, bool force_eof, 
           int *error_at_line)
{
  struct tokenizer tock = {0};
  tock.buf = buf;
  tock.buf_end = buf + len;
  *out = NULL;
  
  enum state_type state = st_init;
  str::data * key = NULL;
  
  stack::data * sp = stack::mk_e(dp_noop, orca_json_max_depth);
  tuple::data * top = NULL;
  tuple::data * result = NULL;

#define SPI(st, j)   tuple::mk_e((enum cee::del_policy [2]){cee::dp_noop, cee::dp_noop}, (void *)st, j)
#define TOPS         (static_cast<enum state_type>(reinterpret_cast<intptr_t>(top->_[0])))
#define POP(sp)      { result = (struct tuple::data *)stack::pop(sp); }
  
  stack::push(sp, SPI(st_done, NULL));

  while(!stack::empty(sp) && !stack::full(sp) &&
        state != st_error && state != st_done) {

    if (result) {
      del(result);
      result = NULL;
    }

    int c = next_token(&tock);
#ifdef DEBUG_PARSER
    printf ("token %c\n", c);
#endif
    
    top = (tuple::data *)stack::top(sp, 0);
    switch(state) {
    case st_object_or_array_or_value_expected:
      if(c=='[')  {
        top->_[1]= mk_array(10);
        state=st_array_value_or_close_expected;
      }
      else if(c=='{') {
        top->_[1]= mk_object();
        state=st_object_key_or_close_expected;
      }
      else if(c==tock_str)  {
        top->_[1]= mk_string(tock.str);
        tock.str = NULL;
        state=TOPS;
        POP(sp);
      }
      else if(c==tock_true) {
        top->_[1]= mk_true();
        state=TOPS;
        POP(sp);
      }
      else if(c==tock_false) {
        top->_[1] = mk_false();
        state=TOPS;
        POP(sp);
      }
      else if(c==tock_null) {
        top->_[1] = mk_null();
        state=TOPS;
        POP(sp);
      }
      else if(c==tock_number) {
        top->_[1] = mk_number (tock.real);
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
        map::data * obj = json::to_object((json::data *)top->_[1]);
        if(c==tock_str) {
          map::add(obj, key, mk_string(tock.str));
          tock.str = NULL;
          state=st_object_close_or_comma_expected;
        }
        else if(c==tock_true) {
          map::add(obj, key, mk_true());
          state=st_object_close_or_comma_expected;
        }
        else if(c==tock_false) {
          map::add(obj, key, mk_false());
          state=st_object_close_or_comma_expected;
        }
        else if(c==tock_null) {
          map::add(obj, key, mk_null());
          state=st_object_close_or_comma_expected;
        }
        else if(c==tock_number) {
          map::add(obj, key, mk_number(tock.real));
          state=st_object_close_or_comma_expected;
        }
        else if(c=='[') {
          json::data * a = mk_array(10);
          map::add(obj, key, a);
          state=st_array_value_or_close_expected;
          stack::push(sp, SPI(st_object_close_or_comma_expected, a));
        }
        else if(c=='{') {
          json::data * o = mk_object();
          map::add(obj, key, o);
          state=st_object_key_or_close_expected;
          stack::push(sp, SPI(st_object_close_or_comma_expected, o));
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
        struct vect::data * ar = json::to_array((json::data *)top->_[1]);
        
        if(c==tock_str)  {
          vect::append(ar, mk_string(tock.str));
          state=st_array_close_or_comma_expected;
        } 
        else if(c==tock_true) {
          vect::append(ar, mk_true());
          state=st_array_close_or_comma_expected;
        } 
        else if(c==tock_false) {
          vect::append(ar, mk_false());
          state=st_array_close_or_comma_expected;
        } 
        else if(c==tock_null) {
          vect::append(ar, mk_null());
          state=st_array_close_or_comma_expected;
        } 
        else if(c==tock_number) {
          vect::append(ar, mk_number(tock.real));
          state=st_array_close_or_comma_expected;
        } 
        else if(c=='[') {
          json::data * a = mk_array(10);
          state=st_array_value_or_close_expected;
          stack::push(sp, SPI(st_array_close_or_comma_expected,a));
        }
        else if(c=='{') {
          json::data * o = mk_object();
          state=st_object_key_or_close_expected;
          stack::push(sp, SPI(st_array_close_or_comma_expected,o));
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
  
  del(sp);
  if(state==st_done) { 
    if(force_eof) {
      if(next_token(&tock)!=tock_eof) {
        *error_at_line=tock.line;
        return false;
      }
    }
    *out = (json::data *)(result->_[1]);
    del(result);
    return true;
  }
  *error_at_line=tock.line;
  return false;
}
    
  }
}