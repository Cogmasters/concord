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

static char * filename = __FILE__;

struct expect_at {
  int loc;
  char * expected;
};

struct expected_results {
  struct expect_at spec;
  struct expect_at field_struct;
  struct expect_at field_cleanup;
  struct expect_at field_extractor;
  struct expect_at field_extractor_arg;
  struct expect_at field_injector;
  struct expect_at field_injector_arg;
  struct expect_at field_inject_settings;
};

struct expected_results results;

#define SET(field, str)     { results.field.expected = str; results.field.loc = __LINE__; }

void check_s(char *s, struct expect_at *correct, char * file, int loc)
{
  while(*s == ' ') s++;
  int ret = strcmp(s, correct->expected);

  if (ret != 0) {
    fprintf(stderr, "%s:%d expecting '%s', got '%s'\n",
            filename, correct->loc, correct->expected, s);
    abort();
  }
}

#define check(s, c) check_s(s, c, __FILE__, __LINE__);



static struct jc_field f;
static int i;
void test_one()
{
  char *str;

  fprintf (stderr, "Testing %s@%d\n", results.spec.expected, results.spec.loc);

  load_field(&f, results.spec.expected);
  str = field_to_string(&i, emit_field, &f);
  check(str, &results.field_struct);

  str = field_to_string(&i, emit_field_cleanup, &f);
  check(str, &results.field_cleanup);

  str = field_to_string(&i, emit_json_extractor, &f);
  check(str, &results.field_extractor);

  str = field_to_string(&i, emit_json_extractor_arg, &f);
  check(str, &results.field_extractor_arg);

  str = field_to_string(&i, emit_json_injector, &f);
  check(str, &results.field_injector);

  str = field_to_string(&i, emit_json_injector_arg, &f);
  check(str, &results.field_injector_arg);

  str = field_to_string(&i, emit_inject_setting, &f);
  check(str, &results.field_inject_settings);
}

int main (int argc, char ** argv)
{
  SET(spec, "{(name):|abc|, (type):{ (base):|int| }}");
  SET(field_struct, "int abc;\n");
  SET(field_cleanup, "//p->abc is a scalar\n");
  SET(field_extractor, "\"(abc):d,\"\n");
  SET(field_extractor_arg, "&p->abc,\n");
  SET(field_injector, "\"(abc):d,\"\n");
  SET(field_injector_arg, "&p->abc,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = &p->abc;\n");
  test_one();

  SET(spec, "{(name):|abc|, (type):{ (base):|int|, (int_alias):|enum code| }}");
  SET(field_struct, "enum code abc;\n");
  SET(field_cleanup, "//p->abc is a scalar\n");
  SET(field_extractor, "\"(abc):d,\"\n");
  SET(field_extractor_arg, "&p->abc,\n");
  SET(field_injector, "\"(abc):d,\"\n");
  SET(field_injector_arg, "&p->abc,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = &p->abc;\n");
  test_one();


  SET(spec, "{(name):|abc|, (json_key):|abc-1 23|, (type):{ (base):|int| }}");
  SET(field_struct, "int abc;\n");
  SET(field_cleanup, "//p->abc is a scalar\n");
  SET(field_extractor, "\"(abc-1 23):d,\"\n");
  SET(field_extractor_arg, "&p->abc,\n");
  SET(field_injector, "\"(abc-1 23):d,\"\n");
  SET(field_injector_arg, "&p->abc,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = &p->abc;\n");
  test_one();

  return 0;
}

