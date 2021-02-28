#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "json-actor.h"
#include "ntl.h"
#include "orka-utils.h"
#include "orka-debug.h"

/*
 *
 * Simple JSON/Query/Body <-> Struct Conversion Spec
 *
 * <definition> := { <namespace> <struct-list> <enum-list> }
 *
 * <namespace> : = "namespace" : [ <string>+ ]
 *
 * <struct> :=  "struct" : { "name": <string>, <fields> }
 *
 * <struct-list> := <struct> <struct-list> | <struct>
 *
 * <fields>  := "fields": [ <field-list> ]
 *
 * <field-list> := <field> <field-list> | <field>
 *
 * <field-info> := { <field-name> <c-name>? <field-type> <field-loc>? <comment>? }
 *
 * <field-name>  :=  "name" : <string>
 * <c-name>  := "c_name" : <string>
 * <comment> := "comment" : <string>
 *
 * <field-type>  :=  "type" : { "base":<string>,
 *                              "c_base"? : <string>,
 *                              "dec"?:("ntl"|"pointer"|"[<string>]"),
 *                              "converter"?:<string>
 *                            }
 *
 * <field-loc>   :=  "loc"  : ("json" | "query" | "body")
 *
 * <enum> := "enum" { "name": <string>, <enum-items> }
 *
 * <enum-items> = "items": [ <item>+ ]
 *
 * <item> := { "name" : <string>, "value": <integer>? }
 *
 */

struct converter {
  char *name;
  char *input_type;
  char *output_type;
  char *extractor;
  char *injector;
  char *extractor_addrof;
  char *injector_addrof;
  char *free;
};

static struct converter **converters = NULL;

static void
load_converter(char *pos, size_t size, void *p)
{
  struct converter *c = (struct converter *)p;
  json_extract(pos, size,
               "(name):?s,"
               "(input_type):?s,"
               "(output_type):?s,"
               "(extractor):?s,"
               "(injector):?s,"
               "(free):?s",
               &c->name,
               &c->input_type,
               &c->output_type,
               &c->extractor,
               &c->injector,
               &c->free);
}

static char * converter_file = NULL;


static void init_converters () {
  converters = ntl_calloc(2, sizeof(struct converter));
  converters[0]->name = "iso8601";
  converters[0]->input_type = "char*";
  converters[0]->output_type = "u64_unix_ms_t";
  converters[0]->free = NULL;
  converters[0]->extractor = "orka_iso8601_to_unix_ms";
  converters[0]->injector = "orka_unix_ms_to_iso8601";
  converters[0]->extractor_addrof = "&";
  converters[0]->injector_addrof = "&";

  converters[1]->name = "snowflake";
  converters[1]->input_type = "char*";
  converters[1]->output_type = "u64_snowflake_t";
  converters[1]->free = NULL;
  converters[1]->extractor = "orka_strtoull";
  converters[1]->injector = "orka_ulltostr";
  converters[1]->extractor_addrof = "&";
  converters[1]->injector_addrof = "&";

  for (int i = 0; converters[i]; i++)
    fprintf(stderr, "loading converters %s ...\n", converters[i]->name);

}
static void
load_converters(char *filename)
{
  size_t len = 0;
  char * data = orka_load_whole_file(filename, &len);
  converter_file = strdup(filename);

  struct ntl_deserializer d = {
    .ntl_recipient_p = (void ***)&converters,
    .init_elem = NULL,
    .elem_size = sizeof(struct converter),
    .elem_from_buf = load_converter
  };
  orka_str_to_ntl(data, len, &d);
}

static struct converter*
get_converter(char *name) {
  int i;
  for (i = 0; converters[i]; i++) {
    if (0 == strcmp(name, converters[i]->name)) {
      //fprintf(stderr, "%p\n", converters + i);
      return converters[i];
    }
  }

  ERR("converter '%s' is not defined in '%s'\n", name, converter_file);
  return NULL;
}


enum file_type {
  FILE_SINGLE_FILE = 0,
  FILE_DECLARATION,
  FILE_DEFINITION,
  FILE_HEADER,
  FILE_CODE
};
static enum file_type file_type = FILE_SINGLE_FILE;

