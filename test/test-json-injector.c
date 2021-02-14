#include <stdio.h>
#include "json-actor.h"
#include <string.h>

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
int main () {
  json_inject(bigbuf, sizeof(bigbuf), "[ true, false, true]");
  fprintf(stderr, "%s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf), "[ null, 1]");
  fprintf(stderr, "%s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf), "[ null, |abc|]");
  fprintf(stderr, "%s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf), "{ (k):null, (b):|abc|}");
  fprintf(stderr, "%s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf), "{ (k):null, (x):|abc|}");
  fprintf(stderr, "%s\n", bigbuf);

  char * t = "abc";
  int i = 10;
  float f = 10.4;

  json_inject(bigbuf, sizeof(bigbuf), "[ s d f ]", t, &i, &f);
  fprintf(stderr, "%s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf),
              "{ (a string) : s  (a int) : d  ( a float ):f }",
              t, &i, &f);
  fprintf(stderr, "%s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf),
                "{ (a string) : s,  (a int) : d,  ( a float ):f }",
                NULL, NULL, NULL);
  fprintf(stderr, "%s\n", bigbuf);

  int b = 0;
  void *A[2] = {&b, 0};
  json_inject(bigbuf, sizeof(bigbuf), "[ b, b ] @", &i, &b, &A);
  fprintf(stderr, "used @ %s\n", bigbuf);

  fprintf (stderr, "funptr %p\n", &foobar);
  json_inject(bigbuf, sizeof(bigbuf), "[ F ]", &foobar, NULL);
  fprintf(stderr, "%s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf), "[ F ]", &foobar, &i);
  fprintf(stderr, "%s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf),
              "(k1) : s"
              "(k2) : {  (1): b }"
              "(k3):f"
              "@",
              NULL, &b, NULL, A);

  fprintf(stderr, "%s\n", bigbuf);


  void *B[4] = {NULL};
  memset(B, 0, sizeof(B));

  char * injector1 = "(k1) : s, (k2) : { (1): b }, (k3) : f @";

  // print out k1
  B[0] = t;
  json_inject(bigbuf, sizeof(bigbuf),
              injector1,
              t, &b, &f, B);
  fprintf(stderr, "%s\n", bigbuf);

  // print out k1 and k3
  B[1] = &f;
  json_inject(bigbuf, sizeof(bigbuf),
              injector1,
              t, &b, &f, B);

  fprintf(stderr, "%s\n", bigbuf);

  // print out k1, k2, and k3
  B[1] = &f;
  B[2] = &b;
  json_inject(bigbuf, sizeof(bigbuf),
              injector1,
              t, &b, &f, B);

  fprintf(stderr, "%s\n", bigbuf);
  return 0;
}
