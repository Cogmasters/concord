#ifdef CEE_AMALGAMATION
#undef   S
#define  S(f)  _cee_closure_##f
#else
#define  S(f)  _##f
#include "cee.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cee-internal.h"
#endif
#include "cee-header.h"

namespace cee {
namespace closure {

struct S(header) {
  struct sect cs;
  struct data _;
};

static void S(del) (void * v) {
  struct S(header) * m = FIND_HEADER(v);
  free(m);
}

struct data * mk (void * context, void * data, void * fun) {
  size_t mem_block_size = sizeof(struct S(header));
  struct S(header) * b = (struct S(header) *)malloc(mem_block_size);
  ZERO_CEE_SECT(&b->cs);
  b->cs.del = S(del);
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = mem_block_size;
  b->_.context = context;
  b->_.data = data;
  b->_.fun = fun;
  return &(b->_);
}
  
} // namespace closure
} // namespace cee