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
 * <definition> := { <namespace> <struct-list> }
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
 *                              <user-defined-conversion>?
 *                            }
 *
 * <user-defined-conversion> := "U":<string>
 * <field-loc>   :=  "loc"  : ("json" | "query" | "body")
 *
 */

enum file_type {
  FILE_SINGLE_FILE = 0,
  FILE_DECLARATION = 1,
  FILE_HEADER,
  FILE_CODE
};
static enum file_type file_type = FILE_SINGLE_FILE;

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
  char *U; // NULL means using builtin converter.
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
  char *name;
  char *c_name;
  struct jc_type type;
  enum loc loc;
  char * comment;
};

static void
print_field(FILE *fp, struct jc_field *p)
{
  fprintf(fp, "name:%s, ", p->name);
  if (p->c_name)
    fprintf(fp, "c-name:%s, ", p->c_name);

  print_type(fp, &p->type);
  fprintf(fp, ", loc:%d\n", p->loc);
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

struct jc_definition {
  char *comment;
  char **namespace; // ntl
  struct jc_struct **structs; //ntl
};

static void
print_definition(FILE *fp, struct jc_definition *p)
{
  fprintf(fp, "/*\n %s  */\n", p->comment);
  fprintf(fp, "namespace: ");
  ntl_apply(fp, (void**)p->namespace, fprintf);
  fprintf(fp, "\n");
  ntl_apply(fp, (void**)p->structs, print_struct);
}

static size_t
loc_from_json(char *json, size_t size, enum loc *p)
{
  if (4 == size && 0 == strncmp(json, "json", 4)) {
    *p = LOC_IN_JSON;
  }
  else if (5 == size && 0 == strncmp(json, "query", 5)) {
    *p = LOC_IN_QUERY;
  }
  else if (4 == size && 0 == strncmp(json, "body", 4)) {
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
  else if (3 == size && 0 == strncmp(json, "ntl", 3)) {
    p->tag = DEC_NTL;
  }
  else if (4 == size && 0 == strncmp(json, "none", 4)) {
    p->tag = DEC_NONE;
  }
  else if (7 == size && 0 == strncmp(json, "pointer", 7)) {
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
                          "(name):?s"
                          "(c_name):?s"
                          "(type.base):?s"
                          "(type.c_base):?s"
                          "(type.dec):F"
                          "(type.U):?s"
                          "(loc):F"
                          "(comment):?s",
                          &p->name,
                          &p->c_name,
                          &p->type.base,
                          &p->type.c_base,
                          dec_from_json, &p->type.dec,
                          &p->type.U,
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
    .elem_size = sizeof(struct jc_field),
    .elem_from_buf = struct_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (void ***)&(s->structs)
  };

  size_t ret = json_extract(json, size,
                            "(comment):?s"
                            "(namespace):F"
                            "(structs):F",
                            &s->comment,
                            orka_str_to_ntl, &d1,
                            orka_str_to_ntl, &d2);
  return ret;
}

static void
gen_default(FILE *fp, char *type)
{
  fprintf(fp, "void %s_init(struct %s *p) {\n", type, type);
  fprintf(fp, "  memset(p, 0, sizeof(struct %s));\n", type);
  fprintf(fp, "}\n");

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

struct action {
  char *c_name;
  char *c_type;
  char *pre_dec;
  char *post_dec;
  char *extract_addrof;
  char *inject_addrof;
  char *extract_spec;
  char *inject_spec;
  char *free;
  bool is_user_def;
};

static int to_builtin_action(struct jc_field *f, struct action *act)
{
  if (strcmp(f->type.base, "int") == 0) {
    act->extract_spec = "d";
    act->inject_spec = "d";
    act->c_type = f->type.c_base ? f->type.c_base : "int";
  }
  else if (strcmp(f->type.base, "u64") == 0) {
    act->extract_spec = "u64";
    act->inject_spec = "u64";
    act->c_type = "uint64_t";
  }
  else if (strcmp(f->type.base, "uint64_t") == 0) {
    act->extract_spec = "u64";
    act->inject_spec = "u64";
    act->c_type = "uint64_t";
  }
  else if (strcmp(f->type.base, "int64_t") == 0) {
    act->extract_spec = "i64";
    act->inject_spec = "i64";
  }
  else if (strcmp(f->type.base, "bool") == 0) {
    act->extract_spec = "b";
    act->inject_spec = "b";
    act->c_type = "bool";
  }
  else {
    fprintf(stderr, "unknown %s\n", f->type.base);
    return 0;
  }
  return 1;
}

static void
to_action(struct jc_field *f, struct action *act)
{
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
        act->inject_spec = "s";
        act->extract_spec = "?s";
        act->extract_addrof = "&";
        act->inject_addrof = "&";
        act->post_dec = "";
        act->pre_dec = "*";
        act->free = "free";
        act->c_type = "char";
        return;
      } else {
        char *tok = strrchr(f->type.base, ':');
        if (tok != NULL) {
          asprintf(&act->inject_spec, "%s_to_json", f->type.base);
          asprintf(&act->extract_spec, "%s_from_json", f->type.base);
          asprintf(&act->free, "%s_free", f->type.base);
          act->extract_addrof = "";
          act->inject_addrof = "";
          act->post_dec = "";
          act->pre_dec = "*";
          act->is_user_def = true;
        }
      }
      break;
    case DEC_NONE:
      act->extract_addrof = "&";
      act->inject_addrof = "&";
      if (!to_builtin_action(f, act)) {
        ERR("unknown %s\n", f->type.base);
      }
      break;
    case DEC_NTL:
      act->extract_addrof = "&";
      act->inject_addrof = "";
      if (to_builtin_action(f, act)) {
        act->free = "free";
      } else {
        act->is_user_def = true;
        asprintf(&act->extract_spec, "%s_list_from_json", f->type.base);
        asprintf(&act->inject_spec, "%s_list_to_json", f->type.base);
        asprintf(&act->free, "%s_list_free", f->type.base);
      }
      break;
    case DEC_ARRAY:
      if (strcmp(f->type.base, "char") == 0) {
        act->inject_spec = "s";
        act->extract_spec = "s";
        act->extract_addrof = "";
        act->inject_addrof = "";
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

static void gen_cleanup(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  fprintf(fp, "void %s_cleanup(struct %s *d) {\n", t, t);
  for (int i = 0; s->fields[i]; i++)
  {
    struct jc_field *f = s->fields[i];
    struct action act = {0};
    to_action(f, &act);

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
  if (f->comment)
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
  fprintf(fp, "  json_extract(json, len, \n");
  int n = ntl_length((void**)s->fields);
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field *f= s->fields[i];
    struct action act = {0};
    to_action(f, &act);

    if (act.is_user_def)
      fprintf(fp, "                \"(%s):F,\"\n", act.c_name);
    else
      fprintf(fp, "                \"(%s):%s,\"\n", act.c_name, act.extract_spec);

    if (i == n-1)
      fprintf(fp, "                \"@A:b\",\n");
  }

  for (int i = 0; s->fields[i]; i++) {
    struct jc_field *f= s->fields[i];
    struct action act = {0};
    to_action(f, &act);
    if (act.is_user_def)
      fprintf(fp, "                %s, &p->%s,\n", act.extract_spec, act.c_name);
    else
      fprintf(fp, "                %sp->%s,\n", act.extract_addrof, act.c_name);
    if (i == n-1) {
      fprintf(fp, "                p->__metadata.A, sizeof(p->__metadata.A),"
        " &p->__metadata.enable_A,\n");
      fprintf(fp, "                p->__metadata.D, sizeof(p->__metadata.D));\n");
    }
  }
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

  int n = ntl_length((void**)s->fields);
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    struct action act = {0};
    to_action(f, &act);
    if (act.is_user_def)
      fprintf(fp, "                \"(%s):F,\"\n", act.c_name);
    else
      fprintf(fp, "                \"(%s):%s,\"\n", act.c_name, act.inject_spec);
    if (i == n-1) {
      fprintf(fp, "                \"@A:b\",\n");
    }
  }

  for (int i = 0; i < n; i++) {
    struct jc_field *f = s->fields[i];
    struct action act = {0};
    to_action(f, &act);
    if (act.is_user_def)
      fprintf(fp, "                %s, p->%s,\n", act.inject_spec, act.c_name);
    else
      fprintf(fp, "                %sp->%s,\n", act.inject_addrof, act.c_name);

    if (i == n-1) {
      fprintf(fp, "                p->__metadata.A, sizeof(p->__metadata.A),"
        " &p->__metadata.enable_A);\n");
    }
  }
  fprintf(fp, "  return r;\n");
  fprintf(fp, "}\n");
}

static void gen_to_query(FILE *fp, struct jc_struct *s)
{
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

  int n = ntl_length((void**)s->fields);
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field *f = s->fields[i];
    if (f->loc != LOC_IN_QUERY)
      continue;

    struct action act = {0};
    to_action(f, &act);
    fprintf(fp, "                \"(%s):%s\"\n", f->name, act.inject_spec);
    if (i == n-1) {
      fprintf(fp, "                \"@A:b\",\n");
    }
  }

  for (int i = 0; i < n; i++) {
    struct jc_field *f = s->fields[i];
    if (f->loc != LOC_IN_QUERY)
      continue;

    struct action act = {0};
    to_action(f, &act);
    fprintf(fp, "                %sp->%s,\n", act.inject_addrof, f->name);
    if (i == n-1) {
      fprintf(fp, "                p->__metadata.A, sizeof(p->__metadata.A),"
        " &p->__metadata.enable_A);\n");
    }
  }
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
  fprintf(fp, "    bool enable_A;\n");
  fprintf(fp, "    bool enable_N;\n");
  fprintf(fp, "    void *A[%d];\n", i);
  fprintf(fp, "    void *N[%d];\n", i);
  fprintf(fp, "    void *D[%d];\n", i);
  fprintf(fp, "  } __metadata;\n");
  fprintf(fp, "};\n");


}

static void gen_wrapper(FILE *fp, struct jc_struct *s)
{
  char *t = s->name;
  fprintf(fp, "void %s_cleanup_v(void *p) {\n"
              "  %s_cleanup((struct %s *)p);\n"
              "}\n", t, t, t);

  fprintf(fp, "void %s_init_v(void *p) {\n"
              "  %s_init((struct %s *)p);\n"
              "}\n", t, t, t);


  fprintf(fp, "void %s_free_v(void *p) {\n"
              " %s_free((struct %s *)p);\n"
              "};\n", t, t, t);

  fprintf(fp, "void %s_from_json_v(char *json, size_t len, void *p) {\n"
              " %s_from_json(json, len, (struct %s*)p);\n"
              "}\n", t, t, t);

  fprintf(fp, "size_t %s_to_json_v(char *json, size_t len, void *p) {\n"
              "  return %s_to_json(json, len, (struct %s*)p);\n"
              "}\n", t, t, t);

  fprintf(fp, "size_t %s_to_query_v(char *json, size_t len, void *p) {\n"
              "  return %s_to_query(json, len, (struct %s*)p);\n"
              "}\n", t, t, t);

  fprintf(fp, "void %s_list_free_v(void **p) {\n"
              "  %s_list_free((struct %s**)p);\n"
              "}\n", t, t, t);

  fprintf(fp, "void %s_list_from_json_v(char *str, size_t len, void ***p) {\n"
              "  %s_list_from_json(str, len, (struct %s ***)p);\n"
              "}\n", t, t, t);

  fprintf(fp, "size_t %s_list_to_json_v(char *str, size_t len, void **p){\n"
              "  return %s_list_to_json(str, len, (struct %s **)p);\n"
              "}\n", t, t, t);
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

  fprintf(fp, "void %s_list_from_json_v(char *str, size_t len, void ***p);\n", t);
  fprintf(fp, "void %s_list_from_json(char *str, size_t len, struct %s ***p);\n",
          t, t);

  fprintf(fp, "size_t %s_list_to_json_v(char *str, size_t len, void **p);\n", t);
  fprintf(fp, "size_t %s_list_to_json(char *str, size_t len, struct %s **p);\n",
          t,t);
}

static void gen_typedef (FILE * fp, struct jc_struct *s) {
  fprintf(fp, "typedef void (*vfvp)(void *);\n");
  fprintf(fp, "typedef void (*vfcsvp)(char *, size_t, void *);\n");
  fprintf(fp, "typedef size_t (*sfcsvp)(char *, size_t, void *);\n");
}

static void gen_struct (FILE * fp, struct jc_struct * s)
{
  char * t = s->name;
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
    gen_typedef(fp, s);
    gen_wrapper(fp, s);
    gen_cleanup(fp, s);
    fprintf(fp, "\n");
    gen_default(fp, t);
    fprintf(fp, "\n");
    gen_from_json(fp, s);
    fprintf(fp, "\n");
    gen_to_json(fp, s);
    fprintf(fp, "\n");
    gen_to_query(fp, s);
    fprintf(fp, "\n");
  } else {
    gen_typedef(fp, s);
    gen_wrapper(fp, s);
    gen_cleanup(fp, s);
    fprintf(fp, "\n");
    gen_default(fp, t);
    fprintf(fp, "\n");
    gen_from_json(fp, s);
    fprintf(fp, "\n");
    gen_to_json(fp, s);
    fprintf(fp, "\n");
    gen_to_query(fp, s);
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
  file_type = type;
  if (type == FILE_SINGLE_FILE || type == FILE_CODE)
    fprintf(fp, "#include \"specs.h\"\n");

  fprintf(fp, "/*\n%s\n*/\n", d->comment);
  if (type != FILE_DECLARATION)
    gen_open_namespace(fp, d->namespace);

  ntl_apply(fp, (void**)d->structs, gen_struct);

  if (type != FILE_DECLARATION)
    gen_close_namespace(fp, d->namespace);
  return;
}
