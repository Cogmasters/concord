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

struct S(header) {
  uintptr_t capacity;
  enum cee_del_policy del_policy;
  struct cee_sect cs;
  char _[1]; // actual data
};

#include "cee-resize.h"

static void S(del) (void * p) {
  struct S(header) * m = FIND_HEADER(p);
  free(m);
}

void * cee_block (size_t n) {
  size_t mem_block_size;
  va_list ap;
  
  mem_block_size = n + sizeof(struct S(header));
  struct S(header) * m = malloc(mem_block_size);
  
  ZERO_CEE_SECT(&m->cs);
  m->del_policy = cee_dp_del_rc;
  m->cs.del = S(del);
  m->cs.resize_method = resize_with_malloc;
  m->cs.mem_block_size = mem_block_size;
  m->cs.cmp = memcmp;
  m->capacity = n;
  return (struct cee_block *)(m->_);
}