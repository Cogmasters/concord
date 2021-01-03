#define CEE_ONE
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <errno.h>
#ifndef CEE_H
#define CEE_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

namespace cee {
  namespace state { struct data; };
  
typedef uintptr_t tag_t;
typedef int (*cmp_fun) (const void *, const void *);

enum resize_method {
  resize_with_identity = 0, // resize with identity function
  resize_with_malloc = 1,   // resize with malloc  (safe, but leak)
  resize_with_realloc = 2   // resize with realloc (probably unsafe)
};


enum trace_action {
  trace_del_no_follow = 0,
  trace_del_follow, // trace points-to graph and delete each node
  trace_mark,       // trace points-to graph and mark each node
};

/*
 * a cotainer is an instance of struct cee_*
 * a cee element is an instance of struct cee_*
 * 
 * 
 * a container has one of the three delete policies, the policies dedicate
 * how the elements of the container will be handled once the container is 
 * deleted (freed).
 * 
 * dp_del_rc: if a container is freed, its cee element's in-degree will be 
 *         decreased by one. If any cee element's in-degree is zero, the element 
 *         will be freed. It's developer's responsibility to prevent cyclically
 *         pointed containers from having this policy.
 * 
 * dp_del: if a container is freed, all its cee elements will be freed 
 *         immediately. It's developer's responsiblity to prevent an element is 
 *         retained by multiple containers that have this policy.
 *
 * dp_noop: if a container is freed, nothing will happen to its elements.
 *          It's developer's responsiblity to prevent memory leaks.
 *
 * the default del_policy is cee_dp_del_rc, which can be configured at compile
 * time with CEE_DEFAULT_DEL_POLICY
 */
enum del_policy {
  dp_del_rc = 0,
  dp_del = 1,
  dp_noop = 2
};

#ifndef CEE_DEFAULT_DEL_POLICY
#define CEE_DEFAULT_DEL_POLICY  dp_del_rc
#endif
/*
 *
 * if an object is owned an del_immediate container, retained is 1, and 
 * in_degree is ignored.
 *
 * if an object is owned by multiple del_rc containers, in_degree is the 
 * number of containers.
 *
 */
struct sect {
  uint8_t  cmp_stop_at_null:1;    // 0: compare all bytes, otherwise stop at '\0'
  uint8_t  resize_method:2;       // three values: identity, malloc, realloc
  uint8_t  retained:1;            // if it is retained, in_degree is ignored
  uint8_t  gc_mark:2;             // used for mark & sweep gc
  uint8_t  n_product;             // n-ary (no more than 256) product type
  uint16_t in_degree;             // the number of cee objects points to this object
  // begin of gc fields
  state::data * state;            // the gc state under which this block is allocated
  struct sect * trace_next;       // used for chaining cee::_::data to be traced
  struct sect * trace_prev;       // used for chaining cee::_::data to be traced
  // end of gc fields
  uintptr_t mem_block_size;       // the size of a memory block enclosing this struct
  void *cmp;                      // compare two memory blocks
  
  // the object specific generic scan function
  // it does memory deallocation, reference count decreasing, or liveness marking
  void (*trace)(void *, enum trace_action);
};


namespace block {
  /*
   * A consecutive memory block of unknown length.
   * It can be safely casted to char *, but it may not 
   * be terminated by '\0'.
   */
  struct data {
    char _[1]; // an array of chars
  };

  /*
   * n: the number of bytes
   * the function performs one task
   * -- allocate a memory block to include at least n consecutive bytes
   * 
   * return: the address of the first byte in consecutive bytes, the address 
   *         can be freed by cee_del
   */
  extern void * mk (state::data * s, size_t n);
};

  
namespace str {
  /*
   * C string is an array of chars, it may or may not be terminated by '\0'.
   * 
   * if it's not terminated by null strlen will read memory out of its bounds.
   *
   */
  struct data {
    char _[1];
  };


  /*
   * the function performs the following task
   * 1  allocate a memory block to include enough consecutive bytes
   * 2. initialize the consecutive bytes as a null terminated string
   *    with fmt and its arguments
   * 
   * return: the start address of the consecutive bytes that is 
   *         null termianted and strlen is 0.
   *         the address can be safely casted to struct cee_block *
   *
   * e.g.
   *
   *      allocate an empty string
   *      cee_str (""); 
   * 
   *      allocate a string for int 10
   *      cee_str ("%d", 10);
   *
   */
  extern str::data  * mk (state::data *s, const char * fmt, ...);


  /*
   * the function performs the following task
   * 1  allocate a memory block to include n consecutive bytes
   * 2. initialize the consecutive bytes with fmt and its arguments
   * 
   * return: the start address of the consecutive bytes that is
   *         null terminated.
   *         the address can be safely casted to struct cee_block *
   * e.g.
   *      allocate a string buffer of 100 bytes, and initialize it with 
   *      an empty string.
   *      cee_str_n(100, "");
   * 
   *      allocate a string buffer of 100 bytes and initialize it with
   *      an integer
   *      cee_str_n(100, "%d", 10);
   *
   */
  extern str::data  * mk_e (state::data * s, size_t n, const char * fmt, ...);

  /*
   * return the pointer of the null terminator;
   * if the array is not null terminated, 
   * NULL is returned.
   */
  extern char * end (struct str::data *);

  /*
   * str: points to the begin of a struct cee_block
   *
   * the function performs one task
   * 1. add any char to the end of str
   *
   * return: the start address of a cee_block, a new cee_block will
   *         be allocated if the cee_block is too small.
   */
  extern str::data * add (str::data * str, char);

  /*
   * just like the standard strcat, but this function composes the src
   * string through a fmt string and its varadic arguments.
   */
  extern str::data * catf (str::data *, const char * fmt, ...);
  extern str::data * ncat (str::data *, char * s, size_t);
};
  
/* an auto expandable list */
namespace list {
  struct data {
    void * _[1]; // an array of `void *`s
  };

  /*
   * capacity: the initial capacity of the list
   * when the list is deleted, its elements will be handled by 
   * the default deletion policy
   */
  extern list::data * mk (state::data * s, size_t capacity);

  /*
   *
   */
  extern list::data * mk_e (state::data * s, enum del_policy o, size_t size);

  /*
   * it may return a new list if the parameter list is too small
   */
  extern list::data * append(list::data ** v, void * e);


  /*
   * it inserts an element e at index and shift the rest elements 
   * to higher indices
   */
  extern list::data * insert(list::data ** v, size_t index, void * e);

  /*
   * it removes an element at index and shift the rest elements
   * to lower indices
   */
  extern bool remove(list::data * v, size_t index);

  /*
   * returns the number of elements in the list
   */
  extern size_t size(list::data *);

  /*
   *
   */
  extern size_t capacity (list::data *);
};

  
namespace tuple {
  struct data {
    void * _[2];
  };


  /*
   * construct a tuple from its parameters
   * v1: the first value of the tuple
   * v2: the second value of the tuple
   */
  extern tuple::data * mk (state::data * s, void * v1, void * v2);
  extern tuple::data * mk_e (state::data * s, 
                             enum del_policy o[2], void * v1, void * v2);
}

namespace triple {
  struct data {
    void * _[3];
  };

  /* 
   * construct a triple from its parameters
   * v1: the first value of the triple
   * v2: the second value of the triple
   * v3: the third value of the triple
   * when the triple is deleted, its elements will not be deleted
   */
  extern triple::data * mk(state::data * s, void * v1, void * v2, void * v3);
  extern triple::data * mk_e(state::data * s, 
                             enum del_policy o[3], void * v1, void * v2, void * v3);
};

  
namespace quadruple {
  struct data {
    void * _[4];
  };

  /* 
   * construct a triple from its parameters
   * v1: the first value of the quaruple
   * v2: the second value of the quaruple
   * v3: the third value of the quadruple
   * v4: the fourth value of the quadruple
   * when the quadruple is deleted, its elements will not be deleted
   */
  extern quadruple::data * mk(state::data * s, 
                              void * v1, void * v2, void * v3, void * v4);

  extern quadruple::data * mk_e(state::data * s, 
                                enum del_policy o[4], void * v1, void * v2, 
                                void *v3, void *v4);
}

namespace n_tuple {
  struct data {
    void * _[1];  // n elements
  };
  extern n_tuple::data * mk (state::data * s, size_t n, ...);
  extern n_tuple::data * mk_e (state::data * s, size_t n, enum del_policy o[], ...);
};


namespace set {
  struct data {
    void * _;
  };

  /*
   * a binary tree based set implementation
   * cmp: the function to compare two elements, it returns 0 
   * if they are equal; it returns large than 0 if the first 
   * parameter is larger than the second parameter; it returns 
   * a value smaller than 0 if the first parameter is smaller than
   * the second parameters;
   *
   * dt: specifiy how its element should be handled when the set is deleted.
   *
   */
  extern set::data * mk (state::data * s, int (*cmp)(const void *, const void *));
  extern set::data * mk_e (state::data *s, enum del_policy o, 
                           int (*cmp)(const void *, const void *));

  extern void add(set::data * m, void * key);
  extern void * find(set::data * m, void * key);
  extern void * remove(set::data * m, void * key);
  extern void clear (set::data * m);
  extern size_t size(set::data * m);
  extern bool empty(set::data * s);
  extern list::data * values(set::data * m);
  extern set::data * union_sets (set::data * s1, set::data * s2);
}

namespace map {
  struct data {
    void * _;
  };

  /*
   * map implementation based on binary tree
   * add/remove
   */
  extern map::data * mk(state::data * s, cmp_fun cmp);
  extern map::data * mk_e(state::data * s, enum del_policy o[2], cmp_fun cmp);

  extern uintptr_t size(map::data *);
  extern void add(map::data * m, void * key, void * value);
  extern void * find(map::data * m, void * key);
  extern void * remove(map::data *m, void * key);
  extern list::data * keys(map::data *m);
  extern list::data * values(map::data *m);
};


namespace dict {
  /*
   * dict behaviors like a map with the following properties
   * 
   * 1. fixed size
   * 2. key is char *
   * 3. insertion only
   *
   */
  struct data {
    char _[1];  // opaque data
  };

  /*
   *
   */
  extern dict::data * mk (state::data * s, size_t n);
  extern dict::data * mk_e (state::data * s, enum del_policy o, size_t n);

  extern void add(dict::data * d, char * key, void * value);
  extern void * find(dict::data * d, char * key);
};

namespace stack {
  /*
   * a stack with a fixed size
   */
  struct data {
    void * _[1];
  };
  /*
   * create a fixed size stack
   * size: the size of the stack
   * dt: specify how its element should be handled when the stack is deleted.
   */
  extern stack::data * mk(state::data *s, size_t n);
  extern stack::data * mk_e (state::data *s, enum del_policy o, size_t n);

