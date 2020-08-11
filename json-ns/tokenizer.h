#ifndef ORCA_JSON_TOK_H
#define ORCA_JSON_TOK_H
#include "cee.h"

namespace cee {
  namespace json {

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
  str::data * str;
  double real;
};

extern enum token next_token(struct tokenizer * t);
    
  }
}
#endif // ORCA_JSON_TOK_H
