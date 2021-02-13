/*
 *
 * json actor (injector or extractor) specification grammar
 *
 * <injector> := <composite-value>
 *               | <access-path-value-list> <existence>?
 *
 * <extractor> := <composite-value>
 *                | <access-path-value-list> <existence>?
 *
 * <access-path> := (<key>) | (<key>) <access-path>
 *
 * <value> := true | false | null | <int> | <float> | <string-literal>
 *            | <composite-value> | <action>
 *
 * <action> := d | ld | lld | f | lf | b | <size-specifier>s
 *            | F | F_nullable | T | L | U(+) | U(?)
 *
 * <access-path-value> := <access-path> : <value>
 *
 * <access-path-value-list> := <access-path-value>
 *                            | <access-path-value> <access-path-value-list>
 *
 * <composite-value> :=  { <access-path-value-list> } <existence>?
 *                   | [ <value> ]  <existence>?
 *
 * <existence> := <size-specifier>@
 *
 * <size-specifier> := <integer> | .* | ? | epsilon
 *
 *
 * examples:
 *
 * json_extract(pos, size, "{ (key) : d, (key) : .*s }", &i)
 *
 * sized_buffer ** list;
 * json_extract(pos, size, "[ L ]", &list);
 *
 *
 * json_inject(pos, size, "{  (key) : d, (key) : |abc| }", i);
 *
 *
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include "json-common.h"
#define N_PATH_MAX 8
#define KEY_MAX 128

#define JSMN_STATIC  // dont expose jsmn symbols
#define JSMN_PARENT_LINKS // add parent links to jsmn_tok, which are needed
#define JSMN_STRICT  // parse json in strict mode
#include "jsmn.h"
#include "ntl.h"
#include "json-actor.h"

enum actor {
  EXTRACTOR = 1,
  INJECTOR
};

/* 
 * the maximum levels of nested json object/array
 */
#define MAX_NESTED_LEVEL  16
#define MAX_ACTOR_NUMBERS 64

struct stack {
  unsigned char array[MAX_NESTED_LEVEL];
  int top;

  struct access_path ** paths;
  struct access_path * cur_path;

  struct value ** values;
  struct value * cur_value;
  enum actor actor;
};

#define PUSH(stack, c)  { stack->array[stack->top++] = c; }
#define TOP(stack)      (stack->array[stack->top-1])
#define POP(stack)      (stack->array[--stack->top])

struct access_path {
  struct sized_buffer key;
  struct access_path * next;
};

static void
print_access_path (FILE * fp, struct access_path * access_path)
{
  fprintf(fp, "|%.*s|", access_path->key.size, access_path->key.start);
  if (access_path->next)
    print_access_path(fp, access_path->next);
}

struct access_path_value;

struct size_specifier {
  enum {
    UNKNOWN_SIZE = 0,
    FIXED_SIZE,
    PARAMETERIZED_SIZE,
    ZERO_SIZE
  } tag;
  union {
    size_t fixed_size;
    size_t parameterized_size;
  } _;
};

enum builtin_type {
  B_BOOL = 1,
  B_INT,
  B_LONG,
  B_LONG_LONG,
  B_FLOAT,
  B_DOUBLE,
  B_STRING,
  B_TOKEN,
  B_LIST
};

struct action {
  enum {
    BUILT_IN = 0,
    USER_DEF_ACCEPT_NON_NULL,
    USER_DEF_ACCEPT_NULL
  } tag;
  union {
    enum builtin_type builtin;
    int (*user_def)(char *, size_t, void *p);
  } _;
  /*
   * must be a pointer, and it cannot be NULL
   * this can be NULL or its value can be UNDEFINED
   */
  void * operand;
  struct size_specifier mem_size; // this designates the memory size of _;
};

struct existence {
  struct size_specifier mem_size;
  void * arg;
  bool has_this;
};

static void
print_action (FILE * fp, struct action * v)
{
  if (BUILT_IN == v->tag)
    fprintf(fp, "builtin(%d)\n", v->_.builtin);
  else
    fprintf(fp, "funptr(%p)\n", v->_.user_def);
}

