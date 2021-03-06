#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "json-actor.h"
#include "ntl.h"
#include "orka-utils.h"
#include "orka-debug.h"

/*
 *
 * Simple JSON/Query/Body <-> Struct Conversion Spec
 *
 * <definition> := {
 *      "disable"?:<bool>,
 *      "title"?:<string>,
 *      "comment"?:<string>,
 *      "namespace"?: [<string>+],
 *      "defs": [ <def-list> ]
 *      }
 *
 * <def> := "title"?:<string>,
 *          "comment"?:<string>,
 *          "namespace"?:[<string>+],
 *          (<struct> | <enum>)
 *
 * <struct> :=  "struct" : <string>, "fields": [ <field>+ ]
 *
 *
 * <field> := { "name"?:<string>,
 *              "json_key"?:<string>,
 *              (<field-type>| "copy_json_value":true)
 *              <field-loc>?
 *              "comment"?:<string>
 *              "lazy_load"?:<bool>
 *              "lazy_init"?:<bool>
 *            }
 *
 *
 * <field-type>  :=  "type" : { "base":<string>,
 *                              "int_alias"? : <string>,
 *                              "dec"?:("ntl"|"*"|"[<string>]"),
 *                              "converter"?:<string>,
 *                              "inject_if_not"?:<string>|<bool>|<number>|null,
 *                            }
 *
 *
 * <field-loc>   :=  "loc"  : ("json" | "query" | "body" | "url)
 *
 *
 * <enum> := "enum" :<string>, "items": [ <items>+ ]
 * <item> := { "name" : <string>, "value": <integer>? }
 *
 */

static void
emit_alias_disabled(FILE *fp, char *f)
{
  /*
  fprintf(fp, "__typeof(%s_disabled) %s __attribute__((weak, alias(\"%s_disabled\")));\n",
          f, f, f);
          */
}

static char * spec_name = "";
static struct sized_buffer spec_buffer = {0};

static void
adjust_lnc(char * json, struct line_and_column *out_lnc)
{
  if (spec_buffer.start) {
    struct line_and_column lnc = {0};
    addr_to_lnc (spec_buffer.start, spec_buffer.size, json, &lnc);
    out_lnc->line += (lnc.line + 1);
    out_lnc->column += lnc.column;
  }
}

struct converter {
  char *name;
  char *input_type;
  char *output_type;
  char *extractor;
  char *injector;
  char *extractor_addrof;
  char *injector_addrof;
  char *free;
  char *converted_builtin_type;
};

static struct converter **converters = NULL;

static void load_converter(char *pos, size_t size, void *p)
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
  converters[0]->converted_builtin_type = "uint64_t";

  converters[1]->name = "snowflake";
  converters[1]->input_type = "char*";
  converters[1]->output_type = "u64_snowflake_t";
  converters[1]->free = NULL;
  converters[1]->extractor = "orka_strtoull";
  converters[1]->injector = "orka_ulltostr";
  converters[1]->extractor_addrof = "&";
  converters[1]->injector_addrof = "&";
  converters[1]->converted_builtin_type = "uint64_t";

  for (int i = 0; converters[i]; i++)
    fprintf(stderr, "adding converters %s ...\n", converters[i]->name);

}
static void load_converters(char *filename)
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