static char*
get_file_suffix(enum file_type t)
{
  switch(t)
  {
    case FILE_SINGLE_FILE: return "cc";
    case FILE_DECLARATION: return "hh";
    case FILE_DEFINITION: return "cc";
    case FILE_HEADER: return "hh";
    case FILE_CODE: return "cc";
  }
}

enum dec_tag {
  DEC_NONE = 0, // this has to be zero as the absence means DEC_NONE
  DEC_POINTER = 1,
  DEC_ARRAY = 2,
  DEC_NTL
};

struct dec {
  enum dec_tag tag;
  char * value;
};

struct jc_type {
  char *base;
  char *c_base;  // use for enum type names that are represented as int
  struct dec dec;
  char * converter;
};

static void
print_type(FILE *fp, struct jc_type *p)
{
  fprintf(fp, "base:%s, dec:%d", p->base, p->dec.tag);
}


enum loc {
  LOC_IN_JSON = 0,  // this has to be zero as the absence means LOC_IN_JSON
  LOC_IN_QUERY,
  LOC_IN_BODY
};

struct jc_field {
  bool todo;
  char *name;
  char *c_name;
  struct jc_type type;
  enum loc loc;
  char * comment;
};

static void
print_field(FILE *fp, struct jc_field *p)
{
  if (p->todo)
    fprintf(fp, "//@todo name:%s\n", p->name);
  else {
    fprintf(fp, "name:%s, ", p->name);
    if (p->c_name)
      fprintf(fp, "c-name:%s, ", p->c_name);

    print_type(fp, &p->type);
    fprintf(fp, ", loc:%d\n", p->loc);
  }
}

struct jc_struct {
  char *name;
  struct jc_field **fields;
};

static void
print_struct(FILE *fp, struct jc_struct *p)
{
  fprintf(fp, "name %s\n", p->name);
  ntl_apply(fp, (void**)p->fields, print_field);
}

struct jc_item {
  char *name;
  int value;
  char *comment;
  bool todo;
  bool has_value;
};

static void
print_item(FILE *fp, struct jc_item *p, int i)
{
  fprintf(fp, "name %s: ", p->name);

  if (p->has_value)
    fprintf(fp, "%d", p->value);
  else
    fprintf(fp, "%d", i);
}

struct jc_enum {
  char *name;
  struct jc_item **items;
};

static void
print_enum(FILE *fp, struct jc_enum *p)
{
  fprintf(fp, "name %s\n", p->name);
  ntl_apply(fp, (void**)p->items, print_item);
}

struct jc_definition {
  char *spec_name;
  bool is_disabled;
  char *comment;
  char **namespace; // ntl
  struct jc_struct **structs; //ntl
  struct jc_enum **enums; //ntl
};

static char*
namespace_to_str(char **ns)
{
  char *buf; size_t len;
  FILE * fp = open_memstream(&buf, &len);
  for(int i = 0; ns && ns[i]; i++)
    fprintf(fp,"%s.", ns[i]);
  fclose(fp);
  return buf;
}

static void
print_definition(FILE *fp, struct jc_definition *p)
{
  fprintf(fp, "/*\n %s  */\n", p->comment);
  fprintf(fp, "namespace: ");
  ntl_apply(fp, (void**)p->namespace, fprintf);

  fprintf(fp, "\n");
  ntl_apply(fp, (void**)p->structs, print_struct);

  fprintf(fp, "\n");
  ntl_apply(fp, (void**)p->enums, print_enum);
}

static size_t
loc_from_json(char *json, size_t size, enum loc *p)
{
  if (4 == size && 0 == strncmp(json, "json", size)) {
    *p = LOC_IN_JSON;
  }
  else if (5 == size && 0 == strncmp(json, "query", size)) {
    *p = LOC_IN_QUERY;
  }
  else if (4 == size && 0 == strncmp(json, "body", size)) {
    *p = LOC_IN_BODY;
  }
  return 1;
}

static size_t
dec_from_json(char *json, size_t size, struct dec *p)
{
  if (1 == size && '*' == *json) {
    p->tag = DEC_POINTER;
  }
  else if (3 == size && 0 == strncmp(json, "ntl", size)) {
    p->tag = DEC_NTL;
  }
  else if (4 == size && 0 == strncmp(json, "none", size)) {
    p->tag = DEC_NONE;
  }
  else if (7 == size && 0 == strncmp(json, "pointer", size)) {
    p->tag = DEC_POINTER;
  }
  else if ('[' == *json) {
    p->tag = DEC_ARRAY;
    p->value = malloc(size+1);
    strncpy(p->value, json, size);
    p->value[size] = 0;
  }

  return 1;
}

