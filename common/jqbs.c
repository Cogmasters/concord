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
 * <field-info> := { <field-name> <c-name>? <field-type> <field-loc>? }
 *
 * <field-name>  :=  "name" : <string>
 * <c-name>  := "c-name" : <string>
 *
 * <field-type>  :=  "type" : { "base":<string>,
 *                              "decorator"?:("ntl"|"pointer"|"array[<string>]"),
 *                              "converter"?:<string>
 *                            }
 * <field-loc>   :=  "loc"  : ("json" | "query" | "body")
 */


enum decorator {
  DEC_NONE = 0, // this has to be zero as the absence means DEC_NONE
  DEC_POINTER = 1,
  DEC_NTL = 2
};

struct jc_type {
  char * base;
  enum decorator dec;
  char * converter; // NULL means using builtin converter.
};

static void
print_type (FILE *fp, struct jc_type *p)
{
  fprintf (fp, "base:%s, dec:%d", p->base, p->dec);
}


enum loc {
  LOC_IN_JSON = 0,  // this has to be zero as the absence means LOC_IN_JSON
  LOC_IN_QUERY,
  LOC_IN_BODY
};

struct jc_field {
  char * name;
  char * c_name;
  struct jc_type type;
  enum loc loc;
};

static void
print_field (FILE * fp, struct jc_field *p)
{
  fprintf (fp, "name:%s, ", p->name);
  if (p->c_name)
    fprintf (fp, "c-name:%s, ", p->c_name);

  print_type (fp, &p->type);
  fprintf (fp, ", loc:%d\n", p->loc);
}

struct jc_struct {
  char * name;
  struct jc_field ** fields;
};

static void
print_struct (FILE * fp, struct jc_struct * p)
{
  fprintf(fp, "name %s\n", p->name);
  ntl_apply(fp, p->fields, print_field);
}

struct jc_definition {
  char * description;
  char **namespace; // ntl
  struct jc_struct ** structs; //ntl
};

static void
print_definition (FILE * fp, struct jc_definition * p)
{
  fprintf(fp, "// %s\n", p->description);
  fprintf(fp, "namespace: ");
  ntl_apply(fp, p->namespace, fprintf);
  fprintf(fp, "\n");
  ntl_apply(fp, p->structs, print_struct);
}


static size_t
loc_from_json (char * json, size_t size, enum loc *p)
{
  if (4 == size && 0 == strncmp(json, "json", 4)) {
    * p = LOC_IN_JSON;
  }
  else if (5 == size && 0 == strncmp(json, "query", 5)) {
    * p = LOC_IN_QUERY;
  }
  else if (4 == size && 0 == strncmp(json, "body", 4)) {
    * p = LOC_IN_BODY;
  }
  return 1;
}

static size_t
dec_from_json (char * json, size_t size, enum decorator *p)
{
  if (1 == size && '*' == *json) {
    *p = DEC_POINTER;
  }
  else if (3 == size && 0 == strncmp(json, "ntl", 3)) {
    *p = DEC_NTL;
  }
  else if (4 == size && 0 == strncmp(json, "none", 4)) {
    *p = DEC_NONE;
  }
  else if (7 == size && 0 == strncmp(json, "pointer", 7)) {
    *p = DEC_POINTER;
  }

  return 1;
}

static size_t
field_from_json (char * json, size_t size, void * x)
{
  struct jc_field *p = (struct jc_field *)x;
  size_t s = json_extract(json, size,
                          "(name):?s"
                          "(c-name):?s"
                          "(type.base):?s"
                          "(type.decorator):F"
                          "(type.converter):?s"
                          "(loc):F",
                          &p->name,
                          &p->c_name,
                          &p->type.base,
                          dec_from_json, &p->type.dec,
                          &p->type.converter,
                          loc_from_json, &p->loc);
  return s;
}


