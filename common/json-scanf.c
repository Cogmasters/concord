/*
 * Copyright (c) 2020 Lucas Müller
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "json-scanf.h"
#include "debug.h"

#include "ntl.h"

#define JSMN_STATIC  // dont expose jsmn symbols
#define JSMN_PARENT_LINKS // add parent links to jsmn_tok, which are needed
#define JSMN_STRICT  // parse json in strict mode
#include "jsmn.h"


#define STREQ(s,t)    (0 == strcmp(s,t))
#define STRNEQ(s,t,n) (0 == strncmp(s,t,n))

#define N_PATH_MAX 8
#define KEY_MAX 128

struct path_specifier {
  char key[KEY_MAX];
  struct path_specifier *next;
};

struct extractor_specifier {
  bool match_toplevel_array; // if this is true, there is no path_specifiers.
  struct path_specifier path_specifiers[N_PATH_MAX];
  char type_specifier[10];
  size_t size;
  void *recipient; //must be a pointer, and it cannot be NULL
  bool is_applied;
  bool has_dynamic_size;
  bool is_nullable;
  bool allocate_memory;
  bool is_funptr;
  extractor *funptr;
};

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

static int
jsoneq(const char *json, jsmntok_t *tok, const char *str)
{
  if (tok->type == JSMN_STRING
      && (int)strlen(str) == tok->end - tok->start
      && STRNEQ(json + tok->start, str, tok->end - tok->start))
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
    // ill formed string
    char * p = NULL;
    asprintf(&p, "cannot unescape an ill-formed-string %.*s", (int)len, str);
    *new_size = strlen(p) + 1;
    return p;
  }
}
static void
match_path (char *buffer, jsmntok_t *t,
            int n_toks, int start_tok,
            struct extractor_specifier *es,
            struct path_specifier *ps)
{
  char *end = 0;
  int i = start_tok, ic;
  if (ps) {
    switch (t[i].type) {
    case JSMN_OBJECT:
        for (ic = i + 1; t[ic].start < t[i].end; ic++)
        {
          if (i != t[ic].parent)
            continue;

          // top level key within t[i]
          
          if (0 == jsoneq(buffer, &t[ic], ps->key)) {
            match_path(buffer, t, n_toks, ic+1, es, ps->next);
            return;
          }
        }
        break;
    case JSMN_ARRAY:
     {
        char *end;
        int index = strtol(ps->key, &end, 10);
        VASSERT_S(*end == 0, "Index '%s' is not a number", ps->key);
        VASSERT_S(index >= 0, "Index '%d' is not zero or positive", index);
        VASSERT_S(index < t[i].size, "Index %d > %d is out-of-bound ",
                  index, t[i].size);

        ic = i + 1; // the first child of i;
        match_path(buffer, t, n_toks, ic + index, es, ps->next);

        break;
     }
    default:
        ERR("Patch match error (not an Object or Array)");
    }

    return;
  }

  es->is_applied = true;
  if (STREQ(es->type_specifier, "char*")){
      switch (t[i].type) {
      case JSMN_STRING: {
        size_t new_size = 0;
        int len = t[i].end - t[i].start;
        char * escaped = copy_over_string(&new_size, buffer + t[i].start, len);
        if (es->allocate_memory) {
          char **p = (char **) es->recipient;
          int len = t[i].end - t[i].start + 1;
            *p = malloc(len);
            int ret = snprintf(*p, len, "%.*s", len - 1, escaped);
            ASSERT_S(ret < len, "out-of-bounds write");
        } else {
          if (es->size) {
            int ret = snprintf((char *) es->recipient, es->size,
                               "%.*s", t[i].end - t[i].start, escaped);
            ASSERT_S((size_t) ret < es->size, "out-of-bounds write");
          } else {
            // we have to allow this potential oob write as
            // we don't know the buffer size of recipient.
            sprintf((char *) es->recipient, "%.*s", (int)new_size, escaped);
          }
        }
        if (escaped != buffer + t[i].start)
          free(escaped);
        break;
      }
      case JSMN_PRIMITIVE:
          //something is wrong if is not null primitive
          if (!STRNEQ(buffer + t[i].start, "null", 4))
              goto type_error;
          if (es->allocate_memory) {
            char **p = (char **) es->recipient;
            *p = NULL;
          }
          else {
            *(char *) es->recipient = '\0'; //@todo we need a better way to represent null
          }
          break;
      default:
        goto type_error;
      }
  }
  else if (STREQ(es->type_specifier, "copy")) {
    if (es->allocate_memory) {
      char **p = (char **) es->recipient;
      int len = t[i].end - t[i].start + 1;
      *p = malloc(len);
      int ret = snprintf(*p, len, "%.*s", len - 1, buffer+t[i].start);
      ASSERT_S(ret < len, "out-of-bounds write");
    }
    else if (es->size) {
      int ret = snprintf((char *) es->recipient, es->size,
                         "%.*s", t[i].end - t[i].start, buffer + t[i].start);
      ASSERT_S((size_t)ret < es->size, "out-of-bounds write");
    }
    else {
      sprintf((char *) es->recipient, "%.*s", t[i].end - t[i].start,
              buffer + t[i].start);
    }
  }
  else if (STREQ(es->type_specifier, "array")) {
    struct sized_buffer **token_array;
    if (JSMN_ARRAY == t[i].type) {
      int n = t[i].size;
      token_array = (struct sized_buffer **)
        ntl_malloc(n, sizeof(struct sized_buffer));
      int idx;
      for (idx = 0, ic = i + 1; ic < n_toks && idx < n; ic++) {
        if (t[ic].parent != i) 
          continue;
        token_array[idx]->start = buffer + t[ic].start;
        token_array[idx]->size = t[ic].end - t[ic].start;

        ++idx;
      }
      *(struct sized_buffer ***)es->recipient = token_array;
    }
    else {
      // something is wrong
      goto type_error;
    }
  }
  else if (STREQ(es->type_specifier, "funptr")) {
    if (t[i].type == JSMN_PRIMITIVE && (STRNEQ(buffer + t[i].start, "null", 4))) {
      es->is_applied = false;
    }
    else if (0 == t[i].size 
            && (t[i].type == JSMN_OBJECT || t[i].type == JSMN_ARRAY)) {
      es->is_applied = false;
    }
    else {
      extractor *e = es->funptr;
      int ret = (*e)(buffer + t[i].start, t[i].end - t[i].start, es->recipient);
      if (0 == ret)
        es->is_applied = false;
    }
  }
  else if (STREQ(es->type_specifier, "token")) {
    struct sized_buffer * tk = es->recipient;
    tk->start = buffer + t[i].start;
    tk->size = t[i].end - t[i].start;
  }
  else if (STREQ(es->type_specifier, "bool*")) {
    VASSERT_S(t[i].type == JSMN_PRIMITIVE, "'%.*s' is not a primitive",
              t[i].size, buffer + t[i].start);
    switch (buffer[t[i].start]) {
      case 't': *(bool *)es->recipient = true; break;
      case 'f': *(bool *)es->recipient = false; break;
      default: goto type_error; 
    }
  }
  else if (STREQ(es->type_specifier, "int*")) {
    VASSERT_S(t[i].type == JSMN_PRIMITIVE, "'%.*s' is not a primitive",
              t[i].size, buffer + t[i].start);
    switch(buffer[t[i].start]) {
      case 'n': *(int *) es->recipient = 0; break;
      default:
        *(int *) es->recipient = (int) strtol(buffer + t[i].start, &end, 10);
        if (end != buffer + t[i].end) goto type_error;
        break;
    }
  }
  else if (STREQ(es->type_specifier, "long*")) {
    VASSERT_S(t[i].type == JSMN_PRIMITIVE, "'%.*s' is not a primitive",
              t[i].size, buffer + t[i].start);
    switch(buffer[t[i].start]) {
      case 'n': *(long *) es->recipient = 0; break;
      default:
        *(long *) es->recipient = strtol(buffer + t[i].start, &end, 10);
        if (end != buffer + t[i].end) goto type_error;
        break;
    }
  }
  else if (STREQ(es->type_specifier, "long long*")) {
    VASSERT_S(t[i].type == JSMN_PRIMITIVE, "'%.*s' is not a primitive",
              t[i].size, buffer + t[i].start);
    switch(buffer[t[i].start]) {
      case 'n': *(long long *) es->recipient = 0; break;
      default:
        *(long long *) es->recipient = strtoll(buffer + t[i].start, &end, 10);
        if (end != buffer + t[i].end) goto type_error;
        break;
    }
  }
  else if (STREQ(es->type_specifier, "float*")) {
    VASSERT_S(t[i].type == JSMN_PRIMITIVE, "'%.*s' is not a primitive",
              t[i].size, buffer + t[i].start);
    switch(buffer[t[i].start]) {
      case 'n': *(float *) es->recipient = 0; break;
      default:
        *(float *) es->recipient = strtof(buffer + t[i].start, &end);
        if (end != buffer + t[i].end) goto type_error;
        break;
    }
  }
  else if (STREQ(es->type_specifier, "double*")) {
    VASSERT_S(t[i].type == JSMN_PRIMITIVE, "'%.*s' is not a primitive",
              t[i].size, buffer + t[i].start);
    switch(buffer[t[i].start]) {
      case 'n': *(double *) es->recipient = 0; break;
      default:
        *(double *) es->recipient = strtod(buffer + t[i].start, &end);
        if (end != buffer + t[i].end) goto type_error;
        break;
    }
  }
  else if (STREQ(es->type_specifier, "exist")) {
    // this has to be applied after all applications are done
    es->is_applied = false;
  }
  else {
      goto type_error;
  }

  return;

type_error:
  ERR("Expected specifier %s but found: '%.*s' )\n", es->type_specifier,
        t[i].end - t[i].start, buffer + t[i].start);
  // report errors;
  return;
}

static void
apply_array (char *str, jsmntok_t * tok, int n_toks,
             struct extractor_specifier *es)
{
  if (es->match_toplevel_array) {
    match_path(str, tok, n_toks, 0, es, es->path_specifiers[0].next);
  }
  else {
    ERR("Toplevel array does not match extractor_specifier %s)\n",
          es->path_specifiers[0].key);
  }
}

static void
apply_object(char *str, jsmntok_t *tok, int n_toks,
             struct extractor_specifier *es)
{
  int ik = 1, iv = 2;
  do {
    // tok[ik] must be a toplevel key, and tok[iv] must be its value
    if (tok[ik].type != JSMN_STRING) {
      D_PRINT("[%u][p:%d][size:%d]%s (%.*s)\n", ik, tok[ik].parent,
              tok[ik].size, print_token(tok[ik].type),
              (int)(tok[ik].end - tok[ik].start), str + tok[ik].start);
    }
    ASSERT_S(tok[ik].type == JSMN_STRING, "Not a key"); // make sure it's a key
    ASSERT_S(tok[ik].parent == 0, "Token is not at top level"); // make sure it's at the toplevel

    if (0 == jsoneq(str, &tok[ik], es->path_specifiers[0].key)) {
      match_path(str, tok, n_toks, iv, es, es->path_specifiers[0].next);
      break;
    }
    
    // skip all children toks of tok[iv]
    ik = iv + 1;
    if (ik >= n_toks)
      break; // we are done

    // find the next toplevel key
    for (ik = iv + 1; ik < n_toks && tok[ik].end < tok[iv].end; ik++)
      continue;

    iv = ik + 1;
    if (ik >= n_toks || iv >= n_toks)
      break; // we are done
  } while (ik < n_toks && iv < n_toks);
}


static char*
parse_type_specifier(char *specifier, struct extractor_specifier *es)
{
  char *start = specifier, *end;
  long size = strtol(start, &end, 10);

  bool is_valid_size = false, has_dsize = false, allocate_memory = false;
  if (end != start) {
    is_valid_size = true;
    specifier = end; // jump to the end of number
  }
  else if ('.' == *specifier && '*' == *(specifier+1)) {
    has_dsize = true;
    specifier += 2; // eat up '.' and '*'
  }
  else if ('.' == *specifier && '+' == *(specifier+1)) {
    allocate_memory = true;
    specifier += 2; // eat up '.' and '+'
  }
  else if ('.' == *specifier) {
    allocate_memory = true;
    specifier ++; // eat up '.'
  }
  else if ('?' == *specifier) { // this is deprecated and should be removed
    allocate_memory = true;
    specifier ++;
  }

  if (STRNEQ(specifier, "s", 1)){
    es->size = (is_valid_size) ? size : 0;
    es->has_dynamic_size = has_dsize;
    es->allocate_memory = allocate_memory;
    strcpy(es->type_specifier, "char*");
    return specifier + 1;
  }
  else if (STRNEQ(specifier, "S", 1)) {
    es->size = (is_valid_size) ? size : 0;
    es->has_dynamic_size = has_dsize;
    es->allocate_memory = allocate_memory;
    strcpy(es->type_specifier, "copy");
    return specifier + 1;
  }
  else if (STRNEQ(specifier, "L", 1)) {
    strcpy(es->type_specifier, "array");
    return specifier + 1;
  }
  else if (STRNEQ(specifier, "A", 1)) {
    strcpy(es->type_specifier, "array");
    return specifier + 1;
  }
  else if (STRNEQ(specifier, "F", 1)) {
    strcpy(es->type_specifier, "funptr");
    es->is_funptr = true;
    return specifier + 1;
  }
  else if (STRNEQ(specifier, "E", 1)) {
    strcpy(es->type_specifier, "exist");
    es->size = (is_valid_size) ? size : 0;
    es->has_dynamic_size = has_dsize;
    es->allocate_memory = allocate_memory;
    return specifier + 1;
  }
  else if (STRNEQ(specifier, "T", 1)) {
    strcpy(es->type_specifier, "token");
    return specifier + 1;
  }
  else if (STRNEQ(specifier, "d", 1)) {
    es->size = sizeof(int);
    strcpy(es->type_specifier, "int*");
    return specifier + 1;
  }
  else if (STRNEQ(specifier, "ld", 2)) {
    es->size = sizeof(long);
    strcpy(es->type_specifier, "long*");
    return specifier + 2;
  }
  else if (STRNEQ(specifier, "lld", 3)) {
    es->size = sizeof(long long);
    strcpy(es->type_specifier, "long long*");
    return specifier + 3;
  }
  else if (STRNEQ(specifier, "f", 1)) {
    es->size = sizeof(float);
    strcpy(es->type_specifier, "float*");
    return specifier + 1;
  }
  else if (STRNEQ(specifier, "lf", 2)) {
    es->size = sizeof(double);
    strcpy(es->type_specifier, "double*");
    return specifier + 2;
  }
  else if (STRNEQ(specifier, "b", 1)){
    es->size = sizeof(bool);
    strcpy(es->type_specifier, "bool*");
    return specifier + 1;
  }

  return 0;
}

/*
 * legit inputs:
 *      abc]
 *      10]
 *
 * illegit inputs:
 *      abc
 *      ]
 *      10
 */