static size_t
field_from_json(char *json, size_t size, void *x)
{
  struct jc_field *p = (struct jc_field *)x;
  size_t s = json_extract(json, size,
                          "(name):?s,"
                          "(todo):b,"
                          "(c_name):?s,"
                          "(type.base):?s,"
                          "(type.c_base):?s,"
                          "(type.dec):F,"
                          "(type.converter):?s,"
                          "(loc):F,"
                          "(comment):?s",
                          &p->name,
                          &p->todo,
                          &p->c_name,
                          &p->type.base,
                          &p->type.c_base,
                          dec_from_json, &p->type.dec,
                          &p->type.converter,
                          loc_from_json, &p->loc,
                          &p->comment);
  return s;
}

static size_t
struct_from_json(char *json, size_t size, struct jc_struct *s)
{
  struct ntl_deserializer d = {
    .elem_size = sizeof(struct jc_field),
    .elem_from_buf = field_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)&(s->fields)
  };

  size_t ret = json_extract(json, size,
                            "(name):?s"
                            "(fields):F",
                            &s->name,
                            orka_str_to_ntl, &d);
  return ret;
}

static size_t
item_from_json(char *json, size_t size, void *x)
{
  struct jc_item *p = (struct jc_item *)x;
  void * defined[4] = {0};

  size_t s = json_extract(json, size,
                          "(name):?s,"
                          "(todo):b,"
                          "(value):d,"
                          "(comment):?s"
                          "@record_defined",
                          &p->name,
                          &p->todo,
                          &p->value,
                          &p->comment,
                          defined, sizeof(defined));

  for (int i = 0; i < 4; i++) {
    if (defined[i] == &p->value)
      p->has_value = true;
  }
  return s;
}

static size_t
enum_from_json(char * json, size_t size, struct jc_enum *e)
{
  struct ntl_deserializer d = {
    .elem_size = sizeof(struct jc_item),
    .elem_from_buf = item_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)&(e->items)
  };

  size_t ret = json_extract(json, size,
                            "(name):?s"
                            "(items):F",
                            &e->name,
                            orka_str_to_ntl, &d);
  return ret;
}

static void gen_enum(FILE *fp, struct jc_enum *e)
{
  char *t = e->name;
  fprintf(fp, "\n\n");
  fprintf(fp, "enum %s {\n", t);
  int i = 0, prev_value;

  for (i = 0; e->items[i]; i++) {
    struct jc_item * item = e->items[i];
    if (item->todo) {
      fprintf(fp, "//@todo %s %s\n", item->name, item->comment);
    }
    else {
      fprintf(fp, "  %s", item->name);
      if (item->has_value) {
        fprintf(fp, " = %d,\n", item->value);
        prev_value = item->value;
      }
      else {
        fprintf(fp, " = %d,\n", prev_value + 1);
        prev_value ++;
      }
    }
  }
  fprintf(fp, "};\n");
}

static size_t
name_from_json(char *json, size_t size, char *p)
{
  memcpy(p, json, size);
  p[size] = 0;
  return size;
}

static size_t
definition_from_json(char *json, size_t size, struct jc_definition *s)
{
  struct ntl_deserializer d1 = {
    .elem_size = 256,
    .elem_from_buf = name_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)&(s->namespace)
  };

  struct ntl_deserializer d2 = {
    .elem_size = sizeof(struct jc_struct),
    .elem_from_buf = struct_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)&(s->structs)
  };

  struct ntl_deserializer d3 = {
    .elem_size = sizeof(struct jc_enum),
    .elem_from_buf = enum_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)&(s->enums)
  };

  size_t ret = json_extract(json, size,
                            "(disabled):b"
                            "(comment):?s"
                            "(namespace):F"
                            "(structs):F"
                            "(enums):F",
                            &s->is_disabled,
                            &s->comment,
                            orka_str_to_ntl, &d1,
                            orka_str_to_ntl, &d2,
                            orka_str_to_ntl, &d3);
  return ret;
}

