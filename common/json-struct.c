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
 *      "namespace_alias"?: [<string>+],
 *      "defs": [<def-list>]
 *      }
 *
 * <def> := "title"?:<string>,
 *          "comment"?:<string>,
 *          "namespace"?:[<string>+],
 *          (<struct> | <enum>)
 *
 * <struct> :=  "struct" : <string>, "typedef" : <string>, "fields": [ <field>+ ]
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
 * <enum> := "enum" :<string>, "typedef" : <string>, "items": [ <items>+ ]
 * <item> := { "name" : <string>, "value": <integer>? }
 *
 */

typedef char name_t[80];

typedef void (*vvpvp)(void *, void *);
typedef void (*vcpsvp)(char *, size_t, void *);

static void
emit_alias_disabled(FILE *fp, char *f)
{
  /*
  fprintf(fp, "__typeof(%s_disabled) %s __attribute__((weak, alias(\"%s_disabled\")));\n",
          f, f, f);
          */
}

static char *spec_name = "";
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

static NTL_T(struct converter) converters = NULL;

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
  converters = (NTL_T(struct converters))ntl_calloc(2, sizeof(struct converter));
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

  /*
  for (int i = 0; converters[i]; i++)
    fprintf(stderr, "adding converters %s ...\n", converters[i]->name);
    */

}
static void load_converters(char *filename)
{
  size_t len = 0;
  char * data = orka_load_whole_file(filename, &len);
  converter_file = strdup(filename);

  struct ntl_deserializer d = {
    .ntl_recipient_p = (ntl_t *)&converters,
    .init_elem = NULL,
    .elem_size = sizeof(struct converter),
    .elem_from_buf = (vcpsvp)load_converter
  };
  extract_ntl_from_json(data, len, &d);
  //orka_str_to_ntl(data, len, &d);
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
  FILE_ENUM_DECLARATION,
  FILE_STRUCT_DECLARATION,
  FILE_OPAQUE_STRUCT_DECLARATION,
  FILE_FUN_DECLARATION,
  FILE_DECLARATION,
  FILE_DEFINITION,
  FILE_HEADER,
  FILE_CODE
};
//static enum file_type file_type = FILE_SINGLE_FILE;


struct emit_option {
  bool wrapper_only; // emit C++ code which only wrap around C functions.
  bool lang_C; // emit C code instead of C++ which is the default
  enum file_type type;
  NTL_T(name_t) namespace_stack[8];
  int stack_top;
};

struct emit_option global_option;
static void init_emit_option(struct emit_option *opt)
{
  memset(&global_option, 0, sizeof(global_option));
  global_option.lang_C = opt->lang_C;
  global_option.type = opt->type;
}

static char* ns_to_symbol_name(char *name)
{
  if (global_option.lang_C) {
    char *buf;
    size_t len;
    FILE *fp = open_memstream(&buf, &len);
    for (int s = 0; s < global_option.stack_top; s++) {
      NTL_T(name_t) ns = global_option.namespace_stack[s];
      for (int i = 0; ns[i]; i++)
        fprintf(fp, "%s_", (char *)ns[i]);
    }
    fprintf(fp, "%s", name);
    fclose(fp);
    return buf;
  }
  else
    return name;
}

static char* get_file_suffix(enum file_type t)
{
  switch(t)
  {
    case FILE_SINGLE_FILE: return "cc";
    case FILE_DECLARATION: return "hh";
    case FILE_DEFINITION: return "cc";
    case FILE_HEADER: return "hh";
    case FILE_CODE: return "cc";
    default:
      abort();
  }
  return "";
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
  char *converter;
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
  LOC_IN_BODY,
  LOC_IN_URL
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
    char *sval;
  } _;
  char *string;
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
  char *comment;
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
  NTL_T(name_t) disable_methods; \
  struct line_and_column disable_methods_lnc; \
  char *title; \
  char *comment; \
  NTL_T(name_t) namespace; \
  NTL_T(NTL_T(name_t)) namespaces; \
  char *name; \
  char *typedef_name; \
  struct line_and_column name_lnc;


struct jc_struct {
  DEF_HEADER
  NTL_T(struct jc_field) fields;
};

