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
int main () {
  json_inject(bigbuf, sizeof(bigbuf), "[ true, false, true]");
  fprintf(stderr, "%s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf), "[ null, 1]");
  fprintf(stderr, "%s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf), "[ null, |abc|]");
  fprintf(stderr, "%s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf), "[ null, |abc%d|]", 10);
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
  void *A[4] = {&b, 0, 0};
  json_inject(bigbuf, sizeof(bigbuf), "[ b, b ] @A", &i, &b, &A, sizeof(A));
  fprintf(stderr, "used @ %s\n", bigbuf);

  fprintf (stderr, "funptr %p\n", (void*)&foobar);
  json_inject(bigbuf, sizeof(bigbuf), "[ F ]", &foobar, NULL);
  fprintf(stderr, "%s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf), "[ F ]", &foobar, &i);
  fprintf(stderr, "[ F ] > %s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf), "[ |F| ]", &foobar, &i);
  fprintf(stderr, "[ |F| ] > %s\n", bigbuf);

  json_inject(bigbuf, sizeof(bigbuf),
              "(k1) : s"
              "(k2) : {  (1): b }"
              "(k3):f"
              "@A",
              NULL, &b, NULL,
              A, sizeof(A));

  fprintf(stderr, "%s\n", bigbuf);


  void *B[4] = {NULL};
  memset(B, 0, sizeof(B));

  char * injector1 = "(k1) : s, (k2) : { (1): b }, (k3) : f @A";

  // print out k1
  B[0] = t;
  json_inject(bigbuf, sizeof(bigbuf),
              injector1,
              t, &b, &f, B, sizeof(B));
  fprintf(stderr, "%s\n", bigbuf);

  // print out k1 and k3
  B[1] = &f;
  json_inject(bigbuf, sizeof(bigbuf),
              injector1,
              t, &b, &f, B, sizeof(B));

  fprintf(stderr, "%s\n", bigbuf);

  // print out k1, k2, and k3
  B[1] = &f;
  B[2] = &b;
  json_inject(bigbuf, sizeof(bigbuf),
              injector1,
              t, &b, &f, B, sizeof(B));

  fprintf(stderr, "%s\n", bigbuf);

  injector1 = "(ref): |refs/heads/%s| (sha): s";

  char * p = NULL;
  json_ainject(&p, injector1, "master", "sssssshhhhhaa");

  fprintf(stderr, "%s\n", p);
  free(p);

  int delete_message_days = 100;
  char * reason = "a bad reason";

  void *A1[4] = {0};

  if (delete_message_days > 0)
    A1[0] = &delete_message_days;
  if (strlen(reason))
    A1[1] = reason;

  json_inject(bigbuf, sizeof(bigbuf),
              "(delete_message_days):d"
              "(reason):s"
              "@A",
              &delete_message_days,
              reason,
              A1, sizeof(A1));

  fprintf(stderr, "%s\n", bigbuf);

  memset(A1, 0, sizeof(A1));
  delete_message_days = 0;
  if (delete_message_days > 0)
    A1[1] = &delete_message_days;

  if (strlen(reason))
    A1[0] = reason;

  json_inject(bigbuf, sizeof(bigbuf),
              "(delete_message_days):d"
              "(reason):s"
              "@A",
              &delete_message_days,
              reason,
              A1, sizeof(A1));

  fprintf(stderr, "%s\n", bigbuf);


  memset(A1, 0, sizeof(A1));
  delete_message_days = 1000;
  if (delete_message_days > 0)
    A1[0] = &delete_message_days;

  reason = "";
  if (strlen(reason))
    A1[1] = reason;

  json_inject(bigbuf, sizeof(bigbuf),
              "(delete_message_days):d"
              "(reason):s"
              "@A",
              &delete_message_days,
              &reason,
              A1, sizeof(A1));

  fprintf(stderr, "%s\n", bigbuf);

  char * token = "token";
  int intents = 10;
  char * payload = NULL;
  json_ainject(&payload,
               "(op) : 2" // IDENTIFY OP
               "(d) : {"
                 "(token) : s"
                 "(intents) : d"
                 "(properties) : {"
                 "($os): |POSIX|"
                 "($browser) : |orca|"
                 "($device) : |orca|"
                 "}"
                 "(presence) : {"
                 "(since) : null"
                 "(activities) : null"
                 "(status) : |online|"
                 "(afk) : false"
                 "}"
               "}",
               token,
               &intents,
               NULL,
               NULL, NULL,
               "online",
               NULL,
               A, sizeof(A));

  fprintf(stderr, "%s\n", payload);

  extern char * url_decode(char *);
  fprintf(stderr, "%s\n", url_decode("%20hello%20world%20"));

  char query[512];
  char * ss = "Qa'wakana";
  query_inject(query, sizeof(query),
               "(a):d"
               "(b):s",
               &i,
               ss);

  fprintf(stderr, "'%s'\n", query);


  memset(A, 0, sizeof(A));
  A[0] = ss;

  query_inject(query, sizeof(query),
               "(a):d"
               "(b):s"
               "@A",
               &i, ss, A, sizeof(A));

  fprintf(stderr, "'%s'\n", query);


  memset(A, 0, sizeof(A));
  query_inject(query, sizeof(query),
               "(a):d"
               "(b):s"
               "@A",
               &i, ss, A, sizeof(A));

  fprintf(stderr, "empty query_string: '%s'\n", query);

  return 0;
}
