#ifdef CEE_AMALGAMATION
#undef  S
#define S(f)    _cee_set_##f
#else
#define S(f)    _##f
#include "cee.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cee-internal.h"
#endif
#include "cee-header.h"

namespace cee {
  namespace set {

struct S(header) {
  void * context;
  int (*cmp)(const void *l, const void *r);
  uintptr_t size;
  enum del_policy del_policy;
  struct sect cs;
  void * _[1];
};

struct S(pair) {
  void * value;
  struct S(header) * h;
};

static void S(free_pair) (void * c) {
  struct S(header) * h = ((struct S(pair) *)c)->h;
  del_e(h->del_policy, ((struct S(pair) *)c)->value);
  free(c);
}

static void S(del)(void * p) {
  struct S(header) * h = FIND_HEADER (p);
  tdestroy(h->_[0], S(free_pair));
  free(h);
}


static int S(cmp) (const void * v1, const void * v2) {
  struct S(pair) * t1 = (struct S(pair) *) v1;
  struct S(pair) * t2 = (struct S(pair) *) v2;
  if (t1->h == t2->h)
  	return t1->h->cmp(t1->value, t2->value);
  else
    segfault();
}


/*
 * create a new set and the equality of 
 * its two elements are decided by cmp
 * dt: specify how its elements should be handled if the set is deleted.
 */
struct set::data * mk_e (enum del_policy o, int (*cmp)(const void *, const void *)) 
{
  struct S(header) * m = (struct S(header) *)malloc(sizeof(struct S(header)));
  m->cmp = cmp;
  m->size = 0;
  ZERO_CEE_SECT(&m->cs);
  m->cs.del = S(del);
  m->cs.resize_method = resize_with_identity;
  m->cs.n_product = 1;
  m->context = NULL;
  m->_[0] = NULL;
  m->del_policy = o;
  return (struct set::data *)m->_;
}

struct set::data * mk (int (*cmp)(const void *, const void *)) {
  return set::mk_e(CEE_DEFAULT_DEL_POLICY, cmp);
}

size_t size (struct set::data * s) {
  struct S(header) * h = FIND_HEADER(s);
  return h->size;
}

bool empty (struct set::data * s) {
  struct S(header) * h = FIND_HEADER(s);
  return h->size == 0;
}

/*
 * add an element key to the set m
 * 
 */
void add(struct set::data *m, void * val) {
  struct S(header) * h = FIND_HEADER(m);
  void ** c = (void **)malloc(sizeof(void *) * 2);
  c[0] = val;
  c[1] = h;
  void *** oldp = (void ***)tsearch(c, h->_, S(cmp));
  
  if (oldp == NULL)
    segfault();
  else if (*oldp != c)
    free(c);
  else {
    h->size ++;
    incr_indegree(h->del_policy, val);
  }
  return;
}

static void S(noop)(void *p) {}
void cee_set_clear (struct cee_set * s) {
  struct S(header) * h = FIND_HEADER (s);
  switch(h->del_policy) {
    case dp_del_rc:
      tdestroy(h->_[0], del_ref);
      break;  
    case dp_del:
      tdestroy(h->_[0], del);
      break;
    case dp_noop:
      tdestroy(h->_[0], S(noop));
      break;
  }
  h->_[0] = NULL;
  h->size = 0;
}

void * find(struct data *m, void * value) {
  struct S(header) * h = FIND_HEADER(m);
  struct S(pair) p = { value, h };
  void ***oldp = (void ***)tfind(&p, h->_, S(cmp));
  if (oldp == NULL)
    return NULL;
  else {
    void ** t = (void **)*oldp;
    return t[0];
  }
}

static void S(get_value) (const void *nodep, const VISIT which, const int depth) {
  struct S(pair) * p;
  struct S(header) * h;
  switch (which) 
  {
    case preorder:
    case leaf:
      p = (S(pair) *)*(void **)nodep;
      h = p->h;
      h->context = vect::append((struct vect::data *) h->context, p->value);
      break;
    default:
      break;
  }
}

struct vect::data * values(struct set::data * m) {
  uintptr_t s = set::size(m);
  struct S(header) * h = FIND_HEADER(m);
  h->context = vect::mk(s);
  use_realloc(h->context);
  twalk(h->_[0], S(get_value));
  return (struct vect::data *)h->context;
}

void * remove(struct set::data *m, void * key) {
  struct S(header) * h = FIND_HEADER(m);
  void ** old = (void **)tdelete(key, h->_, h->cmp);
  if (old == NULL)
    return NULL;
  else {
    h->size --;
    struct S(pair) * p = (struct S(pair) *)*old;
    void * k = p->value;
    free(p);
    return k;
  }
}

struct set::data * union_set (struct set::data * s1, struct set::data * s2) {
  struct S(header) * h1 = FIND_HEADER(s1);
  struct S(header) * h2 = FIND_HEADER(s2);
  if (h1->cmp == h2->cmp) {
    struct set::data * s0 = set::mk(h1->cmp);
    struct vect::data * v1 = set::values(s1);
    struct vect::data * v2 = set::values(s2);
    int i;
    for (i = 0; i < vect::size(v1); i++)
      set::add(s0, v1->_[i]);
    
    for (i = 0; i < vect::size(v2); i++)
      set::add(s0, v2->_[i]);
    
    del(v1);
    del(v2);
    return s0;
  } else
    segfault();
  return NULL;
}
    
  }
}