static void
print_struct(FILE *fp, struct jc_struct *p)
{
  fprintf(fp, "name %s\n", p->name);
  ntl_apply(fp, (ntl_t)p->fields, (vvpvp)print_field);
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
  NTL_T(struct jc_item) items;
};

struct jc_def {
  DEF_HEADER
  union {
    NTL_T(struct jc_field) fields;
    NTL_T(struct jc_item) items;
  } list;
  bool is_struct;
};

static void
print_enum(FILE *fp, struct jc_enum *p)
{
  fprintf(fp, "name %s\n", p->name);
  ntl_apply(fp, (ntl_t)p->items, (vvpvp)print_item);
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
  NTL_T(name_t) namespace; // ntl
  NTL_T(struct jc_def) defs; //ntl
};

static int has_struct(NTL_T(struct jc_def) defs)
{
  for (int i = 0; defs[i]; i++)
    if (defs[i]->is_struct)
      return 1;
  return 0;
}

static int has_enum(NTL_T(struct jc_def) defs)
{
  for (int i = 0; defs[i]; i++)
    if (!defs[i]->is_struct)
      return 1;
  return 0;
}

static char* namespace_to_str(NTL_T(name_t) ns)
{
  char *buf; size_t len;
  FILE * fp = open_memstream(&buf, &len);
  for(int i = 0; ns && ns[i]; i++)
    fprintf(fp,"%s.", (char *)ns[i]);
  fclose(fp);
  return buf;
}

static void
print_definition(FILE *fp, struct jc_definition *p)
{
  fprintf(fp, "/*\n %s  */\n", p->comment);
  fprintf(fp, "namespace: ");
  ntl_apply(fp, (ntl_t)p->namespace, (vvpvp)fprintf);

  fprintf(fp, "\n");
  ntl_apply(fp, (ntl_t)p->defs, (vvpvp)print_def);
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
  else if (3 == size && 0 == strncmp(json, "url", size)) {
    *p = LOC_IN_URL;
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

  //bool copy_json_value = false;

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
      char *str = malloc(t.size + 1);
      strncpy(str, t.start, t.size);
      str[t.size] = 0;
      p->inject_condition.string = str;
    }
  }
  return s;
}

static size_t name_from_json(char *json, size_t size, char *p)
{
  ASSERT_S(size < sizeof(name_t), "namespace is too long");
  memcpy(p, json, size);
  p[size] = 0;
  return size;
}

static size_t
namespace_from_json(char *json, size_t size, NTL_T(name_t) *ns_p)
{
  struct ntl_deserializer d0 = {
    .elem_size = sizeof(name_t),
    .elem_from_buf = (vcpsvp)name_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (ntl_t *)ns_p
  };

  //return orka_str_to_ntl(json, size, &d0);
  return extract_ntl_from_json(json, size, &d0);
}

static size_t struct_from_json(char *json, size_t size, struct jc_struct *s)
{
  struct ntl_deserializer dx = {
    .elem_size = sizeof(name_t),
    .elem_from_buf = (vcpsvp)name_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (ntl_t *)&(s->disable_methods)
  };

  struct ntl_deserializer d1 = {
    .elem_size = sizeof(struct jc_field),
    .elem_from_buf = (vcpsvp)field_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (ntl_t *)&(s->fields)
  };

  size_t ret = json_extract(json, size,
                            "(disable_methods):F,"
                            "(disable_methods):lnc,"
                            "(fields):F",
                            extract_ntl_from_json, &dx,
                            &s->disable_methods_lnc,
                            extract_ntl_from_json, &d1);

  adjust_lnc(json, &s->disable_methods_lnc);
  return ret;
}

static size_t item_from_json(char *json, size_t size, void *x)
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

static size_t enum_from_json(char * json, size_t size, struct jc_enum *e)
{
  struct ntl_deserializer d1 = {
    .elem_size = sizeof(struct jc_item),
    .elem_from_buf = (vcpsvp)item_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (ntl_t *)&(e->items)
  };

  size_t ret = json_extract(json, size,
                            "(items):F",
                            extract_ntl_from_json, &d1);
  return ret;
}

