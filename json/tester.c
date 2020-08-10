#include "json.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmp (const void *v1, const void *v2) {
  printf ("%s, %s\n", (char *)v1, (char *)v2);
  return strcmp((char *)v1, (char *)v2);
}

int cmp1 (const void *v1, const void * v2) {
  struct cee_vect * vv1 = (struct cee_vect *) v1;
  struct cee_vect * vv2 = (struct cee_vect *) v2;
  //printf ("%s, %s\n", (char *)(vv1->e[0]), (char *)(vv2->e[0]));
  return strcmp((char *)(vv1->_[0]), (char *)(vv2->_[0]));
}

int main () {
  struct json * js = json_object ();
  
  json_object_set_bool(js, "b", true);
  json_object_set_bool(js, "b1", false);
  
  json_object_set_string(js, "s1", "xxx\n");
  struct json * js1 = json_object ();
  json_object_set_string(js1, "s2", "yyy");
  json_object_set(js, "y1", js1);
  
  struct json * js2 = json_array (10);
  json_array_append_string(js2, "false");
  json_array_append_string(js2, "true");
  json_object_set(js, "a1", js2);
  
  size_t jlen = json_snprintf(NULL, 0, js, 1);
  printf (" %u\n", jlen);
  jlen = json_snprintf(NULL, 0, js, 0);
  printf (" %u\n", jlen);
  
  char buf[1000];
  json_snprintf(buf, 109, js, 1);
  printf ("%s\n", buf);
  
  json_snprintf(buf, 109, js, 0);
  printf ("%s\n", buf);
  struct json * result = NULL;
  int line;
  printf ("pasing\n");
  json_parse(buf, jlen, &result, true, &line);
  printf ("end of parsing\n");
  
  json_snprintf(buf, 109, result, 0);
  printf ("parsed -> printed\n");
  printf ("%s\n", buf);
  cee_del(result);
  cee_del(js);
  return 0;
}
