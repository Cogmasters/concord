#ifdef CEE_AMALGAMATION
#undef  S
#define S(f)  _cee_map_##f
#else
#define S(f)  _##f
#include "cee.h"
#include "cee-internal.h"
#include <stdlib.h>
#include <string.h>
#endif
#include "cee-header.h"

struct S(header) {
  void * context;
  int (*cmp)(const void *l, const void *r);
  uintptr_t size;
  enum cee_del_policy key_del_policy;
  enum cee_del_policy val_del_policy;
  struct cee_sect cs;
  void * _[1];
};

struct S(pair) {
  struct cee_tuple * value;
  struct S(header) * h;
};

static void S(free_pair)(void * c) {
  struct S(pair) * p = c;
  cee_del(p->value);
  free(p);
}

static void S(del)(void * p) {
  struct S(header) * b = FIND_HEADER (p);
  tdestroy(b->_[0], S(free_pair));
  free(b);
}

static int S(cmp) (const void * v1, const void * v2) {
  struct S(pair) * t1 = (struct S(pair) *) v1;
  struct S(pair) * t2 = (struct S(pair) *) v2;
  if (t1->h == t2->h)
  	return t1->h->cmp(t1->value->_[0], t2->value->_[0]);
  else
    cee_segfault();
}

struct cee_map * cee_map (int (*cmp)(const void *, const void *)) {
  size_t mem_block_size = sizeof(struct S(header));
  struct S(header) * m = malloc(mem_block_size);
  m->context = NULL;
  m->cmp = cmp;
  m->size = 0;
  ZERO_CEE_SECT(&m->cs);
  m->cs.del = S(del);
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->cs.cmp = 0;
  m->cs.cmp_stop_at_null = 0;
  m->cs.n_product = 2; // key, value
  m->_[0] = 0;
  return (struct cee_map *)m->_;
}

uintptr_t cee_map_size(struct cee_map * m) {
  struct S(header) * b = FIND_HEADER(m);
  return b->size;
}

void cee_map_add(struct cee_map * m, void * key, void * value) {
  struct S(header) * b = FIND_HEADER(m);
  struct S(pair) * triple = malloc(sizeof(struct S(pair)));
  triple->h = b;
  triple->value = cee_tuple(key, value);
  struct S(pair) ** oldp = tsearch(triple, b->_, S(cmp));
  if (oldp == NULL)
    cee_segfault(); // run out of memory
  else if (*oldp != triple) 
    S(free_pair)(triple);
  else
    b->size ++;
  return;
}

void * cee_map_find(struct cee_map * m, void * key) {
  struct S(header) * b = FIND_HEADER(m);
  struct cee_tuple t = { key, 0 };
  struct S(pair) keyp = { .value = &t, .h = b };
  void **oldp = tfind(&keyp, b->_, S(cmp));
  if (oldp == NULL)
    return NULL;
  else {
    struct S(pair) * p = *oldp;
    return p->value->_[1];
  }
}

void * cee_map_remove(struct cee_map * m, void * key) {
  struct S(header) * b = FIND_HEADER(m);
  void ** oldp = tdelete(key, b->_, S(cmp));
  if (oldp == NULL)
    return NULL;
  else {
    b->size --;
    struct S(pair) * t = *oldp;
    struct cee_tuple * ret = t->value;
    S(free_pair)(t);
    cee_decr_indegree(b->key_del_policy, ret->_[0]);
    cee_decr_indegree(b->val_del_policy, ret->_[1]);
    return ret->_[1];
  }
}

static void S(get_key) (const void *nodep, const VISIT which, const int depth) {
  struct S(pair) * p;
  struct S(header) * h;
  struct cee_vect * keys;
  switch (which) 
  {
    case preorder:
    case leaf:
      p = *(struct S(pair) **)nodep;
      h = p->h;
      keys = h->context;
      h->context = cee_vect_append(keys, p->value->_[0]);
      break;
    default:
      break;
  }
}

struct cee_vect * cee_map_keys(struct cee_map * m) {
  uintptr_t s = cee_map_size(m);
  struct S(header) * b = FIND_HEADER(m);
  struct cee_vect * keys = cee_vect(s);
  b->context = keys;
  twalk(b->_[0], S(get_key));
  return keys;
}


static void S(get_value) (const void *nodep, const VISIT which, const int depth) {
  struct S(pair) * p;
  struct S(header) * h;
  struct cee_vect * values;
  switch (which) 
  {
    case preorder:
    case leaf:
      p = *(void **)nodep;
      h = p->h;
      values = h->context;
      h->context = cee_vect_append(values, p->value->_[1]);
      break;
    default:
      break;
  }
}


struct cee_vect * cee_map_values(struct cee_map * m) {
  uintptr_t s = cee_map_size(m);
  struct S(header) * b = FIND_HEADER(m);
  struct cee_vect * values = cee_vect(s);
  b->context = values;
  twalk(b->_[0], S(get_value));
  return values;
}