#ifdef CEE_AMALGAMATION
#undef   S
#define  S(f)  _cee_block_##f
#else
#define  S(f)  _##f
#include "cee.h"
#include "cee-internal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#endif
#include "cee-header.h"

#ifndef CEE_BLOCK
#define  CEE_BLOCK 64
#endif

namespace cee {
namespace block {
struct S(header) {
  uintptr_t capacity;
  enum del_policy del_policy;
  struct sect cs;
  char _[1]; // actual data
};

#include "cee-resize.h"

static void S(del) (void * p) {
  struct S(header) * m = (struct S(header) *)FIND_HEADER(p);
  free(m);
}

void * mk (size_t n) {
  size_t mem_block_size;
  va_list ap;
  
  mem_block_size = n + sizeof(struct S(header));
  struct S(header) * m = (struct S(header) *)malloc(mem_block_size);
  
  ZERO_CEE_SECT(&m->cs);
  m->del_policy = dp_del_rc;
  m->cs.del = S(del);
  m->cs.resize_method = resize_with_malloc;
  m->cs.mem_block_size = mem_block_size;
  m->cs.cmp = (void *)memcmp;
  m->capacity = n;
  return (struct block::data *)(m->_);
}
}
}