#ifndef NTL_H
#define NTL_H
#include <stddef.h> /* for size_t */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * this is a very important data structure that is used
 * pervasively in the conversion between JSON strings and C structs,
 * http request/response body
 */
struct sized_buffer {
  char *start;
  size_t size;
};


/*
 * A Null Terminated List (ntl) implementation
 *
 * A null terminated list of n elements of type struct E is defined as
 *
 * struct ntl {
 *    void * indices[n+1];  // indices[n] = NULL
 *    struct E e[n];  // sizeof (struct E)
 * };
 *
 * the list can be allocated as
 * p = ntl_calloc(n, size);
 *
 *       /-indices[n+1]\   /--------- e[n]-----------\
 * p -> [ | | | | | | |0][e_0]...............[e_(n-1)]
 *       |                 ^
 *       |                 |
 *       +-------->--------+
 *
 * p points to the begin of the memory block which overlaps with indices.
 *
 * p[0] points to e_0
 * p[1] points to e_1
 * ...
 * p[n-1] points to e_(n-1)
 * p[n] points to NULL
 *
 *
 * if p is NULL, it is treated as an empty NTL by all ntl functions.
 *
 * The use of ntl is very simple
 *
 *  for (size_t i = 0; p && p[i]; i++)
 *    // do something here for each element
 *
 * A ntl pointed by p is empty if p is NULL or p[0] == NULL
 *
 */
typedef void** ntl_t;

/*
 * used to define ntl with an actual type
 */
#define NTL_T(t)  t**


typedef void (*ntl_init_cb)(void *);

/*
 * this is the preferred method to allocate a ntl
 * if init is NULL, it is the same as ntl_calloc
 */
ntl_t ntl_calloc_init(size_t nelems, size_t elem_size, ntl_init_cb init_cb);


/*
 * this is the preferred method to allocate a ntl
 */
ntl_t ntl_calloc(size_t nelems,  size_t elem_size);


/*
 * please use ntl_calloc_init unless you have a very good reason to use this
 * if init is NULL, it is the same as ntl_malloc
 */
ntl_t ntl_malloc_init(size_t nelems, size_t elem_size, ntl_init_cb init_cb);


/*
 * please use ntl_calloc unless you have a very good reason to use this
 */
ntl_t ntl_malloc(size_t nelems,  size_t elem_size);


ntl_t ntl_realloc_init(void **p, size_t new_nelems, size_t elem_size, ntl_init_cb init_cb);

/*
 * duplicate a ntl
 */
ntl_t ntl_dup(ntl_t p, size_t size);

typedef void (*ntl_free_cb)(void*);
/*
 * for each element e, calls cleanup(e)
 * free(p);
 */
void ntl_free(ntl_t p, ntl_free_cb cb);

size_t ntl_length(ntl_t p);
size_t ntl_length_max(ntl_t p, size_t max);
size_t ntl_elem_size(ntl_t p);

/*
 * for each element e, calls f(e)
 */
void ntl_apply(void *cxt, ntl_t p, void (*f)(void *cxt, void *elem_p));

typedef void (elem_converter)(void *cxt, void *from_elem, void *to_elem);

ntl_t ntl_fmap(void *cxt, ntl_t from_list, size_t to_elem_size, elem_converter *f);

/*
 * Add one element to the end of ntl, this is not super efficient
 * for many appends, but it's ok for a few appends.
 *
 * It caller's responsibility to make sure the added_elem has the
 * same type and size as the element's type and size of the ntl
 */
ntl_t ntl_append(ntl_t p, size_t elem_size, void *added_elem);


void ntl_append2(ntl_t *p, size_t elem_size, void *added_elem);


typedef size_t (ntl_elem_serializer)(char * buf, size_t size, void *p);

struct ntl_serializer {
  struct ntl_str_delimiter * delimiter;
  /*
 * elem_to_buf(NULL, 0, p) calculates the size needed to serializer p
 * elem_to_buf(buf, n, p) serialize p to a buffer
 * elem_to_buf should return a negative value for any errors
 */
  size_t (*elem_to_buf)(char *buf, size_t size, void *elem);
  ntl_t ntl_provider;
};

struct ntl_str_delimiter {
  char start_delimiter;
  char *element_delimiter;
  char *last_element_delimiter;
  char end_delimiter;
  char *null_ntl;
};

/*
 * ntl_to_buf behaviors like snprintf
 *
 * ntl_to_buf(NULL, 0, ..) return the number of bytes (excluding \0) needed to
 *       serialize p
 *
 * ntl_to_buf(buf, n, ..) serialize p to buf and return the number of
 *       bytes written excluding \0
 */
size_t ntl_to_buf(char *buf, size_t buf_size, ntl_t p, struct ntl_str_delimiter  *d, ntl_elem_serializer *x);

/*
 * ntl_to_abuf behaviors like asprintf
 */

size_t ntl_to_abuf(char **buf_ptr, ntl_t p, struct ntl_str_delimiter *d, ntl_elem_serializer *x);


size_t ntl_to_buf2(char *buf, size_t size, struct ntl_serializer *serializer);
size_t ntl_to_abuf2(char **buf_p, struct ntl_serializer *serializer);

struct ntl_deserializer {
  /* Required: this function partition a sized buffer to n sized buffers,
   * each one represents one element */
  int (*partition_as_sized_bufs)(char *, size_t, NTL_T(struct sized_buffer) *p);
  /* Required: the size of each element, it will be used to allocate memory */
  size_t elem_size;
  /* Optional: the function to initialize an element, it can be NULL */
  void (*init_elem)(void *);
  /* Required: the function to load element data from buf to recipient */
  void (*elem_from_buf)(char *buf, size_t size, void *recipient);

  /* Required: a pointer of ntl that is to receive the reconstructed ntl */
  ntl_t *ntl_recipient_p;
};

/*
 * The function reconstructs a ntl from a sized buffer
 *
 * ntl_deserializer: have all the information to reconstruct an element
 *    from a sized buffer
 */
size_t ntl_from_buf(char *buf, size_t len, struct ntl_deserializer *ntl_deserializer);
size_t ntl_from_buf2(char *buf, size_t len, struct ntl_deserializer *ntl_deserializer);

int ntl_is_a_member(ntl_t p , void *addr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*NTL_H */
