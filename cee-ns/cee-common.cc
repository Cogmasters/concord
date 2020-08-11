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

#define FIND_SECT(p)  (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)))

using namespace cee;

/*
 * a generic resource delete function for all cee_* pointers
 */
void cee::del(void *p) {
  if (!p) cee::segfault();
  
  struct sect * cs = FIND_SECT(p);
  cs->del(p);
}

void cee::del_ref(void *p) {
  if (!p) cee::segfault();
  
  struct sect * cs = FIND_SECT(p);
  
  if (cs->in_degree) cs->in_degree --;
  
  /* if it's retained by an owner,
     it should be freed by cee_del
  */
  if (cs->retained) return;
  
  if (!cs->in_degree) cs->del(p);
}

void cee::use_realloc(void * p) {
  struct sect * cs = FIND_SECT(p);
  if (cs->resize_method)
    cs->resize_method = resize_with_realloc;
}

void cee::use_malloc(void * p) {
  struct sect * cs = FIND_SECT(p);
  if (cs->resize_method)
    cs->resize_method = resize_with_malloc;
}

void cee::segfault() {
  volatile char * c = 0;
  *c = 0;
  __builtin_unreachable();
}

static void S(incr_rc) (void * p) {
  struct sect * cs = FIND_SECT(p);
  if (cs->retained) return;
  
  cs->in_degree ++;
}

static void S(decr_rc) (void * p) {
  struct sect * cs = FIND_SECT(p);
  if (cs->retained) return;
  
  if (cs->in_degree)
    cs->in_degree --;
  else {
    // report warnings
  }
}

uint16_t get_in_degree (void * p) {
  struct sect * cs = FIND_SECT(p);
  return cs->in_degree;
}

static void S(retain) (void *p) {
  struct sect * cs = FIND_SECT(p);
  cs->retained = 1;
}

static void S(release) (void * p) {
  struct sect * cs = FIND_SECT(p);
  if(cs->retained)
    cs->retained = 0;
  else {
    // report error
    cee::segfault();
  }
}

void cee::incr_indegree (enum del_policy o, void * p) {
  switch(o) {
    case dp_del_rc:
      S(incr_rc)(p);
      break;
    case dp_del:
      S(retain)(p);
      break;
    case dp_noop:
      break;
  }
}

void cee::decr_indegree (enum del_policy o, void * p) {
  switch(o) {
    case dp_del_rc:
      S(decr_rc)(p);
      break;
    case dp_del:
      S(release)(p);
      break;
    case dp_noop:
      break;
  }
}


void cee::del_e (enum del_policy o, void *p) {
  switch(o) {
    case dp_del_rc:
      cee::del_ref(p);
      break;
    case dp_del:
      cee::del(p);
      break;
    case dp_noop:
      break;
  }
}