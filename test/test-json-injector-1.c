#include <stdio.h>
#include "json-actor.h"
#include <string.h>
#include <stdlib.h>

int foobar (char * pos, size_t size, void *p)
{
  if (NULL == p) {
    return snprintf(pos, size, "{}");
  }
  else {
    int * i = (int *)p;
    return snprintf(pos, size, "%d, %d", *i, *i+1);
  }
}

static char bigbuf[1024];
int main ()
{
  void * A[2] = {0};
  char * content = "This is the content.";

  json_inject(bigbuf, sizeof(bigbuf), "(content):s @arg_switches",
              content, A, sizeof(A));
  fprintf(stderr, "%s\n", bigbuf);

  A[0] = content;
  json_inject(bigbuf, sizeof(bigbuf), "(content):s @arg_switches",
              content, A, sizeof(A));
  fprintf(stderr, "%s\n", bigbuf);

  //content = NULL;
  A[0] = NULL;
  json_inject(bigbuf, sizeof(bigbuf), "(content):s @arg_switches",
              content, A, sizeof(A));
  fprintf(stderr, "%s\n", bigbuf);

  return 0;
}