static size_t
definition_list_from_json(char *json, size_t size, struct jc_definition ***s)
{
  struct ntl_deserializer d = {
    .elem_size = sizeof(struct jc_definition),
    .elem_from_buf = definition_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)s
  };
  return orka_str_to_ntl(json, size, &d);
}

static size_t
spec_from_json(char *json, size_t size, struct jc_definition ***s)
{
  char *const xend_pos = json + size;

  while (isspace(*json)) {
    json ++;
  }
  if ('[' == *json)
    definition_list_from_json(json, xend_pos - json, s);
  else {
    *s = ntl_calloc(1, sizeof(struct jc_definition));
    definition_from_json(json, xend_pos - json, (*s)[0]);
  }
}


struct action {
  bool todo;
  char *c_name;
  char *c_type;
  char *pre_dec;
  char *post_dec;
  char *extract_arg_decor;
  char *inject_arg_decor;
  char *extractor;
  char *injector;
  char *free;
  char *alloc;
  bool is_user_def;
  bool is_caller_alloc;
};

static int to_builtin_action(struct jc_field *f, struct action *act)
{
  if (strcmp(f->type.base, "int") == 0) {
    act->extractor = "d";
    act->injector = "d";
    act->c_type = f->type.c_base ? f->type.c_base : "int";
  }
  else if (strcmp(f->type.base, "s_as_u64") == 0) {
    act->extractor = "s_as_u64";
    act->injector = "s_as_u64";
    act->c_type = "uint64_t";
  }
  else if (strcmp(f->type.base, "s_as_i64") == 0) {
    act->extractor = "s_as_i64";
    act->injector = "s_as_i64";
    act->c_type = "uint64_t";
  }
  else if (strcmp(f->type.base, "int64_t") == 0) {
    act->extractor = "i64";
    act->injector = "i64";
  }
  else if (strcmp(f->type.base, "bool") == 0) {
    act->extractor = "b";
    act->injector = "b";
    act->c_type = "bool";
  }
  else {
    //fprintf(stderr, "unknown %s\n", f->type.base);
    return 0;
  }
  return 1;
}

static void
to_action(struct jc_field *f, struct action *act)
{
  if (f->todo) {
    act->todo = true;
    return;
  }

  act->post_dec = "";
  act->pre_dec = "";
  if (f->type.c_base)
    act->c_type = f->type.c_base;
  else
    act->c_type = f->type.base;

  act->c_name = f->c_name ? f->c_name : f->name;

  switch(f->type.dec.tag)
  {
    case DEC_POINTER:
      if (strcmp(f->type.base, "char") == 0) {
        act->injector = "s";
        act->extractor = "?s";
        act->extract_arg_decor = "&";
        act->inject_arg_decor = "&";
        act->post_dec = "";
        act->pre_dec = "*";
        act->free = "free";
        act->c_type = "char";
        if (f->type.converter) {
          struct converter *c = get_converter(f->type.converter);
          act->is_user_def = true;
          act->extractor = c->extractor;
          act->injector = c->injector;
          act->free = c->free;
          act->extract_arg_decor = c->extractor_addrof;
          act->inject_arg_decor = c->injector_addrof;
          if (0 == strcmp(c->input_type, "char*")) {
            act->c_type = c->output_type;
            act->post_dec = "";
            act->pre_dec = "";
          }
          else {
            ERR("type mismatch %s\n", c->input_type);
          }
        }
        return;
      } else {
        char *tok = strrchr(f->type.base, ':');
        if (tok != NULL) {
          asprintf(&act->injector, "%s_to_json", f->type.base);
          asprintf(&act->extractor, "%s_from_json", f->type.base);
          asprintf(&act->alloc, "%s_alloc", f->type.base);
          asprintf(&act->free, "%s_free", f->type.base);
          act->extract_arg_decor = "";
          act->inject_arg_decor = "";
          act->post_dec = "";
          act->pre_dec = "*";
          act->is_user_def = true;
          act->is_caller_alloc = false;
        }
      }
      break;
    case DEC_NONE:
      act->extract_arg_decor = "&";
      act->inject_arg_decor = "&";
      if (!to_builtin_action(f, act)) {
        ERR("unknown %s\n", f->type.base);
      }
      break;
    case DEC_NTL:
      act->extract_arg_decor = "&";
      act->inject_arg_decor = "";
      act->pre_dec = "**";
      act->is_user_def = true;
      act->is_caller_alloc = true;
      if (to_builtin_action(f, act)) {
        act->free = "free";
        asprintf(&act->extractor, "%s_list_from_json", f->type.base);
        asprintf(&act->injector, "%s_list_to_json", f->type.base);
      } else {
        asprintf(&act->extractor, "%s_list_from_json", f->type.base);
        asprintf(&act->injector, "%s_list_to_json", f->type.base);
        asprintf(&act->free, "%s_list_free", f->type.base);
      }
      break;
    case DEC_ARRAY:
      if (strcmp(f->type.base, "char") == 0) {
        act->injector = "s";
        act->extractor = "s";
        act->extract_arg_decor = "";
        act->inject_arg_decor = "";
        act->post_dec = f->type.dec.value;
        act->pre_dec = "";
        act->free = NULL;
        act->c_type = "char";
        return;
      } else {
        ERR("array only support char\n");
      }
  }
}

