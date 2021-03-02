#include <assert.h>
#include "json-struct.c"
#include "orka-utils.h"

char* json_string(char *s)
{
  char * b;
  json_ainject(&b, s);
  return b;
}

void load_field(struct jc_field *f, char *str)
{
  memset(f, 0, sizeof(*f));
  char *json = json_string(str);
  fprintf(stderr, "%s\n", json);
  field_from_json(json, strlen(json), f);
}

struct expected_results {
  char * spec;
  char * file;
  int loc;
  char * field_struct;
  char * field_cleanup;
  char * field_extractor;
  char * field_extractor_arg;
  char * field_injector;
  char * field_injector_arg;
  char * field_inject_settings;
};

struct expected_results results;

void check_s(char *s, const char *correct, char * file, int loc)
{
  while(*s == ' ') s++;
  int ret = strcmp(s, correct);

  if (ret != 0) {
    fprintf(stderr, "%s:%d expecting '%s', got '%s'\n",
            results.file, results.loc, correct, s);
    abort();
  }
}

#define check(s, c) check_s(s, c, __FILE__, __LINE__);



static struct jc_field f;
static int i;
void test_one(struct expected_results *results)
{
  char *str, * spec = results->spec;

  fprintf (stderr, "Testing %s\n", spec);

  load_field(&f, spec);
  str = field_to_string(&i, emit_field, &f);
  check(str, results->field_struct);

  str = field_to_string(&i, emit_field_cleanup, &f);
  check(str, results->field_cleanup);

  str = field_to_string(&i, emit_json_extractor, &f);
  check(str, results->field_extractor);

  str = field_to_string(&i, emit_json_extractor_arg, &f);
  check(str, results->field_extractor_arg);

  str = field_to_string(&i, emit_json_injector, &f);
  check(str, results->field_injector);

  str = field_to_string(&i, emit_json_injector_arg, &f);
  check(str, results->field_injector_arg);

  str = field_to_string(&i, emit_inject_setting, &f);
  check(str, results->field_inject_settings);
}

int main (int argc, char ** argv)
{
  results.spec = "{(name):|abc|, (type):{ (base):|int| }}";;
  results.field_struct = "int abc;\n";
  results.field_cleanup = "//p->abc is a scalar\n";
  results.field_extractor = "\"(abc):d,\"\n";
  results.field_extractor_arg = "&p->abc,\n";
  results.field_injector = "\"(abc):d,\"\n";
  results.field_injector_arg = "&p->abc,\n";
  results.field_inject_settings = "p->__M.arg_switches[0] = &p->abc;\n";
  test_one(&results);

  results.spec = "{(name):|abc|, (type):{ (base):|int|, (int_alias):|enum code| }}";;
  results.field_struct = "enum code abc;\n";
  results.field_cleanup = "//p->abc is a scalar\n";
  results.field_extractor = "\"(abc):d,\"\n";
  results.field_extractor_arg = "&p->abc,\n";
  results.field_injector = "\"(abc):d,\"\n";
  results.field_injector_arg = "&p->abc,\n";
  results.field_inject_settings = "p->__M.arg_switches[0] = &p->abc;\n";
  test_one(&results);


  results.spec = "{(name):|abc|, (json_key):|abc-1 23|, (type):{ (base):|int| }}";;
  results.field_struct = "int abc;\n";
  results.field_cleanup = "//p->abc is a scalar\n";
  results.field_extractor = "\"(abc-1 23):d,\"\n";
  results.field_extractor_arg = "&p->abc,\n";
  results.field_injector = "\"(abc-1 23):d,\"\n";
  results.field_injector_arg = "&p->abc,\n";
  results.field_inject_settings = "p->__M.arg_switches[0] = &p->abc;\n";
  test_one(&results);

  return 0;
}