static char*
parse_path_specifier(char * format, struct extractor_specifier *es,
                     struct path_specifier *curr_path, int next_path_idx)
{
  //@todo does this accounts for objects with numerical keys?
  ASSERT_S(next_path_idx < N_PATH_MAX, "Too many path specifiers");

  // until find a ']' or '\0'
  char *start = format;
  while (*format) {
    if (']' == *format) {
      break;
    }
    ++format;
  }

  ASSERT_S(*format == ']', "A close bracket ']' is missing");

  int len = format - start;
  if (0 == len && 1 == next_path_idx) { // this is the first path specifier
    es->match_toplevel_array = true;
  }
  else {
    // we don't allow empty [] at other places like this: [key][]
    ASSERT_S(len > 0, "Key is missing");
  }

  int ret = snprintf (curr_path->key, KEY_MAX, "%.*s", len, start);
  ASSERT_S(ret < KEY_MAX, "Key is too long (out-of-bounds write)");

  ++format; // eat up ']'
  switch (*format) {
  case '[':
   {
      ++format; // eat up '['
      struct path_specifier *next_path = es->path_specifiers+next_path_idx;
      curr_path->next = next_path;
      return parse_path_specifier(format, es, next_path, next_path_idx+1);
   }
  case '%':
  case ':':
      ++format; // eat up '%' or ':'
      return parse_type_specifier(format, es);
  default:
      return NULL;
  }
}