static void
gen_init (FILE *fp, struct jc_struct *s)
{
  char *t = s->name;

  fprintf(fp, "void %s_init(struct %s *p) {\n", t, t);
  fprintf(fp, "  memset(p, 0, sizeof(struct %s));\n", t);
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    struct action act = { 0 };
    to_action(f, &act);

    if (act.todo) continue;

    if (act.alloc)
      fprintf (fp, "  p->%s = %s();\n", act.c_name, act.alloc);
  }
  fprintf(fp, "}\n");
}

static void
gen_default(FILE *fp, struct jc_struct * s)
{
  char * type = s->name;

  gen_init(fp, s);
  fprintf(fp, "struct %s* %s_alloc() {\n", type, type);
  fprintf(fp, "  struct %s *p= (struct %s*)malloc(sizeof(struct %s));\n",
          type, type, type);
  fprintf(fp, "  %s_init(p);\n", type);
  fprintf(fp, "  return p;\n");
  fprintf(fp, "}\n\n");

  fprintf(fp, "void %s_free(struct %s *p) {\n", type, type);
  fprintf(fp, "  %s_cleanup(p);\n", type);
  fprintf(fp, "  free(p);\n");
  fprintf(fp, "}\n\n");

  fprintf(fp, "void %s_list_free(struct %s **p) {\n", type, type);
  fprintf(fp, "  ntl_free((void**)p, (vfvp)%s_cleanup);\n", type);
  fprintf(fp, "}\n\n");

  fprintf(fp, "void %s_list_from_json(char *str, size_t len, struct %s ***p)\n",
          type, type);
  fprintf(fp, "{\n");
  fprintf(fp, "  struct ntl_deserializer d;\n");
  fprintf(fp, "  memset(&d, 0, sizeof(d));\n");
  fprintf(fp, "  d.elem_size = sizeof(struct %s);\n", type);
  fprintf(fp, "  d.init_elem = %s_init_v;\n", type);
  fprintf(fp, "  d.elem_from_buf = %s_from_json_v;\n", type);
  fprintf(fp, "  d.ntl_recipient_p= (void***)p;\n");
  fprintf(fp, "  orka_str_to_ntl(str, len, &d);\n");
  fprintf(fp, "}\n\n");

  fprintf(fp, "size_t %s_list_to_json(char *str, size_t len, struct %s **p)\n",
          type, type);
  fprintf(fp, "{\n");
  fprintf(fp, "  return ntl_to_buf(str, len, (void **)p, NULL, %s_to_json_v);\n",
          type);
  fprintf(fp, "}\n");
}

static void gen_cleanup(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  fprintf(fp, "void %s_cleanup(struct %s *d) {\n", t, t);
  for (int i = 0; s->fields[i]; i++)
  {
    struct jc_field *f = s->fields[i];
    struct action act = {0};
    to_action(f, &act);

    if (act.todo) continue;

    if (act.free) {
      fprintf(fp,
              "  if (d->%s)\n"
              "    %s(d->%s);\n",
              act.c_name, act.free, act.c_name);
    }
  }
  fprintf(fp, "}\n");
}

static void gen_field(FILE *fp, struct jc_field *f)
{
  struct action act = {0};
  to_action(f, &act);
  if (act.todo) {
    fprintf(fp, "  //@todo %s %s;\n", f->name, f->comment);
  }
  else if (f->comment)
    fprintf(fp, "  %s %s%s%s; // %s\n",
            act.c_type, act.pre_dec, act.c_name, act.post_dec, f->comment);
  else
    fprintf(fp, "  %s %s%s%s;\n",
            act.c_type, act.pre_dec, act.c_name, act.post_dec);
}

