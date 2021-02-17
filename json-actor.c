/*
 *
 * json actor (injector or extractor) specification grammar
 *
 * <injector> := <composite-value> <existence>?
 *               | <access-path-value-list> <existence>?
 *
 * <extractor> := <composite-value> <existence>?
 *                | <access-path-value-list> <existence>?
 *                | [ # ]
 *
 * <access-path> := (<key>) | (<key>) <access-path>
 *
 * <value> := true | false | null | <int> | <float> | <string-literal>
 *            | <composite-value> | <action>
 *
 * <action> := d | ld | lld | f | lf | b | <size-specifier>s
 *            | F | F_nullable
 *
 * <access-path-value> := <access-path> : <value>
 *
 * <access-path-value-list> := <access-path-value>
 *                            | <access-path-value> <access-path-value-list>
 *
 * <composite-value> :=  { <access-path-value-list> } | [ <value> ]
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

#define JSMN_STATIC  // dont expose jsmn symbols
#define JSMN_PARENT_LINKS // add parent links to jsmn_tok, which are needed
#define JSMN_STRICT  // parse json in strict mode
#include "jsmn.h"
#include "ntl.h"
#include "json-actor.h"

static void assert_is_pointer(void * p)
{
  if (NULL == p)
    return;

  /*
   * This is a poor man's method to check if
   * p is a legit pointer.
   */
  char * x = (char *)p;
  static char c; //has to be a static variable such that compilers won't remove them
  c = *x;
}


extern char *
json_escape_string (size_t * output_len_p, char * input, size_t input_len);


enum actor {
  EXTRACTOR = 1,
  INJECTOR
};

/* 
 * the maximum levels of nested json object/array
 */
#define MAX_NESTED_LEVELS  16
#define MAX_ACTION_NUMBERS 64

struct stack {
  unsigned char array[MAX_NESTED_LEVELS];
  int top;

  struct access_path ** paths;
  struct access_path * cur_path;

  struct value ** values;
  struct value * cur_value;
  enum actor actor;
};


static void PUSH(struct stack * s, char c)
{
  ASSERT_S(s->top < MAX_NESTED_LEVELS,
           "too many nested objects exceeding"
           " the max nested levels: 16");
  s->array[s->top] = c;
  s->top ++;
}

static char TOP(struct stack * s)
{
  return s->array[s->top-1];
}

static char POP(struct stack * s)
{
  --s->top;
  return s->array[s->top];
}

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
    SIZE_UNKNOWN = 0,
    SIZE_FIXED,
    SIZE_PARAMETERIZED,
    SIZE_ZERO
  } tag;
  size_t size;
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
enum action_type {
  ACT_BUILT_IN = 0,
  ACT_USER_DEF_ACCEPT_NON_NULL,
  ACT_USER_DEF_ACCEPT_NULL,
  ACT_USER_DEF_ACCEPT_NON_NULL_ENCLOSED,
  ACT_USER_DEF_ACCEPT_NULL_ENCLOSED,
  ACT_FORMAT_STRING = 10,
};

enum arg_type {
  ARG_PTR = 0,
  ARG_INT,
  ARG_DOUBLE
};


struct fmt_arg {
  enum arg_type tag;
  union {
    void * ptr;
    int  integer;
    //double real;
  }_;
};
struct action {
  enum action_type tag;
  union {
    enum builtin_type builtin;
    struct sized_buffer fmt;
    int (*user_def)(char *, size_t, void *p);
  } _;
  /*
   * must be a pointer, and it cannot be NULL
   * this can be NULL or its value can be UNDEFINED
   */
  struct fmt_arg fmt_args[8]; // no more than 8 arguments
  void * operand;
  struct size_specifier mem_size; // this designates the memory size of _;
};

struct existence {
  struct size_specifier mem_size;
  void * arg;
  int    sizeof_arg;
  bool has_this;
};

static void
print_action (FILE * fp, struct action * v)
{
  if (ACT_BUILT_IN == v->tag)
    fprintf(fp, "builtin(%d)\n", v->_.builtin);
  else
    fprintf(fp, "funptr(%p)\n", v->_.user_def);
}

enum value_type {
  V_COMPOSITE_VALUE = 1,
  V_ACTION,
  V_PRIMITIVE = 10,
  V_STRING_LITERAL,
};

struct value {
  enum value_type tag;
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
    case V_COMPOSITE_VALUE:
      print_composite_value(fp, v->_.cv);
      break;
    case V_ACTION:
      print_action (fp, &v->_.action);
      break;
    case V_STRING_LITERAL:
    {
      size_t len;
      char * p = json_escape_string (&len, v->_.primitve.start,
                                     v->_.primitve.size);
      fprintf(fp, "\"%.*s\"\n", len, p);
      break;
    }
    default:
      fprintf(fp, "%.*s\n", v->_.primitve.size, v->_.primitve.start);
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
  int is_object; // otherwise, it is an array
  union {
    struct sized_value elements;
    struct sized_access_path_value pairs;
  } _;
  struct existence E;
};

static void
print_composite_value (FILE * fp, struct composite_value * cv)
{
  if (cv->is_object) {
    for (size_t i = 0; i < cv->_.pairs.size; i++)
      print_access_path_value(fp, cv->_.pairs.pos + i);
  }
  else {
    for (size_t i = 0; i < cv->_.elements.size; i++)
      print_value(fp, cv->_.elements.pos + i);
  }

  if (cv->E.has_this) {
    fprintf(fp, "@");
  }
}

/*
 * we only count how many format specifiers are used
 * @todo analyze what format specifiers are used.
 */
