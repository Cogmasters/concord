#include <stddef.h>
#include <stdio.h>
#include "json-actor.h"
#include "ntl.h"
#include "orka-utils.h"

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
 * <field-info> := { <field-name> <field-type> <field-loc>? }
 *
 * <field-name>  :=  "name" : <string>
 * <field-type>  :=  "type" : { "base":<string>, "decorator":("ntl"|"none"|"pointer"|"array[<name>]") }
 * <field-loc>   :=  "loc"  : ("json" | "query" | "body")
 */


enum decorator {
  DEC_NONE = 0,
  DEC_POINTER = 1,
  DEC_NTL = 2
};

struct jc_type {
  char * base;
  enum decorator dec;
};

static void
print_type (FILE *fp, struct jc_type *p)
{
  fprintf (fp, "base:%s, dec:%d", p->base, p->dec);
}


enum loc {
  LOC_IN_JSON = 0,
  LOC_IN_QUERY,
  LOC_IN_BODY
};

struct jc_field {
  char * name;
  struct jc_type type;
  enum loc loc;
};

static void
print_field (FILE * fp, struct jc_field *p)
{
  fprintf (fp, "name:%s, ", p->name);
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
  if (3 == size && 0 == strncmp(json, "ntl", 3)) {
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
                          "(type.base):?s"
                          "(type.decorator):F"
                          "(loc):F",
                          &p->name,
                          &p->type.base,
                          dec_from_json, &p->type.dec,
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
  fprintf(fp, "void init_%s(void *p) {\n", type);
  fprintf(fp, "  memset(p, 0, sizeof(%s));\n", type);
  fprintf(fp, "}\n");

  fprintf(fp, "struct %s* alloc_%s() {\n", type, type);
  fprintf(fp, "  struct %s * p= (%s*)malloc(sizeof(%s));\n", type, type, type);
  fprintf(fp, "  init_%s((void*)p);\n", type);
  fprintf(fp, "  return p;\n");
  fprintf(fp, "}\n");

  fprintf(fp, "void free_%s(struct %s *p) {\n", type, type);
  fprintf(fp, "  cleanup_%s((void *)p);\n", type);
  fprintf(fp, "  free(p);\n");
  fprintf(fp, "}\n");

  fprintf(fp, "void free_list(struct %s **p) {\n", type);
  fprintf(fp, "  ntl_free((void**)p, &cleanup_%s);\n", type);
  fprintf(fp, "}\n");

  fprintf(fp, "void list_from_json(char *str, size_t len, void *p)\n");
  fprintf(fp, "{\n");
  fprintf(fp, "  struct ntl_deserializer deserializer = {\n");
  fprintf(fp, "    .elem_size = sizeof(%s),\n", type);
  fprintf(fp, "    .init_elem = &init_%s,\n", type);
  fprintf(fp, "    .elem_from_buf = &from_json,\n");
  fprintf(fp, "    .ntl_recipient_p= (void***)p\n");
  fprintf(fp, "  };\n");
  fprintf(fp, "  orka_str_to_ntl(str, len, &deserializer);\n");
  fprintf(fp, "}\n");
}

static void gen_cleanup(FILE * fp, struct jc_struct * s)
{
  char * t = s->name;
  fprintf(fp, "void cleanup_%s(void *p) {\n", t);
  fprintf(fp, "  struct %s * d = (struct %s *)p;\n", t, t);
  for (int i = 0; s->fields[i]; i++)
  {
    struct jc_field * f = s->fields[i];
    if (DEC_POINTER == f->type.dec) {
      fprintf(fp, "  if (d->%s) free(d->%s);\n", f->name, f->name);
    }
    else if (DEC_NTL == f->type.dec) {
      fprintf(fp, "  if (d->%s) ntl_free(d->%s, cleanup_%s);\n",
        f->name, f->name, f->type.base);
    }
  }
  fprintf(fp, "}\n");
}

static void gen_field (FILE * fp, struct jc_field * f)
{
  char * pre_dec = NULL, * post_dec = "";
  switch(f->type.dec)
  {
    case DEC_NTL:
      pre_dec = "**";
      break;
    case DEC_POINTER:
      pre_dec = "*";
      break;
    case DEC_NONE:
      pre_dec = "";
      break;
  }
  fprintf(fp, "  %s %s %s %s;\n",
     f->type.base, pre_dec, f->name, post_dec);
}

static char * to_action(struct jc_field * f)
{
  switch(f->type.dec)
  {
    case DEC_POINTER:
      break;
    case DEC_NONE:
      break;
    case DEC_NTL:
      break;
  }
  return "s";
}

static void gen_from_json(FILE *fp, struct jc_struct *s)
{
  char * t = s->name;
  fprintf (fp, "void from_json (char * json, size_t len, struct %s * p)\n", t);
  fprintf (fp, "{\n");

  fprintf (fp, "  json_extract (json, len, \n");
  int n = ntl_length(s->fields);
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field * f= s->fields[i];
    char * s = to_action(f);

    fprintf(fp, "                \"(%s):%s\"\n", f->name, s);
    if (i == n-1)
      fprintf(fp, "                @A:b,\n");
  }

  for (int i = 0; s->fields[i]; i++) {
    struct jc_field * f= s->fields[i];
    fprintf(fp, "                &p->%s,\n", f->name);
    if (i == n-1) {
      fprintf(fp, "                &p->__metadata.A, sizeof(p->__metadata.A), &p->__metadata.enable_A,\n");
      fprintf(fp, "                &p->__metadata.D, sizeof(p->__metadata.D));\n");
    }
  }
  fprintf (fp, "}\n");
}