/* count amount of keys and check for formatting errors */
static void
format_analyze(char *format, size_t *num_keys)
{
  bool is_open = false;

next_iter:
  while (*format) /* run until end of string found */
  {
    // search for open bracket
    while (*format)
    {
      if (('%' == *format || ':' == *format) && 'E' == *(format+1)) {
        format += 2;
        (*num_keys) ++ ;
        goto next_iter;
      } else if ('[' == *format) {
        is_open = true;
        ++format; // eat up '['
        break;
      }
      ++format;
    }
    ASSERT_S(is_open && *format, "Missing '[' token in format string");

    // search for close bracket
    while (*format)
    {
      if (']' == *format) {
        if (*++format != '[') {
          is_open = false;
          break;
        }
        else {
          is_open = true;
        }
      }
      ++format;
    }
    ASSERT_S(!is_open, "Missing ']' token in format string");

    /* find % occurrence */
    while (*format)
    {
      if ('%' == *format || ':' == *format) {
        do { // skip type specifier
          ++format;
        } while (*format && *format != '[' && *format != ' ');
        break;
      }
      ++format;
    }
    (*num_keys) ++;
  }
}

#define SKIP_SPACES(s)   { while (isspace(*s)) ++s; }

static struct extractor_specifier*
parse_extractor_specifiers(char * format, size_t n)
{
  struct extractor_specifier *es = calloc(n, sizeof(*es));

  size_t i = 0;
  while (*format) 
  {
    SKIP_SPACES(format);
    if (('%' == *format || ':' == *format) && 'E' == *(format + 1)) {
      ++format; // eat up '%' or ':';
      format = parse_type_specifier(format, es+i);
    }
    else if ('[' == *format) {
      ++format; //eat up '['
      format = parse_path_specifier(format, es+i, es[i].path_specifiers+0, 1);
    }
    else {
      free(es);
      return NULL;
    }
    ++i;
  }

  return es;
}