struct value {
  enum {
    JSON_PRIMITIVE = 1,
    JSON_COMPOSITE_VALUE,
    JSON_ACTION,
  } tag;
  union {
    struct sized_buffer primitve;
    struct composite_value * cv;
    struct action action;
  } _;
};

static void
print_composite_value (FILE * fp, struct composite_value * cv);

static void
print_value (FILE * fp, struct value * v) {
  fprintf(fp, "tag_%d ", v->tag);

  switch (v->tag)
  {
    case JSON_PRIMITIVE:
      fprintf(fp, "%.*s\n", v->_.primitve.size, v->_.primitve.start);
      break;
    case JSON_COMPOSITE_VALUE:
      print_composite_value(fp, v->_.cv);
      break;
    case JSON_ACTION:
      print_action (fp, &v->_.action);
      break;
    default:
      break;
  }
}

struct access_path_value {
  struct access_path path;
  struct value value;
};

static void
print_access_path_value (FILE * fp, struct access_path_value *p)
{
  print_access_path(fp, &p->path);
  fprintf(fp, " : ");
  print_value(fp, &p->value);
}

struct sized_access_path_value {
  struct access_path_value * pos;
  size_t size;
};

struct sized_value {
  struct value * pos;
  size_t size;
};

struct composite_value {
  enum {
    ARRAY = 1,
    OBJECT
  } tag;
  union {
    struct sized_value elements;
    struct sized_access_path_value pairs;
  } _;
  struct existence E;
};

static void
print_composite_value (FILE * fp, struct composite_value * cv)
{
  if (cv->tag == ARRAY) {
    for (size_t i = 0; i < cv->_.elements.size; i++)
      print_value(fp, cv->_.elements.pos+i);
  }
  else {
    for (size_t i = 0; i < cv->_.pairs.size; i++)
      print_access_path_value(fp, cv->_.pairs.pos+i);
  }
  if (cv->E.has_this) {
    fprintf(fp, "@");
  }
}

