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
  #define CEE_SINGLETON_SIZE (sizeof(struct cee::singleton) + sizeof(struct cee::sect))

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