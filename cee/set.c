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

struct S(header) {
  void * context;
  int (*cmp)(const void *l, const void *r);
  uintptr_t size;
  enum cee_del_policy del_policy;
  struct cee_sect cs;
  void * _[1];
};

struct S(pair) {
  void * value;
  struct S(header) * h;
};

static void S(free_pair) (void * c) {
  struct S(header) * h = ((struct S(pair) *)c)->h;
  cee_del_e(h->del_policy, ((struct S(pair) *)c)->value);
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
    cee_segfault();
}


/*
 * create a new set and the equality of 
 * its two elements are decided by cmp
 * dt: specify how its elements should be handled if the set is deleted.
 */
struct cee_set * cee_set_e (enum cee_del_policy o, int (*cmp)(const void *, const void *)) {
  struct S(header) * m = malloc(sizeof(struct S(header)));
  m->cmp = cmp;
  m->size = 0;
  ZERO_CEE_SECT(&m->cs);
  m->cs.del = S(del);
  m->cs.resize_method = resize_with_identity;
  m->cs.n_product = 1;
  m->context = NULL;
  m->_[0] = NULL;
  m->del_policy = o;
  return (struct cee_set *)m->_;
}

struct cee_set * cee_set (int (*cmp)(const void *, const void *)) {
  return cee_set_e(CEE_DEFAULT_DEL_POLICY, cmp);
}

size_t cee_set_size (struct cee_set * s) {
  struct S(header) * h = FIND_HEADER(s);
  return h->size;
}

bool cee_set_empty (struct cee_set * s) {
  struct S(header) * h = FIND_HEADER(s);
  return h->size == 0;
}


/*
 * add an element key to the set m
 * 
 */
void cee_set_add(struct cee_set *m, void * val) {
  struct S(header) * h = FIND_HEADER(m);
  void ** c = malloc(sizeof(void *) * 2);
  c[0] = val;
  c[1] = h;
  void *** oldp = tsearch(c, h->_, S(cmp));
  
  if (oldp == NULL)
    cee_segfault();
  else if (*oldp != c)
    free(c);
  else {
    h->size ++;
    cee_incr_indegree(h->del_policy, val);
  }
  return;
}

static void S(noop)(void *p) {}
void cee_set_clear (struct cee_set * s) {
  struct S(header) * h = FIND_HEADER (s);
  switch(h->del_policy) {
    case cee_dp_del_rc:
      tdestroy(h->_[0], cee_del_ref);
      break;  
    case cee_dp_del:
      tdestroy(h->_[0], cee_del);
      break;
    case cee_dp_noop:
      tdestroy(h->_[0], S(noop));
      break;
  }
  h->_[0] = NULL;
  h->size = 0;
}

void * cee_set_find(struct cee_set *m, void * value) {
  struct S(header) * h = FIND_HEADER(m);
  struct S(pair) p = { value, h };
  void ***oldp = tfind(&p, h->_, S(cmp));
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
      p = *(void **)nodep;
      h = p->h;
      h->context = cee_vect_append((struct cee_vect *) h->context, p->value);
      break;
    default:
      break;
  }
}

struct cee_vect * cee_set_values(struct cee_set * m) {
  uintptr_t s = cee_set_size(m);
  struct S(header) * h = FIND_HEADER(m);
  h->context = cee_vect(s);
  cee_use_realloc(h->context);
  twalk(h->_[0], S(get_value));
  return h->context;
}

void * cee_set_remove(struct cee_set *m, void * key) {
  struct S(header) * h = FIND_HEADER(m);
  void ** old = tdelete(key, h->_, h->cmp);
  if (old == NULL)
    return NULL;
  else {
    h->size --;
    struct S(pair) * p = *old;
    void * k = p->value;
    free(p);
    return k;
  }
}

struct cee_set * cee_set_union (struct cee_set * s1, struct cee_set * s2) {
  struct S(header) * h1 = FIND_HEADER(s1);
  struct S(header) * h2 = FIND_HEADER(s2);
  if (h1->cmp == h2->cmp) {
    struct cee_set * s0 = cee_set(h1->cmp);
    struct cee_vect * v1 = cee_set_values(s1);
    struct cee_vect * v2 = cee_set_values(s2);
    int i;
    for (i = 0; i < cee_vect_size(v1); i++)
      cee_set_add(s0, v1->_[i]);
    
    for (i = 0; i < cee_vect_size(v2); i++)
      cee_set_add(s0, v2->_[i]);
    
    cee_del(v1);
    cee_del(v2);
    return s0;
  } else
    cee_segfault();
  return NULL;
}