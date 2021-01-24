#include "null_term_list.h"


void ** null_term_list_malloc (size_t nmem,  size_t elem_size)
{
  char * p = (char *)malloc((nmem + 1) * sizeof(void *) + nmem * elem_size);
  char * elem_start = p + (nmem + 1) * sizeof(void *);
  void ** array = (void **)p;
  int i;
  for (i = 0; i < nmem; i++) {
    array[i] = (void *)elem_start;
    elem_start += elem_size;
  }
  array[i] = 0;
  return array;
}

size_t null_term_list_length (void **p)
{
  int i;
  for (i = 0; p[i]; i++);
  return i;
}

void ** null_term_list_dup (void ** p, size_t elem_size)
{
  return null_term_list_malloc(null_term_list_length(p), elem_size);
}

/*
 * snp(NULL, 0, p) will calculate the size needed to print *p
 * snp(buf, n, p) will print to buffer
 */
typedef int (snp)(char * str, size_t size, void *p);

/*
 * null_term_list_snp(NULL, 0, p, x) will calculate the size needed to print p
 */
int null_term_list_snp(char *str, size_t size, void **p, snp * x)
{
  char * start = str;
  int i, tsize = 0;
  for(i = 0; p[i]; i++)
  {
    int psize = (*x)(NULL, 0, p[i]);

    if(start) {
      (*x)(str, psize, p[i]);
      str += psize;
    }
  }
  return str - start;
}

