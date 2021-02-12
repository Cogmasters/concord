#include "json-actor.c"
#include <string.h>

int f (char * pos, size_t size, void *p)
{
  if (NULL == p) {
    snprintf(pos, size, "{}");
  }
  else {
    snprintf(pos, size, "%s", p);
  }
}

int main () {
  char * pos;
  pos = json_injector("[ true false true]");
  fprintf(stderr, "%s\n", pos);
  free(pos);

  pos = json_injector("[ null 1]");
  fprintf(stderr, "%s\n", pos);
  free(pos);

  pos = json_injector("[ null \"abc\"]");
  fprintf(stderr, "%s\n", pos);
  free(pos);

  pos = json_injector("{ [k]:null [b]:\"abc\"}");
  fprintf(stderr, "%s\n", pos);
  free(pos);


  pos = json_injector("{ [k]:null [x]:\"abc\"}");
  fprintf(stderr, "%s\n", pos);
  free(pos);


  char * t = "abc";
  int i = 10;
  float f = 10.4;

  pos = json_injector("[ s d f ]", t, &i, &f);
  fprintf(stderr, "%s\n", pos);
  free(pos);

  pos = json_injector("{ [a string] : s  [a int] : d  [ a float ]:f }",
                      t, &i, &f);
  fprintf(stderr, "%s\n", pos);
  free(pos);


  pos = json_injector("{ [a string] : s  [a int] : d  [ a float ]:f }",
                      NULL, NULL, NULL);
  fprintf(stderr, "%s\n", pos);
  free(pos);

  int b = 0;
  pos = json_injector("[ b b ]", &i, &b);
  fprintf(stderr, "%s\n", pos);
  free(pos);


  fprintf (stderr, "funptr %p\n", &f);
  pos = json_injector("[ F ]", &f, NULL);
  fprintf(stderr, "%s\n", pos);
  free(pos);
}
