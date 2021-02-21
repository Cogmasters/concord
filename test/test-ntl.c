#include <stdio.h>
#include "ntl.h"


static int count = 0;
struct abc {
  char s[10];
  int i;
};

void init(void * x)
{
  struct abc * p = (struct abc *) x;
  snprintf(p->s, 10, "%d", count);
  p->i = count;
  count ++;
}

void print_abc(struct abc * p, int i)
{
  fprintf(stderr, "[%d] %s, %d\n", i, p->s, p->i);
}

int main ()
{
  void **p = ntl_malloc_init(10, sizeof(struct abc), init);

  for(int i = 0; p[i]; i++)
    print_abc(p[i], i);

  p = ntl_realloc_init(p, 100, sizeof(struct abc), init);

  for(int i = 0; p[i]; i++)
    print_abc(p[i], i);
}
