/*
 *
 * json actor (injector or extractor) specification grammar
 *
 * <injector> := <composite-value> <existence>?
 *               | <access-path-value-list> <existence>?
 *
 * <extractor> := <composite-value> <existence>?
 *                | <access-path-value-list> <existence>?
 *
 * <access-path> := (<key>) | (<key>) <access-path>
 *
 * <value> := true | false | null | <int> | <float> | <string-literal>
 *            | <composite-value> | <action>
 *
 * <action> := d | ld | lld | f | lf | b | <size-specifier>s
 *            | F | F_nullable | T | L
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
#define N_PATH_MAX 8
#define KEY_MAX 128

#define JSMN_STATIC  // dont expose jsmn symbols
#define JSMN_PARENT_LINKS // add parent links to jsmn_tok, which are needed
#define JSMN_STRICT  // parse json in strict mode
#include "jsmn.h"
#include "ntl.h"
#include "json-actor.h"

extern char *
json_escape_string (size_t * output_len_p, char * input, size_t input_len);

enum actor {
  EXTRACTOR = 1,
  INJECTOR
};

/* 
 * the maximum levels of nested json object/array
 */
#define MAX_NESTED_LEVEL   16
#define MAX_ACTION_NUMBERS 64

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
enum action_type {
  ACT_BUILT_IN = 0,
  ACT_USER_DEF_ACCEPT_NON_NULL,
  ACT_USER_DEF_ACCEPT_NULL,
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

enum jv_type {
  JV_COMPOSITE_VALUE = 1,
  JV_ACTION,
  JV_PRIMITIVE = 10,
  JV_STRING_LITERAL,
};

struct value {
  enum jv_type tag;
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
    case JV_COMPOSITE_VALUE:
      print_composite_value(fp, v->_.cv);
      break;
    case JV_ACTION:
      print_action (fp, &v->_.action);
      break;
    case JV_STRING_LITERAL:
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

enum cv_type {
  CV_ARRAY = 1,
  CV_OBJECT
};

struct composite_value {
  enum cv_type tag;
  union {
    struct sized_value elements;
    struct sized_access_path_value pairs;
  } _;
  struct existence E;
};

static void
print_composite_value (FILE * fp, struct composite_value * cv)
{
  if (cv->tag == CV_ARRAY) {
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

static int has_format_string (char * pos, char * end_pos)
{
  int count = 0;
  while (pos < end_pos) {
    if ('%' == *pos) {
      if (pos+1 == end_pos) {
        ERR("dangling format % string is not allowed\n", pos);
      }
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
  enum jv_type * type)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  unsigned char c;
  int has_format_string;

  c = * pos;

  *type = JV_PRIMITIVE;
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
      *type = JV_STRING_LITERAL;
      pos ++;
      while (pos < end_pos) {
        c = *pos; pos ++;
        if ('"' == c)
          goto return_true;
      }
      break;
    case '|': // a proprietary string literal
      *type = JV_STRING_LITERAL;
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
  char * const end_pos = pos + size, * next_pos;
  enum jv_type jv_type;

  if (is_primitive(stack, pos, size, &next_pos, &jv_type)) {
    p->tag = jv_type;
    p->_.primitve.start = pos;
    p->_.primitve.size = next_pos - pos;
    if (jv_type == JV_STRING_LITERAL) {
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
        p->tag = JV_ACTION;
        p->_.action.tag = ACT_FORMAT_STRING + n;
      }
    }
    *next_pos_p = next_pos;
    return 1;
  }
  struct action * act = &p->_.action;
  p->tag = JV_ACTION;
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
        av->value.tag = JV_COMPOSITE_VALUE;
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
    if (0 != i && ',' == * pos) {
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
      cv->tag = CV_OBJECT;
      pos++;
      PUSH(stack, '}');
      pos = parse_access_path_value_list(stack, pos, end_pos - pos, &cv->_.pairs);
      c = POP(stack);
      if (c != *pos)
        ERR("Mismatched stack: expecting %c, but getting %c\n", c, *pos);
      pos++;
      break;
    case '[':
      cv->tag = CV_ARRAY;
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
      cv->tag = CV_OBJECT;
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
}

struct operand_addrs {
  void * addrs[MAX_ACTION_NUMBERS];
  enum arg_type types[MAX_ACTION_NUMBERS];
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
    case JV_ACTION:
      act = &v->_.action;
      switch (act->tag)
      {
        case ACT_BUILT_IN:
          if (PARAMETERIZED_SIZE == act->mem_size.tag) {
            rec->addrs[rec->pos] = &act->mem_size._.parameterized_size;
            rec->pos ++;
          }
          rec->addrs[rec->pos] = &act->operand;
          rec->pos ++;
          break;
        case ACT_USER_DEF_ACCEPT_NON_NULL:
        case ACT_USER_DEF_ACCEPT_NULL:
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
              rec->pos ++;
            }
          }
          break;
      }
      break;
    case JV_COMPOSITE_VALUE:
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
  if(CV_OBJECT == cv->tag)
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
  if(JV_COMPOSITE_VALUE == v->tag) {
    free_composite_value(v->_.cv);
    free(v->_.cv);
  }
}

static void free_access_path (struct access_path * p)
{
  if (p->next)
    free_access_path(p->next);
  else
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
  if(CV_OBJECT == cv->tag) {
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
    free(cv->_.pairs.pos);
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
        case UNKNOWN_SIZE:
        case ZERO_SIZE:
          escaped = json_escape_string(&len, s, strlen(s));
          ret = xprintf(pos, size, info, "\"%s\"", escaped);
          if (escaped != s)
            free(escaped);
          return ret;
        case FIXED_SIZE:
          escaped = json_escape_string(&len, s, v->mem_size._.fixed_size);
          ret = xprintf(pos, size, info, "\"%.*s\"", len, escaped);
          if (escaped != s)
            free(escaped);
          return ret;
        case PARAMETERIZED_SIZE:
          escaped = json_escape_string(&len, s,
                                       v->mem_size._.parameterized_size);
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

static int inject_composite_value (char *, size_t, struct injection_info * );

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
      ERR("format string '%s' has more than 8 arguments\n", format, n);
  }
  //@todo we should escape p
  int ret = snprintf(pos, size, "\"%s\"", p);
  free(p);
  free(format);
  return ret;
}
static int
inject_value (char * pos, size_t size, struct injection_info * info)
{
  struct value * v = (struct value *)info->data;
  switch (v->tag)
  {
    case JV_ACTION:
    {
      struct action *a = &v->_.action;
      switch (a->tag)
      {
        case ACT_BUILT_IN:
          info->data = a;
          return inject_builtin(pos, size, info);
        case ACT_USER_DEF_ACCEPT_NON_NULL:
        case ACT_USER_DEF_ACCEPT_NULL:
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
    case JV_COMPOSITE_VALUE:
      info->data = v->_.cv;
      return inject_composite_value(pos, size, info);
    case JV_PRIMITIVE:
      return xprintf(pos, size, info, "%.*s",
                     v->_.primitve.size,
                     v->_.primitve.start);
    case JV_STRING_LITERAL:
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
has_value (struct injection_info * info, struct value * v)
{
  if (NULL == info->E) return 1;

  void ** assigned_addrs = (void **)info->E->arg;
  size_t sizeof_assigned_addres = (size_t) info->E->sizeof_arg;
  switch (v->tag) {
    case JV_ACTION:
    {
      for (size_t i = 0; i < sizeof_assigned_addres/sizeof(void*); i++) {
        if (assigned_addrs[i] == v->_.action.operand)
          return 1;
      }
      return 0;
    }
    case JV_COMPOSITE_VALUE:
    {
      struct composite_value * cv = v->_.cv;
      int has_one = 0;
      if (CV_OBJECT == cv->tag) {
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
inject_composite_value (char * pos, size_t size, struct injection_info * info)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  size_t used_bytes = 0, count;
  struct composite_value * cv = (struct composite_value *) info->data;

  if (CV_OBJECT == cv->tag) {
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

      info->data = p;
      used_bytes += inject_access_path_value(pos, end_pos - pos, info);
      pos = info->next_pos;

      if (j + 1 != count) {
        used_bytes += xprintf(pos, end_pos - pos, info, ",");
        pos = info->next_pos;
      }
      j++;
    }
    used_bytes += xprintf(pos, end_pos - pos, info, "}");
    pos = info->next_pos;
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

      info->data = cv->_.elements.pos + i;
      used_bytes += inject_value(pos, end_pos - pos, info);
      pos = info->next_pos;

      if (j+1 != count) {
        used_bytes += xprintf(pos, end_pos - pos, info, ",");
        pos = info->next_pos;
      }
      j ++;
    }
    used_bytes += xprintf(pos, end_pos - pos, info, "]");
    pos = info->next_pos;
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

  struct operand_addrs  rec = { 0 };
  get_composite_value_operand_addrs(&cv, &rec);

  for (size_t i = 0; i < rec.pos; i++) {
    switch(rec.types[i])
    {
      case ARG_PTR:
        *((void **) rec.addrs[i]) = va_arg(ap, void *);
        break;
      case ARG_INT:
        *((int *) rec.addrs[i]) = va_arg(ap, int);
        break;
      case ARG_DOUBLE:
        *((double *) rec.addrs[i]) = va_arg(ap, double);
        break;
    }
  }

  struct injection_info info = { 0 };
  char * mem = NULL;
  size_t mem_size;
  if (1)
    info.fp = NULL;
  else
    info.fp = open_memstream(&mem, &mem_size);

  info.data = &cv;
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
  free_composite_value(&cv);
  return used_bytes;
}

int json_inject_alloc(char ** buf_p, size_t * size_p, char * injector, ...)
{
  va_list ap;
  va_start(ap, injector);
  size_t used_bytes = json_injector_va_list(NULL, 0, injector, ap);
  va_end(ap);

  char * buf = malloc(used_bytes+1);
  buf[used_bytes] = 0;
  if (size_p)
    *size_p = used_bytes+1;
  *buf_p = buf;

  va_start(ap, injector);
  json_injector_va_list(buf, used_bytes+1, injector, ap);
  va_end(ap);

  ASSERT_S(used_bytes == strlen(buf), "used_bytes != strlen(buf)");
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

extern int json_extract(char * pos, size_t size, void *);