static struct extractor_specifier*
format_parse(char *format, size_t *n)
{
  format_analyze(format, n);

  if (*n == 0) {
    ERR("fatal error: cannot find any format strings %s", format);
  }

  return parse_extractor_specifiers(format, *n);
}

/*
 *
 *  format grammar:
 *      ([key1]|[<n>])+:(d|ld|lld|f|lf|b|<n>s|<n>S|.*s|.*S|?s|?S|T) <space>
 *
 *      n is an integer
 *
 *  usage:
 *
 *      json_scanf(buf_start, buf_size, "[k1][k2]:d  [k2][1]:s", &i, str);
 *      :d, :f, :lf, :s, :.*s have the same effects as if they are used in scanf
 *
 *      :T captures the start position and length of any JSON value within
 *      the buf range (buf_start, buf_start + buf_size]
 *
 *      :S clones any JSON value as a string
 *
 *      :<n>s :<n>S -- length modifier can be applied to :s to limit how many bytes
 *      can be copied to the receiving parameter.
 *
 *      :.*s :.*S:
 *
 *      :?s :?S:
 *
 *      sized_buffer * toks = NULL;
 *      json_scanf(buf, buf_size, "[]:A", &toks);
 *      json_scanf(buf, buf_size, "[key]:A", &toks);
 *
 *      if the call succeeds, toks points to a null terminated array.
 *      for (int i = 0; toks[i]; i++) {
 *          // deserialize each element of the json array
 *          json_scanf(toks[i].start, toks[i].size, "...", ...);
 *      }
 *
 */
