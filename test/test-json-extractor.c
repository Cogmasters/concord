#include "json-extractor.c"
#include <string.h>

int main ()
{
  int i;
  char * json = "{ \"a\":10 }";
  json_extract(json, strlen(json), "(a):d", &i);
  fprintf (stderr, "%d\n", i);
  return 0;
}