static int is_primitive (
  struct stack * stack,
  char * pos,
  size_t size,
  char ** next_pos_p)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  unsigned char c;

  c = * pos;

  switch (c)
  {
    case 't': // true
      if (pos + 3 < end_pos
          && 'r' == pos[1] && 'u' == pos[2] && 'e' == pos[3]) {
        pos += 4;
        goto return_true;
      }
      break;
    case 'f': // false
      if (pos + 4 < end_pos
          && 'a' == pos[1] && 'l' == pos[2] && 's' == pos[3] && 'e' == pos[4]) {
        pos += 5;
        goto return_true;
      }
      break;
    case 'n': // null
      if (pos + 3 < end_pos
          && 'u' == pos[1] && 'l' == pos[2] && 'l' == pos[3]) {
        pos += 4;
        goto return_true;
      }
      break;
    case '"': // a string literal
      pos ++;
      while (pos < end_pos) {
        c = *pos; pos ++;
        if ('"' == c)
          goto return_true;
      }
      break;
    case '|': // a proprietary string literal
      pos ++;
      while (pos < end_pos) {
        c = *pos; pos ++;
        if ('|' == c)
          goto return_true;
      }
      break;
    default:
      if ('0' <= c && c <= '9') {
        pos++;
        while (pos < end_pos) {
          c = *pos;
          if (' ' == c || ',' == c || c == TOP(stack)) goto return_true;
          else if ('.' == c || '0' <= c || c <= '9') pos++;
          else {
            ERR("unexpected %c in %s\n", c, start_pos);
          }
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
  char * const start_pos = pos, * const end_pos = pos + size, * x;
  long fixed_size = strtol(start_pos, &x, 10);

  if (x != start_pos) {
    if (fixed_size <= 0)
      ERR("size has to be a non-zero postive value %ld\n", fixed_size);

    p->tag = FIXED_SIZE;
    p->_.fixed_size = fixed_size;
    *next_pos_p = x; // jump to the end of number
    return 1;
  }
  else if (pos + 1 < end_pos && '.' == *pos && '*' == *(pos+1)) {
    p->tag = PARAMETERIZED_SIZE;
    *next_pos_p = pos + 2;
    return 1;
  }
  else if ('?' == *pos) {
    p->tag = ZERO_SIZE;
    *next_pos_p = pos + 1;
    return 1;
  }
  return 0;
}

static int
parse_value(
  struct stack * stack,
  char *pos,
  size_t size,
  struct value * p,
  char ** next_pos_p)
{
  char * const end_pos = pos + size;

  char *next_pos = NULL;
  if (is_primitive(stack, pos, size, &next_pos)) {
    p->tag = JSON_PRIMITIVE;
    p->_.primitve.start = pos;
    p->_.primitve.size = next_pos - pos;
    *next_pos_p = next_pos;
    return 1;
  }
  struct action * act = &p->_.action;
  p->tag = JSON_ACTION;
  int has_size_specifier = 0;

  if (parse_size_specifier(pos, end_pos - pos,
                           &act->mem_size, &next_pos)) {
    pos = next_pos;
    has_size_specifier = 1;
  }

  act->tag = BUILT_IN;
  switch(*pos)
  {
    case 'b':
      act->mem_size._.fixed_size = sizeof(bool);
      act->mem_size.tag = FIXED_SIZE;
      act->_.builtin = B_BOOL;
      pos ++;
      goto return_true;
    case 'd':
      act->mem_size._.fixed_size = sizeof(int);
      act->mem_size.tag = FIXED_SIZE;
      act->_.builtin = B_INT;
      pos ++;
      goto return_true;
    case 'f':
      act->mem_size._.fixed_size = sizeof(float);
      act->mem_size.tag = FIXED_SIZE;
      act->_.builtin = B_FLOAT;
      pos ++;
      goto return_true;
    case 'l':
      if (STRNEQ(pos, "ld", 2)) {
        act->mem_size._.fixed_size = sizeof(long);
        act->mem_size.tag = FIXED_SIZE;
        act->_.builtin = B_LONG;
        pos += 2;
        goto return_true;
      }
      else if (STRNEQ(pos, "lld", 3)) {
        act->mem_size._.fixed_size = sizeof(long long);
        act->mem_size.tag = FIXED_SIZE;
        act->_.builtin = B_LONG_LONG;
        pos += 3;
        goto return_true;
      }
      else if (STRNEQ(pos, "lf", 2)) {
        act->mem_size._.fixed_size = sizeof(double);
        act->mem_size.tag = FIXED_SIZE;
        act->_.builtin = B_DOUBLE;
        pos += 2;
        goto return_true;
      }
      else
        ERR("unexpected %s\n", *pos);
      break;
    case 's':
      act->_.builtin = B_STRING;
      pos ++;
      goto return_true;
    case 'L':
      act->_.builtin = B_LIST;
      pos ++;
      goto return_true;
    case 'F':
      if (STRNEQ(pos, "F_nullable", 10)) {
        act->tag = USER_DEF_ACCEPT_NULL;
        pos += 10;
      }
      else {
        act->tag = USER_DEF_ACCEPT_NON_NULL;
        pos++;
      }
      goto return_true;
    case 'T':
      act->_.builtin = B_TOKEN;
      pos ++;
      goto return_true;
    default:
      if (TOP(stack) == *pos) {
        if (has_size_specifier)
          ERR("size specifier '.' or '.*' should be followed by 's' \n");
        return 0;
      }
      else
        ERR("unexpected %c\n", *pos);
  }

return_true:
  *next_pos_p = pos;
  return 1;
}

static int
parse_existence(char *pos, size_t size, struct existence * p, char ** next_pos_p)
{
  if (size == 0)
    return 0;

  char * next_pos = NULL;
  if (parse_size_specifier(pos, size, &p->mem_size, &next_pos))
    pos = next_pos;

  if ('@' == *pos) {
    p->has_this = true;
    pos ++;
    *next_pos_p = pos;
    return 1;
  }
  return 0;
}

static char * 
parse_composite_value(struct stack *, char *, size_t, struct composite_value *);

#define SKIP_SPACES(s, end)   { while (s < end && isspace(*s)) ++s; }

static char *
parse_access_path_value(
  struct stack *stack,
  char *pos,
  size_t size,
  struct access_path_value *av,
  struct access_path *curr_path)
{
  // until find a ']' or '\0'
  char * const start_pos = pos, * const end_pos = pos + size,
    * next_pos = NULL;

  ASSERT_S('(' == *pos, "expecting '('");
  pos ++;
  while (*pos && pos < end_pos) {
    if (')' == *pos) break;
    ++pos;
  }

  ASSERT_S(')' == *pos, "A close bracket ')' is missing");

  int len = pos - start_pos - 1;
  ASSERT_S(len > 0, "Key is missing");

  curr_path->key.start = calloc(1, len); // @todo get memory from stack's pool
  curr_path->key.size = len;
  memcpy(curr_path->key.start, start_pos+1, len);

  ++pos; // eat up ')'
  SKIP_SPACES(pos, end_pos);
  struct access_path * next_path;
  switch (*pos)
  {
    case '(':
      next_path = calloc(1, sizeof(struct access_path));
      curr_path->next = next_path;
      return parse_access_path_value(stack, pos, end_pos - pos, av, next_path);
    case ':':
      ++pos; // eat up ':'
      SKIP_SPACES(pos, end_pos);
      if ('[' == *pos || '{' == *pos) {
        struct composite_value * cv = calloc(1, sizeof(struct composite_value));
        av->value._.cv = cv;
        av->value.tag = JSON_COMPOSITE_VALUE;
        pos = parse_composite_value(stack, pos, end_pos - pos, cv);
      }
      else if (parse_value(stack, pos, end_pos - pos, &av->value, &next_pos))
        pos = next_pos;
      else
        ERR("expecting a value after ':', %s does not have a legit value", pos);
      break;
    default:
      ERR("expecting '(', or ':', but getting %c\n", *pos);
  }
  return pos;
}

static char *
parse_access_path_value_list(
  struct stack * stack,
  char * pos,
  size_t size,
  struct sized_access_path_value * pairs)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  pairs->pos = calloc(20, sizeof(struct access_path_value));

  size_t i = 0;
  while (pos < end_pos) {
    SKIP_SPACES(pos, end_pos);
    if (0 != i && ',' == *pos) {
      pos ++;
      continue;
    }
    else if ('(' == *pos) {
      pos = parse_access_path_value(stack, pos, end_pos - pos,
                              pairs->pos + i, &pairs->pos[i].path);
      i++;
    }
    else if (0 == stack->top || TOP(stack) == *pos ) {
      pairs->size = i;
      return pos;
    }
    else
      ERR("Expecting %c, but found %c in %s", TOP(stack), *pos, start_pos);
  }
  pairs->size = i;
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
    if (0 != i && ',' == * pos) {
      pos ++;
      continue;
    }
    else if (parse_value(stack, pos, end_pos - pos, elements->pos+i, &next_pos)) {
      i++;
      pos = next_pos;
    }
    else if (TOP(stack) == *pos) {
      elements->size = i;
      return pos;
    }
    else {
      ERR("Unexpected %c in %s", *pos, pos);
    }
  }
  elements->size = i;
  return pos;
}