static void gen_from_json(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  fprintf(fp, "void %s_from_json(char *json, size_t len, struct %s *p)\n",
          t, t);
  fprintf(fp, "{\n");
  fprintf(fp, "  static size_t ret=0; // used for debugging\n");
  fprintf(fp, "  size_t r=0;\n");
  fprintf(fp, "  r=json_extract(json, len, \n");
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field *f= s->fields[i];
    struct action act = {0};
    to_action(f, &act);
    if (act.todo) continue;

    if (act.is_user_def)
      fprintf(fp, "                \"(%s):F,\"\n", act.c_name);
    else
      fprintf(fp, "                \"(%s):%s,\"\n", act.c_name, act.extractor);
  }
  fprintf(fp, "                \"@arg_switches:b\",\n");

  for (int i = 0; s->fields[i]; i++) {
    struct jc_field *f= s->fields[i];
    struct action act = {0};
    to_action(f, &act);
    if (act.todo) continue;

    if (act.is_user_def) {
      if (act.is_caller_alloc)
        fprintf(fp, "                %s, &p->%s,\n",
                act.extractor, act.c_name);
      else
        fprintf(fp, "                %s, %sp->%s,\n",
                act.extractor, act.extract_arg_decor, act.c_name);
    }
    else
      fprintf(fp, "                %sp->%s,\n",
              act.extract_arg_decor, act.c_name);
  }
  fprintf(fp, "                p->__metadata.arg_switches,"
    " sizeof(p->__metadata.arg_switches),"
    " &p->__metadata.enable_arg_switches,\n");
  fprintf(fp, "                p->__metadata.record_defined,"
    " sizeof(p->__metadata.record_defined));\n");
  fprintf(fp, "  ret = r;\n");
  fprintf(fp, "}\n");
}

static void gen_to_json(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  fprintf(fp, "size_t %s_to_json(char *json, size_t len, struct %s *p)\n",
          t, t);
  fprintf(fp, "{\n");
  fprintf(fp, "  size_t r;\n");
  fprintf(fp, "  r=json_inject(json, len, \n");

  for (int i = 0; s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    struct action act = {0};
    to_action(f, &act);
    if (act.todo) continue;

    if (act.is_user_def)
      fprintf(fp, "                \"(%s):F,\"\n", act.c_name);
    else
      fprintf(fp, "                \"(%s):%s,\"\n", act.c_name, act.injector);
  }
  fprintf(fp, "                \"@arg_switches:b\",\n");

  for (int i = 0; s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    struct action act = {0};
    to_action(f, &act);
    if (act.todo) continue;

    if (act.is_user_def)
      fprintf(fp, "                %s, %sp->%s,\n",
              act.injector, act.inject_arg_decor, act.c_name);
    else
      fprintf(fp, "                %sp->%s,\n",
              act.inject_arg_decor, act.c_name);
  }
  fprintf(fp, "                p->__metadata.arg_switches, "
    "sizeof(p->__metadata.arg_switches),"
    " &p->__metadata.enable_arg_switches);\n");
  fprintf(fp, "  return r;\n");
  fprintf(fp, "}\n");
}

static void gen_to_query(FILE *fp, struct jc_struct *s)
{
  return;

  char *t = s->name;
  bool has_query = false;
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    if (f->loc != LOC_IN_QUERY)
      continue;
    has_query = true;
  }


  fprintf(fp, "size_t %s_to_query(char *json, size_t len, struct %s* p)\n",
          t, t);
  fprintf(fp, "{\n");
  fprintf(fp, "  size_t r = 0;\n");
  if (!has_query) {
    fprintf(fp,  "  return r;\n");
    fprintf(fp, "}\n");
    return;
  }

  fprintf(fp, "  r = query_inject(json, len, \n");

  
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    if (f->loc != LOC_IN_QUERY)
      continue;

    struct action act = {0};
    to_action(f, &act);
    if (act.todo) continue;
    fprintf(fp, "                \"(%s):%s\"\n", f->name, act.injector);
  }
  fprintf(fp, "                \"@arg_switches:b\",\n");

  for (int i = 0; s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    if (f->loc != LOC_IN_QUERY)
      continue;

    struct action act = {0};
    to_action(f, &act);
    if (act.todo) continue;

    fprintf(fp, "                %sp->%s,\n", act.inject_arg_decor, f->name);
  }
  fprintf(fp, "                p->__metadata.arg_switches,"
    " sizeof(p->__metadata.arg_switches),"
    " &p->__metadata.enable_arg_switches);\n");
  fprintf(fp,  "  return r;\n");
  fprintf(fp, "}\n");
}