static struct converter* get_converter(char *name) {
  for (int i = 0; converters[i]; i++) {
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

static char* get_file_suffix(enum file_type t)
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

enum decor_tag {
  DEC_NONE = 0, // this has to be zero as the absence means DEC_NONE
  DEC_POINTER = 1,
  DEC_ARRAY = 2,
  DEC_NTL
};

struct decor {
  enum decor_tag tag;
  char * value;
};

struct jc_type {
  char *base;
  char *int_alias; // use for enum type names that are represented as int
  char *json_type; // string, number, bool, object, array
  struct decor decor;
  char * converter;
  bool nullable;
};

static void
print_type(FILE *fp, struct jc_type *p)
{
  fprintf(fp, "base:%s, dec:%d", p->base, p->decor.tag);
}


enum loc {
  LOC_IN_JSON = 0,  // this has to be zero as the absence means LOC_IN_JSON
  LOC_IN_QUERY,
  LOC_IN_BODY
};

enum inject_opcode {
  INJECT_ALWAYS = 0,
  INJECT_IF_NOT_NULL,
  INJECT_IF_NOT_EMPTY_STR,
  INJECT_IF_NOT_STR,
  INJECT_IF_NOT_BOOL,
  INJECT_IF_NOT_INT,
  INJECT_IF_NOT_DOUBLE
};

struct inject_condition {
  enum inject_opcode opcode;
  union {
    uint64_t ival;
    double dval;
    char * sval;
  } _;
  char * string;
};


struct jc_field {
  struct line_and_column lnc;
  bool todo;
  char *name;
  //char *c_name;
  char *json_key;
  struct jc_type type;
  enum loc loc;
  struct inject_condition inject_condition;
  char * comment;
  bool lazy_init;
  char spec[512];
  bool option;
  bool copy_json_value;
};

static void
print_field(FILE *fp, struct jc_field *p)
{
  if (p->todo)
    fprintf(fp, "//@todo name:%s\n", p->name);
  else {
    fprintf(fp, "name:%s, ", p->name);
    if (p->json_key)
      fprintf(fp, "json_key:%s, ", p->json_key);

    print_type(fp, &p->type);
    fprintf(fp, ", loc:%d\n", p->loc);
  }
}

#define DEF_HEADER \
  char **disable_methods; \
  struct line_and_column disable_methods_lnc; \
  char *title; \
  char *comment; \
  char **namespace; \
  char *name; \
  struct line_and_column name_lnc;


struct jc_struct {
  DEF_HEADER
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
  DEF_HEADER
  struct jc_item **items;
};

struct jc_def {
  DEF_HEADER
  union {
    struct jc_field **fields;
    struct jc_item **items;
  } list;
  bool is_struct;
};

static void
print_enum(FILE *fp, struct jc_enum *p)
{
  fprintf(fp, "name %s\n", p->name);
  ntl_apply(fp, (void**)p->items, print_item);
}

static void
print_def(FILE *fp, struct jc_def *d)
{
  if (d->is_struct)
    print_struct(fp, (struct jc_struct *)d);
  else
    print_enum(fp, (struct jc_enum *)d);
};

static void
emit_field_spec(void *cxt, FILE *fp, struct jc_field *f)
{
  fprintf(fp, "  /* %s:%d:%d\n", spec_name, f->lnc.line, f->lnc.column);
  fprintf(fp, "     '%s'\n", f->spec);
  fprintf(fp, "  */\n");
}

struct jc_definition {
  char *spec_name;
  bool is_disabled;
  char *comment;
  char **namespace; // ntl
  struct jc_def **defs; //ntl
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
  ntl_apply(fp, (void**)p->defs, print_def);
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
decor_from_json(char *json, size_t size, struct decor *p)
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
  bool has_inject_if_not = false;
  struct sized_buffer t = {0};

  bool copy_json_value = false;

  size_t s = json_extract(json, size,
                          "(name):?s,"
                          "(name):lnc,"
                          "(todo):b,"
                          "(json_key):?s,"
                          // "(type):?s,"
                          "(type.base):?s,"
                          "(type.int_alias):?s,"
                          "(type.json_type):?s,"
                          "(type.dec):F,"
                          "(type.converter):?s,"
                          "(type.nullable):b,"
                          "(option):b,"
                          "(inject_if_not):key,"
                          "(inject_if_not):T,"
                          "(lazy_init):b,"
                          "(loc):F,"
                          "(comment):?s",
                          &p->name,
                          &p->lnc,
                          &p->todo,
                          &p->json_key,
                          //&copy_json_value,
                          &p->type.base,
                          &p->type.int_alias,
                          &p->type.json_type,
                          decor_from_json, &p->type.decor,
                          &p->type.converter,
                          &p->type.nullable,
                          &p->option,
                          &has_inject_if_not,
                          &t,
                          &p->lazy_init,
                          loc_from_json, &p->loc,
                          &p->comment);

  snprintf(p->spec, sizeof(p->spec), "%.*s", (int)size, json);
  adjust_lnc(json, &p->lnc);

  if (has_inject_if_not) {
    if (t.size == 0) {
      p->inject_condition.opcode = INJECT_IF_NOT_EMPTY_STR;
    }
    else if (strlen("null") == t.size
             && strncmp("null", t.start, t.size) == 0) {
      p->inject_condition.opcode = INJECT_IF_NOT_NULL;
    }
    else {
      // we will convert this to actual type later
      p->inject_condition.opcode = INJECT_IF_NOT_STR;
      char * str = malloc(t.size + 1);
      strncpy(str, t.start, t.size);
      str[t.size] = 0;
      p->inject_condition.string = str;
    }
  }
  return s;
}

static size_t
name_from_json(char *json, size_t size, char *p)
{
  memcpy(p, json, size);
  p[size] = 0;
  return size;
}

static size_t
struct_from_json(char *json, size_t size, struct jc_struct *s)
{
  struct ntl_deserializer d0 = {
    .elem_size = 256,
    .elem_from_buf = name_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)&(s->namespace)
  };

  struct ntl_deserializer dx = {
    .elem_size = 256,
    .elem_from_buf = name_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)&(s->disable_methods)
  };

