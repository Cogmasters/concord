#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ntl.h"


#ifdef CEE_STATIC
#define STATIC static
#else
#define STATIC
#endif 

/* 
 * @n_elems  the number of new elements
 * @elem_size  the size of element
 * @init   the function to initialize each element, it can be NULL
 */
STATIC ntl_t ntl_malloc_init(size_t n_elems,  size_t elem_size, ntl_init_cb init_cb)
{
  /*
   * allocate one consecutive memory block for storing
   *
   * 1. a NULL terminated array of (n_elems + 1) pointers
   * 2. n_elems elements of size `elem_size`
   */
  void **p = malloc(
    (n_elems + 1) * sizeof(void *) /* for a NULL terminated array of n_elems pointers */
    + n_elems * elem_size /* for n_elems elements */
  );

  /*
   * p[0] .. p[n_elems - 1] will store the addresses of `n_elems` elements
   * p[n_elems] will store a NULL pointer to terminate the array
   * p[n_elems + 1] points to the start of the first element
   */
  char * elem_start = (char *)&p[n_elems + 1];
  size_t i;

  for (i = 0; i < n_elems; i++) {
    /* p[i] points to the start of ith element. */
    p[i] = (void *)elem_start;
    if (init_cb)
      init_cb(p[i]);

    /* move elem_start to point to the start of the next element */
    elem_start += elem_size;
  }

  /* terminate this ntl with a NULL; */
  p[n_elems] = NULL;
  return p;
}

STATIC ntl_t ntl_malloc(size_t n_elems, size_t elem_size)
{
  return ntl_malloc_init(n_elems, elem_size, NULL);
}

/*
 * @n_elems  the number of elements
 * @e_size   the size of each element
 * @init     the function to initialize an element
 */
STATIC ntl_t ntl_calloc_init(size_t n_elems, size_t e_size, ntl_init_cb init_cb)
{
  ntl_t p = ntl_malloc_init(n_elems, e_size, NULL);
  /*
   * p[0] .. p[elems - 1] hold the addressess of n_elems elements
   * p[elems] is NULL to terminated the array
   * p[elems + 1] is the start of the first element
   */
  char * elem_start = (char *)(&p[n_elems + 1]);
  int i;

  memset(elem_start, 0, n_elems * e_size);

  if (init_cb) {
    for (i = 0; p[i]; i++)
      init_cb(p[i]);
  }
  return p;
}

STATIC ntl_t ntl_calloc(size_t n_elems,  size_t elem_size)
{
  return ntl_calloc_init(n_elems, elem_size, NULL);
}

/*
 * @p a NTL
 * @new_n_elems  the new number of elements
 * @elem_size   the size of an element
 * @init        the function to initialize an element, it can be NULL
 *
 */
STATIC ntl_t ntl_realloc_init(ntl_t p, size_t new_n_elems, size_t elem_size, ntl_init_cb init_cb)
{
  ntl_t new_p = ntl_calloc_init(new_n_elems, elem_size, NULL);

  size_t i=0;

  if (NULL != p) {
    for ( ; p[i]; ++i) {
      /* (shallow) copy over data from old element to new element */
      memcpy(new_p[i], p[i], elem_size);
    }
    /* free the ntl but NOT cleanup its elements */
    free(p);
  }

  if (init_cb) {
    for ( ; new_p[i]; ++i) {
      /* initialize new elements */
      init_cb(new_p[i]);
    }
  }

  return new_p;
}


/*
 * @p a NTL to be freed, it can be NULL
 * @cleanup  clean up each element, it can be NULL
 */
STATIC void ntl_free(ntl_t p, ntl_free_cb free_cb)
{
  size_t i;

  if (p == NULL)
    return;

  if (free_cb)
    for (i = 0; p[i]; i++)
      (*free_cb)(p[i]);
  free(p);
}

/*
 * @p a NTL
 */
STATIC size_t ntl_length(ntl_t p)
{
  if (NULL == p) /* NULL is treated as empty */
    return 0;

  static size_t dummy;
  size_t i = 0;
  while (p[i]) {
    /* dummy will never be used, but it can prevent compilers */
    /* from optimizing this loop away. */
    dummy ++;
    i ++;
  }

  return i;
}

/*
 * @p a NTL
 * @max maximum length the function can return, used for optimization
 */
STATIC size_t ntl_length_max(ntl_t p, size_t max)
{
  if (NULL == p) /* NULL is treated as empty */
    return 0;

  static size_t dummy;
  size_t i = 0;
  while (p[i] && i < max) {
    /* dummy will never be used, but it can prevent compilers */
    /* from optimizing this loop away. */
    dummy ++;
    i ++;
  }

  return i;
}


STATIC ntl_t ntl_dup(ntl_t p, size_t elem_size)
{
  size_t i;
  ntl_t o =  ntl_calloc(ntl_length(p), elem_size);
  for (i = 0; p[i]; i++)
    memcpy(o[i], p[i], elem_size);
  return o;
}


STATIC void ntl_apply(void *cxt, ntl_t p, void (*f)(void *cxt, void *p))
{
  if (NULL == p) return;
  size_t i;
  for (i = 0; p[i]; i++)
    (*f)(cxt, p[i]);
}

STATIC size_t ntl_to_buf2(char *buf, size_t size, struct ntl_serializer *serializer)
{
  if (serializer->ntl_provider == NULL)
    return 0;
  return ntl_to_buf(buf, size,
                    serializer->ntl_provider,
                    serializer->delimiter,
                    serializer->elem_to_buf);
}

STATIC size_t ntl_to_abuf2(char **buf_p, struct ntl_serializer *serializer)
{
  int s = ntl_to_buf2(NULL, 0, serializer);
  if (s < 0)
    return -1;

  *buf_p = (char *)malloc(s);
  return ntl_to_buf2(*buf_p, s, serializer);
}