static struct stack stack = { .array = {0}, .top = 0, .actor = INJECTOR };

static char *
parse_composite_value(
  struct stack *stack,
  char *pos,
  size_t size,
  struct composite_value *cv)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  char * next_pos, c;

  SKIP_SPACES(pos, end_pos);
  switch(*pos)
  {
    case '{':
      cv->tag = OBJECT;
      pos++;
      PUSH(stack, '}');
      pos = parse_access_path_value_list(stack, pos, end_pos - pos, &cv->_.pairs);
      c = POP(stack);
      if (c != *pos)
        ERR("Mismatched stack: expecting %c, but getting %c\n", c, *pos);
      pos++;
      SKIP_SPACES(pos, end_pos);
      if (parse_existence(pos, end_pos - pos, &cv->E, &next_pos))
        pos = next_pos;
      break;
    case '[':
      cv->tag = ARRAY;
      pos++;
      PUSH(stack, ']');
      pos = parse_value_list(stack, pos, end_pos - pos, &cv->_.elements);
      c = POP(stack);
      if (c != *pos)
        ERR("Mismatched stack: expecting %c, but getting %c\n", c, *pos);
      pos++;
      SKIP_SPACES(pos, end_pos);
      if (parse_existence(pos, end_pos - pos, &cv->E, &next_pos))
        pos = next_pos;
      break;
    default:
      ERR("unexpected %c in %s\n", *pos, start_pos);
  }
  return pos;
}

