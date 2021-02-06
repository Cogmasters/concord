#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memcmp()

#include "orka-utils.h"
#include "json-scanf.h"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "%s <file>", argv[0]);
    return 0;
  }

  size_t size = 0;
  char * str = orka_load_whole_file(argv[1], &size);

  fprintf(stderr, "raw string size\t%ld\n", size);
  size_t new_size = 0;
  char * estr = json_escape_string(&new_size, str, size);

  fprintf(stderr, "escaped size\t%ld\n", new_size);
  //fprintf(stderr, "escaped string %.*s\n", new_size, estr);

  size_t unstr_size = 0;
  char * unstr = NULL;
  json_unescape_string(&unstr, &unstr_size, estr, new_size);

  fprintf(stderr, "unescaped size\t%ld\n", unstr_size);

  if (0 != memcmp(str, unstr, size)) {
    fprintf(stderr, "escaping/unescaping failed\n");
  }
  return 0;
}