  /*
   * return the element nth element away from the top element
   */
  extern void * top(stack::data *, size_t nth);
  /*
   * pop out the top element and return it
   */
  extern void * pop(stack::data *);
  /*
   * push an element to the top of the stack
   */
  extern int push(stack::data *, void *);
  /*
   * test if the stack is empty
   */
  extern bool empty (stack::data *);
  /*
   * test if the stack is full
   */
  extern bool full (stack::data *);
  /*
   * return the size of the stack
   */
  extern uintptr_t size (stack::data *);
};
  
  
namespace singleton {  
  /*
   * singleton
   */
  struct data {
    tag_t  tag;
    uintptr_t val;
  };
  extern singleton::data * init(void *, uintptr_t tag, uintptr_t val);
  #define CEE_SINGLETON_SIZE (sizeof(struct cee::singleton::data) + sizeof(struct cee::sect))

}
  
  
namespace boxed {
  enum primitive_type {
    primitive_f64 = 1,
    primitive_f32,
    primitive_u64,
    primitive_u32,
    primitive_u16,
    primitive_u8,
    primitive_i64,
    primitive_i32,
    primitive_i16,
    primitive_i8
  };
  union primitive_value {
    double   f64;
    float    f32;
    uint64_t u64;
    uint32_t u32;
    uint16_t u16;
    uint8_t  u8;
    int64_t  i64;
    int32_t  i32;
    int16_t  i16;
    int8_t   i8;
  };

  /*
   * boxed primitive value
   */
  struct data {
    union primitive_value _;
  };

  extern boxed::data * from_double(state::data *, double);
  extern boxed::data * from_float(state::data *, float);

  extern boxed::data * from_u64(state::data *, uint64_t);
  extern boxed::data * from_u32(state::data *, uint32_t);
  extern boxed::data * from_u16(state::data *, uint16_t);
  extern boxed::data * from_u8(state::data *, uint8_t);

  extern boxed::data * from_i64(state::data *, int64_t);
  extern boxed::data * from_i32(state::data *, int32_t);
  extern boxed::data * from_i16(state::data *, int16_t);
  extern boxed::data * from_i8(state::data *, int8_t);

  extern double   to_double(boxed::data * x);
  extern float    to_float(boxed::data * x);
  
  extern uint64_t to_u64(boxed::data * x);
  extern uint32_t to_u32(boxed::data * x);
  extern uint16_t to_u16(boxed::data * x);
  extern uint8_t  to_u8(boxed::data * x);

  extern int64_t  to_i64(boxed::data * x);
  extern int32_t  to_i32(boxed::data * x);
  extern int16_t  to_i16(boxed::data * x);
  extern int8_t   to_i8(boxed::data * x);

  /*
   * number of bytes needed to print out the value
   */
  extern size_t snprint(char * buf, size_t size, boxed::data *p);
};
  
namespace tagged {
  struct data;
  
  union ptr {
    void * _;
    str::data       * str;
    set::data       * set;
    list::data      * list;
    map::data       * map;
    dict::data      * dict;
    tuple::data     * tuple;
    triple::data    * triple;
    quadruple::data * quadruple;
    block::data     * block;
    boxed::data     * boxed;
    singleton::data * singleton;
    stack::data     * stack;
    tagged::data    * tagged;
  };
  
  
  /*
   * the generic tagged value is useful to construct tagged union
   * runtime checking is needed. 
   */
  struct data {
    tag_t tag;
    union ptr ptr;
  };

  /*
   * tag: any integer value
   * v: a pointer
   */
  extern tagged::data * mk (state::data *, uintptr_t tag, void * v);
  extern tagged::data * mk_e (state::data *, enum del_policy o, uintptr_t tag, void *v);
}

namespace env {
  struct data {
    env::data  * outer;
    map::data  * vars;
  };
  extern env::data * mk(state::data *, env::data * outer, map::data vars);
  extern env::data * mk_e(state::data *, enum del_policy dp[2], env::data * outer, 
                          map::data * vars);
};

namespace closure {
  struct data {
    env::data * env;
    void (*fun)(env::data * env, size_t n, ...);
  };
  
  extern closure::data * mk(env::data * env, void * fun);
};

extern void use_realloc(void *);
extern void use_malloc(void *);
  
  /*
   * release the memory block pointed by p immediately
   * it may follow the points-to edges to delete
   *    the in-degree (reference count) of targeted memory blocks
   *    or targeted memory blocks
   *
   */
extern void del (void *);
extern void del_ref(void *);
extern void del_e (enum del_policy o, void * p);

extern void trace (void *p, enum trace_action ta);
extern int cmp (void *, void *);

extern void incr_indegree (enum del_policy o, void * p);
extern void decr_indegree (enum del_policy o, void * p);

/* 
 * return the reference count of an object
 */
extern uint16_t get_rc (void *);

/*
 * call this to cause segfault for non-recoverable errors
 */
extern void segfault() __attribute__((noreturn));

namespace state {
  struct data {
    // arbitrary number of contexts
    map::data * contexts;
    stack::data * stack;  // the stack
    struct sect * trace_tail;
    // all memory blocks are reachables from the roots
    // are considered alive
    set::data   * roots; 
    // the mark value for the next iteration
    int           next_mark;
  };
  /*
   * the size of stack
   */
  extern state::data * mk(size_t n);
  extern void add_gc_root(state::data *, void *);
  extern void remove_gc_root(state::data *, void *);
  extern void gc(state::data *);
  extern void add_context(state::data *, char * key, void * val);
  extern void remove_context(state::data *, char * key);
  extern void * get_context(state::data *, char * key);
};
  
}
#endif 
#ifndef CEE_INTERNAL_H
#define CEE_INTERNAL_H

#ifndef NULL
#define NULL     ((void *)0)
#endif 

#endif // CEE_INTERNAL_H
typedef enum { FIND, ENTER } ACTION;
typedef enum { preorder, postorder, endorder, leaf } VISIT;
typedef struct musl_entry {
 char *key;
 void *data;
} MUSL_ENTRY;
int musl_hcreate(size_t);
void musl_hdestroy(void);
MUSL_ENTRY *musl_hsearch(MUSL_ENTRY, ACTION);
struct musl_hsearch_data {
 struct __tab *__tab;
 unsigned int __unused1;
 unsigned int __unused2;
};
int musl_hcreate_r(size_t, struct musl_hsearch_data *);
void musl_hdestroy_r(struct musl_hsearch_data *);
int musl_hsearch_r(MUSL_ENTRY, ACTION, MUSL_ENTRY **, struct musl_hsearch_data *);
void musl_insque(void *, void *);
void musl_remque(void *);
void *musl_lsearch(const void *, void *, size_t *, size_t,
 int (*)(const void *, const void *));
void *musl_lfind(const void *, const void *, size_t *, size_t,
 int (*)(const void *, const void *));
