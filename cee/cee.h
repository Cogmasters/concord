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