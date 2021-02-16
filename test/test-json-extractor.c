#include "json-extractor.c"
#include <string.h>

int main ()
{
  int i, j, k;
  char * json = "{ \"a\":10 }";
  json_extract(json, strlen(json), "(a):d", &i);
  fprintf (stderr, "%d\n", i);


  json = "{ \"a\": { \"b\":10 }";
  json_extract(json, strlen(json), "(a)(b):d", &i);
  fprintf (stderr, "%d\n", i);

  json = "[ 13, 14, 15 ]";

  json_extract(json, strlen(json), "[d, d, d]", &i, &j, &k);
  fprintf (stderr, "%d, %d, %d\n", i, j, k);
  return 0;
}