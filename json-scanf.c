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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "json-scanf.h"
#include "json-common.h"

#define JSMN_PARENT_LINKS
#define JSMN_STRICT
#include "jsmn.h"

#define N_PATH_MAX 8
#define KEY_MAX 128

struct path_specifier {
  char key[KEY_MAX];
  struct path_specifier *next;
};

struct extractor_specifier {
  struct path_specifier path_specifiers[N_PATH_MAX];
  char type_specifier[10];
  size_t size;
  void *recipient; //must be a pointer
  bool is_applied;
  bool has_dynamic_size;
  bool has_unknown_size;
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
    default:              ERROR("Unknown JSMN_XXXX type encountered (code: %d)", type);
  }
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

static void
match_path (char *buffer, jsmntok_t *t,
            size_t n_toks, int start_tok,
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
        ASSERT_S(*end == 0, "Index is not a number");
        ASSERT_S(index >= 0, "Index is not zero or positive");
        ASSERT_S(index < t[i].size, "Index is out-of-bound");

        ic = i + 1; // the first child of i;
        match_path(buffer, t, n_toks, ic + index, es, ps->next);

        break;
     }
    default:
        ERROR("Patch match error (not an Object or Array)");
    }

    return;
  }

  es->is_applied = true;
  if (STREQ(es->type_specifier, "char*")){
      switch (t[i].type) {
      case JSMN_STRING:
          if (es->has_unknown_size) {
            char ** p = (char **) es->recipient;
            size_t len = t[i].end - t[i].start + 1;
            *p = malloc(len);
            int ret = snprintf(*p, len, "%.*s", len - 1, buffer+t[i].start);
            ASSERT_S((size_t) ret < len, "out-of-bounds write");
          }
          else if (es->size) {
            int ret = snprintf((char *) es->recipient, es->size,
                               "%.*s", t[i].end - t[i].start,
                               buffer+t[i].start);
            ASSERT_S((size_t)ret < es->size, "out-of-bounds write");
          }
          else {
            // we have to allow this potential oob write as
            // we don't know the buffer size of recipient.
            sprintf((char *) es->recipient, "%.*s",
                    t[i].end - t[i].start,
                    buffer + t[i].start);
          }
          break;
      case JSMN_PRIMITIVE:
          //something is wrong if is not null primitive
          if (!STRNEQ(buffer + t[i].start, "null", 4))
              goto type_error;

          *(char *)es->recipient = '\0'; //@todo we need a better way to represent null

          break;
      default:
        goto type_error;
      }
  }
  else if (STREQ(es->type_specifier, "copy")) {
    if (es->has_unknown_size) {
      char ** p = (char **) es->recipient;
      size_t len = t[i].end - t[i].start + 1;
      *p = malloc(len);
      int ret = snprintf(*p, len, "%.*s", len - 1, buffer+t[i].start);
      ASSERT_S((size_t) ret < len, "out-of-bounds write");
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
  else if (STREQ(es->type_specifier, "token")) {
    struct json_token * tk = es->recipient;
    tk->start = buffer + t[i].start;
    tk->length = t[i].end - t[i].start;
  }
  else if (STREQ(es->type_specifier, "bool*")) {
    ASSERT_S(t[i].type == JSMN_PRIMITIVE, "Not a primitive");
    switch (buffer[t[i].start]) {
      case 't': *(bool *)es->recipient = true; break;
      case 'f': *(bool *)es->recipient = false; break;
      default: goto type_error; 
    }
  }
  else if (STREQ(es->type_specifier, "int*")) {
    ASSERT_S(t[i].type == JSMN_PRIMITIVE, "Not a primitive");
    switch(buffer[t[i].start]) {
      case 'n': *(int *) es->recipient = 0; break;
      default:
        *(int *) es->recipient = (int) strtol(buffer + t[i].start, &end, 10);
        if (end != buffer + t[i].end) goto type_error;
        break;
    }
  }
  else if (STREQ(es->type_specifier, "long*")) {
    ASSERT_S(t[i].type == JSMN_PRIMITIVE, "Not a primitive");
    switch(buffer[t[i].start]) {
      case 'n': *(long *) es->recipient = 0; break;
      default:
        *(long *) es->recipient = strtol(buffer + t[i].start, &end, 10);
        if (end != buffer + t[i].end) goto type_error;
        break;
    }
  }
  else if (STREQ(es->type_specifier, "long long*")) {
    ASSERT_S(t[i].type == JSMN_PRIMITIVE, "Not a primitive");
    switch(buffer[t[i].start]) {
      case 'n': *(long long *) es->recipient = 0; break;
      default:
        *(long long *) es->recipient = strtoll(buffer + t[i].start, &end, 10);
        if (end != buffer + t[i].end) goto type_error;
        break;
    }
  }
  else if (STREQ(es->type_specifier, "float*")) {
    ASSERT_S(t[i].type == JSMN_PRIMITIVE, "Not a primitive");
    switch(buffer[t[i].start]) {
      case 'n': *(float *) es->recipient = 0; break;
      default:
        *(float *) es->recipient = strtof(buffer + t[i].start, &end);
        if (end != buffer + t[i].end) goto type_error;
        break;
    }
  }
  else if (STREQ(es->type_specifier, "double*")) {
    ASSERT_S(t[i].type == JSMN_PRIMITIVE, "Not a primitive");
    switch(buffer[t[i].start]) {
      case 'n': *(double *) es->recipient = 0; break;
      default:
        *(double *) es->recipient = strtod(buffer + t[i].start, &end);
        if (end != buffer + t[i].end) goto type_error;
        break;
    }
  }
  else {
      goto type_error;
  }

  return;

type_error:
  ERROR("Expected specifier %s but found: '%.*s' )\n", es->type_specifier,
        t[i].end - t[i].start, buffer + t[i].start);
  // report errors;
  return;
}

static void
apply(char *str, jsmntok_t *tok, size_t n_toks, struct extractor_specifier *es)
{
  size_t ik = 1, iv = 2;
  do {
    // tok[ik] must be a toplevel key, and tok[iv] must be its value
    if (tok[ik].type != JSMN_STRING) {
      D_PRINT("[%ld][p:%d][size:%d]%s (%.*s)\n", ik, tok[ik].parent,
              tok[ik].size, print_token(tok[ik].type),
              tok[ik].end - tok[ik].start, str + tok[ik].start);
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

  bool is_valid_size = false, has_dsize = false, has_unknown_size = false;
  if (end != start) {
    is_valid_size = true;
    specifier = end; // jump to the end of number
  }
  else if ('.' == *specifier && '*' == *(specifier+1)) {
    has_dsize = true;
    specifier += 2; // eat up '.' and '*'
  }
  else if ('?' == *specifier) {
    has_unknown_size = true;
    specifier ++;
  }

  if (STRNEQ(specifier, "s", 1)){
    es->size = (is_valid_size) ? size : 0;
    es->has_dynamic_size = has_dsize;
    es->has_unknown_size = has_unknown_size;
    strcpy(es->type_specifier, "char*");
    return specifier + 1;
  }
  else if (STRNEQ(specifier, "S", 1)) {
    es->size = (is_valid_size) ? size : 0;
    es->has_dynamic_size = has_dsize;
    es->has_unknown_size = has_unknown_size;
    strcpy(es->type_specifier, "copy");
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
  ASSERT_S(len > 0, "Key is missing");

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
      ++format; // eat up '%'

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
  while (*format) /* run until end of string found */
  {
    // search for open bracket
    while (*format)
    {
      if ('[' == *format) {
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
      if ('%' == *format){
        do { // skip type specifier
          ++format;
        } while (*format && *format != '[');
        break;
      }
      ++format;
    }
    ++*num_keys;
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
    if ('[' == *format) {
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

  return parse_extractor_specifiers(format, *n);
}

/*
 *
 *  format grammar:
 *      ([key1]|[<n>])+%(d|ld|lld|f|lf|b|<n>s|<n>S|.*s|.*S|?s|?S|T) <space>
 *
 *      n is an integer
 *
 *  usage:
 *
 *      json_scanf(buf_start, buf_size, "[k1][k2]%d  [k2][1]%s", &i, str);
 *      %d, %f, %lf, %s, %.*s have the same effects as if they are used in scanf
 *
 *      %T captures the start position and length of any JSON value within
 *      the buf range (buf_start, buf_start + buf_size]
 *
 *      %S clones any JSON value as a string
 *
 *      %<n>s %<n>S: length modifier can be applied to %s to limit how many bytes
 *      can be copied to the receiving parameter.
 *
 *      %.*s %.*S:
 *
 *      %?s %?S:
 *
 */
int
json_scanf(char *buffer, size_t buf_size, char *format, ...)
{
  size_t num_keys = 0, i;
  struct extractor_specifier *es = format_parse(format, &num_keys);
  if (NULL == es) return 0;

  va_list ap;
  va_start(ap, format);

  for (i = 0; i < num_keys ; ++i) {
    if (es[i].has_dynamic_size)  {
      es[i].size = va_arg(ap, int); // use this as a size
    }
    void *p_value = va_arg(ap, void*);
    ASSERT_S(NULL != p_value, "NULL pointer given as argument parameter");
    es[i].recipient = p_value;
  }

  va_end(ap);

  // debugging print out es

  //calculate how many tokens are needed
  jsmn_parser parser;
  jsmn_init(&parser);
  int num_tok = jsmn_parse(&parser, buffer, buf_size, NULL, 0);
  D_PRINT("# of tokens = %d", num_tok);

  jsmntok_t *tok = malloc(sizeof(jsmntok_t) * num_tok);

  jsmn_init(&parser);
  num_tok = jsmn_parse(&parser, buffer, buf_size, tok, num_tok);

  if (num_tok < 0) {
    D_PRINT("Failed to parse JSON: %d", num_tok);
    goto cleanup;
  }

  /* Assume the top-level element is an object */
  if (num_tok < 1 || tok[0].type != JSMN_OBJECT) {
    D_PRINT("Object expected");
    goto cleanup;
  }

  for (i = 0; i < num_tok; i++) {
    D_PRINT("[%d][p:%d][size:%d]%s (%.*s)\n", i, tok[i].parent,
           tok[i].size, print_token(tok[i].type),
           tok[i].end - tok[i].start, buffer + tok[i].start);
  }

  for (i = 0; i < num_keys; ++i) {
    apply(buffer, tok, num_tok, es+i);
  }

cleanup:
  free(tok);
  free(es);

  return 0;
}

char*
__json_strerror(json_errcode code, char codetag[], void *where, char entity[])
{
  char err_is[128];
  switch (code){
  case JSON_EXT__OUT_MEM:
      snprintf(err_is, sizeof(err_is)-1, "Out of Memory");
      break;
  case JSON_EXT__INVALID_TOKEN:
      snprintf(err_is, sizeof(err_is)-1, "Invalid Token: '%c'", *((char*)where));
      break;
  case JSON_EXT__INVALID_STRING:
      snprintf(err_is, sizeof(err_is)-1, "Missing string token: ' \" '");
      break;
  case JSON_EXT__INVALID_BOOLEAN:
      snprintf(err_is, sizeof(err_is)-1, "Missing boolean token: 't' or 'f'");
      break;
  case JSON_EXT__INVALID_NUMBER:
      snprintf(err_is, sizeof(err_is)-1, "Missing number tokens: '+-.0-9e'");
      break;
  case JSON_EXT__INVALID_COMPOSITE:
      snprintf(err_is, sizeof(err_is)-1, "Missing Object or Array tokens: '{}[]'");
      break;
  case JSON_EXT__NOT_STRING:
      snprintf(err_is, sizeof(err_is)-1, "Item is not a string");
      break;
  case JSON_EXT__NOT_BOOLEAN:
      snprintf(err_is, sizeof(err_is)-1, "Item is not a boolean");
      break;
  case JSON_EXT__NOT_NUMBER:
      snprintf(err_is, sizeof(err_is)-1, "Item is not a number");
      break;
  case JSON_EXT__NOT_COMPOSITE:
      snprintf(err_is, sizeof(err_is)-1, "Item is not a Object or Array");
      break;
  case JSON_EXT__EMPTY_FIELD:
      snprintf(err_is, sizeof(err_is)-1, "Field is missing");
      break;
  case JSON_INT__NOT_FREED:
      snprintf(err_is, sizeof(err_is)-1, "JSON couldn't free memory");
      break;
  case JSON_INT__OVERFLOW:
      snprintf(err_is, sizeof(err_is)-1, "JSON tried to access forbidden memory (Overflow)");
      break;
  default:
      snprintf(err_is, sizeof(err_is)-1, "Unknown Error");
      break;
  }

  char errbuf[512];
  errbuf[511] = 0; // pre-terminate the string
  snprintf(errbuf, sizeof(errbuf)-1, "%s (Code: %d)\n\t%s\n\tAt '%s' (addr: %p)",
           codetag, code, err_is, entity, where);

  char *errdynm = strdup(errbuf);
  if (NULL == errdynm)
    ERROR("%s", errbuf);

  return  errdynm;
}
