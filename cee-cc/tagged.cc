#ifdef CEE_AMALGAMATION
#undef   S
#define  S(f)  _cee_tagged_##f
#else
#define  S(f)  _##f
#include "cee.h"
#include "cee-internal.h"
#include <stdlib.h>
#include <string.h>
#endif
#include "cee-header.h"

namespace cee {
  namespace tagged {
    

struct S(header) {
  enum del_policy del_policy;
  struct sect cs;
  struct tagged::data _;
};

static void S(del) (void * v) {
  struct S(header) * m = FIND_HEADER(v);
  del_e(m->del_policy, m->_.ptr._);
  free(m);
}

struct tagged::data * mk_e (enum del_policy o, uintptr_t tag, void *p) {
  size_t mem_block_size = sizeof(struct S(header));
  struct S(header) * b = (struct S(header) *)malloc(mem_block_size);
  ZERO_CEE_SECT(&b->cs);
  b->cs.del = S(del);
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = mem_block_size;
  b->_.tag = tag;
  b->_.ptr._ = p;
  b->del_policy = o;
  incr_indegree(o, p);
  return &b->_;
}

struct tagged::data * mk (uintptr_t tag, void *p) {
  return mk_e(CEE_DEFAULT_DEL_POLICY, tag, p);
}
    
  }
}