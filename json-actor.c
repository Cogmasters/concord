/*
 *
 * <apath> := [key] | [key] <apath>
 *
 * <value> := true | false | null | <int> | <float> | <complex-value> | <actor>
 *
 * <actor> := d | ld | lld | f | lf | b | (.|.*|<n>)?s | F | T
 *
 * <apath-value> := <apath> : <value>
 *
 * <complex-value> :=  { <apath-value>* }
 *                   | [ <value> ]
 *
 * <spec> := <complex-value> (.|.*|<n>)?(E|O)?
 *
 *
 * json_extractor(pos, size, "{ [key] : d"
 *                           "[key] : .*s }", &i)
 *
 * int ** list;
 * json_extractor(pos, size, "[ d ]", &list)*
 *
 *
 * json_injector(pos, size, "{  [key] : d"
 *                          "[key] : |abc| }", i);
 *
 *
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "json-common.h"
#define N_PATH_MAX 8
#define KEY_MAX 128

#define JSMN_STATIC  // dont expose jsmn symbols
#define JSMN_PARENT_LINKS // add parent links to jsmn_tok, which are needed
#define JSMN_STRICT  // parse json in strict mode
#include "jsmn.h"
#include "ntl.h"

typedef int (extractor)(char *, size_t, void *p);

#define MAX_STACK_SIZE  1024

struct stack { ;
  unsigned char array[MAX_STACK_SIZE];
  int top;

  struct apath ** paths;
  struct apath * cur_path;

  struct value ** values;
  struct value * cur_value;
};

#define PUSH(stack, c)  { stack->array[stack->top++] = c; }
#define TOP(stack)      (stack->array[stack->top-1])
#define POP(stack)      (stack->array[--stack->top])

struct apath {
  struct sized_buffer key;
  struct apath * next;
};

static void
print_apath (struct apath * apath)
{
  fprintf(stderr, "[%.*s]", apath->key.size, apath->key.start);
  if (apath->next)
    print_apath(apath->next);
}

struct apath_value;

struct size_specifier {
  enum {
    NO_SIZE,
    STATIC_SIZE,
    DYNAMIC_SIZE,
    NEED_MEMORY
  } tag;
  union {
    size_t static_size;
    void * dynamic_size;
  } _;
};

struct jv_actor {
  char type_specifier[10];
  struct size_specifier size_specifier;
  void *recipient; //must be a pointer, and it cannot be NULL
  bool is_nullable;
  bool is_funptr;
  extractor *funptr;
};

struct jv_existence {
  struct size_specifier size_specifier;
  bool has_this;
};

static void
print_jv_actor (struct jv_actor * v)
{
  fprintf(stderr, "%s\n", v->type_specifier);
}

struct value {
  enum {
    JSON_PRIMITIVE = 1,
    JSON_COMPLEX_VALUE,
    JSON_ACTOR,
  } tag;
  union {
    struct sized_buffer primitve;
    struct complex_value * expr;
    struct jv_actor ts;
  } _;
};

static void
print_complex_value (struct complex_value * cv);

static void
print_value (struct value * v) {
  fprintf(stderr, "tag_%d ", v->tag);

  switch (v->tag) {
    case JSON_PRIMITIVE:
      fprintf(stderr, "%.*s\n", v->_.primitve.size, v->_.primitve.start);
      break;
    case JSON_COMPLEX_VALUE:
      print_complex_value(v->_.expr);
      break;
    case JSON_ACTOR:
      print_jv_actor(&v->_.ts);
      break;
    default:
      break;
  }
}

struct apath_value {
  struct apath path;
  struct value value;
};

static void
print_apath_value (struct apath_value *p)
{
  print_apath(&p->path);
  print_value(&p->value);
}

struct E {
};

struct sized_apath_value {
  struct apath_value * pos;
  size_t size;
};

struct sized_value {
  struct value * pos;
  size_t size;
};

struct complex_value {
  enum {
    ARRAY = 1,
    OBJECT
  } tag;
  union {
    struct sized_value elements;
    struct sized_apath_value pairs;
  } _;
  struct jv_existence E;
};

static void
print_complex_value (struct complex_value * cv)
{
  if (cv->tag == ARRAY) {
    for (int i = 0; i < cv->_.elements.size; i++)
      print_value(cv->_.elements.pos+i);
  }
  else {
    for (int i = 0; i < cv->_.pairs.size; i++)
      print_apath_value(cv->_.pairs.pos+i);
  }
  if (cv->E.has_this) {
    fprintf(stderr, "E ");
  }
}

static int
is_primitive (char * pos, size_t size, char ** next_pos_p)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  unsigned char c;

  c = * pos;

  switch (c) {
    case 't': { // true
      if (pos + 3 < end_pos &&
          ('r' == *(pos + 1) && 'u' == *(pos + 2) && 'e' == *(pos + 3))) {
        pos += 4;
        goto return_true;
      }
      break;
    }
    case 'f': { // false
      if (pos + 5 < end_pos &&
          'a' == *(pos + 1) && 'l' == *(pos + 2) && 's' == *(pos + 3)
          && 'e' == *(pos + 4)) {
        pos += 5;
        goto return_true;
      }
      break;
    }
    case 'n': { // null
      if (pos + 4 < end_pos &&
          'u' == *(pos + 1) && 'l' == *(pos + 2) && 'l' == *(pos + 3)) {
        pos += 4;
        goto return_true;
      }
      break;
    }
    case '"': { // a string literal
      pos ++;
      while (pos < end_pos) {
        c = *pos;
        pos ++;
        if ('"' == c)
          goto return_true;
      }
      break;
    }
    case '|': { // a propertiary string literal
      pos ++;
      while (pos < end_pos) {
        c = *pos;
        pos ++;
        if ('|' == c)
          goto return_true;
      }
      break;
    }
    default:
      if ('0' <= c && c <= '9') {
        pos++;
        while (pos < end_pos) {
          c = *pos;
          if (' ' == c || ',' == c) goto return_true;
          if ('.' == c || '0' <= c || c <= '9') pos++;
          else return 0;
        }
        goto return_true;
      }
      break;
  }
  return 0;


return_true:
  *next_pos_p = pos;
  return 1;
}

static int
parse_size_specifier (char * pos, size_t size,
                      struct size_specifier * p,
                      char **next_pos_p)
{
  char * const start_pos = pos, * end;
  long value_size = strtol(start_pos, &end, 10);

  int is_valid_size = 0, has_dsize = 0, allocate_memory = 0;
  if (end != start_pos) {
    p->tag = STATIC_SIZE;
    p->_.static_size = value_size;
    *next_pos_p = end; // jump to the end of number
    return 1;
  }
  else if ('.' == *pos && '*' == *(pos+1)) {
    p->tag = DYNAMIC_SIZE;
    *next_pos_p = pos + 2;
    return 1;
  }
  else if ('.' == *pos) {
    p->tag = NEED_MEMORY;
    *next_pos_p = pos + 1;
    return 1;
  }
  return 0;
}

static int
parse_value(char *pos, size_t size, struct value * p, char ** next_pos_p)
{
  char *const start_pos = pos, *end;

  char *next_pos = NULL;
  if (is_primitive(pos, size, &next_pos)) {
    p->tag = JSON_PRIMITIVE;
    p->_.primitve.start = pos;
    p->_.primitve.size = next_pos - pos;
    *next_pos_p = next_pos;
    return 1;
  }
  struct jv_actor * ts = &p->_.ts;
  p->tag = JSON_ACTOR;

  if (parse_size_specifier(pos, size - (pos- start_pos),
                           &ts->size_specifier, &next_pos)) {
    pos = *next_pos;
  }

  if (STRNEQ(pos, "s", 1)){
    strcpy(ts->type_specifier, "char*");
    pos ++;
    goto return_true;
  }
  else if (STRNEQ(pos, "L", 1)) {
    strcpy(ts->type_specifier, "array");
    pos ++;
    goto return_true;
  }
  else if (STRNEQ(pos, "A", 1)) {
    strcpy(ts->type_specifier, "array");
    pos ++;
    goto return_true;
  }
  else if (STRNEQ(pos, "F", 1)) {
    strcpy(ts->type_specifier, "funptr");
    ts->is_funptr = true;
    pos ++;
    goto return_true;
  }
  else if (STRNEQ(pos, "T", 1)) {
    strcpy(ts->type_specifier, "token");
    pos ++;
    goto return_true;
  }
  else if (STRNEQ(pos, "d", 1)) {
    ts->size_specifier._.static_size = sizeof(int);
    ts->size_specifier.tag = STATIC_SIZE;
    strcpy(ts->type_specifier, "int*");
    pos ++;
    goto return_true;
  }
  else if (STRNEQ(pos, "ld", 2)) {
    ts->size_specifier._.static_size = sizeof(long);
    ts->size_specifier.tag = STATIC_SIZE;
    strcpy(ts->type_specifier, "long*");
    pos += 2;
    goto return_true;
  }
  else if (STRNEQ(pos, "lld", 3)) {
    ts->size_specifier._.static_size = sizeof(long long);
    ts->size_specifier.tag = STATIC_SIZE;
    strcpy(ts->type_specifier, "long long *");
    pos += 3;
    goto return_true;
  }
  else if (STRNEQ(pos, "f", 1)) {
    ts->size_specifier._.static_size = sizeof(float);
    ts->size_specifier.tag = STATIC_SIZE;
    strcpy(ts->type_specifier, "float *");
    pos ++;
    goto return_true;
  }
  else if (STRNEQ(pos, "lf", 2)) {
    ts->size_specifier._.static_size = sizeof(double);
    ts->size_specifier.tag = STATIC_SIZE;
    strcpy(ts->type_specifier, "double *");
    pos += 2;
    goto return_true;
  }
  else if (STRNEQ(pos, "b", 1)){
    ts->size_specifier._.static_size = sizeof(bool);
    ts->size_specifier.tag = STATIC_SIZE;
    strcpy(ts->type_specifier, "bool*");
    pos ++;
    goto return_true;
  }
  return 0;

return_true:
  *next_pos_p = pos;
  return 1;
}

static int
parse_existence(char *pos, size_t size,
                struct jv_existence * p,
                char ** next_pos_p)
{
  if (size == 0)
    return 0;

  char *const start_pos = pos, * next_pos = NULL;
  if (parse_size_specifier(pos, size, &p->size_specifier, &next_pos)) {
    pos = next_pos;
  }

  if (STRNEQ(pos, "E", 1)){
    p->has_this = true;
    pos ++;
    *next_pos_p = pos;
    return 1;
  }
  return 0;
}

char * parse_expr (struct stack * stack, char * pos,
                   size_t size, struct complex_value * expr);

#define SKIP_SPACES(s, end)   { while (s < end && isspace(*s)) ++s; }

char * parse_apath_value(struct stack *stack,
                         char *pos, size_t size, struct apath_value *av,
                         struct apath *curr_path)
{
  // until find a ']' or '\0'
  char * const start_pos = pos, * const end_pos = pos + size;
  while (*pos && pos < end_pos) {
    if (']' == *pos) break;
    ++pos;
  }

  ASSERT_S(*pos == ']', "A close bracket ']' is missing");

  int len = pos - start_pos;

  curr_path->key.start = calloc(1, len);
  curr_path->key.size = len;

  // we don't allow empty [] at other places like this: [key][]
  ASSERT_S(len > 0, "Key is missing");

  memcpy(curr_path->key.start, start_pos, len);

  ++pos; // eat up ']'
  SKIP_SPACES(pos, end_pos);
  switch (*pos) {
    case '[':
    {
      ++pos; // eat up '['
      struct apath *next_path = calloc(1, sizeof(struct apath));
      curr_path->next = next_path;
      return parse_apath_value(stack, pos, end_pos - pos, av, next_path);
    }
    case ':':
    {
      ++pos; // eat up ':'
      SKIP_SPACES(pos, end_pos);
      if ('[' == *pos || '{' == *pos) {
        struct complex_value * expr = calloc(1, sizeof(struct complex_value));
        av->value._.expr = expr;
        av->value.tag = JSON_COMPLEX_VALUE;
        pos = parse_expr(stack, pos, end_pos - pos, expr);
      }
      else {
        char * next_pos = NULL;
        if (parse_value(pos, end_pos - pos, &av->value, &next_pos)) {
          pos = next_pos;
        }
      }
      break;
    }
    default: {
      ERR("expecting '[' or ':', but getting %c\n", *pos);
      return NULL;
    }
  }
  return pos;
}

static char *
parse_apath_value_list(struct stack * stack, char * pos, size_t size,
                       struct sized_apath_value * pairs)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  char c;
  pairs->pos = calloc(20, sizeof(struct apath_value));

  size_t i = 0;
  while (*pos && pos < end_pos) {
    SKIP_SPACES(pos, end_pos);
    if ('[' == *pos) {
      ++pos; //eat up '['
      pos = parse_apath_value(stack, pos, end_pos - pos,
                              pairs->pos + i, &pairs->pos[i].path);
    }
    else if (TOP(stack) == *pos) {
      pairs->size = i;
      return pos;
    }
    else {
      ERR("Expecting %c, but found %c in %s", TOP(stack), *pos, start_pos);
    }
    ++i;
  }
  ERR("Expecting %c to close the list\n", TOP(stack));
}

static char *
parse_value_list (struct stack * stack, char * pos, size_t size,
                  struct sized_value * elements)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  elements->pos = calloc(20, sizeof(struct value));
  char * next_pos = NULL;

  size_t i = 0;
  while (*pos && pos < end_pos) {
    SKIP_SPACES(pos, end_pos);
    next_pos = NULL;
    if (parse_value(pos, size, elements->pos+i, &next_pos)) {
      pos = next_pos;
    }
    else if (TOP(stack) == *pos) {
      elements->size = i;
      return pos;
    }
    else {
      ERR("Unexpected %c in %s", *pos, pos);
    }
    ++i;
  }
  ERR("Expecting %c to terminate the array list\n", TOP(stack));
}

struct stack stack = { .array = {0}, .top = 0 };



char * parse_expr (struct stack * stack, char * pos,
                   size_t size, struct complex_value * expr)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  char * next_pos = NULL;

  SKIP_SPACES(pos, end_pos);
  if ('{' == *pos) {
    expr->tag = OBJECT;
    pos++;
    PUSH(stack, '}');
    pos = parse_apath_value_list(stack, pos, end_pos - pos, &expr->_.pairs);
    POP(stack);
    SKIP_SPACES(pos, end_pos);
    pos++;
    SKIP_SPACES(pos, end_pos);
    if (parse_existence(pos, end_pos - pos, &expr->E, &next_pos)) {
      pos = *next_pos;
    }

  }
  else if ('[' == *pos) {
    expr->tag = ARRAY;
    pos++;
    PUSH(stack, ']');
    pos = parse_value_list(stack, pos, end_pos - pos, &expr->_.elements);
    POP(stack);
    SKIP_SPACES(pos, end_pos);
    pos++;
    SKIP_SPACES(pos, end_pos);
    if (parse_existence(pos, end_pos - pos, &expr->E, &next_pos)) {
      pos = *next_pos;
    }
  }
  return pos;
}

