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

namespace cee {
typedef uintptr_t tag_t;
typedef int (*cmp_fun) (const void *, const void *);

enum resize_method {
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
  uint8_t cmp_stop_at_null:1; // 0: compare all bytes, otherwise stop at '\0'
  uint8_t resize_method:2;    // three values: identity, malloc, realloc
  uint8_t retained:1;         // if it is retained, in_degree is ignored
  uint8_t n_product;          // n-ary (no more than 256) product type
  uint16_t in_degree;         // the number of cee objects points to this object
  uintptr_t mem_block_size;   // the size of a memory block enclosing this struct
  void *cmp;                  // compare two memory blocks
  void (*del)(void *);        // the object specific delete function
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
  extern void * mk (size_t n);
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
  extern str::data  * mk (const char * fmt, ...);


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
  extern str::data  * mk_e (size_t n, const char * fmt, ...);

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
  
namespace vect {

  struct data {
    void * _[1]; // an array of `void *`s
  };

  /*
   * size: the initial size of the vector
   * when the vector is deleted, its elements will not be deleted
   */
  extern vect::data * mk (size_t size);



  extern vect::data * mk_e (enum del_policy o, size_t size);

  /*
   * it may return a new vector if the parameter vector is too small
   */
  extern vect::data * append(vect::data * v, void * e);


  /*
   * it inserts an element e at index and shift the rest elements 
   * to higher indices
   */
  extern vect::data * insert(vect::data * v, size_t index, void * e);

  /*
   * it removes an element at index and shift the rest elements 
   * to lower indices
   */
  extern vect::data * remove(vect::data * v, size_t index);

  /*
   * returns the number of elements in the vector
   */
  extern size_t size(vect::data *);

  /*
   *
   */
  extern size_t capacity (vect::data *);
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
  extern tuple::data * mk (void * v1, void * v2);
  extern tuple::data * mk_e (enum del_policy o[2], void * v1, void * v2);
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
  extern triple::data * mk(void * v1, void * v2, void * v3);
  extern triple::data * mk_e(enum del_policy o[3], void * v1, void * v2, void * v3);
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
  extern quadruple::data * mk(void * v1, void * v2, void * v3, void * v4);

  extern quadruple::data * mk_e(enum del_policy o[4], void * v1, void * v2, void *v3, void *v4);
}

namespace n_tuple {
  struct data {
    void * _[1];  // n elements
  };
  extern n_tuple::data * mk (size_t n, ...);
  extern n_tuple::data * mk_e (size_t n, enum del_policy o[], ...);
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
  extern set::data * mk (int (*cmp)(const void *, const void *));
  extern set::data * mk_e (enum del_policy o, 
                           int (*cmp)(const void *, const void *));

  extern void add(set::data * m, void * key);
  extern void * find(set::data * m, void * key);
  extern void * remove(set::data * m, void * key);
  extern void clear (set::data * m);
  extern size_t size(set::data * m);
  extern bool empty(set::data * s);
  extern vect::data * values(set::data * m);
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
  extern map::data * mk(cmp_fun cmp);
  extern map::data * mk_e(enum del_policy o[2], cmp_fun cmp);

  extern uintptr_t size(map::data *);
  extern void add(map::data * m, void * key, void * value);
  extern void * find(map::data * m, void * key);
  extern void * remove(map::data *m, void * key);
  extern vect::data * keys(map::data *m);
  extern vect::data * values(map::data *m);
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
    struct hsearch_data _;
  };

  /*
   *
   */
  extern dict::data * mk (size_t s);
  extern dict::data * mk_e (enum del_policy o, size_t s);

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
  extern stack::data * mk(size_t size);
  extern stack::data * mk_e (enum del_policy o, size_t size);

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
  extern singleton::data * init(uintptr_t tag, void *);
  #define CEE_SINGLETON_SIZE (sizeof(struct cee::singleton::data) + sizeof(struct cee::sect))

}
  
  
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

namespace box {
  /*
   * boxed primitive value
   */
  struct data {
    union primitive_value _;
  };

  extern box::data * from_double(double);
  extern box::data * from_float(float);

  extern box::data * from_u64(uint64_t);
  extern box::data * from_u32(uint32_t);
  extern box::data * from_u16(uint16_t);
  extern box::data * from_u8(uint8_t);

  extern box::data * from_i64(int64_t);
  extern box::data * from_i32(int32_t);
  extern box::data * from_i16(int16_t);
  extern box::data * from_i8(int8_t);

  extern double as_double(box::data * x);
  extern float as_float(box::data * x);
  extern uint64_t as_u64(box::data * x);
  extern uint32_t as_u32(box::data * x);
  extern uint16_t as_u16(box::data * x);
  extern uint8_t  as_u8(box::data * x);