static char *
parse_toplevel(
  struct stack *stack,
  char *pos,
  size_t size,
  struct composite_value *cv)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  SKIP_SPACES(pos, end_pos);
  while (pos < end_pos) {
    if ('{' == *pos || '[' == *pos) {
      pos = parse_composite_value(stack, pos, end_pos - pos, cv);
    }
    else if ('(' == *pos) {
      cv->tag = OBJECT;
      pos = parse_access_path_value_list(stack, pos, end_pos - pos, &cv->_.pairs);
      SKIP_SPACES(pos, end_pos);
      char * next_pos = NULL;
      if (parse_existence(pos, end_pos - pos, &cv->E, &next_pos))
        pos = next_pos;
    }
    SKIP_SPACES(pos, end_pos);
    if (pos == end_pos) {
      return pos;
    }
    else if (pos != end_pos) {
      ERR("unexpected %s\n", pos);
    }
  }
}

struct recipients {
  void * addrs[MAX_ACTOR_NUMBERS];
  size_t pos;
};

static void
collect_composite_value_recipients (
  struct composite_value *cv,
  struct recipients * rec);

static void
collect_value_recipients (struct value *v, struct recipients *rec)
{
  struct action * act;
  switch (v->tag)
  {
    case JSON_ACTION:
      act = &v->_.action;
      switch (act->tag)
      {
        case BUILT_IN:
          if (PARAMETERIZED_SIZE == act->mem_size.tag) {
            rec->addrs[rec->pos] = &act->mem_size._.parameterized_size;
            rec->pos ++;
          }
          rec->addrs[rec->pos] = &act->operand;
          rec->pos ++;
          break;
        case USER_DEF_ACCEPT_NON_NULL:
        case USER_DEF_ACCEPT_NULL:
          rec->addrs[rec->pos] = &act->_.user_def;
          rec->pos ++;
          rec->addrs[rec->pos] = &act->operand;
          rec->pos ++;
          break;
      }
      break;
    case JSON_COMPOSITE_VALUE:
      collect_composite_value_recipients(v->_.cv, rec);
      break;
    case JSON_PRIMITIVE:
      break;
  }
}

static void
collect_composite_value_recipients (
  struct composite_value *cv,
  struct recipients * rec)
{
  struct access_path_value *apv;
  struct value *v;
  switch(cv->tag)
  {
    case OBJECT:
      for (size_t i = 0; i < cv->_.pairs.size; i++) {
        apv = cv->_.pairs.pos + i;
        collect_value_recipients(&apv->value, rec);
      }
      break;
    case ARRAY:
      for (size_t i = 0; i < cv->_.elements.size; i++) {
        v = cv->_.elements.pos + i;
        collect_value_recipients(v, rec);
      }
      break;
  }
}


/*
 * write only buffer, it's data should never be trusted
 * it is used to simplify the calculation of bytes needed
 * for json_injector.
 */
static char write_only [1024*10];

struct injection_info {
  char * next_pos;
  void * data;
  struct stack sp;
  FILE * fp;
};

