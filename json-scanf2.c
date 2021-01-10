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

#include "jscon-common.h"
#include "debug.h"

#define JSMN_PARENT_LINKS
#define JSMN_STRICT
#include "jsmn.h"

#define KEY_MAX 256

struct path_specifier {
  enum {
    KEY,
    INDEX,
  } type;
  union {
    char key[KEY_MAX];
    int index;
  } path;
  struct path_specifier * next;
};

struct extractor_specifier {
  struct path_specifier path_specifier;
  char type_specifier[10];
  size_t size;
  void *recipient; /* must be a pointer */
  bool is_applied;
};


static int
jsoneq(const char *json, jsmntok_t *tok, const char *s)
{
  if (tok->type == JSMN_STRING
      && (int)strlen(s) == tok->end - tok->start
      && STRNEQ(json + tok->start, s, tok->end - tok->start))
  {
    return 0;
  }
  return -1;
}

static void
match_path (char *buffer,
            jsmntok_t *t, size_t n_toks, int start_tok,
            struct extractor_specifier *es,
            struct path_specifier *path)
{
  char *end = 0;
  int i = start_tok;
  if (path) {
    match_path(buffer, t, n_toks, i, es, path);
    return;
  }

  es->is_applied = true;
  if (STREQ(es->type_specifier, "char*")){
    if (es->size) {
        strscpy((char *)es->recipient, buffer + t[i].start, es->size + 1);
    }
    else {
        strscpy((char *)es->recipient, buffer + t[i].start, 
            t[i].end - t[i].start + 1);
    }
  }
  else if (STREQ(es->type_specifier, "bool*")) {
    if (0 == jsoneq(buffer, &t[i], "true")) {
        *(bool *)es->recipient = true;
    }
    else if (0 == jsoneq(buffer, &t[i], "false")){
        *(bool *)es->recipient = false;
    }
    else {
        goto type_error;
    }
  }
  else if (STREQ(es->type_specifier, "int*")) {
      *(int *)es->recipient = (int)strtol(buffer + t[i].start, &end, 10);
      if (end != buffer + t[i].end) goto type_error;
  }
  else if (STREQ(es->type_specifier, "long*")) {
      *(long *)es->recipient = strtol(buffer + t[i].start, &end, 10);
      if (end != buffer + t[i].end) goto type_error;
  }
  else if (STREQ(es->type_specifier, "long long*")) {
      *(long long *)es->recipient = strtoll(buffer + t[i].start, &end, 10);
      if (end != buffer + t[i].end) goto type_error;
  }
  else if (STREQ(es->type_specifier, "float*")) {
      *(float *)es->recipient = strtof(buffer + t[i].start, &end);
      if (end != buffer + t[i].end) goto type_error;
  }
  else if (STREQ(es->type_specifier, "double*")) {
      *(double *)es->recipient = strtod(buffer + t[i].start, &end);
      if (end != buffer + t[i].end) goto type_error;
  }
  else {
      goto type_error;
  }

  return;

type_error:
  ERROR("Expected specifier %s but found: '%.*s' )\n", es->type_specifier, t[i].end - t[i].start, buffer + t[i].start);
  // report errors;
  return;
}

static void
apply(char *test_string, jsmntok_t *tok, size_t n_toks, struct extractor_specifier *es)
{
  size_t ik = 1, iv = 2;
  do {
    // tok[ik] must be a toplevel key, and t[iv] must be its value
    ASSERT_S(tok[ik].type == JSMN_STRING, "Not a key"); // make sure it's a key
    ASSERT_S(tok[ik].parent == 0, "Token is not at top level"); // make sure it's at the toplevel

    if (0 == jsoneq(test_string, &tok[ik], es->path_specifier.path.key)) {
      match_path(test_string, tok, n_toks, iv, es, es->path_specifier.next);
      break;
    }
    
    // skip all children toks of t[i_1]
    ik = iv + 1;
    if (ik >= n_toks) {
      break; // we are done
    }

    // find the next toplevel key

    for (ik = iv + 1; tok[ik].end < tok[iv].end; ik++)
        continue;

    iv = ik + 1;
  } while (ik < n_toks && iv < n_toks);
}


static char*
parse_type_specifier(char *specifier, struct extractor_specifier *  p)
{
  char *start = specifier, * end;
  long size = strtol(start, &end, 10);

  bool is_valid_size = false;
  if (end != start) {
    is_valid_size = true;
    specifier = end;
  }

  if (STRNEQ(specifier, "s", 1) || STRNEQ(specifier, "S", 1)){
    strcpy(p->type_specifier, "char*");

    p->size = (is_valid_size) ? size : 0;

    return specifier + 1;
  }
  if (STRNEQ(specifier, "d", 1)) {
    p->size = sizeof(int);
    strcpy(p->type_specifier, "int*");
    return specifier + 1;
  }
  if (STRNEQ(specifier, "ld", 2)) {
    p->size = sizeof(long);
    strcpy(p->type_specifier, "long*");
    return specifier + 2;
  }
  if (STRNEQ(specifier, "lld", 3)) {
    p->size = sizeof(long long);
    strcpy(p->type_specifier, "long long*");
    return specifier + 3;
  }
  if (STRNEQ(specifier, "f", 1)) {
    p->size = sizeof(float);
    strcpy(p->type_specifier, "float*");
    return specifier + 1;
  }
  if (STRNEQ(specifier, "lf", 2)) {
    p->size = sizeof(double);
    strcpy(p->type_specifier, "double*");
    return specifier + 2;
  }
  if (STRNEQ(specifier, "b", 1)){
    p->size = sizeof(bool);
    strcpy(p->type_specifier, "bool*");
    return specifier + 1;
  }

  return 0;
}