static size_t
struct_from_json (char * json, size_t size, struct jc_struct * s)
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
name_from_json (char * json, size_t size, char * p)
{
  memcpy(p, json, size);
  p[size] = 0;
}


static size_t
definition_from_json (char * json, size_t size, struct jc_definition * s)
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
                            "(description):?s"
                            "(namespace):F"
                            "(structs):F",
                            &s->description,
                            orka_str_to_ntl, &d1,
                            orka_str_to_ntl, &d2);
  return ret;
}

static void
gen_default(FILE * fp, char * type)
{
  fprintf(fp, "void init(void *p) {\n", type);
  fprintf(fp, "  memset(p, 0, sizeof(struct %s));\n", type);
  fprintf(fp, "}\n");

  fprintf(fp, "struct %s* alloc() {\n", type, type);
  fprintf(fp, "  struct %s * p= (struct %s*)malloc(sizeof(struct %s));\n", type, type, type);
  fprintf(fp, "  init_%s((void*)p);\n", type);
  fprintf(fp, "  return p;\n");
  fprintf(fp, "}\n");

  fprintf(fp, "void release(struct %s *p) {\n", type);
  fprintf(fp, "  _cleanup_((void *)p);\n", type);
  fprintf(fp, "  free(p);\n");
  fprintf(fp, "}\n");

  fprintf(fp, "void free_list(struct %s **p) {\n", type);
  fprintf(fp, "  ntl_free((void**)p, &_cleanup_);\n");
  fprintf(fp, "}\n");

  fprintf(fp, "void list_from_json(char *str, size_t len, void ***p)\n");
  fprintf(fp, "{\n");
  fprintf(fp, "  struct ntl_deserializer d;\n");
  fprintf(fp, "  memset(&d, 0, sizeof(d));\n");
  fprintf(fp, "  d.elem_size = sizeof(struct %s);\n", type);
  fprintf(fp, "  d.init_elem = _init_;\n");
  fprintf(fp, "  d.elem_from_buf = from_json;\n");
  fprintf(fp, "  d.ntl_recipient_p= (void***)p;\n");
  fprintf(fp, "  orka_str_to_ntl(str, len, &deserializer);\n");
  fprintf(fp, "}\n");

  fprintf(fp, "void list_to_json(char *str, size_t len, void **p)\n");
  fprintf(fp, "{\n");
  fprintf(fp, "  ntl_to_buf(str, len, p, NULL, to_json);\n");
  fprintf(fp, "}\n");
}

struct action {
  char * c_type;
  char * pre_dec;
  char * post_dec;
  char * addrof;
  char * extract_spec;
  char * inject_spec;
  char * free;
  bool is_user_def;
};

static int to_builtin_action (struct jc_field * f, struct action * act)
{
  if (strcmp(f->type.base, "int") == 0) {
    act->extract_spec = "d";
    act->inject_spec = "d";
  }
  else if (strcmp(f->type.base, "u64") == 0) {
    act->extract_spec = "u64";
    act->inject_spec = "u64";
  }
  else if (strcmp(f->type.base, "uint64_t") == 0) {
    act->extract_spec = "u64";
    act->inject_spec = "u64";
  }
  else if (strcmp(f->type.base, "int64_t") == 0) {
    act->extract_spec = "i64";
    act->inject_spec = "i64";
  }
  else if (strcmp(f->type.base, "bool") == 0) {
    act->extract_spec = "b";
    act->inject_spec = "b";
  }
  else {
    fprintf(stderr, "unknown %s\n", f->type.base);
    return 0;
  }
  return 1;
}