static size_t def_from_json(char *json, size_t size, struct jc_def *def)
{
  bool is_struct = false, is_enum = false;
  struct ntl_deserializer d0 = {
    .elem_size = sizeof(name_t),
    .elem_from_buf = (vcpsvp)name_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (ntl_t *)&(def->namespace)
  };

  struct ntl_deserializer d0_alias = {
    .elem_size = sizeof(void*),
    .elem_from_buf = (vcpsvp)namespace_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (ntl_t *)&(def->namespaces)
  };

  json_extract(json, size,
               "(comment):?s,"
               "(title):?s,"
               "(namespace):F,"
               "(namespaces):F,"
               "(typedef):?s,"
               "(struct):key,(enum):key,"
               "(struct):?s, (enum):?s,"
               "(struct):lnc",
               &def->comment,
               &def->title,
               extract_ntl_from_json, &d0,
               extract_ntl_from_json, &d0_alias,
               &def->typedef_name,
               &is_struct, &is_enum,
               &def->name, &def->name,
               &def->name_lnc
               );

  adjust_lnc(json, &def->name_lnc);
  if (is_struct) {
    def->is_struct = true;
    return struct_from_json(json, size, (struct jc_struct *)def);
  }
  else if (is_enum) {
    def->is_struct = false;
    return enum_from_json(json, size, (struct jc_enum *)def);
  }
  else {
    ERR("missing 'struct' or 'enum' in '%.*s'", (int)size, json);
    return 0;
  }
}


static void gen_open_namespace(FILE *fp, NTL_T(name_t) p)
{
  if (NULL == p) return;
  if (global_option.lang_C) {
    global_option.namespace_stack[global_option.stack_top] = p;
    global_option.stack_top ++;
  }
  else {
    for (int i = 0; p[i]; i++)
      fprintf(fp, "namespace %s {\n", (char *)p[i]);
  }
}

static void gen_close_namespace(FILE *fp, NTL_T(name_t) p)
{
  if (NULL == p) return;
  if (global_option.lang_C) {
    global_option.stack_top --;
    global_option.namespace_stack[global_option.stack_top] = NULL;
  }
  else {
    int n = ntl_length((ntl_t)p);
    for (int i = n - 1; i >= 0; i--)
      fprintf(fp, "} // namespace %s\n", (char *)p[i]);
  }
}

static void gen_enum(FILE *fp, struct jc_enum *e, name_t **ns)
{
  fprintf(stderr, "%d\n", global_option.type);
  fprintf(fp, "\n\n");

  gen_open_namespace(fp, ns);
  char *t = ns_to_symbol_name(e->name);
  char *t_alias = NULL;
  
  if (e->typedef_name) 
    t_alias = ns_to_symbol_name(e->typedef_name);

  if (t_alias)
    fprintf(fp, "typedef ");
  
  fprintf(fp, "enum %s {\n", t);
  int i = 0, prev_value = -1;

  for (i = 0; e->items && e->items[i]; i++) {
    struct jc_item * item = e->items[i];
    if (item->todo) {
      fprintf(fp, "//@todo %s %s\n", item->name, item->comment);
    }
    else {
      fprintf(fp, "  %s", item->name);
      if (item->has_value) {
        fprintf(fp, " = %d", item->value);
        prev_value = item->value;
      }
      else {
        fprintf(fp, " = %d", prev_value + 1);
        prev_value ++;
      }
      if (item->comment)
        fprintf(fp, ", // %s\n", item->comment);
      else
        fprintf(fp, ",\n");
    }
  }
  if (t_alias)
    fprintf(fp, "} %s\n", t_alias);
  else
    fprintf(fp, "};\n");
  gen_close_namespace(fp, ns);
}


