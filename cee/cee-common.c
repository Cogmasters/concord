#ifdef CEE_AMALGAMATION
#undef   S
#define  S(f)  _cee_common_##f
#else
#define  S(f)  _##f
#include "cee.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cee-internal.h"
#endif

#define FIND_SECT(p)  ((void *)((char *)p - sizeof(struct cee_sect)))

/*
 * a generic resource delete function for all cee_* pointers
 */
void cee_del(void *p) {
  if (!p) cee_segfault();
  
  struct cee_sect * cs = FIND_SECT(p);
  cs->del(p);
}

void cee_del_ref(void *p) {
  if (!p) cee_segfault();
  
  struct cee_sect * cs = FIND_SECT(p);
  
  if (cs->in_degree) cs->in_degree --;
  
  /* if it's retained by an owner,
     it should be freed by cee_del
  */
  if (cs->retained) return;
  
  if (!cs->in_degree) cs->del(p);
}

void cee_use_realloc(void * p) {
  struct cee_sect * cs = FIND_SECT(p);
  if (cs->resize_method)
    cs->resize_method = resize_with_realloc;
}

void cee_use_malloc(void * p) {
  struct cee_sect * cs = FIND_SECT(p);
  if (cs->resize_method)
    cs->resize_method = resize_with_malloc;
}

void cee_segfault() {
  volatile char * c = 0;
  *c = 0;
  __builtin_unreachable();
}

static void S(incr_rc) (void * p) {
  struct cee_sect * cs = FIND_SECT(p);
  if (cs->retained) return;
  
  cs->in_degree ++;
}

static void S(decr_rc) (void * p) {
  struct cee_sect * cs = FIND_SECT(p);
  if (cs->retained) return;
  
  if (cs->in_degree)
    cs->in_degree --;
  else {
    // report warnings
  }
}

uint16_t cee_get_in_degree (void * p) {
  struct cee_sect * cs = FIND_SECT(p);
  return cs->in_degree;
}

static void S(retain) (void *p) {
  struct cee_sect * cs = FIND_SECT(p);
  cs->retained = 1;
}

static void S(release) (void * p) {
  struct cee_sect * cs = FIND_SECT(p);
  if(cs->retained)
    cs->retained = 0;
  else {
    // report error
    cee_segfault();
  }
}

void cee_incr_indegree (enum cee_del_policy o, void * p) {
  switch(o) {
    case cee_dp_del_rc:
      S(incr_rc)(p);
      break;
    case cee_dp_del:
      S(retain)(p);
      break;
    case cee_dp_noop:
      break;
  }
}

void cee_decr_indegree (enum cee_del_policy o, void * p) {
  switch(o) {
    case cee_dp_del_rc:
      S(decr_rc)(p);
      break;
    case cee_dp_del:
      S(release)(p);
      break;
    case cee_dp_noop:
      break;
  }
}


void cee_del_e (enum cee_del_policy o, void *p) {
  switch(o) {
    case cee_dp_del_rc:
      cee_del_ref(p);
      break;
    case cee_dp_del:
      cee_del(p);
      break;
    case cee_dp_noop:
      break;
  }
}