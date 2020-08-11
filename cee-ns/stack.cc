#ifdef CEE_AMALGAMATION
#undef   S
#define  S(f)   _cee_stack_##f
#else
#define  S(f)   _##f
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "cee.h"
#include "cee-internal.h"
#endif
#include "cee-header.h"

namespace cee {
  namespace stack {
  
struct S(header) {
  uintptr_t used;
  uintptr_t top;
  uintptr_t capacity;
  enum del_policy del_policy;
  struct sect cs;
  void * _[];
};

static void S(del) (void * v) {
  struct S(header) * m = FIND_HEADER(v);
  int i;
  for (i = 0; i < m->used; i++)
    del_e(m->del_policy, m->_[i]);
  free(m);
}

stack::data * mk_e (enum del_policy o, size_t size) {
  uintptr_t mem_block_size = sizeof(struct S(header)) + size * sizeof(void *);
  struct S(header) * m = (struct S(header) *)malloc(mem_block_size);
  m->capacity = size;
  m->used = 0;
  m->top = (0-1);
  m->del_policy = o;
  ZERO_CEE_SECT(&m->cs);
  m->cs.del = S(del);
  m->cs.mem_block_size = mem_block_size;
  return (stack::data *)(m->_);
}

stack::data * mk (size_t size) {
  return mk_e(CEE_DEFAULT_DEL_POLICY, size);
}

int push (stack::data * v, void *e) {
  struct S(header) * m = FIND_HEADER((void **)v);
  if (m->used == m->capacity)
    return 0;

  m->top ++;
  m->used ++;
  m->_[m->top] = e;
  incr_indegree(m->del_policy, e);
  return 1;
}

void * pop (stack::data * v) {
  struct S(header) * b = FIND_HEADER((void **)v);
  if (b->used == 0) {
    return NULL;
  } 
  else {
    void * p = b->_[b->top];
    b->used --;
    b->top --;
    decr_indegree(b->del_policy, p);
    return p;
  }
}

/*
 *  nth: 0 -> the topest element
 *       1 -> 1 element way from the topest element
 */
void * top (stack::data * v, uintptr_t nth) {
  struct S(header) * b = FIND_HEADER(v);
  if (b->used == 0 || nth >= b->used)
    return NULL;
  else
    return b->_[b->top-nth];
}

uintptr_t size (stack::data *x) {
  struct S(header) * m = FIND_HEADER((void **)x);
  return m->used;
}

/*
uintptr_t stack::capacity (stack::data *s) {
  struct S(header) * m = FIND_HEADER(s);
  return m->capacity;
}
*/

bool empty (stack::data *x) {
  struct S(header) * b = FIND_HEADER(x);
  return b->used == 0;
}

bool full (stack::data *x) {
  struct S(header) * b = FIND_HEADER(x);
  return b->used >= b->capacity;
}
    
  }
}