static void gen_to_json(FILE * fp, struct jc_struct *s)
{
  char * t = s->name;
  fprintf (fp, "void to_json (char * json, size_t len, struct %s * p)\n", t);
  fprintf (fp, "{\n");
  fprintf (fp, "  json_inject (json, len, \n");

  int n = ntl_length(s->fields);
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field * f = s->fields[i];
    char * s = to_action(f);
    fprintf (fp, "                \"(%s):%s\"\n", f->name, s);
    if (i == n-1) {
      fprintf (fp, "                \"@A:b\",\n");
    }
  }

  for (int i = 0; i < n; i++) {
    struct jc_field * f = s->fields[i];
    fprintf (fp, "                &p->%s,\n", f->name);
    if (i == n-1) {
      fprintf (fp, "                &p->__metadata.A, sizeof(p->__metadata.A), &p->__metadata.enable_A);\n");
    }
  }
  fprintf (fp, "}\n");
}

static void gen_to_query(FILE * fp, struct jc_struct *s)
{
  char * t = s->name;
  fprintf (fp, "void to_query (char * json, size_t len, struct %s * p)\n", t);
  fprintf (fp, "{\n");
  fprintf (fp, "  query_inject (json, len, \n");

  int n = ntl_length(s->fields);
  for (int i = 0; s->fields[i]; i++) {
    struct jc_field * f = s->fields[i];
    if (f->loc != LOC_IN_QUERY)
      continue;

    char * s = to_action(f);
    fprintf (fp, "                \"(%s):%s\"\n", f->name, s);
    if (i == n-1) {
      fprintf (fp, "                \"@A:b\",\n");
    }
  }

  for (int i = 0; i < n; i++) {
    struct jc_field * f = s->fields[i];
    fprintf (fp, "                &p->%s,\n", f->name);
    if (i == n-1) {
      fprintf (fp, "                &p->__metadata.A, sizeof(p->__metadata.A), &p->__metadata.enable_A);\n");
    }
  }
  fprintf (fp, "}\n");
}


static void gen_struct (FILE * fp, struct jc_struct *s)
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

  gen_default(fp, t);
  gen_cleanup(fp, s);
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
