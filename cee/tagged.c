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

struct S(header) {
  enum cee_del_policy del_policy;
  struct cee_sect cs;
  struct cee_tagged _;
};

static void S(del) (void * v) {
  struct S(header) * m = FIND_HEADER(v);
  cee_del_e(m->del_policy, m->_.ptr._);
  free(m);
}

struct cee_tagged * cee_tag_e (enum cee_del_policy o, uintptr_t tag, void *p) {
  size_t mem_block_size = sizeof(struct S(header));
  struct S(header) * b = malloc(mem_block_size);
  ZERO_CEE_SECT(&b->cs);
  b->cs.del = S(del);
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = mem_block_size;
  b->_.tag = tag;
  b->_.ptr = (union cee_ptr)p;
  b->del_policy = o;
  cee_incr_indegree(o, p);
  return &b->_;
}

struct cee_tagged * cee_tag (uintptr_t tag, void *p){
  return cee_tag_e (CEE_DEFAULT_DEL_POLICY, tag, p);
}