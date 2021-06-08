#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <locale.h>

#include "orka-utils.h"
#include "json-actor.c"

#define UTF8_JSON "{\"a\":\"Íñdîæ\",\"b\":\"Müller\",\"c\":\"的\",\"d\":\"😊\"}"

int main()
{
  setlocale(LC_ALL, "");

  char a[16], b[16], c[16], d[16];

  json_extract(UTF8_JSON, sizeof(UTF8_JSON), \
      "(a):s,(b):s,(c):s,(d):s", a, b, c, d);
  printf("original a: Íñdîæ\tnew a: %s\n", a);
  printf("original b: Müller\tnew b: %s\n", b);
  printf("original c: 的\tnew c: %s\n", c);
  printf("original d: 😊\tnew d: %s\n", d);

  char payload[1024];
  json_inject(payload, sizeof(payload), \
      "(a):s,(b):s,(c):s,(d):s", a, b, c, d);
  printf("original json:\n"UTF8_JSON"\nnew json:\n%s\n", payload);

  assert(0 == strcmp(a, "Íñdîæ"));
  assert(0 == strcmp(b, "Müller"));
  assert(0 == strcmp(c, "的"));
  assert(0 == strcmp(d, "😊"));
  assert(0 == strcmp(payload, UTF8_JSON));

  return EXIT_SUCCESS;
}

