#ifdef CEE_AMALGAMATION
#undef   S
#define  S(f)  _cee_vect_##f
#else
#define  S(f)  _##f
#include "cee.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "cee-internal.h"
#endif
#include "cee-header.h"

namespace cee {
namespace vect {

struct S(header) {
  uintptr_t size;
  uintptr_t capacity;
  enum del_policy del_policy;
  struct sect cs;
  void * _[];
};

#include "cee-resize.h"

static void S(del) (void * v) {
  struct S(header) * m = FIND_HEADER(v);
  int i;
  for (i = 0; i < m->size; i++)
    del_e(m->del_policy, m->_[i]);
  free(m);
}

vect::data * mk_e (enum del_policy o, size_t cap) {
  size_t mem_block_size = sizeof(struct S(header)) + cap * sizeof(void *);
  struct S(header) * m = (struct S(header) *)malloc(mem_block_size);
  m->capacity = cap;
  m->size = 0;
  m->del_policy = o;
  ZERO_CEE_SECT(&m->cs);
  m->cs.del = S(del);
  m->cs.resize_method = resize_with_malloc;
  m->cs.mem_block_size = mem_block_size;
  return (vect::data *)(m->_);
}

vect::data * mk (size_t cap) {
  return mk_e(dp_del_rc, cap);
}

vect::data * append (vect::data * v, void *e) {
  struct S(header) * m = FIND_HEADER(v);
  size_t capacity = m->capacity;
  size_t extra_cap = capacity ? capacity : 1;
  if (m->size == m->capacity) {
    size_t new_mem_block_size = m->cs.mem_block_size + extra_cap * sizeof(void *);
    struct S(header) * m1 = S(resize)(m, new_mem_block_size);
    m1->capacity = capacity + extra_cap;
    m = m1;
  }
  m->_[m->size] = e;
  m->size ++;
  incr_indegree(m->del_policy, e);
  return (vect::data *)m->_;
}

vect::data * insert(vect::data * v, size_t index, void *e) {
  struct S(header) * m = FIND_HEADER(v);
  size_t capacity = m->capacity;
  size_t extra_cap = capacity ? capacity : 1;
  if (m->size == m->capacity) {
    size_t new_mem_block_size = m->cs.mem_block_size + extra_cap * sizeof(void *);
    struct S(header) * m1 = S(resize)(m, new_mem_block_size);
    m1->capacity = capacity + extra_cap;
    m = m1;
  }
  int i;
  for (i = m->size; i > index; i--)
    m->_[i] = m->_[i-1];
  
  m->_[index] = e;
  m->size ++;
  incr_indegree(m->del_policy, e);
  return (vect::data *)m->_;
}

vect::data * remove(vect::data * v, size_t index) {
  struct S(header) * m = FIND_HEADER(v);
  if (index >= m->size) return v;
 
  void * e = m->_[index];
  m->_[index] = 0;
  int i;
  for (i = index; i < (m->size - 1); i++)
    m->_[i] = m->_[i+1];
  
  m->size --;
  decr_indegree(m->del_policy, e);
  return (vect::data *)m->_;
}


size_t size (vect::data *x) {
  struct S(header) * m = FIND_HEADER(x);
  return m->size;
}

size_t capacity (vect::data * x) {
  struct S(header) * h = FIND_HEADER(x);
  return h->capacity;
}
  
  }
}