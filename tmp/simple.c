#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * A small example of jsmn parsing when JSON structure is known and number of
 * tokens is predictable.
 */

static const char *test_string =
    "{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000,\n  "
    "\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

static char * print_token(jsmntype_t t) {
  switch(t) {
    case JSMN_UNDEFINED: return "undefined";
    case JSMN_OBJECT: return "object";
    case JSMN_ARRAY: return "array";
    case JSMN_STRING: return "string";
    case JSMN_PRIMITIVE: return "primitive";
  }
}

int main() {
  int i;
  int r;
  jsmn_parser p;
  jsmntok_t t[128]; /* We expect no more than 128 tokens */

  jsmn_init(&p);
  r = jsmn_parse(&p, test_string, strlen(test_string), t,
                 sizeof(t) / sizeof(t[0]));
  if (r < 0) {
    printf("Failed to parse JSON: %d\n", r);
    return 1;
  }

  /* Assume the top-level element is an object */
  if (r < 1 || t[0].type != JSMN_OBJECT) {
    printf("Object expected\n");
    return 1;
  }

  /* Loop over all keys of the root object */
  for (i = 1; i < r; i++) {
    if (jsoneq(test_string, &t[i], "user") == 0) {
      /* We may use strndup() to fetch string value */
      printf("- User: %.*s\n", t[i + 1].end - t[i + 1].start,
             test_string + t[i + 1].start);
      i++;
    } else if (jsoneq(test_string, &t[i], "admin") == 0) {
      /* We may additionally check if the value is either "true" or "false" */
      printf("- Admin: %.*s\n", t[i + 1].end - t[i + 1].start,
             test_string + t[i + 1].start);
      i++;
    } else if (jsoneq(test_string, &t[i], "uid") == 0) {
      /* We may want to do strtol() here to get numeric value */
      printf("- UID: %.*s\n", t[i + 1].end - t[i + 1].start,
             test_string + t[i + 1].start);
      i++;
    } else if (jsoneq(test_string, &t[i], "groups") == 0) {
      int j;
      printf("- Groups:\n");
      assert(t[i + 1].type == JSMN_ARRAY);
      for (j = 0; j < t[i + 1].size; j++) {
        jsmntok_t *g = &t[i + j + 2];
        printf("  * %.*s\n", g->end - g->start, test_string + g->start);
      }
      i += t[i + 1].size + 1;
    } else {
      printf("Unexpected key: %.*s\n", t[i].end - t[i].start,
             test_string + t[i].start);
    }
  }
  for (i = 0; i < r; i++) {
    printf("[%d]%s\n", i, print_token(t[i].type));
  }
  return EXIT_SUCCESS;
}