  struct ntl_deserializer d1 = {
    .elem_size = sizeof(struct jc_field),
    .elem_from_buf = field_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)&(s->fields)
  };

  size_t ret = json_extract(json, size,
                            "(comment):?s,"
                            "(title):?s,"
                            "(namespace):F,"
                            "(struct):?s,"
                            "(struct):lnc,"
                            "(disable_methods):F,"
                            "(disable_methods):lnc,"
                            "(fields):F",
                            &s->comment,
                            &s->title,
                            orka_str_to_ntl, &d0,
                            &s->name,
                            &s->name_lnc,
                            orka_str_to_ntl, &dx,
                            &s->disable_methods_lnc,
                            orka_str_to_ntl, &d1);

  adjust_lnc(json, &s->disable_methods_lnc);
  adjust_lnc(json, &s->name_lnc);
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
  struct ntl_deserializer d0 = {
    .elem_size = 256,
    .elem_from_buf = name_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)&(e->namespace)
  };

  struct ntl_deserializer d1 = {
    .elem_size = sizeof(struct jc_item),
    .elem_from_buf = item_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)&(e->items)
  };

  size_t ret = json_extract(json, size,
                            "(namespace):F"
                            "(enum):?s"
                            "(items):F",
                            orka_str_to_ntl, &d0,
                            &e->name,
                            orka_str_to_ntl, &d1);
  return ret;
}

static size_t
def_from_json(char *json, size_t size, struct jc_def *def)
{
  bool is_struct = false, is_enum = false;
  char *s_name = NULL, *e_name = NULL;
  json_extract(json, size,
               "(struct):key,"
               "(enum):key,"
               "(struct):?s,"
               "(enum):?s",
               &is_struct,
               &is_enum,
               &s_name, &e_name);

  if (is_struct) {
    def->is_struct = true;
    def->name = s_name;
    return struct_from_json(json, size, (struct jc_struct *)def);
  }
  else if (is_enum) {
    def->is_struct = false;
    def->name = e_name;
    return enum_from_json(json, size, (struct jc_enum *)def);
  }
  else {
    ERR("missing 'struct' or 'enum' in '%.*s'", size, json);
    return 0;
  }
}

static void gen_open_namespace(FILE *fp, char **p)
{
  if (NULL == p) return;
  for (int i = 0; p[i]; i++) {
    fprintf(fp, "namespace %s {\n", p[i]);
  }
}

static void gen_close_namespace(FILE *fp, char **p)
{
  if (NULL == p) return;
  int n = ntl_length((void**)p);
  for (int i = n-1; i >= 0; i--) {
    fprintf(fp, "} // namespace %s\n", p[i]);
  }
}


static void gen_enum(FILE *fp, struct jc_enum *e)
{
  fprintf(stderr, "%d\n", file_type);
  char *t = e->name;
  fprintf(fp, "\n\n");
  gen_open_namespace(fp, e->namespace);
  fprintf(fp, "enum %s {\n", t);
  int i = 0, prev_value;

  for (i = 0; e->items && e->items[i]; i++) {
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
  gen_close_namespace(fp, e->namespace);
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
    .elem_size = sizeof(struct jc_def),
    .elem_from_buf = def_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)&(s->defs)
  };
  size_t ret = json_extract(json, size,
                            "(disabled):b"
                            "(comment):?s"
                            "(namespace):F"
                            "(defs):F",
                            &s->is_disabled,
                            &s->comment,
                            orka_str_to_ntl, &d1,
                            orka_str_to_ntl, &d2);
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
    return definition_list_from_json(json, xend_pos - json, s);
  else {
    *s = ntl_calloc(1, sizeof(struct jc_definition));
    return definition_from_json(json, xend_pos - json, (*s)[0]);
  }
}


