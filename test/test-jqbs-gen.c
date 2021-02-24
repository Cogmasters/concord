#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "jqbs.c"
#include "json-scanf.h"

static
void print_usage (char * prog)
{
  fprintf(stderr, "Usage: %s [-h|-c] -o output-file input-file\n",
          prog);
  exit(EXIT_FAILURE);
}

int main (int argc, char ** argv)
{
  size_t len = 0;
  char * s;

  int opt;
  char * config_file = NULL;
  enum file_type type = FILE_SINGLE_FILE;

  while ((opt = getopt(argc, argv, "hco:")) != -1) {
    switch (opt) {
      case 'o':
        config_file = strdup(optarg);
        break;
      case 'h':
        type = FILE_HEAD;
        break;
      case 'c':
        type = FILE_CODE;
        break;
      default: /* '?' */
        print_usage(argv[0]);
    }
  }

  char * file =  argv[optind];
  s = orka_load_whole_file(file, &len);

  struct jc_definition d;
  memset(&d, 0, sizeof(d));
  definition_from_json(s, len, &d);
  //print_definition(stderr, &d);
  FILE * fp = fopen(config_file, "w");
  gen_definition(fp, type, &d);
  fclose(fp);
  return 0;
}
