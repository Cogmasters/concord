#ifndef NTL_H
#define NTL_H

#include <stddef.h> // for size_t

/*
 * a null terminated list implementation
 *
 * a null terminated list of n elements of type struct E is defined as
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
 *  for (size_t i = 0; p[i]; i++)
 *    // do something here for each element
 *
 */
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


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
 * this is the preferred method to allocate a ntl
 * if init is NULL, it is the same as ntl_calloc
 */
void **
ntl_calloc_init (size_t nelems,  size_t elem_size, void (*init)(void * elem_p));


/*
 * this is the preferred method to allocate a ntl
 */
void **
ntl_calloc (size_t nelems,  size_t elem_size);


/*
 * please use ntl_calloc_init unless you have a very good reason to use this
 * if init is NULL, it is the same as ntl_malloc
 */
void **
ntl_malloc_init (size_t nelems,  size_t elem_size, void (*init)(void * elem_p));


/*
 * please use ntl_calloc unless you have a very good reason to use this
 */
void ** ntl_malloc (size_t nelems,  size_t elem_size);


void **
ntl_realloc_init(void **p, size_t new_nelems, size_t elem_size,
                 void (*init)(void * elem_p));
/*
 * duplicate a ntl
 */
void ** ntl_dup (void ** p, size_t size);

/*
 * for each element e, calls free_elem(e)
 * free(p);
 */
void ntl_free(void **p, void (*free_elem)(void *));

size_t ntl_length (void **p);
size_t ntl_elem_size (void **p);

/*
 * for each element e, calls f(e)
 */
void ntl_apply(void *cxt, void **p, void (*f)(void *cxt, void *p));

typedef void (ntl_converter)(void *cxt, void * from, void * to);
void ** ntl_fmap(void * cxt, void ** from_list,
                 size_t to_elem_size, ntl_converter * f);

/*
 * Add one element to the end of ntl, this is not super efficient
 * for many appends, but it's ok for a few appends.
 *
 * It caller's responsibility to make sure the added_elem has the
 * same type and size as the element's type and size of the ntl
 */
void ** ntl_append(void ** p, size_t elem_size, void * added_elem);


typedef int (ntl_elem_serializer)(char * buf, size_t size, void *p);

struct ntl_serializer {
  struct ntl_str_delimiter * delimiter;
  /*
 * elem_to_buf(NULL, 0, p) calculates the size needed to serializer p
 * elem_to_buf(buf, n, p) serialize p to a buffer
 * elem_to_buf should return a negative value for any errors
 */
  void (*elem_to_buf)(char * buf, size_t size, void * elem);
  void ** ntl_provider;
};

struct ntl_str_delimiter {
  char start_delimiter;
  char * element_delimiter;
  char * last_element_delimiter;
  char end_delimiter;
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
int ntl_to_buf(char *buf, size_t buf_size, void **p,
               struct ntl_str_delimiter  * d,
               ntl_elem_serializer * x);

/*
 * ntl_to_abuf behaviors like asprintf
 */

int ntl_to_abuf(char **buf_ptr, void **p, struct ntl_str_delimiter  * d,
                ntl_elem_serializer * x);


int ntl_to_buf2(char * buf, size_t size, struct ntl_serializer * serializer);
int ntl_to_abuf2(char ** buf_p, struct ntl_serializer * serializer);

struct ntl_deserializer {
  /* Required: this function partition a sized buffer to n sized buffers,
   * each one represents one element */
  int (*partition_as_sized_bufs)(char *, size_t, struct sized_buffer ***p);
  /* Required: the size of each element, it will be used to allocate memory */
  size_t elem_size;
  /* Optional: the function to initialize an element, it can be NULL */
  void (*init_elem)(void *);
  /* Required: the function to load element data from buf to recipient */
  void (*elem_from_buf)(char * buf, size_t size, void * recipient);

  /* Required: a pointer of ntl that is to receive the reconstructed ntl */
  void *** ntl_recipient_p;
};

/*
 * The function reconstructs a ntl from a sized buffer
 *
 * ntl_deserializer: have all the information to reconstruct an element
 *    from a sized buffer
 */
int
ntl_from_buf (char *buf, size_t len, struct ntl_deserializer * ntl_deserializer);

int
ntl_is_a_member (void ** p , void * addr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //NTL_H
