#include <stdio.h>
#include <stdlib.h>

#include "orka-utils.h"
#include "json-scanf.h"
#include "json-actor.h"

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "%s <json-file>\n", argv[0]);
    return 1;
  }

  size_t len = 0;
  char * json = orka_load_whole_file(argv[1], &len);

  int i;
  json_extract(json, len, "(total):d", &i);
  fprintf(stderr, "%d", i);
  return 0;
}

