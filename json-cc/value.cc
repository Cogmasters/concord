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

namespace cee {
  namespace json {

json::data * mk_true () {
  static char b[CEE_SINGLETON_SIZE];
  return (json::data *) singleton::init ((uintptr_t)type_is_boolean, b);
}

json::data * mk_false () {
  static char b[CEE_SINGLETON_SIZE];
  return (json::data *) singleton::init ((uintptr_t)type_is_boolean, b);
}

json::data * mk_bool(bool b) {
  if (b)
    return mk_true();
  else
    return mk_false();
}

json::data * mk_undefined () {
  static char b[CEE_SINGLETON_SIZE];
  return (json::data *) singleton::init ((uintptr_t)type_is_undefined, b);
}

json::data * mk_null () {
  static char b[CEE_SINGLETON_SIZE];
  return (json::data *) singleton::init ((uintptr_t)type_is_null, b);
}

map::data * to_object (json::data * p) {
  if (p->t == type_is_object) {
    return p->value.object;
  }
  return NULL;
}
    
vect::data * to_array (json::data * p) {
  if (p->t == type_is_array) {
    return p->value.array;
  }
  return NULL;
}

str::data * to_string (json::data * p) {
  if (p->t == type_is_string) {
    return p->value.string;
  }
  return NULL;
}

box::data * to_number (json::data * p) {
  if (p->t  == type_is_number) {
    return p->value.number;
  }
  return NULL;
}

bool to_bool (json::data * p) {
  if (p == mk_true())
    return true;
  else if (p == mk_false())
    return false;
  
  segfault();
  return false;
}

json::data * mk_number (double d) {
  box::data *p = box::from_double (d);
  tagged::data * t = tagged::mk (type_is_number, p);
  return (json::data *)t;
}

json::data * mk_string(str::data *s) {
  tagged::data * t = tagged::mk(type_is_string, s);
  return (json::data *)t;
}

json::data * mk_array(int s) {
  vect::data * v = vect::mk(s);
  tagged::data * t = tagged::mk(type_is_array, v);
  return (json::data *)t;
}
    
json::data * mk_object() {
  map::data * m = map::mk ((cmp_fun)strcmp);
  tagged::data * t = tagged::mk(type_is_object, m);
  return (json::data *)t;
}

void object_set(json::data * j, char * key, json::data * v) {
  map::data * o = to_object(j);
  if (!o) 
    segfault();
  map::add(o, str::mk("%s", key), v);
}

void object_set_bool(json::data * j, char * key, bool b) {
  map::data * o = to_object(j);
  if (!o) 
    segfault();
  map::add(o, str::mk("%s", key), mk_bool(b));
}

void object_set_string (json::data * j, char * key, char * str) {
  map::data * o = to_object(j);
  if (!o) 
    segfault();
  map::add(o, str::mk("%s", key), mk_string(str::mk("%s", str)));
}

void object_set_number (json::data * j, char * key, double real) {
  map::data * o = to_object(j);
  if (!o) 
    segfault();
  map::add(o, str::mk("%s", key), mk_number(real));
}

void array_append (json::data * j, json::data *v) {
  vect::data * o = to_array(j);
  if (!o) 
    segfault();
  vect::append(o, v);
}

void array_append_bool (json::data * j, bool b) {
  vect::data * o = to_array(j);
  if (!o) 
    segfault();
  vect::append(o, mk_bool(b));
}

void array_append_string (json::data * j, char * x) {
  vect::data * o = to_array(j);
  if (!o) 
    segfault();
  vect::append(o, mk_string(str::mk("%s", x)));
}

/*
 * this function assume the file pointer points to the begin of a file
 */
json::data * load_from_file (FILE * f, bool force_eof, int * error_at_line) {
  int fd = fileno(f);
  struct stat buf;
  fstat(fd, &buf);
  off_t size = buf.st_size;
  char * b = (char *)malloc(size);
  if (!b) 
    segfault();
  
  int line = 0;
  json::data * j;
  if (!parse(b, size, &j, true, &line)) {
    // report error
  }
  return j;
}

bool save(json::data * j, FILE *f, enum format how) {
  size_t s = json::snprint(NULL, 0, j, how);
  char * p = (char *)malloc(s+1);
  snprint(p, s+1, j, how);
  if (fwrite(p, s+1, 1, f) != 1) {
    fprintf(stderr, "%s", strerror(errno));
    return false;
  }
  return true;
}
    
  }
}