static void gen_def(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  fprintf(fp, "\n\n");
  fprintf(fp, "struct %s {\n", t);
  int i = 0;
  for (i = 0; s->fields[i]; i++)
    gen_field(fp, s->fields[i]);
  fprintf(fp, "  struct {\n");
  fprintf(fp, "    bool enable_arg_switches;\n");
  fprintf(fp, "    bool enable_record_defined;\n");
  fprintf(fp, "    bool enable_record_null;\n");
  fprintf(fp, "    void *arg_switches[%d];\n", i);
  fprintf(fp, "    void *record_defined[%d];\n", i);
  fprintf(fp, "    void *record_null[%d];\n", i);
  fprintf(fp, "  } __metadata;\n");
  fprintf(fp, "};\n");
}

static void gen_wrapper(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  fprintf(fp, "void %s_cleanup_v(void *p) {\n"
              "  %s_cleanup((struct %s *)p);\n"
              "}\n\n", t, t, t);

  fprintf(fp, "void %s_init_v(void *p) {\n"
              "  %s_init((struct %s *)p);\n"
              "}\n\n", t, t, t);


  fprintf(fp, "void %s_free_v(void *p) {\n"
              " %s_free((struct %s *)p);\n"
              "};\n\n", t, t, t);

  fprintf(fp, "void %s_from_json_v(char *json, size_t len, void *p) {\n"
              " %s_from_json(json, len, (struct %s*)p);\n"
              "}\n\n", t, t, t);

  fprintf(fp, "size_t %s_to_json_v(char *json, size_t len, void *p) {\n"
              "  return %s_to_json(json, len, (struct %s*)p);\n"
              "}\n\n", t, t, t);

#if 0
  fprintf(fp, "size_t %s_to_query_v(char *json, size_t len, void *p) {\n"
              "  return %s_to_query(json, len, (struct %s*)p);\n"
              "}\n\n", t, t, t);
#endif

  fprintf(fp, "void %s_list_free_v(void **p) {\n"
              "  %s_list_free((struct %s**)p);\n"
              "}\n\n", t, t, t);

  fprintf(fp, "void %s_list_from_json_v(char *str, size_t len, void *p) {\n"
              "  %s_list_from_json(str, len, (struct %s ***)p);\n"
              "}\n\n", t, t, t);

  fprintf(fp, "size_t %s_list_to_json_v(char *str, size_t len, void *p){\n"
              "  return %s_list_to_json(str, len, (struct %s **)p);\n"
              "}\n\n", t, t, t);
}

static void gen_forward_declare(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  fprintf(fp, "void %s_cleanup_v(void *p);\n", t);
  fprintf(fp, "void %s_cleanup(struct %s *p);\n", t, t);

  fprintf(fp, "void %s_init_v(void *p);\n", t);
  fprintf(fp, "void %s_init(struct %s *p);\n", t, t);

  fprintf(fp, "struct %s * %s_alloc();\n", t, t);

  fprintf(fp, "void %s_free_v(void *p);\n", t);
  fprintf(fp, "void %s_free(struct %s *p);\n", t, t);

  fprintf(fp, "void %s_from_json_v(char *json, size_t len, void *p);\n", t);
  fprintf(fp, "void %s_from_json(char *json, size_t len, struct %s *p);\n",
          t, t);

  fprintf(fp, "size_t %s_to_json_v(char *json, size_t len, void *p);\n", t);
  fprintf(fp, "size_t %s_to_json(char *json, size_t len, struct %s *p);\n",
          t, t);

  fprintf(fp, "size_t %s_to_query_v(char *json, size_t len, void *p);\n", t);
  fprintf(fp, "size_t %s_to_query(char *json, size_t len, struct %s *p);\n",
          t, t);

  fprintf(fp, "void %s_list_free_v(void **p);\n", t);
  fprintf(fp, "void %s_list_free(struct %s **p);\n", t, t);

  fprintf(fp, "void %s_list_from_json_v(char *str, size_t len, void *p);\n", t);
  fprintf(fp, "void %s_list_from_json(char *str, size_t len, struct %s ***p);\n",
          t, t);

  fprintf(fp, "size_t %s_list_to_json_v(char *str, size_t len, void *p);\n", t);
  fprintf(fp, "size_t %s_list_to_json(char *str, size_t len, struct %s **p);\n",
          t,t);
}