struct action {
  bool todo;
  char *c_name;
  char *json_key;
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
  bool is_actor_alloc;
  bool need_double_quotes;
};

static int to_builtin_action(struct jc_field *f, struct action *act)
{
  char * xend = NULL;
  if (strcmp(f->type.base, "int") == 0) {
    act->extractor = "d";
    act->injector = "d";
    act->c_type = f->type.int_alias ? f->type.int_alias : "int";
    if (f->inject_condition.opcode == INJECT_IF_NOT_STR) {
      f->inject_condition.opcode = INJECT_IF_NOT_INT;
      f->inject_condition._.ival = (uint64_t)strtol(f->inject_condition.string,
                                                    &xend, 10);
      //@todo check xend
    }
  }
  else if (strcmp(f->type.base, "s_as_u64") == 0) {
    act->extractor = "s_as_u64";
    act->injector = "s_as_u64";
    act->c_type = "uint64_t";
    if (f->inject_condition.opcode == INJECT_IF_NOT_STR) {
      f->inject_condition.opcode = INJECT_IF_NOT_INT;
      f->inject_condition._.ival = (uint64_t)strtoll(f->inject_condition.string,
                                                     &xend, 10);
      //@todo check xend
    }
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
    if (f->inject_condition.opcode == INJECT_IF_NOT_STR) {
      f->inject_condition.opcode = INJECT_IF_NOT_BOOL;
      if (strcmp("true", f->inject_condition.string) == 0) {
        f->inject_condition._.sval = "true";
      }
      else if (strcmp("false", f->inject_condition.string) == 0) {
        f->inject_condition._.sval = "false";
      }
      else {
        ERR("%s is not a bool value\n", f->inject_condition.string);
      }
    }
  }
  else if (strcmp(f->type.base, "float") == 0) {
    act->extractor = "f";
    act->injector = "f";
    act->c_type = "float";
    if (f->inject_condition.opcode == INJECT_IF_NOT_STR) {
      f->inject_condition.opcode = INJECT_IF_NOT_DOUBLE;
      f->inject_condition._.dval = strtod(f->inject_condition.string, &xend);
      //@todo check xend
    }
  }
  else if (strcmp(f->type.base, "char") == 0
           && DEC_POINTER == f->type.decor.tag) {
    if(!f->type.converter) {
      act->injector = "s";
      act->extractor = "?s";
      act->extract_arg_decor = "&";
      act->inject_arg_decor = "";
      act->post_dec = "";
      act->pre_dec = "*";
      act->free = "free";
      act->c_type = "char";
    }
    else {
      struct converter *c = get_converter(f->type.converter);
      act->is_user_def = true;
      act->extractor = c->extractor;
      act->injector = c->injector;
      act->free = c->free;
      act->extract_arg_decor = c->extractor_addrof;
      act->inject_arg_decor = c->injector_addrof;
      act->c_type = c->output_type;
      act->post_dec = "";
      act->pre_dec = "";
      act->need_double_quotes = true;

      if (f->inject_condition.opcode == INJECT_IF_NOT_STR) {
        if (strcmp(c->converted_builtin_type, "uint64_t") == 0) {
          f->inject_condition.opcode = INJECT_IF_NOT_INT;
          f->inject_condition._.ival = (uint64_t) strtoll(
            f->inject_condition.string,
            &xend, 10);
          //@todo check xend
        }
      }
    }
    return 1;
  }
  else {
    return 0;
  }
  return 1;
}

