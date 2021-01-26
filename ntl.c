#include "ntl.h"
#include <stdlib.h>
#include <string.h>

void **
ntl_malloc (size_t nelems,  size_t elem_size)
{
  char * p = (char *)malloc((nelems + 1) * sizeof(void *) + nelems * elem_size);
  char * elem_start = p + (nelems + 1) * sizeof(void *);
  void ** array = (void **)p;
  int i;
  for (i = 0; i < nelems; i++) {
    array[i] = (void *)elem_start;
    elem_start += elem_size;
  }
  array[i] = 0;
  return array;
}

void **
ntl_calloc (size_t nelems,  size_t elem_size)
{
  void ** p = ntl_malloc(nelems, elem_size);
  char * start_to_zero = (char *)p + ((nelems + 1) * sizeof(void *));
  memset(start_to_zero, 0, nelems * elem_size);
  return p;
}

void
ntl_free(void **p, void (*free_elem)(void *p))
{
  int i;
  for (i = 0; p[i]; i++)
    (*free_elem)(p[i]);
  free(p);
}

size_t
ntl_length (void **p)
{
  int i;
  for (i = 0; p[i]; i++) /* empty body */;

  return i;
}

void **
ntl_dup (void ** p, size_t elem_size)
{
  // use calloc to make the dupcated list safer
  return ntl_calloc(ntl_length(p), elem_size);
}


void
ntl_apply(void **p, void (*f)(void *p))
{
  int i;
  for (i = 0; p[i]; i++)
    (*f)(p[i]);
}

/*
 * null_term_list_snp(NULL, 0, p, x) will calculate the size needed to print p
 */
int
ntl_sn2str(char *str, size_t size, void **p, sn2str * x)
{
  char * start = str;
  int i, tsize = 0;
  if (start) {
    str[0] = '[';
    str ++;
  }

  tsize ++;
  for(i = 0; p[i]; i++) {
    bool is_last = (NULL == p[i+1]);
    int psize = (*x)(NULL, 0, p[i], is_last);
    tsize += psize;

    if(start) {
      (*x)(str, psize, p[i], is_last);
      str += psize;
    }
  }

  if (start) {
    str[0] = ']';
  }
  tsize ++;
  return tsize;
}

int
ntl_as2str(char ** str, void **p, sn2str * x)
{
  int s = ntl_sn2str(NULL, 0, p, x);
  *str = (char *)malloc(s);
  return ntl_sn2str(*str, s, p, x);
}

void **
ntl_fmap(void ** from_list, size_t to_elem_size, ntl_converter * f)
{
  void ** to_list = ntl_dup(from_list, to_elem_size);
  int i;
  for (i = 0; from_list[i]; i++)
    (*f)(&from_list[i], &to_list[i]);
  return to_list;
}