void *musl_tdelete(void * cxt, const void *__restrict, void **__restrict, int(*)(void *, const void *, const void *));
void *musl_tfind(void * cxt, const void *, void *const *, int(*)(void *, const void *, const void *));
void *musl_tsearch(void * cxt, const void *, void **, int (*)(void *, const void *, const void *));
void musl_twalk(void * cxt, const void *, void (*)(void *, const void *, VISIT, int));
struct musl_qelem {
 struct qelem *q_forw, *q_back;
 char q_data[1];
};
void musl_tdestroy(void * cxt, void *, void (*)(void * cxt, void *));
/*
open addressing hash table with 2^n table size
quadratic probing is used in case of hash collision
tab indices and hash are size_t
after resize fails with ENOMEM the state of tab is still usable

with the posix api items cannot be iterated and length cannot be queried
*/
struct __tab {
  MUSL_ENTRY *entries;
  size_t mask;
  size_t used;
};
static struct musl_hsearch_data htab;
/*
static int musl_hcreate_r(size_t, struct musl_hsearch_data *);
static void musl_hdestroy_r(struct musl_hsearch_data *);
static int mul_hsearch_r(MUSL_ENTRY, ACTION, MUSL_ENTRY **, struct musl_hsearch_data *);
*/
static size_t keyhash(char *k)
{
  unsigned char *p = (unsigned char *)k;
  size_t h = 0;
  while (*p)
    h = 31*h + *p++;
  return h;
}
static int resize(size_t nel, struct musl_hsearch_data *htab)
{
  size_t newsize;
  size_t i, j;
  MUSL_ENTRY *e, *newe;
  MUSL_ENTRY *oldtab = htab->__tab->entries;
  MUSL_ENTRY *oldend = htab->__tab->entries + htab->__tab->mask + 1;
  if (nel > ((size_t)-1/2 + 1))
    nel = ((size_t)-1/2 + 1);
  for (newsize = 8; newsize < nel; newsize *= 2);
  htab->__tab->entries = (MUSL_ENTRY *)calloc(newsize, sizeof *htab->__tab->entries);
  if (!htab->__tab->entries) {
    htab->__tab->entries = oldtab;
    return 0;
  }
  htab->__tab->mask = newsize - 1;
  if (!oldtab)
    return 1;
  for (e = oldtab; e < oldend; e++)
    if (e->key) {
      for (i=keyhash(e->key),j=1; ; i+=j++) {
        newe = htab->__tab->entries + (i & htab->__tab->mask);
        if (!newe->key)
          break;
      }
      *newe = *e;
    }
  free(oldtab);
  return 1;
}
int musl_hcreate(size_t nel)
{
  return musl_hcreate_r(nel, &htab);
}
void musl_hdestroy(void)
{
  musl_hdestroy_r(&htab);
}
static MUSL_ENTRY *lookup(char *key, size_t hash, struct musl_hsearch_data *htab)
{
  size_t i, j;
  MUSL_ENTRY *e;
  for (i=hash,j=1; ; i+=j++) {
    e = htab->__tab->entries + (i & htab->__tab->mask);
    if (!e->key || strcmp(e->key, key) == 0)
      break;
  }
  return e;
}
MUSL_ENTRY *musl_hsearch(MUSL_ENTRY item, ACTION action)
{
  MUSL_ENTRY *e;
  musl_hsearch_r(item, action, &e, &htab);
  return e;
}
int musl_hcreate_r(size_t nel, struct musl_hsearch_data *htab)
{
  int r;
  htab->__tab = (struct __tab *) calloc(1, sizeof *htab->__tab);
  if (!htab->__tab)
    return 0;
  r = resize(nel, htab);
  if (r == 0) {
    free(htab->__tab);
    htab->__tab = 0;
  }
  return r;
}
void musl_hdestroy_r(struct musl_hsearch_data *htab)
{
  if (htab->__tab) free(htab->__tab->entries);
  free(htab->__tab);
  htab->__tab = 0;
}
int musl_hsearch_r(MUSL_ENTRY item, ACTION action, MUSL_ENTRY **retval,
                   struct musl_hsearch_data *htab)
{
  size_t hash = keyhash(item.key);
  MUSL_ENTRY *e = lookup(item.key, hash, htab);
  if (e->key) {
    *retval = e;
    return 1;
  }
  if (action == FIND) {
    *retval = 0;
    return 0;
  }
  *e = item;
  if (++htab->__tab->used > htab->__tab->mask - htab->__tab->mask/4) {
    if (!resize(2*htab->__tab->used, htab)) {
      htab->__tab->used--;
      e->key = 0;
      *retval = 0;
      return 0;
    }
    e = lookup(item.key, hash, htab);
  }
  *retval = e;
  return 1;
}
struct _musl_lsearch__node {
  struct _musl_lsearch__node *next;
  struct _musl_lsearch__node *prev;
};
void musl_insque(void *element, void *pred)
{
  struct _musl_lsearch__node *e = (struct _musl_lsearch__node *)element;
  struct _musl_lsearch__node *p = (struct _musl_lsearch__node *)pred;
  if (!p) {
    e->next = e->prev = 0;
    return;
  }
  e->next = p->next;
  e->prev = p;
  p->next = e;
  if (e->next)
    e->next->prev = e;
}
void musl_remque(void *element)
{
  struct _musl_lsearch__node *e = (struct _musl_lsearch__node *)element;
  if (e->next)
    e->next->prev = e->prev;
  if (e->prev)
    e->prev->next = e->next;
}
void *musl_lsearch(const void *key, void *base, size_t *nelp, size_t width,
  int (*compar)(const void *, const void *))
{
  char **p = (char **)base;
  size_t n = *nelp;
  size_t i;
  for (i = 0; i < n; i++)
    if (compar(p[i], key) == 0)
      return p[i];
  *nelp = n+1;
  // b.o. here when width is longer than the size of key
  return memcpy(p[n], key, width);
}
void *musl_lfind(const void *key, const void *base, size_t *nelp,
  size_t width, int (*compar)(const void *, const void *))
{
  char **p = (char **)base;
  size_t n = *nelp;
  size_t i;
  for (i = 0; i < n; i++)
    if (compar(p[i], key) == 0)
      return p[i];
  return 0;
}
/* AVL tree height < 1.44*log2(nodes+2)-0.3, MAXH is a safe upper bound.  */
struct _cee_tsearch_node {
  const void *key;
  void *a[2];
  int h;
};
static int height(void *n) { return n ? ((struct _cee_tsearch_node *)n)->h : 0; }
static int rot(void **p, struct _cee_tsearch_node *x, int dir /* deeper side */)
{
  struct _cee_tsearch_node *y = (struct _cee_tsearch_node *)x->a[dir];
  struct _cee_tsearch_node *z = (struct _cee_tsearch_node *)y->a[!dir];
  int hx = x->h;
  int hz = height(z);
  if (hz > height(y->a[dir])) {
    /*
     *   x
     *  / \ dir          z
     * A   y            /      *    / \   -->    x   y
y
     *   z   D        /|   |     *  / \          A B   C D
D
     * B   C
     */
    x->a[dir] = z->a[!dir];
    y->a[!dir] = z->a[dir];
    z->a[!dir] = x;
    z->a[dir] = y;
    x->h = hz;
    y->h = hz;
    z->h = hz+1;
  } else {
    /*
     *   x               y
     *  / \             /      * A   y    -->    x   D
D
     *    / \         /      *   z   D       A   z
z
     */
    x->a[dir] = z;
    y->a[!dir] = x;
    x->h = hz+1;
    y->h = hz+2;
    z = y;
  }
  *p = z;
  return z->h - hx;
}
/* balance *p, return 0 if height is unchanged.  */
static int __tsearch_balance(void **p)
{
  struct _cee_tsearch_node *n = (struct _cee_tsearch_node *)*p;
  int h0 = height(n->a[0]);
  int h1 = height(n->a[1]);
  if (h0 - h1 + 1u < 3u) {
    int old = n->h;
    n->h = h0<h1 ? h1+1 : h0+1;
    return n->h - old;
  }
  return rot(p, n, h0<h1);
}
void *musl_tsearch(void *cxt, const void *key, void **rootp,
  int (*cmp)(void *, const void *, const void *))
{
  if (!rootp)
    return 0;
  void **a[(sizeof(void*)*8*3/2)];
  struct _cee_tsearch_node *n = (struct _cee_tsearch_node *)*rootp;
  struct _cee_tsearch_node *r;
  int i=0;
  a[i++] = rootp;
  for (;;) {
    if (!n)
      break;
    int c = cmp(cxt, key, n->key);
    if (!c)
      return n;
    a[i++] = &n->a[c>0];
    n = (struct _cee_tsearch_node *)n->a[c>0];
  }
  r = (struct _cee_tsearch_node *)malloc(sizeof *r);
  if (!r)
    return 0;
  r->key = key;
  r->a[0] = r->a[1] = 0;
  r->h = 1;
  /* insert new node, rebalance ancestors.  */
  *a[--i] = r;
  while (i && __tsearch_balance(a[--i]));
  return r;
}
void musl_tdestroy(void * cxt, void *root, void (*freekey)(void *, void *))
{
  struct _cee_tsearch_node *r = (struct _cee_tsearch_node *)root;
  if (r == 0)
    return;
  musl_tdestroy(cxt, r->a[0], freekey);
  musl_tdestroy(cxt, r->a[1], freekey);
  if (freekey) freekey(cxt, (void *)r->key);
  free(r);
}
void *musl_tfind(void * cxt, const void *key, void *const *rootp,
  int(*cmp)(void * cxt, const void *, const void *))
{
  if (!rootp)
    return 0;
  struct _cee_tsearch_node *n = (struct _cee_tsearch_node *)*rootp;
  for (;;) {
    if (!n)
      break;
    int c = cmp(cxt, key, n->key);
    if (!c)
      break;
    n = (struct _cee_tsearch_node *)n->a[c>0];
  }
  return n;
}
static void walk(void * cxt, struct _cee_tsearch_node *r,
                 void (*action)(void *, const void *, VISIT, int), int d)
{
  if (!r)
    return;
  if (r->h == 1)
    action(cxt, r, leaf, d);
  else {
    action(cxt, r, preorder, d);
    walk(cxt, (struct _cee_tsearch_node *)r->a[0], action, d+1);
    action(cxt, r, postorder, d);
    walk(cxt, (struct _cee_tsearch_node *)r->a[1], action, d+1);
    action(cxt, r, endorder, d);
  }
}
void musl_twalk(void * cxt, const void *root,
                void (*action)(void *, const void *, VISIT, int))
{
  walk(cxt, (struct _cee_tsearch_node *)root, action, 0);
}
void *musl_tdelete(void * cxt, const void * key, void ** rootp,
  int(*cmp)(void * cxt, const void *, const void *))
{
  if (!rootp)
    return 0;
  void **a[(sizeof(void*)*8*3/2)+1];
  struct _cee_tsearch_node *n = (struct _cee_tsearch_node *)*rootp;
  struct _cee_tsearch_node *parent;
  struct _cee_tsearch_node *child;
  int i=0;
  /* *a[0] is an arbitrary non-null pointer that is returned when
     the root node is deleted.  */
  a[i++] = rootp;
  a[i++] = rootp;
  for (;;) {
    if (!n)
      return 0;
    int c = cmp(cxt, key, n->key);
    if (!c)
      break;
    a[i++] = &n->a[c>0];
    n = (struct _cee_tsearch_node *)n->a[c>0];
  }
  parent = (struct _cee_tsearch_node *)*a[i-2];
  if (n->a[0]) {
    /* free the preceding node instead of the deleted one.  */
    struct _cee_tsearch_node *deleted = n;
    a[i++] = &n->a[0];
    n = (struct _cee_tsearch_node *)n->a[0];
    while (n->a[1]) {
      a[i++] = &n->a[1];
      n = (struct _cee_tsearch_node *)n->a[1];
    }
    deleted->key = n->key;
    child = (struct _cee_tsearch_node *)n->a[0];
  } else {
    child = (struct _cee_tsearch_node *)n->a[1];
  }
  /* freed node has at most one child, move it up and rebalance.  */
  if (parent == n)
    parent = NULL;
  free(n);
  *a[--i] = child;
  while (--i && __tsearch_balance(a[i]));
  return parent;
}
using namespace cee;
void cee::trace (void *p, enum trace_action ta) {
  if (!p) cee::segfault();
  struct sect * cs = (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)));
  cs->trace(p, ta);
}
/*
 * a generic resource delete function for all cee_* pointers
 */