static void to_action(struct jc_field *f, struct action *act)
{
  if (f->todo) {
    act->todo = true;
    return;
  }

  act->post_dec = "";
  act->pre_dec = "";
  if (f->type.int_alias)
    act->c_type = f->type.int_alias;
  else
    act->c_type = f->type.base;

  act->c_name = f->name;
  act->json_key = f->json_key ? f->json_key : f->name;

  switch(f->type.decor.tag)
  {
    case DEC_POINTER:
      if (!to_builtin_action(f, act)) {
        if (strcmp(f->type.base, "char") == 0) {
          ERR("this should never happen\n");
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
            act->is_actor_alloc = false;
          }
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
      act->is_actor_alloc = true;
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
        act->post_dec = f->type.decor.value;
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
emit_field_init(void *cxt, FILE *fp, struct jc_field *f)
{
  struct action act = { 0 };
  to_action(f, &act);

  if (act.todo) return;

  if (act.alloc && !f->lazy_init)
    fprintf (fp, "  p->%s = %s();\n", act.c_name, act.alloc);
}

static void
gen_init (FILE *fp, struct jc_struct *s)
{
  char *t = s->name;

  fprintf(fp, "void %s_init(struct %s *p) {\n", t, t);
  fprintf(fp, "  memset(p, 0, sizeof(struct %s));\n", t);
  for (int i = 0; s->fields && s->fields[i]; i++) {
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_field_init(NULL, fp, s->fields[i]);
    fprintf(fp, "\n");
  }

  fprintf(fp, "}\n");
}

static void gen_default(FILE *fp, struct jc_struct * s)
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

static void
emit_field_cleanup(void *cxt, FILE *fp, struct jc_field *f)
{
  struct action act = {0};
  to_action(f, &act);

  if (act.todo)
    fprintf(fp, "  //@todo p->%s\n", act.c_name);
  else if (act.free)
    fprintf(fp,
            "  if (d->%s)\n"
            "    %s(d->%s);\n",
            act.c_name, act.free, act.c_name);
  else
    fprintf(fp, "  //p->%s is a scalar\n", act.c_name);
}

static void gen_cleanup(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  fprintf(fp, "void %s_cleanup(struct %s *d) {\n", t, t);
  for (int i = 0; s->fields && s->fields[i]; i++) {
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_field_cleanup(NULL, fp, s->fields[i]);
  }

  fprintf(fp, "}\n");
}

static void emit_field(void *cxt, FILE *fp, struct jc_field *f)
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

static void
emit_json_extractor(void *cxt, FILE *fp, struct jc_field *f)
{
  struct action act = {0};
  to_action(f, &act);
  if (act.todo) return;

  if (act.is_user_def)
    fprintf(fp, "                \"(%s):F,\"\n", act.json_key);
  else
    fprintf(fp, "                \"(%s):%s,\"\n", act.json_key, act.extractor);
}

static void
emit_json_extractor_arg(void *cxt, FILE *fp, struct jc_field *f)
{
  struct action act = {0};
  to_action(f, &act);
  if (act.todo) return;

  if (act.is_user_def) {
    if (act.is_actor_alloc)
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

static bool
is_disabled_method(struct jc_struct *s, char *name)
{
  for (int i = 0; s->disable_methods && s->disable_methods[i]; i++)
    if (strcmp(name, s->disable_methods[i]) == 0)
      return true;
  return false;
}

static void gen_from_json(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  bool emit_spec = true, is_disabled = false;
  char * suffix = "";

  if (is_disabled_method(s, "from_json")) {
    emit_spec = false;
    suffix = "_disabled";
    is_disabled = true;
  }

  if (is_disabled) {
    fprintf(fp, "\n/* This method is disabled at %s:%d:%d */\n",
            spec_name,
            s->disable_methods_lnc.line,
            s->disable_methods_lnc.column);
  }
  fprintf(fp, "void %s_from_json%s(char *json, size_t len, struct %s *p)\n",
          t, suffix, t);

  fprintf(fp, "{\n");
  fprintf(fp, "  static size_t ret=0; // used for debugging\n");
  fprintf(fp, "  size_t r=0;\n");
  fprintf(fp, "  r=json_extract(json, len, \n");
  for (int i = 0; s->fields && s->fields[i]; i++) {
    if (emit_spec)
      emit_field_spec(NULL, fp, s->fields[i]);
    emit_json_extractor(NULL, fp, s->fields[i]);
  }

  fprintf(fp, "                \"@arg_switches:b\"\n");
  fprintf(fp, "                \"@record_defined\"\n");
  fprintf(fp, "                \"@record_null\",\n");

  for (int i = 0; s->fields && s->fields[i]; i++) {
    if (emit_spec)
      emit_field_spec(NULL, fp, s->fields[i]);
    emit_json_extractor_arg(NULL, fp, s->fields[i]);
  }

  fprintf(fp, "                p->__M.arg_switches,"
    " sizeof(p->__M.arg_switches),"
    " p->__M.enable_arg_switches,\n");
  fprintf(fp, "                p->__M.record_defined,"
    " sizeof(p->__M.record_defined),\n");
  fprintf(fp, "                p->__M.record_null,"
    " sizeof(p->__M.record_null));\n");
  fprintf(fp, "  ret = r;\n");
  fprintf(fp, "}\n");

  if (is_disabled) {
    char *f = NULL;
    asprintf(&f, "%s_from_json", t);
    emit_alias_disabled(fp, f);
    free(f);
  }
}

static void emit_inject_setting(void *cxt, FILE *fp, struct jc_field *f)
{
  struct action act = {0};
  to_action(f, &act);
  if (act.todo) return;

  int i = *(int *)cxt;

  switch(f->inject_condition.opcode)
  {
    case INJECT_ALWAYS:
      fprintf(fp, "  p->__M.arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
    case INJECT_IF_NOT_NULL:
      fprintf(fp, "  if (p->%s != NULL)\n", act.c_name);
      fprintf(fp, "    p->__M.arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
    case INJECT_IF_NOT_BOOL:
      fprintf(fp, "  if (p->%s != %s)\n", act.c_name,
              f->inject_condition._.sval);
      fprintf(fp, "    p->__M.arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
    case INJECT_IF_NOT_INT:
      fprintf(fp, "  if (p->%s != %s)\n", act.c_name,
              f->inject_condition.string);
      fprintf(fp, "    p->__M.arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
    case INJECT_IF_NOT_DOUBLE:
      fprintf(fp, "  if (p->%s != %s)\n", act.c_name,
              f->inject_condition.string);
      fprintf(fp, "    p->__M.arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
    case INJECT_IF_NOT_STR:
      fprintf(fp, "  if (strcmp(p->%s, %s) != 0)\n", act.c_name,
              f->inject_condition.string);
      fprintf(fp, "    p->__M.arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
    case INJECT_IF_NOT_EMPTY_STR:
      if (f->type.decor.tag == DEC_POINTER)
        fprintf(fp, "  if (p->%s != NULL && strlen(p->%s) != 0)\n",
                act.c_name, act.c_name);
      else
        fprintf(fp, "  if (strlen(p->%s) != 0)\n", act.c_name);
      fprintf(fp, "    p->__M.arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
  }
}

static void gen_use_default_inject_settings(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  fprintf(fp, "void %s_use_default_inject_settings(struct %s *p)\n",
          t, t);
  fprintf(fp, "{\n");
  fprintf(fp, "  p->__M.enable_arg_switches = true;\n");
  for (int i = 0; s->fields && s->fields[i]; i++) {
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_inject_setting(&i, fp, s->fields[i]);
    fprintf(fp, "\n");
  }
  fprintf(fp, "}\n");
}

static void emit_json_injector(void *cxt, FILE *fp, struct jc_field *f)
{
  struct action act = {0};
  to_action(f, &act);
  if (act.todo) return;

  if (act.is_user_def)
    if (act.need_double_quotes)
      fprintf(fp, "                \"(%s):|F|,\"\n", act.json_key);
    else
      fprintf(fp, "                \"(%s):F,\"\n", act.json_key);
  else
    fprintf(fp, "                \"(%s):%s,\"\n", act.json_key, act.injector);
}

static void emit_json_injector_arg(void * cxt, FILE *fp, struct jc_field *f)
{
  struct action act = {0};
  to_action(f, &act);
  if (act.todo) return;

  if (act.is_user_def)
    fprintf(fp, "                %s, %sp->%s,\n",
            act.injector, act.inject_arg_decor, act.c_name);
  else
    fprintf(fp, "                %sp->%s,\n",
            act.inject_arg_decor, act.c_name);
}

static void gen_to_json(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  bool emit_spec = true, is_disabled = false;
  char * suffix = "";

  if (is_disabled_method(s, "to_json")) {
    emit_spec = false;
    is_disabled = true;
    suffix = "_disabled";
  }

  if (is_disabled) {
    fprintf(fp, "\n/* This method is disabled at %s:%d:%d */\n",
            spec_name,
            s->disable_methods_lnc.line,
            s->disable_methods_lnc.column);
  }
  fprintf(fp, "size_t %s_to_json%s(char *json, size_t len, struct %s *p)\n",
          t, suffix, t);
  fprintf(fp, "{\n");
  fprintf(fp, "  size_t r;\n");
  fprintf(fp, "  r=json_inject(json, len, \n");

  for (int i = 0; s->fields && s->fields[i]; i++) {
    if (emit_spec)
      emit_field_spec(NULL, fp, s->fields[i]);
    emit_json_injector(NULL, fp, s->fields[i]);
  }

  fprintf(fp, "                \"@arg_switches:b\",\n");

  for (int i = 0; s->fields && s->fields[i]; i++) {
    if (emit_spec)
      emit_field_spec(NULL, fp, s->fields[i]);
    emit_json_injector_arg(NULL, fp, s->fields[i]);
  }

  fprintf(fp, "                p->__M.arg_switches, "
    "sizeof(p->__M.arg_switches),"
    " p->__M.enable_arg_switches);\n");
  fprintf(fp, "  return r;\n");
  fprintf(fp, "}\n");

  if (is_disabled) {
    char *f = NULL;
    asprintf(&f, "%s_to_json", t);
    emit_alias_disabled(fp, f);
    free(f);
  }
}

static void gen_to_query(FILE *fp, struct jc_struct *s)
{
  return;

  char *t = s->name;
  bool has_query = false;
  for (int i = 0; s->fields && s->fields[i]; i++) {
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

  
  for (int i = 0; s->fields && s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    if (f->loc != LOC_IN_QUERY)
      continue;

    struct action act = {0};
    to_action(f, &act);
    if (act.todo) continue;
    fprintf(fp, "                \"(%s):%s\"\n", f->name, act.injector);
  }
  fprintf(fp, "                \"@arg_switches:b\",\n");

  for (int i = 0; s->fields && s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    if (f->loc != LOC_IN_QUERY)
      continue;

    struct action act = {0};
    to_action(f, &act);
    if (act.todo) continue;

    fprintf(fp, "                %sp->%s,\n", act.inject_arg_decor, act.c_name);
  }
  fprintf(fp, "                p->__M.arg_switches,"
    " sizeof(p->__M.arg_switches),"
    " &p->__M.enable_arg_switches);\n");
  fprintf(fp,  "  return r;\n");
  fprintf(fp, "}\n");
}

static void
gen_struct(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  if (s->title)
    fprintf(fp, "/* Title: %s */\n", s->title);
  if (s->comment)
    fprintf(fp, "/* %s */\n", s->comment);

  fprintf(fp, "/* This is defined at %s:%d:%d */\n",
          spec_name, s->name_lnc.line, s->name_lnc.column);
  fprintf(fp, "struct %s {\n", t);
  int i = 0;
  for (i = 0; s->fields && s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    emit_field_spec(NULL, fp, f);
    emit_field(NULL, fp, f);
    fprintf(fp, "\n");
  }
  fprintf(fp, "  // The following is metadata used to \n");
  fprintf(fp, "  // 1. control which field should be extracted/injected\n");
  fprintf(fp, "  // 2. record which field is presented(defined) in JSON\n");
  fprintf(fp, "  // 3. record which field is null in JSON\n");
  fprintf(fp, "  struct {\n");
  fprintf(fp, "    bool enable_arg_switches;\n");
  fprintf(fp, "    bool enable_record_defined;\n");
  fprintf(fp, "    bool enable_record_null;\n");
  fprintf(fp, "    void *arg_switches[%d];\n", i);
  fprintf(fp, "    void *record_defined[%d];\n", i);
  fprintf(fp, "    void *record_null[%d];\n", i);
  fprintf(fp, "  } __M; // metadata\n");
  fprintf(fp, "};\n");
}

static void
gen_wrapper(FILE *fp, struct jc_struct *s)
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

static void
gen_forward_declare(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  fprintf(fp, "extern void %s_cleanup_v(void *p);\n", t);
  fprintf(fp, "extern void %s_cleanup(struct %s *p);\n", t, t);

  fprintf(fp, "extern void %s_init_v(void *p);\n", t);
  fprintf(fp, "extern void %s_init(struct %s *p);\n", t, t);

  fprintf(fp, "extern struct %s * %s_alloc();\n", t, t);

  fprintf(fp, "extern void %s_free_v(void *p);\n", t);
  fprintf(fp, "extern void %s_free(struct %s *p);\n", t, t);

  fprintf(fp, "extern void %s_from_json_v(char *json, size_t len, void *p);\n", t);
  fprintf(fp, "extern void %s_from_json(char *json, size_t len, struct %s *p);\n",
          t, t);

  fprintf(fp, "extern size_t %s_to_json_v(char *json, size_t len, void *p);\n", t);
  fprintf(fp, "extern size_t %s_to_json(char *json, size_t len, struct %s *p);\n",
          t, t);

  fprintf(fp, "extern size_t %s_to_query_v(char *json, size_t len, void *p);\n", t);
  fprintf(fp, "extern size_t %s_to_query(char *json, size_t len, struct %s *p);\n",
          t, t);

  fprintf(fp, "extern void %s_list_free_v(void **p);\n", t);
  fprintf(fp, "extern void %s_list_free(struct %s **p);\n", t, t);

  fprintf(fp, "extern void %s_list_from_json_v(char *str, size_t len, void *p);\n", t);
  fprintf(fp, "extern void %s_list_from_json(char *str, size_t len, struct %s ***p);\n",
          t, t);

  fprintf(fp, "extern size_t %s_list_to_json_v(char *str, size_t len, void *p);\n", t);
  fprintf(fp, "extern size_t %s_list_to_json(char *str, size_t len, struct %s **p);\n",
          t,t);

  fprintf(fp, "extern void %s_use_default_inject_settings(struct %s *p);\n", t, t);
}

static void
gen_typedef (FILE *fp, struct jc_struct *s)
{
#if 1
  fprintf(fp, "typedef void (*vfvp)(void *);\n");
  fprintf(fp, "typedef void (*vfcpsvp)(char *, size_t, void *);\n");
  fprintf(fp, "typedef size_t (*sfcpsvp)(char *, size_t, void *);\n");
#endif
}

static void
gen_struct_all (FILE *fp, struct jc_struct *s)
{
  fprintf(fp, "\n");
  gen_open_namespace(fp, s->namespace);

  if (file_type == FILE_HEADER || file_type == FILE_DECLARATION) {
    gen_struct (fp, s);
    //fprintf (fp, "\n*/\n");
    gen_forward_declare(fp, s);
  }
  else if (file_type == FILE_SINGLE_FILE) {
    gen_struct (fp, s);
    //fprintf (fp, "\n*/\n");
    gen_forward_declare(fp, s);

    gen_from_json(fp, s);
    fprintf(fp, "\n");
    gen_to_json(fp, s);
    fprintf(fp, "\n");

    gen_use_default_inject_settings(fp, s);
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

    gen_use_default_inject_settings(fp, s);
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
  gen_close_namespace(fp, s->namespace);
}

static void
gen_def (FILE *fp, struct jc_def *def)
{
  if (def->is_struct)
    gen_struct_all(fp, (struct jc_struct *)def);
  else {
    if (file_type == FILE_HEADER
        || file_type == FILE_DECLARATION
        || file_type == FILE_SINGLE_FILE) {
      gen_enum(fp, (struct jc_enum *)def);
    }
  }
}


static void
gen_definition(FILE *fp, enum file_type type, struct jc_definition *d)
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

  ntl_apply(fp, (void**)d->defs, gen_def);

  if (type != FILE_DECLARATION && type != FILE_DEFINITION)
    gen_close_namespace(fp, d->namespace);
  return;
}

static void
gen_definition_list(char *folder, enum file_type type, struct jc_definition **ntl)
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

static char*
field_to_string(
  void *cxt,
  void (*emitter)(void *cxt, FILE *fp, struct jc_field *),
  struct jc_field *f)
{
  char * buf; size_t len;
  FILE *fp = open_memstream(&buf, &len);
  emitter(cxt, fp, f);
  fclose(fp);
  return buf;
}