/*
 *
 * json actor (injector or extractor) specification grammar
 *
 * <injector> := <composite-value> <pointer-availability>?
 *               | <access-path-value-list> <pointer-availability>?
 *
 * <extractor> := <composite-value> <pointer-availability>? <defined>
 *                | <access-path-value-list> <pointer-availability>? <defined>
 *                | [ # ]
 *
 * <access-path> := (<key>) | (*) | (<key>) <access-path>
 *
 * <value> := true | false | null | <int> | <float> | <string-literal>
 *            | <composite-value> | <action>
 *
 * <action> := d | ld | lld | f | lf | b | s_as_u64 <size-specifier>s
 *            | F | F_nullable | key | s_as_u64 | s_as_hex64 | lnc
 *
 * <access-path-value> := <access-path> : <value>
 *
 * <access-path-value-list> := <access-path-value>
 *                            | <access-path-value> <access-path-value-list>
 *
 * <composite-value> :=  { <access-path-value-list> } | [ <value> ]
 *
 * <pointer-availability> := @<kind>:b | @<kind>
 *
 * <kind> := switch_args | record_defined | record_null
 *
 * <defined> := <size-specifier>$
 *
 * <size-specifier> := <integer> | .* | ? | epsilon
 *
 *
 * examples:
 *
 * json_extract(pos, size, "{ (key) : d, (key) : .*s }", &i)
 *
 * sized_buffer ** list;
 * json_extract(pos, size, "[ # ]", &list);
 *
 *
 * json_inject(pos, size, "{  (key) : d, (key) : |abc| }", i);
 *
 *
 * query_inject(pos, size, "(key)=d&(key1)=s", &i, str);
 *
 */
#define _GNU_SOURCE
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <inttypes.h>

#define JSMN_STATIC  /* dont expose jsmn symbols */
#define JSMN_PARENT_LINKS /* add parent links to jsmn_tok, which are needed */
#define JSMN_STRICT  /* parse json in strict mode */
#include "jsmn.h"
#include "ntl.h"
#include "debug.h"
#include "json-actor.h"


static const char*
jsmn_code_print(int code)
{
  switch (code) {
  case JSMN_ERROR_INVAL: return "JSMN_ERROR_INVAL";
  case JSMN_ERROR_NOMEM: return "JSMN_ERROR_NOMEM";
  case JSMN_ERROR_PART: return "JSMN_ERROR_PART";
  default: return NULL;
  }
}

static const char*
jsmn_strerror(int code)
{
  switch (code) {
  case JSMN_ERROR_INVAL:
      return "Bad token, JSON string is corrupted";
  case JSMN_ERROR_NOMEM:
      return "Not enough tokens, JSON string is too large";
  case JSMN_ERROR_PART:
      return "JSON string is too short, expecting more JSON data";
  default: return "Unknown JSMN error";
  }
}

#define JSMN_CHECK(code, json, size)                    \
  if (code <= 0)                                        \
    ERR("\n\tFailed at: '%.*s'\n\t%s(code: %d) %s",     \
      (int)size, json,                                  \
      jsmn_code_print(code), code, jsmn_strerror(code))


static int strong_type = 1;
void json_actor_strong_type(int b)
{
  strong_type = b;
}

/*
 * convert address to line and column
 */
void addr_to_lnc (char *json, size_t size,
                  char *addr, struct line_and_column * ln)
{
  char *const istart_pos = json, *const xend_pos = json + size;
  char *pos = json;

  if (!(istart_pos <= addr && addr < xend_pos)) {
    ERR("address is not in the range of %p\n", json);
  }

  size_t l = 0, c = 0;
  while (pos < addr) {
    if (*pos == '\n') {
      l++;
      c = 0; /* reset column */
    }
    pos++;
    c++;
  }

  ln->line = l;
  ln->column = c;
}

static void assert_is_pointer(void * p)
{
  if (NULL == p)
    return;

  /*
   * This is a poor man's method to check if
   * p is a legit pointer.
   */
  char * x = (char *)p;
  static char c; /*has to be a static variable such that compilers won't remove them*/
  c = *x;
  (void)c;
}


extern char *
json_string_escape(size_t *output_len_p, char *input, size_t input_len);

extern int json_string_unescape(char **new_str, size_t *new_size,
                                char *str, size_t old_size);

extern char *url_encode_ext(char *, size_t);
extern char *url_decode_ext(char *, size_t);

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
  bool is_star; /* match any key and get its value */
  struct access_path * next;
};

static void
print_access_path (FILE * fp, struct access_path * access_path)
{
  fprintf(fp, "|%.*s|", (int)access_path->key.size, access_path->key.start);
  if (access_path->next)
    print_access_path(fp, access_path->next);
}

struct access_path_value;

enum size_tag {
  SIZE_UNKNOWN = 0,
  SIZE_FIXED,
  SIZE_PARAMETERIZED,
  SIZE_ZERO
};

struct size_specifier {
  enum size_tag tag;
  size_t size;
};

enum builtin_type {
  B_KEY_EXISTENCE = 1,
  B_LINE_AND_COLUMN,
  B_BOOL,
  B_INT,
  B_LONG,
  B_LONG_LONG,
  B_UINT64,
  B_STRING_AS_HEX_UINT,
  B_STRING_AS_U64,
  B_STRING_AS_HEX64,
  B_FLOAT,
  B_DOUBLE,
  B_STRING,
  B_TOKEN,
  B_TOKEN_CLONE,
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
    /*double real; */
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
  struct fmt_arg fmt_args[8]; /* no more than 8 arguments */
  void * operand;
  struct size_specifier mem_size; /* this designates the memory size of _; */
  void *key;
};

enum ptr_map_tag {
  PTR_MAP_ARG_SWITCHES = 1,
  PTR_MAP_RECORD_DEFINED,
  PTR_MAP_RECORD_NULL,
};

struct ptr_map {
  enum ptr_map_tag tag;
  void **arg;
  int  sizeof_arg;
  int  enabled;
  bool has_this;
  bool has_enabler;
  int next_idx; /* only used for recorder */
  int xend_idx; /* exclusive end index */
};


static void
print_ptr_map (FILE *fp, struct ptr_map *m)
{
  if (!m->has_this) return;
  switch(m->tag)
  {
    case PTR_MAP_ARG_SWITCHES:
      fprintf(fp, "@arg_switches %p %d\n", m->arg, m->sizeof_arg);
      break;
    case PTR_MAP_RECORD_DEFINED:
      fprintf(fp, "@record_defined %p %d\n", m->arg, m->sizeof_arg);
      break;
    case PTR_MAP_RECORD_NULL:
      fprintf(fp, "@record_null %p %d\n", m->arg, m->sizeof_arg);
      break;
  }
}

static void
check_ptr_maps(struct ptr_map **m) {
  int i;

  for (i = 0; m[i]; i++) {
    if (m[i]->has_this) {
      if (m[i]->arg == NULL)
        ERR(
          "The argument of @ (used for checking the pointer_maps of a value) is NULL");
      if (m[i]->sizeof_arg % sizeof(void *))
        ERR(
          "The sizeof @arg_switches's argument has to be a multiplication of sizeof(void *)\n");

      m[i]->xend_idx = m[i]->sizeof_arg / sizeof(void *);
    }
  }
}

