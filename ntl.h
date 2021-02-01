#ifndef NTL_H
#define NTL_H
#include <stddef.h> // for size_t
#include <stdbool.h>

/*
 * a null terminated list implementation
 *
 * a null terminated list of n elements of type struct E is defined as
 *
 * struct ntl {
 *    void * indices[n+1];  // indices[n] = NULL
 *    size_t size;
 *    struct E e[n];  // sizeof (struct E) == size
 * };
 *
 * the list can be allocated as
 * p = ntl_calloc(n, size);
 *
 *       /-indices[n+1]\        /--------- e[n]-----------\
 * p -> [ | | | | | | |0][size][e_0]...............[e_(n-1)]
 *       |                     ^
 *       |                     |
 *       +----------->---------+
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
 *  for (int i = 0; p[i]; i++)
 *    // do something here for each element
 *
 */
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/*
 * this is a very important data structure that is used
 * pervasive in the conversion between JSON string and C structs,
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



/*
 * duplicate a ntl
 */
void ** ntl_dup (void ** p);

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
void ntl_apply(void **p, void (*f)(void *p));

typedef void (ntl_converter)(void * from, void * to);
void ** ntl_fmap(void ** from_list, size_t to_elem_size, ntl_converter * f);

/*
 * Add one element to the end of ntl, this is not super efficient
 * for many appends, but it's ok for a few appends.
 *
 * It caller's responsibility to make sure the added_elem has the
 * same type and size as the element's type and size of the ntl
 */
void ** ntl_append(void ** p, void * added_elem);

/*
 * sn2str(NULL, 0, p) will calculate the size needed to print *p
 * sn2str(buf, n, p) will print to buffer
 */
typedef int (sn2str)(char * str, size_t size, void *p);

struct ntl_str_delimiter {
  char start_delimiter;
  char * element_delimiter;
  char * last_element_delimiter;
  char end_delimiter;
};

int ntl_sn2str(char *buf, size_t buf_size, void **p,
               struct ntl_str_delimiter  * d,
               sn2str * x);

int ntl_as2str(char **buf_ptr, void **p,
               struct ntl_str_delimiter  * d,
               sn2str * x);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //NTL_H