static int
xprintf(
  char * pos,
  size_t size,
  struct injection_info * info,
  char * format, ...)
{
  int ret1 = 0, ret2 = 0;
  va_list ap;
  va_start(ap, format);
  ret1 = vsnprintf(pos, size, format, ap);
  va_end(ap);
  ASSERT_S(ret1 >= 0, "vsnprintf");

  if (info->fp) {
    va_list ap;
    va_start(ap, format);
    ret1 = vfprintf(info->fp, format, ap);
    va_end(ap);
    ASSERT_S(ret2 >= 0, "vfprintf");
    ASSERT_S(ret1 == ret1, "errror");
  }

  if (NULL == pos)
    info->next_pos = NULL;
  else
    info->next_pos = pos + ret1;
  return ret1;
}


static int
inject_builtin (char * pos, size_t size, struct injection_info * info)
{
  struct action * v = (struct action *) info->data;
  if (NULL == v->operand)
    return xprintf(pos, size, info, "null");

  char *s;
  switch(v->_.builtin)
  {
    case B_BOOL:
      if (*(int *)v->operand)
        return xprintf(pos, size, info, "true");
      else
        return xprintf(pos, size, info, "false");
    case B_INT:
      return xprintf(pos, size, info, "%d", v->operand);
    case B_FLOAT:
      return xprintf(pos, size, info, "%f", v->operand);
    case B_DOUBLE:
      return xprintf(pos, size, info, "%lf", v->operand);
    case B_STRING:
      s = (char *) v->operand;
      switch (v->mem_size.tag)
      {
        case UNKNOWN_SIZE:
          return xprintf(pos, size, info, "\"%s\"", s);
        case FIXED_SIZE:
          return xprintf(pos, size, info, "\"%.*s\"", v->mem_size._.fixed_size, s);
        case PARAMETERIZED_SIZE: {
          int ms = (int) v->mem_size._.parameterized_size;
          return xprintf(pos, size, info, "\"%.*s\"", ms, s);
        }
        case ZERO_SIZE:
          return xprintf(pos, size, info, "\"%s\"", s);
      }
      break;
    default:
      ERR("unexpected cases\n");
      break;
  }
}

static int inject_composite_value (char *, size_t, struct injection_info * );

static int
inject_value (char * pos, size_t size, struct injection_info * info)
{
  struct value * v = (struct value *)info->data;
  switch (v->tag) {
    case JSON_ACTION: {
      struct action *a = &v->_.action;
      switch (a->tag)
      {
        case BUILT_IN:
          info->data = a;
          return inject_builtin(pos, size, info);
        case USER_DEF_ACCEPT_NON_NULL:
        case USER_DEF_ACCEPT_NULL:
        {
          int (*f)(char *, size_t, void *);
          f = a->_.user_def;
          if (info->fp) {
            char *b = malloc(1024);
            (*f)(b, sizeof(b), a->operand);
            fprintf(info->fp, "%s", b);
            free(b);
          }
          size_t used_bytes = (*f)(pos, size, a->operand);
          if (NULL == pos)
            info->next_pos = NULL;
          else
            info->next_pos = pos + used_bytes;
          return used_bytes;
        }
      }
      ERR("should not be here");
    }
    case JSON_COMPOSITE_VALUE:
      info->data = v->_.cv;
      return inject_composite_value(pos, size, info);
    case JSON_PRIMITIVE:
      return xprintf(pos, size, info, "%.*s",
                     v->_.primitve.size,
                     v->_.primitve.start);
  }
}

static int
inject_access_path_value (char * pos, size_t size, struct injection_info * info)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  struct access_path_value * ap = (struct access_path_value *) info->data;
  size_t used_bytes = 0;
  used_bytes += xprintf(pos, size, info, "\"%.*s\"", ap->path.key.size,
                        ap->path.key.start);
  pos = info->next_pos;
  if (ap->path.next) {
    // @todo
  }
  else {
    used_bytes += xprintf(pos, end_pos - pos, info, ":");
    pos = info->next_pos;

    info->data = &ap->value;
    used_bytes += inject_value(pos, end_pos - pos, info);
    pos = info->next_pos;
    return used_bytes;
  }
}