static struct ptr_map*
get_arg_switches(struct ptr_map **l)
{
  int i;

  for (i = 0; l[i]; i++)
    if (l[i]->has_this && l[i]->tag == PTR_MAP_ARG_SWITCHES) {
      if (l[i]->has_enabler)
        if (l[i]->enabled)
          return l[i];
        else
          return NULL;
      else
        return l[i];
    }
  return NULL;
}

static struct ptr_map*
get_record_defined(struct ptr_map **l)
{
  int i;

  for (i = 0; l[i]; i++)
    if (l[i]->has_this && l[i]->tag == PTR_MAP_RECORD_DEFINED)
      return l[i];
  return NULL;
}

static void
add_defined (struct ptr_map **s, void *p)
{
  struct ptr_map *m = get_record_defined(s);
  if (m == NULL)
    return;

  void **v = m->arg;
  if (m->next_idx < m->xend_idx) {
    /*fprintf(stderr, "&arg %p, arg %p\n", &m->arg, m->arg); */
    v[m->next_idx] = p;
    m->next_idx ++;
  }
  else {
    ERR("array is too small\n");
  }
}

static void
print_action (FILE * fp, struct action * v)
{
  if (ACT_BUILT_IN == v->tag)
    fprintf(fp, "builtin(%d)\n", v->_.builtin);
  else
    fprintf(fp, "funptr(%p)\n", (void*)v->_.user_def);
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
  bool is_applied;
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
      char * p = json_string_escape(&len, v->_.primitve.start,
                                    v->_.primitve.size);
      fprintf(fp, "\"%.*s\"\n", (int)len, p);
      break;
    }
    default:
      fprintf(fp, "%.*s\n", (int)v->_.primitve.size, v->_.primitve.start);
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
  int is_object; /* otherwise, it is an array */
  union {
    struct sized_value elements;
    struct sized_access_path_value pairs;
  } _;
  struct ptr_map *maps[4];
  struct ptr_map data[3];
};

static void
composite_value_init(struct composite_value *c)
{
  c->maps[0] = c->data+0;
  c->maps[1] = c->data+1;
  c->maps[2] = c->data+2;
  c->maps[3] = NULL;
  memset(c->data, 0, sizeof(c->data));
}

static struct composite_value*
composite_value_alloc()
{
  struct composite_value * cv = calloc(1, sizeof(*cv));
  composite_value_init(cv);
  return cv;
}