static size_t
definition_from_json(char *json, size_t size, struct jc_definition *s)
{
  struct ntl_deserializer d1 = {
    .elem_size = sizeof(name_t),
    .elem_from_buf = (vcpsvp)name_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (ntl_t *)&(s->namespace)
  };

  struct ntl_deserializer d2 = {
    .elem_size = sizeof(struct jc_def),
    .elem_from_buf = (vcpsvp)def_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (ntl_t *)&(s->defs)
  };
  size_t ret = json_extract(json, size,
                            "(disabled):b"
                            "(comment):?s"
                            "(namespace):F"
                            "(defs):F",
                            &s->is_disabled,
                            &s->comment,
                            extract_ntl_from_json, &d1,
                            extract_ntl_from_json, &d2);
  return ret;
}

static size_t
definition_list_from_json(char *json, size_t size,
                          NTL_T(struct jc_definition) *s)
{
  struct ntl_deserializer d = {
    .elem_size = sizeof(struct jc_definition),
    .elem_from_buf = (vcpsvp)definition_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (ntl_t *)s
  };
  return extract_ntl_from_json(json, size, &d);
}

static size_t spec_from_json(char *json, size_t size,
                             NTL_T(struct jc_definition) *s)
{
  char *const xend_pos = json + size;

  while (isspace(*json)) {
    json ++;
  }
  if ('[' == *json)
    return definition_list_from_json(json, xend_pos - json, s);
  else {
    *s = (NTL_T(struct jc_definition))ntl_calloc(1, sizeof(struct jc_definition));
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
    //act->c_type = f->type.int_alias ? f->type.int_alias : "int";
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
  else if (strcmp(f->type.base, "s_as_hex_uint") == 0) {
    act->extractor = "s_as_hex_uint";
    act->injector = "s_as_hex_uint";
    act->c_type = "unsigned int";
    if (f->type.int_alias) {
      act->c_type = f->type.int_alias;
    }
    if (f->inject_condition.opcode == INJECT_IF_NOT_STR) {
      f->inject_condition.opcode = INJECT_IF_NOT_INT;
      f->inject_condition._.ival = (uint64_t)strtoll(f->inject_condition.string,
                                                     &xend, 10);
      //@todo check xend
    }
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


static char* to_C_name(char *s)
{
  char *ns = malloc(strlen(s) + 1);
  char *p = ns;
  while (*s) {
    if (*s == ':' && *(s+1) == ':') {
      *p = '_';
      p ++;
      s += 2;
    }
    else {
      *p = *s;
      p ++;
      s ++;
    }
  }
  *p = 0;
  return ns;
}


static void to_action(struct jc_field *f, struct action *act)
{
  if (f->todo) {
    act->todo = true;
    return;
  }

  bool is_user_defined_type = true;
  act->post_dec = "";
  act->pre_dec = "";
  if (f->type.int_alias)
    act->c_type = f->type.int_alias;
  else
    act->c_type = f->type.base;

  char *tok = strrchr(act->c_type, ':');
  if (tok != NULL) {
    is_user_defined_type = true;
    if (global_option.lang_C)
      act->c_type = to_C_name(act->c_type);
  }

  act->c_name = f->name;
  act->json_key = f->json_key ? f->json_key : f->name;

  switch(f->type.decor.tag)
  {
    case DEC_POINTER:
      if (!to_builtin_action(f, act)) {
        if (strcmp(f->type.base, "char") == 0) {
          ERR("this should never happen\n");
        } else {
          if (is_user_defined_type) {
            asprintf(&act->injector, "%s_to_json", act->c_type);
            asprintf(&act->extractor, "%s_from_json", act->c_type);
            asprintf(&act->alloc, "%s_alloc", act->c_type);
            asprintf(&act->free, "%s_free", act->c_type);
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
        asprintf(&act->extractor, "%s_list_from_json", act->c_type);
        asprintf(&act->injector, "%s_list_to_json", act->c_type);
      } else {
        asprintf(&act->extractor, "%s_list_from_json", act->c_type);
        asprintf(&act->injector, "%s_list_to_json", act->c_type);
        asprintf(&act->free, "%s_list_free", act->c_type);
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

static void emit_field_init(void *cxt, FILE *fp, struct jc_field *f)
{
  struct action act = { 0 };
  to_action(f, &act);

  if (act.todo) return;

  if (act.alloc && !f->lazy_init)
    fprintf (fp, "  p->%s = %s();\n", act.c_name, act.alloc);
}

static void gen_init (FILE *fp, struct jc_struct *s)
{
  char *t = ns_to_symbol_name(s->name);

  fprintf(fp, "void %s_init(struct %s *p) {\n", t, t);
  fprintf(fp, "  memset(p, 0, sizeof(struct %s));\n", t);
  for (int i = 0; s->fields && s->fields[i]; i++) {
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_field_init(NULL, fp, s->fields[i]);
    fprintf(fp, "\n");
  }

  fprintf(fp, "}\n");
}

static void gen_default(FILE *fp, struct jc_struct *s)
{
  char * type = ns_to_symbol_name(s->name);

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
  fprintf(fp, "  extract_ntl_from_json(str, len, &d);\n");
  fprintf(fp, "}\n\n");

  fprintf(fp, "size_t %s_list_to_json(char *str, size_t len, struct %s **p)\n",
          type, type);
  fprintf(fp, "{\n");
  fprintf(fp, "  return ntl_to_buf(str, len, (void **)p, NULL, %s_to_json_v);\n",
          type);
  fprintf(fp, "}\n");
}

static void emit_field_cleanup(void *cxt, FILE *fp, struct jc_field *f)
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
  char *t = ns_to_symbol_name(s->name);
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

static void emit_json_extractor(void *cxt, FILE *fp, struct jc_field *f)
{
  struct action act = {0};
  to_action(f, &act);
  if (act.todo) return;

  if (act.is_user_def)
    fprintf(fp, "                \"(%s):F,\"\n", act.json_key);
  else
    fprintf(fp, "                \"(%s):%s,\"\n", act.json_key, act.extractor);
}

static void emit_json_extractor_arg(void *cxt, FILE *fp, struct jc_field *f)
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

static bool is_disabled_method(struct jc_struct *s, char *name)
{
  for (int i = 0; s->disable_methods && s->disable_methods[i]; i++)
    if (strcmp(name, (char *)s->disable_methods[i]) == 0)
      return true;
  return false;
}

static void gen_from_json(FILE *fp, struct jc_struct *s)
{
  char *t = ns_to_symbol_name(s->name);

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
  char *t = ns_to_symbol_name(s->name);

  fprintf(fp, "static void %s_use_default_inject_settings(struct %s *p)\n",
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
  char *t = ns_to_symbol_name(s->name);
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
  fprintf(fp, "  %s_use_default_inject_settings(p);\n", t);
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

  char *t = ns_to_symbol_name(s->name);

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

static void gen_struct(FILE *fp, struct jc_struct *s)
{
  char *t = ns_to_symbol_name(s->name);
  char *t_alias = NULL;

  if (s->typedef_name)
    t_alias = ns_to_symbol_name(s->typedef_name);

  if (s->title)
    fprintf(fp, "/* Title: %s */\n", s->title);
  if (s->comment)
    fprintf(fp, "/* %s */\n", s->comment);

  fprintf(fp, "/* This is defined at %s:%d:%d */\n",
          spec_name, s->name_lnc.line, s->name_lnc.column);

  if (t_alias)
    fprintf(fp, "typedef ");

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
  if (t_alias)
    fprintf(fp, "} %s;\n", t_alias);
  else  
    fprintf(fp, "};\n");
}

static void gen_wrapper(FILE *fp, struct jc_struct *s)
{
  char *t = ns_to_symbol_name(s->name);

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

static void gen_forward_fun_declare(FILE *fp, struct jc_struct *s)
{
  char *t = ns_to_symbol_name(s->name);

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

  //fprintf(fp, "extern void %s_use_default_inject_settings(struct %s *p);\n", t, t);
}

static void gen_typedef (FILE *fp, struct jc_struct *s)
{
#if 1
  fprintf(fp, "typedef void (*vfvp)(void *);\n");
  fprintf(fp, "typedef void (*vfcpsvp)(char *, size_t, void *);\n");
  fprintf(fp, "typedef size_t (*sfcpsvp)(char *, size_t, void *);\n");
#endif
}

static void gen_opaque_struct(FILE *fp, struct jc_struct *s, name_t **ns)
{
  fprintf(fp, "\n");
  gen_open_namespace(fp, ns);

  char *t = ns_to_symbol_name(s->name);

  if (s->title)
    fprintf(fp, "/* Title: %s */\n", s->title);
  if (s->comment)
    fprintf(fp, "/* %s */\n", s->comment);

  fprintf(fp, "/* This is defined at %s:%d:%d */\n",
          spec_name, s->name_lnc.line, s->name_lnc.column);

  fprintf(fp, "struct %s;\n", t);

  gen_close_namespace(fp, ns);
}

static void gen_struct_all(FILE *fp, struct jc_struct *s, name_t **ns)
{
  fprintf(fp, "\n");
  gen_open_namespace(fp, ns);

  if (global_option.type == FILE_STRUCT_DECLARATION) {
    gen_struct (fp, s);
  }
  else if (global_option.type == FILE_FUN_DECLARATION) {
    gen_forward_fun_declare(fp, s);
  }
  else if (global_option.type == FILE_HEADER
      || global_option.type == FILE_DECLARATION) {
    gen_struct (fp, s);
    //fprintf (fp, "\n*/\n");
    gen_forward_fun_declare(fp, s);
  }
  else if (global_option.type == FILE_SINGLE_FILE) {
    gen_struct (fp, s);
    //fprintf (fp, "\n*/\n");
    gen_forward_fun_declare(fp, s);

    gen_from_json(fp, s);
    fprintf(fp, "\n");

    gen_use_default_inject_settings(fp, s);
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

    gen_use_default_inject_settings(fp, s);
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
  gen_close_namespace(fp, ns);
}

static void gen_all_ns(FILE *fp, struct jc_def *def,
                       void (g)(FILE *, struct jc_def *, name_t **))
{
  g(fp, def, def->namespace);
  if (def->namespaces) {
    for (int i = 0; def->namespaces[i]; i++)
      g(fp, def, *(def->namespaces[i]));
  }
}

static void gen_def (FILE *fp, struct jc_def *def)
{
  if (def->is_struct) {
    if (global_option.type == FILE_OPAQUE_STRUCT_DECLARATION) {
      gen_all_ns(fp, def, gen_opaque_struct);
    }
    else if (global_option.type != FILE_ENUM_DECLARATION) {
      gen_all_ns(fp, def, gen_struct_all);
    }
  }
  else {
    if (global_option.type == FILE_HEADER
        || global_option.type == FILE_DECLARATION
        || global_option.type == FILE_ENUM_DECLARATION
        || global_option.type == FILE_SINGLE_FILE) {
      gen_all_ns(fp, def, gen_enum);
    }
  }
}

static void
gen_definition(FILE *fp, struct emit_option * option, struct jc_definition *d)
{
  init_emit_option(option);

  if (d->is_disabled)
    return;
  init_converters(); // @todo move it out of this function.
  if (d->spec_name)
    fprintf(fp, "/* This file is generated from %s, Please don't edit it. */\n",
            d->spec_name);

  if (global_option.type == FILE_SINGLE_FILE || global_option.type == FILE_CODE)
    fprintf(fp, "#include \"specs.h\"\n");

  fprintf(fp, "/*\n%s\n*/\n", d->comment);
  if (global_option.lang_C ||
      (global_option.type != FILE_DECLARATION
       && global_option.type != FILE_DEFINITION))
    gen_open_namespace(fp, d->namespace);

  ntl_apply(fp, (ntl_t)d->defs, (vvpvp)gen_def);

  if (global_option.lang_C ||
      (global_option.type != FILE_DECLARATION
       && global_option.type != FILE_DEFINITION))
    gen_close_namespace(fp, d->namespace);
  return;
}

static void
gen_definition_list(char *folder,
                    struct emit_option *opt,
                    NTL_T(struct jc_definition) ntl)
{
  char *fname = NULL;
  for (int i = 0; ntl && ntl[i]; i++) {
    struct jc_definition *d = ntl[i];
    char *f = namespace_to_str(d->namespace);
    asprintf(&fname, "%s/%s%s", folder, f, get_file_suffix(global_option.type));
    FILE *fp = fopen(fname, "w");
    gen_definition(fp, opt, d);
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