  extern int64_t as_i64(box::data * x);
  extern int32_t as_i32(box::data * x);
  extern int16_t as_i16(box::data * x);
  extern int8_t  as_i8(box::data * x);

  /*
   * number of bytes needed to print out the value
   */
  extern size_t snprint(char * buf, size_t size, box::data *p);
};

union ptr {
  void * _;
  str::data       * str;
  set::data       * set;
  vect::data      * vect;
  map::data       * map;
  dict::data      * dict;
  tuple::data     * tuple;
  triple::data    * triple;
  quadruple::data * quadruple;
  block::data     * block;
  box::data       * box;
  singleton::data * singleton;
  stack::data     * stack;
};
  
namespace tagged {
/*
 * tagged value is useful to construct tagged union
 */
struct data {
  tag_t tag;
  union ptr ptr;
};

/*
 * tag: any integer value
 * v: a value 
 */
extern tagged::data * mk (uintptr_t tag, void * v);
extern tagged::data * mk_e (enum del_policy o, uintptr_t tag, void *v);
}

namespace closure {
  struct data {
    void * context;
    void * data;
    void * fun;
  };
};

extern void use_realloc(void *);
extern void use_malloc(void *);
extern void del(void *);
extern void del_ref(void *);
extern void del_e (enum del_policy o, void * p);
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
}
#endif // CEE_H 
#ifndef CEE_INTERNAL_H
#define CEE_INTERNAL_H

#ifndef NULL
#define NULL     ((void *)0)
#endif 

