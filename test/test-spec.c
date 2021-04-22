#include <assert.h>
#include <ctype.h>
#include "json-struct.c"
#include "orka-utils.h"


void load_field(struct jc_field *f, char *str)
{
  memset(f, 0, sizeof(*f));
  char *json=NULL;
  json_ainject(&json, str);
  fprintf(stderr, "%s\n", json);
  field_from_json(json, strlen(json), f);
}

static char * filename = __FILE__;

struct expect_at {
  int loc;
  char * expected;
};

#define SKIP_SPACES(s)  while(isspace(*s)) s++;

struct expected_results {
  struct expect_at spec;
  struct expect_at field_struct;
  struct expect_at field_cleanup;
  struct expect_at field_extractor;
  struct expect_at field_extractor_arg;
  struct expect_at field_injector;
  struct expect_at field_injector_arg;
  struct expect_at field_inject_settings;
  struct expect_at field_init;
};

struct expected_results results;

#define SET(field, str)     { results.field.expected = str; results.field.loc = __LINE__; }

void check_s(char *s, struct expect_at *correct, char * file, int loc)
{
  if (s == NULL && correct->expected == NULL)
    return;

  while(*s == ' ') s++;
  int ret = strcmp(s, correct->expected);

  if (ret != 0) {
    fprintf(stderr, "%s:%d expecting |%s|, got |%s|\n",
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

  fprintf (stderr, "%s:%d  testing `%s`\n",
           filename, results.spec.loc, results.spec.expected);

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

  str = field_to_string(&i, emit_field_init, &f);
  check(str, &results.field_init);
}

int main (int argc, char ** argv)
{
  init_converters ();
  SET(spec, "{(name):|abc|, (type):{ (base):|int| }}");
  SET(field_struct, "int abc;\n");
  SET(field_cleanup, "//p->abc is a scalar\n");
  SET(field_extractor, "\"(abc):d,\"\n");
  SET(field_extractor_arg, "&p->abc,\n");
  SET(field_injector, "\"(abc):d,\"\n");
  SET(field_injector_arg, "&p->abc,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = &p->abc;\n");
  SET(field_init, NULL);
  test_one();

  SET(spec, "{(name):|abc|, (type):{ (base):|int|, (int_alias):|enum code| }}");
  SET(field_struct, "enum code abc;\n");
  SET(field_cleanup, "//p->abc is a scalar\n");
  SET(field_extractor, "\"(abc):d,\"\n");
  SET(field_extractor_arg, "&p->abc,\n");
  SET(field_injector, "\"(abc):d,\"\n");
  SET(field_injector_arg, "&p->abc,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = &p->abc;\n");
  SET(field_init, NULL);
  test_one();


  SET(spec, "{(name):|abc|, (json_key):|abc-1 23|, (type):{ (base):|int| }}");
  SET(field_struct, "int abc;\n");
  SET(field_cleanup, "//p->abc is a scalar\n");
  SET(field_extractor, "\"(abc-1 23):d,\"\n");
  SET(field_extractor_arg, "&p->abc,\n");
  SET(field_injector, "\"(abc-1 23):d,\"\n");
  SET(field_injector_arg, "&p->abc,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = &p->abc;\n");
  SET(field_init, NULL);
  test_one();

  SET(spec, "{(name):|f1|, (type):{ (base):|char|, (dec):|*| }}");
  SET(field_struct, "char *f1;\n");
  SET(field_cleanup, "if (d->f1)\n    free(d->f1);\n");
  SET(field_extractor, "\"(f1):?s,\"\n");
  SET(field_extractor_arg, "&p->f1,\n");
  SET(field_injector, "\"(f1):s,\"\n");
  SET(field_injector_arg, "p->f1,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = p->f1;\n");
  SET(field_init, NULL);
  test_one();


  SET(spec, "{(name):|f1|, (type):{ (base):|char|, (dec):|*|, (converter):|snowflake|}}");
  SET(field_struct, "u64_snowflake_t f1;\n");
  SET(field_cleanup, "//p->f1 is a scalar\n");
  SET(field_extractor, "\"(f1):F,\"\n");
  SET(field_extractor_arg, "orka_strtoull, &p->f1,\n");
  SET(field_injector, "\"(f1):|F|,\"\n");
  SET(field_injector_arg, "orka_ulltostr, &p->f1,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = &p->f1;\n");
  SET(field_init, NULL);
  test_one();

  SET(spec, "{(name):|f1|, (type):{ (base):|char|, (dec):|*|, (converter):|iso8601|}}");
  SET(field_struct, "u64_unix_ms_t f1;\n");
  SET(field_cleanup, "//p->f1 is a scalar\n");
  SET(field_extractor, "\"(f1):F,\"\n");
  SET(field_extractor_arg, "orka_iso8601_to_unix_ms, &p->f1,\n");
  SET(field_injector, "\"(f1):|F|,\"\n");
  SET(field_injector_arg, "orka_unix_ms_to_iso8601, &p->f1,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = &p->f1;\n");
  SET(field_init, NULL);
  test_one();

  SET(spec, "{(name):|f1|, (type):{ (base):|char|, (dec):|*| }, (inject_if_not):|null|}");
  SET(field_struct, "char *f1;\n");
  SET(field_cleanup, "if (d->f1)\n    free(d->f1);\n");
  SET(field_extractor, "\"(f1):?s,\"\n");
  SET(field_extractor_arg, "&p->f1,\n");
  SET(field_injector, "\"(f1):s,\"\n");
  SET(field_injector_arg, "p->f1,\n");
  SET(field_inject_settings, "if (p->f1 != NULL)\n    p->__M.arg_switches[0] = p->f1;\n");
  SET(field_init, NULL);
  test_one();

  SET(spec, "{(name):|f1|, (type):{ (base):|int| }, (inject_if_not):10}");
  SET(field_struct, "int f1;\n");
  SET(field_cleanup, "//p->f1 is a scalar\n");
  SET(field_extractor, "\"(f1):d,\"\n");
  SET(field_extractor_arg, "&p->f1,\n");
  SET(field_injector, "\"(f1):d,\"\n");
  SET(field_injector_arg, "&p->f1,\n");
  SET(field_inject_settings, "if (p->f1 != 10)\n    p->__M.arg_switches[0] = &p->f1;\n");
  SET(field_init, NULL);
  test_one();


  SET(spec, "{(name):|f1|, (type):{ (base):|ja_str|, (dec):|ntl| }, (inject_if_not):null}");
  SET(field_struct, "ja_str **f1;\n");
  SET(field_cleanup, "if (d->f1)\n    ja_str_list_free(d->f1);\n");
  SET(field_extractor, "\"(f1):F,\"\n");
  SET(field_extractor_arg, "ja_str_list_from_json, &p->f1,\n");
  SET(field_injector, "\"(f1):F,\"\n");
  SET(field_injector_arg, "ja_str_list_to_json, p->f1,\n");
  SET(field_inject_settings, "if (p->f1 != NULL)\n    p->__M.arg_switches[0] = p->f1;\n");
  SET(field_init, NULL);
  test_one();

  SET(spec, "{(name):|f1|, (type):{ (base):|a::dati|, (dec):|*| }, (inject_if_not):null}");
  SET(field_struct, "a::dati *f1;\n");
  SET(field_cleanup, "if (d->f1)\n    a::dati_free(d->f1);\n");
  SET(field_extractor, "\"(f1):F,\"\n");
  SET(field_extractor_arg, "a::dati_from_json, p->f1,\n");
  SET(field_injector, "\"(f1):F,\"\n");
  SET(field_injector_arg, "a::dati_to_json, p->f1,\n");
  SET(field_inject_settings, "if (p->f1 != NULL)\n    p->__M.arg_switches[0] = p->f1;\n");
  SET(field_init, "p->f1 = a::dati_alloc();\n");
  test_one();

  SET(spec, "{(name):|f1|, (type):{ (base):|a::dati|, (dec):|*| }, (lazy_init):true }");
  SET(field_struct, "a::dati *f1;\n");
  SET(field_cleanup, "if (d->f1)\n    a::dati_free(d->f1);\n");
  SET(field_extractor, "\"(f1):F,\"\n");
  SET(field_extractor_arg, "a::dati_from_json, p->f1,\n");
  SET(field_injector, "\"(f1):F,\"\n");
  SET(field_injector_arg, "a::dati_to_json, p->f1,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = p->f1;\n");
  SET(field_init, NULL);
  test_one();

  SET(spec, "{(name):|f1|, (type):{ (base):|a_dati|, (dec):|*| }, (lazy_init):true }");
  SET(field_struct, "a_dati *f1;\n");
  SET(field_cleanup, "if (d->f1)\n    a_dati_free(d->f1);\n");
  SET(field_extractor, "\"(f1):F,\"\n");
  SET(field_extractor_arg, "a_dati_from_json, p->f1,\n");
  SET(field_injector, "\"(f1):F,\"\n");
  SET(field_injector_arg, "a_dati_to_json, p->f1,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = p->f1;\n");
  SET(field_init, NULL);
  test_one();

  SET(spec, "{(name):|f1|, (type):{ (base):|a_dati|, (dec):|ntl| }, (lazy_init):true }");
  SET(field_struct, "a_dati **f1;\n");
  SET(field_cleanup, "if (d->f1)\n    a_dati_list_free(d->f1);\n");
  SET(field_extractor, "\"(f1):F,\"\n");
  SET(field_extractor_arg, "a_dati_list_from_json, &p->f1,\n");
  SET(field_injector, "\"(f1):F,\"\n");
  SET(field_injector_arg, "a_dati_list_to_json, p->f1,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = p->f1;\n");
  SET(field_init, NULL);
  test_one();


  SET(spec, "{(name):|abc|, (type):{ (base):|int|, (int_alias):|abc_code| }}");
  SET(field_struct, "abc_code abc;\n");
  SET(field_cleanup, "//p->abc is a scalar\n");
  SET(field_extractor, "\"(abc):d,\"\n");
  SET(field_extractor_arg, "&p->abc,\n");
  SET(field_injector, "\"(abc):d,\"\n");
  SET(field_injector_arg, "&p->abc,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = &p->abc;\n");
  SET(field_init, NULL);
  test_one();


  SET(spec, "{(name):|abc|, (type):{ (base):|s_as_hex_uint|}}");
  SET(field_struct, "unsigned int abc;\n");
  SET(field_cleanup, "//p->abc is a scalar\n");
  SET(field_extractor, "\"(abc):s_as_hex_uint,\"\n");
  SET(field_extractor_arg, "&p->abc,\n");
  SET(field_injector, "\"(abc):s_as_hex_uint,\"\n");
  SET(field_injector_arg, "&p->abc,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = &p->abc;\n");
  SET(field_init, NULL);
  test_one();


  SET(spec, "{(name):|abc|, (type):{ (base):|s_as_hex_uint|, (int_alias):|enum flags|}}");
  SET(field_struct, "enum flags abc;\n");
  SET(field_cleanup, "//p->abc is a scalar\n");
  SET(field_extractor, "\"(abc):s_as_hex_uint,\"\n");
  SET(field_extractor_arg, "&p->abc,\n");
  SET(field_injector, "\"(abc):s_as_hex_uint,\"\n");
  SET(field_injector_arg, "&p->abc,\n");
  SET(field_inject_settings, "p->__M.arg_switches[0] = &p->abc;\n");
  SET(field_init, NULL);
  test_one();


  SET(spec, "{(name):|permissions|, (type):{ (base):|s_as_hex_uint|, (int_alias):|permissions::code|}, (inject_if_not):0}");
  SET(field_struct, "permissions::code permissions;\n");
  SET(field_cleanup, "//p->permissions is a scalar\n");
  SET(field_extractor, "\"(permissions):s_as_hex_uint,\"\n");
  SET(field_extractor_arg, "&p->permissions,\n");
  SET(field_injector, "\"(permissions):s_as_hex_uint,\"\n");
  SET(field_injector_arg, "&p->permissions,\n");
  SET(field_inject_settings, "if (p->permissions != 0)\n    p->__M.arg_switches[0] = &p->permissions;\n");
  SET(field_init, NULL);
  test_one();

  return 0;
}

