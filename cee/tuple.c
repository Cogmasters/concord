#ifdef CEE_AMALGAMATION
#undef   S
#define  S(f)   _cee_tuple_##f
#else
#define  S(f)   _##f
#include <stdlib.h>
#include <string.h>
#include "cee.h"
#include "cee-internal.h"
#endif
#include "cee-header.h"

struct S(header) {
  enum cee_del_policy del_policies[2];
  struct cee_sect cs;
  void * _[2];
};

static void S(del)(void * v) {
  struct S(header) * b = FIND_HEADER(v);
  int i;
  for (i = 0; i < 2; i++)
    cee_del_e(b->del_policies[i], b->_[i]);
  free(b);
}


struct cee_tuple * cee_tuple_e (enum cee_del_policy o[2], void * v1, void * v2) {
  size_t mem_block_size = sizeof(struct S(header));
  struct S(header) * m = malloc(mem_block_size);
  ZERO_CEE_SECT(&m->cs);
  m->cs.del = S(del);
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->_[0] = v1;
  m->_[1] = v2;
  int i;
  for (i = 0; i < 2; i++) {
    m->del_policies[i] = o[i];
    cee_incr_indegree(o[i], m->_[i]);
  }
  return (struct cee_tuple *)&m->_;
}

struct cee_tuple * cee_tuple (void * v1, void * v2) {
  enum cee_del_policy o[2] = { CEE_DEFAULT_DEL_POLICY, CEE_DEFAULT_DEL_POLICY };
  return cee_tuple_e(o, v1, v2);
}