/*
 * legit inputs:
 *      abc]
 *      ]
 *      10]
 *
 * illegit inputs:
 *      abc
 *      10
 */
static char*
parse_path_specifier(char * format, struct extractor_specifier *es, struct path_specifier *curr_path)
{
  //@todo does this accounts for objects with numerical keys?
  
  char *start = format;
  bool is_index = true;

  do {
    if (!isdigit(*format)) {
      is_index = false;
    }
    format++;
  } while (*format && *format != ']' && *format != '%');

  size_t len = format - start; 
  ASSERT_S(len < KEY_MAX, "Key is too long (Buffer Overflow)");
  ASSERT_S(0 != len, "Key has invalid size 0");

  if (is_index) { // array indexing
    char *end;
    long l_num = strtol(start, &end, 10);
    ASSERT_S(end == format, "Invalid characters in the numerical string");

    curr_path->path.index = l_num;
    curr_path->type = INDEX;
  }
  else { // key indexing
    strscpy(curr_path->path.key, start, len + 1);
    curr_path->type = KEY;
  }

  ++format; // eat up ']'
  if (*format == '[') {
    ++format; // eat up '['
    struct path_specifier *next_path = calloc(1, sizeof(*next_path));
    curr_path->next = next_path;
    return parse_path_specifier(format, es, next_path);
  }
  else if (*format == '%'){
    ++format;
    return parse_type_specifier(format, es);
  }

  return NULL;
}

/* count amount of keys and check for formatting errors */
static void
format_analyze(char *format, size_t *num_keys)
{
  bool is_open = false;
  while (*format) /* run until end of string found */
  {
    // search for open bracket
    while (*format) {
      if ('[' == *format) {
        ++format;
        is_open = true;
        break;
      }
      ++format;
    }
    ASSERT_S(is_open && *format, "Missing '[' token in format string");

    // search for close bracket
    while (*format) {
      if (']' == *format) {
        is_open = false;
        if (*++format != '[') {
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
    while (*format) {
      if ('%' == *format){
        do {
          // skip type specifier
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
  struct extractor_specifier *nes = calloc(n, sizeof(*nes));

  SKIP_SPACES(format);

  size_t i = 0;
  while (*format) 
  {
    if (*format == '[') {
      ++format; //eat up '['
      format = parse_path_specifier(format, nes+i, &nes[i].path_specifier);
    }
    else {
      free(nes);
      return NULL;
    }

    i++;
  }

  return nes;
}

static struct extractor_specifier*
format_parse(char *format, size_t *n)
{
  format_analyze(format, n);

  return parse_extractor_specifiers(format, *n);
}

/*
 *  format grammar:
 *      ([key1]|[]|[<n>])+%(d|ld|lld|f|lf|b|<n>s|<n>S)
 *
 *      n is an integer
 *
 *  usage:
 *      json_scanf2(str, "[k1][k2]%d", &i);
 *
 */
int
json_scanf2(char *buffer, char *format, ...)
{
  va_list ap;
  size_t num_keys = 0;

  struct extractor_specifier *nes;
  nes = format_parse(format, &num_keys);

  if (NULL == nes) return 0;

  va_start(ap, format);
  for (size_t i = 0; i < num_keys ; ++i) {
    void *p_value = va_arg(ap, void*);;
    ASSERT_S(NULL != p_value, "NULL pointer given as argument parameter");

    nes[i].recipient = p_value;
  }
  va_end(ap);

  jsmn_parser parser;
  jsmn_init(&parser);

  //calculate how many tokens are needed
  int ret = jsmn_parse(&parser, buffer, strlen(buffer), NULL, 0);

  D_PRINT("Necessary tokens = %d", ret);
  jsmntok_t *tok = malloc(sizeof(jsmntok_t) * ret);
  jsmn_init(&parser);
  ret = jsmn_parse(&parser, buffer, strlen(buffer), tok, ret);

  if (ret < 0) {
    D_PRINT("Failed to parse JSON: %d", ret);
    goto cleanup;
  }

  /* Assume the top-level element is an object */
  if (ret < 1 || tok[0].type != JSMN_OBJECT) {
    D_PRINT("Object expected");
    goto cleanup;
  }

  for (size_t i = 0; i < num_keys; ++i) {
    apply(buffer, tok, ret, nes+i);
  }

cleanup:
  free(tok);
  free(nes);

  return 0;
}