int
json_scanf(char *buffer, size_t buf_size, char *format, ...)
{
  size_t num_keys = 0;
  int extracted_values = 0;
  struct extractor_specifier *es = format_parse(format, &num_keys);
  if (NULL == es) return 0;

  struct extractor_specifier * capture_existance = NULL;

  va_list ap;
  va_start(ap, format);
  for (size_t i = 0; i < num_keys ; ++i) {
    if (es[i].has_dynamic_size)  {
      es[i].size = va_arg(ap, int); // use this as a size
    }
    else if (es[i].is_funptr) {
      es[i].funptr = va_arg(ap, extractor*);
    }
    void *p_value = va_arg(ap, void*);
    ASSERT_S(NULL != p_value, "NULL pointer given as argument parameter");
    es[i].recipient = p_value;

    if (STREQ(es[i].type_specifier, "exist")) {
      capture_existance = &es[i];
    }
  }
  va_end(ap);

  // debugging print out es

  //calculate how many tokens are needed
  jsmn_parser parser;
  jsmn_init(&parser);
  jsmntok_t * tok = NULL;
  int num_tok = jsmn_parse(&parser, buffer, buf_size, NULL, 0);
  DS_PRINT("# of tokens = %d", num_tok);
  if (num_tok < 0) {
    ERR("Failed to parse JSON: %.*s", (int)buf_size, buffer);
  }

  tok = malloc(sizeof(jsmntok_t) * num_tok);

  jsmn_init(&parser);
  num_tok = jsmn_parse(&parser, buffer, buf_size, tok, num_tok);

  /* Assume the top-level element is an object */
  if (num_tok < 1 || !(tok[0].type == JSMN_OBJECT || tok[0].type == JSMN_ARRAY)) {
    ERR("Object or array expected");
  }

  for (int i = 0; i < num_tok; i++) {
    DS_PRINT("[%d][p:%d][size:%d]%s (%.*s)\n", i, tok[i].parent,
             tok[i].size, print_token(tok[i].type),
             (int)(tok[i].end - tok[i].start), buffer + tok[i].start);
  }

  for (size_t i = 0; i < num_keys; ++i) {
    if (es+i == capture_existance) // it should be applied after all others
      continue;

    switch (tok[0].type) {
      case JSMN_OBJECT:
        apply_object(buffer, tok, num_tok, es + i);
        break;
      case JSMN_ARRAY:
        apply_array(buffer, tok, num_tok, es+i);
        break;
      default:
        ERR("Unexpected toplevel token %s\n", print_token(tok[0].type));
        goto cleanup;
    }

    if (es[i].is_applied) extracted_values ++;
  }

  if (capture_existance) {
    void ** has_values = NULL;
    if (capture_existance->allocate_memory)
      has_values = ntl_calloc(extracted_values, sizeof(void *));
    else
      has_values = (void **) capture_existance->recipient;

    for (size_t i = 0, j = 0; i < num_keys; i++) {
      if (es+i == capture_existance) continue;

      if (es[i].is_applied) {
        has_values[j] = es[i].recipient;
        j++;
      }
    }
    if (capture_existance->allocate_memory)
      *(void **)capture_existance->recipient = (void *) has_values;
  }

cleanup:
  if (tok) free(tok);
  free(es);

  return extracted_values;
}