static int has_format_string (char * pos, char * end_pos)
{
  int count = 0;
  while (pos < end_pos) {
    if ('%' == *pos) {
      if (pos+1 == end_pos)
        ERR("dangling format %s string is not allowed\n", pos);
      pos ++;
      switch (*pos)
      {
        case '%': // escaped %
          pos++;
          break;
        case '.':
          if (pos + 2 < end_pos && '*' == *(pos+1) && 's' == *(pos+2)) {
            count += 2;
            pos += 3;
          }
          break;
        default: // other format string
          count ++;
          pos ++;
          break;
      }
    }
    else
      pos ++;
  }
  return count;
}

static int is_primitive (
  struct stack * stack,
  char * pos,
  size_t size,
  char ** next_pos_p,
  enum value_type * type)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  unsigned char c;
  int has_format_string;

  c = * pos;

  *type = V_PRIMITIVE;
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
      *type = V_STRING_LITERAL;
      pos ++;
      while (pos < end_pos) {
        c = *pos; pos ++;
        if ('"' == c)
          goto return_true;
      }
      break;
    case '|': // a proprietary string literal
      if (STRNEQ("|F|", pos, 3)) {
        *type = V_ACTION;
        return 0;
      }
      *type = V_STRING_LITERAL;
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

    p->tag = SIZE_FIXED;
    p->size = fixed_size;
    *next_pos_p = x; // jump to the end of number
    return 1;
  }
  else if (pos + 1 < end_pos && '.' == *pos && '*' == *(pos+1)) {
    p->tag = SIZE_PARAMETERIZED;
    *next_pos_p = pos + 2;
    return 1;
  }
  else if ('?' == *pos) {
    p->tag = SIZE_ZERO;
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
  char * const end_pos = pos + size, * next_pos;
  enum value_type v_type;

  if (is_primitive(stack, pos, size, &next_pos, &v_type)) {
    p->tag = v_type;
    p->_.primitve.start = pos;
    p->_.primitve.size = next_pos - pos;
    if (v_type == V_STRING_LITERAL) {
      // skip the two delimiter
      p->_.primitve.start ++;
      p->_.primitve.size -= 2;
      int n = has_format_string(p->_.primitve.start,
                                p->_.primitve.start + p->_.primitve.size);
      if (n) {
        char * x = p->_.primitve.start;
        size_t s = p->_.primitve.size;
        p->_.action._.fmt.start = x;
        p->_.action._.fmt.size = s;
        p->tag = V_ACTION;
        p->_.action.tag = ACT_FORMAT_STRING + n;
      }
    }
    *next_pos_p = next_pos;
    return 1;
  }
  struct action * act = &p->_.action;
  p->tag = V_ACTION;
  int has_size_specifier = 0;

  if (parse_size_specifier(pos, end_pos - pos,
                           &act->mem_size, &next_pos)) {
    pos = next_pos;
    has_size_specifier = 1;
  }

  act->tag = ACT_BUILT_IN;
  switch(*pos)
  {
    case 'b':
      act->mem_size.size = sizeof(bool);
      act->mem_size.tag = SIZE_FIXED;
      act->_.builtin = B_BOOL;
      pos ++;
      goto return_true;
    case 'd':
      act->mem_size.size = sizeof(int);
      act->mem_size.tag = SIZE_FIXED;
      act->_.builtin = B_INT;
      pos ++;
      goto return_true;
    case 'f':
      act->mem_size.size = sizeof(float);
      act->mem_size.tag = SIZE_FIXED;
      act->_.builtin = B_FLOAT;
      pos ++;
      goto return_true;
    case 'l':
      if (STRNEQ(pos, "ld", 2)) {
        act->mem_size.size = sizeof(long);
        act->mem_size.tag = SIZE_FIXED;
        act->_.builtin = B_LONG;
        pos += 2;
        goto return_true;
      }
      else if (STRNEQ(pos, "lld", 3)) {
        act->mem_size.size = sizeof(long long);
        act->mem_size.tag = SIZE_FIXED;
        act->_.builtin = B_LONG_LONG;
        pos += 3;
        goto return_true;
      }
      else if (STRNEQ(pos, "lf", 2)) {
        act->mem_size.size = sizeof(double);
        act->mem_size.tag = SIZE_FIXED;
        act->_.builtin = B_DOUBLE;
        pos += 2;
        goto return_true;
      }
      else
        ERR("unexpected %s\n", pos);
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
        act->tag = ACT_USER_DEF_ACCEPT_NULL;
        pos += 10;
      }
      else {
        act->tag = ACT_USER_DEF_ACCEPT_NON_NULL;
        pos++;
      }
      goto return_true;
    case '|':
      if (STRNEQ(pos, "|F|", 3)) {
        act->tag = ACT_USER_DEF_ACCEPT_NON_NULL_ENCLOSED;
        pos += 3;
        goto return_true;
      }
      else if (STRNEQ(pos, "|F_nullable|", 3)) {
        act->tag = ACT_USER_DEF_ACCEPT_NULL_ENCLOSED;
        pos += 3;
        goto return_true;
      }
      else
        ERR("Unexpected case %s\n", pos);
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
  char * const start_pos = pos, * const end_pos = pos + size,
    * next_pos = NULL;

  ASSERT_S('(' == *pos || '|' == *pos, "expecting '(' or '|'");
  pos ++;
  while (*pos && pos < end_pos) {
    if (')' == *pos || '|' == *pos) break;
    ++pos;
  }

  ASSERT_S(')' == *pos || '|' == *pos, "A close bracket ')' or '|' is missing");

  int len = pos - start_pos - 1;
  ASSERT_S(len > 0, "Key is missing");

  curr_path->key.start = start_pos + 1;
  curr_path->key.size = len;

  ++pos; // eat up ')'
  SKIP_SPACES(pos, end_pos);
  struct access_path * next_path;
  switch (*pos)
  {
    case '(':
    case '|':
      next_path = calloc(1, sizeof(struct access_path));
      curr_path->next = next_path;
      return parse_access_path_value(stack, pos, end_pos - pos, av, next_path);
    case ':':
      ++pos; // eat up ':'
      SKIP_SPACES(pos, end_pos);
      if ('[' == *pos || '{' == *pos) {
        struct composite_value * cv = calloc(1, sizeof(struct composite_value));
        av->value._.cv = cv;
        av->value.tag = V_COMPOSITE_VALUE;
        pos = parse_composite_value(stack, pos, end_pos - pos, cv);
      }
      else if (parse_value(stack, pos, end_pos - pos, &av->value, &next_pos))
        pos = next_pos;
      else
        ERR("expecting a value after ':', %s does not have a legit value", pos);
      break;
    default:
      ERR("expecting '(', '|', or ':', but getting %c\n", *pos);
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
  pairs->pos = calloc(MAX_ACTION_NUMBERS, sizeof(struct access_path_value));

  size_t i = 0;
  while (pos < end_pos) {
    SKIP_SPACES(pos, end_pos);
    if (0 != i && ',' == *pos) {
      pos ++;
      continue;
    }
    else if ('(' == *pos || '|' == *pos) {
      pos = parse_access_path_value(stack, pos, end_pos - pos,
                              pairs->pos + i, &pairs->pos[i].path);
      i++;
    }
    else if (0 == stack->top || TOP(stack) == *pos ) {
      ASSERT_S(i < MAX_ACTION_NUMBERS, "exceed max allowed actions\n");
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
  elements->pos = calloc(MAX_ACTION_NUMBERS, sizeof(struct value));
  char * next_pos = NULL;

  size_t i = 0;
  while (pos < end_pos) {
    SKIP_SPACES(pos, end_pos);
    if ('#' == * pos) {
      pos ++;
      if (0 != i)
        ERR ("# has to be the only symbol between []\n");

      SKIP_SPACES(pos, end_pos);
      if (TOP(stack) == *pos) {
        struct value * v = elements->pos;
        v->tag = V_ACTION;
        v->_.action.tag = ACT_BUILT_IN;
        v->_.action._.builtin = B_LIST;
        elements->size = 1;
        return pos;
      }
      else
        ERR ("# has to be the only symbol between []\n");
    }
    else if (0 != i && ',' == * pos) {
      pos ++;
      continue;
    }
    else if (parse_value(stack, pos, end_pos - pos, elements->pos+i, &next_pos)) {
      i++;
      pos = next_pos;
    }
    else if (TOP(stack) == *pos) {
      ASSERT_S(i < MAX_ACTION_NUMBERS, "exceed max allowed actions\n");
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
      cv->is_object = 1;
      pos++;
      PUSH(stack, '}');
      pos = parse_access_path_value_list(stack, pos, end_pos - pos, &cv->_.pairs);
      c = POP(stack);
      if (c != *pos)
        ERR("Mismatched stack: expecting %c, but getting %c\n", c, *pos);
      pos++;
      break;
    case '[':
      cv->is_object = 0;
      pos++;
      PUSH(stack, ']');
      pos = parse_value_list(stack, pos, end_pos - pos, &cv->_.elements);
      c = POP(stack);
      if (c != *pos)
        ERR("Mismatched stack: expecting %c, but getting %c\n", c, *pos);
      pos++;
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
    else if ('(' == *pos || '|' == *pos) {
      cv->is_object = 1;
      pos = parse_access_path_value_list(stack, pos, end_pos - pos, &cv->_.pairs);
    }
    SKIP_SPACES(pos, end_pos);
    char * next_pos = NULL;
    if (parse_existence(pos, end_pos - pos, &cv->E, &next_pos))
      pos = next_pos;
    SKIP_SPACES(pos, end_pos);
    if (pos == end_pos) {
      return pos;
    }
    else if (pos != end_pos) {
      ERR("unexpected %s\n", pos);
    }
  }
  return 0;
}

struct operand_addrs {
  void * addrs[MAX_ACTION_NUMBERS];
  enum arg_type types[MAX_ACTION_NUMBERS];
  char may_not_be_ptr[MAX_ACTION_NUMBERS];
  size_t pos;
};

static void
get_composite_value_operand_addrs (
  struct composite_value *cv,
  struct operand_addrs * rec);

static void
get_value_operand_addrs (struct value *v, struct operand_addrs *rec)
{
  struct action * act;
  switch (v->tag)
  {
    case V_ACTION:
      act = &v->_.action;
      switch (act->tag)
      {
        case ACT_BUILT_IN:
          if (SIZE_PARAMETERIZED == act->mem_size.tag) {
            rec->addrs[rec->pos] = &act->mem_size.size;
            rec->pos ++;
          }
          rec->addrs[rec->pos] = &act->operand;
          rec->pos ++;
          break;
        case ACT_USER_DEF_ACCEPT_NON_NULL:
        case ACT_USER_DEF_ACCEPT_NULL:
        case ACT_USER_DEF_ACCEPT_NON_NULL_ENCLOSED:
        case ACT_USER_DEF_ACCEPT_NULL_ENCLOSED:
          rec->addrs[rec->pos] = &act->_.user_def;
          rec->pos ++;
          rec->addrs[rec->pos] = &act->operand;
          rec->pos ++;
          break;
        default:
          if (act->tag > ACT_FORMAT_STRING) {
            int n = act->tag - ACT_FORMAT_STRING;
            for (int i = 0; i < n; i++) {
              //@todo analyze native format string
              // to find out the argument types
              rec->addrs[rec->pos] = &act->fmt_args[i]._;
              rec->may_not_be_ptr[rec->pos] = 1;
              rec->pos ++;
            }
          }
          break;
      }
      break;
    case V_COMPOSITE_VALUE:
      get_composite_value_operand_addrs(v->_.cv, rec);
      break;
    default:
      break;
  }
}

static void
get_composite_value_operand_addrs (
  struct composite_value *cv,
  struct operand_addrs * rec)
{
  struct access_path_value *apv;
  struct value *v;
  if(cv->is_object)
    for (size_t i = 0; i < cv->_.pairs.size; i++) {
      apv = cv->_.pairs.pos + i;
      get_value_operand_addrs(&apv->value, rec);
    }
  else
    for (size_t i = 0; i < cv->_.elements.size; i++) {
      v = cv->_.elements.pos + i;
      get_value_operand_addrs(v, rec);
    }

  if (cv->E.has_this) {
    rec->addrs[rec->pos] = &cv->E.arg;
    rec->types[rec->pos] = ARG_PTR;
    rec->pos ++;
    rec->addrs[rec->pos] = &cv->E.sizeof_arg;
    rec->types[rec->pos] = ARG_INT;
    rec->pos ++;
  }
}

static void free_composite_value (struct composite_value *cv);

static void free_value (struct value * v)
{
  if(V_COMPOSITE_VALUE == v->tag) {
    free_composite_value(v->_.cv);
    free(v->_.cv);
  }
}

static void free_access_path (struct access_path * p)
{
  if (p->next)
    free_access_path(p->next);
  free(p);
}

static void free_access_path_value (struct access_path_value * ap)
{
  if (ap->path.next)
    free_access_path(ap->path.next);
  free_value(&ap->value);
}

static void  free_composite_value (struct composite_value *cv)
{
  struct access_path_value *apv;
  struct value *v;
  if(cv->is_object) {
    for (size_t i = 0; i < cv->_.pairs.size; i++) {
      apv = cv->_.pairs.pos + i;
      free_access_path_value(apv);
    }
    free(cv->_.pairs.pos);
  }
  else {
    for (size_t i = 0; i < cv->_.elements.size; i++) {
      v = cv->_.elements.pos + i;
      free_value(v);
    }
    free(cv->_.elements.pos);
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
  struct stack sp;
  FILE * fp;
  struct existence * E;
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
inject_builtin (
  char * pos,
  size_t size,
  struct action * v,
  struct injection_info * info)
{
  if (NULL == v->operand)
    return xprintf(pos, size, info, "null");

  char *s;
  switch(v->_.builtin)
  {
    case B_BOOL:
      if (*(bool *)v->operand)
        return xprintf(pos, size, info, "true");
      else
        return xprintf(pos, size, info, "false");
    case B_INT:
      return xprintf(pos, size, info, "%d", *(int *)v->operand);
    case B_FLOAT:
      return xprintf(pos, size, info, "%f", *(float *)v->operand);
    case B_DOUBLE:
      return xprintf(pos, size, info, "%lf",*(double *)v->operand);
    case B_STRING:
    {
      s = (char *) v->operand;
      size_t len;
      int ret;
      char * escaped;
      switch (v->mem_size.tag)
      {
        case SIZE_UNKNOWN:
        case SIZE_ZERO:
          escaped = json_escape_string(&len, s, strlen(s));
          ret = xprintf(pos, size, info, "\"%.*s\"", len, escaped);
          if (escaped != s)
            free(escaped);
          return ret;
        case SIZE_FIXED:
          escaped = json_escape_string(&len, s, v->mem_size.size);
          ret = xprintf(pos, size, info, "\"%.*s\"", len, escaped);
          if (escaped != s)
            free(escaped);
          return ret;
        case SIZE_PARAMETERIZED:
          escaped = json_escape_string(&len, s, v->mem_size.size);
          ret = xprintf(pos, size, info, "\"%.*s\"", len, escaped);
          if (escaped != s)
            free(escaped);
          return ret;
      }
      break;
    }
    default:
      ERR("unexpected cases\n");
      break;
  }
}

static int
inject_composite_value(
  char *,
  size_t,
  struct composite_value * ,
  struct injection_info *);

/*
 * @todo the injection need to detect argument size
 * the current implementation won't work for double
 */
static int
inject_format_string (
  char * pos,
  size_t size,
  struct sized_buffer * sbuf,
  int n,
  struct fmt_arg * args)
{
  char *p = NULL;
  char * format;
  asprintf(&format, "%.*s", sbuf->size, sbuf->start);
  switch(n) {
    case 1:
      asprintf(&p, format, args[0]._);
      break;
    case 2:
      asprintf(&p, format, args[0]._, args[1]._);
      break;
    case 3:
      asprintf(&p, format, args[0]._, args[1]._, args[2]._);
      break;
    case 4:
      asprintf(&p, format, args[0]._, args[1]._, args[2]._, args[3]._);
      break;
    case 5:
      asprintf(&p, format, args[0]._, args[1]._, args[2]._, args[3]._,
               args[4]._);
      break;
    case 6:
      asprintf(&p, format, args[0]._, args[1]._, args[2]._, args[3]._,
               args[4]._, args[5]._);
      break;
    case 7:
      asprintf(&p, format, args[0]._, args[1]._, args[2]._, args[3]._,
               args[4]._, args[5]._, args[6]._);
      break;
    default:
      ERR("format string '%s' has %d, which is more than 8 arguments\n",
          format, n);
  }
  //@todo we should escape p
  int ret = snprintf(pos, size, "\"%s\"", p);
  free(p);
  free(format);
  return ret;
}
static int
inject_value (
  char * pos,
  size_t size,
  struct value * v,
  struct injection_info * info)
{
  switch (v->tag)
  {
    case V_ACTION:
    {
      struct action *a = &v->_.action;
      switch (a->tag)
      {
        case ACT_BUILT_IN:
          return inject_builtin(pos, size, a, info);
        case ACT_USER_DEF_ACCEPT_NON_NULL:
        case ACT_USER_DEF_ACCEPT_NULL:
        case ACT_USER_DEF_ACCEPT_NON_NULL_ENCLOSED:
        case ACT_USER_DEF_ACCEPT_NULL_ENCLOSED:
        {
          int enclosed = ACT_USER_DEF_ACCEPT_NULL_ENCLOSED == a->tag
                         || ACT_USER_DEF_ACCEPT_NON_NULL_ENCLOSED == a->tag;
          int extra_bytes = enclosed ? 2: 0;

          int (*f)(char *, size_t, void *);
          f = a->_.user_def;
          if (info->fp) {
            char *b = malloc(1024);
            (*f)(b, sizeof(b), a->operand);
            fprintf(info->fp, "%s", b);
            free(b);
          }
          if (NULL != pos && enclosed) {
            *pos = '"'; pos++;
          }
          size_t used_bytes = (*f)(pos, size, a->operand);
          if (NULL == pos)
            info->next_pos = NULL;
          else
            info->next_pos = pos + used_bytes;
          if (NULL != pos && enclosed) {
            *(pos + used_bytes) = '"';
            info->next_pos ++;
          }
          return used_bytes + extra_bytes;
        }
        default:
          if (a->tag > ACT_FORMAT_STRING) {
            size_t used_bytes = inject_format_string(pos,
                                                     size,
                                                     &a->_.fmt,
                                                     a->tag - ACT_FORMAT_STRING,
                                                     a->fmt_args);
            if (NULL == pos)
              info->next_pos = NULL;
            else
              info->next_pos = pos + used_bytes;
            return used_bytes;
          }
          break;
      }
      ERR("should not be here");
    }
    case V_COMPOSITE_VALUE:
      return inject_composite_value(pos, size, v->_.cv, info);
    case V_PRIMITIVE:
      return xprintf(pos, size, info, "%.*s",
                     v->_.primitve.size,
                     v->_.primitve.start);
    case V_STRING_LITERAL:
    {
      size_t len;
      char * p = json_escape_string (&len, v->_.primitve.start,
                                     v->_.primitve.size);
      return xprintf(pos, size, info, "\"%.*s\"", len, p);
    }
    default:
      ERR("unknown case %d\n", v->tag);
  }
}

static int
inject_access_path_value (
  char * pos,
  size_t size,
  struct access_path_value * ap,
  struct injection_info * info)
{
  char * const start_pos = pos, * const end_pos = pos + size;
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

    used_bytes += inject_value(pos, end_pos - pos, &ap->value, info);
    pos = info->next_pos;
    return used_bytes;
  }
}

static int
has_value (struct injection_info * info, struct value * v)
{
  if (NULL == info->E) return 1;

  void ** assigned_addrs = (void **)info->E->arg;
  size_t sizeof_assigned_addres = (size_t) info->E->sizeof_arg;
  switch (v->tag) {
    case V_ACTION:
      for (size_t i = 0; i < sizeof_assigned_addres/sizeof(void*); i++) {
        assert_is_pointer(v->_.action.operand);
        if (assigned_addrs[i] == v->_.action.operand)
          return 1;
      }
      return 0;
    case V_COMPOSITE_VALUE:
    {
      struct composite_value * cv = v->_.cv;
      int has_one = 0;
      if (cv->is_object) {
        for (size_t i = 0; i < cv->_.pairs.size; i++) {
          struct access_path_value *p = cv->_.pairs.pos + i;
          if (has_value(info, &p->value)) {
            has_one = 1;
            break;
          }
        }
      }
      else {
        for (size_t i = 0; i < cv->_.elements.size; i++) {
          struct value * p = cv->_.elements.pos + i;
          if (has_value(info, p)) {
            has_one = 1;
            break;
          }
        }
      }
      return has_one;
    }
    default:
      return 1;
  }
}

static int
inject_composite_value (
  char * pos,
  size_t size,
  struct composite_value * cv,
  struct injection_info * info)
{
  char * const end_pos = pos + size;
  size_t used_bytes = 0, count;

  if (cv->is_object) {
    used_bytes += xprintf(pos, end_pos - pos, info, "{");
    pos = info->next_pos;

    count = cv->_.pairs.size;
    for (size_t i = 0; i < cv->_.pairs.size; i++) {
      struct access_path_value *p = cv->_.pairs.pos + i;
      if (!has_value(info, &p->value))
        count--;
    }

    for (size_t i = 0, j = 0; i < cv->_.pairs.size; i++) {
      struct access_path_value *p = cv->_.pairs.pos + i;
      if (!has_value(info, &p->value)) continue;

      used_bytes += inject_access_path_value(pos, end_pos - pos, p, info);
      pos = info->next_pos;

      if (j + 1 != count) {
        used_bytes += xprintf(pos, end_pos - pos, info, ",");
        pos = info->next_pos;
      }
      j++;
    }
    used_bytes += xprintf(pos, end_pos - pos, info, "}");
  }
  else {
    used_bytes += xprintf(pos, end_pos - pos, info, "[");
    pos = info->next_pos;

    count = cv->_.elements.size;
    for (size_t i = 0; i < cv->_.elements.size; i++) {
      struct value *v = cv->_.elements.pos + i;
      if (!has_value(info, v)) count--;
    }

    for (size_t i = 0, j = 0; i < cv->_.elements.size; i++) {
      struct value * v = cv->_.elements.pos + i;
      if (!has_value(info, v)) continue;

      used_bytes += inject_value(pos, end_pos - pos, v, info);
      pos = info->next_pos;

      if (j+1 != count) {
        used_bytes += xprintf(pos, end_pos - pos, info, ",");
        pos = info->next_pos;
      }
      j ++;
    }
    used_bytes += xprintf(pos, end_pos - pos, info, "]");
  }
  return used_bytes;
}

static int
prepare_actor(
  struct stack * stack,
  struct operand_addrs * operand_addrs,
  struct composite_value * cv,
  char * pos,
  size_t size,
  char * actor,
  va_list ap)
{
  memset(cv, 0, sizeof(struct composite_value));

  size_t len = strlen(actor);
  char *next_pos = parse_toplevel(stack, actor, len, cv);
  if (next_pos != actor + len) {
    ERR("unexpected %s\n", next_pos);
  }
  get_composite_value_operand_addrs(cv, operand_addrs);

  for (size_t i = 0; i < operand_addrs->pos; i++) {
    switch (operand_addrs->types[i]) {
      case ARG_PTR:
        *((void **) operand_addrs->addrs[i]) = va_arg(ap, void *);
        break;
      case ARG_INT:
        *((int *) operand_addrs->addrs[i]) = va_arg(ap, int);
        break;
      case ARG_DOUBLE:
        *((double *) operand_addrs->addrs[i]) = va_arg(ap, double);
        break;
    }
  }
  return 1;
}

int
json_inject_va_list(
  char *pos,
  size_t size,
  char *injector,
  va_list ap)
{
  struct stack stack = { .array = {0}, .top = 0, .actor = INJECTOR };
  struct operand_addrs  rec = { 0 };
  struct composite_value cv;

  prepare_actor(&stack, &rec, &cv, pos, size, injector, ap);

  struct injection_info info = { 0 };
  char * mem = NULL;
  size_t mem_size = 0;
  if (1)
    info.fp = NULL;
  else
    info.fp = open_memstream(&mem, &mem_size);

  if (cv.E.has_this) {
    if (cv.E.arg == NULL)
      ERR("The argument of @ (used for checking the existence of a value) is NULL");
    info.E = &cv.E;
    if(cv.E.sizeof_arg % sizeof(void *))
      ERR("The sizeof @'s argument has to be a multiplication of sizeof(void *)\n");
  }

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

  size_t used_bytes =
    inject_composite_value(output_buf, output_size, &cv, &info);
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
  free_composite_value(&cv);
  return used_bytes;
}

int json_inject_alloc(char ** buf_p, size_t * size_p, char * injector, ...)
{
  va_list ap;
  va_start(ap, injector);
  size_t used_bytes = json_inject_va_list(NULL, 0, injector, ap);
  va_end(ap);

  char * buf = malloc(used_bytes+1);
  buf[used_bytes] = 0;
  if (size_p)
    *size_p = used_bytes+1;
  *buf_p = buf;

  va_start(ap, injector);
  json_inject_va_list(buf, used_bytes + 1, injector, ap);
  va_end(ap);

  ASSERT_S(used_bytes == strlen(buf), "used_bytes != strlen(buf)");
  return used_bytes;
}

int json_inject (char * pos, size_t size, char * injector, ...)
{
  va_list ap;
  va_start(ap, injector);
  size_t used_bytes = json_inject_va_list(pos, size, injector, ap);
  va_end(ap);
  return used_bytes;
}


static char*
print_token(jsmntype_t type)
{
  switch (type) {
    case JSMN_UNDEFINED:  return "undefined";
    case JSMN_OBJECT:     return "object";
    case JSMN_ARRAY:      return "array";
    case JSMN_STRING:     return "string";
    case JSMN_PRIMITIVE:  return "primitive";
    default:              ERR("Unknown JSMN_XXXX type encountered (code: %d)", type);
  }
  return NULL; // avoid warning
}

static int keycmp(char *json, jsmntok_t *tok, struct sized_buffer *key)
{
  if (tok->type == JSMN_STRING
      && key->size == (size_t)(tok->end - tok->start)
      && STRNEQ(json + tok->start, key->start, key->size))
  {
    return 0;
  }
  return -1;
}

static char * copy_over_string (size_t * new_size, char * str, size_t len)
{
  char * new_str = NULL;
  if (json_unescape_string(&new_str, new_size, str, len)) {
    return new_str;
  }
  else {
    // ill formed string
    char * p = NULL;
    asprintf(&p, "cannot unescape an ill-formed-string %.*s", (int)len, str);
    *new_size = strlen(p) + 1;
    return p;
  }
}

struct e_info {
  char * pos;
  jsmntok_t *tok;
  int n_toks;
  struct existence * E;
};



static int extract_str (struct action * v, int i, struct e_info * info)
{
  jsmntok_t * t = info->tok;
  ASSERT_S (JSMN_STRING == t[i].type, "expecect string");

  size_t new_size = 0;
  int len = t[i].end - t[i].start;
  char * json = info->pos;
  char * escaped = copy_over_string(&new_size, json + t[i].start, len);

  switch(v->mem_size.tag)
  {
    case SIZE_ZERO: {
      char **p = (char **) v->operand;
      int len = t[i].end - t[i].start + 1;
      *p = malloc(len);
      int ret = snprintf(*p, len, "%.*s", len - 1, escaped);
      ASSERT_S(ret < len, "out-of-bounds write");
      break;
    }
    case SIZE_FIXED:
    case SIZE_PARAMETERIZED:
    {
      int ret = snprintf((char *) v->operand, v->mem_size.size,
                         "%.*s", t[i].end - t[i].start, escaped);
      ASSERT_S((size_t) ret < v->mem_size.size, "out-of-bounds write");
      break;
    }
    case SIZE_UNKNOWN:
    {
      // we have to allow this potential oob write as
      // we don't know the buffer size of recipient.
      sprintf((char *) v->operand, "%.*s", (int)new_size, escaped);
      break;
    }
  }
  if (escaped != json + t[i].start)
    free(escaped);
  return 0;
}

static int extract_scalar (struct action * a, int i, struct e_info * info)
{
  jsmntok_t * t = info->tok;
  char * json = info->pos, * end;
  ASSERT_S(t[i].type == JSMN_PRIMITIVE, "Not a primitive");

  switch(a->_.builtin)
  {
    case B_INT:
      if ('n' == json[t[i].start])
        *(int *) a->operand = 0;
      else {
        *(int *) a->operand = (int) strtol(json + t[i].start, &end, 10);
        if (end != json + t[i].end) goto type_error;
        break;
      }
    case B_BOOL:
      switch (json[t[i].start]) {
        case 't': *(bool *)a->operand = true; break;
        case 'f': *(bool *)a->operand = false; break;
        default: goto type_error;
      }
      break;
    case B_LONG_LONG:
      if ('n' == json[t[i].start])
        *(long long *) a->operand = 0;
      else {
        *(long long *) a->operand = strtoll(json + t[i].start, &end, 10);
        if (end != json + t[i].end) goto type_error;
      }
      break;
    case B_FLOAT:
      if ('n' == json[t[i].start])
        *(float *) a->operand = 0;
      else {
        *(float *) a->operand = strtof(json + t[i].start, &end);
        if (end != json + t[i].end) goto type_error;
      }
      break;
    case B_DOUBLE:
      if ('n' == json[t[i].start])
        *(double *) a->operand = 0;
      else {
        *(double *) a->operand = strtod(json + t[i].start, &end);
        if (end != json + t[i].end) goto type_error;
      }
      break;
    default:
      ERR("unexpected");
  }
  type_error:
  return 0;
}

static int apply_action (struct value * v, int idx, struct e_info * info)
{
  jsmntok_t * t = info->tok;
  char * json = info->pos;
  ASSERT_S(V_ACTION == v->tag, "expect an action");

  struct action * a = &v->_.action;
  if (ACT_BUILT_IN == v->_.action.tag) {
    switch (a->_.builtin) {
      case B_STRING:
        extract_str(a, idx, info);
        break;
      case B_TOKEN: {
        struct sized_buffer *tk = a->operand;
        tk->start = json + t[idx].start;
        tk->size = t[idx].end - t[idx].start;
        break;
      }
      default:
        if (a->_.builtin < B_STRING)
          extract_scalar(a, idx, info);
        else
          ERR("unexpected case %d\n", a->_.builtin);
        break;
    }
  }
  else if (ACT_FORMAT_STRING == a->tag) {
    ERR("not supported yet");
  }
  else {
    if (t[idx].type == JSMN_PRIMITIVE
        && (STRNEQ(json + t[idx].start, "null", 4))) {
      //es->is_applied = false;
    }
    else if (0 == t[idx].size
             && (t[idx].type == JSMN_OBJECT || t[idx].type == JSMN_ARRAY)) {
    }
    else {
      int (*f)(char *, size_t, void *);
      f = a->_.user_def;
      int ret = (*f)(json + t[idx].start, t[idx].end - t[idx].start, a->operand);
      //if (0 == ret);
      //es->is_applied = false;
    }
  }
  return 0;
}

static int
extract_object_value (struct composite_value * cv, int parent, struct e_info *);
static int
extract_array_value (struct composite_value * cv, int parent, struct e_info *);

static int
extract_value (struct value * v, int val_idx, struct e_info * info)
{
  switch (v->tag) {
    case V_ACTION:
      apply_action(v, val_idx, info);
      break;
    case V_COMPOSITE_VALUE:
      if (v->_.cv->is_object)
        extract_object_value(v->_.cv, val_idx, info);
      else
        extract_array_value(v->_.cv, val_idx, info);
      break;
    case V_PRIMITIVE:
      break;
    case V_STRING_LITERAL:
      break;
  }
  return 0;
}

static int
extract_access_path (
  int val_idx,
  struct access_path_value *apv,
  struct access_path *curr_path,
  struct e_info * info)
{
  char * json = info->pos;
  jsmntok_t * t = info->tok;

  char *end = 0;
  int i = val_idx, ic;
  if (curr_path)
  {
    switch (t[val_idx].type) {
      case JSMN_OBJECT:
        for (ic = i + 1; t[ic].start < t[i].end; ic++) {
          if (i != t[ic].parent)
            continue;

          // top level key within t[i]
          if (0 == keycmp(json, &t[ic], &curr_path->key))
            return extract_access_path(ic+1, apv, curr_path->next, info);
        }
        return 0;
      case JSMN_ARRAY:
      {
        char *end;
        int index = strtol(curr_path->key.start, &end, 10);
        ASSERT_S(*end == ')', "Index is not a number");
        ASSERT_S(index >= 0, "Index is not zero or positive");
        ASSERT_S(index < t[i].size, "Index is out-of-bound");

        ic = i + 1; // the first child of i;
        return extract_access_path(ic + index, apv, curr_path->next, info);
      }
      default:
        ERR("Patch match error (not an Object or Array)");
    }
    return 0;
  }
  struct value * v = &apv->value;
  return extract_value(v, val_idx, info);
}

static void
print_tok (char * json, jsmntok_t * tok, int i) {
  D_PRINT("[%u][p:%d][size:%d]%s (%.*s)\n",
          i, tok[i].parent,
          tok[i].size, print_token(tok[i].type),
          (int)(tok[i].end - tok[i].start), json + tok[i].start);
}
static int
extract_object_value (
  struct composite_value * cv,
  int parent,
  struct e_info * info)
{
  char * json = info->pos;
  jsmntok_t * t = info->tok;

  int key_idx = parent + 1, val_idx = parent + 2;
  struct access_path_value *p;
  int nkeys = 0;
  while (1) {
    if (t[key_idx].type != JSMN_STRING) {
      print_tok(json, t, key_idx);
    }
    ASSERT_S(t[key_idx].type == JSMN_STRING, "Not a key"); // make sure it's a key
    ASSERT_S(t[key_idx].parent == parent, "Token is not at top level"); // make sure it's at the toplevel

    for (size_t i = 0; i < cv->_.pairs.size; i++) {
      p = cv->_.pairs.pos + i;
      if (0 == keycmp(json, &t[key_idx], &p->path.key))
        extract_access_path(val_idx, p, p->path.next, info);
    }

    nkeys ++;
    if (nkeys < t[parent].size) {
      // find the next toplevel key
      key_idx = val_idx + 1;
      while (t[key_idx].end < t[val_idx].end && t[key_idx].end < t[parent].end) {
        print_tok(json, t, key_idx);
        key_idx ++;
      }
    }
    else
      break;
  }
}

static struct value * is_list_extraction (struct composite_value * cv)
{
  struct value * v = cv->_.elements.pos;
  if (1 == cv->_.elements.size
      && V_ACTION == v->tag
      && ACT_BUILT_IN == v->_.action.tag
      && B_LIST == v->_.action._.builtin) {
    return v;
  }

  return NULL;
}

static int
extract_array_value (
  struct composite_value * cv,
  int parent,
  struct e_info * info)
{
  jsmntok_t * t = info->tok;
  int n_toks = info->n_toks;

  struct sized_buffer **token_array = NULL;
  int * children;

  int n = t[parent].size;

  struct value * v = is_list_extraction(cv);

  if (v)
    token_array = (struct sized_buffer **)
      ntl_malloc(n, sizeof(struct sized_buffer));
  else
    children = malloc(n * sizeof(int));

  int idx, ic;
  for (idx = 0, ic = parent + 1; ic < n_toks && idx < n; ic++) {
    if (t[ic].parent != parent)
      continue;

    if (v) {
      token_array[idx]->start = info->pos + t[ic].start;
      token_array[idx]->size = t[ic].end - t[ic].start;
    }
    else {
      children[idx] = ic;
    }
    ++idx;
  }

  if (v) {
    *(struct sized_buffer ***)v->_.action.operand = token_array;
    return 1;
  }

  for (size_t i = 0; i < cv->_.elements.size && i < n; i++) {
    v = cv->_.elements.pos + i;
    extract_value(v, children[i], info);
  }

  free(children);
  return 0;
}

int
json_extract_va_list (char * json, size_t size, char * extractor, va_list ap)
{
  struct stack stack = { .array = {0}, .top = 0, .actor = EXTRACTOR };
  struct operand_addrs rec = { 0 };
  struct composite_value cv;

  prepare_actor(&stack, &rec, &cv, json, size, extractor, ap);
  struct e_info info = { .pos = json, .E = NULL };

  //calculate how many tokens are needed
  jsmn_parser parser;
  jsmn_init(&parser);
  jsmntok_t * tok = NULL;
  int num_tok = jsmn_parse(&parser, json, size, NULL, 0);
  D_PRINT("# of tokens = %d", num_tok);
  if (num_tok < 0) {
    D_PRINT("Failed to parse JSON: %.*s", (int)size, json);
    D_PRINT("Returned token number: %d", num_tok);
    goto cleanup;
  }

  tok = malloc(sizeof(jsmntok_t) * num_tok);
  jsmn_init(&parser);
  num_tok = jsmn_parse(&parser, json, size, tok, num_tok);

  /* Assume the top-level element is an object */
  if (num_tok < 1 || !(tok[0].type == JSMN_OBJECT || tok[0].type == JSMN_ARRAY))
  {
    ERR("Object or array expected");
    goto cleanup;
  }

  for (int i = 0; i < num_tok; i++) {
    print_tok(json, tok, i);
  }

  info.n_toks = num_tok;
  info.tok = tok;
  switch (tok[0].type)
  {
    case JSMN_OBJECT:
      ASSERT_S(cv.is_object, "Cannot extract array from json object\n");
      extract_object_value(&cv, 0, &info);
      break;
    case JSMN_ARRAY:
      ASSERT_S(!cv.is_object, "Cannot extract object from json array\n");
      extract_array_value(&cv, 0, &info);
      break;
    default:
      ERR("Unexpected toplevel token %s\n", print_token(tok[0].type));
      goto cleanup;
  }

  cleanup:
  free(tok);
  free_composite_value(&cv);
  return 0;
}

int json_extract (char * json, size_t size, char * extractor, ...)
{
  va_list ap;
  va_start(ap, extractor);
  size_t used_bytes = json_extract_va_list(json, size, extractor, ap);
  va_end(ap);
  return used_bytes;
}