#endif // CEE_INTERNAL_H
using namespace cee;
void cee::del(void *p) {
  if (!p) cee::segfault();
  struct sect * cs = (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)));
  cs->del(p);
}
void cee::del_ref(void *p) {
  if (!p) cee::segfault();
  struct sect * cs = (struct sect *)((void *)((char *)p - sizeof(struct cee::sect)));
  if (cs->in_degree) cs->in_degree --;
  if (cs->retained) return;
  if (!cs->in_degree) cs->del(p);
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
  namespace box {
struct _cee_box_header {
  enum primitive_type type;
  struct sect cs;
  union primitive_value _[1];
};
static void _cee_box_del (void * v) {
  struct _cee_box_header * m = (struct _cee_box_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_box_header, _))));
  free(m);
}
static int _cee_box_cmp (void * v1, void * v2) {
  struct _cee_box_header * h1 = (struct _cee_box_header *)((void *)((char *)(v1) - (__builtin_offsetof(struct _cee_box_header, _))));
  struct _cee_box_header * h2 = (struct _cee_box_header *)((void *)((char *)(v2) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h1->cs.del == h2->cs.del)
    segfault();
  else
    segfault();
}
static struct _cee_box_header * _cee_box_mk_header(enum primitive_type t) {
  size_t mem_block_size = sizeof(struct _cee_box_header);
  struct _cee_box_header * b = (struct _cee_box_header *)malloc(mem_block_size);
  do{ memset(&b->cs, 0, sizeof(struct cee::sect)); } while(0);;
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
box::data * from_double (double d) {
  size_t mem_block_size = sizeof(struct data);
  struct _cee_box_header * b = _cee_box_mk_header(primitive_f64);
  b->cs.cmp = (void *)_cee_box_cmp_double;
  b->_[0].f64 = d;
  return (box::data *)b->_;
}
static int _cee_box_cmp_float(float v1, float v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
box::data * from_float (float d) {
  size_t mem_block_size = sizeof(struct data);
  struct _cee_box_header * b = _cee_box_mk_header(primitive_f32);
  b->cs.cmp = (void *)_cee_box_cmp_float;
  b->_[0].f32 = d;
  return (struct data *)b->_;
}
static int _cee_box_cmp_u64(uint64_t v1, uint64_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
box::data * from_u64 (uint64_t d) {
  size_t mem_block_size = sizeof(struct data);
  struct _cee_box_header * b = _cee_box_mk_header(primitive_u64);
  b->_[0].u64 = d;
  return (box::data *)b->_;
}
static int _cee_box_cmp_u32(uint32_t v1, uint32_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
box::data * from_u32 (uint32_t d) {
  size_t mem_block_size = sizeof(struct data);
  struct _cee_box_header * b = _cee_box_mk_header(primitive_u32);
  b->cs.cmp = (void *)_cee_box_cmp_u32;
  b->_[0].u32 = d;
  return (box::data *)b->_;
}
static int _cee_box_cmp_u16(uint16_t v1, uint16_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
box::data * from_u16 (uint16_t d) {
  size_t mem_block_size = sizeof(struct data);
  struct _cee_box_header * b = _cee_box_mk_header(primitive_u16);
  b->cs.cmp = (void *) _cee_box_cmp_u16;
  b->_[0].u16 = d;
  return (box::data *)b->_;
}
static int _cee_box_cmp_u8(uint8_t v1, uint8_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
box::data * from_u8 (uint8_t d) {
  size_t mem_block_size = sizeof(struct data);
  struct _cee_box_header * b = _cee_box_mk_header(primitive_u8);
  b->cs.cmp = (void *)_cee_box_cmp_u8;
  b->_[0].u8 = d;
  return (box::data *)b->_;
}
static int _cee_box_cmp_i64(int64_t v1, int64_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
box::data * from_i64 (int64_t d) {
  size_t mem_block_size = sizeof(struct data);
  struct _cee_box_header * b = _cee_box_mk_header(primitive_i64);
  b->cs.cmp = (void *)_cee_box_cmp_i64;
  b->_[0].i64 = d;
  return (box::data *)b->_;
}
static int _cee_box_cmp_i32(int32_t v1, int32_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
box::data * from_i32 (int32_t d) {
  size_t mem_block_size = sizeof(struct data);
  struct _cee_box_header * b = _cee_box_mk_header(primitive_i32);
  b->cs.cmp = (void *)_cee_box_cmp_i32;
  b->_[0].i32 = d;
  return (box::data *)b->_;
}
static int _cee_box_cmp_i16(int16_t v1, int16_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
box::data * from_i16 (int16_t d) {
  size_t mem_block_size = sizeof(struct box::data);
  struct _cee_box_header * b = _cee_box_mk_header(primitive_i16);
  b->cs.cmp = (void *)_cee_box_cmp_i16;
  b->_[0].i16 = d;
  return (box::data *)b->_;
}
static int _cee_box_cmp_i8(int8_t v1, int8_t v2) {
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    return 1;
  else
    return -1;
}
box::data * from_i8 (int8_t d) {
  size_t mem_block_size = sizeof(struct data);
  struct _cee_box_header * b = _cee_box_mk_header(primitive_i8);
  b->cs.cmp = (void *)_cee_box_cmp_i8;
  b->_[0].i8 = d;
  return (box::data *)b->_;
}
size_t snprint (char * buf, size_t size, box::data * x) {
  struct _cee_box_header * h = (struct _cee_box_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
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
double as_double (box::data * x) {
  struct _cee_box_header * h = (struct _cee_box_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == primitive_f64)
    return h->_[0].f64;
  else
    segfault();
}
float as_float (box::data * x) {
  struct _cee_box_header * h = (struct _cee_box_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == primitive_f32)
    return h->_[0].f32;
  else
    segfault();
}
uint64_t as_u64 (box::data * x) {
  struct _cee_box_header * h = (struct _cee_box_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == primitive_u64)
    return h->_[0].u64;
  else
    segfault();
}
uint32_t as_u32 (box::data * x) {
  struct _cee_box_header * h = (struct _cee_box_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == primitive_u32)
    return h->_[0].u32;
  else
    segfault();
}
uint16_t as_u16 (box::data * x) {
  struct _cee_box_header * h = (struct _cee_box_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == primitive_u16)
    return h->_[0].u16;
  else
    segfault();
}
uint8_t as_u8 (box::data * x) {
  struct _cee_box_header * h = (struct _cee_box_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == primitive_u8)
    return h->_[0].u8;
  else
    segfault();
}
int64_t as_i64 (box::data * x) {
  struct _cee_box_header * h = (struct _cee_box_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == primitive_i64)
    return h->_[0].i64;
  else
    segfault();
}
int32_t as_i32 (box::data * x) {
  struct _cee_box_header * h = (struct _cee_box_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == primitive_i32)
    return h->_[0].i32;
  else
    segfault();
}
int16_t as_i16 (box::data * x) {
  struct _cee_box_header * h = (struct _cee_box_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
  if (h->type == primitive_i16)
    return h->_[0].i16;
  else
    segfault();
}
int8_t as_i8 (box::data * x) {
  struct _cee_box_header * h = (struct _cee_box_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_box_header, _))));
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
static struct _cee_str_header * _cee_str_resize(struct _cee_str_header * h, size_t s)
{
  struct _cee_str_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
     ret = (struct _cee_str_header *)realloc(h, s);
      ret->cs.mem_block_size = s;
      break;
    case resize_with_malloc:
     ret = (struct _cee_str_header *)malloc(s);
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
  struct _cee_str_header * m = (struct _cee_str_header *)((void *)((char *)(p) - (__builtin_offsetof(struct _cee_str_header, _))));
  free(m);
}
str::data * mk (const char * fmt, ...) {
  if (!fmt) {
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
  h->cs.del = _cee_str_del;
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
str::data * mk_e (size_t n, const char * fmt, ...) {
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
  struct _cee_str_header * m = (struct _cee_str_header *) malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  m->cs.del = _cee_str_del;
  m->cs.resize_method = resize_with_malloc;
  m->cs.mem_block_size = mem_block_size;
  m->cs.cmp = (void *)strcmp;
  m->cs.cmp_stop_at_null = 1;
  m->capacity = mem_block_size - sizeof(struct _cee_str_header);
  if (fmt) {
    va_start(ap, fmt);
    vsnprintf(m->_, mem_block_size, fmt, ap);
  }
  else {
    m->_[0] = '\0';
  }
  return (str::data *)(m->_);
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
char * end(str::data * str) {
  struct _cee_str_header * b = (struct _cee_str_header *)((void *)((char *)(str) - (__builtin_offsetof(struct _cee_str_header, _))));
  return (char *)str + strlen((char *)str);
}
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
  s ++;
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
  struct vect::data * keys;
  struct vect::data * vals;
  uintptr_t size;
  enum del_policy del_policy;
  struct sect cs;
  struct hsearch_data _[1];
};
static void _cee_dict_del(void *d) {
  struct _cee_dict_header * m = (struct _cee_dict_header *)((void *)((char *)(d) - (__builtin_offsetof(struct _cee_dict_header, _))));
  hdestroy_r(m->_);
  del_e(m->del_policy, m->keys);
  del_e(m->del_policy, m->vals);
  free(m);
}
dict::data * mk_e (enum del_policy o, size_t size) {
  size_t mem_block_size = sizeof(struct _cee_dict_header);
  struct _cee_dict_header * m = (struct _cee_dict_header *)malloc(mem_block_size);
  m->del_policy = o;
  m->keys = vect::mk(size);
  use_realloc(m->keys);
  m->vals = vect::mk(size);
  use_realloc(m->vals);
  m->size = size;
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  m->cs.del = _cee_dict_del;
  m->cs.mem_block_size = mem_block_size;
  m->cs.resize_method = resize_with_identity;
  m->cs.n_product = 2;
  size_t hsize = (size_t)((float)size * 1.25);
  memset(m->_, 0, sizeof(struct hsearch_data));
  if (hcreate_r(hsize, m->_))
    return (dict::data *)(m->_);
  else {
    del(m->keys);
    del(m->vals);
    free(m);
    return NULL;
  }
}
dict::data * mk (size_t size) {
  return dict::mk_e (CEE_DEFAULT_DEL_POLICY, size);
}
void add (dict::data * d, char * key, void * value) {
  struct _cee_dict_header * m = (struct _cee_dict_header *)((void *)((char *)(d) - (__builtin_offsetof(struct _cee_dict_header, _))));
  ENTRY n, *np;
  n.key = key;
  n.data = value;
  if (!hsearch_r(n, ENTER, &np, m->_))
    segfault();
  m->keys = append(m->keys, key);
  m->vals = append(m->vals, value);
}
void * find(dict::data * d, char * key) {
  struct _cee_dict_header * m = (struct _cee_dict_header *)((void *)((char *)(d) - (__builtin_offsetof(struct _cee_dict_header, _))));
  ENTRY n, *np;
  n.key = key;
  n.data = NULL;
  if (hsearch_r(n, FIND, &np, m->_))
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
  struct sect cs;
  void * _[1];
};
struct _cee_map_pair {
  struct tuple::data * value;
  struct _cee_map_header * h;
};
static void _cee_map_free_pair(void * c) {
  struct _cee_map_pair * p = (struct _cee_map_pair *)c;
  del(p->value);
  free(p);
}
static void _cee_map_del(void * p) {
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(p) - (__builtin_offsetof(struct _cee_map_header, _))));
  tdestroy(b->_[0], _cee_map_free_pair);
  free(b);
}
static int _cee_map_cmp (const void * v1, const void * v2) {
  struct _cee_map_pair * t1 = (struct _cee_map_pair *) v1;
  struct _cee_map_pair * t2 = (struct _cee_map_pair *) v2;
  if (t1->h == t2->h)
   return t1->h->cmp(t1->value->_[0], t2->value->_[0]);
  else
    segfault();
}
map::data * mk (int (*cmp)(const void *, const void *)) {
  size_t mem_block_size = sizeof(struct _cee_map_header);
  struct _cee_map_header * m = (struct _cee_map_header *)malloc(mem_block_size);
  m->context = NULL;
  m->cmp = cmp;
  m->size = 0;
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  m->cs.del = _cee_map_del;
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->cs.cmp = 0;
  m->cs.cmp_stop_at_null = 0;
  m->cs.n_product = 2;
  m->_[0] = 0;
  return (map::data *)m->_;
}
uintptr_t size(struct map::data * m) {
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  return b->size;
}
void add(map::data * m, void * key, void * value) {
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  struct _cee_map_pair * triple = (struct _cee_map_pair *) malloc(sizeof(struct _cee_map_pair));
  triple->h = b;
  triple->value = tuple::mk(key, value);
  struct _cee_map_pair ** oldp = (struct _cee_map_pair **)tsearch(triple, b->_, _cee_map_cmp);
  if (oldp == NULL)
    segfault();
  else if (*oldp != triple)
    _cee_map_free_pair(triple);
  else
    b->size ++;
  return;
}
void * find(map::data * m, void * key) {
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  struct tuple::data t = { key, 0 };
  struct _cee_map_pair keyp = { .value = &t, .h = b };
  void **oldp = (void **)tfind(&keyp, b->_, _cee_map_cmp);
  if (oldp == NULL)
    return NULL;
  else {
    struct _cee_map_pair * p = (struct _cee_map_pair *)*oldp;
    return p->value->_[1];
  }
}
void * remove(map::data * m, void * key) {
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  void ** oldp = (void **)tdelete(key, b->_, _cee_map_cmp);
  if (oldp == NULL)
    return NULL;
  else {
    b->size --;
    struct _cee_map_pair * t = (struct _cee_map_pair *)*oldp;
    struct tuple::data * ret = t->value;
    _cee_map_free_pair(t);
    decr_indegree(b->key_del_policy, ret->_[0]);
    decr_indegree(b->val_del_policy, ret->_[1]);
    return ret->_[1];
  }
}
static void _cee_map_get_key (const void *nodep, const VISIT which, const int depth) {
  struct _cee_map_pair * p;
  struct _cee_map_header * h;
  struct vect::data * keys;
  switch (which)
  {
    case preorder:
    case leaf:
      p = *(struct _cee_map_pair **)nodep;
      h = p->h;
      keys = (struct vect::data *)h->context;
      h->context = vect::append(keys, p->value->_[0]);
      break;
    default:
      break;
  }
}
vect::data * keys(map::data * m) {
  uintptr_t s = map::size(m);
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  vect::data * keys = vect::mk(s);
  b->context = keys;
  twalk(b->_[0], _cee_map_get_key);
  return keys;
}
static void _cee_map_get_value (const void *nodep, const VISIT which, const int depth) {
  struct _cee_map_pair * p;
  struct _cee_map_header * h;
  vect::data * values;
  switch (which)
  {
    case preorder:
    case leaf:
      p = (struct _cee_map_pair *)*(void **)nodep;
      h = p->h;
      values = (vect::data *)h->context;
      h->context = vect::append(values, p->value->_[1]);
      break;
    default:
      break;
  }
}
vect::data * values(map::data * m) {
  uintptr_t s = map::size(m);
  struct _cee_map_header * b = (struct _cee_map_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_map_header, _))));
  vect::data * values = vect::mk(s);
  b->context = values;
  twalk(b->_[0], _cee_map_get_value);
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
  struct sect cs;
  void * _[1];
};
struct _cee_set_pair {
  void * value;
  struct _cee_set_header * h;
};
static void _cee_set_free_pair (void * c) {
  struct _cee_set_header * h = ((struct _cee_set_pair *)c)->h;
  del_e(h->del_policy, ((struct _cee_set_pair *)c)->value);
  free(c);
}
static void _cee_set_del(void * p) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(p) - (__builtin_offsetof(struct _cee_set_header, _))));
  tdestroy(h->_[0], _cee_set_free_pair);
  free(h);
}
static int _cee_set_cmp (const void * v1, const void * v2) {
  struct _cee_set_pair * t1 = (struct _cee_set_pair *) v1;
  struct _cee_set_pair * t2 = (struct _cee_set_pair *) v2;
  if (t1->h == t2->h)
   return t1->h->cmp(t1->value, t2->value);
  else
    segfault();
}
set::data * mk_e (enum del_policy o, int (*cmp)(const void *, const void *))
{
  struct _cee_set_header * m = (struct _cee_set_header *)malloc(sizeof(struct _cee_set_header));
  m->cmp = cmp;
  m->size = 0;
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  m->cs.del = _cee_set_del;
  m->cs.resize_method = resize_with_identity;
  m->cs.n_product = 1;
  m->context = NULL;
  m->_[0] = NULL;
  m->del_policy = o;
  return (set::data *)m->_;
}
set::data * mk (int (*cmp)(const void *, const void *)) {
  return set::mk_e(CEE_DEFAULT_DEL_POLICY, cmp);
}
size_t size (set::data * s) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(s) - (__builtin_offsetof(struct _cee_set_header, _))));
  return h->size;
}
bool empty (set::data * s) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(s) - (__builtin_offsetof(struct _cee_set_header, _))));
  return h->size == 0;
}
void add(set::data *m, void * val) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_set_header, _))));
  void ** c = (void **)malloc(sizeof(void *) * 2);
  c[0] = val;
  c[1] = h;
  void *** oldp = (void ***)tsearch(c, h->_, _cee_set_cmp);
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
static void _cee_set_noop(void *p) {}
void cee_set_clear (struct cee_set * s) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(s) - (__builtin_offsetof(struct _cee_set_header, _))));
  switch(h->del_policy) {
    case dp_del_rc:
      tdestroy(h->_[0], del_ref);
      break;
    case dp_del:
      tdestroy(h->_[0], del);
      break;
    case dp_noop:
      tdestroy(h->_[0], _cee_set_noop);
      break;
  }
  h->_[0] = NULL;
  h->size = 0;
}
void * find(set::data *m, void * value) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_set_header, _))));
  struct _cee_set_pair p = { value, h };
  void ***oldp = (void ***)tfind(&p, h->_, _cee_set_cmp);
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
      p = (_cee_set_pair *)*(void **)nodep;
      h = p->h;
      h->context = vect::append((struct vect::data *) h->context, p->value);
      break;
    default:
      break;
  }
}
vect::data * values(set::data * m) {
  uintptr_t s = set::size(m);
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_set_header, _))));
  h->context = vect::mk(s);
  use_realloc(h->context);
  twalk(h->_[0], _cee_set_get_value);
  return (vect::data *)h->context;
}
void * remove(set::data *m, void * key) {
  struct _cee_set_header * h = (struct _cee_set_header *)((void *)((char *)(m) - (__builtin_offsetof(struct _cee_set_header, _))));
  void ** old = (void **)tdelete(key, h->_, h->cmp);
  if (old == NULL)
    return NULL;
  else {
    h->size --;
    struct _cee_set_pair * p = (struct _cee_set_pair *)*old;
    void * k = p->value;
    free(p);
    return k;
  }
}
set::data * union_set (set::data * s1, set::data * s2) {
  struct _cee_set_header * h1 = (struct _cee_set_header *)((void *)((char *)(s1) - (__builtin_offsetof(struct _cee_set_header, _))));
  struct _cee_set_header * h2 = (struct _cee_set_header *)((void *)((char *)(s2) - (__builtin_offsetof(struct _cee_set_header, _))));
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
static void _cee_stack_del (void * v) {
  struct _cee_stack_header * m = (struct _cee_stack_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_stack_header, _))));
  int i;
  for (i = 0; i < m->used; i++)
    del_e(m->del_policy, m->_[i]);
  free(m);
}
stack::data * mk_e (enum del_policy o, size_t size) {
  uintptr_t mem_block_size = sizeof(struct _cee_stack_header) + size * sizeof(void *);
  struct _cee_stack_header * m = (struct _cee_stack_header *)malloc(mem_block_size);
  m->capacity = size;
  m->used = 0;
  m->top = (0-1);
  m->del_policy = o;
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  m->cs.del = _cee_stack_del;
  m->cs.mem_block_size = mem_block_size;
  return (stack::data *)(m->_);
}
stack::data * mk (size_t size) {
  return mk_e(CEE_DEFAULT_DEL_POLICY, size);
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
static void _cee_tuple_del(void * v) {
  struct _cee_tuple_header * b = (struct _cee_tuple_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_tuple_header, _))));
  int i;
  for (i = 0; i < 2; i++)
    del_e(b->del_policies[i], b->_[i]);
  free(b);
}
tuple::data * mk_e (enum del_policy o[2], void * v1, void * v2) {
  size_t mem_block_size = sizeof(struct _cee_tuple_header);
  struct _cee_tuple_header * m = (struct _cee_tuple_header *) malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  m->cs.del = _cee_tuple_del;
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
  m->_[0] = v1;
  m->_[1] = v2;
  int i;
  for (i = 0; i < 2; i++) {
    m->del_policies[i] = o[i];
    incr_indegree(o[i], m->_[i]);
  }
  return (tuple::data *)&m->_;
}
tuple::data * mk (void * v1, void * v2) {
  enum del_policy o[2] = { CEE_DEFAULT_DEL_POLICY, CEE_DEFAULT_DEL_POLICY };
  return mk_e(o, v1, v2);
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
static void _cee_triple_del(void * v) {
  struct _cee_triple_header * b = (struct _cee_triple_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_triple_header, _))));
  int i;
  for (i = 0; i < 3; i++)
    del_e(b->del_policies[i], b->_[i]);
  free(b);
}
triple::data * mk_e (enum del_policy o[3], void * v1, void * v2, void * v3) {
  size_t mem_block_size = sizeof(struct _cee_triple_header);
  struct _cee_triple_header * m = (struct _cee_triple_header *)malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  m->cs.del = _cee_triple_del;
  m->cs.resize_method = resize_with_identity;
  m->cs.mem_block_size = mem_block_size;
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
triple::data * mk (void * v1, void * v2, void *v3) {
  enum del_policy o[3] = { CEE_DEFAULT_DEL_POLICY,
                          CEE_DEFAULT_DEL_POLICY,
                          CEE_DEFAULT_DEL_POLICY };
  return mk_e(o, v1, v2, v3);
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
static void _cee_quadruple_del(void * v) {
  struct _cee_quadruple_header * b = (struct _cee_quadruple_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_quadruple_header, _))));
  int i;
  for (i = 0; i < 4; i++)
    del_e(b->del_policies[i], b->_[i]);
  free(b);
}
quadruple::data * mk_e (enum del_policy o[4], void * v1, void * v2, void * v3,
                        void * v4) {
  size_t mem_block_size = sizeof(struct _cee_quadruple_header);
  struct _cee_quadruple_header * m = (struct _cee_quadruple_header *) malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
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
    incr_indegree(o[i], m->_[i]);
  }
  return (quadruple::data *)&m->_;
}
  }
}
namespace cee {
namespace vect {
struct _cee_vect_header {
  uintptr_t size;
  uintptr_t capacity;
  enum del_policy del_policy;
  struct sect cs;
  void * _[];
};
static struct _cee_vect_header * _cee_vect_resize(struct _cee_vect_header * h, size_t s)
{
  struct _cee_vect_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
     ret = (struct _cee_vect_header *)realloc(h, s);
      ret->cs.mem_block_size = s;
      break;
    case resize_with_malloc:
     ret = (struct _cee_vect_header *)malloc(s);
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
  struct _cee_vect_header * m = (struct _cee_vect_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_vect_header, _))));
  int i;
  for (i = 0; i < m->size; i++)
    del_e(m->del_policy, m->_[i]);
  free(m);
}
vect::data * mk_e (enum del_policy o, size_t cap) {
  size_t mem_block_size = sizeof(struct _cee_vect_header) + cap * sizeof(void *);
  struct _cee_vect_header * m = (struct _cee_vect_header *)malloc(mem_block_size);
  m->capacity = cap;
  m->size = 0;
  m->del_policy = o;
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  m->cs.del = _cee_vect_del;
  m->cs.resize_method = resize_with_malloc;
  m->cs.mem_block_size = mem_block_size;
  return (vect::data *)(m->_);
}
vect::data * mk (size_t cap) {
  return mk_e(dp_del_rc, cap);
}
vect::data * append (vect::data * v, void *e) {
  struct _cee_vect_header * m = (struct _cee_vect_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_vect_header, _))));
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
  incr_indegree(m->del_policy, e);
  return (vect::data *)m->_;
}
vect::data * insert(vect::data * v, size_t index, void *e) {
  struct _cee_vect_header * m = (struct _cee_vect_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_vect_header, _))));
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
  incr_indegree(m->del_policy, e);
  return (vect::data *)m->_;
}
vect::data * remove(vect::data * v, size_t index) {
  struct _cee_vect_header * m = (struct _cee_vect_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_vect_header, _))));
  if (index >= m->size) return v;
  void * e = m->_[index];
  m->_[index] = 0;
  int i;
  for (i = index; i < (m->size - 1); i++)
    m->_[i] = m->_[i+1];
  m->size --;
  decr_indegree(m->del_policy, e);
  return (vect::data *)m->_;
}
size_t size (vect::data *x) {
  struct _cee_vect_header * m = (struct _cee_vect_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_vect_header, _))));
  return m->size;
}
size_t capacity (vect::data * x) {
  struct _cee_vect_header * h = (struct _cee_vect_header *)((void *)((char *)(x) - (__builtin_offsetof(struct _cee_vect_header, _))));
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
static void _cee_tagged_del (void * v) {
  struct _cee_tagged_header * m = (struct _cee_tagged_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_tagged_header, _))));
  del_e(m->del_policy, m->_.ptr._);
  free(m);
}
tagged::data * mk_e (enum del_policy o, uintptr_t tag, void *p) {
  size_t mem_block_size = sizeof(struct _cee_tagged_header);
  struct _cee_tagged_header * b = (struct _cee_tagged_header *)malloc(mem_block_size);
  do{ memset(&b->cs, 0, sizeof(struct cee::sect)); } while(0);;
  b->cs.del = _cee_tagged_del;
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = mem_block_size;
  b->_.tag = tag;
  b->_.ptr._ = p;
  b->del_policy = o;
  incr_indegree(o, p);
  return &b->_;
}
tagged::data * mk (uintptr_t tag, void *p) {
  return mk_e(CEE_DEFAULT_DEL_POLICY, tag, p);
}
  }
}
namespace cee {
  namespace singleton {
struct _cee_singleton_header {
  struct sect cs;
  uintptr_t _;
  uintptr_t val;
};
static void _cee_singleton_noop(void *p) {}
singleton::data * init(uintptr_t tag, void *s) {
  struct _cee_singleton_header * b = (struct _cee_singleton_header *)s;
  do{ memset(&b->cs, 0, sizeof(struct cee::sect)); } while(0);;
  b->cs.del = _cee_singleton_noop;
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = 0;
  b->cs.n_product = 0;
  b->_ = tag;
  b->val = 0;
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
static void _cee_closure_del (void * v) {
  struct _cee_closure_header * m = (struct _cee_closure_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_closure_header, _))));
  free(m);
}
struct data * mk (void * context, void * data, void * fun) {
  size_t mem_block_size = sizeof(struct _cee_closure_header);
  struct _cee_closure_header * b = (struct _cee_closure_header *)malloc(mem_block_size);
  do{ memset(&b->cs, 0, sizeof(struct cee::sect)); } while(0);;
  b->cs.del = _cee_closure_del;
  b->cs.resize_method = resize_with_identity;
  b->cs.mem_block_size = mem_block_size;
  b->_.context = context;
  b->_.data = data;
  b->_.fun = fun;
  return &(b->_);
}
}
}
namespace cee {
  namespace block {
struct _cee_block_header {
  uintptr_t capacity;
  enum del_policy del_policy;
  struct sect cs;
  char _[1];
};
static struct _cee_block_header * _cee_block_resize(struct _cee_block_header * h, size_t s)
{
  struct _cee_block_header * ret;
  switch(h->cs.resize_method)
  {
    case resize_with_realloc:
     ret = (struct _cee_block_header *)realloc(h, s);
      ret->cs.mem_block_size = s;
      break;
    case resize_with_malloc:
     ret = (struct _cee_block_header *)malloc(s);
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
  struct _cee_block_header * m = (struct _cee_block_header *)(struct _cee_block_header *)((void *)((char *)(p) - (__builtin_offsetof(struct _cee_block_header, _))));
  free(m);
}
void * mk (size_t n) {
  size_t mem_block_size;
  va_list ap;
  mem_block_size = n + sizeof(struct _cee_block_header);
  struct _cee_block_header * m = (struct _cee_block_header *)malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  m->del_policy = dp_del_rc;
  m->cs.del = _cee_block_del;
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
static void _cee_n_tuple_del(void * v) {
  struct _cee_n_tuple_header * b = (struct _cee_n_tuple_header *)((void *)((char *)(v) - (__builtin_offsetof(struct _cee_n_tuple_header, _))));
  int i;
  for (i = 0; i < b->cs.n_product; i++)
    del_e(b->del_policies[i], b->_[i]);
  free(b);
}
static struct _cee_n_tuple_header * cee_n_tuple_v (size_t ntuple,
                                         enum del_policy o[], va_list ap) {
  if (ntuple > 16)
    segfault();
  size_t mem_block_size = sizeof(struct _cee_n_tuple_header);
  struct _cee_n_tuple_header * m = (struct _cee_n_tuple_header *) malloc(mem_block_size);
  do{ memset(&m->cs, 0, sizeof(struct cee::sect)); } while(0);;
  m->cs.del = _cee_n_tuple_del;
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
n_tuple::data * mk (size_t ntuple, ...) {
  va_list ap;
  va_start(ap, ntuple);
  enum del_policy * o = (enum del_policy *)malloc(ntuple * sizeof (enum del_policy));
  int i;
  for (i = 0; i < ntuple; i++)
    o[i] = CEE_DEFAULT_DEL_POLICY;
  struct _cee_n_tuple_header * h = cee_n_tuple_v(ntuple, o, ap);
  free(o);
  return (n_tuple::data *)(h->_);
}
  }
}
#endif