static void gen_typedef (FILE * fp, struct jc_struct *s)
{
#if 1
  fprintf(fp, "typedef void (*vfvp)(void *);\n");
  fprintf(fp, "typedef void (*vfcpsvp)(char *, size_t, void *);\n");
  fprintf(fp, "typedef size_t (*sfcpsvp)(char *, size_t, void *);\n");
#endif
}

static void gen_struct (FILE * fp, struct jc_struct * s)
{
  //fprintf (fp, "/* comment out to avoid redefinition warning\n");

  if (file_type == FILE_HEADER || file_type == FILE_DECLARATION) {
    gen_def(fp, s);
    //fprintf (fp, "\n*/\n");
    gen_forward_declare(fp, s);
  }
  else if (file_type == FILE_SINGLE_FILE) {
    gen_def(fp, s);
    //fprintf (fp, "\n*/\n");
    gen_forward_declare(fp, s);

    gen_from_json(fp, s);
    fprintf(fp, "\n");
    gen_to_json(fp, s);
    fprintf(fp, "\n");
    gen_to_query(fp, s);
    fprintf(fp, "\n");

    // boilerplate
    gen_typedef(fp, s);
    gen_wrapper(fp, s);
    gen_cleanup(fp, s);
    fprintf(fp, "\n");
    gen_default(fp, s);
    fprintf(fp, "\n");
  } else {
    gen_from_json(fp, s);
    fprintf(fp, "\n");
    gen_to_json(fp, s);
    fprintf(fp, "\n");
    gen_to_query(fp, s);
    fprintf(fp, "\n");

    // boilerplate
    gen_typedef(fp, s);
    gen_wrapper(fp, s);
    fprintf(fp, "\n");
    gen_cleanup(fp, s);
    fprintf(fp, "\n");
    gen_default(fp, s);
    fprintf(fp, "\n");
  }
}


static void gen_open_namespace(FILE *fp, char **p)
{
  for (int i = 0; p[i]; i++) {
    fprintf(fp, "namespace %s {\n", p[i]);
  }
}

static void gen_close_namespace(FILE *fp, char **p)
{
  int n = ntl_length((void**)p);
  for (int i = n-1; i >= 0; i--) {
    fprintf(fp, "} // namespace %s\n", p[i]);
  }
}

static void gen_definition(FILE *fp, enum file_type type,
                           struct jc_definition *d)
{
  if (d->is_disabled)
    return;
  init_converters(); // @todo move it out of this function.
  file_type = type;
  if (d->spec_name)
    fprintf(fp, "/* This file is generated from %s, Please don't edit it. */\n",
            d->spec_name);

  if (type == FILE_SINGLE_FILE || type == FILE_CODE)
    fprintf(fp, "#include \"specs.h\"\n");

  fprintf(fp, "/*\n%s\n*/\n", d->comment);
  if (type != FILE_DECLARATION && type != FILE_DEFINITION)
    gen_open_namespace(fp, d->namespace);

  ntl_apply(fp, (void**)d->enums, gen_enum);
  ntl_apply(fp, (void**)d->structs, gen_struct);

  if (type != FILE_DECLARATION && type != FILE_DEFINITION)
    gen_close_namespace(fp, d->namespace);
  return;
}

static void
gen_definition_list(
  char *folder,
  enum file_type type,
  struct jc_definition **ntl)
{
  char * fname = NULL;
  for (int i = 0; ntl && ntl[i]; i++) {
    struct jc_definition *d = ntl[i];
    char * f = namespace_to_str(d->namespace);
    asprintf(&fname, "%s/%s%s", folder, f, get_file_suffix(type));
    FILE *fp = fopen(fname, "w");
    gen_definition(fp, type, d);
    fclose(fp);
  }
}