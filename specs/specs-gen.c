#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "json-struct.c"

static void print_usage(char *prog)
{
  fprintf(
    stderr,
    "Usage: %s [-h|-c|-d|-f] -o output-file -i include-headers input-file \n"
    "      -h generate header\n"
    "      -c generate data and function definitions\n"
    "      -d generate data and function declarations\n"
    "      -S generate struct declarations\n"
    "      -E generate enum declarations\n"
    "      -F generate function declarations\n"
    "      -f generate function definitions\n"
    "      -O generate all opaque struct declarations\n"
    "      -a append to output\n",
    prog);
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
  size_t len = 0;
  char *s;

  char *config_file = NULL;
  struct emit_option eo = { .type = FILE_SINGLE_FILE };

  char *open_mode = "w";
  NTL_T(name_t) incl_headers = NULL;

  int opt;
  while (-1 != (opt = getopt(argc, argv, "ahcdfSEFOo:i:"))) {
    switch (opt) {
    case 'a': open_mode = "a"; break;
    case 'o': config_file = strdup(optarg); break;
    case 'i': {
      name_t header = "";
      snprintf(header, sizeof(name_t), "%s", optarg);
      ntl_append2((ntl_t *)&incl_headers, sizeof(name_t), &header);
      break;
    }
    case 'h': eo.type = FILE_HEADER; break;
    case 'c': eo.type = FILE_CODE; break;
    case 'd': eo.type = FILE_DECLARATION; break;
    case 'f': eo.type = FILE_DEFINITION; break;
    case 'S': eo.type = FILE_STRUCT_DECLARATION; break;
    case 'E': eo.type = FILE_ENUM_DECLARATION; break;
    case 'F': eo.type = FILE_FUN_DECLARATION; break;
    case 'O': eo.type = FILE_OPAQUE_STRUCT_DECLARATION; break;
    default: /* '?' */ print_usage(argv[0]);
    }
  }

  if (!config_file) print_usage(argv[0]);

  char *file = argv[optind];
  s = cee_load_whole_file(file, &len);
  spec_name = file;
  spec_buffer.start = s;
  spec_buffer.size = len;

  struct jc_definition d;
  memset(&d, 0, sizeof(d));
  definition_from_json(s, len, &d);
  d.spec_name = file;
  d.incl_headers = incl_headers;
  gen_definition(config_file, open_mode, &eo, &d);

  return EXIT_SUCCESS;
}