static int
inject_composite_value (char * pos, size_t size, struct injection_info * info)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  size_t used_bytes = 0;

  struct composite_value * cv = (struct composite_value *) info->data;
  switch(cv->tag)
  {
    case OBJECT:
      used_bytes += xprintf(pos, end_pos - pos, info, "{");
      pos = info->next_pos;

      for (size_t i = 0; i < cv->_.pairs.size; i++) {
        info->data = cv->_.pairs.pos + i;
        used_bytes += inject_access_path_value(pos, end_pos - pos, info);
        pos = info->next_pos;

        if (i+1 != cv->_.pairs.size) {
          used_bytes += xprintf(pos, end_pos - pos, info, ",");
          pos = info->next_pos;
        }
      }
      used_bytes += xprintf(pos, end_pos - pos, info, "}");
      pos = info->next_pos;
      break;
    case ARRAY:
      used_bytes += xprintf(pos, end_pos - pos, info, "[");
      pos = info->next_pos;
      for (size_t i = 0; i < cv->_.elements.size; i++) {
        info->data = cv->_.elements.pos + i;
        used_bytes += inject_value(pos, end_pos - pos, info);
        pos = info->next_pos;

        if (i+1 != cv->_.elements.size) {
          used_bytes += xprintf(pos, end_pos - pos, info, ",");
          pos = info->next_pos;
        }
      }
      used_bytes += xprintf(pos, end_pos - pos, info, "]");
      pos = info->next_pos;
      break;
  }
  return used_bytes;
}

int
json_injector_va_list(
  char * pos,
  size_t size,
  char * injector,
  va_list ap)
{
  struct stack stack = { .array = {0}, .top = 0, .actor = INJECTOR };
  struct composite_value cv;
  memset(&cv, 0, sizeof(struct composite_value));
  size_t len = strlen(injector);
  char * next_pos = parse_toplevel(&stack, injector, len, &cv);
  if (next_pos != injector + len) {
    ERR("unexpected %s\n", next_pos);
  }

  struct recipients  rec = { 0 };
  collect_composite_value_recipients(&cv, &rec);

  for (size_t i = 0; i < rec.pos; i++)
    *((void **) rec.addrs[i]) = va_arg(ap, void *);

  struct injection_info info = { 0 };
  char * mem = NULL;
  size_t mem_size;
  if (1)
    info.fp = NULL;
  else
    info.fp = open_memstream(&mem, &mem_size);

  info.data = &cv;
  char * output_buf;
  size_t output_size;
  if (NULL == pos) {
    output_buf = NULL;//write_only;
    output_size = 0; //sizeof(write_only);
  }
  else {
    output_buf = pos;
    output_size = size;
  }
  size_t used_bytes = inject_composite_value(output_buf, output_size, &info);
  if (info.fp)
    fclose(info.fp);

  if (mem) {
    ASSERT_S(used_bytes == mem_size, "snprint.size != open_memstream.size");
    //fprintf(stderr, "%s\n", write_only);
    if (mem) {
      //fprintf(stderr, "%s\n", mem);
      free(mem);
    }
  }
  return used_bytes;
}

int
json_inject_alloc(char ** buf_p, size_t * size_p, char * injector, ...)
{
  va_list ap;
  va_start(ap, injector);
  size_t used_bytes = json_injector_va_list(NULL, 0, injector, ap);
  va_end(ap);

  char * buf = malloc(used_bytes+1);
  *size_p = used_bytes+1;
  *buf_p = buf;

  va_start(ap, injector);
  json_injector_va_list(buf, used_bytes+1, injector, ap);
  va_end(ap);
  return used_bytes;
}

int json_inject (char * pos, size_t size, char * injector, ...)
{
  va_list ap;
  va_start(ap, injector);
  size_t used_bytes = json_injector_va_list(pos, size, injector, ap);
  va_end(ap);
  return used_bytes;
}