void cee::del(void *p) {
  if (!p) cee::segfault();
  struct sect * cs = (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)));
  cs->trace(p, trace_del_follow);
}
void cee::del_ref(void *p) {
  if (!p) cee::segfault();
  struct sect * cs = (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)));
  if (cs->in_degree) cs->in_degree --;
  /* if it's retained by an owner,
     it should be freed by cee_del
  */
  if (cs->retained) return;
  if (!cs->in_degree) cs->trace(p, trace_del_follow);
}
void cee::use_realloc(void * p) {
  struct sect * cs = (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)));
  if (cs->resize_method)
    cs->resize_method = resize_with_realloc;
}
void cee::use_malloc(void * p) {
  struct sect * cs = (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)));
  if (cs->resize_method)
    cs->resize_method = resize_with_malloc;
}
void cee::segfault() {
  volatile char * c = 0;
  *c = 0;
  __builtin_unreachable();
}
static void _cee_common_incr_rc (void * p) {
  struct sect * cs = (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)));
  if (cs->retained) return;
  cs->in_degree ++;
}
static void _cee_common_decr_rc (void * p) {
  struct sect * cs = (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)));
  if (cs->retained) return;
  if (cs->in_degree)
    cs->in_degree --;
  else {
    // report warnings
  }
}
uint16_t get_in_degree (void * p) {
  struct sect * cs = (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)));
  return cs->in_degree;
}
static void _cee_common_retain (void *p) {
  struct sect * cs = (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)));
  cs->retained = 1;
}
static void _cee_common_release (void * p) {
  struct sect * cs = (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)));
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
      _cee_common_incr_rc(p);
      break;
    case dp_del:
      _cee_common_retain(p);
      break;
    case dp_noop:
      break;
  }
}
void cee::decr_indegree (enum del_policy o, void * p) {
  switch(o) {
    case dp_del_rc:
      _cee_common_decr_rc(p);
      break;
    case dp_del:
      _cee_common_release(p);
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
namespace cee {
  namespace boxed {
struct _cee_boxed_header {
  enum primitive_type type;
  struct sect cs;
  union primitive_value _[1];
};
static void _cee_boxed_chain (struct _cee_boxed_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_boxed_de_chain (struct _cee_boxed_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_boxed_header * _cee_boxed_resize(struct _cee_boxed_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_boxed_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_boxed_de_chain(h);
     ret = (struct _cee_boxed_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_boxed_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_boxed_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_boxed_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_boxed_trace (void * v, enum trace_action ta) {
  struct _cee_boxed_header * m = (struct _cee_boxed_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  switch(ta) {
    case trace_del_follow:
    case trace_del_no_follow:
      _cee_boxed_de_chain(m);
      free(m);
      break;
    default:
      m->cs.gc_mark = ta - trace_mark;
      break;
  }
}
static int _cee_boxed_cmp (void * v1, void * v2) {
  struct _cee_boxed_header * h1 = (struct _cee_boxed_header *)((void *)((char *)(v1) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  struct _cee_boxed_header * h2 = (struct _cee_boxed_header *)((void *)((char *)(v2) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  if (h1->cs.trace == h2->cs.trace)
    segfault();
  else
    segfault();
}
static struct _cee_boxed_header * _cee_boxed_mk_header(state::data * s, enum primitive_type t) {
  size_t mem_block_size = sizeof(struct _cee_boxed_header);
  struct _cee_boxed_header * b = (struct _cee_boxed_header *)malloc(mem_block_size);
  do{ memset(&b->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_boxed_chain(b, s);
  b->cs.trace = _cee_boxed_trace;
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = mem_block_size;
  b->cs.cmp = NULL;
  b->cs.n_product = 0;
  b->type = t;
  b->_[0].u64 = 0;
  return b;
}
static int _cee_boxed_cmp_double(double v1, double v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
boxed::data * from_double (state::data * s, double d) {
  size_t mem_block_size = sizeof(boxed::data);
  struct _cee_boxed_header * b = _cee_boxed_mk_header(s, primitive_f64);
  b->cs.cmp = (void *)_cee_boxed_cmp_double;
  b->_[0].f64 = d;
  return (boxed::data *)b->_;
}
static int _cee_boxed_cmp_float(float v1, float v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
boxed::data * from_float (state::data * s, float d) {
  size_t mem_block_size = sizeof(boxed::data);
  struct _cee_boxed_header * b = _cee_boxed_mk_header(s, primitive_f32);
  b->cs.cmp = (void *)_cee_boxed_cmp_float;
  b->_[0].f32 = d;
  return (boxed::data *)b->_;
}
static int _cee_boxed_cmp_u64(uint64_t v1, uint64_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
boxed::data * from_u64 (state::data * s, uint64_t d) {
  size_t mem_block_size = sizeof(boxed::data);
  struct _cee_boxed_header * b = _cee_boxed_mk_header(s, primitive_u64);
  b->_[0].u64 = d;
  return (boxed::data *)b->_;
}
static int _cee_boxed_cmp_u32(uint32_t v1, uint32_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
boxed::data * from_u32 (state::data * s, uint32_t d) {
  size_t mem_block_size = sizeof(boxed::data);
  struct _cee_boxed_header * b = _cee_boxed_mk_header(s, primitive_u32);
  b->cs.cmp = (void *)_cee_boxed_cmp_u32;
  b->_[0].u32 = d;
  return (boxed::data *)b->_;
}
static int _cee_boxed_cmp_u16(uint16_t v1, uint16_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
boxed::data * from_u16 (state::data * s, uint16_t d) {
  size_t mem_block_size = sizeof(boxed::data);
  struct _cee_boxed_header * b = _cee_boxed_mk_header(s, primitive_u16);
  b->cs.cmp = (void *) _cee_boxed_cmp_u16;
  b->_[0].u16 = d;
  return (boxed::data *)b->_;
}
static int _cee_boxed_cmp_u8(uint8_t v1, uint8_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
boxed::data * from_u8 (state::data * s, uint8_t d) {
  size_t mem_block_size = sizeof(boxed::data);
  struct _cee_boxed_header * b = _cee_boxed_mk_header(s, primitive_u8);
  b->cs.cmp = (void *)_cee_boxed_cmp_u8;
  b->_[0].u8 = d;
  return (boxed::data *)b->_;
}
static int _cee_boxed_cmp_i64(int64_t v1, int64_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
boxed::data * from_i64 (state::data *s, int64_t d) {
  size_t mem_block_size = sizeof(boxed::data);
  struct _cee_boxed_header * b = _cee_boxed_mk_header(s, primitive_i64);
  b->cs.cmp = (void *)_cee_boxed_cmp_i64;
  b->_[0].i64 = d;
  return (boxed::data *)b->_;
}
static int _cee_boxed_cmp_i32(int32_t v1, int32_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
boxed::data * from_i32 (state::data * s, int32_t d) {
  size_t mem_block_size = sizeof(boxed::data);
  struct _cee_boxed_header * b = _cee_boxed_mk_header(s, primitive_i32);
  b->cs.cmp = (void *)_cee_boxed_cmp_i32;
  b->_[0].i32 = d;
  return (boxed::data *)b->_;
}
static int _cee_boxed_cmp_i16(int16_t v1, int16_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
boxed::data * from_i16 (state::data * s, int16_t d) {
  size_t mem_block_size = sizeof(boxed::data);
  struct _cee_boxed_header * b = _cee_boxed_mk_header(s, primitive_i16);
  b->cs.cmp = (void *)_cee_boxed_cmp_i16;
  b->_[0].i16 = d;
  return (boxed::data *)b->_;
}
static int _cee_boxed_cmp_i8(int8_t v1, int8_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
boxed::data * from_i8 (state::data *s, int8_t d) {
  size_t mem_block_size = sizeof(boxed::data);
  struct _cee_boxed_header * b = _cee_boxed_mk_header(s, primitive_i8);
  b->cs.cmp = (void *)_cee_boxed_cmp_i8;
  b->_[0].i8 = d;
  return (boxed::data *)b->_;
}
size_t snprint (char * buf, size_t size, boxed::data * x) {
  struct _cee_boxed_header * h = (struct _cee_boxed_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  int s;
  switch(h->type)
  {
    case primitive_f64:
      s = ::snprintf(buf, size, "%lf", h->_[0].f64);
      break;
    case primitive_f32:
      s = ::snprintf(buf, size, "%f", h->_[0].f32);
      break;
    case primitive_i64:
      s = ::snprintf(buf, size, "%lld", h->_[0].i64);
      break;
    case primitive_u32:
    case primitive_u16:
    case primitive_u8:
      s = ::snprintf(buf, size, "%u", h->_[0].u32);
      break;
    case primitive_u64:
      s = ::snprintf(buf, size, "%llu", h->_[0].u64);
      break;
    case primitive_i32:
    case primitive_i16:
    case primitive_i8:
      s = ::snprintf(buf, size, "%d", h->_[0].i8);
      break;
    default:
      segfault();
      break;
  }
  if (s > 0)
    return (size_t)s;
  else
    segfault();
}
double to_double (boxed::data * x) {
  struct _cee_boxed_header * h = (struct _cee_boxed_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  if (h->type == primitive_f64)
    return h->_[0].f64;
  else
    segfault();
}
float to_float (boxed::data * x) {
  struct _cee_boxed_header * h = (struct _cee_boxed_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  if (h->type == primitive_f32)
    return h->_[0].f32;
  else
    segfault();
}
uint64_t to_u64 (boxed::data * x) {
  struct _cee_boxed_header * h = (struct _cee_boxed_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  if (h->type == primitive_u64)
    return h->_[0].u64;
  else
    segfault();
}
uint32_t to_u32 (boxed::data * x) {
  struct _cee_boxed_header * h = (struct _cee_boxed_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  if (h->type == primitive_u32)
    return h->_[0].u32;
  else
    segfault();
}
uint16_t to_u16 (boxed::data * x) {
  struct _cee_boxed_header * h = (struct _cee_boxed_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  if (h->type == primitive_u16)
    return h->_[0].u16;
  else
    segfault();
}
uint8_t to_u8 (boxed::data * x) {
  struct _cee_boxed_header * h = (struct _cee_boxed_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  if (h->type == primitive_u8)
    return h->_[0].u8;
  else
    segfault();
}
int64_t to_i64 (boxed::data * x) {
  struct _cee_boxed_header * h = (struct _cee_boxed_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  if (h->type == primitive_i64)
    return h->_[0].i64;
  else
    segfault();
}
int32_t to_i32 (boxed::data * x) {
  struct _cee_boxed_header * h = (struct _cee_boxed_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  if (h->type == primitive_i32)
    return h->_[0].i32;
  else
    segfault();
}
int16_t to_i16 (boxed::data * x) {
  struct _cee_boxed_header * h = (struct _cee_boxed_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  if (h->type == primitive_i16)
    return h->_[0].i16;
  else
    segfault();
}
int8_t to_i8 (boxed::data * x) {
  struct _cee_boxed_header * h = (struct _cee_boxed_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_boxed_header, _))));
  if (h->type == primitive_i8)
    return h->_[0].i8;
  else
    segfault();
}
  }
}
namespace cee {
  namespace str {
struct _cee_str_header {
  uintptr_t capacity;
  struct sect cs;
  char _[1];
};
static void _cee_str_chain (struct _cee_str_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_str_de_chain (struct _cee_str_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_str_header * _cee_str_resize(struct _cee_str_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_str_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_str_de_chain(h);
     ret = (struct _cee_str_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_str_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_str_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_str_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_str_trace (void * p, enum trace_action ta) {
  struct _cee_str_header * m = (struct _cee_str_header *)((void *)((char *)(p) - (__builtin_offsetof(struct _cee_str_header, _))));
  switch (ta) {
    case trace_del_no_follow:
    case trace_del_follow:
      _cee_str_de_chain(m);
      free(m);
      break;
    default:
      m->cs.gc_mark = ta - trace_mark;
      break;
  }
}
str::data * mk (state::data * st, const char * fmt, ...) {
  if (!fmt) {
    // fmt cannot be null
    // intentionally cause a segfault
    segfault();
  }
  uintptr_t s;
  va_list ap;
  va_start(ap, fmt);
  s = vsnprintf(NULL, 0, fmt, ap);
  s ++;
  s += sizeof(struct _cee_str_header);
  s = (s / 64 + 1) * 64;
  size_t mem_block_size = s;
  struct _cee_str_header * h = (struct _cee_str_header *)malloc(mem_block_size);
  do{ memset(&h->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_str_chain(h, st);
  h->cs.trace = _cee_str_trace;
  h->cs.resize_method = resize_with_malloc;
  h->cs.mem_block_size = mem_block_size;
  h->cs.cmp = (void *)strcmp;
  h->cs.cmp_stop_at_null = 1;
  h->cs.n_product = 0;
  h->capacity = s - sizeof(struct _cee_str_header);
  va_start(ap, fmt);
  vsnprintf(h->_, s, fmt, ap);
  return (str::data *)(h->_);
}
str::data * mk_e (state::data * st, size_t n, const char * fmt, ...) {
  uintptr_t s;
  va_list ap;
  if (fmt) {
    va_start(ap, fmt);
    s = vsnprintf(NULL, 0, fmt, ap);
    s ++; // including the null terminator
  }
  else
    s = n;
  s += sizeof(struct _cee_str_header);
  size_t mem_block_size = (s / 64 + 1) * 64;
  struct _cee_str_header * m = (struct _cee_str_header *) malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  m->cs.trace = _cee_str_trace;
  m->cs.resize_method = resize_with_malloc;
  m->cs.mem_block_size = mem_block_size;
  m->cs.cmp = (void *)strcmp;
  m->cs.cmp_stop_at_null = 1;
  _cee_str_chain(m, st);
  m->capacity = mem_block_size - sizeof(struct _cee_str_header);
  if (fmt) {
    va_start(ap, fmt);
    vsnprintf(m->_, mem_block_size, fmt, ap);
  }
  else {
    m->_[0] = '\0'; // terminates with '\0'
  }
  return (str::data *)(m->_);
}
static void _cee_str_noop(void * v, enum trace_action ta) {}
struct cee_block * cee_block_empty () {
  static struct _cee_str_header singleton;
  singleton.cs.trace = _cee_str_noop;
  singleton.cs.resize_method = resize_with_malloc;
  singleton.cs.mem_block_size = sizeof(struct _cee_str_header);
  singleton.capacity = 1;
  singleton._[0] = 0;
  return (struct cee_block *)&singleton._;
}
/*
 * if it's not NULL terminated, NULL should be returned
 */
char * end(str::data * str) {
  struct _cee_str_header * b = (struct _cee_str_header *)((void *)((char *)(str) - (__builtin_offsetof(struct _cee_str_header, _))));
  // TODO: fixes this
  return (char *)str + strlen((char *)str);
  /*
  int i = 0; 
  for (i = 0;i < b->used; i++)
    if (b->_[i] == '\0')
      return (b->_ + i);

  return NULL;
  */
}
/*
 * append any char (including '\0') to str;
 */
str::data * add(str::data * str, char c) {
  struct _cee_str_header * b = (struct _cee_str_header *)((void *)((char *)(str) - (__builtin_offsetof(struct _cee_str_header, _))));
  uint32_t slen = strlen((char *)str);
  if (slen < b->capacity) {
    b->_[slen] = c;
    b->_[slen+1] = '\0';
    return (str::data *)(b->_);
  }
  else {
    struct _cee_str_header * b1 = _cee_str_resize(b, b->cs.mem_block_size + 64);
    b1->capacity = b->capacity + 64;
    b1->_[b->capacity] = c;
    b1->_[b->capacity+1] = '\0';
    return (str::data *)(b1->_);
  }
}
str::data * catf(str::data * str, const char * fmt, ...) {
  struct _cee_str_header * b = (struct _cee_str_header *)((void *)((char *)(str) - (__builtin_offsetof(struct _cee_str_header, _))));
  if (!fmt)
    return str;
  size_t slen = strlen((char *)str);
  va_list ap;
  va_start(ap, fmt);
  size_t s = vsnprintf(NULL, 0, fmt, ap);
  s ++; // including the null terminator
  va_start(ap, fmt);
  if (slen + s < b->capacity) {
    vsnprintf(b->_ + slen, s, fmt, ap);
    return str;
  }
  else {
    struct _cee_str_header * b1 = _cee_str_resize(b, slen + s);
    vsnprintf(b1->_ + slen, s, fmt, ap);
    return (str::data *)(b1->_);
  }
}
str::data * ncat (str::data * str, char * s, size_t slen) {
  return NULL;
}
  }
}
namespace cee {
  namespace dict {
struct _cee_dict_header {
  struct list::data * keys;
  struct list::data * vals;
  uintptr_t size;
  enum del_policy del_policy;
  struct sect cs;
  struct musl_hsearch_data _[1];
};
static void _cee_dict_chain (struct _cee_dict_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_dict_de_chain (struct _cee_dict_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_dict_header * _cee_dict_resize(struct _cee_dict_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_dict_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_dict_de_chain(h);
     ret = (struct _cee_dict_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_dict_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_dict_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_dict_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_dict_trace(void *d, enum trace_action ta) {
  struct _cee_dict_header * m = (struct _cee_dict_header *)((void *)((char *)(d) - (__builtin_offsetof(struct _cee_dict_header, _))));
  switch (ta) {
    case trace_del_no_follow:
      musl_hdestroy_r(m->_);
      _cee_dict_de_chain(m);
      free(m);
      break;
    case trace_del_follow:
      del_e(m->del_policy, m->keys);
      del_e(m->del_policy, m->vals);
      musl_hdestroy_r(m->_);
      _cee_dict_de_chain(m);
      free(m);
      break;
    default:
      m->cs.gc_mark = ta - trace_mark;
      trace(m->keys, ta);
      trace(m->vals, ta);
      break;
  }
}
dict::data * mk_e (state::data * s, enum del_policy o, size_t size) {
  size_t mem_block_size = sizeof(struct _cee_dict_header);
  struct _cee_dict_header * m = (struct _cee_dict_header *)malloc(mem_block_size);
  m->del_policy = o;
  m->keys = list::mk(s, size);
  use_realloc(m->keys);
  m->vals = list::mk(s, size);
  use_realloc(m->vals);
  m->size = size;
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_dict_chain(m, s);
  m->cs.trace = _cee_dict_trace;
  m->cs.mem_block_size = mem_block_size;
  m->cs.resize_method = resize_with_identity;
  m->cs.n_product = 2; // key:str, value
  size_t hsize = (size_t)((float)size * 1.25);
  memset(m->_, 0, sizeof(struct musl_hsearch_data));
  if (musl_hcreate_r(hsize, m->_)) {
    return (dict::data *)(&m->_);
  }
  else {
    del(m->keys);
    del(m->vals);
    free(m);
    return NULL;
  }
}
dict::data * mk (state::data *s, size_t size) {
  return dict::mk_e (s, CEE_DEFAULT_DEL_POLICY, size);
}
void add (dict::data * d, char * key, void * value) {
  struct _cee_dict_header * m = (struct _cee_dict_header *)((void *)((char *)(d) - (__builtin_offsetof(struct _cee_dict_header, _))));
  MUSL_ENTRY n, *np;
  n.key = key;
  n.data = value;
  if (!musl_hsearch_r(n, ENTER, &np, m->_))
    segfault();
  append(&m->keys, key);
  append(&m->vals, value);
}
void * find(dict::data * d, char * key) {
  struct _cee_dict_header * m = (struct _cee_dict_header *)((void *)((char *)(d) - (__builtin_offsetof(struct _cee_dict_header, _))));
  MUSL_ENTRY n, *np;
  n.key = key;
  n.data = NULL;
  if (musl_hsearch_r(n, FIND, &np, m->_))
    return np->data;
  printf ("%s\n", strerror(errno));
  return NULL;
}
  }
}
namespace cee {
  namespace map {
struct _cee_map_header {
  void * context;
  int (*cmp)(const void *l, const void *r);
  uintptr_t size;
  enum del_policy key_del_policy;
  enum del_policy val_del_policy;
  enum trace_action ta;
  struct sect cs;
  void * _[1];
};
static void _cee_map_chain (struct _cee_map_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_map_de_chain (struct _cee_map_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_map_header * _cee_map_resize(struct _cee_map_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_map_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_map_de_chain(h);
     ret = (struct _cee_map_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_map_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_map_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_map_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_map_free_pair_follow(void * cxt, void * c) {
  del(c);
}
static void _cee_map_trace_pair (void * cxt, const void *nodep, const VISIT which, const int depth) {
  tuple::data * p;
  struct _cee_map_header * h;
  switch (which)
  {
    case preorder:
    case leaf:
      p = (tuple::data *)*(void **)nodep;
      trace(p, *(enum trace_action *)cxt);
      break;
    default:
      break;
  }
}
static void _cee_map_trace(void * p, enum trace_action ta) {
  struct _cee_map_header * h = (struct _cee_map_header *)((void *)((char *)(p) - (__builtin_offsetof(struct _cee_map_header, _))));
  switch (ta) {
    case trace_del_no_follow:
      musl_tdestroy(NULL, h->_[0], NULL);
      _cee_map_de_chain(h);
      free(h);
      break;
    case trace_del_follow:
      musl_tdestroy((void *)&ta, h->_[0], _cee_map_free_pair_follow);
      _cee_map_de_chain(h);
      free(h);
      break;
    default:
      h->cs.gc_mark = ta - trace_mark;
      h->ta = ta;
      musl_twalk(&ta, h->_[0], _cee_map_trace_pair);
      break;
  }
}
static int _cee_map_cmp (void * cxt, const void * v1, const void * v2) {
  struct _cee_map_header * h = (struct _cee_map_header *) cxt;
  tuple::data * t1 = (tuple::data *) v1;
  tuple::data * t2 = (tuple::data *) v2;
  return h->cmp(t1->_[0], t2->_[0]);
}
map::data * mk_e (state::data * st, enum del_policy o[2],
                  int (*cmp)(const void *, const void *)) {
  size_t mem_block_size = sizeof(struct _cee_map_header);
  struct _cee_map_header * m = (struct _cee_map_header *)malloc(mem_block_size);
  m->context = NULL;
  m->cmp = cmp;
  m->size = 0;
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_map_chain(m, st);
  m->cs.trace = _cee_map_trace;
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->cs.cmp = 0;
  m->cs.cmp_stop_at_null = 0;
  m->cs.n_product = 2; // key, value
  m->key_del_policy = o[0];
  m->val_del_policy = o[1];
  m->_[0] = 0;
  return (map::data *)m->_;
}
map::data * mk(state::data * st, int (*cmp) (const void *, const void *)) {
  static enum del_policy d[2] = { CEE_DEFAULT_DEL_POLICY, CEE_DEFAULT_DEL_POLICY };
  return mk_e(st, d, cmp);
}
uintptr_t size(struct map::data * m) {
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  return b->size;
}
void add(map::data * m, void * key, void * value) {
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  enum del_policy d[2];
  d[0] = b->key_del_policy;
  d[1] = b->val_del_policy;
  tuple::data * t = tuple::mk_e(b->cs.state, d, key, value);
  tuple::data ** oldp = (tuple::data **)musl_tsearch(b, t, b->_, _cee_map_cmp);
  if (oldp == NULL)
    segfault(); // run out of memory
  else if (*oldp != t)
    del(t);
  else
    b->size ++;
  return;
}
void * find(map::data * m, void * key) {
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  tuple::data t = { key, 0 };
  tuple::data **pp = (tuple::data **)musl_tfind(b, &t, b->_, _cee_map_cmp);
  if (pp == NULL)
    return NULL;
  else {
    tuple::data * p = *pp;
    return p->_[1];
  }
}
void * remove(map::data * m, void * key) {
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  void ** oldp = (void **)musl_tdelete(b, key, b->_, _cee_map_cmp);
  if (oldp == NULL)
    return NULL;
  else {
    b->size --;
    tuple::data * ret = (tuple::data *)*oldp;
    del(ret);
    decr_indegree(b->key_del_policy, ret->_[0]);
    decr_indegree(b->val_del_policy, ret->_[1]);
    return ret->_[1];
  }
}
static void _cee_map_get_key (void * cxt, const void *nodep, const VISIT which, const int depth) {
  tuple::data * p;
  switch (which)
  {
    case preorder:
    case leaf:
      p = *(tuple::data **)nodep;
      list::append((list::data **)cxt, p->_[0]);
      break;
    default:
      break;
  }
}
list::data * keys(map::data * m) {
  uintptr_t n = map::size(m);
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  list::data * keys = list::mk(b->cs.state, n);
  b->context = keys;
  musl_twalk(&keys, b->_[0], _cee_map_get_key);
  return keys;
}
static void _cee_map_get_value (void * cxt, const void *nodep, const VISIT which, const int depth) {
  tuple::data * p;
  switch (which)
  {
    case preorder:
    case leaf:
      p = (tuple::data *)*(void **)nodep;
      list::append((list::data **)cxt, p->_[1]);
      break;
    default:
      break;
  }
}
list::data * values(map::data * m) {
  uintptr_t s = map::size(m);
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  list::data * values = list::mk(b->cs.state, s);
  b->context = values;
  musl_twalk(&values, b->_[0], _cee_map_get_value);
  return values;
}
  }
}
namespace cee {
  namespace set {
struct _cee_set_header {
  void * context;
  int (*cmp)(const void *l, const void *r);
  uintptr_t size;
  enum del_policy del_policy;
  enum trace_action ta;
  struct sect cs;
  void * _[1];
};
static void _cee_set_chain (struct _cee_set_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_set_de_chain (struct _cee_set_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_set_header * _cee_set_resize(struct _cee_set_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_set_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_set_de_chain(h);
     ret = (struct _cee_set_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_set_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_set_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_set_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_set_free_pair_follow (void * cxt, void * c) {
  enum del_policy dp = * (enum del_policy *) cxt;
  del_e(dp, c);
}
static void _cee_set_trace_pair (void * cxt, const void *nodep, const VISIT which, const int depth) {
  void * p;
  struct _cee_set_header * h;
  switch (which)
  {
    case preorder:
    case leaf:
      p = *(void **)nodep;
      trace(p, *((enum trace_action *)cxt));
      break;
    default:
      break;
  }
}
static void _cee_set_trace(void * p, enum trace_action ta) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(p) - (__builtin_offsetof(struct _cee_set_header, _))));
  switch (ta) {
    case trace_del_no_follow:
      musl_tdestroy(NULL, h->_[0], NULL);
      _cee_set_de_chain(h);
      free(h);
      break;
    case trace_del_follow:
      musl_tdestroy(NULL, h->_[0], _cee_set_free_pair_follow);
      _cee_set_de_chain(h);
      free(h);
      break;
    default:
      h->cs.gc_mark = ta - trace_mark;
      h->ta = ta;
      musl_twalk(&ta, h->_[0], _cee_set_trace_pair);
      break;
  }
}
int _cee_set_cmp (void * cxt, const void * v1, const void *v2) {
  struct _cee_set_header * h = (struct _cee_set_header *) cxt;
  return h->cmp(v1, v2);
}
/*
 * create a new set and the equality of 
 * its two elements are decided by cmp
 * dt: specify how its elements should be handled if the set is deleted.
 */
set::data * mk_e (state::data * st, enum del_policy o,
                  int (*cmp)(const void *, const void *))
{
  struct _cee_set_header * m = (struct _cee_set_header *)malloc(sizeof(struct _cee_set_header));
  m->cmp = cmp;
  m->size = 0;
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_set_chain(m, st);
  m->cs.trace = _cee_set_trace;
  m->cs.resize_method = resize_with_identity;
  m->cs.n_product = 1;
  m->context = NULL;
  m->_[0] = NULL;
  m->del_policy = o;
  return (set::data *)m->_;
}
set::data * mk (state::data * s, int (*cmp)(const void *, const void *)) {
  return set::mk_e(s, CEE_DEFAULT_DEL_POLICY, cmp);
}
size_t size (set::data * s) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(s) - (__builtin_offsetof(struct _cee_set_header, _))));
  return h->size;
}
bool empty (set::data * s) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(s) - (__builtin_offsetof(struct _cee_set_header, _))));
  return h->size == 0;
}
/*
 * add an element key to the set m
 * 
 */
void add(set::data *m, void * val) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_set_header, _))));
  void ** oldp = (void **) musl_tsearch(h, val, h->_, _cee_set_cmp);
  if (oldp == NULL)
    segfault();
  else if (*oldp != (void *)val)
    return;
  else {
    h->size ++;
    incr_indegree(h->del_policy, val);
  }
  return;
}
static void _cee_set_del(void * cxt, void * p) {
  enum del_policy dp = *((enum del_policy *)cxt);
  switch(dp) {
    case dp_del_rc:
      del_ref(p);
      break;
    case dp_del:
      del(p);
      break;
    case dp_noop:
      break;
  }
}
void cee_set_clear (set::data * s) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(s) - (__builtin_offsetof(struct _cee_set_header, _))));
  musl_tdestroy(&h->del_policy, h->_[0], _cee_set_del);
  h->_[0] = NULL;
  h->size = 0;
}
void * find(set::data *m, void * key) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_set_header, _))));
  void **oldp = (void **) musl_tfind(h, key, h->_, _cee_set_cmp);
  if (oldp == NULL)
    return NULL;
  else
    return *oldp;
}
static void _cee_set_get_value (void * cxt, const void *nodep, const VISIT which, const int depth) {
  void * p;
  switch (which)
  {
    case preorder:
    case leaf:
      p = *(void **)nodep;
      list::append((list::data **)cxt, p);
      break;
    default:
      break;
  }
}
list::data * values(set::data * m) {
  uintptr_t s = set::size(m);
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_set_header, _))));
  h->context = list::mk(h->cs.state, s);
  use_realloc(h->context);
  musl_twalk(&h->context, h->_[0], _cee_set_get_value);
  return (list::data *)h->context;
}
void * remove(set::data *m, void * key) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_set_header, _))));
  void ** old = (void **)musl_tfind(h, key, h->_, _cee_set_cmp);
  if (old == NULL)
    return NULL;
  else {
    h->size --;
    void * k = *old;
    musl_tdelete(h, key, h->_, _cee_set_cmp);
    return k;
  }
}
set::data * union_set (state::data * s, set::data * s1, set::data * s2) {
  struct _cee_set_header * h1 = (struct _cee_set_header *)((void *)((char *)(s1) - (__builtin_offsetof(struct _cee_set_header, _))));
  struct _cee_set_header * h2 = (struct _cee_set_header *)((void *)((char *)(s2) - (__builtin_offsetof(struct _cee_set_header, _))));
  if (h1->cmp == h2->cmp) {
    set::data * s0 = set::mk(s, h1->cmp);
    list::data * v1 = set::values(s1);
    list::data * v2 = set::values(s2);
    int i;
    for (i = 0; i < list::size(v1); i++)
      set::add(s0, v1->_[i]);
    for (i = 0; i < list::size(v2); i++)
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
namespace cee {
  namespace stack {
struct _cee_stack_header {
  uintptr_t used;
  uintptr_t top;
  uintptr_t capacity;
  enum del_policy del_policy;
  struct sect cs;
  void * _[];
};
static void _cee_stack_chain (struct _cee_stack_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_stack_de_chain (struct _cee_stack_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_stack_header * _cee_stack_resize(struct _cee_stack_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_stack_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_stack_de_chain(h);
     ret = (struct _cee_stack_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_stack_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_stack_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_stack_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_stack_trace (void * v, enum trace_action ta) {
  struct _cee_stack_header * m = (struct _cee_stack_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_stack_header, _))));
  int i;
  switch (ta) {
    case trace_del_no_follow:
      _cee_stack_de_chain(m);
      free(m);
      break;
    case trace_del_follow:
      for (i = 0; i < m->used; i++)
        del_e(m->del_policy, m->_[i]);
      _cee_stack_de_chain(m);
      free(m);
      break;
    default:
      m->cs.gc_mark = ta - trace_mark;
      for (i = 0; i < m->used; i++)
        trace(m->_[i], ta);
      break;
  }
}
stack::data * mk_e (state::data * st, enum del_policy o, size_t size) {
  uintptr_t mem_block_size = sizeof(struct _cee_stack_header) + size * sizeof(void *);
  struct _cee_stack_header * m = (struct _cee_stack_header *)malloc(mem_block_size);
  m->capacity = size;
  m->used = 0;
  m->top = (0-1);
  m->del_policy = o;
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_stack_chain(m, st);
  m->cs.trace = _cee_stack_trace;
  m->cs.mem_block_size = mem_block_size;
  return (stack::data *)(m->_);
}
stack::data * mk (state::data * st, size_t size) {
  return mk_e(st, CEE_DEFAULT_DEL_POLICY, size);
}
int push (stack::data * v, void *e) {
  struct _cee_stack_header * m = (struct _cee_stack_header *)((void *)((char *)((void **)v) - (__builtin_offsetof(struct _cee_stack_header, _))));
  if (m->used == m->capacity)
    return 0;
  m->top ++;
  m->used ++;
  m->_[m->top] = e;
  incr_indegree(m->del_policy, e);
  return 1;
}
void * pop (stack::data * v) {
  struct _cee_stack_header * b = (struct _cee_stack_header *)((void *)((char *)((void **)v) - (__builtin_offsetof(struct _cee_stack_header, _))));
  if (b->used == 0) {
    return NULL;
  }
  else {
    void * p = b->_[b->top];
    b->used --;
    b->top --;
    decr_indegree(b->del_policy, p);
    return p;
  }
}
/*
 *  nth: 0 -> the topest element
 *       1 -> 1 element way from the topest element
 */
void * top (stack::data * v, uintptr_t nth) {
  struct _cee_stack_header * b = (struct _cee_stack_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_stack_header, _))));
  if (b->used == 0 || nth >= b->used)
    return NULL;
  else
    return b->_[b->top-nth];
}
uintptr_t size (stack::data *x) {
  struct _cee_stack_header * m = (struct _cee_stack_header *)((void *)((char *)((void **)x) - (__builtin_offsetof(struct _cee_stack_header, _))));
  return m->used;
}
/*
uintptr_t stack::capacity (stack::data *s) {
  struct S(header) * m = FIND_HEADER(s);
  return m->capacity;
}
*/
bool empty (stack::data *x) {
  struct _cee_stack_header * b = (struct _cee_stack_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_stack_header, _))));
  return b->used == 0;
}
bool full (stack::data *x) {
  struct _cee_stack_header * b = (struct _cee_stack_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_stack_header, _))));
  return b->used >= b->capacity;
}
  }
}
namespace cee {
  namespace tuple {
struct _cee_tuple_header {
  enum del_policy del_policies[2];
  struct sect cs;
  void * _[2];
};
static void _cee_tuple_chain (struct _cee_tuple_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_tuple_de_chain (struct _cee_tuple_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_tuple_header * _cee_tuple_resize(struct _cee_tuple_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_tuple_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_tuple_de_chain(h);
     ret = (struct _cee_tuple_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_tuple_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_tuple_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_tuple_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_tuple_trace(void * v, enum trace_action ta) {
  struct _cee_tuple_header * b = (struct _cee_tuple_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_tuple_header, _))));
  int i;
  switch (ta) {
    case trace_del_no_follow:
      _cee_tuple_de_chain(b);
      free(b);
      break;
    case trace_del_follow:
      for (i = 0; i < 2; i++)
        del_e(b->del_policies[i], b->_[i]);
      _cee_tuple_de_chain(b);
      free(b);
      break;
    default:
      b->cs.gc_mark = ta - trace_mark;
      for (i = 0; i < 2; i++)
        trace(b->_[i], ta);
      break;
  }
}
tuple::data * mk_e (state::data * st, enum del_policy o[2], void * v1, void * v2) {
  size_t mem_block_size = sizeof(struct _cee_tuple_header);
  struct _cee_tuple_header * m = (struct _cee_tuple_header *) malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_tuple_chain(m, st);
  m->cs.trace = _cee_tuple_trace;
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->cs.state = st;
  m->_[0] = v1;
  m->_[1] = v2;
  int i;
  for (i = 0; i < 2; i++) {
    m->del_policies[i] = o[i];
    incr_indegree(o[i], m->_[i]);
  }
  return (tuple::data *)&m->_;
}
tuple::data * mk (state::data * st, void * v1, void * v2) {
  static enum del_policy o[2] = { CEE_DEFAULT_DEL_POLICY, CEE_DEFAULT_DEL_POLICY };
  return mk_e(st, o, v1, v2);
}
  }
}
namespace cee {
  namespace triple {
struct _cee_triple_header {
  enum del_policy del_policies[3];
  struct sect cs;
  void * _[3];
};
static void _cee_triple_chain (struct _cee_triple_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_triple_de_chain (struct _cee_triple_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_triple_header * _cee_triple_resize(struct _cee_triple_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_triple_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_triple_de_chain(h);
     ret = (struct _cee_triple_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_triple_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_triple_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_triple_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_triple_trace(void * v, enum trace_action ta) {
  struct _cee_triple_header * b = (struct _cee_triple_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_triple_header, _))));
  int i;
  switch (ta) {
    case trace_del_no_follow:
      _cee_triple_de_chain(b);
      free(b);
      break;
    case trace_del_follow:
      for (i = 0; i < 3; i++)
        del_e(b->del_policies[i], b->_[i]);
      _cee_triple_de_chain(b);
      free(b);
      break;
    default:
      b->cs.gc_mark = ta - trace_mark;
      for (i = 0; i < 3; i++)
        trace(b->_[i], ta);
      break;
  }
}
triple::data * mk_e (state::data * st, enum del_policy o[3], void * v1, void * v2, void * v3) {
  size_t mem_block_size = sizeof(struct _cee_triple_header);
  struct _cee_triple_header * m = (struct _cee_triple_header *)malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_triple_chain(m, st);
  m->cs.trace = _cee_triple_trace;
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->cs.state = st;
  m->_[0] = v1;
  m->_[1] = v2;
  m->_[2] = v3;
  int i;
  for (i = 0; i < 3; i++) {
    m->del_policies[i] = o[i];
    incr_indegree(o[i], m->_[i]);
  }
  return (triple::data *)&m->_;
}
triple::data * mk (state::data * st, void * v1, void * v2, void *v3) {
  static enum del_policy o[3] = { CEE_DEFAULT_DEL_POLICY,
                                 CEE_DEFAULT_DEL_POLICY,
                                 CEE_DEFAULT_DEL_POLICY };
  return mk_e(st, o, v1, v2, v3);
}
  }
}
namespace cee {
  namespace quadruple {
struct _cee_quadruple_header {
  enum del_policy del_policies[4];
  struct sect cs;
  void * _[4];
};
static void _cee_quadruple_chain (struct _cee_quadruple_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_quadruple_de_chain (struct _cee_quadruple_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_quadruple_header * _cee_quadruple_resize(struct _cee_quadruple_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_quadruple_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_quadruple_de_chain(h);
     ret = (struct _cee_quadruple_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_quadruple_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_quadruple_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_quadruple_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_quadruple_trace(void * v, enum trace_action ta) {
  struct _cee_quadruple_header * b = (struct _cee_quadruple_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_quadruple_header, _))));
  int i;
  switch (ta) {
    case trace_del_no_follow:
      _cee_quadruple_de_chain(b);
      free(b);
      break;
    case trace_del_follow:
      for (i = 0; i < 4; i++)
        del_e(b->del_policies[i], b->_[i]);
      _cee_quadruple_de_chain(b);
      free(b);
      break;
    default:
      b->cs.gc_mark = ta - trace_mark;
      for (i = 0; i < 4; i++)
        trace(b->_[i], ta);
      break;
  }
}
quadruple::data * mk_e (state::data * st, enum del_policy o[4],
                        void * v1, void * v2, void * v3, void * v4) {
  size_t mem_block_size = sizeof(struct _cee_quadruple_header);
  struct _cee_quadruple_header * m = (struct _cee_quadruple_header *) malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_quadruple_chain(m, st);
  m->cs.trace = _cee_quadruple_trace;
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->cs.n_product = 4;
  m->cs.state = st;
  m->_[0] = v1;
  m->_[1] = v2;
  m->_[2] = v3;
  m->_[3] = v4;
  int i;
  for (i = 0; i < 4; i++) {
    m->del_policies[i] = o[i];
    incr_indegree(o[i], m->_[i]);
  }
  return (quadruple::data *)&m->_;
}
  }
}
namespace cee {
  namespace list {
struct _cee_list_header {
  uintptr_t size;
  uintptr_t capacity;
  enum del_policy del_policy;
  struct sect cs;
  void * _[];
};
static void _cee_list_chain (struct _cee_list_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_list_de_chain (struct _cee_list_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_list_header * _cee_list_resize(struct _cee_list_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_list_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_list_de_chain(h);
     ret = (struct _cee_list_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_list_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_list_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_list_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_list_trace (void * v, enum trace_action ta) {
  struct _cee_list_header * m = (struct _cee_list_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_list_header, _))));
  int i;
  switch(ta) {
    case trace_del_no_follow:
      _cee_list_de_chain(m);
      free(m);
      break;
    case trace_del_follow:
      for (i = 0; i < m->size; i++)
        del_e(m->del_policy, m->_[i]);
      _cee_list_de_chain(m);
      free(m);
      break;
    default:
      m->cs.gc_mark = ta - trace_mark;
      for (i = 0; i < m->size; i++)
        trace(m->_[i], ta);
      break;
  }
}
list::data * mk_e (state::data * st, enum del_policy o, size_t cap) {
  size_t mem_block_size = sizeof(struct _cee_list_header) + cap * sizeof(void *);
  struct _cee_list_header * m = (struct _cee_list_header *)malloc(mem_block_size);
  m->capacity = cap;
  m->size = 0;
  m->del_policy = o;
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_list_chain(m, st);
  m->cs.trace = _cee_list_trace;
  m->cs.resize_method = resize_with_malloc;
  m->cs.mem_block_size = mem_block_size;
  return (list::data *)(m->_);
}
list::data * mk (state::data * s, size_t cap) {
  return mk_e(s, CEE_DEFAULT_DEL_POLICY, cap);
}
list::data * append (list::data ** l, void *e) {
  list::data * v = *l;
  struct _cee_list_header * m = (struct _cee_list_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_list_header, _))));
  size_t capacity = m->capacity;
  size_t extra_cap = capacity ? capacity : 1;
  if (m->size == m->capacity) {
    size_t new_mem_block_size = m->cs.mem_block_size + extra_cap * sizeof(void *);
    struct _cee_list_header * m1 = _cee_list_resize(m, new_mem_block_size);
    m1->capacity = capacity + extra_cap;
    *l = (list::data *)m1->_;
    m = m1;
  }
  m->_[m->size] = e;
  m->size ++;
  incr_indegree(m->del_policy, e);
  return *l;
}
list::data * insert(state::data * s, list::data ** l, size_t index, void *e) {
  list::data * v = *l;
  if (v == NULL) {
    v = mk(s, 10);
    use_realloc(v);
  }
  struct _cee_list_header * m = (struct _cee_list_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_list_header, _))));
  size_t capacity = m->capacity;
  size_t extra_cap = capacity ? capacity : 1;
  if (m->size == m->capacity) {
    size_t new_mem_block_size = m->cs.mem_block_size + extra_cap * sizeof(void *);
    struct _cee_list_header * m1 = _cee_list_resize(m, new_mem_block_size);
    m1->capacity = capacity + extra_cap;
    *l = (list::data *)m1->_;
    m = m1;
  }
  int i;
  for (i = m->size; i > index; i--)
    m->_[i] = m->_[i-1];
  m->_[index] = e;
  m->size ++;
  incr_indegree(m->del_policy, e);
  return *l;
}
bool remove(list::data * v, size_t index) {
  struct _cee_list_header * m = (struct _cee_list_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_list_header, _))));
  if (index >= m->size) return false;
  void * e = m->_[index];
  m->_[index] = 0;
  int i;
  for (i = index; i < (m->size - 1); i++)
    m->_[i] = m->_[i+1];
  m->size --;
  decr_indegree(m->del_policy, e);
  return true;
}
size_t size (list::data *x) {
  struct _cee_list_header * m = (struct _cee_list_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_list_header, _))));
  return m->size;
}
size_t capacity (list::data * x) {
  struct _cee_list_header * h = (struct _cee_list_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_list_header, _))));
  return h->capacity;
}
  }
}
namespace cee {
  namespace tagged {
struct _cee_tagged_header {
  enum del_policy del_policy;
  struct sect cs;
  struct tagged::data _;
};
static void _cee_tagged_chain (struct _cee_tagged_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_tagged_de_chain (struct _cee_tagged_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_tagged_header * _cee_tagged_resize(struct _cee_tagged_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_tagged_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_tagged_de_chain(h);
     ret = (struct _cee_tagged_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_tagged_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_tagged_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_tagged_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_tagged_trace (void * v, enum trace_action ta) {
  struct _cee_tagged_header * m = (struct _cee_tagged_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_tagged_header, _))));
  switch (ta) {
    case trace_del_no_follow:
      _cee_tagged_de_chain(m);
      free(m);
      break;
    case trace_del_follow:
      del_e(m->del_policy, m->_.ptr._);
      _cee_tagged_de_chain(m);
      free(m);
      break;
    default:
      m->cs.gc_mark = ta - trace_mark;
      trace(m->_.ptr._, ta);
      break;
  }
}
tagged::data * mk_e (state::data * st, enum del_policy o, uintptr_t tag, void *p) {
  size_t mem_block_size = sizeof(struct _cee_tagged_header);
  struct _cee_tagged_header * b = (struct _cee_tagged_header *)malloc(mem_block_size);
  do{ memset(&b->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_tagged_chain(b, st);
  b->cs.trace = _cee_tagged_trace;
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = mem_block_size;
  b->_.tag = tag;
  b->_.ptr._ = p;
  b->del_policy = o;
  incr_indegree(o, p);
  return &b->_;
}
tagged::data * mk (state::data * st, uintptr_t tag, void *p) {
  return mk_e(st, CEE_DEFAULT_DEL_POLICY, tag, p);
}
  }
}
namespace cee {
  namespace singleton {
struct _cee_singleton_header {
  struct sect cs;
  uintptr_t _; // tag
  uintptr_t val;
};
/*
 * singleton should never be deleted, hence we pass a noop
 */
static void _cee_singleton_noop(void *p, enum trace_action ta) {}
/*
 * the parameter of this function has to be a global/static 
 * uintptr_t array of two elements
 */
singleton::data * init(void *s, uintptr_t tag, uintptr_t val) {
  struct _cee_singleton_header * b = (struct _cee_singleton_header *)s;
  do{ memset(&b->cs, 0, sizeof(struct cee::sect)); } while(0);;
  b->cs.trace = _cee_singleton_noop;
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = 0;
  b->cs.n_product = 0;
  b->_ = tag;
  b->val = val;
  return (singleton::data *)&(b->_);
}
  }
}
namespace cee {
  namespace closure {
struct _cee_closure_header {
  struct sect cs;
  struct data _;
};
static void _cee_closure_chain (struct _cee_closure_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_closure_de_chain (struct _cee_closure_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_closure_header * _cee_closure_resize(struct _cee_closure_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_closure_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_closure_de_chain(h);
     ret = (struct _cee_closure_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_closure_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_closure_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_closure_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_closure_trace (void * v, enum trace_action sa) {
  struct _cee_closure_header * m = (struct _cee_closure_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_closure_header, _))));
  switch (sa) {
    case trace_del_no_follow:
    case trace_del_follow:
      _cee_closure_de_chain(m);
      free(m);
      break;
    default:
      break;
  }
}
struct data * mk (state::data * s, env::data * env, void * fun) {
  size_t mem_block_size = sizeof(struct _cee_closure_header);
  struct _cee_closure_header * b = (struct _cee_closure_header *)malloc(mem_block_size);
  do{ memset(&b->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_closure_chain(b, s);
  b->cs.trace = _cee_closure_trace;
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = mem_block_size;
  b->_.env = NULL;
  b->_.fun = NULL;
  return &(b->_);
}
  } // namespace closure
} // namespace cee
namespace cee {
  namespace block {
struct _cee_block_header {
  uintptr_t capacity;
  enum del_policy del_policy;
  struct sect cs;
  char _[1]; // actual data
};
static void _cee_block_chain (struct _cee_block_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_block_de_chain (struct _cee_block_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_block_header * _cee_block_resize(struct _cee_block_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_block_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_block_de_chain(h);
     ret = (struct _cee_block_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_block_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_block_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_block_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_block_trace (void * p, enum trace_action ta) {
  struct _cee_block_header * m = (struct _cee_block_header *)(struct _cee_block_header *)((void *)((char *)(p) - (__builtin_offsetof(struct _cee_block_header, _))));
  switch (ta) {
    case trace_del_follow:
    case trace_del_no_follow:
      _cee_block_de_chain(m);
      free(m);
      break;
    default:
      m->cs.gc_mark = ta - trace_mark;
      break;
  }
}
static void _cee_block_mark (void * p) {
};
void * mk (state::data * s, size_t n) {
  size_t mem_block_size;
  va_list ap;
  mem_block_size = n + sizeof(struct _cee_block_header);
  struct _cee_block_header * m = (struct _cee_block_header *)malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  m->del_policy = dp_del_rc;
  _cee_block_chain(m, s);
  m->cs.trace = _cee_block_trace;
  m->cs.resize_method = resize_with_malloc;
  m->cs.mem_block_size = mem_block_size;
  m->cs.cmp = (void *)memcmp;
  m->capacity = n;
  return (block::data *)(m->_);
}
  }
}
namespace cee {
  namespace n_tuple {
struct _cee_n_tuple_header {
  enum del_policy del_policies[16];
  struct sect cs;
  void * _[16];
};
static void _cee_n_tuple_chain (struct _cee_n_tuple_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_n_tuple_de_chain (struct _cee_n_tuple_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_n_tuple_header * _cee_n_tuple_resize(struct _cee_n_tuple_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_n_tuple_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_n_tuple_de_chain(h);
     ret = (struct _cee_n_tuple_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_n_tuple_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_n_tuple_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_n_tuple_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_n_tuple_trace(void * v, enum trace_action ta) {
  struct _cee_n_tuple_header * b = (struct _cee_n_tuple_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_n_tuple_header, _))));
  int i;
  switch (ta) {
    case trace_del_no_follow:
      _cee_n_tuple_de_chain(b);
      free(b);
      break;
    case trace_del_follow:
      for (i = 0; i < b->cs.n_product; i++)
        del_e(b->del_policies[i], b->_[i]);
      _cee_n_tuple_de_chain(b);
      free(b);
      break;
    default:
      b->cs.gc_mark = ta - trace_mark;
      for (i = 0; i < b->cs.n_product; i++)
        trace(b->_[i], ta);
      break;
  }
}
static struct _cee_n_tuple_header * cee_n_tuple_v (state::data * st, size_t ntuple,
                                         enum del_policy o[], va_list ap) {
  if (ntuple > 16)
    segfault();
  size_t mem_block_size = sizeof(struct _cee_n_tuple_header);
  struct _cee_n_tuple_header * m = (struct _cee_n_tuple_header *) malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_n_tuple_chain(m, st);
  m->cs.trace = _cee_n_tuple_trace;
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->cs.n_product = ntuple;
  int i;
  for(i = 0; i < ntuple; i++) {
    m->_[i] = va_arg(ap, void *);
    m->del_policies[i] = o[i];
    incr_indegree(o[i], m->_[i]);
  }
  return m;
}
n_tuple::data * mk (state::data * st, size_t ntuple, ...) {
  va_list ap;
  va_start(ap, ntuple);
  enum del_policy * o = (enum del_policy *)malloc(ntuple * sizeof (enum del_policy));
  int i;
  for (i = 0; i < ntuple; i++)
    o[i] = CEE_DEFAULT_DEL_POLICY;
  struct _cee_n_tuple_header * h = cee_n_tuple_v(st, ntuple, o, ap);
  free(o);
  return (n_tuple::data *)(h->_);
}
  }
}
namespace cee {
  namespace env {
struct _cee_env_header {
  enum del_policy env_dp;
  enum del_policy vars_dp;
  struct sect cs;
  struct data _;
};
static void _cee_env_chain (struct _cee_env_header * h, state::data * st) {
  h->cs.state = st;
  h->cs.trace_prev = st->trace_tail;
  st->trace_tail->trace_next = &h->cs;
  st->trace_tail = &h->cs;
}
static void _cee_env_de_chain (struct _cee_env_header * h) {
  state::data * st = h->cs.state;
  struct sect * prev = h->cs.trace_prev;
  struct sect * next = h->cs.trace_next;
  if (st->trace_tail == &h->cs) {
    prev->trace_next = NULL;
    st->trace_tail = prev;
  }
  else {
    prev->trace_next = next;
    if (next)
      next->trace_prev = prev;
  }
}
static struct _cee_env_header * _cee_env_resize(struct _cee_env_header * h, size_t n)
{
  state::data * state = h->cs.state;
  struct _cee_env_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
      _cee_env_de_chain(h);
     ret = (struct _cee_env_header *)realloc(h, n);
      ret->cs.mem_block_size = n;
      _cee_env_chain(ret, state);
      break;
    case resize_with_malloc:
     ret = (struct _cee_env_header *)malloc(n);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = n;
      _cee_env_chain(ret, state);
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_env_trace (void * v, enum trace_action ta) {
  struct _cee_env_header * h = (struct _cee_env_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_env_header, _))));
  switch (ta) {
    case trace_del_no_follow:
      _cee_env_de_chain(h);
      free(h);
      break;
    case trace_del_follow:
      del_e(h->env_dp, h->_.outer);
      del_e(h->vars_dp, h->_.vars);
      _cee_env_de_chain(h);
      free(h);
      break;
    default:
      h->cs.gc_mark = ta - trace_mark;
      trace(h->_.outer, ta);
      trace(h->_.vars, ta);
      break;
  }
}
env::data * mk_e(state::data * st, enum del_policy dp[2], env::data * outer, map::data * vars) {
  size_t mem_block_size = sizeof(struct _cee_env_header);
  struct _cee_env_header * h = (struct _cee_env_header *)malloc(mem_block_size);
  do{ memset(&h->cs, 0, sizeof(struct cee::sect)); } while(0);;
  _cee_env_chain(h, st);
  h->cs.trace = _cee_env_trace;
  h->cs.resize_method = resize_with_identity;
  h->cs.mem_block_size = mem_block_size;
  h->cs.cmp = NULL;
  h->cs.n_product = 0;
  h->env_dp = dp[0];
  h->vars_dp = dp[1];
  h->_.outer = outer;
  h->_.vars = vars;
  return &h->_;
}
env::data * mk(state::data * st, env::data * outer, map::data * vars) {
  enum del_policy dp[2] = { CEE_DEFAULT_DEL_POLICY, CEE_DEFAULT_DEL_POLICY };
  return mk_e (st, dp, outer, vars);
}
  } // env
} // cee
namespace cee {
namespace state {
struct _cee_state_header {
  struct sect cs;
  struct data _;
};
static void _cee_state_trace (void * v, enum trace_action ta) {
  struct _cee_state_header * m = (struct _cee_state_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_state_header, _))));
  switch (ta) {
    case trace_del_follow:
    {
      // following this tracing chain but not the relations
      struct sect * tail = m->_.trace_tail;
      while (tail != &m->cs) {
        trace(tail + 1, trace_del_no_follow);
        tail = m->_.trace_tail;
      }
      free(m);
      break;
    }
    case trace_del_no_follow:
    {
      // TODO detach the this state from all memory blocks
      free(m);
      break;
    }
    default:
    {
      m->cs.gc_mark = ta - trace_mark;
      trace(m->_.roots, ta);
      trace(m->_.stack, ta);
      trace(m->_.contexts, ta);
      break;
    }
  }
}
static void _cee_state_sweep (void * v, enum trace_action ta) {
  struct _cee_state_header * m = (struct _cee_state_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_state_header, _))));
  struct sect * head = &m->cs;
  while (head != NULL) {
    struct sect * next = head->trace_next;
    if (head->gc_mark != ta - trace_mark)
      trace(head + 1, trace_del_no_follow);
    head = next;
  }
}
static int _cee_state_cmp (const void * v1, const void * v2) {
  if (v1 < v2)
    return -1;
  else if (v1 == v2)
    return 0;
  else
    return 1;
}
state::data * mk(size_t n) {
  size_t memblock_size = sizeof(struct _cee_state_header);
  struct _cee_state_header * h = (struct _cee_state_header *)malloc(memblock_size);
  do{ memset(&h->cs, 0, sizeof(struct cee::sect)); } while(0);;
  h->cs.trace = _cee_state_trace;
  h->_.trace_tail = &h->cs; // points to self;
  set::data * roots = set::mk_e(&h->_, dp_noop, _cee_state_cmp);
  h->_.roots = roots;
  h->_.next_mark = 1;
  h->_.stack = stack::mk(&h->_, n);
  h->_.contexts = map::mk(&h->_, (cmp_fun)strcmp);
  return &h->_;
}
void add_gc_root(state::data * s, void * key) {
  set::add(s->roots, key);
}
void remove_gc_root(state::data * s, void * key) {
  set::remove(s->roots, key);
}
void add_context (state::data * s, char * key, void * val) {
  map::add(s->contexts, key, val);
}
void remove_context (state::data * s, char * key) {
  map::remove(s->contexts, key);
}
void * get_context (state::data * s, char * key) {
  return map::find(s->contexts, key);
}
void gc (state::data * s) {
  struct _cee_state_header * h = (struct _cee_state_header *)((void *)((char *)(s) - (__builtin_offsetof(struct _cee_state_header, _))));
  int mark = trace_mark + s->next_mark;
  trace(s, (enum trace_action)mark);
  _cee_state_sweep(s, (enum trace_action) mark);
  if (s->next_mark == 0) {
    s->next_mark = 1;
  } else {
    s->next_mark = 0;
  }
}
  }
}