static void
to_action(struct jc_field * f, struct action * act)
{
  act->post_dec = "";
  act->pre_dec = "";
  switch(f->type.dec)
  {
    case DEC_POINTER:
      if (strcmp(f->type.base, "char") == 0) {
        act->inject_spec = "s";
        act->extract_spec = "s";
        act->addrof = "";
        act->post_dec = "";
        act->pre_dec = "*";
        act->free = "free";
        return;
      } else {
        char * tok = strrchr(f->type.base, ':');
        if (tok != NULL) {
          asprintf(&act->inject_spec, "%s::to_json", f->type.base);
          asprintf(&act->extract_spec, "%s::from_json", f->type.base);
          asprintf(&act->free, "%s::release", f->type.base);
          act->addrof = "";
          act->post_dec = "";
          act->pre_dec = "*";
          act->is_user_def = true;
        }
      }
      break;
    case DEC_NONE:
      act->addrof = "&";
      if (!to_builtin_action(f, act)) {
        ERR("unknown %s\n", f->type.base);
      }
      break;
    case DEC_NTL:
      act->addrof = "";
      if (to_builtin_action(f, act)) {
        act->free = "free";
      } else {
        act->is_user_def = true;
        asprintf(&act->extract_spec, "%s::list_from_json", f->type.base);
        asprintf(&act->inject_spec, "%s::list_to_json", f->type.base);
        asprintf(&act->free, "%s::free_list", f->type.base);
      }
      break;
  }
}

static void gen_cleanup(FILE * fp, struct jc_struct * s)
{
  char * t = s->name;
  fprintf(fp, "void cleanup(void *p) {\n", t);
  fprintf(fp, "  struct %s * d = (struct %s *)p;\n", t, t);
  for (int i = 0; s->fields[i]; i++)
  {
    struct jc_field * f = s->fields[i];
    struct action act;
    to_action(f, &act);


    if (DEC_POINTER == f->type.dec) {
      fprintf(fp, "  if (d->%s) %s(d->%s);\n", f->name, act.free, f->name);
    }
    else if (DEC_NTL == f->type.dec) {
      fprintf(fp, "  if (d->%s) %s(d->%s);\n", f->name, act.free, f->name);
    }
  }
  fprintf(fp, "}\n");
}

static void gen_field (FILE * fp, struct jc_field * f)
{
  struct action act = {0};
  to_action(f, &act);
  char * name = f->c_name ? f->c_name : f->name;
  fprintf(fp, "  %s %s %s %s;\n", f->type.base, act.pre_dec, name, act.post_dec);
}

static void gen_from_json(FILE *fp, struct jc_struct *s)
{
  char * t = s->name;
  char * addrof = "";
  fprintf (fp, "void from_json (char * json, size_t len, struct %s * p)\n",
           t, t);
  fprintf (fp, "{\n");

  fprintf (fp, "  json_extract (json, len, \n");
  int n = ntl_length(s->fields);
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field * f= s->fields[i];
    struct action act = {0};
    to_action(f, &act);

    if (act.is_user_def)
      fprintf(fp, "                \"(%s):F\"\n", f->name);
    else
      fprintf(fp, "                \"(%s):%s\"\n", f->name, act.extract_spec);

    if (i == n-1)
      fprintf(fp, "                @A:b,\n");
  }

  for (int i = 0; s->fields[i]; i++) {
    struct jc_field * f= s->fields[i];
    struct action act = {0};
    to_action(f, &act);
    if (act.is_user_def)
      fprintf(fp, "                %s, &%s\n", act.extract_spec, f->name);
    else
      fprintf(fp, "                %sp->%s,\n", act.addrof, f->name);
    if (i == n-1) {
      fprintf(fp, "                p->__metadata.A, sizeof(p->__metadata.A), &p->__metadata.enable_A,\n");
      fprintf(fp, "                p->__metadata.D, sizeof(p->__metadata.D));\n");
    }
  }
  fprintf (fp, "}\n");
}

