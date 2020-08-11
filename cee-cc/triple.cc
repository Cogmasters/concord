#ifdef CEE_AMALGAMATION
#undef   S
#define  S(f)  _cee_triple_##f
#else
#define  S(f)  _##f
#include "cee.h"
#include "cee-internal.h"
#include <stdlib.h>
#include <string.h>
#endif
#include "cee-header.h"

namespace cee {
  namespace triple {

struct S(header) {
  enum del_policy del_policies[3];
  struct sect cs;
  void * _[3];
};

static void S(del)(void * v) {
  struct S(header) * b = FIND_HEADER(v);
  int i;
  for (i = 0; i < 3; i++)
    del_e(b->del_policies[i], b->_[i]);
  free(b);
}

struct triple::data * mk_e (enum del_policy o[3], void * v1, void * v2, void * v3) {
  size_t mem_block_size = sizeof(struct S(header));
  struct S(header) * m = (struct S(header) *)malloc(mem_block_size);
  ZERO_CEE_SECT(&m->cs);
  m->cs.del = S(del);
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->_[0] = v1;
  m->_[1] = v2;
  m->_[2] = v3;
  int i;
  for (i = 0; i < 3; i++) {
    m->del_policies[i] = o[i];
    incr_indegree(o[i], m->_[i]);
  }
  return (struct triple::data *)&m->_;
}

struct triple::data * mk (void * v1, void * v2, void *v3) {
  enum del_policy o[3] = { CEE_DEFAULT_DEL_POLICY, 
                          CEE_DEFAULT_DEL_POLICY, 
                          CEE_DEFAULT_DEL_POLICY };
  return triple::mk_e(o, v1, v2, v3);
}
    
  }
}