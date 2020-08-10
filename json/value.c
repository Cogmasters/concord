#ifndef ORCA_JSON_AMALGAMATION
#include "json.h"
#include <stdlib.h>
#include "cee.h"
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

struct json * json_true () {
  static char b[CEE_SINGLETON_SIZE];
  return (struct json *) cee_singleton_init ((uintptr_t)is_boolean, b);
}

struct json * json_false () {
  static char b[CEE_SINGLETON_SIZE];
  return (struct json *) cee_singleton_init ((uintptr_t)is_boolean, b);
}

struct json * json_bool(bool b) {
  if (b)
    return json_true();
  else
    return json_false();
}


struct json * json_undefined () {
  static char b[CEE_SINGLETON_SIZE];
  return (struct json *)cee_singleton_init ((uintptr_t)is_undefined, b);
}

struct json * json_null () {
  static char b[CEE_SINGLETON_SIZE];
  return (struct json *)cee_singleton_init ((uintptr_t)is_null, b);
}

struct cee_map * json_to_object (struct json * p) {
  if (p->t == is_object) {
    return p->value.object;
  }
  return NULL;
}
struct cee_vect * json_to_array (struct json * p) {
  if (p->t == is_array) {
    return p->value.array;
  }
  return NULL;
}

struct cee_str * json_to_string (struct json * p) {
  if (p->t == is_string) {
    return p->value.string;
  }
  return NULL;
}

struct cee_box * json_to_number (struct json * p) {
  if (p->t  == is_number) {
    return p->value.number;
  }
  return NULL;
}

bool json_to_bool (struct json * p) {
  if (p == json_true())
    return true;
  else if (p == json_false())
    return false;
  
  cee_segfault();
  return false;
}

struct json * json_number (double d) {
  struct cee_box *p = cee_box_double (d);
  struct cee_tagged * t = cee_tag (is_number, p);
  return (struct json *)t;
}

struct json * json_string(struct cee_str *s) {
  struct cee_tagged * t = cee_tag(is_string, s);
  return (struct json *)t;
}

struct json * json_array(int s) {
  struct cee_vect * v = cee_vect (s);
  struct cee_tagged * t = cee_tag(is_array, v);
  return (struct json *)t;
}

struct json * json_object() {
  struct cee_map * m = cee_map ((cee_cmp_fun)strcmp);
  struct cee_tagged * t = cee_tag(is_object, m);
  return (struct json *)t;
}

void json_object_set(struct json * j, char * key, struct json * v) {
  struct cee_map * o = json_to_object(j);
  if (!o) 
    cee_segfault();
  cee_map_add(o, cee_str("%s", key), v);
}

void json_object_set_bool(struct json * j, char * key, bool b) {
  struct cee_map * o = json_to_object(j);
  if (!o) 
    cee_segfault();
  cee_map_add(o, cee_str("%s", key), json_bool(b));
}

void json_object_set_string (struct json * j, char * key, char * str) {
  struct cee_map * o = json_to_object(j);
  if (!o) 
    cee_segfault();
  cee_map_add(o, cee_str("%s", key), json_string(cee_str("%s", str)));
}

void json_object_set_number (struct json * j, char * key, double real) {
  struct cee_map * o = json_to_object(j);
  if (!o) 
    cee_segfault();
  cee_map_add(o, cee_str("%s", key), json_number(real));
}

void json_array_append (struct json * j, struct json *v) {
  struct cee_vect * o = json_to_array(j);
  if (!o) 
    cee_segfault();
  cee_vect_append(o, v);
}

void json_array_append_bool (struct json * j, bool b) {
  struct cee_vect * o = json_to_array(j);
  if (!o) 
    cee_segfault();
  cee_vect_append(o, json_bool(b));
}

void json_array_append_string (struct json * j, char * x) {
  struct cee_vect * o = json_to_array(j);
  if (!o) 
    cee_segfault();
  cee_vect_append(o, json_string(cee_str("%s", x)));
}

/*
 * this function assume the file pointer points to the begin of a file
 */
struct json * json_load_from_file (FILE * f, bool force_eof, 
                                   int * error_at_line) {
  int fd = fileno(f);
  struct stat buf;
  fstat(fd, &buf);
  off_t size = buf.st_size;
  char * b = malloc(size);
  if (!b) 
    cee_segfault();
  
  int line = 0;
  struct json * j;
  if (!json_parse(b, size, &j, true, &line)) {
    // report error
  }
  return j;
}

bool json_save(struct json * j, FILE *f, int how) {
  size_t s = json_snprintf(NULL, 0, j, how);
  char * p = malloc(s+1);
  json_snprintf(p, s+1, j, how);
  if (fwrite(p, s+1, 1, f) != 1) {
    fprintf(stderr, "%s", strerror(errno));
    return false;
  }
  return true;
}