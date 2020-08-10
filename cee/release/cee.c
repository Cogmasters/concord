#ifndef CEE_ONE
#define CEE_ONE
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <search.h>
#include <assert.h>
#include <errno.h>
#ifndef CEE_H
#define CEE_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <search.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uintptr_t tag_t;
typedef int (*cee_cmp_fun) (const void *, const void *);

enum cee_resize_method {
  resize_with_identity = 0, // resize with identity function
  resize_with_malloc = 1,
  resize_with_realloc = 2
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
 * cee_dp_del_rc: if a container is freed, its cee element's in-degree will be 
 *         decreased by one. If any cee element's in-degree is zero, the element 
 *         will be freed. It's developer's responsibility to prevent cyclically
 *         pointed containers from having this policy.
 * 
 * cee_dp_del: if a container is freed, all its cee elements will be freed 
 *         immediately. It's developer's responsiblity to prevent an element is 
 *         retained by multiple containers that have this policy.
 *
 * cee_dp_noop: if a container is freed, nothing will happen to its elements.
 *              It's developer's responsiblity to prevent memory leaks.
 *
 * the default del_policy is cee_dp_del_rc, which can be configured at compile
 * time with CEE_DEFAULT_DEL_POLICY
 */
enum cee_del_policy {
  cee_dp_del_rc = 0,  
  cee_dp_del = 1,
  cee_dp_noop = 2
};

#ifndef CEE_DEFAULT_DEL_POLICY
#define CEE_DEFAULT_DEL_POLICY  cee_dp_del_rc
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
struct cee_sect {
  uint8_t cmp_stop_at_null:1; // 0: compare all bytes, otherwise stop at '\0'
  uint8_t resize_method:2;    // three values: identity, malloc, realloc
  uint8_t retained:1;         // if it is retained, in_degree is ignored
  uint8_t n_product;          // n-ary (no more than 256) product type
  uint16_t in_degree;         // the number of cee objects points to this object
  uintptr_t mem_block_size;   // the size of a memory block enclosing this struct
  void *cmp;                  // compare two memory blocks
  void (*del)(void *);        // the object specific delete function
};


/*
 * A consecutive memory block of unknown length.
 * It can be safely casted to char *, but it may not 
 * be terminated by '\0'.
 */
struct cee_block {
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
extern void * cee_block (size_t n);

/*
 * C string is an array of chars, it may or may not be terminated by '\0'.
 * 
 * if it's not terminated by null strlen will read memory out of its bounds.
 *
 */
struct cee_str {
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
extern struct cee_str  * cee_str (const char * fmt, ...);


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
extern struct cee_str  * cee_str_n (size_t n, const char * fmt, ...);

/*
 * return the pointer of the null terminator;
 * if the array is not null terminated, 
 * NULL is returned.
 */
extern char * cee_str_end (struct cee_str *);

/*
 * str: points to the begin of a struct cee_block
 *
 * the function performs one task
 * 1. add any char to the end of str
 *
 * return: the start address of a cee_block, a new cee_block will
 *         be allocated if the cee_block is too small.
 */
extern struct cee_str * cee_str_add (struct cee_str * str, char);

/*
 * just like the standard strcat, but this function composes the src
 * string through a fmt string and its varadic arguments.
 */
extern struct cee_str * cee_str_catf (struct cee_str *, const char * fmt, ...);
extern struct cee_str * cee_str_ncat (struct cee_str *, char * s, size_t);

struct cee_vect {
  void * _[1]; // an array of `void *`s
};

/*
 * size: the initial size of the vector
 * when the vector is deleted, its elements will not be deleted
 */
extern struct cee_vect * cee_vect (size_t size);

extern struct cee_vect * cee_vect_e (enum cee_del_policy o, size_t size);

/*
 * it may return a new vector if the parameter vector is too small
 */
extern struct cee_vect * cee_vect_append(struct cee_vect * v, void * e);


/*
 * it inserts an element e at index and shift the rest elements 
 * to higher indices
 */
extern struct cee_vect * cee_vect_insert(struct cee_vect * v, size_t index,
                                         void * e);

/*
 * it removes an element at index and shift the rest elements 
 * to lower indices
 */
extern struct cee_vect * cee_vect_remove(struct cee_vect * v, size_t index);

/*
 * returns the number of elements in the vector
 */
extern size_t cee_vect_size(struct cee_vect *);

/*
 *
 */
extern size_t cee_vect_capacity (struct cee_vect *);


struct cee_tuple {
  void * _[2];
};


/*
 * construct a tuple from its parameters
 * v1: the first value of the tuple
 * v2: the second value of the tuple
 */
extern struct cee_tuple * cee_tuple (void * v1, void * v2);

extern struct cee_tuple * cee_tuple_e (enum cee_del_policy o[2], 
                                       void * v1, void * v2);

struct cee_triple {
  void * _[3];
};

/* 
 * construct a triple from its parameters
 * v1: the first value of the triple
 * v2: the second value of the triple
 * v3: the third value of the triple
 * when the triple is deleted, its elements will not be deleted
 */
extern struct cee_triple * cee_triple(void * v1, void * v2, void * v3);
extern struct cee_triple * cee_triple_e(enum cee_del_policy o[3], 
                                       void * v1, void * v2, void * v3);

struct cee_quadruple {
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
extern struct cee_quadruple * cee_quadruple(void * v1, void * v2, void * v3, 
                                            void * v4);

extern struct cee_quadruple * cee_quadruple_e(enum cee_del_policy o[4],
                                             void * v1, void * v2, void *v3, void *v4);

struct cee_n_tuple {
  void * _[1];  // n elements
};

extern struct cee_n_tuple * cee_n_tuple (size_t n, ...);

extern struct cee_n_tuple * cee_n_tuple_e (size_t n, enum cee_del_policy o[n], ...);

struct cee_set {
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
extern struct cee_set * cee_set (int (*cmp)(const void *, const void *));
extern struct cee_set * cee_set_e (enum cee_del_policy o, 
                                   int (*cmp)(const void *, const void *));

extern void cee_set_add(struct cee_set * m, void * key);
extern void * cee_set_find(struct cee_set * m, void * key);
extern void * cee_set_remove(struct cee_set * m, void * key);
extern void cee_set_clear (struct cee_set * m);
extern size_t cee_set_size(struct cee_set * m);
extern bool cee_set_empty(struct cee_set * s);
extern struct cee_vect * cee_set_values(struct cee_set * m);
extern struct cee_set * cee_set_union (struct cee_set * s1, struct cee_set * s2);

struct cee_map {
  void * _;
};

/*
 * map implementation based on binary tree
 * add/remove
 */
extern struct cee_map * cee_map(cee_cmp_fun cmp);
extern struct cee_map * cee_map_e(enum cee_del_policy o[2], cee_cmp_fun cmp);

extern uintptr_t cee_map_size(struct cee_map *);
extern void cee_map_add(struct cee_map * m, void * key, void * value);
extern void * cee_map_find(struct cee_map * m, void * key);
extern void * cee_map_remove(struct cee_map *m, void * key);
extern struct cee_vect * cee_map_keys(struct cee_map *m);
extern struct cee_vect * cee_map_values(struct cee_map *m);

union cee_ptr {
  void * _;
  struct cee_char      * str;
  struct cee_set       * set;
  struct cee_vect      * vect;
  struct cee_map       * map;
  struct cee_dict      * dict;
  struct cee_tuple     * tuple;
  struct cee_triple    * triple;
  struct cee_quadruple * quadruple;
  struct cee_block     * block;
  struct cee_box       * box;
  struct cee_singleton * singleton;
  struct cee_stack     * stack;
};

/*
 * dict behaviors like a map with the following properties
 * 
 * 1. fixed size
 * 2. key is char *
 * 3. insertion only
 *
 */
struct cee_dict {
  struct hsearch_data _;
};

/*
 *
 */
extern struct cee_dict * cee_dict (size_t s);
extern struct cee_dict * cee_dict_e (enum cee_del_policy o, size_t s);

extern void cee_dict_add(struct cee_dict * d, char * key, void * value);
extern void * cee_dict_find(struct cee_dict * d, char * key);

/*
 * a stack with a fixed size
 */
struct cee_stack {
  void * _[1];
};
/*
 * create a fixed size stack
 * size: the size of the stack
 * dt: specify how its element should be handled when the stack is deleted.
 */
extern struct cee_stack * cee_stack(size_t size);
extern struct cee_stack * cee_stack_e (enum cee_del_policy o, size_t size);

/*
 * return the element nth element away from the top element
 */
extern void * cee_stack_top(struct cee_stack *, size_t nth);
/*
 * pop out the top element and return it
 */
extern void * cee_stack_pop(struct cee_stack *);
/*
 * push an element to the top of the stack
 */
extern int cee_stack_push(struct cee_stack *, void *);
/*
 * test if the stack is empty
 */
extern bool cee_stack_empty (struct cee_stack *);
/*
 * test if the stack is full
 */
extern bool cee_stack_full (struct cee_stack *);
/*
 * return the size of the stack
 */
extern uintptr_t cee_stack_size (struct cee_stack *);

/*
 * singleton
 */
struct cee_singleton {
  tag_t  tag;
  uintptr_t val;
};
extern struct cee_singleton * cee_singleton_init(uintptr_t tag, void *);
#define CEE_SINGLETON_SIZE (sizeof(struct cee_singleton) + sizeof(struct cee_sect))

enum cee_primitive_type {
  cee_primitive_f64 = 1,
  cee_primitive_f32,
  cee_primitive_u64,
  cee_primitive_u32,
  cee_primitive_u16,
  cee_primitive_u8,
  cee_primitive_i64,
  cee_primitive_i32,
  cee_primitive_i16,
  cee_primitive_i8
};

union cee_primitive_value {
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
struct cee_box {
  union cee_primitive_value _;
};

extern struct cee_box * cee_box_double(double);
extern struct cee_box * cee_box_float(float);

extern struct cee_box * cee_box_u64(uint64_t);
extern struct cee_box * cee_box_u32(uint32_t);
extern struct cee_box * cee_box_u16(uint16_t);
extern struct cee_box * cee_box_u8(uint8_t);

extern struct cee_box * cee_box_i64(int64_t);
extern struct cee_box * cee_box_i32(int32_t);
extern struct cee_box * cee_box_i16(int16_t);
extern struct cee_box * cee_box_i8(int8_t);

extern double cee_box_as_double(struct cee_box * x);
extern float cee_box_as_float(struct cee_box * x);
extern uint64_t cee_box_as_u64(struct cee_box * x);
extern uint32_t cee_box_as_u32(struct cee_box * x);
extern uint16_t cee_box_as_u16(struct cee_box * x);
extern uint8_t  cee_box_as_u8(struct cee_box * x);

extern int64_t cee_box_as_i64(struct cee_box * x);
extern int32_t cee_box_as_i32(struct cee_box * x);
extern int16_t cee_box_as_i16(struct cee_box * x);
extern int8_t  cee_box_as_i8(struct cee_box * x);

/*
 * number of bytes needed to print out the value
 */
extern size_t cee_box_snprintf(char * buf, size_t size, struct cee_box *p);

enum cee_tag { dummy };
/*
 * tagged value is useful to construct tagged union
 */
struct cee_tagged {
  tag_t tag;
  union cee_ptr ptr;
};

/*
 * tag: any integer value
 * v: a value 
 */
extern struct cee_tagged * cee_tag (uintptr_t tag, void * v);
extern struct cee_tagged * cee_tag_e (enum cee_del_policy o, 
                                      uintptr_t tag, void *v);

struct cee_closure {
  void * context;
  void * data;
  void * fun;
};

extern void cee_use_realloc(void *);
extern void cee_use_malloc(void *);
extern void cee_del(void *);
extern void cee_del_ref(void *);
extern void cee_del_e (enum cee_del_policy o, void * p);
extern int cee_cmp (void *, void *);

extern void cee_incr_indegree (enum cee_del_policy o, void * p);
extern void cee_decr_indegree (enum cee_del_policy o, void * p);

/* 
 * return the reference count of an object
 */
extern uint16_t cee_get_rc (void *);

/*
 * call this to cause segfault for non-recoverable errors
 */
extern void cee_segfault() __attribute__((noreturn));

#endif // CEE_H 
#ifndef CEE_INTERNAL_H
#define CEE_INTERNAL_H

#ifndef NULL
#define NULL     ((void *)0)
#endif 

#endif // CEE_INTERNAL_H
void cee_del(void *p) {
  if (!p) cee_segfault();
  struct cee_sect * cs = ((void *)((char *)p - sizeof(struct cee_sect)));
  cs->del(p);
}
void cee_del_ref(void *p) {
  if (!p) cee_segfault();
  struct cee_sect * cs = ((void *)((char *)p - sizeof(struct cee_sect)));
  if (cs->in_degree) cs->in_degree --;
  if (cs->retained) return;
  if (!cs->in_degree) cs->del(p);
}
void cee_use_realloc(void * p) {
  struct cee_sect * cs = ((void *)((char *)p - sizeof(struct cee_sect)));
  if (cs->resize_method)
    cs->resize_method = resize_with_realloc;
}
void cee_use_malloc(void * p) {
  struct cee_sect * cs = ((void *)((char *)p - sizeof(struct cee_sect)));
  if (cs->resize_method)
    cs->resize_method = resize_with_malloc;
}
void cee_segfault() {
  volatile char * c = 0;
  *c = 0;
  __builtin_unreachable();
}
static void _cee_common_incr_rc (void * p) {
  struct cee_sect * cs = ((void *)((char *)p - sizeof(struct cee_sect)));
  if (cs->retained) return;
  cs->in_degree ++;
}
static void _cee_common_decr_rc (void * p) {
  struct cee_sect * cs = ((void *)((char *)p - sizeof(struct cee_sect)));
  if (cs->retained) return;
  if (cs->in_degree)
    cs->in_degree --;
  else {
  }
}
uint16_t cee_get_in_degree (void * p) {
  struct cee_sect * cs = ((void *)((char *)p - sizeof(struct cee_sect)));
  return cs->in_degree;
}
static void _cee_common_retain (void *p) {
  struct cee_sect * cs = ((void *)((char *)p - sizeof(struct cee_sect)));
  cs->retained = 1;
}
static void _cee_common_release (void * p) {
  struct cee_sect * cs = ((void *)((char *)p - sizeof(struct cee_sect)));
  if(cs->retained)
    cs->retained = 0;
  else {
    cee_segfault();
  }
}
void cee_incr_indegree (enum cee_del_policy o, void * p) {
  switch(o) {
    case cee_dp_del_rc:
      _cee_common_incr_rc(p);
      break;
    case cee_dp_del:
      _cee_common_retain(p);
      break;
    case cee_dp_noop:
      break;
  }
}
void cee_decr_indegree (enum cee_del_policy o, void * p) {
  switch(o) {
    case cee_dp_del_rc:
      _cee_common_decr_rc(p);
      break;
    case cee_dp_del:
      _cee_common_release(p);
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
struct _cee_box_header {
  enum cee_primitive_type type;
  struct cee_sect cs;
  union cee_primitive_value _[1];
};
static void _cee_box_del (void * v) {
  struct _cee_box_header * m = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_box_header, _))));
  free(m);
}
static int _cee_box_cmp (void * v1, void * v2) {
  struct _cee_box_header * h1 = ((void *)((char *)(v1) - (__builtin_offsetof(struct _cee_box_header, _))));
  struct _cee_box_header * h2 = ((void *)((char *)(v2) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h1->cs.del == h2->cs.del)
    cee_segfault();
  else
    cee_segfault();
}
static struct _cee_box_header * _cee_box_mk_header(enum cee_primitive_type t) {
  size_t mem_block_size = sizeof(struct _cee_box_header);
  struct _cee_box_header * b = malloc(mem_block_size);
  do{ memset(&b->cs, 0, sizeof(struct cee_sect)); } while(0);;
  b->cs.del = _cee_box_del;
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = mem_block_size;
  b->cs.cmp = NULL;
  b->cs.n_product = 0;
  b->type = t;
  b->_[0].u64 = 0;
  return b;
}
static int _cee_box_cmp_double(double v1, double v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
struct cee_box * cee_box_double (double d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct _cee_box_header * b = _cee_box_mk_header(cee_primitive_f64);
  b->cs.cmp = _cee_box_cmp_double;
  b->_[0].f64 = d;
  return (struct cee_box *)b->_;
}
static int _cee_box_cmp_float(float v1, float v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
struct cee_box * cee_box_float (float d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct _cee_box_header * b = _cee_box_mk_header(cee_primitive_f32);
  b->cs.cmp = _cee_box_cmp_float;
  b->_[0].f32 = d;
  return (struct cee_box *)b->_;
}
static int _cee_box_cmp_u64(uint64_t v1, uint64_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
struct cee_box * cee_box_u64 (uint64_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct _cee_box_header * b = _cee_box_mk_header(cee_primitive_u64);
  b->_[0].u64 = d;
  return (struct cee_box *)b->_;
}
static int _cee_box_cmp_u32(uint32_t v1, uint32_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
struct cee_box * cee_box_u32 (uint32_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct _cee_box_header * b = _cee_box_mk_header(cee_primitive_u32);
  b->cs.cmp = _cee_box_cmp_u32;
  b->_[0].u32 = d;
  return (struct cee_box *)b->_;
}
static int _cee_box_cmp_u16(uint16_t v1, uint16_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
struct cee_box * cee_box_u16 (uint16_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct _cee_box_header * b = _cee_box_mk_header(cee_primitive_u16);
  b->cs.cmp = _cee_box_cmp_u16;
  b->_[0].u16 = d;
  return (struct cee_box *)b->_;
}
static int _cee_box_cmp_u8(uint8_t v1, uint8_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
struct cee_box * cee_box_u8 (uint8_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct _cee_box_header * b = _cee_box_mk_header(cee_primitive_u8);
  b->cs.cmp = _cee_box_cmp_u8;
  b->_[0].u8 = d;
  return (struct cee_box *)b->_;
}
static int _cee_box_cmp_i64(int64_t v1, int64_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
struct cee_box * cee_box_i64 (int64_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct _cee_box_header * b = _cee_box_mk_header(cee_primitive_i64);
  b->cs.cmp = _cee_box_cmp_i64;
  b->_[0].i64 = d;
  return (struct cee_box *)b->_;
}
static int _cee_box_cmp_i32(int32_t v1, int32_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
struct cee_box * cee_box_i32 (int32_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct _cee_box_header * b = _cee_box_mk_header(cee_primitive_i32);
  b->cs.cmp = _cee_box_cmp_i32;
  b->_[0].i32 = d;
  return (struct cee_box *)b->_;
}
static int _cee_box_cmp_i16(int16_t v1, int16_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
struct cee_box * cee_box_i16 (int16_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct _cee_box_header * b = _cee_box_mk_header(cee_primitive_i16);
  b->cs.cmp = _cee_box_cmp_i16;
  b->_[0].i16 = d;
  return (struct cee_box *)b->_;
}
static int _cee_box_cmp_i8(int8_t v1, int8_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
struct cee_box * cee_box_i8 (int8_t d) {
  size_t mem_block_size = sizeof(struct cee_box);
  struct _cee_box_header * b = _cee_box_mk_header(cee_primitive_i8);
  b->cs.cmp = _cee_box_cmp_i8;
  b->_[0].i8 = d;
  return (struct cee_box *)b->_;
}
size_t cee_box_snprintf (char * buf, size_t size, struct cee_box * x) {
  struct _cee_box_header * h = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  int s;
  switch(h->type)
  {
    case cee_primitive_f64:
      s = snprintf(buf, size, "%lf", h->_[0].f64);
      break;
    case cee_primitive_f32:
      s = snprintf(buf, size, "%f", h->_[0].f32);
      break;
    case cee_primitive_i64:
      s = snprintf(buf, size, "%lld", h->_[0].i64);
      break;
    case cee_primitive_u32:
    case cee_primitive_u16:
    case cee_primitive_u8:
      s = snprintf(buf, size, "%u", h->_[0].u32);
      break;
    case cee_primitive_u64:
      s = snprintf(buf, size, "%llu", h->_[0].u64);
      break;
    case cee_primitive_i32:
    case cee_primitive_i16:
    case cee_primitive_i8:
      s = snprintf(buf, size, "%d", h->_[0].i8);
      break;
    default:
      cee_segfault();
      break;
  }
  if (s > 0)
    return (size_t)s;
  else
    cee_segfault();
}
double cee_box_as_double (struct cee_box * x) {
  struct _cee_box_header * h = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == cee_primitive_f64)
    return h->_[0].f64;
  else
    cee_segfault();
}
float cee_box_as_float (struct cee_box * x) {
  struct _cee_box_header * h = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == cee_primitive_f32)
    return h->_[0].f32;
  else
    cee_segfault();
}
uint64_t cee_box_as_u64 (struct cee_box * x) {
  struct _cee_box_header * h = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == cee_primitive_u64)
    return h->_[0].u64;
  else
    cee_segfault();
}
uint32_t cee_box_as_u32 (struct cee_box * x) {
  struct _cee_box_header * h = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == cee_primitive_u32)
    return h->_[0].u32;
  else
    cee_segfault();
}
uint16_t cee_box_as_u16 (struct cee_box * x) {
  struct _cee_box_header * h = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == cee_primitive_u16)
    return h->_[0].u16;
  else
    cee_segfault();
}
uint8_t cee_box_as_u8 (struct cee_box * x) {
  struct _cee_box_header * h = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == cee_primitive_u8)
    return h->_[0].u8;
  else
    cee_segfault();
}
int64_t cee_box_as_i64 (struct cee_box * x) {
  struct _cee_box_header * h = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == cee_primitive_i64)
    return h->_[0].i64;
  else
    cee_segfault();
}
int32_t cee_box_as_i32 (struct cee_box * x) {
  struct _cee_box_header * h = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == cee_primitive_i32)
    return h->_[0].i32;
  else
    cee_segfault();
}
int16_t cee_box_as_i16 (struct cee_box * x) {
  struct _cee_box_header * h = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == cee_primitive_i16)
    return h->_[0].i16;
  else
    cee_segfault();
}
int8_t cee_box_as_i8 (struct cee_box * x) {
  struct _cee_box_header * h = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == cee_primitive_i8)
    return h->_[0].i8;
  else
    cee_segfault();
}
struct _cee_str_header {
  uintptr_t capacity;
  struct cee_sect cs;
  char _[1];
};
static struct _cee_str_header * _cee_str_resize(struct _cee_str_header * h, size_t s)
{
  struct _cee_str_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
     ret = realloc(h, s);
      ret->cs.mem_block_size = s;
      break;
    case resize_with_malloc:
     ret = malloc(s);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = s;
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_str_del (void * p) {
  struct _cee_str_header * m = ((void *)((char *)(p) - (__builtin_offsetof(struct _cee_str_header, _))));
  free(m);
}
struct cee_str * cee_str (const char * fmt, ...) {
  if (!fmt) {
    cee_segfault();
  }
  uintptr_t s;
  va_list ap;
  va_start(ap, fmt);
  s = vsnprintf(NULL, 0, fmt, ap);
  s ++;
  s += sizeof(struct _cee_str_header);
  s = (s / 64 + 1) * 64;
  size_t mem_block_size = s;
  struct _cee_str_header * h = malloc(mem_block_size);
  do{ memset(&h->cs, 0, sizeof(struct cee_sect)); } while(0);;
  h->cs.del = _cee_str_del;
  h->cs.resize_method = resize_with_malloc;
  h->cs.mem_block_size = mem_block_size;
  h->cs.cmp = strcmp;
  h->cs.cmp_stop_at_null = 1;
  h->cs.n_product = 0;
  h->capacity = s - sizeof(struct _cee_str_header);
  va_start(ap, fmt);
  vsnprintf(h->_, s, fmt, ap);
  return (struct cee_str *)(h->_);
}
struct cee_str * cee_str_n (size_t n, const char * fmt, ...) {
  uintptr_t s;
  va_list ap;
  if (fmt) {
    va_start(ap, fmt);
    s = vsnprintf(NULL, 0, fmt, ap);
    s ++;
  }
  else
    s = n;
  s += sizeof(struct _cee_str_header);
  size_t mem_block_size = (s / 64 + 1) * 64;
  struct _cee_str_header * m = malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee_sect)); } while(0);;
  m->cs.del = _cee_str_del;
  m->cs.resize_method = resize_with_malloc;
  m->cs.mem_block_size = mem_block_size;
  m->cs.cmp = strcmp;
  m->cs.cmp_stop_at_null = 1;
  m->capacity = mem_block_size - sizeof(struct _cee_str_header);
  if (fmt) {
    va_start(ap, fmt);
    vsnprintf(m->_, mem_block_size, fmt, ap);
  }
  else {
    m->_[0] = '\0';
  }
  return (struct cee_str *)(m->_);
}
static void _cee_str_noop(void * v) {}
struct cee_block * cee_block_empty () {
  static struct _cee_str_header singleton;
  singleton.cs.del = _cee_str_noop;
  singleton.cs.resize_method = resize_with_malloc;
  singleton.cs.mem_block_size = sizeof(struct _cee_str_header);
  singleton.capacity = 1;
  singleton._[0] = 0;
  return (struct cee_block *)&singleton._;
}
char * cee_str_end(struct cee_str * str) {
  struct _cee_str_header * b = ((void *)((char *)(str) - (__builtin_offsetof(struct _cee_str_header, _))));
  return (char *)str + strlen((char *)str);
}
struct cee_str * cee_str_add(struct cee_str * str, char c) {
  struct _cee_str_header * b = ((void *)((char *)(str) - (__builtin_offsetof(struct _cee_str_header, _))));
  uint32_t slen = strlen((char *)str);
  if (slen < b->capacity) {
    b->_[slen] = c;
    b->_[slen+1] = '\0';
    return (struct cee_str *)(b->_);
  }
  else {
    struct _cee_str_header * b1 = _cee_str_resize(b, b->cs.mem_block_size + 64);
    b1->capacity = b->capacity + 64;
    b1->_[b->capacity] = c;
    b1->_[b->capacity+1] = '\0';
    return (struct cee_str *)(b1->_);
  }
}
struct cee_str * cee_str_catf(struct cee_str * str, const char * fmt, ...) {
  struct _cee_str_header * b = ((void *)((char *)(str) - (__builtin_offsetof(struct _cee_str_header, _))));
  if (!fmt)
    return str;
  size_t slen = strlen((char *)str);
  va_list ap;
  va_start(ap, fmt);
  size_t s = vsnprintf(NULL, 0, fmt, ap);
  s ++;
  va_start(ap, fmt);
  if (slen + s < b->capacity) {
    vsnprintf(b->_ + slen, s, fmt, ap);
    return str;
  }
  else {
    struct _cee_str_header * b1 = _cee_str_resize(b, slen + s);
    vsnprintf(b1->_ + slen, s, fmt, ap);
    return (struct cee_str *)(b1->_);
  }
}
struct cee_str * cee_str_ncat (struct cee_str * str, char * s, size_t slen) {
  return NULL;
}
struct _cee_dict_header {
  struct cee_vect * keys;
  struct cee_vect * vals;
  uintptr_t size;
  enum cee_del_policy del_policy;
  struct cee_sect cs;
  struct hsearch_data _[1];
};
static void _cee_dict_del(void *d) {
  struct _cee_dict_header * m = ((void *)((char *)(d) - (__builtin_offsetof(struct _cee_dict_header, _))));
  hdestroy_r(m->_);
  cee_del_e(m->del_policy, m->keys);
  cee_del_e(m->del_policy, m->vals);
  free(m);
}
struct cee_dict * cee_dict_e (enum cee_del_policy o, size_t size) {
  size_t mem_block_size = sizeof(struct _cee_dict_header);
  struct _cee_dict_header * m = malloc(mem_block_size);
  m->del_policy = o;
  m->keys = cee_vect(size);
  cee_use_realloc(m->keys);
  m->vals = cee_vect(size);
  cee_use_realloc(m->vals);
  m->size = size;
  do{ memset(&m->cs, 0, sizeof(struct cee_sect)); } while(0);;
  m->cs.del = _cee_dict_del;
  m->cs.mem_block_size = mem_block_size;
  m->cs.resize_method = resize_with_identity;
  m->cs.n_product = 2;
  size_t hsize = (size_t)((float)size * 1.25);
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
  struct _cee_dict_header * m = ((void *)((char *)(d) - (__builtin_offsetof(struct _cee_dict_header, _))));
  ENTRY n, *np;
  n.key = key;
  n.data = value;
  if (!hsearch_r(n, ENTER, &np, m->_))
    cee_segfault();
  m->keys = cee_vect_append(m->keys, key);
  m->vals = cee_vect_append(m->vals, value);
}
void * cee_dict_find(struct cee_dict * d, char * key) {
  struct _cee_dict_header * m = ((void *)((char *)(d) - (__builtin_offsetof(struct _cee_dict_header, _))));
  ENTRY n, *np;
  n.key = key;
  n.data = NULL;
  if (hsearch_r(n, FIND, &np, m->_))
    return np->data;
  printf ("%s\n", strerror(errno));
  return NULL;
}
struct _cee_map_header {
  void * context;
  int (*cmp)(const void *l, const void *r);
  uintptr_t size;
  enum cee_del_policy key_del_policy;
  enum cee_del_policy val_del_policy;
  struct cee_sect cs;
  void * _[1];
};
struct _cee_map_pair {
  struct cee_tuple * value;
  struct _cee_map_header * h;
};
static void _cee_map_free_pair(void * c) {
  struct _cee_map_pair * p = c;
  cee_del(p->value);
  free(p);
}
static void _cee_map_del(void * p) {
  struct _cee_map_header * b = ((void *)((char *)(p) - (__builtin_offsetof(struct _cee_map_header, _))));
  tdestroy(b->_[0], _cee_map_free_pair);
  free(b);
}
static int _cee_map_cmp (const void * v1, const void * v2) {
  struct _cee_map_pair * t1 = (struct _cee_map_pair *) v1;
  struct _cee_map_pair * t2 = (struct _cee_map_pair *) v2;
  if (t1->h == t2->h)
   return t1->h->cmp(t1->value->_[0], t2->value->_[0]);
  else
    cee_segfault();
}
struct cee_map * cee_map (int (*cmp)(const void *, const void *)) {
  size_t mem_block_size = sizeof(struct _cee_map_header);
  struct _cee_map_header * m = malloc(mem_block_size);
  m->context = NULL;
  m->cmp = cmp;
  m->size = 0;
  do{ memset(&m->cs, 0, sizeof(struct cee_sect)); } while(0);;
  m->cs.del = _cee_map_del;
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->cs.cmp = 0;
  m->cs.cmp_stop_at_null = 0;
  m->cs.n_product = 2;
  m->_[0] = 0;
  return (struct cee_map *)m->_;
}
uintptr_t cee_map_size(struct cee_map * m) {
  struct _cee_map_header * b = ((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  return b->size;
}
void cee_map_add(struct cee_map * m, void * key, void * value) {
  struct _cee_map_header * b = ((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  struct _cee_map_pair * triple = malloc(sizeof(struct _cee_map_pair));
  triple->h = b;
  triple->value = cee_tuple(key, value);
  struct _cee_map_pair ** oldp = tsearch(triple, b->_, _cee_map_cmp);
  if (oldp == NULL)
    cee_segfault();
  else if (*oldp != triple)
    _cee_map_free_pair(triple);
  else
    b->size ++;
  return;
}
void * cee_map_find(struct cee_map * m, void * key) {
  struct _cee_map_header * b = ((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  struct cee_tuple t = { key, 0 };
  struct _cee_map_pair keyp = { .value = &t, .h = b };
  void **oldp = tfind(&keyp, b->_, _cee_map_cmp);
  if (oldp == NULL)
    return NULL;
  else {
    struct _cee_map_pair * p = *oldp;
    return p->value->_[1];
  }
}
void * cee_map_remove(struct cee_map * m, void * key) {
  struct _cee_map_header * b = ((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  void ** oldp = tdelete(key, b->_, _cee_map_cmp);
  if (oldp == NULL)
    return NULL;
  else {
    b->size --;
    struct _cee_map_pair * t = *oldp;
    struct cee_tuple * ret = t->value;
    _cee_map_free_pair(t);
    cee_decr_indegree(b->key_del_policy, ret->_[0]);
    cee_decr_indegree(b->val_del_policy, ret->_[1]);
    return ret->_[1];
  }
}
static void _cee_map_get_key (const void *nodep, const VISIT which, const int depth) {
  struct _cee_map_pair * p;
  struct _cee_map_header * h;
  struct cee_vect * keys;
  switch (which)
  {
    case preorder:
    case leaf:
      p = *(struct _cee_map_pair **)nodep;
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
  struct _cee_map_header * b = ((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  struct cee_vect * keys = cee_vect(s);
  b->context = keys;
  twalk(b->_[0], _cee_map_get_key);
  return keys;
}
static void _cee_map_get_value (const void *nodep, const VISIT which, const int depth) {
  struct _cee_map_pair * p;
  struct _cee_map_header * h;
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
  struct _cee_map_header * b = ((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  struct cee_vect * values = cee_vect(s);
  b->context = values;
  twalk(b->_[0], _cee_map_get_value);
  return values;
}
struct _cee_set_header {
  void * context;
  int (*cmp)(const void *l, const void *r);
  uintptr_t size;
  enum cee_del_policy del_policy;
  struct cee_sect cs;
  void * _[1];
};
struct _cee_set_pair {
  void * value;
  struct _cee_set_header * h;
};
static void _cee_set_free_pair (void * c) {
  struct _cee_set_header * h = ((struct _cee_set_pair *)c)->h;
  cee_del_e(h->del_policy, ((struct _cee_set_pair *)c)->value);
  free(c);
}
static void _cee_set_del(void * p) {
  struct _cee_set_header * h = ((void *)((char *)(p) - (__builtin_offsetof(struct _cee_set_header, _))));
  tdestroy(h->_[0], _cee_set_free_pair);
  free(h);
}
static int _cee_set_cmp (const void * v1, const void * v2) {
  struct _cee_set_pair * t1 = (struct _cee_set_pair *) v1;
  struct _cee_set_pair * t2 = (struct _cee_set_pair *) v2;
  if (t1->h == t2->h)
   return t1->h->cmp(t1->value, t2->value);
  else
    cee_segfault();
}
struct cee_set * cee_set_e (enum cee_del_policy o, int (*cmp)(const void *, const void *)) {
  struct _cee_set_header * m = malloc(sizeof(struct _cee_set_header));
  m->cmp = cmp;
  m->size = 0;
  do{ memset(&m->cs, 0, sizeof(struct cee_sect)); } while(0);;
  m->cs.del = _cee_set_del;
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
  struct _cee_set_header * h = ((void *)((char *)(s) - (__builtin_offsetof(struct _cee_set_header, _))));
  return h->size;
}
bool cee_set_empty (struct cee_set * s) {
  struct _cee_set_header * h = ((void *)((char *)(s) - (__builtin_offsetof(struct _cee_set_header, _))));
  return h->size == 0;
}
void cee_set_add(struct cee_set *m, void * val) {
  struct _cee_set_header * h = ((void *)((char *)(m) - (__builtin_offsetof(struct _cee_set_header, _))));
  void ** c = malloc(sizeof(void *) * 2);
  c[0] = val;
  c[1] = h;
  void *** oldp = tsearch(c, h->_, _cee_set_cmp);
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
static void _cee_set_noop(void *p) {}
void cee_set_clear (struct cee_set * s) {
  struct _cee_set_header * h = ((void *)((char *)(s) - (__builtin_offsetof(struct _cee_set_header, _))));
  switch(h->del_policy) {
    case cee_dp_del_rc:
      tdestroy(h->_[0], cee_del_ref);
      break;
    case cee_dp_del:
      tdestroy(h->_[0], cee_del);
      break;
    case cee_dp_noop:
      tdestroy(h->_[0], _cee_set_noop);
      break;
  }
  h->_[0] = NULL;
  h->size = 0;
}
void * cee_set_find(struct cee_set *m, void * value) {
  struct _cee_set_header * h = ((void *)((char *)(m) - (__builtin_offsetof(struct _cee_set_header, _))));
  struct _cee_set_pair p = { value, h };
  void ***oldp = tfind(&p, h->_, _cee_set_cmp);
  if (oldp == NULL)
    return NULL;
  else {
    void ** t = (void **)*oldp;
    return t[0];
  }
}
static void _cee_set_get_value (const void *nodep, const VISIT which, const int depth) {
  struct _cee_set_pair * p;
  struct _cee_set_header * h;
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
  struct _cee_set_header * h = ((void *)((char *)(m) - (__builtin_offsetof(struct _cee_set_header, _))));
  h->context = cee_vect(s);
  cee_use_realloc(h->context);
  twalk(h->_[0], _cee_set_get_value);
  return h->context;
}
void * cee_set_remove(struct cee_set *m, void * key) {
  struct _cee_set_header * h = ((void *)((char *)(m) - (__builtin_offsetof(struct _cee_set_header, _))));
  void ** old = tdelete(key, h->_, h->cmp);
  if (old == NULL)
    return NULL;
  else {
    h->size --;
    struct _cee_set_pair * p = *old;
    void * k = p->value;
    free(p);
    return k;
  }
}
struct cee_set * cee_set_union (struct cee_set * s1, struct cee_set * s2) {
  struct _cee_set_header * h1 = ((void *)((char *)(s1) - (__builtin_offsetof(struct _cee_set_header, _))));
  struct _cee_set_header * h2 = ((void *)((char *)(s2) - (__builtin_offsetof(struct _cee_set_header, _))));
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
struct _cee_stack_header {
  uintptr_t used;
  uintptr_t top;
  uintptr_t capacity;
  enum cee_del_policy del_policy;
  struct cee_sect cs;
  void * _[];
};
static void _cee_stack_del (void * v) {
  struct _cee_stack_header * m = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_stack_header, _))));
  int i;
  for (i = 0; i < m->used; i++)
    cee_del_e(m->del_policy, m->_[i]);
  free(m);
}
struct cee_stack * cee_stack_e (enum cee_del_policy o, size_t size) {
  uintptr_t mem_block_size = sizeof(struct _cee_stack_header) + size * sizeof(void *);
  struct _cee_stack_header * m = malloc(mem_block_size);
  m->capacity = size;
  m->used = 0;
  m->top = (0-1);
  m->del_policy = o;
  do{ memset(&m->cs, 0, sizeof(struct cee_sect)); } while(0);;
  m->cs.del = _cee_stack_del;
  m->cs.mem_block_size = mem_block_size;
  return (struct cee_stack *)(m->_);
}
struct cee_stack * cee_stack (size_t size) {
  return cee_stack_e(CEE_DEFAULT_DEL_POLICY, size);
}
int cee_stack_push (struct cee_stack * v, void *e) {
  struct _cee_stack_header * m = ((void *)((char *)((void **)v) - (__builtin_offsetof(struct _cee_stack_header, _))));
  if (m->used == m->capacity)
    return 0;
  m->top ++;
  m->used ++;
  m->_[m->top] = e;
  cee_incr_indegree(m->del_policy, e);
  return 1;
}
void * cee_stack_pop (struct cee_stack * v) {
  struct _cee_stack_header * b = ((void *)((char *)((void **)v) - (__builtin_offsetof(struct _cee_stack_header, _))));
  if (b->used == 0) {
    return NULL;
  }
  else {
    void * p = b->_[b->top];
    b->used --;
    b->top --;
    cee_decr_indegree(b->del_policy, p);
    return p;
  }
}
void * cee_stack_top (struct cee_stack * v, uintptr_t nth) {
  struct _cee_stack_header * b = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_stack_header, _))));
  if (b->used == 0 || nth >= b->used)
    return NULL;
  else
    return b->_[b->top-nth];
}
uintptr_t cee_stack_size (struct cee_stack *x) {
  struct _cee_stack_header * m = ((void *)((char *)((void **)x) - (__builtin_offsetof(struct _cee_stack_header, _))));
  return m->used;
}
uintptr_t cee_stack_capacity (struct cee_stack *s) {
  struct _cee_stack_header * m = ((void *)((char *)(s) - (__builtin_offsetof(struct _cee_stack_header, _))));
  return m->capacity;
}
bool cee_stack_empty (struct cee_stack *x) {
  struct _cee_stack_header * b = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_stack_header, _))));
  return b->used == 0;
}
bool cee_stack_full (struct cee_stack *x) {
  struct _cee_stack_header * b = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_stack_header, _))));
  return b->used >= b->capacity;
}
struct _cee_tuple_header {
  enum cee_del_policy del_policies[2];
  struct cee_sect cs;
  void * _[2];
};
static void _cee_tuple_del(void * v) {
  struct _cee_tuple_header * b = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_tuple_header, _))));
  int i;
  for (i = 0; i < 2; i++)
    cee_del_e(b->del_policies[i], b->_[i]);
  free(b);
}
struct cee_tuple * cee_tuple_e (enum cee_del_policy o[2], void * v1, void * v2) {
  size_t mem_block_size = sizeof(struct _cee_tuple_header);
  struct _cee_tuple_header * m = malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee_sect)); } while(0);;
  m->cs.del = _cee_tuple_del;
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
struct _cee_triple_header {
  enum cee_del_policy del_policies[3];
  struct cee_sect cs;
  void * _[3];
};
static void _cee_triple_del(void * v) {
  struct _cee_triple_header * b = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_triple_header, _))));
  int i;
  for (i = 0; i < 3; i++)
    cee_del_e(b->del_policies[i], b->_[i]);
  free(b);
}
struct cee_triple * cee_triple_e (enum cee_del_policy o[3],
                                  void * v1, void * v2, void * v3) {
  size_t mem_block_size = sizeof(struct _cee_triple_header);
  struct _cee_triple_header * m = malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee_sect)); } while(0);;
  m->cs.del = _cee_triple_del;
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->_[0] = v1;
  m->_[1] = v2;
  m->_[2] = v3;
  int i;
  for (i = 0; i < 3; i++) {
    m->del_policies[i] = o[i];
    cee_incr_indegree(o[i], m->_[i]);
  }
  return (struct cee_triple *)&m->_;
}
struct cee_triple * cee_triple (void * v1, void * v2, void *v3) {
  enum cee_del_policy o[3] = { CEE_DEFAULT_DEL_POLICY,
                              CEE_DEFAULT_DEL_POLICY,
                              CEE_DEFAULT_DEL_POLICY };
  return cee_triple_e(o, v1, v2, v3);
}
struct _cee_quadruple_header {
  enum cee_del_policy del_policies[4];
  struct cee_sect cs;
  void * _[4];
};
static void _cee_quadruple_del(void * v) {
  struct _cee_quadruple_header * b = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_quadruple_header, _))));
  int i;
  for (i = 0; i < 4; i++)
    cee_del_e(b->del_policies[i], b->_[i]);
  free(b);
}
struct cee_quadruple * cee_quadruple_e (enum cee_del_policy o[4],
                                        void * v1, void * v2, void * v3,
                                        void * v4) {
  size_t mem_block_size = sizeof(struct _cee_quadruple_header);
  struct _cee_quadruple_header * m = malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee_sect)); } while(0);;
  m->cs.del = _cee_quadruple_del;
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->cs.n_product = 4;
  m->_[0] = v1;
  m->_[1] = v2;
  m->_[2] = v3;
  m->_[3] = v4;
  int i;
  for (i = 0; i < 4; i++) {
    m->del_policies[i] = o[i];
    cee_incr_indegree(o[i], m->_[i]);
  }
  return (struct cee_quadruple *)&m->_;
}
struct _cee_vect_header {
  uintptr_t size;
  uintptr_t capacity;
  enum cee_del_policy del_policy;
  struct cee_sect cs;
  void * _[];
};
static struct _cee_vect_header * _cee_vect_resize(struct _cee_vect_header * h, size_t s)
{
  struct _cee_vect_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
     ret = realloc(h, s);
      ret->cs.mem_block_size = s;
      break;
    case resize_with_malloc:
     ret = malloc(s);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = s;
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_vect_del (void * v) {
  struct _cee_vect_header * m = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_vect_header, _))));
  int i;
  for (i = 0; i < m->size; i++)
    cee_del_e(m->del_policy, m->_[i]);
  free(m);
}
struct cee_vect * cee_vect_e (enum cee_del_policy o, size_t cap) {
  size_t mem_block_size = sizeof(struct _cee_vect_header) + cap * sizeof(void *);
  struct _cee_vect_header * m = malloc(mem_block_size);
  m->capacity = cap;
  m->size = 0;
  m->del_policy = o;
  do{ memset(&m->cs, 0, sizeof(struct cee_sect)); } while(0);;
  m->cs.del = _cee_vect_del;
  m->cs.resize_method = resize_with_malloc;
  m->cs.mem_block_size = mem_block_size;
  return (struct cee_vect *)(m->_);
}
struct cee_vect * cee_vect (size_t cap) {
  return cee_vect_e(cee_dp_del_rc, cap);
}
struct cee_vect * cee_vect_append (struct cee_vect * v, void *e) {
  struct _cee_vect_header * m = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_vect_header, _))));
  size_t capacity = m->capacity;
  size_t extra_cap = capacity ? capacity : 1;
  if (m->size == m->capacity) {
    size_t new_mem_block_size = m->cs.mem_block_size + extra_cap * sizeof(void *);
    struct _cee_vect_header * m1 = _cee_vect_resize(m, new_mem_block_size);
    m1->capacity = capacity + extra_cap;
    m = m1;
  }
  m->_[m->size] = e;
  m->size ++;
  cee_incr_indegree(m->del_policy, e);
  return (struct cee_vect *)m->_;
}
struct cee_vect * cee_vect_insert(struct cee_vect * v, size_t index, void *e) {
  struct _cee_vect_header * m = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_vect_header, _))));
  size_t capacity = m->capacity;
  size_t extra_cap = capacity ? capacity : 1;
  if (m->size == m->capacity) {
    size_t new_mem_block_size = m->cs.mem_block_size + extra_cap * sizeof(void *);
    struct _cee_vect_header * m1 = _cee_vect_resize(m, new_mem_block_size);
    m1->capacity = capacity + extra_cap;
    m = m1;
  }
  int i;
  for (i = m->size; i > index; i--)
    m->_[i] = m->_[i-1];
  m->_[index] = e;
  m->size ++;
  cee_incr_indegree(m->del_policy, e);
  return (struct cee_vect *)m->_;
}
struct cee_vect * cee_vect_remove(struct cee_vect * v, size_t index) {
  struct _cee_vect_header * m = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_vect_header, _))));
  if (index >= m->size) return v;
  void * e = m->_[index];
  m->_[index] = 0;
  int i;
  for (i = index; i < (m->size - 1); i++)
    m->_[i] = m->_[i+1];
  m->size --;
  cee_decr_indegree(m->del_policy, e);
  return (struct cee_vect *)m->_;
}
size_t cee_vect_size (struct cee_vect *x) {
  struct _cee_vect_header * m = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_vect_header, _))));
  return m->size;
}
size_t cee_vect_capacity (struct cee_vect * x) {
  struct _cee_vect_header * h = ((void *)((char *)(x) - (__builtin_offsetof(struct _cee_vect_header, _))));
  return h->capacity;
}
struct _cee_tagged_header {
  enum cee_del_policy del_policy;
  struct cee_sect cs;
  struct cee_tagged _;
};
static void _cee_tagged_del (void * v) {
  struct _cee_tagged_header * m = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_tagged_header, _))));
  cee_del_e(m->del_policy, m->_.ptr._);
  free(m);
}
struct cee_tagged * cee_tag_e (enum cee_del_policy o, uintptr_t tag, void *p) {
  size_t mem_block_size = sizeof(struct _cee_tagged_header);
  struct _cee_tagged_header * b = malloc(mem_block_size);
  do{ memset(&b->cs, 0, sizeof(struct cee_sect)); } while(0);;
  b->cs.del = _cee_tagged_del;
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
struct _cee_singleton_header {
  struct cee_sect cs;
  uintptr_t _;
  uintptr_t val;
};
static void _cee_singleton_noop(void *p) {}
struct cee_singleton * cee_singleton_init(uintptr_t tag, void *s) {
  struct _cee_singleton_header * b = (struct _cee_singleton_header *)s;
  do{ memset(&b->cs, 0, sizeof(struct cee_sect)); } while(0);;
  b->cs.del = _cee_singleton_noop;
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = 0;
  b->cs.n_product = 0;
  b->_ = tag;
  b->val = 0;
  return (struct cee_singleton *)&(b->_);
}
struct _cee_closure_header {
  struct cee_sect cs;
  struct cee_closure _;
};
static void _cee_closure_del (void * v) {
  struct _cee_closure_header * m = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_closure_header, _))));
  free(m);
}
struct cee_closure * cee_closure (void * context, void * data, void * fun) {
  size_t mem_block_size = sizeof(struct _cee_closure_header);
  struct _cee_closure_header * b = malloc(mem_block_size);
  do{ memset(&b->cs, 0, sizeof(struct cee_sect)); } while(0);;
  b->cs.del = _cee_closure_del;
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = mem_block_size;
  b->_.context = context;
  b->_.data = data;
  b->_.fun = fun;
  return &(b->_);
}
struct _cee_block_header {
  uintptr_t capacity;
  enum cee_del_policy del_policy;
  struct cee_sect cs;
  char _[1];
};
static struct _cee_block_header * _cee_block_resize(struct _cee_block_header * h, size_t s)
{
  struct _cee_block_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
     ret = realloc(h, s);
      ret->cs.mem_block_size = s;
      break;
    case resize_with_malloc:
     ret = malloc(s);
     memcpy(ret, h, h->cs.mem_block_size);
      ret->cs.mem_block_size = s;
      break;
    case resize_with_identity:
      ret = h;
      break;
  }
  return ret;
}
static void _cee_block_del (void * p) {
  struct _cee_block_header * m = ((void *)((char *)(p) - (__builtin_offsetof(struct _cee_block_header, _))));
  free(m);
}
void * cee_block (size_t n) {
  size_t mem_block_size;
  va_list ap;
  mem_block_size = n + sizeof(struct _cee_block_header);
  struct _cee_block_header * m = malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee_sect)); } while(0);;
  m->del_policy = cee_dp_del_rc;
  m->cs.del = _cee_block_del;
  m->cs.resize_method = resize_with_malloc;
  m->cs.mem_block_size = mem_block_size;
  m->cs.cmp = memcmp;
  m->capacity = n;
  return (struct cee_block *)(m->_);
}
struct _cee_n_tuple_header {
  enum cee_del_policy del_policies[16];
  struct cee_sect cs;
  void * _[16];
};
static void _cee_n_tuple_del(void * v) {
  struct _cee_n_tuple_header * b = ((void *)((char *)(v) - (__builtin_offsetof(struct _cee_n_tuple_header, _))));
  int i;
  for (i = 0; i < b->cs.n_product; i++)
    cee_del_e(b->del_policies[i], b->_[i]);
  free(b);
}
static struct _cee_n_tuple_header * cee_n_tuple_v (size_t ntuple,
                                         enum cee_del_policy o[ntuple],
                                         va_list ap) {
  if (ntuple > 16)
    cee_segfault();
  size_t mem_block_size = sizeof(struct _cee_n_tuple_header);
  struct _cee_n_tuple_header * m = malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee_sect)); } while(0);;
  m->cs.del = _cee_n_tuple_del;
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->cs.n_product = ntuple;
  int i;
  for(i = 0; i < ntuple; i++) {
    m->_[i] = va_arg(ap, void *);
    m->del_policies[i] = o[i];
    cee_incr_indegree(o[i], m->_[i]);
  }
  return m;
}
struct cee_n_tuple * cee_n_tuple (size_t ntuple, ...) {
  va_list ap;
  va_start(ap, ntuple);
  enum cee_del_policy * o = malloc(ntuple * sizeof (enum cee_del_policy));
  int i;
  for (i = 0; i < ntuple; i++)
    o[i] = CEE_DEFAULT_DEL_POLICY;
  struct _cee_n_tuple_header * h = cee_n_tuple_v(ntuple, o, ap);
  free(o);
  return (struct cee_n_tuple *)(h->_);
}
#endif
