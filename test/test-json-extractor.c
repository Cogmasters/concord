#include "json-actor.c"
#include <string.h>
#include <assert.h>

int main ()
{
  int i, j, k;
  char * json = "{ \"a\":10 }";
  json_extract(json, strlen(json), "(a):d", &i);
  fprintf (stderr, "%d\n", i);
  assert(i == 10);


  json = "{ \"a\": { \"b\":11 }}";
  json_extract(json, strlen(json), "(a)(b):d", &i);
  fprintf (stderr, "%d\n", i);
  assert(i == 11);


  json = "{ \"a\": [ 13, 14, 15 ] }";
  json_extract(json, strlen(json), "(a)(0):d", &i);
  fprintf (stderr, "%d\n", i);
  assert(i == 13);


  json = "{ \"a\": [ { \"b\":123 }, 14, 15 ] }";
  json_extract(json, strlen(json), "(a)(0)(b):d", &i);
  fprintf (stderr, "%d\n", i);
  assert(i == 123);

  json = "[ 13, 14, 15 ]";

  json_extract(json, strlen(json), "[d, d, d]", &i, &j, &k);
  fprintf (stderr, "%d, %d, %d\n", i, j, k);
  return 0;
}