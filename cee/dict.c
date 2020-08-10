#ifdef CEE_AMALGAMATION
#undef   S
#define  S(f)  _cee_dict_##f
#else
#define  S(f)  _##f
#include "cee.h"
#include "cee-internal.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#endif
#include "cee-header.h"

struct S(header) {
  struct cee_vect * keys;
  struct cee_vect * vals;
  uintptr_t size;
  enum cee_del_policy del_policy;
  struct cee_sect cs;
  struct hsearch_data _[1];
};


static void S(del)(void *d) {
  struct S(header) * m = FIND_HEADER(d);
  hdestroy_r(m->_);
  cee_del_e(m->del_policy, m->keys);
  cee_del_e(m->del_policy, m->vals);
  free(m);
}

struct cee_dict * cee_dict_e (enum cee_del_policy o, size_t size) {
  size_t mem_block_size = sizeof(struct S(header));
  struct S(header) * m = malloc(mem_block_size);
  m->del_policy = o;
  m->keys = cee_vect(size);
  cee_use_realloc(m->keys);
  
  m->vals = cee_vect(size);
  cee_use_realloc(m->vals);
  
  m->size = size;
  ZERO_CEE_SECT(&m->cs);
  m->cs.del = S(del);
  m->cs.mem_block_size = mem_block_size;
  m->cs.resize_method = resize_with_identity;
  m->cs.n_product = 2; // key:str, value
  size_t  hsize = (size_t)((float)size * 1.25);
  memset(m->_, 0, sizeof(struct hsearch_data));
  if (hcreate_r(hsize, m->_))
    return (struct cee_dict *)(m->_);
  else {
    cee_del(m->keys);
    cee_del(m->vals);
    free(m);
    return NULL;
  }
}

struct cee_dict * cee_dict (size_t size) {
  return cee_dict_e (CEE_DEFAULT_DEL_POLICY, size);
}

void cee_dict_add (struct cee_dict * d, char * key, void * value) {
  struct S(header) * m = FIND_HEADER(d);
  ENTRY n, *np;
  n.key = key;
  n.data = value;
  if (!hsearch_r(n, ENTER, &np, m->_))
    cee_segfault();
  m->keys = cee_vect_append(m->keys, key);
  m->vals = cee_vect_append(m->vals, value);
}

void * cee_dict_find(struct cee_dict * d, char * key) {
  struct S(header) * m = FIND_HEADER(d);
  ENTRY n, *np;
  n.key = key;
  n.data = NULL;
  if (hsearch_r(n, FIND, &np, m->_))
    return np->data;
  printf ("%s\n", strerror(errno));
  return NULL;
}