/*
 *
 */
STATIC size_t ntl_to_buf(char *buf, size_t size, ntl_t p, struct ntl_str_delimiter *d, ntl_elem_serializer *x)
{
  static struct ntl_str_delimiter dx = 
  { .start_delimiter = '[', 
    .element_delimiter = ",", 
    .last_element_delimiter = "", 
    .end_delimiter = ']',
    .null_ntl = "null"
  };

  if (!d) d = &dx;

  const char *start = buf;
  size_t i, tsize = 0;
  size_t psize;

  if (p == NULL) {
    if (dx.null_ntl == NULL)
      return 0;
    else {
      tsize = snprintf(buf, size, "%s", dx.null_ntl);
      return tsize;
    }
  }

  

  if (start) {
    buf[0] = d->start_delimiter;
    buf ++;
  }
  tsize ++;

  for(i = 0; p[i]; i++) {
    bool is_last = (NULL == p[i+1]);
    psize = (*x)(buf, size, p[i]);

    if(start) {
      buf += psize; /* move to next available byte */
    }
    tsize += psize;
    if (is_last) {
      psize = strlen (d->last_element_delimiter);
      if (start) {
        memcpy(buf, d->last_element_delimiter, psize);
        buf += psize;
      }
    }
    else {
      psize = strlen (d->element_delimiter);
      if (start) {
        memcpy(buf, d->element_delimiter, psize);
        buf += psize;
      }
    }
    tsize += psize;
  }

  if (start) {
    *buf = d->end_delimiter;
    buf ++;
  }
  *buf = '\0';

  tsize ++;
  return tsize;
}

STATIC size_t ntl_to_abuf(char **buf_p, ntl_t p, struct ntl_str_delimiter *d, ntl_elem_serializer *x)
{
  if (p == NULL)
    return 0;

  int s = ntl_to_buf(NULL, 0, p, d, x);
  if (s < 0)
    return -1;

  *buf_p = (char *)malloc(s);
  return ntl_to_buf(*buf_p, s, p, d, x);
}

/*
 * This is like Haskell list's fmap
 *
 * @cxt  points to any context data need for this transformation
 * @in_list the input ntl
 * @out_elem_size, the size of each output element
 * @f the function transform each in element to one out element
 */
STATIC ntl_t ntl_fmap(void *cxt, ntl_t in_list, size_t out_elem_size, elem_converter *f)
{
  size_t i;
  if (in_list == NULL)
    return NULL;

  ntl_t out_list = ntl_calloc(ntl_length(in_list), out_elem_size);
  if (f)
    for (i = 0; in_list[i]; i++)
      (*f)(cxt, in_list[i], out_list[i]);

  return out_list;
}


/*
 * In most cases, you don't need this.
 */
STATIC ntl_t ntl_append(ntl_t p, size_t elem_size, void *added_elem)
{
  size_t i=0;
  ntl_t o = ntl_calloc(1 + ntl_length(p), elem_size);
  while (p && p[i]) {
    /* copy prev array contents to new array */
    memcpy(o[i], p[i], elem_size);
    i++;
  }
  memcpy(o[i], added_elem, elem_size);
  return o;
}


/*
 * @p the address that stores a NTL
 * @esize the element size of the new element
 * @added_elem  the memory of element to be appended
 * @free_elem  free the memory of each element
 *
 * this function will allocate memory for a new list
 * and free the old list.
 *
 */
STATIC void ntl_append2(ntl_t *p, size_t esize, void * added_elem)
{
  ntl_t ntl1 = *p;
  ntl_t ntl2 = ntl_append(ntl1, esize, added_elem);
  if (ntl1)
    free(ntl1);
  *p = ntl2;
}

STATIC size_t ntl_from_buf(char *buf, size_t len, struct ntl_deserializer *deserializer)
{
  struct sized_buffer **elem_bufs = NULL;
  int ret = (*deserializer->partition_as_sized_bufs)(buf, len, &elem_bufs);
  if (0 == ret) {
    *deserializer->ntl_recipient_p = NULL;
    return 0;
  }

  size_t i;
  size_t n_elems = ntl_length((void **)elem_bufs);
  ntl_t new_ntl =
    ntl_calloc_init(n_elems, deserializer->elem_size, deserializer->init_elem);

  for (i=0; elem_bufs[i]; ++i)
    (*deserializer->elem_from_buf)(
      elem_bufs[i]->start,
      elem_bufs[i]->size,
      new_ntl[i]);

  free(elem_bufs);
  *(deserializer->ntl_recipient_p) = new_ntl;
  return n_elems;
}

STATIC size_t ntl_from_buf2(char *buf, size_t len, struct ntl_deserializer *deserializer)
{
  struct sized_buffer **elem_bufs = NULL;
  int ret = (*deserializer->partition_as_sized_bufs)(buf, len, &elem_bufs);
  if (0 == ret) {
    *deserializer->ntl_recipient_p = NULL;
    return 0;
  }

  size_t n_elems = ntl_length((void **)elem_bufs);
  size_t i;
  ntl_t new_ntl =
    ntl_calloc_init(n_elems, deserializer->elem_size, deserializer->init_elem);

  for (i=0; elem_bufs[i]; ++i)
    (*deserializer->elem_from_buf)(
      elem_bufs[i]->start,
      elem_bufs[i]->size,
      new_ntl+i);

  free(elem_bufs);
  *(deserializer->ntl_recipient_p) = new_ntl;
  return n_elems;
}

STATIC int ntl_is_a_member(ntl_t p, void *addr)
{
  size_t i;

  if (p == NULL)
    return 0;

  for (i = 0; p[i]; i++)
    if (p[i] == addr)
      return 1;

  return 0;
}
