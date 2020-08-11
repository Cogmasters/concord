#ifdef CEE_AMALGAMATION
#undef   S
#define  S(f)  _cee_str_##f
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
  namespace str {
    

struct S(header) {
  uintptr_t capacity;
  struct sect cs;
  char _[1];
};

#include "cee-resize.h"

static void S(del) (void * p) {
  struct S(header) * m = FIND_HEADER(p);
  free(m);
}

str::data * mk (const char * fmt, ...) {
  if (!fmt) {
    // fmt cannot be null
    // intentionally cause a segfault
    segfault();
  }
  
  uintptr_t s;
  va_list ap;
  
  va_start(ap, fmt);
  s = vsnprintf(NULL, 0, fmt, ap);
  s ++;
  
  s += sizeof(struct S(header));
  s = (s / CEE_BLOCK + 1) * CEE_BLOCK;
  size_t mem_block_size = s;
  struct S(header) * h = (struct S(header) *)malloc(mem_block_size);
  
  ZERO_CEE_SECT(&h->cs);
  h->cs.del = S(del);
  h->cs.resize_method = resize_with_malloc;
  h->cs.mem_block_size = mem_block_size;
  h->cs.cmp = (void *)strcmp;
  h->cs.cmp_stop_at_null = 1;
  h->cs.n_product = 0;
  h->capacity = s - sizeof(struct S(header));
  
  va_start(ap, fmt);
  vsnprintf(h->_, s, fmt, ap);
  return (str::data *)(h->_);
} 

str::data * mk_e (size_t n, const char * fmt, ...) {
  uintptr_t s;
  va_list ap;
  
  if (fmt) {
    va_start(ap, fmt);
    s = vsnprintf(NULL, 0, fmt, ap);
    s ++; // including the null terminator
  }
  else
    s = n;
  
  s += sizeof(struct S(header));
  size_t mem_block_size = (s / CEE_BLOCK + 1) * CEE_BLOCK;
  struct S(header) * m = (struct S(header) *) malloc(mem_block_size);
  
  ZERO_CEE_SECT(&m->cs);
  m->cs.del = S(del);
  m->cs.resize_method = resize_with_malloc;
  m->cs.mem_block_size = mem_block_size;
  m->cs.cmp = (void *)strcmp;
  m->cs.cmp_stop_at_null = 1;
  m->capacity = mem_block_size - sizeof(struct S(header));
  if (fmt) {
    va_start(ap, fmt);
    vsnprintf(m->_, mem_block_size, fmt, ap);
  } 
  else {
    m->_[0] = '\0'; // terminates with '\0'
  }
  return (str::data *)(m->_);
}

static void S(noop)(void * v) {}
struct cee_block * cee_block_empty () {
  static struct S(header) singleton;
  singleton.cs.del = S(noop);
  singleton.cs.resize_method = resize_with_malloc;
  singleton.cs.mem_block_size = sizeof(struct S(header));
  singleton.capacity = 1;
  singleton._[0] = 0;
  return (struct cee_block *)&singleton._;
}

/*
 * if it's not NULL terminated, NULL should be returned
 */
char * end(str::data * str) {
  struct S(header) * b = FIND_HEADER(str);
  // TODO: fixes this
  return (char *)str + strlen((char *)str);
  /*
  int i = 0; 
  for (i = 0;i < b->used; i++)
    if (b->_[i] == '\0')
      return (b->_ + i);
  
  return NULL;
  */
}

/*
 * append any char (including '\0') to str;
 */
str::data * add(str::data * str, char c) {
  struct S(header) * b = FIND_HEADER(str);
  uint32_t slen = strlen((char *)str);
  if (slen < b->capacity) {
    b->_[slen] = c;
    b->_[slen+1] = '\0';
    return (str::data *)(b->_);
  } 
  else {
    struct S(header) * b1 = S(resize)(b, b->cs.mem_block_size + CEE_BLOCK);
    b1->capacity = b->capacity + CEE_BLOCK;
    b1->_[b->capacity] = c;
    b1->_[b->capacity+1] = '\0';
    return (str::data *)(b1->_);
  }
}

str::data * catf(str::data * str, const char * fmt, ...) {
  struct S(header) * b = FIND_HEADER(str);
  if (!fmt)
    return str;
  
  size_t slen = strlen((char *)str);
  
  va_list ap;
  va_start(ap, fmt);
  size_t s = vsnprintf(NULL, 0, fmt, ap);
  s ++; // including the null terminator
  
  va_start(ap, fmt);
  if (slen + s < b->capacity) {
    vsnprintf(b->_ + slen, s, fmt, ap);
    return str;
  }
  else {
    struct S(header) * b1 = S(resize)(b, slen + s);
    vsnprintf(b1->_ + slen, s, fmt, ap);
    return (str::data *)(b1->_);
  }
}

str::data * ncat (str::data * str, char * s, size_t slen) {
  return NULL;
}
    
  }
}