static void gen_to_json(FILE * fp, struct jc_struct *s)
{
  char * t = s->name;
  char * addrof = "";
  fprintf (fp, "void to_json (char * json, size_t len, struct %s * p)\n",
           t, t);
  fprintf (fp, "{\n");
  fprintf (fp, "  json_inject (json, len, \n");

  int n = ntl_length(s->fields);
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field * f = s->fields[i];
    struct action act = {0};
    to_action(f, &act);
    if (act.is_user_def)
      fprintf (fp, "                \"(%s):F\"\n", f->name);
    else
      fprintf (fp, "                \"(%s):%s\"\n", f->name, act.inject_spec);
    if (i == n-1) {
      fprintf (fp, "                \"@A:b\",\n");
    }
  }

  for (int i = 0; i < n; i++) {
    struct jc_field * f = s->fields[i];
    struct action act = {0};
    to_action(f, &act);
    if (act.is_user_def)
      fprintf (fp, "                %s, p->%s,\n", act.inject_spec, f->name);
    else
      fprintf (fp, "                %sp->%s,\n", act.addrof, f->name);
    if (i == n-1) {
      fprintf (fp, "                p->__metadata.A, sizeof(p->__metadata.A), &p->__metadata.enable_A);\n");
    }
  }
  fprintf (fp, "}\n");
}

static void gen_to_query(FILE * fp, struct jc_struct *s)
{
  char * t = s->name;
  char * addrof = "";
  fprintf (fp, "void to_query (char * json, size_t len, struct %s * p)\n",
           t, t);
  fprintf (fp, "{\n");
  fprintf (fp, "  query_inject (json, len, \n");

  int n = ntl_length(s->fields);
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field * f = s->fields[i];
    if (f->loc != LOC_IN_QUERY)
      continue;

    struct action act = {0};
    to_action(f, &act);
    fprintf (fp, "                \"(%s):%s\"\n", f->name, act.inject_spec);
    if (i == n-1) {
      fprintf (fp, "                \"@A:b\",\n");
    }
  }

  for (int i = 0; i < n; i++) {
    struct jc_field * f = s->fields[i];
    struct action act = {0};
    to_action(f, &act);
    fprintf (fp, "                %sp->%s,\n", act.addrof, f->name);
    if (i == n-1) {
      fprintf (fp, "                p->__metadata.A, sizeof(p->__metadata.A), &p->__metadata.enable_A);\n");
    }
  }
  fprintf (fp, "}\n");
}


static void gen_def (FILE * fp, struct jc_struct *s)
{
  char * t = s->name;
  fprintf(fp, "\n\n");
  fprintf(fp, "struct %s {\n", t);
  int i = 0;
  for (i = 0; s->fields[i]; i++)
    gen_field(fp, s->fields[i]);
  fprintf(fp, "  struct {\n");
  fprintf(fp, "    bool enable_A;\n");
  fprintf(fp, "    bool enable_N;\n");
  fprintf(fp, "    void * A[%d];\n", i);
  fprintf(fp, "    void * N[%d];\n", i);
  fprintf(fp, "    void * D[%d];\n", i);
  fprintf(fp, "  } __metadata;\n");
  fprintf(fp, "};\n");


}

static void gen_struct (FILE * fp, struct jc_struct * s)
{
  char * t = s->name;
  fprintf (fp, "/* comment out to avoid redefinition warning\n");
  gen_def(fp, s);
  fprintf (fp, "\n*/\n");
  gen_cleanup(fp, s);
  gen_default(fp, t);
  gen_from_json(fp, s);
  gen_to_json(fp, s);
  gen_to_query(fp, s);
}

static void gen_open_namespace (FILE * fp, char ** p)
{
  for (int i = 0; p[i]; i++) {
    fprintf(fp, "namespace %s {\n", p[i]);
  }
}

static void gen_close_namespace (FILE * fp, char ** p)
{
  for (int i = 0; p[i]; i++) {
    fprintf(fp, "} // %s\n", p[i]);
  }
}

static void gen_definition (FILE * fp, struct jc_definition * d)
{
  fprintf(fp, "// %s\n", d->description);
  gen_open_namespace(fp, d->namespace);
  ntl_apply(fp, d->structs, gen_struct);
  gen_close_namespace(fp, d->namespace);
  return;
}
