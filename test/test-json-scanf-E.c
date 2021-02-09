#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "json-scanf.h"

const char test_str [] =
  "{"
  " |i|:10, |b|:true, |s|:|hello world| "
  "}";


int main () {
  int i;
  float f;
  bool b;
  char s[20];

  void *E[5] = {0};

  char * json_str = NULL;
  json_asprintf(&json_str, (char *)test_str);


  int ret = json_scanf(json_str, strlen(json_str),
                       "[i]%d [f]%f  [b]%b [s]%20s %E",
                       &i, &f, &b, s, &E);

  free(json_str);

  printf ("json_scan extract %d values\n", ret);
  printf ("i = %d, &i = %p\n", i, &i);

  for (int j = 0; E[j]; j++) {
    printf ("%p\n", E[j]);

    if (E[j] == &i)
      printf ("i is defined\n");

    if (E[j] == &f)
      printf ("f is defined\n");

    if (E[j] == &b)
      printf ("b is defined\n");

    if (E[j] == &s)
      printf ("s is defined\n");
  }
  return 0;
}

