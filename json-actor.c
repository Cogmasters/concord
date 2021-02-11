/*
 *
 * <apath> := [key] | [key] <apath>
 *
 * <value> := true | false | null | <int> | <float> | <string-literal>
 *            | <complex-value> | <actor>
 *
 * <actor> := d | ld | lld | f | lf | b | <size-specifier>? s | F(?)? | T(*)?
 *
 * <apath-value> := <apath> : <value>
 *
 * <complex-value> :=  { <apath-value>* } <existence-omission>?
 *                   | [ <value> ]  <existence-omission>?
 *
 * <existence-omission> := <size-specifier>? (E|O)
 *
 * <size-specifier> := . | .* | <integer>
 *
 *
 * examples:
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


enum actor {
  EXTRACTOR = 1,
  INJECTOR
};

#define MAX_STACK_SIZE  1024

struct stack {
  unsigned char array[MAX_STACK_SIZE];
  int top;

  struct apath ** paths;
  struct apath * cur_path;

  struct value ** values;
  struct value * cur_value;
  enum actor actor;
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
    UNKNOWN_SIZE = 0,
    STATIC_SIZE,
    DYNAMIC_SIZE,
    ZERO_SIZE
  } tag;
  union {
    size_t static_size;
    void * parameterized_size;
  } _;
};

struct jv_actor {
  enum actor tag;
  union {
    void *recipient; //must be a pointer, and it cannot be NULL
    void *provider; // this can be NULL or its value can be UNDEFINED
  } _;
  struct size_specifier memory_size; // this designate the size of _;
  enum {
    BUILT_IN = 0,
    USER_DEF_ACCEPT_NON_NULL,
    USER_DEF_ACCEPT_NULL
  } action_tag;
  union {
    char built_in[10];
    int (*user_def)(char *, size_t, void *p);
  } action;
};

struct jv_existence {
  struct size_specifier memory_size;
  bool has_this;
};

static void
print_jv_actor (struct jv_actor * v)
{
  if (EXTRACTOR == v->tag)
    fprintf (stderr, "[extractor]");
  else
    fprintf (stderr, "[injector]");
  if (BUILT_IN == v->action_tag)
    fprintf(stderr, "builtin(%s)\n", v->action.built_in);
  else
    fprintf(stderr, "funptr(%p)\n", v->action.user_def);
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
  fprintf(stderr, " : ");
  print_value(&p->value);
}

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
    for (size_t i = 0; i < cv->_.elements.size; i++)
      print_value(cv->_.elements.pos+i);
  }
  else {
    for (size_t i = 0; i < cv->_.pairs.size; i++)
      print_apath_value(cv->_.pairs.pos+i);
  }
  if (cv->E.has_this) {
    fprintf(stderr, "E ");
  }
}

static int
is_primitive (
  char * pos,
  size_t size,
  char ** next_pos_p)
{
  char * const end_pos = pos + size;
  unsigned char c;

  c = * pos;

  switch (c) {
    case 't': { // true
      if (pos + 3 < end_pos
          && 'r' == pos[1] && 'u' == pos[2] && 'e' == pos[3]) {
        pos += 4;
        goto return_true;
      }
      break;
    }
    case 'f': { // false
      if (pos + 4 < end_pos
          && 'a' == pos[1] && 'l' == pos[2] && 's' == pos[3] && 'e' == pos[4]) {
        pos += 5;
        goto return_true;
      }
      break;
    }
    case 'n': { // null
      if (pos + 3 < end_pos
          && 'u' == pos[1] && 'l' == pos[2] && 'l' == pos[3]) {
        pos += 4;
        goto return_true;
      }
      break;
    }
    case '"': { // a string literal
      pos ++;
      while (pos < end_pos) {
        c = *pos; pos ++;
        if ('"' == c)
          goto return_true;
      }
      break;
    }
    case '|': { // a propertiary string literal
      pos ++;
      while (pos < end_pos) {
        c = *pos; pos ++;
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
parse_size_specifier (
  char * pos,
  size_t size,
  struct size_specifier * p,
  char **next_pos_p)
{
  char * const start_pos = pos, * end;
  long value_size = strtol(start_pos, &end, 10);

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
    p->tag = ZERO_SIZE;
    *next_pos_p = pos + 1;
    return 1;
  }
  return 0;
}

static int
parse_value(
  struct stack * stack,
  char *pos, size_t size,
  struct value * p,
  char ** next_pos_p)
{
  char * const end_pos = pos + size;

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
  ts->tag = stack->actor;

  if (parse_size_specifier(pos, end_pos - pos,
                           &ts->memory_size, &next_pos)) {
    pos = next_pos;
  }

  ts->action_tag = BUILT_IN;
  switch(*pos)
  {
    case 's':
      strcpy(ts->action.built_in, "char*");
      pos ++;
      goto return_true;
    case 'L':
      strcpy(ts->action.built_in, "array");
      pos ++;
      goto return_true;
    case 'A':
      strcpy(ts->action.built_in, "array");
      pos ++;
      goto return_true;
    case 'F':
      ts->action_tag = USER_DEF_ACCEPT_NON_NULL;
      pos ++;
      goto return_true;
    case 'T':
      strcpy(ts->action.built_in, "token");
      pos ++;
      goto return_true;
    case 'd':
      ts->memory_size._.static_size = sizeof(int);
      ts->memory_size.tag = STATIC_SIZE;
      strcpy(ts->action.built_in, "int*");
      pos ++;
      goto return_true;
    case 'l': {
      if (STRNEQ(pos, "ld", 2)) {
        ts->memory_size._.static_size = sizeof(long);
        ts->memory_size.tag = STATIC_SIZE;
        strcpy(ts->action.built_in, "long*");
        pos += 2;
        goto return_true;
      } else if (STRNEQ(pos, "lld", 3)) {
        ts->memory_size._.static_size = sizeof(long long);
        ts->memory_size.tag = STATIC_SIZE;
        strcpy(ts->action.built_in, "long long *");
        pos += 3;
        goto return_true;
      } else if (STRNEQ(pos, "lf", 2)) {
        ts->memory_size._.static_size = sizeof(double);
        ts->memory_size.tag = STATIC_SIZE;
        strcpy(ts->action.built_in, "double *");
        pos += 2;
        goto return_true;
      }
    }
    case 'f':
      ts->memory_size._.static_size = sizeof(float);
      ts->memory_size.tag = STATIC_SIZE;
      strcpy(ts->action.built_in, "float *");
      pos ++;
      goto return_true;
    case 'b':
      ts->memory_size._.static_size = sizeof(bool);
      ts->memory_size.tag = STATIC_SIZE;
      strcpy(ts->action.built_in, "bool*");
      pos ++;
      goto return_true;
    default:
      if (TOP(stack) == *pos)
        return 0;
      else
        ERR("unexpected %c\n", *pos);
  }

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

  char * next_pos = NULL;
  if (parse_size_specifier(pos, size, &p->memory_size, &next_pos)) {
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

static char * parse_complex_value(struct stack *stack, char *pos,
                                  size_t size, struct complex_value *expr);

#define SKIP_SPACES(s, end)   { while (s < end && isspace(*s)) ++s; }

static char *
parse_apath_value(
  struct stack *stack,
  char *pos, size_t size, struct apath_value *av,
  struct apath *curr_path)
{
  // until find a ']' or '\0'
  char * const start_pos = pos, * const end_pos = pos + size,
    * next_pos = NULL;

  ASSERT_S('[' == *pos, "expecting '['");
  pos ++;
  while (*pos && pos < end_pos) {
    if (']' == *pos) break;
    ++pos;
  }

  ASSERT_S(*pos == ']', "A close bracket ']' is missing");

  int len = pos - start_pos - 1;
  ASSERT_S(len > 0, "Key is missing");

  curr_path->key.start = calloc(1, len); // @todo get memory from stack's pool
  curr_path->key.size = len;
  memcpy(curr_path->key.start, start_pos+1, len);

  ++pos; // eat up ']'
  SKIP_SPACES(pos, end_pos);
  switch (*pos) {
    case '[':
    {
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
        pos = parse_complex_value(stack, pos, end_pos - pos, expr);
      }
      else if (parse_value(stack, pos, end_pos - pos, &av->value, &next_pos)) {
        pos = next_pos;
      }
      else {
        ERR("expecting value after ':', %s does not have a legit value", pos);
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
parse_apath_value_list(
  struct stack * stack,
  char * pos,
  size_t size,
  struct sized_apath_value * pairs)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  pairs->pos = calloc(20, sizeof(struct apath_value));

  size_t i = 0;
  while (pos < end_pos) {
    SKIP_SPACES(pos, end_pos);
    if ('[' == *pos) {
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
  return pos;
}

static char *
parse_value_list (
  struct stack * stack,
  char * pos,
  size_t size,
  struct sized_value * elements)
{
  char * const end_pos = pos + size;
  elements->pos = calloc(20, sizeof(struct value));
  char * next_pos = NULL;

  size_t i = 0;
  while (pos < end_pos) {
    SKIP_SPACES(pos, end_pos);
    next_pos = NULL;
    if (parse_value(stack, pos, size, elements->pos+i, &next_pos)) {
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
  return pos;
}

struct stack stack = { .array = {0}, .top = 0, .actor = EXTRACTOR };

static char *
parse_complex_value(
  struct stack *stack,
  char *pos,
  size_t size,
  struct complex_value *expr)
{
  char * const end_pos = pos + size;
  char * next_pos = NULL;

  SKIP_SPACES(pos, end_pos);
  if ('{' == *pos) {
    expr->tag = OBJECT;
    pos++;
    PUSH(stack, '}');
    pos = parse_apath_value_list(stack, pos, end_pos - pos, &expr->_.pairs);
    char c = POP(stack);
    if (c != *pos)
      ERR("Mismatched stack: expecting %c, but getting %c\n", c, *pos);
    pos++;
    SKIP_SPACES(pos, end_pos);
    if (parse_existence(pos, end_pos - pos, &expr->E, &next_pos)) {
      pos = next_pos;
    }
  }
  else if ('[' == *pos) {
    expr->tag = ARRAY;
    pos++;
    PUSH(stack, ']');
    pos = parse_value_list(stack, pos, end_pos - pos, &expr->_.elements);
    char c = POP(stack);
    if (c != *pos)
      ERR("Mismatched stack: expecting %c, but getting %c\n", c, *pos);
    pos++;
    SKIP_SPACES(pos, end_pos);
    if (parse_existence(pos, end_pos - pos, &expr->E, &next_pos)) {
      pos = next_pos;
    }
  }
  return pos;
}