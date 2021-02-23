#include <stdio.h>
#include <string.h>
#include "jqbs.c"
#include "json-scanf.h"

int main (int argc, char ** argv)
{
  size_t len = 0;
  char s[1024];

  json_snprintf(s, sizeof(s),
                "{ |namespace|: [ |A|, |B| ],"
                  "|description|: |url|,"
                  "|structs|:"
                  "["
                  "  { |name|:|dati|,"
                  "    |fields|:"
                  "    ["
                  "      { |name|:|f1|, |type|:{ |base|:|char|, |decorator|:|pointer| } },"
                  "      { |name|:|f2|, |type|:{ |base|:|char|, |decorator|:|pointer| } }"
                  "      { |name|:|f3|, |type|:{ |base|:|long long|, |decorator|:|none| } }"
                  "    ]"
                  "  },"
                  "  { |name|:|params|,"
                  "    |fields|:"
                  "    ["
                  "      { |name|:|f1|, |type|:{ |base|:|char|, |decorator|:|pointer| }, |loc|:|json| },"
                  "      { |name|:|f2|, |type|:{ |base|:|char|, |decorator|:|pointer| }, |loc|:|body| }"
                  "      { |name|:|f3|, |type|:{ |base|:|long long|, |decorator|:|none| }, |loc|:|query| }"
                  "    ]"
                  "  }"
                  "]"
                "}");

  fprintf(stderr, "%s\n", s);

  struct jc_definition d;
  memset(&d, 0, sizeof(d));
  definition_from_json(s, strlen(s), &d);
  print_definition(stderr, &d);

  gen_definition(stderr, &d);
  return 0;
}
