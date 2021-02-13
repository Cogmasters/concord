#include "json-actor.c"
#include <string.h>

int foobar (char * pos, size_t size, void *p)
{
  if (NULL == p) {
    return snprintf(pos, size, "{}");
  }
  else {
    return snprintf(pos, size, "%s", p);
  }
}

static char bigbuf[1024];
int main () {
  json_injector(bigbuf, sizeof(bigbuf), "[ true false true]");
  fprintf(stderr, "%s\n", bigbuf);

  json_injector(bigbuf, sizeof(bigbuf), "[ null 1]");
  fprintf(stderr, "%s\n", bigbuf);

  json_injector(bigbuf, sizeof(bigbuf), "[ null \"abc\"]");
  fprintf(stderr, "%s\n", bigbuf);

  json_injector(bigbuf, sizeof(bigbuf), "{ [k]:null [b]:\"abc\"}");
  fprintf(stderr, "%s\n", bigbuf);

  json_injector(bigbuf, sizeof(bigbuf), "{ [k]:null [x]:\"abc\"}");
  fprintf(stderr, "%s\n", bigbuf);

  char * t = "abc";
  int i = 10;
  float f = 10.4;

  json_injector(bigbuf, sizeof(bigbuf), "[ s d f ]", t, &i, &f);
  fprintf(stderr, "%s\n", bigbuf);

  json_injector(bigbuf, sizeof(bigbuf),
                "{ [a string] : s  [a int] : d  [ a float ]:f }",
                t, &i, &f);
  fprintf(stderr, "%s\n", bigbuf);

  json_injector(bigbuf, sizeof(bigbuf),
                "{ [a string] : s  [a int] : d  [ a float ]:f }",
                NULL, NULL, NULL);
  fprintf(stderr, "%s\n", bigbuf);

  int b = 0;
  json_injector(bigbuf, sizeof(bigbuf), "[ b b ]", &i, &b);
  fprintf(stderr, "%s\n", bigbuf);

  fprintf (stderr, "funptr %p\n", &foobar);
  json_injector(bigbuf, sizeof(bigbuf), "[ F ]", &foobar, NULL);
  fprintf(stderr, "%s\n", bigbuf);
}
