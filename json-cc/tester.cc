#include "json.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace cee;

int cmp (const void *v1, const void *v2) {
  printf ("%s, %s\n", (char *)v1, (char *)v2);
  return strcmp((char *)v1, (char *)v2);
}

int cmp1 (const void *v1, const void * v2) {
  vect::data * vv1 = (vect::data *) v1;
  vect::data * vv2 = (vect::data *) v2;
  //printf ("%s, %s\n", (char *)(vv1->e[0]), (char *)(vv2->e[0]));
  return strcmp((char *)(vv1->_[0]), (char *)(vv2->_[0]));
}

int main () {
  json::data * js = json::mk_object ();
  
  json::object_set_bool(js, "b", true);
  json::object_set_bool(js, "b1", false);
  
  json::object_set_string(js, "s1", "xxx\n");
  json::data * js1 = json::mk_object ();
  json::object_set_string(js1, "s2", "yyy");
  json::object_set(js, "y1", js1);
  
  json::data * js2 = json::mk_array (10);
  json::array_append_string(js2, "false");
  json::array_append_string(js2, "true");
  json::object_set(js, "a1", js2);
  
  size_t jlen = json::snprint(NULL, 0, js, json::readable);
  printf (" %u\n", jlen);
  jlen = json::snprint(NULL, 0, js, json::compact);
  printf (" %u\n", jlen);
  
  char buf[1000];
  json::snprint(buf, 109, js, json::readable);
  printf ("%s\n", buf);
  
  json::snprint(buf, 109, js, json::compact);
  printf ("%s\n", buf);
  json::data * result = NULL;
  int line;
  printf ("pasing\n");
  json::parse(buf, jlen, &result, true, &line);
  printf ("end of parsing\n");
  
  json::snprint(buf, 109, result, json::compact);
  printf ("parsed -> printed\n");
  printf ("%s\n", buf);
  
  del(result);
  del(js);
  return 0;
}
