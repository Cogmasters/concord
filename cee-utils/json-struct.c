#define _GNU_SOURCE
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include "json-actor.h"
#include "cee-utils.h"

/* generated code dependencies */
static const char SPECS_DEPS_H[] =
  "#include <stdbool.h>\n"
  "#include <stdlib.h>\n"
  "#include <string.h>\n"
  "#include <strings.h>\n"
  "#include \"json-actor.h\"\n"
  "#include \"json-actor-boxed.h\"\n"
  "#include \"cee-utils.h\"\n"
;

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
 *              "inject_if_not"?:<string>|<bool>|<number>|null
 *              "todo"?:<bool>
 *            }
 *
 *
 * <field-type>  :=  "type" : { "base":<string>,
 *                              "int_alias"? : <string>,
 *                              "dec"?:("ntl"|"*"|"[<string>]"),
 *                              "converter"?:<string>,
 *                              "default_value"?:<string>|<bool>|<number>
 *                            }
 *
 *
 * <field-loc>   :=  "loc"  : ("json" | "query" | "body" | "url" | "multipart")
 *
 *
 * <enum> := "enum" :<string>, "typedef" : <string>, "items": [ <items>+ ]
 * <item> := { "name" : <string>, "value": <integer>? }
 *
 */

typedef char name_t[80];

typedef void (*vvpvp)(void *, void *);
typedef void (*vcpsvp)(char *, size_t, void *);

static char *spec_name = "";
static struct sized_buffer spec_buffer={0};

static void
adjust_lnc(char *json, struct line_and_column *out_lnc)
{
  if (!spec_buffer.start) return;

  struct line_and_column lnc = {0};
  addr_to_lnc (spec_buffer.start, spec_buffer.size, json, &lnc);
  out_lnc->line += (lnc.line + 1);
  out_lnc->column += lnc.column;
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
  bool need_double_quotes;
  bool inject_is_user_def;
  bool extract_is_user_def;
};

static NTL_T(struct converter) converters = NULL;

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

/* @todo creating a callback for each converter to modify struct action would be much easier to maintain */
static void 
init_converters(void) 
{
  converters = (struct converter**)ntl_calloc(3, sizeof(struct converter));
  converters[0]->name = "iso8601";
  converters[0]->input_type = "char*";
  converters[0]->output_type = "u64_unix_ms_t";
  converters[0]->free = NULL;
  converters[0]->extractor = "cee_iso8601_to_unix_ms";
  converters[0]->injector = "cee_unix_ms_to_iso8601";
  converters[0]->extractor_addrof = "&";
  converters[0]->injector_addrof = "&";
  converters[0]->converted_builtin_type = "uint64_t";
  converters[0]->need_double_quotes = true;
  converters[0]->inject_is_user_def = true;
  converters[0]->extract_is_user_def = true;

  converters[1]->name = "snowflake";
  converters[1]->input_type = "char*";
  converters[1]->output_type = "u64_snowflake_t";
  converters[1]->free = NULL;
  converters[1]->extractor = "cee_strtoull";
  converters[1]->injector = "cee_ulltostr";
  converters[1]->extractor_addrof = "&";
  converters[1]->injector_addrof = "&";
  converters[1]->converted_builtin_type = "uint64_t";
  converters[1]->need_double_quotes = true;
  converters[1]->inject_is_user_def = true;
  converters[1]->extract_is_user_def = true;

  converters[2]->name = "mixed";
  converters[2]->input_type = "char*";
  converters[2]->output_type = "json_char_t*";
  converters[2]->free = "free";
  converters[2]->extractor = "cee_strndup";
  converters[2]->injector = "s";
  converters[2]->extractor_addrof = "&";
  converters[2]->injector_addrof = "";
  converters[2]->converted_builtin_type = ""; /* will fallback to str */
  converters[2]->need_double_quotes = false;
  converters[2]->inject_is_user_def = false;
  converters[2]->extract_is_user_def = true;
}

static void 
load_converters(char *filename)
{
  size_t len = 0;
  char *data = cee_load_whole_file(filename, &len);
  converter_file = strdup(filename);

  struct ntl_deserializer d = {
    .ntl_recipient_p = (ntl_t *)&converters,
    .init_elem = NULL,
    .elem_size = sizeof(struct converter),
    .elem_from_buf = (vcpsvp)load_converter
  };
  extract_ntl_from_json(data, len, &d);
}