static void
print_composite_value (FILE * fp, struct composite_value * cv)
{
  size_t i;

  if (cv->is_object) {
    for (i = 0; i < cv->_.pairs.size; i++)
      print_access_path_value(fp, cv->_.pairs.pos + i);
  }
  else {
    for (i = 0; i < cv->_.elements.size; i++)
      print_value(fp, cv->_.elements.pos + i);
  }

  for (i = 0; cv->maps[i]; i++)
  {
    struct ptr_map *m = cv->maps[i];

    if (m->has_this)
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
        case '%': /* escaped % */
          pos++;
          break;
        case '.':
          if (pos + 2 < end_pos && '*' == *(pos+1) && 's' == *(pos+2)) {
            count += 2;
            pos += 3;
          }
          break;
        default: /* other format string */
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

  c = * pos;
  *type = V_PRIMITIVE;
  switch (c)
  {
    case 't': /* true */
      if (pos + 3 < end_pos
          && 'r' == pos[1] && 'u' == pos[2] && 'e' == pos[3]) {
        pos += 4;
        goto return_true;
      }
      break;
    case 'f': /* false */
      if (pos + 4 < end_pos
          && 'a' == pos[1] && 'l' == pos[2] && 's' == pos[3] && 'e' == pos[4]) {
        pos += 5;
        goto return_true;
      }
      break;
    case 'n': /* null */
      if (pos + 3 < end_pos
          && 'u' == pos[1] && 'l' == pos[2] && 'l' == pos[3]) {
        pos += 4;
        goto return_true;
      }
      break;
    case '"': /* a string literal */
      *type = V_STRING_LITERAL;
      pos ++;
      while (pos < end_pos) {
        c = *pos; pos ++;
        if ('"' == c)
          goto return_true;
      }
      break;
    case '|': /* a proprietary string literal */
      if (0 == strncmp("|F|", pos, 3)) {
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
          if (' ' == c || ',' == c || '(' == c || c == TOP(stack))
            goto return_true;
          else if ('.' == c || ('0' <= c && c <= '9')) pos++;
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
    *next_pos_p = x; /* jump to the end of number */
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
      /* skip the two delimiter */
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
    case 'u': {
      size_t sz = strlen("u64");
      if (pos + sz <= end_pos && 0 == strncmp(pos, "u64", sz)) {
        act->mem_size.size = sizeof(long);
        act->mem_size.tag = SIZE_FIXED;
        act->_.builtin = B_UINT64;
        pos += sz;
        goto return_true;
      }
      else
        ERR("unexpected %s\n", pos);
    }
    case 'f':
      act->mem_size.size = sizeof(float);
      act->mem_size.tag = SIZE_FIXED;
      act->_.builtin = B_FLOAT;
      pos ++;
      goto return_true;
    case 'k': {
      size_t sz = strlen("key");
      if (pos + sz <= end_pos && 0 == strncmp(pos, "key", sz)) {
        act->mem_size.size = sizeof(bool);
        act->mem_size.tag = SIZE_FIXED;
        act->_.builtin = B_KEY_EXISTENCE;
        pos += sz;
      }
      goto return_true;
    }
    case 'l':
      if (pos + 1 < end_pos && 0 == strncmp(pos, "ld", 2)) {
        act->mem_size.size = sizeof(long);
        act->mem_size.tag = SIZE_FIXED;
        act->_.builtin = B_LONG;
        pos += 2;
        goto return_true;
      }
      else if (pos + 2 < end_pos && 0 == strncmp(pos, "lld", 3)) {
        act->mem_size.size = sizeof(long long);
        act->mem_size.tag = SIZE_FIXED;
        act->_.builtin = B_LONG_LONG;
        pos += 3;
        goto return_true;
      }
      else if (pos + 1 < end_pos && 0 == strncmp(pos, "lf", 2)) {
        act->mem_size.size = sizeof(double);
        act->mem_size.tag = SIZE_FIXED;
        act->_.builtin = B_DOUBLE;
        pos += 2;
        goto return_true;
      }
      else if (pos + 2 < end_pos && 0 == strncmp(pos, "lnc", 3)) {
        act->mem_size.size = sizeof(struct line_and_column);
        act->mem_size.tag = SIZE_FIXED;
        act->_.builtin = B_LINE_AND_COLUMN;
        pos += 3;
        goto return_true;
      }
      else
        ERR("unexpected %s\n", pos);
      break;
    case 's':
    {
      size_t sz1 = strlen("s_as_u64"), sz2 = strlen("s_as_hex64");
      size_t sz0 = strlen("s_as_hex_uint");

      if (pos + sz0 <= end_pos && 0 == strncmp(pos, "s_as_hex_uint", sz0)) {
        act->mem_size.size = sizeof(unsigned int);
        act->mem_size.tag = SIZE_FIXED;
        act->_.builtin = B_STRING_AS_HEX_UINT;
        pos += sz0;
        goto return_true;
      }
      else if (pos + sz1 <= end_pos && 0 == strncmp(pos, "s_as_u64", sz1)) {
        act->mem_size.size = sizeof(uint64_t);
        act->mem_size.tag = SIZE_FIXED;
        act->_.builtin = B_STRING_AS_U64;
        pos += sz1;
        goto return_true;
      }
      else if (pos + sz2 <= end_pos && 0 == strncmp(pos, "s_as_hex64", sz2)) {
        act->mem_size.size = sizeof(uint64_t);
        act->mem_size.tag = SIZE_FIXED;
        act->_.builtin = B_STRING_AS_HEX64;
        pos += sz2;
        goto return_true;
      }
      else {
        act->_.builtin = B_STRING;
        pos++;
        goto return_true;
      }
    }  
    case 'L':
      act->_.builtin = B_LIST;
      pos ++;
      goto return_true;
    case 'F':
      if (0 == strncmp(pos, "F_nullable", 10)) {
        act->tag = ACT_USER_DEF_ACCEPT_NULL;
        pos += 10;
      }
      else {
        act->tag = ACT_USER_DEF_ACCEPT_NON_NULL;
        pos++;
      }
      goto return_true;
    case '|':
      if (0 == strncmp(pos, "|F|", 3)) {
        act->tag = ACT_USER_DEF_ACCEPT_NON_NULL_ENCLOSED;
        pos += 3;
        goto return_true;
      }
      else if (0 == strncmp(pos, "|F_nullable|", 12)) {
        act->tag = ACT_USER_DEF_ACCEPT_NULL_ENCLOSED;
        pos += 12;
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

#define SKIP_SPACES(s, end)   { while (s < end && isspace(*s)) ++s; }

static int
parse_pointer_maps(
  char *pos,
  size_t size,
  struct ptr_map **p,
  char **next_pos_p)
{
  char * const xend_pos = pos + size;
  if (size == 0)
    return 0;

  int next_map = 0;

  while (pos < xend_pos)
  {
    SKIP_SPACES(pos, xend_pos);
    if ('@' == *pos) {
      pos ++;

      size_t sz1 = strlen("arg_switches"),
      sz2 = strlen("record_defined"),
      sz3 = strlen("record_null");

      if (pos + sz1 <= xend_pos
          && (0 == strncmp(pos, "arg_switches", sz1))) {
        p[next_map]->tag = PTR_MAP_ARG_SWITCHES;
        p[next_map]->has_this = true;
        pos += sz1;
        if (pos + 2 <= xend_pos
            && ':' == *pos && 'b' == *(pos + 1)) {
          p[next_map]->has_enabler = true;
          pos += 2;
        }
        *next_pos_p = pos;
        next_map ++;
      }
      else if (pos + sz2 <= xend_pos
               && (0 == strncmp(pos, "record_defined", sz2))) {
        p[next_map]->tag = PTR_MAP_RECORD_DEFINED;
        p[next_map]->has_this = true;
        pos += sz2;
        if (pos + 2 <= xend_pos
            && ':' == *pos && 'b' == *(pos + 1)) {
          p[next_map]->has_enabler = true;
          pos += 2;
        }
        *next_pos_p = pos;
        next_map ++;
      }
      else if (pos + sz3 <= xend_pos
               && (0 == strncmp(pos, "record_null", sz3))) {
        p[next_map]->tag = PTR_MAP_RECORD_NULL;
        p[next_map]->has_this = true;
        pos += sz3;
        if (pos + 2 <= xend_pos
            && ':' == *pos && 'b' == *(pos + 1)) {
          p[next_map]->has_enabler = true;
          pos += 2;
        }
        *next_pos_p = pos;
        next_map ++;
      }
    }
  }
  return next_map;
}

static char * 
parse_composite_value(struct stack *, char *, size_t, struct composite_value *);



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
  int len = 0;
  ASSERT_S('(' == *pos || '.' == *pos, "expecting '(' or '.'");
  pos ++;
  while (pos < end_pos) {
    if (')' == *pos)
      break;
    else if ('.' == *pos)
      break;
    ++pos;
  }

  if (pos == end_pos)
    ERR("A close bracket ')' or '.' is missing");

  len = pos - start_pos - 1;
  if (len == 0)
    ERR("Key is missing");

  curr_path->key.start = start_pos + 1;
  curr_path->key.size = len;
  if (len == 1 && *(start_pos+1) == '*')
    curr_path->is_star = true;

  if (')' == *pos)
    ++pos; /* eat up ')' */
  SKIP_SPACES(pos, end_pos);
  struct access_path * next_path;
  switch (*pos)
  {
    case '(':
    case '.':
      if (curr_path->is_star)
        ERR("'*' has to be the final key");

      next_path = calloc(1, sizeof(struct access_path));
      curr_path->next = next_path;
      return parse_access_path_value(stack, pos, end_pos - pos, av, next_path);
    case ':':
      ++pos; /* eat up ':' */
      SKIP_SPACES(pos, end_pos);
      if ('[' == *pos || '{' == *pos) {
        struct composite_value * cv = composite_value_alloc();
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
      ERR("expecting '(', '.', or ':', but getting %c\n", *pos);
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
  char c;

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
parse_actor(
  struct stack *stack,
  char *pos,
  size_t size,
  struct composite_value * cv)
{
  /* work around the incompatible pointer warning */
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
    char *next_pos = NULL;
    if ('@' == *pos && parse_pointer_maps(pos, end_pos - pos, cv->maps, &next_pos))
      pos = next_pos;
    SKIP_SPACES(pos, end_pos);
    if (pos == end_pos)
      return pos;
    else if (pos != end_pos)
      ERR("unexpected %s@[%zu] before end, "
          "in %s[%zu]\n",
          pos, (size_t)(end_pos - pos),
          start_pos, (size_t)(pos - start_pos));
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
            int i;
            int n = act->tag - ACT_FORMAT_STRING;

            for (i = 0; i < n; i++) {
              /*@todo analyze native format string
                to find out the argument types */
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
  size_t i;
  if(cv->is_object)
    for (i = 0; i < cv->_.pairs.size; i++) {
      apv = cv->_.pairs.pos + i;
      if (apv->path.is_star && apv->path.next == NULL) {
        rec->addrs[rec->pos] = &(apv->value._.action.key);
        rec->types[rec->pos] = ARG_PTR;
        rec->pos++;
      }
      get_value_operand_addrs(&apv->value, rec);
    }
  else
    for (i = 0; i < cv->_.elements.size; i++) {
      v = cv->_.elements.pos + i;
      get_value_operand_addrs(v, rec);
    }

  for (i = 0; cv->maps[i]; i++) {
    struct ptr_map *m = cv->maps[i];

    if (!m->has_this)
      continue;

    rec->addrs[rec->pos] = &m->arg;
    rec->types[rec->pos] = ARG_PTR;
    rec->pos++;
    rec->addrs[rec->pos] = &m->sizeof_arg;
    rec->types[rec->pos] = ARG_INT;
    rec->pos++;

    if (m->has_enabler) {
      rec->addrs[rec->pos] = &m->enabled;
      rec->types[rec->pos] = ARG_INT;
      rec->pos++;
    }
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
  size_t i;
  if(cv->is_object) {
    if (NULL == cv->_.pairs.pos)
      return;
    for (i = 0; i < cv->_.pairs.size; i++) {
      apv = cv->_.pairs.pos + i;
      free_access_path_value(apv);
    }
    free(cv->_.pairs.pos);
  }
  else {
    if (NULL == cv->_.elements.pos)
      return;
    for (i = 0; i < cv->_.elements.size; i++) {
      v = cv->_.elements.pos + i;
      free_value(v);
    }
    free(cv->_.elements.pos);
  }
}

enum encoding_type
{
  ENCODING_JSON = 0,
  ENCODING_URL = 1,
  ENCODING_BASE64
};

struct injection_info {
  char * next_pos;
  struct stack sp;
  FILE * fp;
  struct ptr_map **A;
  enum encoding_type encoding;
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
    ret2 = vfprintf(info->fp, format, ap);
    va_end(ap);
    ASSERT_S(ret2 >= 0, "vfprintf");
    ASSERT_S(ret2 == ret1, "errror");
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
      return xprintf(pos, size, info, "%d", *(int*)v->operand);
    case B_LONG:
      return xprintf(pos, size, info, "%ld", *(long*)v->operand);
    case B_LONG_LONG:
      return xprintf(pos, size, info, "%lld", *(long long*)v->operand);
    case B_UINT64:
      return xprintf(pos, size, info, "%" PRIu64, *(uint64_t*)v->operand);
    case B_STRING_AS_HEX_UINT:
      return xprintf(pos, size, info, "\"%u\"", *(unsigned int*)v->operand);
    case B_STRING_AS_U64:
      return xprintf(pos, size, info, "\"%" PRIu64 "\"", *(uint64_t*)v->operand);
    case B_STRING_AS_HEX64:
      return xprintf(pos, size, info, "\"%" PRIx64 "\"", *(uint64_t*)v->operand);
    case B_FLOAT:
      return xprintf(pos, size, info, "%f", *(float*)v->operand);
    case B_DOUBLE:
      return xprintf(pos, size, info, "%lf",*(double*)v->operand);
    case B_STRING:
    {
      s = (char *) v->operand;
      size_t len;
      int ret = 0;
      char *escaped;
      switch (v->mem_size.tag)
      {
        case SIZE_UNKNOWN:
        case SIZE_ZERO:
          if (ENCODING_JSON == info->encoding) {
            escaped = json_string_escape(&len, s, strlen(s));
            ret = xprintf(pos, size, info, "\"%.*s\"", len, escaped);
            if (escaped != s)
              free(escaped);
          }
          else if (ENCODING_URL == info->encoding) {
            escaped = url_encode_ext(s, strlen(s));
            ret = xprintf(pos, size, info, "%s", escaped);
            free(escaped);
          }
          return ret;
        case SIZE_FIXED:
          if (ENCODING_JSON == info->encoding) {
            escaped = json_string_escape(&len, s, v->mem_size.size);
            ret = xprintf(pos, size, info, "\"%.*s\"", v->mem_size.size, escaped);
            if (escaped != s)
              free(escaped);
          }
          else if (ENCODING_URL == info->encoding) {
            escaped = url_encode_ext(s, v->mem_size.size);
            ret = xprintf(pos, size, info, "%.*s", v->mem_size.size, escaped);
          }
          return ret;
        case SIZE_PARAMETERIZED:
          if (ENCODING_JSON == info->encoding) {
            escaped = json_string_escape(&len, s, v->mem_size.size);
            ret = xprintf(pos, size, info, "\"%.*s\"", len, escaped);
            if (escaped != s)
              free(escaped);
          }
          else if (ENCODING_URL == info->encoding) {
            escaped = url_encode_ext(s, v->mem_size.size);
            ret = xprintf(pos, size, info, "%.*s", v->mem_size.size, escaped);
          }
          return ret;
      }
      break;
    }
    default:
      ERR("unexpected cases\n");
      break;
  }
  return 0;
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
  asprintf(&format, "%.*s", (int)sbuf->size, sbuf->start);
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
  /*@todo we should escape p */
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
      char * p = json_string_escape(&len, v->_.primitve.start,
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
  char * const end_pos = pos + size;
  size_t used_bytes = 0;
  used_bytes += xprintf(pos, size, info, "\"%.*s\"", ap->path.key.size,
                        ap->path.key.start);
  pos = info->next_pos;
  if (ap->path.next) {
    /* @todo */
    ERR("does not support %.*s.%.*s yet\n",
        (int)ap->path.key.size, ap->path.key.start,
        (int)ap->path.next->key.size, ap->path.next->key.start);
    return 0;
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
  struct ptr_map *arg_switches = get_arg_switches(info->A);
  if (arg_switches == NULL)
    return 1;

  void ** assigned_addrs = arg_switches->arg;
  switch (v->tag) {
    case V_ACTION:
    {
      size_t i;
      for (i = 0; i < arg_switches->xend_idx; i++) {
        assert_is_pointer(v->_.action.operand);
        if (NULL != v->_.action.operand
            && assigned_addrs[i] == v->_.action.operand)
          return 1;
      }
      return 0;
    }
    case V_COMPOSITE_VALUE:
    {
      struct composite_value * cv = v->_.cv;
      int has_one = 0;
      if (cv->is_object) {
        size_t i;
        for (i = 0; i < cv->_.pairs.size; i++) {
          struct access_path_value *p = cv->_.pairs.pos + i;
          if (has_value(info, &p->value)) {
            has_one = 1;
            break;
          }
        }
      }
      else {
        size_t i;
        for (i = 0; i < cv->_.elements.size; i++) {
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
  struct access_path_value * apv;
  struct value * v;
  size_t i, j;

  if (cv->is_object) {
    used_bytes += xprintf(pos, end_pos - pos, info, "{");
    pos = info->next_pos;

    count = cv->_.pairs.size;
    for (i = 0; i < cv->_.pairs.size; i++) {
      apv = cv->_.pairs.pos + i;
      if (!has_value(info, &apv->value))
        count--;
    }

    for (i = 0, j = 0; i < cv->_.pairs.size; i++) {
      apv = cv->_.pairs.pos + i;
      if (!has_value(info, &apv->value)) continue;

      used_bytes += inject_access_path_value(pos, end_pos - pos, apv, info);
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
    for (i = 0; i < cv->_.elements.size; i++) {
      v = cv->_.elements.pos + i;
      if (!has_value(info, v)) count--;
    }

    for (i = 0, j = 0; i < cv->_.elements.size; i++) {
      v = cv->_.elements.pos + i;
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
  char * (*parser)(struct stack *, char *, size_t, struct composite_value *),
  struct stack * stack,
  struct operand_addrs * operand_addrs,
  struct composite_value * cv,
  char * actor,
  va_list ap)
{
  void *p;
  size_t len = strlen(actor);
  composite_value_init(cv);
  char *next_pos = parser(stack, actor, len, cv);
  if (next_pos != actor + len) {
    ERR("unexpected %s\n", next_pos);
  }
  memset(operand_addrs, 0, sizeof(*operand_addrs));
  get_composite_value_operand_addrs(cv, operand_addrs);
  size_t i;

  for (i = 0; i < operand_addrs->pos; i++) {
    switch (operand_addrs->types[i])
    {
      case ARG_PTR:
        p = va_arg(ap, void *);
        *((void **) operand_addrs->addrs[i]) = p;
        DS_PRINT("load pointer %p as %dth operand to store in %p\n",
                 p, i, operand_addrs->addrs[i]);
        break;
      case ARG_INT:
      {
        int iv = va_arg(ap, int);
        *((int *) operand_addrs->addrs[i]) = iv;
        DS_PRINT("load int %d as %dth operand to store in %p\n",
                 iv, i, operand_addrs->addrs[i]);
        break;
      }
      case ARG_DOUBLE:
      {
        double dv = va_arg(ap, double);
        *((double *) operand_addrs->addrs[i]) = dv;
        DS_PRINT("load double %lf as %dth operand to store in %p\n",
                 dv, i, operand_addrs->addrs[i]);
        break;
      }
    }
  }
  return 1;
}

/*
 *
 * return the number of bytes written (excluding the null terminator)
 */
size_t
json_vinject(
  char *pos,
  size_t size,
  char *injector,
  va_list ap)
{
  struct stack stack = { .array = {0}, .top = 0, .actor = INJECTOR };
  struct operand_addrs rec;
  struct composite_value cv;

  prepare_actor(parse_actor, &stack, &rec, &cv, injector, ap);
  check_ptr_maps(cv.maps);


  char * output_buf = pos;
  size_t output_size = pos ? size : 0;

  struct injection_info info = {
    .encoding = ENCODING_JSON,
    .A = cv.maps
  };

  size_t used_bytes =
    inject_composite_value(output_buf, output_size, &cv, &info);
  if (info.fp)
    fclose(info.fp);

  free_composite_value(&cv);

  return used_bytes;
}

/*
 * buf_p:  points to a memory block to hold the allocated memory block
 *
 * on return:
 *      the number of bytes written (excluding the null terminator)
 *      buf_p points a null terminated JSON string
 *
 */
size_t json_ainject (char ** buf_p, char * injector, ...)
{
  va_list ap;
  va_start(ap, injector);
  size_t used_bytes = json_vinject(NULL, 0, injector, ap);
  va_end(ap);

  char * buf = malloc(used_bytes+1);
  buf[used_bytes] = 0;
  *buf_p = buf;

  va_start(ap, injector);
  json_vinject(buf, used_bytes + 1, injector, ap);
  va_end(ap);

  ASSERT_S(used_bytes == strlen(buf), "used_bytes != strlen(buf)");
  return used_bytes;
}

size_t json_inject (char * pos, size_t size, char * injector, ...)
{
  va_list ap;
  va_start(ap, injector);
  size_t used_bytes = json_vinject(pos, size, injector, ap);
  va_end(ap);
  return used_bytes;
}


static char* type_to_string(jsmntype_t type)
{
  switch (type) {
    case JSMN_UNDEFINED:  return "undefined";
    case JSMN_OBJECT:     return "object";
    case JSMN_ARRAY:      return "array";
    case JSMN_STRING:     return "string";
    case JSMN_PRIMITIVE:  return "primitive";
    default:              ERR("Unknown JSMN_XXXX type encountered (code: %d)", type);
  }
  return NULL; /* avoid warning */
}

static void
print_tok (FILE * fp, char * json, jsmntok_t * tok, int i) {
  fprintf(fp, "[%u][p:%d][size:%d]%s `%.*s`\n",
          i, tok[i].parent,
          tok[i].size, type_to_string(tok[i].type),
          (int)(tok[i].end - tok[i].start), json + tok[i].start);
}

static int keycmp(char *json, jsmntok_t *tok, struct sized_buffer *key)
{
  if (tok->type == JSMN_STRING
      && key->size == (size_t)(tok->end - tok->start)
      && 0 == strncmp(json + tok->start, key->start, key->size))
  {
    return 0;
  }
  return -1;
}

static char * copy_over_string (size_t * new_size, char * str, size_t len)
{
  char * new_str = NULL;
  if (json_string_unescape(&new_str, new_size, str, len)) {
    return new_str;
  }
  else {
    /* ill formed string */
    char * p = NULL;
    asprintf(&p, "cannot unescape an ill-formed-string %.*s", (int)len, str);
    *new_size = strlen(p) + 1;
    return p;
  }
}

struct extraction_info {
  struct sized_buffer input;
  char * pos;
  jsmntok_t *tokens;
  int n_tokens;
  struct ptr_map **E;
};

static size_t extract_str (struct action * v, int i, struct extraction_info * info)
{
  jsmntok_t * tokens = info->tokens;
  char * json = info->pos;
  if (JSMN_STRING != tokens[i].type && JSMN_PRIMITIVE != tokens[i].type) {
    if (strong_type) {
      print_tok(stderr, json, tokens, i);
      ERR("expected string");
    }
    else {
      return 0;
    }
  }

  bool is_null = false;
  if (JSMN_PRIMITIVE == tokens[i].type && 'n' == json[tokens[i].start]) {
    is_null = true;
  }

  size_t new_size = 0;
  int len = tokens[i].end - tokens[i].start;
  char * escaped = copy_over_string(&new_size, json + tokens[i].start, len);

  switch(v->mem_size.tag)
  {
    case SIZE_ZERO:
    {
      char **p = (char **) v->operand;
      if (is_null) {
        *p = NULL;
      }
      else {
        int len = tokens[i].end - tokens[i].start + 1;
        *p = malloc(len);
        int ret = snprintf(*p, len, "%.*s", len - 1, escaped);
        ASSERT_S(ret < len, "out-of-bounds write");
      }
      add_defined(info->E, p);
      break;
    }
    case SIZE_FIXED:
    case SIZE_PARAMETERIZED:
    {
      if (is_null) {
        ((char *)v->operand)[0] = 0;
      }
      else {
        int ret = snprintf((char *) v->operand, v->mem_size.size,
                           "%.*s", tokens[i].end - tokens[i].start, escaped);
        ASSERT_S((size_t) ret < v->mem_size.size, "out-of-bounds write");
      }
      add_defined(info->E, v->operand);
      break;
    }
    case SIZE_UNKNOWN:
    {
      /* we have to allow this potential oob write as
         we don't know the buffer size of recipient.*/
      if (is_null) {
        ((char *)v->operand)[0] = 0;
      }
      else {
        sprintf((char *) v->operand, "%.*s", (int) new_size, escaped);
      }
      add_defined(info->E, v->operand);
      break;
    }
  }
  if (escaped != json + tokens[i].start)
    free(escaped);
  return 1;
}

static size_t extract_scalar (struct action * a, int i, struct extraction_info * info)
{
  jsmntok_t * tokens = info->tokens;
  char * json = info->pos, * xend; /* exclusive end */
  if (tokens[i].type != JSMN_PRIMITIVE && tokens[i].type != JSMN_STRING) {
    if (strong_type) {
      print_tok(stderr, json, tokens, i);
      ERR("Token is not a primitive or string");
    }
    else {
      return 0;
    }
  }

  bool is_null = false;
  if (JSMN_PRIMITIVE == tokens[i].type && 'n' == json[tokens[i].start])
    is_null = true;
  switch(a->_.builtin)
  {
    case B_INT:
    {
      if (is_null)
        *(int *) a->operand = 0;
      else {
        int ival = (int) strtol(json + tokens[i].start, &xend, 10);
        if (xend != json + tokens[i].end) {
          ival = (int) strtol(json + tokens[i].start, &xend, 16);
          if (xend != json + tokens[i].end) {
            ERR("failed to extract int from %.*s\n",
                tokens[i].end - tokens[i].start, json + tokens[i].start);
          }
        }
        *(int *) a->operand = ival;
      }
      add_defined(info->E, a->operand);
      break;
    }
    case B_STRING_AS_HEX_UINT:
    {
      if (is_null)
        *(int *) a->operand = 0;
      else if (JSMN_STRING == tokens[i].type) {
        *(int *) a->operand = (int) strtoul(json + tokens[i].start, &xend, 16);
        if (xend != json + tokens[i].end)
          ERR("failed to extract s_as_hex_int from %.*s\n",
              tokens[i].end - tokens[i].start, json + tokens[i].start);
      }
      else {
        ERR("failed to extract s_as_hex_int from %.*s\n",
            tokens[i].end - tokens[i].start, json + tokens[i].start);
      }
      add_defined(info->E, a->operand);
      break;
    }
    case B_STRING_AS_U64:
    case B_STRING_AS_HEX64:
    {
      int base = 10;
      if (a->_.builtin == B_STRING_AS_HEX64)
        base = 0;

      if (is_null)
        *(uint64_t *) a->operand = 0;
      else if (JSMN_STRING == tokens[i].type) {
        *(uint64_t *) a->operand = (uint64_t) strtoull(json + tokens[i].start,
                                                       &xend, base);
        if (xend != json + tokens[i].end)
          ERR("failed to extract s_as_u64 or s_as_hex64 from %.*s\n",
              tokens[i].end - tokens[i].start, json + tokens[i].start);
      }
      else {
        ERR("failed to extract s_as_u64 or s_as_hex64 from %.*s\n",
            tokens[i].end - tokens[i].start, json + tokens[i].start);
      }
      add_defined(info->E, a->operand);
      break;
    }
    case B_BOOL:
      if (JSMN_PRIMITIVE == tokens[i].type)
        switch (json[tokens[i].start])
        {
          case 't': *(bool *)a->operand = true; break;
          case 'f': *(bool *)a->operand = false; break;
          default:
            ERR("failed to extract bool from %.*s\n",
                tokens[i].end - tokens[i].start, json + tokens[i].start);
        }
      else
        ERR("failed to extract bool from %.*s\n",
            tokens[i].end - tokens[i].start, json + tokens[i].start);
      add_defined(info->E, a->operand);
      break;
    case B_KEY_EXISTENCE:
      *(bool *)a->operand = true;
      break;
    case B_LONG:
      if (is_null)
        *(long *) a->operand = 0;
      else {
        *(long *) a->operand = strtol(json + tokens[i].start, &xend, 10);
        if (xend != json + tokens[i].end)
          ERR("failed to extract long from %.*s\n",
              tokens[i].end - tokens[i].start, json + tokens[i].start);
      }
      add_defined(info->E, a->operand);
      break;
    case B_UINT64:
      if (is_null)
        *(uint64_t *) a->operand = 0;
      else {
        *(uint64_t *) a->operand = strtoll(json + tokens[i].start, &xend, 10);
        if (xend != json + tokens[i].end)
          ERR("failed to extract long long from %.*s\n",
              tokens[i].end - tokens[i].start, json + tokens[i].start);
      }
      add_defined(info->E, a->operand);
      break;
    case B_LONG_LONG:
      if (is_null)
        *(long long *) a->operand = 0;
      else {
        *(long long *) a->operand = strtoll(json + tokens[i].start, &xend, 10);
        if (xend != json + tokens[i].end)
          ERR("failed to extract long long from %.*s\n",
              tokens[i].end - tokens[i].start, json + tokens[i].start);
      }
      add_defined(info->E, a->operand);
      break;
    case B_FLOAT:
      if (is_null)
        *(float *) a->operand = 0;
      else {
        *(float *) a->operand = strtof(json + tokens[i].start, &xend);
        if (xend != json + tokens[i].end)
          ERR("failed to extract float from %.*s\n",
              tokens[i].end - tokens[i].start, json + tokens[i].start);
      }
      add_defined(info->E, a->operand);
      break;
    case B_DOUBLE:
      if (is_null)
        *(double *) a->operand = 0;
      else {
        *(double *) a->operand = strtod(json + tokens[i].start, &xend);
        if (xend != json + tokens[i].end)
          ERR("failed to extract double from %.*s\n",
              tokens[i].end - tokens[i].start, json + tokens[i].start);
      }
      add_defined(info->E, a->operand);
      break;
    default:
      ERR("unexpected %d\n", a->_.builtin);
  }
  return 1;
}

static size_t apply_extraction(struct value *v, int idx, struct extraction_info *info)
{
  jsmntok_t * tokens = info->tokens;
  char * json = info->pos;
  ASSERT_S(V_ACTION == v->tag, "expect an action");

  struct action * a = &v->_.action;
  if (ACT_BUILT_IN == a->tag) {
    switch (a->_.builtin)
    {
      case B_LINE_AND_COLUMN:
      {
        struct line_and_column *lnc = (struct line_and_column *) a->operand;
        struct line_and_column x;
        addr_to_lnc(info->input.start, info->input.size,
                    json + tokens[idx].start, &x);
        lnc->line = x.line;
        lnc->column = x.column;
        break;
      }
      case B_STRING:
        return extract_str(a, idx, info);
      case B_TOKEN:
      {
        struct sized_buffer *tk = a->operand;
        tk->start = json + tokens[idx].start;
        tk->size = tokens[idx].end - tokens[idx].start;
        add_defined(info->E, a->operand);
        return 1;
      }
      default:
        if (a->_.builtin < B_STRING)
          return extract_scalar(a, idx, info);
        else
          ERR("unexpected case %d\n", a->_.builtin);
    }
  }
  else if (ACT_FORMAT_STRING == a->tag) {
    ERR("not supported yet");
  }
  else {
    if (tokens[idx].type == JSMN_PRIMITIVE
        && (0 == strncmp(json + tokens[idx].start, "null", 4))) {
      /*es->is_applied = false;*/
      return 0;
    }
    else if (0 == tokens[idx].size
             && (tokens[idx].type == JSMN_OBJECT
                 || tokens[idx].type == JSMN_ARRAY)) {
      return 0;
    }
    else {
      int (*f)(char *, size_t, void *);
      f = a->_.user_def;
      int ret = (*f)(json + tokens[idx].start,
                     tokens[idx].end - tokens[idx].start,
                     a->operand);
      if (0 == ret)
        return 0;
      else {
        add_defined(info->E, a->operand);
        return 1;
      }
    }
  }
  return 1;
}

static size_t
extract_object_value (struct composite_value * cv, int parent, struct extraction_info *);
static size_t
extract_array_value (struct composite_value * cv, int parent, struct extraction_info *);

static size_t
extract_value (struct value * v, int val_idx, struct extraction_info * info)
{
  size_t ret = 0;
  switch (v->tag) {
    case V_ACTION:
      ret = apply_extraction(v, val_idx, info);
      break;
    case V_COMPOSITE_VALUE:
      if (v->_.cv->is_object)
        ret = extract_object_value(v->_.cv, val_idx, info);
      else
        ret = extract_array_value(v->_.cv, val_idx, info);
      break;
    case V_PRIMITIVE:
      ERR("extract does not support json primitive\n");
      break;
    case V_STRING_LITERAL:
      ERR("extract does not support string literal\n");
      break;
  }
  v->is_applied = true;
  return ret;
}

static size_t
extract_access_path (
  int val_idx,
  struct access_path_value *apv,
  struct access_path *curr_path,
  struct extraction_info * info)
{
  char * json = info->pos;
  jsmntok_t * tokens = info->tokens;
  int n_toks = info->n_tokens;

  int i = val_idx, ic;
  if (curr_path) {
    switch (tokens[val_idx].type)
    {
      case JSMN_OBJECT:
        if (0 == tokens[val_idx].size)
          return 0;

        for (ic = i + 1; ic < n_toks && tokens[ic].start < tokens[i].end; ic++) {
          if (i != tokens[ic].parent)
            continue;

          /* top level key within tokens[i] */
          if (0 == keycmp(json, &tokens[ic], &curr_path->key)) {
            /* fpri ntf(stderr, "> %.*s == ", curr_path->key.size, curr_path->key.start);
               print_tok(stderr, json, t, ic); */
            return extract_access_path(ic + 1, apv, curr_path->next, info);
          }
        }
        return 0;
      case JSMN_ARRAY:
      {
        if (0 == tokens[val_idx].size)
          return 0;

        char *xend;
        int index = strtol(curr_path->key.start, &xend, 10);
        ASSERT_S(*xend == ')', "Index is not a number");
        ASSERT_S(index >= 0, "Index is not zero or positive");
        ASSERT_S(index < tokens[i].size, "Index is out-of-bound");

        ic = i + 1; /* the first child of i; */
        if (ic < n_toks)
          return extract_access_path(ic + index, apv, curr_path->next, info);
        else
          return 0;
      }
      default:
        ERR("Patch match error (not an Object or Array)");
    }
    return 0;
  }
  struct value * v = &apv->value;
  int ret = extract_value(v, val_idx, info);
  apv->value.is_applied = true;
  if (ret) {
    /*print_access_path_value(stderr, apv); */
    /*fprintf(stderr, "< matched: "); */
    /*print_tok(stderr, json, t, val_idx); */
  }
  return ret;
}

static size_t
extract_object_value (
  struct composite_value * cv,
  int parent,
  struct extraction_info * info)
{
  char * json = info->pos;
  jsmntok_t * tokens = info->tokens;

  int key_idx = parent + 1, val_idx = parent + 2;
  struct access_path_value *p;
  int nkeys = 0, ret = 0, n = tokens[parent].size;

  while (1) {
    size_t i;
    if (tokens[key_idx].type != JSMN_STRING) {
      print_tok(stderr, json, tokens, key_idx);
    }
    ASSERT_S(tokens[key_idx].type == JSMN_STRING, "Not a key"); /* make sure it's a key */
    ASSERT_S(tokens[key_idx].parent == parent, "Token is not at top level"); /* make sure it's at the toplevel */

    val_idx = key_idx + 1;
    for (i = 0; i < cv->_.pairs.size; i++) {
      p = cv->_.pairs.pos + i;
      if (p->value.is_applied)
        continue;

      if (0 == keycmp(json, &tokens[key_idx], &p->path.key)) {
        /*fprintf(stderr, "> %.*s == ", p->path.key.size, p->path.key.start);
          print_tok(stderr, json, t, key_idx); */
        ret += extract_access_path(val_idx, p, p->path.next, info);
      }
      else if (p->path.is_star) {
        size_t ksize = tokens[key_idx].end - tokens[key_idx].start;
        asprintf((char **)(p->value._.action.key),
                 "%.*s", (int)ksize, json + tokens[key_idx].start);
        ret += extract_access_path(val_idx, p, p->path.next, info);
      }
    }

    nkeys ++;
    if (nkeys < n) {
      /* find the next key */
      key_idx = val_idx + 1;  /* this might not be a key */
      while (tokens[key_idx].parent != parent) key_idx ++;
    }
    else
      break;
  }
  return ret;
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

static size_t
extract_array_value (
  struct composite_value * cv,
  int parent,
  struct extraction_info * info)
{
  jsmntok_t * tokens = info->tokens;
  struct sized_buffer **token_array = NULL;
  int * children;
  int n = tokens[parent].size;
  size_t ret = 0;
  size_t i;
  int child_no, ic;

  struct value * v = is_list_extraction(cv);

  if (v)
    token_array = (struct sized_buffer **)
      ntl_malloc(n, sizeof(struct sized_buffer));
  else
    children = malloc(n * sizeof(int));

  for (child_no = 0, ic = parent + 1; child_no < n; ic++) {
    if (tokens[ic].parent != parent)  /* not a child */
      continue;

    if (v) {
      token_array[child_no]->start = info->pos + tokens[ic].start;
      token_array[child_no]->size = tokens[ic].end - tokens[ic].start;
    }
    else {
      children[child_no] = ic;
    }
    ++child_no;
  }

  if (v) {
    *(struct sized_buffer ***)v->_.action.operand = token_array;
    return 1;
  }

  for (i = 0; i < cv->_.elements.size && i < (size_t)n; i++) {
    v = cv->_.elements.pos + i;
    if (v->is_applied)
      continue;
    ret += extract_value(v, children[i], info);
  }

  free(children);
  return ret;
}

size_t
json_vextract(char * json, size_t size, char * extractor, va_list ap)
{
  struct stack stack = { .array = {0}, .top = 0, .actor = EXTRACTOR };
  struct operand_addrs rec;
  struct composite_value cv;

  prepare_actor(parse_actor, &stack, &rec, &cv, extractor, ap);
  check_ptr_maps(cv.maps);


  jsmn_parser parser;

  /*calculate how many tokens are needed */
  jsmn_init(&parser);
  int num_tok = jsmn_parse(&parser, json, size, NULL, 0);
  JSMN_CHECK(num_tok, json, size);
  DS_PRINT("# of tokens = %d", num_tok);

  jsmntok_t * tokens = malloc(sizeof(jsmntok_t) * num_tok);

  /*fetch tokens */
  jsmn_init(&parser);
  num_tok = jsmn_parse(&parser, json, size, tokens, num_tok);
  JSMN_CHECK(num_tok, json, size);

  /* Assume the top-level element is an object */
  if (!(tokens[0].type == JSMN_OBJECT || tokens[0].type == JSMN_ARRAY))
    ERR("Found %d, Object or array expected", tokens[0].type);


  struct extraction_info info = {
    .pos = json, 
    .E = cv.maps,
    .input = {.start = json, .size = size},
    .n_tokens = num_tok,
    .tokens = tokens
  };


  size_t ret = 0;
  switch (tokens[0].type)
  {
    case JSMN_OBJECT:
      if (!cv.is_object)
        ERR("Cannot apply '%s' to json array:'%.*s'\n",
            extractor, tokens[0].size, json + tokens[0].start);
      ret = extract_object_value(&cv, 0, &info);
      break;
    case JSMN_ARRAY:
      if (cv.is_object)
        ERR("Cannot apply '%s' to json object:'%.*s'\n",
            extractor, tokens[0].size, json + tokens[0].start);
      ret = extract_array_value(&cv, 0, &info);
      break;
    default:
      ERR("Unexpected toplevel token %s\n", type_to_string(tokens[0].type));
  }


  free(tokens);
  free_composite_value(&cv);

  return ret;
}

size_t json_extract (char * json, size_t size, char * extractor, ...)
{
  va_list ap;
  va_start(ap, extractor);
  size_t used_bytes = json_vextract(json, size, extractor, ap);
  va_end(ap);
  return used_bytes;
}

static char *
parse_key_value(
  struct stack *stack,
  char *pos,
  size_t size,
  struct access_path_value *av)
{
  char * const start_pos = pos, * const end_pos = pos + size,
    * next_pos = NULL;
  int len = 0;
  ASSERT_S('(' == *pos, "expecting '('");
  pos ++;
  while (pos < end_pos) {
    if (')' == *pos) goto out_of_loop;
    ++pos;
  }

  if (pos == end_pos)
    ERR("A close bracket ')' is missing");

  out_of_loop:
  len = pos - start_pos - 1;
  ASSERT_S(len > 0, "Key is missing");

  av->path.key.start = start_pos + 1;
  av->path.key.size = len;

  if (')' == *pos)
    ++pos; /* eat up ')' */
  SKIP_SPACES(pos, end_pos);
  switch (*pos)
  {
    case ':':
      ++pos; /* eat up ':' */
      if (parse_value(stack, pos, end_pos - pos, &av->value, &next_pos))
        pos = next_pos;
      else
        ERR("expecting a value after '=', %s does not have a legit value", pos);
      break;
    default:
      ERR("expecting '=' %c\n", *pos);
  }
  return pos;
}

static char *
parse_query_string (
  struct stack * stack,
  char * pos,
  size_t size,
  struct composite_value  * cv)
{
  char * const start_pos = pos, * const end_pos = pos + size;
  struct sized_access_path_value * pairs = &cv->_.pairs;
  pairs->pos = calloc(MAX_ACTION_NUMBERS, sizeof(struct access_path_value));
  cv->is_object = true;

  size_t i = 0;
  while (pos < end_pos)
  {
    SKIP_SPACES(pos, end_pos);
    if (',' == *pos) {
      pos ++;
    }
    else if ('(' == *pos) {
      pos = parse_key_value(stack, pos, end_pos - pos, pairs->pos + i);
      i++;
    }
    else if ('@' == *pos) {
      char *next_pos = NULL;
      if (parse_pointer_maps(pos, end_pos - pos, cv->maps, &next_pos))
        pos = next_pos;
      SKIP_SPACES(pos, end_pos);
    }
    else if (0 == stack->top || TOP(stack) == *pos) {
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


static int
inject_query_key_value (
  char * pos,
  size_t size,
  struct access_path_value * ap,
  struct injection_info * info)
{
  char * const end_pos = pos + size;
  size_t used_bytes = 0;
  used_bytes += xprintf(pos, size, info, "%.*s=", ap->path.key.size,
                        ap->path.key.start);
  pos = info->next_pos;

  used_bytes += inject_value(pos, end_pos - pos, &ap->value, info);
  return used_bytes;
}

static int
inject_query_key_value_list (
  char * pos,
  size_t size,
  struct composite_value * cv,
  struct injection_info * info)
{
  char * const end_pos = pos + size;
  size_t used_bytes = 0, count, i, j;

  count = cv->_.pairs.size;
  for (i = 0; i < cv->_.pairs.size; i++) {
    struct access_path_value *p = cv->_.pairs.pos + i;
    if (!has_value(info, &p->value))
      count--;
  }

  if (0 == count) {
    xprintf(pos, size, info, "");
    return 0;
  }
  else {
    xprintf(pos, size, info, "?");
    pos = info->next_pos;
  }

  for (i = 0, j = 0; i < cv->_.pairs.size; i++) {
    struct access_path_value *p = cv->_.pairs.pos + i;
    if (!has_value(info, &p->value)) continue;

    used_bytes += inject_query_key_value(pos, end_pos - pos, p, info);
    pos = info->next_pos;

    if (j + 1 != count) {
      used_bytes += xprintf(pos, end_pos - pos, info, "&");
      pos = info->next_pos;
    }
    j++;
  }
  return used_bytes;
}


size_t
query_vinject(char *pos, size_t size, char *injector, va_list ap)
{
  struct stack stack = { .array = {0}, .top = 0, .actor = INJECTOR };
  struct operand_addrs  rec;
  struct composite_value cv;

  prepare_actor(parse_query_string, &stack, &rec, &cv, injector, ap);
  check_ptr_maps(cv.maps);


  char * output_buf = pos;
  size_t output_size = pos ? size : 0;

  struct injection_info info = {
    .encoding = ENCODING_URL,
    .A = cv.maps
  };

  size_t used_bytes =
    inject_query_key_value_list(output_buf, output_size, &cv, &info);
  if (info.fp)
    fclose(info.fp);

  free_composite_value(&cv);

  return used_bytes;
}

size_t
query_inject(char *query, size_t size, char *injector, ...)
{
  va_list ap;
  va_start(ap, injector);
  size_t used_bytes = query_vinject(query, size, injector, ap);
  va_end(ap);
  return used_bytes;
}

int
json_to_sized_buffer_ntl(char *json, size_t size, NTL_T(struct sized_buffer) *p)
{
  int i;
  int num_tok;
  jsmn_parser parser;
  jsmn_init(&parser);
  jsmntok_t * tokens = NULL;
  num_tok = jsmn_parse(&parser, json, size, NULL, 0);
  DS_PRINT("# of tokens = %d", num_tok);
  JSMN_CHECK(num_tok, json, size);

  tokens = malloc(sizeof(jsmntok_t) * num_tok);
  jsmn_init(&parser);
  num_tok = jsmn_parse(&parser, json, size, tokens, num_tok);
  JSMN_CHECK(num_tok, json, size);

  /* Assume the top-level element is an object */
  if (!(tokens[0].type == JSMN_OBJECT || tokens[0].type == JSMN_ARRAY))
    ERR("Found %d, Object or array expected", tokens[0].type);

  for (i = 0; i < num_tok; i++) {
    /*print_tok(stderr, json, tokens, i); */
  }

  struct sized_buffer **token_array = NULL;
  int n = tokens[0].size;
  token_array = (struct sized_buffer **)ntl_calloc(n, sizeof(struct sized_buffer));

  int idx, ic;
  for (idx = 0, ic = 0 + 1; ic < num_tok && idx < n; ic++) {
    if (tokens[ic].parent != 0)
      continue;
    token_array[idx]->start = json + tokens[ic].start;
    token_array[idx]->size = tokens[ic].end - tokens[ic].start;
    ++idx;
  }
  free(tokens);
  *p = token_array;
  return n;
}

size_t
extract_ntl_from_json(
  char *buf,
  size_t len,
  struct ntl_deserializer *ntl_deserializer)
{
  ntl_deserializer->partition_as_sized_bufs = json_to_sized_buffer_ntl;
  return ntl_from_buf(buf, len, ntl_deserializer);
}

size_t
extract_ntl_from_json2(
  char *buf,
  size_t len,
  struct ntl_deserializer *ntl_deserializer)
{
  ntl_deserializer->partition_as_sized_bufs = json_to_sized_buffer_ntl;
  return ntl_from_buf2(buf, len, ntl_deserializer);
}
