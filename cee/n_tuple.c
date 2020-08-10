#ifdef CEE_AMALGAMATION
#undef   S
#define  S(f)  _cee_n_tuple_##f
#else
#define  S(f)  _##f
#include "cee.h"
#include "cee-internal.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#endif
#include "cee-header.h"

#define CEE_MAX_N_TUPLE  16
struct S(header) {
  enum cee_del_policy del_policies[CEE_MAX_N_TUPLE];
  struct cee_sect cs;
  void * _[CEE_MAX_N_TUPLE];
};

static void S(del)(void * v) {
  struct S(header) * b = FIND_HEADER(v);
  int i; 
  for (i = 0; i < b->cs.n_product; i++)
    cee_del_e(b->del_policies[i], b->_[i]);
  free(b);
}


static struct S(header) * cee_n_tuple_v (size_t ntuple, 
                                         enum cee_del_policy o[ntuple], 
                                         va_list ap) {
  if (ntuple > CEE_MAX_N_TUPLE)
    cee_segfault();
  
  size_t mem_block_size = sizeof(struct S(header));
  struct S(header) * m = malloc(mem_block_size);
  ZERO_CEE_SECT(&m->cs);
  m->cs.del = S(del);
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->cs.n_product = ntuple;
  
  int i;
  for(i = 0; i < ntuple; i++) {
    m->_[i] = va_arg(ap, void *);
    m->del_policies[i] = o[i];
    cee_incr_indegree(o[i], m->_[i]);
  }
  return m;
}


struct cee_n_tuple * cee_n_tuple (size_t ntuple, ...) {
  va_list ap;
  va_start(ap, ntuple);
  enum cee_del_policy * o = malloc(ntuple * sizeof (enum cee_del_policy));
  int i;
  for (i = 0; i < ntuple; i++)
    o[i] = CEE_DEFAULT_DEL_POLICY;
  
  struct S(header) * h = cee_n_tuple_v(ntuple, o, ap);
  free(o);
  return (struct cee_n_tuple *)(h->_);
}