static struct converter* 
get_converter(char *name) 
{
  int i;
  for (i = 0; converters[i]; i++) {
    if (0 == strcmp(name, converters[i]->name)) {
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

struct emit_option {
  enum file_type type;
  NTL_T(name_t) namespace_stack[8];
  int stack_top;
};

static struct emit_option global_option;

static void init_emit_option(struct emit_option *opt)
{
  memset(&global_option, 0, sizeof(global_option));
  global_option.type = opt->type;
}

static char* 
ns_to_symbol_name(char *name)
{
  char *buf;
  size_t len;
  FILE *fp = open_memstream(&buf, &len);
  int s, i;
  for (s = 0; s < global_option.stack_top; s++) {
    NTL_T(name_t) ns = global_option.namespace_stack[s];
    for (i = 0; ns[i]; i++)
      fprintf(fp, "%s_", (char *)ns[i]);
  }
  fprintf(fp, "%s", name);
  fclose(fp);
  return buf;
}

static char* 
ns_to_item_name(char *name)
{
  char *buf;
  size_t len;
  FILE *fp = open_memstream(&buf, &len);
  int si, i;
  for (si = 0; si < global_option.stack_top; si++) {
    NTL_T(name_t) ns = global_option.namespace_stack[si];
    for (i = 0; ns[i]; i++)
      fprintf(fp, "%s_", (char *)ns[i]);
  }
  fprintf(fp, "%s", name);
  fclose(fp);
  char *s = buf;
  while (*s) {
    *s = toupper((unsigned char)*s);
    s++;
  }
  return buf;
}

static char* 
get_file_suffix(enum file_type t)
{
  switch(t) {
  case FILE_SINGLE_FILE: return "cc";
  case FILE_DECLARATION: return "hh";
  case FILE_DEFINITION: return "cc";
  case FILE_HEADER: return "hh";
  case FILE_CODE: return "cc";
  default: ERR("Unknown file suffix (code %d)", t);
  }
  return "";
}

enum decor_tag {
  DEC_NONE = 0, /* this has to be zero as the absence means DEC_NONE */
  DEC_POINTER = 1,
  DEC_ARRAY = 2,
  DEC_NTL
};

struct decor {
  enum decor_tag tag;
  char * value;
};

enum type_opcode {
  TYPE_UNDEFINED = 0,
  TYPE_RAW_JSON,
  TYPE_NULL,
  TYPE_EMPTY_STR,
  TYPE_STR,
  TYPE_BOOL,
  TYPE_INT,
  TYPE_DOUBLE
};

struct type_value {
  enum type_opcode opcode;
  union {
    uint64_t ival;
    double dval;
    char *sval;
  } _;
  char *token; /* will be used for conversion */
};

struct jc_type {
  char *base;
  char *int_alias; /* use for enum type names that are represented as int */
  struct decor decor;
  char *converter;
  bool nullable;
  struct type_value default_value;
};

static void
print_type(FILE *fp, struct jc_type *p) {
  fprintf(fp, "base:%s, dec:%d", p->base, p->decor.tag);
}


enum loc {
  LOC_IN_JSON = 0,  /* this has to be zero as the absence means LOC_IN_JSON */
  LOC_IN_QUERY,
  LOC_IN_BODY,
  LOC_IN_URL,
  LOC_IN_MULTIPART
};

struct jc_field {
  struct jc_type type;
  struct type_value inject_condition;
  struct line_and_column lnc;
  bool todo;
  char *name;
  char *json_key;
  enum loc loc;
  char *comment;
  char spec[512];
  bool option;
  bool copy_json_value;
};

static void
print_field(FILE *fp, struct jc_field *p)
{
  if (p->todo)
    fprintf(fp, "/* @todo name: %s */\n", p->name);
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
  bool enum_is_bitwise_flag; \
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
  fprintf(fp, "     '%s' */\n", f->spec);
}

struct jc_definition {
  char *spec_name;
  NTL_T(name_t) incl_headers;
  bool is_disabled;
  char *comment;
  NTL_T(name_t) namespace; /* ntl */
  NTL_T(struct jc_def) defs; /*ntl */
};

static int has_struct(NTL_T(struct jc_def) defs)
{
  int i;
  for (i = 0; defs[i]; i++)
    if (defs[i]->is_struct)
      return 1;
  return 0;
}

static int has_enum(NTL_T(struct jc_def) defs)
{
  int i;
  for (i = 0; defs[i]; i++)
    if (!defs[i]->is_struct)
      return 1;
  return 0;
}

static char* namespace_to_str(NTL_T(name_t) ns)
{
  int i;
  char *buf; size_t len;
  FILE * fp = open_memstream(&buf, &len);

  for(i = 0; ns && ns[i]; i++)
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
  else if (9 == size && 0 == strncmp(json, "multipart", size)) {
    *p = LOC_IN_MULTIPART;
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
  struct sized_buffer t_inject_if_not = {0};
  struct sized_buffer t_default_value = {0};

#if 0
  bool copy_json_value = false;
#endif

  size_t s = json_extract(json, size,
                          "(name):?s,"
                          "(name):lnc,"
                          "(todo):b,"
                          "(json_key):?s,"
#if 0
                          "(type):?s,"
#endif
                          "(type.base):?s,"
                          "(type.int_alias):?s,"
                          "(type.dec):F,"
                          "(type.converter):?s,"
                          "(type.nullable):b,"
                          "(type.default_value):T,"
                          "(option):b,"
                          "(inject_if_not):key,"
                          "(inject_if_not):T,"
                          "(loc):F,"
                          "(comment):?s",
                          &p->name,
                          &p->lnc,
                          &p->todo,
                          &p->json_key,
#if 0
                          &copy_json_value,
#endif
                          &p->type.base,
                          &p->type.int_alias,
                          decor_from_json, &p->type.decor,
                          &p->type.converter,
                          &p->type.nullable,
                          &t_default_value,
                          &p->option,
                          &has_inject_if_not,
                          &t_inject_if_not,
                          loc_from_json, &p->loc,
                          &p->comment);

  snprintf(p->spec, sizeof(p->spec), "%.*s", (int)size, json);
  adjust_lnc(json, &p->lnc);

  if (has_inject_if_not) {
    if (t_inject_if_not.size == 0) {
      p->inject_condition.opcode = TYPE_EMPTY_STR;
    }
    else if (4 == t_inject_if_not.size 
             && 0 == strncmp("null", t_inject_if_not.start, t_inject_if_not.size)) 
    {
      p->inject_condition.opcode = TYPE_NULL;
    }
    else { /* we will convert this to actual type later */
      p->inject_condition.opcode = TYPE_RAW_JSON;
      asprintf(&p->inject_condition.token, 
          "%.*s", (int)t_inject_if_not.size, t_inject_if_not.start);
    }
  }

  if (t_default_value.size != 0) {
    p->type.default_value.opcode = TYPE_RAW_JSON;
    asprintf(&p->type.default_value.token,
        "%.*s", (int)t_default_value.size, t_default_value.start);
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

  int i;
  for (i = 0; i < 4; i++) {
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
               "(struct):lnc,"
               "(bitwise):b",
               &def->comment,
               &def->title,
               extract_ntl_from_json, &d0,
               extract_ntl_from_json, &d0_alias,
               &def->typedef_name,
               &is_struct, &is_enum,
               &def->name, &def->name,
               &def->name_lnc,
               &def->enum_is_bitwise_flag);

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
  global_option.namespace_stack[global_option.stack_top] = p;
  ++global_option.stack_top;
}

static void gen_close_namespace(FILE *fp, NTL_T(name_t) p)
{
  if (NULL == p) return;
  global_option.stack_top--;
  global_option.namespace_stack[global_option.stack_top] = NULL;
}

static void gen_enum(FILE *fp, struct jc_enum *e)
{
  char *t = ns_to_symbol_name(e->name);
  char *t_alias = NULL;
  
  if (e->typedef_name) 
    t_alias = ns_to_symbol_name(e->typedef_name);

  if (e->title)
    fprintf(fp, "/* %s */\n", e->title);
  fprintf(fp, "/* defined at %s:%d:%d */\n",
          spec_name, e->name_lnc.line, e->name_lnc.column);
  fputs("/**\n", fp);
  {
    if (e->comment)
      fprintf(fp, " * @see %s\n *\n", e->comment);
   fprintf(fp, 
       " * @verbatim embed:rst:leading-asterisk\n"
       " * .. container:: toggle\n\n"
       " *   .. container:: header\n\n"
       " *     **Methods**\n\n"
       " *   * :code:`char* %s_print(enum %s code)`\n"
       " *   * :code:`enum %s %s_eval(char *code_as_str)`\n"
       " * @endverbatim\n",
       t, t, 
       t, t);
  }
  fputs(" */\n", fp);

  if (t_alias)
    fprintf(fp, "typedef ");
  fprintf(fp, "enum %s {\n", t);

  int i = 0, prev_value = -1;
  for ( ; e->items && e->items[i]; i++) {
    struct jc_item *item = e->items[i];
    char *item_name = ns_to_item_name(item->name);

    if (item->todo) {
      fprintf(fp, "/* @todo %s %s */\n", item_name, item->comment);
    }
    else {
      fprintf(fp, "  %s", item_name);
      if (item->has_value) {
        fprintf(fp, " = %d", item->value);
        prev_value = item->value;
      }
      else {
        fprintf(fp, " = %d", prev_value + 1);
        prev_value ++;
      }

      if (item->comment)
        fprintf(fp, ", /**< %s */\n", item->comment);
      else
        fprintf(fp, ",\n");
    }
  }
  if (t_alias)
    fprintf(fp, "} %s\n", t_alias);
  else
    fprintf(fp, "};\n");
}

static void gen_enum_eval(FILE *fp, struct jc_enum *e)
{
  char *t = ns_to_symbol_name(e->name);
  char *t_alias = NULL;
  int i;
  
  if (e->typedef_name) 
    t_alias = ns_to_symbol_name(e->typedef_name);

  if (t_alias)
    fprintf(fp, "%s %s_eval(char *s){\n", t_alias, t_alias);
  else
    fprintf(fp, "enum %s %s_eval(char *s){\n", t, t);

  for (i = 0; e->items && e->items[i]; i++) {
    struct jc_item *item = e->items[i];
    char *item_name = ns_to_item_name(item->name);
    if (item->todo)
      fprintf(fp, "/* %s */\n", item->name);
    else
      fprintf(fp, "  if(strcasecmp(\"%s\", s) == 0) return %s;\n", 
              item->name, item_name);
  }
  fprintf(fp, "  ERR(\"'%%s' doesn't match any known enumerator.\", s);\n");
  fprintf(fp, "}\n");
}

static void gen_enum_print(FILE *fp, struct jc_enum *e)
{
  char *t = ns_to_symbol_name(e->name);
  char *t_alias = NULL;
  int i;
  
  if (e->typedef_name) 
    t_alias = ns_to_symbol_name(e->typedef_name);

  if (t_alias)
    fprintf(fp, "char* %s_print(%s v){\n", t_alias, t_alias);
  else
    fprintf(fp, "char* %s_print(enum %s v){\n", t, t);

  fprintf(fp, "\n  switch (v) {\n");
  for (i = 0; e->items && e->items[i]; i++) {
    struct jc_item *item = e->items[i];
    if (item->todo)
      fprintf(fp, "/* %s */\n", item->name);
    else
      fprintf(fp, "  case %s: return \"%s\";\n", 
              ns_to_item_name(item->name), item->name);
  }
  fprintf(fp, "  }\n");

  fprintf(fp, "\n  return NULL;\n");
  fprintf(fp, "}\n");
}

static void gen_forward_fun_declare(FILE *fp, struct jc_def *d);
static void gen_typedef (FILE *fp);
static void gen_default(FILE *fp, struct jc_def *d);
static void gen_wrapper(FILE *fp, struct jc_def *d);

static void gen_enum_all(FILE *fp, struct jc_def *d, name_t **ns)
{
  struct jc_enum *e = (struct jc_enum*)d;

  fprintf(fp, "\n\n");
  gen_open_namespace(fp, ns);
  /* */
  switch (global_option.type) {
  case FILE_DECLARATION:
  case FILE_ENUM_DECLARATION:
  case FILE_HEADER:
      gen_enum(fp, e);
      gen_forward_fun_declare(fp, d);
      break;
  case FILE_CODE:
      gen_typedef(fp);
      gen_wrapper(fp, d);

      gen_enum_eval(fp, e);
      fprintf(fp, "\n");

      gen_enum_print(fp, e);
      fprintf(fp, "\n");

      gen_default(fp, d);
      fprintf(fp, "\n");

      break;
  default:
      break;
  }
  /* */
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
  char *fun_prefix;
  char *pre_dec;
  char *post_dec;
  char *extract_arg_decor;
  char *inject_arg_decor;
  char *extractor;
  char *injector;
  char *alloc;
  char *free;
  bool inject_is_user_def;
  bool extract_is_user_def;
  bool is_actor_alloc;
  bool need_double_quotes;
};

static int to_builtin_action(struct jc_field *f, struct action *act)
{
  char * xend = NULL;
  if (strcmp(f->type.base, "int") == 0) {
    act->extractor = "d";
    act->injector = "d";
#if 0
    act->c_type = f->type.int_alias ? f->type.int_alias : "int";
#endif
    if (f->inject_condition.opcode == TYPE_RAW_JSON) {
      f->inject_condition.opcode = TYPE_INT;
      f->inject_condition._.ival = (uint64_t)strtol(f->inject_condition.token,
                                                    &xend, 10);
      /* @todo check xend */
    }
    if (f->type.default_value.opcode == TYPE_RAW_JSON) {
      f->type.default_value.opcode = TYPE_INT;
      f->type.default_value._.ival = (uint64_t)strtol(f->type.default_value.token,
                                                    &xend, 10);
      /* @todo check xend */
    }
  }
  else if (strcmp(f->type.base, "s_as_u64") == 0) {
    act->extractor = "s_as_u64";
    act->injector = "s_as_u64";
    act->c_type = "uint64_t";
    if (f->inject_condition.opcode == TYPE_RAW_JSON) {
      f->inject_condition.opcode = TYPE_INT;
      f->inject_condition._.ival = (uint64_t)strtoull(f->inject_condition.token,
                                                     &xend, 10);
      /* @todo check xend */
    }
    if (f->type.default_value.opcode == TYPE_RAW_JSON) {
      f->type.default_value.opcode = TYPE_INT;
      f->type.default_value._.ival = (uint64_t)strtoull(f->type.default_value.token,
                                                     &xend, 10);
      /* @todo check xend */
    }
  }
  else if (strcmp(f->type.base, "s_as_hex_uint") == 0) {
    act->extractor = "s_as_hex_uint";
    act->injector = "s_as_hex_uint";
    act->c_type = "unsigned int";
    if (f->type.int_alias) {
      act->c_type = f->type.int_alias;
    }
    if (f->inject_condition.opcode == TYPE_RAW_JSON) {
      f->inject_condition.opcode = TYPE_INT;
      f->inject_condition._.ival = (uint64_t)strtoll(f->inject_condition.token,
                                                     &xend, 10);
      /* @todo check xend */
    }
    if (f->type.default_value.opcode == TYPE_RAW_JSON) {
      f->type.default_value.opcode = TYPE_INT;
      f->type.default_value._.ival = (uint64_t)strtoll(f->type.default_value.token,
                                                     &xend, 10);
      /* @todo check xend */
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
    if (f->inject_condition.opcode == TYPE_RAW_JSON) {
      f->inject_condition.opcode = TYPE_BOOL;
      if (strcmp("true", f->inject_condition.token) == 0) {
        f->inject_condition._.sval = "true";
      }
      else if (strcmp("false", f->inject_condition.token) == 0) {
        f->inject_condition._.sval = "false";
      }
      else {
        ERR("%s is not a bool value\n", f->inject_condition.token);
      }
    }
    if (f->type.default_value.opcode == TYPE_RAW_JSON) {
      f->type.default_value.opcode = TYPE_BOOL;
      if (strcmp("true", f->type.default_value.token) == 0) {
        f->type.default_value._.sval = "true";
      }
      else if (strcmp("false", f->type.default_value.token) == 0) {
        f->type.default_value._.sval = "false";
      }
      else {
        ERR("%s is not a bool value\n", f->type.default_value.token);
      }
    }
  }
  else if (strcmp(f->type.base, "float") == 0) {
    act->extractor = "f";
    act->injector = "f";
    act->c_type = "float";
    if (f->inject_condition.opcode == TYPE_RAW_JSON) {
      f->inject_condition.opcode = TYPE_DOUBLE;
      f->inject_condition._.dval = strtod(f->inject_condition.token, &xend);
      /* @todo check xend */
    }
    if (f->type.default_value.opcode == TYPE_RAW_JSON) {
      f->type.default_value.opcode = TYPE_DOUBLE;
      f->type.default_value._.dval = strtod(f->type.default_value.token, &xend);
      /* @todo check xend */
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
      act->inject_is_user_def = c->inject_is_user_def;
      act->extract_is_user_def = c->extract_is_user_def;
      act->need_double_quotes = c->need_double_quotes;
      act->extractor = c->extractor;
      act->injector = c->injector;
      act->free = c->free;
      act->extract_arg_decor = c->extractor_addrof;
      act->inject_arg_decor = c->injector_addrof;
      act->c_type = c->output_type;
      act->post_dec = "";
      act->pre_dec = "";

      if (f->inject_condition.opcode == TYPE_RAW_JSON) {
        if (strcmp(c->converted_builtin_type, "uint64_t") == 0) {
          f->inject_condition.opcode = TYPE_INT;
          f->inject_condition._.ival = \
            (uint64_t)strtoll(f->inject_condition.token, &xend, 10);
          /* @todo check xend */
        }
        else {
          f->inject_condition.opcode = TYPE_STR;
        }
      }
      if (f->type.default_value.opcode == TYPE_RAW_JSON) {
        if (strcmp(c->converted_builtin_type, "uint64_t") == 0) {
          f->type.default_value.opcode = TYPE_INT;
          f->type.default_value._.ival = \
            (uint64_t)strtoll(f->type.default_value.token, &xend, 10);
          /* @todo check xend */
        }
        else {
          f->type.default_value.opcode = TYPE_STR;
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
  if (f->type.int_alias) {
    act->c_type = f->type.int_alias;
    char *tok = strstr(f->type.int_alias, "enum");
    if (tok != NULL) {
      tok += strlen("enum");
      while (*tok && isspace(*tok)) tok++;
      asprintf(&act->fun_prefix, "%s", tok);
      act->fun_prefix = to_C_name(act->fun_prefix);
    }
    else {
      act->fun_prefix = f->type.int_alias;
    }
  }
  else {
    act->c_type = f->type.base;
    char *tok = strstr(f->type.base, "struct");
    if (tok != NULL) {
      tok += strlen("struct");
      while (*tok && isspace(*tok)) tok++;
      asprintf(&act->fun_prefix, "%s", tok);
      is_user_defined_type = true;
      act->fun_prefix = to_C_name(act->fun_prefix);
    }
    else {
      act->fun_prefix = f->type.base;
    }
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
            asprintf(&act->injector, "%s_to_json", act->fun_prefix);
            asprintf(&act->extractor, "%s_from_json", act->fun_prefix);
            asprintf(&act->alloc, "%s_init", act->fun_prefix);
            asprintf(&act->free, "%s_cleanup", act->fun_prefix);
            act->extract_arg_decor = "&";
            act->inject_arg_decor = "";
            act->post_dec = "";
            act->pre_dec = "*";
            act->inject_is_user_def = true;
            act->extract_is_user_def = true;
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
      act->inject_is_user_def = true;
      act->extract_is_user_def = true;
      act->is_actor_alloc = true;
      if (to_builtin_action(f, act)) {
        asprintf(&act->extractor, "%s_list_from_json", act->fun_prefix);
        asprintf(&act->injector, "%s_list_to_json", act->fun_prefix);
      } else {
        asprintf(&act->extractor, "%s_list_from_json", act->fun_prefix);
        asprintf(&act->injector, "%s_list_to_json", act->fun_prefix);
        asprintf(&act->free, "%s_list_free", act->fun_prefix);
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

  switch(f->type.default_value.opcode) {
  case TYPE_RAW_JSON:
      ERR("(Internal Error) Type is TYPE_RAW_JSON, but should have been converted to a primitive");
      break;
  case TYPE_UNDEFINED: /* do nothing */
  case TYPE_EMPTY_STR:
  default:
      break;
  case TYPE_NULL:
      fprintf(fp, "  p->%s = NULL;\n", act.c_name);
      break;
  case TYPE_BOOL:
      fprintf(fp, "  p->%s = %s;\n", act.c_name, f->type.default_value._.sval);
      break;
  case TYPE_INT:
  case TYPE_DOUBLE:
      fprintf(fp, "  p->%s = %s;\n", act.c_name, f->type.default_value.token);
      break;
      fprintf(fp, "  p->%s = %s;\n", act.c_name, f->type.default_value.token);
      break;
  case TYPE_STR:
      fprintf(fp, "  p->%s = strdup(%s);\n", act.c_name, f->type.default_value.token);
      break;
  }
}

static void gen_init (FILE *fp, struct jc_struct *s)
{
  char *t = ns_to_symbol_name(s->name);
  int i;
  fprintf(fp, "void %s_init(struct %s *p) {\n", t, t);
  fprintf(fp, "  memset(p, 0, sizeof(struct %s));\n", t);
  for (i = 0; s->fields && s->fields[i]; i++) {
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_field_init(NULL, fp, s->fields[i]);
    fprintf(fp, "\n");
  }

  fprintf(fp, "}\n");
}

static bool is_disabled_method(struct jc_def *d, char *name)
{
  int i;
  for (i = 0; d->disable_methods && d->disable_methods[i]; i++)
    if (strcmp(name, (char *)d->disable_methods[i]) == 0)
      return true;
  return false;
}

static void gen_default(FILE *fp, struct jc_def *d)
{
  char * type = ns_to_symbol_name(d->name);

  char extractor[256], injector[256], cleanup[256];
  char * prefix;
  if (d->is_struct) {
    gen_init(fp, (struct jc_struct*)d);
    snprintf(extractor, sizeof(extractor), "%s_from_json_v", type);
    snprintf(injector, sizeof(injector), "%s_to_json_v", type);
    snprintf(cleanup, sizeof(cleanup), "(vfvp)%s_cleanup", type);
    prefix = "struct";
  }
  else {
    snprintf(extractor, sizeof(extractor), "ja_u64_from_json_v");
    snprintf(injector, sizeof(injector), "ja_u64_to_json_v");
    snprintf(cleanup, sizeof(cleanup), "NULL");
    prefix = "enum";
  }

  fprintf(fp, "void %s_list_free(%s %s **p) {\n", type, prefix, type);
  fprintf(fp, "  ntl_free((void**)p, %s);\n", cleanup);
  fprintf(fp, "}\n\n");

  if (!is_disabled_method(d, "from_json")) {
    fprintf(fp, "void %s_list_from_json(char *str, size_t len, %s %s ***p)\n",
            type, prefix, type);
    fprintf(fp, "{\n");
    fprintf(fp, "  struct ntl_deserializer d;\n");
    fprintf(fp, "  memset(&d, 0, sizeof(d));\n");
    fprintf(fp, "  d.elem_size = sizeof(%s %s);\n", prefix, type);
    fprintf(fp, "  d.init_elem = NULL;\n");
    fprintf(fp, "  d.elem_from_buf = %s;\n", extractor);
    fprintf(fp, "  d.ntl_recipient_p= (void***)p;\n");
    fprintf(fp, "  extract_ntl_from_json2(str, len, &d);\n");
    fprintf(fp, "}\n\n");
  }

  if (!is_disabled_method(d, "to_json")) {
    fprintf(fp, "size_t %s_list_to_json(char *str, size_t len, %s %s **p)\n",
            type, prefix, type);
    fprintf(fp, "{\n");
    fprintf(fp, "  return ntl_to_buf(str, len, (void **)p, NULL, %s);\n",
            injector);
    fprintf(fp, "}\n");
  }
}

static void emit_field_cleanup(void *cxt, FILE *fp, struct jc_field *f)
{
  struct action act = {0};
  to_action(f, &act);

  if (act.todo)
    fprintf(fp, "  /* @todo p->%s */\n", act.c_name);
  else if (act.free) {
    if (strstr(act.free, "_cleanup"))
      fprintf(fp, "  if (d->%s) {\n"
                  "    %s(d->%s);\n"
                  "    free(d->%s);\n"
                  "  }\n",
                  act.c_name, act.free, act.c_name, act.c_name);
    else
      fprintf(fp, "  if (d->%s)\n"
                  "    %s(d->%s);\n",
                  act.c_name, act.free, act.c_name);
  } 
  else
    fprintf(fp, "  /* p->%s is a scalar */\n", act.c_name);
}

static void gen_cleanup(FILE *fp, struct jc_struct *s)
{
  char *t = ns_to_symbol_name(s->name);
  int i;
  fprintf(fp, "void %s_cleanup(struct %s *d) {\n", t, t);
  for (i = 0; s->fields && s->fields[i]; i++) {
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
    fprintf(fp, "  /* @todo %s %s; */\n", f->name, f->comment);
  }
  else if (f->comment)
    fprintf(fp, "  %s %s%s%s; /**< %s */\n",
            act.c_type, act.pre_dec, act.c_name, act.post_dec, f->comment);
  else
    fprintf(fp, "  %s %s%s%s;\n",
            act.c_type, act.pre_dec, act.c_name, act.post_dec);
}

static void emit_json_extractor(void *cxt, FILE *fp, struct jc_field *f, bool last_arg)
{
  char *strend = !last_arg ? "\n" : ",\n";

  struct action act = {0};
  to_action(f, &act);
  if (act.todo) return;

  if (act.extract_is_user_def)
    fprintf(fp, "                \"(%s):F,\"%s", act.json_key, strend);
  else
    fprintf(fp, "                \"(%s):%s,\"%s", act.json_key, act.extractor, strend);
}

static void emit_json_extractor_arg(void *cxt, FILE *fp, struct jc_field *f, bool last_arg)
{
  char *strend = !last_arg ? ",\n" : ");\n";

  struct action act = {0};
  to_action(f, &act);
  if (act.todo) return;

  if (act.extract_is_user_def) {
    if (act.is_actor_alloc)
      fprintf(fp, "                %s, &p->%s%s",
              act.extractor, act.c_name, strend);
    else
      fprintf(fp, "                %s, %sp->%s%s",
              act.extractor, act.extract_arg_decor, act.c_name, strend);
  }
  else
    fprintf(fp, "                %sp->%s%s",
            act.extract_arg_decor, act.c_name, strend);
}

static void gen_from_json(FILE *fp, struct jc_struct *s)
{
  char *t = ns_to_symbol_name(s->name);
  size_t fields_amt = ntl_length((ntl_t)s->fields);
  int i;

  if (is_disabled_method((struct jc_def*)s, "from_json")) {
    fprintf(fp, "\n/* This method is disabled at %s:%d:%d */\n",
            spec_name,
            s->disable_methods_lnc.line,
            s->disable_methods_lnc.column);
    return;
  }

  fprintf(fp, "void %s_from_json(char *json, size_t len, struct %s **pp)\n",
          t, t);

  fprintf(fp, "{\n");
  fprintf(fp, "  static size_t ret=0; /**< used for debugging */\n");
  fprintf(fp, "  size_t r=0;\n");
  fprintf(fp, "  if (!*pp) *pp = malloc(sizeof **pp);\n");
  fprintf(fp, "  struct %s *p = *pp;\n", t);
  fprintf(fp, "  %s_init(p);\n", t);
  fprintf(fp, "  r=json_extract(json, len, \n");

#ifdef JSON_STRUCT_METADATA
  for (i = 0; i < fields_amt; i++) {
    if (s->fields[i]->loc != LOC_IN_JSON)
      continue;
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_json_extractor(NULL, fp, s->fields[i], false);
  }
  fprintf(fp, "                \"@record_defined\"\n");
  fprintf(fp, "                \"@record_null\",\n");

  for (i = 0; i < fields_amt; i++) {
    if (s->fields[i]->loc != LOC_IN_JSON)
      continue;
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_json_extractor_arg(NULL, fp, s->fields[i], false);
  }
  fprintf(fp, "                p->__M.record_defined,"
    " sizeof(p->__M.record_defined),\n");
  fprintf(fp, "                p->__M.record_null,"
    " sizeof(p->__M.record_null));\n");
#else
  for (i = 0; i < fields_amt-1; i++) {
    if (s->fields[i]->loc != LOC_IN_JSON)
      continue;
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_json_extractor(NULL, fp, s->fields[i], false);
  }
  emit_field_spec(NULL, fp, s->fields[i]);
  emit_json_extractor(NULL, fp, s->fields[i], true);

  for (i = 0; i < fields_amt-1; i++) {
    if (s->fields[i]->loc != LOC_IN_JSON)
      continue;
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_json_extractor_arg(NULL, fp, s->fields[i], false);
  }
  emit_field_spec(NULL, fp, s->fields[i]);
  emit_json_extractor_arg(NULL, fp, s->fields[i], true);
#endif
  fprintf(fp, "  ret = r;\n");
  fprintf(fp, "}\n");
}

static void emit_inject_setting(void *cxt, FILE *fp, struct jc_field *f)
{
  struct action act = {0};
  to_action(f, &act);
  if (act.todo) return;

  int i = *(int *)cxt;

  switch(f->inject_condition.opcode) {
  case TYPE_RAW_JSON:
      ERR("(Internal Error) Type is TYPE_RAW_JSON, but should have been converted to a primitive");
      break;
  default:
      break;
  case TYPE_UNDEFINED:
      fprintf(fp, "  arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
  case TYPE_NULL:
      fprintf(fp, "  if (p->%s != NULL)\n", act.c_name);
      fprintf(fp, "    arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
  case TYPE_BOOL:
      fprintf(fp, "  if (p->%s != %s)\n", act.c_name,
              f->inject_condition._.sval);
      fprintf(fp, "    arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
  case TYPE_INT:
      fprintf(fp, "  if (p->%s != %s)\n", act.c_name,
              f->inject_condition.token);
      fprintf(fp, "    arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
  case TYPE_DOUBLE:
      fprintf(fp, "  if (p->%s != %s)\n", act.c_name,
              f->inject_condition.token);
      fprintf(fp, "    arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
  case TYPE_STR:
      fprintf(fp, "  if (strcmp(p->%s, %s) != 0)\n", act.c_name,
              f->inject_condition.token);
      fprintf(fp, "    arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
  case TYPE_EMPTY_STR:
      if (f->type.decor.tag == DEC_POINTER)
        fprintf(fp, "  if (p->%s && *p->%s)\n", act.c_name, act.c_name);
      else
        fprintf(fp, "  if (*p->%s)\n", act.c_name);

      fprintf(fp,   "    arg_switches[%d] = %sp->%s;\n",
              i, act.inject_arg_decor, act.c_name);
      break;
  }
}

static void emit_json_injector(void *cxt, FILE *fp, struct jc_field *f)
{
  struct action act = {0};
  to_action(f, &act);
  if (act.todo) return;

  if (act.inject_is_user_def)
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

  if (act.inject_is_user_def)
    fprintf(fp, "                %s, %sp->%s,\n",
            act.injector, act.inject_arg_decor, act.c_name);
  else
    fprintf(fp, "                %sp->%s,\n",
            act.inject_arg_decor, act.c_name);
}

static void gen_to_json(FILE *fp, struct jc_struct *s)
{
  char *t = ns_to_symbol_name(s->name);
  size_t fields_amt = ntl_length((ntl_t)s->fields);
  int i;

  if (is_disabled_method((struct jc_def*)s, "to_json")) {
    fprintf(fp, "\n/* This method is disabled at %s:%d:%d */\n",
            spec_name,
            s->disable_methods_lnc.line,
            s->disable_methods_lnc.column);
    return;
  }

  fprintf(fp, "size_t %s_to_json(char *json, size_t len, struct %s *p)\n",
          t, t);
  fprintf(fp, "{\n");
  fprintf(fp, "  size_t r;\n");
  fprintf(fp, "  void *arg_switches[%zu]={NULL};\n", fields_amt);
  for (i = 0; i < fields_amt; i++) {
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_inject_setting(&i, fp, s->fields[i]);
    fprintf(fp, "\n");
  }
  fprintf(fp, "  r=json_inject(json, len, \n");

  for (i = 0; i < fields_amt; i++) {
    if (s->fields[i]->loc != LOC_IN_JSON)
      continue;
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_json_injector(NULL, fp, s->fields[i]);
  }

  fprintf(fp, "                \"@arg_switches:b\",\n");

  for (i = 0; i < fields_amt; i++) {
    if (s->fields[i]->loc != LOC_IN_JSON)
      continue;
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_json_injector_arg(NULL, fp, s->fields[i]);
  }

  fprintf(fp, "                arg_switches, "
    "sizeof(arg_switches),"
    " true);\n");
  fprintf(fp, "  return r;\n");
  fprintf(fp, "}\n");
}

static void gen_to_query(FILE *fp, struct jc_struct *s)
{
  return;

  char *t = ns_to_symbol_name(s->name);
  size_t fields_amt = ntl_length((ntl_t)s->fields);
  int i;
  bool has_query = false;
  for (i = 0; s->fields && s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    if (f->loc != LOC_IN_QUERY)
      continue;
    has_query = true;
  }


  fprintf(fp, "size_t %s_to_query(char *json, size_t len, struct %s* p)\n",
          t, t);
  fprintf(fp, "{\n");
  if (!has_query) {
    fprintf(fp,  "  return r;\n");
    fprintf(fp, "}\n");
    return;
  }
  fprintf(fp, "  size_t r = 0;\n");
  fprintf(fp, "  void *arg_switches[%zu]={NULL};\n", fields_amt);
  for (i = 0; i < fields_amt; i++) {
    emit_field_spec(NULL, fp, s->fields[i]);
    emit_inject_setting(&i, fp, s->fields[i]);
    fprintf(fp, "\n");
  }
  fprintf(fp, "  r = query_inject(json, len, \n");

  
  for (i = 0; i < fields_amt; i++) {
    struct jc_field *f = s->fields[i];
    if (f->loc != LOC_IN_QUERY)
      continue;

    struct action act = {0};
    to_action(f, &act);
    if (act.todo) continue;
    fprintf(fp, "                \"(%s):%s\"\n", f->name, act.injector);
  }
  fprintf(fp, "                \"@arg_switches:b\",\n");

  for (i = 0; i < fields_amt; i++) {
    struct jc_field *f = s->fields[i];
    if (f->loc != LOC_IN_QUERY)
      continue;

    struct action act = {0};
    to_action(f, &act);
    if (act.todo) continue;

    fprintf(fp, "                %sp->%s,\n", act.inject_arg_decor, act.c_name);
  }
  fprintf(fp, "                arg_switches,"
    " sizeof(arg_switches),"
    " true;\n");
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
    fprintf(fp, "/* %s */\n", s->title);
  fprintf(fp, "/* defined at %s:%d:%d */\n",
          spec_name, s->name_lnc.line, s->name_lnc.column);
  fputs("/**\n", fp);
  {
    if (s->comment)
      fprintf(fp, " * @see %s\n *\n", s->comment);
   fprintf(fp, 
       " * @verbatim embed:rst:leading-asterisk\n"
       " * .. container:: toggle\n\n"
       " *   .. container:: header\n\n"
       " *     **Methods**\n\n"
       " *   * Initializer:\n\n"
       " *     * :code:`void %s_init(struct %s *)`\n"
       " *   * Cleanup:\n\n"
       " *     * :code:`void %s_cleanup(struct %s *)`\n"
       " *     * :code:`void %s_list_free(struct %s **)`\n"
       " *   * JSON Decoder:\n\n"
       " *     * :code:`void %s_from_json(char *rbuf, size_t len, struct %s **)`\n"
       " *     * :code:`void %s_list_from_json(char *rbuf, size_t len, struct %s ***)`\n"
       " *   * JSON Encoder:\n\n"
       " *     * :code:`void %s_to_json(char *wbuf, size_t len, struct %s *)`\n"
       " *     * :code:`void %s_list_to_json(char *wbuf, size_t len, struct %s **)`\n"
       " * @endverbatim\n",
       t, t,        /* Initializer */
       t, t, t, t,  /* Cleanup */
       t, t, t, t,  /* JSON Decoder */
       t, t, t, t); /* JSON Encoder */
  }
  fputs(" */\n", fp);

  if (t_alias)
    fprintf(fp, "typedef ");
  fprintf(fp, "struct %s {\n", t);

  int i;
  for (i=0; s->fields && s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    emit_field_spec(NULL, fp, f);
    emit_field(NULL, fp, f);
    fprintf(fp, "\n");
  }
#ifdef JSON_STRUCT_METADATA
  fprintf(fp, "  /* The following is metadata used to \n");
  fprintf(fp, "     1. control which field should be extracted/injected\n");
  fprintf(fp, "     2. record which field is presented(defined) in JSON\n");
  fprintf(fp, "     3. record which field is null in JSON */\n");
  fputs("/** @cond DOXYGEN_SHOULD_SKIP_THIS */\n", fp);
  fprintf(fp, "  struct {\n");
  fprintf(fp, "    bool enable_record_defined;\n");
  fprintf(fp, "    bool enable_record_null;\n");
  fprintf(fp, "    void *record_defined[%d];\n", i);
  fprintf(fp, "    void *record_null[%d];\n", i);
  fprintf(fp, "  } __M; /**< metadata */\n");
  fputs("/** @endcond */\n", fp);
#endif
  if (t_alias)
    fprintf(fp, "} %s;\n", t_alias);
  else  
    fprintf(fp, "};\n");
}

static void gen_wrapper(FILE *fp, struct jc_def *d)
{
  char *t = ns_to_symbol_name(d->name);

  char * prefix;
  if (d->is_struct) 
  {
      prefix = "struct";
      fprintf(fp, "void %s_cleanup_v(void *p) {\n"
                  "  %s_cleanup((struct %s *)p);\n"
                  "}\n\n", t, t, t);

      fprintf(fp, "void %s_init_v(void *p) {\n"
                  "  %s_init((struct %s *)p);\n"
                  "}\n\n", t, t, t);


      if (!is_disabled_method(d, "from_json")) {
        fprintf(fp, "void %s_from_json_v(char *json, size_t len, void *pp) {\n"
                    " %s_from_json(json, len, (struct %s**)pp);\n"
                    "}\n\n", t, t, t);
      }
      if (!is_disabled_method(d, "to_json")) {
        fprintf(fp, "size_t %s_to_json_v(char *json, size_t len, void *p) {\n"
                    "  return %s_to_json(json, len, (struct %s*)p);\n"
                    "}\n\n", t, t, t);
      }
  }
  else {
      prefix = "enum";
  }

  fprintf(fp, "void %s_list_free_v(void **p) {\n"
              "  %s_list_free((%s %s**)p);\n"
              "}\n\n", t, t, prefix, t);

  if (!is_disabled_method(d, "from_json")) {
    fprintf(fp, "void %s_list_from_json_v(char *str, size_t len, void *p) {\n"
                "  %s_list_from_json(str, len, (%s %s ***)p);\n"
                "}\n\n", t, t, prefix, t);
  }
  if (!is_disabled_method(d, "to_json")) {
    fprintf(fp, "size_t %s_list_to_json_v(char *str, size_t len, void *p){\n"
                "  return %s_list_to_json(str, len, (%s %s **)p);\n"
                "}\n\n", t, t, prefix, t);
  }
}

static void gen_forward_fun_declare(FILE *fp, struct jc_def *d)
{
  char *t = ns_to_symbol_name(d->name);

  char * prefix;
  if (d->is_struct) 
  {
      prefix = "struct";

      fprintf(fp, "extern void %s_cleanup_v(void *p);\n", t);
      fprintf(fp, "extern void %s_cleanup(struct %s *p);\n", t, t);

      fprintf(fp, "extern void %s_init_v(void *p);\n", t);
      fprintf(fp, "extern void %s_init(struct %s *p);\n", t, t);

      if (!is_disabled_method(d, "from_json")) {
        fprintf(fp, "extern void %s_from_json_v(char *json, size_t len, void *pp);\n", t);
        fprintf(fp, "extern void %s_from_json(char *json, size_t len, struct %s **pp);\n",
                t, t);
      }

      if (!is_disabled_method(d, "to_json")) {
        fprintf(fp, "extern size_t %s_to_json_v(char *json, size_t len, void *p);\n", t);
        fprintf(fp, "extern size_t %s_to_json(char *json, size_t len, struct %s *p);\n",
                t, t);
      }
#if 0
      fprintf(fp, "extern size_t %s_to_query_v(char *json, size_t len, void *p);\n", t);
      fprintf(fp, "extern size_t %s_to_query(char *json, size_t len, struct %s *p);\n",
              t, t);
#endif
  }
  else {
      prefix = "enum";
      char *t_alias = NULL;
      if (d->typedef_name)
        t_alias = ns_to_symbol_name(d->typedef_name);

      if (t_alias) {
        fprintf(fp, "extern char* %s_print(%s);\n", t_alias, t_alias);
        fprintf(fp, "extern %s %s_eval(char*);\n", t_alias, t_alias);
      }
      else {
        fprintf(fp, "extern char* %s_print(enum %s);\n", t, t);
        fprintf(fp, "extern enum %s %s_eval(char*);\n", t, t);
      }
  }

  fprintf(fp, "extern void %s_list_free_v(void **p);\n", t);
  fprintf(fp, "extern void %s_list_free(%s %s **p);\n", t, prefix, t);

  if (!is_disabled_method(d, "from_json")) {
    fprintf(fp, "extern void %s_list_from_json_v(char *str, size_t len, void *p);\n", t);
    fprintf(fp, "extern void %s_list_from_json(char *str, size_t len, %s %s ***p);\n", t, prefix, t);
  }

  if (!is_disabled_method(d, "to_json")) {
    fprintf(fp, "extern size_t %s_list_to_json_v(char *str, size_t len, void *p);\n", t);
    fprintf(fp, "extern size_t %s_list_to_json(char *str, size_t len, %s %s **p);\n", t, prefix, t);
  }
}

static void gen_typedef (FILE *fp)
{
  fprintf(fp, "typedef void (*vfvp)(void *);\n");
  fprintf(fp, "typedef void (*vfcpsvp)(char *, size_t, void *);\n");
  fprintf(fp, "typedef size_t (*sfcpsvp)(char *, size_t, void *);\n");
}

static void gen_opaque_struct(FILE *fp, struct jc_def *d, name_t **ns)
{
  struct jc_struct *s = (struct jc_struct*)d;
  fprintf(fp, "\n");
  gen_open_namespace(fp, ns);

  char *t = ns_to_symbol_name(s->name);

  fprintf(fp, "/* defined at %s:%d:%d */\n",
          spec_name, s->name_lnc.line, s->name_lnc.column);
  fputs("/**\n", fp);
  {
    if (s->title)
      fprintf(fp, " * @brief %s\n *\n", s->title);
    if (s->comment)
      fprintf(fp, " * @see %s\n", s->comment);
  }
  fputs(" */\n", fp);

  fprintf(fp, "struct %s;\n", t);

  gen_close_namespace(fp, ns);
}

static void gen_struct_all(FILE *fp, struct jc_def *d, name_t **ns)
{
  struct jc_struct *s = (struct jc_struct*)d;

  fprintf(fp, "\n");
  gen_open_namespace(fp, ns);
  switch (global_option.type) {
  case FILE_STRUCT_DECLARATION:
      gen_struct(fp, s);
      break;
  case FILE_FUN_DECLARATION:
      gen_forward_fun_declare(fp, d);
      break;
  case FILE_HEADER: 
  case FILE_DECLARATION:
      gen_struct(fp, s);
      gen_forward_fun_declare(fp, d);
      break;
  case FILE_SINGLE_FILE:
      gen_struct (fp, s);
      gen_forward_fun_declare(fp, d);

      gen_from_json(fp, s);
      fprintf(fp, "\n");

      gen_to_json(fp, s);
      fprintf(fp, "\n");

      gen_to_query(fp, s);
      fprintf(fp, "\n");

      /* boilerplate */
      gen_typedef(fp);
      gen_wrapper(fp, d);
      gen_cleanup(fp, s);
      fprintf(fp, "\n");
      gen_default(fp, d);
      fprintf(fp, "\n");
      break;
  default:
      gen_from_json(fp, s);
      fprintf(fp, "\n");

      gen_to_json(fp, s);
      fprintf(fp, "\n");

      gen_to_query(fp, s);
      fprintf(fp, "\n");

      /* boilerplate */
      gen_typedef(fp);
      gen_wrapper(fp, d);
      fprintf(fp, "\n");
      gen_cleanup(fp, s);
      fprintf(fp, "\n");
      gen_default(fp, d);
      fprintf(fp, "\n");
      break;
  }
  gen_close_namespace(fp, ns);
}

static void 
gen_all_ns(
  FILE *fp, 
  struct jc_def *def,
  void (g)(FILE *, struct jc_def *, name_t **))
{
  int i;
  g(fp, def, def->namespace);
  if (def->namespaces) {
    for (i = 0; def->namespaces[i]; i++)
      g(fp, def, *(def->namespaces[i]));
  }
}

static void 
gen_def(FILE *fp, struct jc_def *def)
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
    gen_all_ns(fp, def, gen_enum_all);
  }
}

static void
gen_definition(char *fname, char *openmode, struct emit_option * option, struct jc_definition *d)
{
  if (strchr(openmode, 'a') && access(fname, F_OK) != 0)
    openmode = "w"; /* first time creating this file */

  FILE *fp = fname ? fopen(fname, openmode) : stderr;
  VASSERT_S(fp != NULL, "Expected file '%s', but it doesn't exist", fname);

  init_emit_option(option);
  if (d->is_disabled) return;

  init_converters(); /* @todo move it out of this function. */

  if (d->spec_name) {
    fprintf(fp, 
      "/* This file is generated from %s, Please don't edit it. */\n",
      d->spec_name);
  }

  if (strchr(openmode, 'w')) {
    fprintf(fp, 
        "/**\n"
        " * @file %s\n"
        " * @see %s\n"
        " */\n\n",
        fname, d->comment);
  }

  if (FILE_SINGLE_FILE == global_option.type
      || FILE_CODE == global_option.type)
  {
    int i;

    fputs(SPECS_DEPS_H, fp);
    if (d->incl_headers)
      for (i=0; d->incl_headers[i]; ++i)
        fprintf(fp, "#include \"%s\"\n", (char*)d->incl_headers[i]);
  }

  gen_open_namespace(fp, d->namespace);
  ntl_apply(fp, (ntl_t)d->defs, (vvpvp)gen_def);
  gen_close_namespace(fp, d->namespace);

  if (fname)
    fclose(fp);
}

static void
gen_definition_list(
  char *folder,
  struct emit_option *opt,
  NTL_T(struct jc_definition) ntl)
{
  char *fname=NULL;
  int i;
  for (i = 0; ntl && ntl[i]; i++) {
    struct jc_definition *d = ntl[i];
    char *f = namespace_to_str(d->namespace);
    asprintf(&fname, "%s/%s%s", folder, f, get_file_suffix(global_option.type));
    gen_definition(fname, "w", opt, d);
  }
}

static char*
field_to_string(
  void *cxt,
  void (*emitter)(void *cxt, FILE *fp, struct jc_field *),
  struct jc_field *f)
{
  char * buf = NULL; size_t len;
  FILE *fp = open_memstream(&buf, &len);
  emitter(cxt, fp, f);
  fclose(fp);
  if (len == 0 && buf) {
    free(buf);
    buf = NULL;
  }
  return buf;
}
