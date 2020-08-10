#include "cee.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void foo (char * x) {
  struct cee_str * s = cee_str("logfile %s", x);
  printf("%p\n", s);
  printf("%s\n", (char *)s);
  cee_del(s);
  return;
}

int main () {
  /* test str */
  foo("hello world");
  struct cee_str * s, * s1, * s2;
  
  s = cee_str("the number ten: %d", 10);
  printf("%s\n", (char *)s);
  
  s1 = cee_str("the number ten point three: %.1f", 10.3);
  printf("%s\n", (char *)s1);
  
  s2 = cee_str("%s, %s", s, s1);
  printf("%s\n", s2->_);
  
  /* test vector */
  struct cee_vect *v, *v1, *v2;
  
  v = cee_vect(1);
  cee_use_realloc(v);
  
  v = cee_vect_append(v, s);
  v = cee_vect_append(v, s1);
  v = cee_vect_append(v, s2);
  
  printf("v.count %u\n", cee_vect_size(v));
  int i;
  for (i = 0; i < cee_vect_size(v); i++)
    printf ("%d:%s\n", i, (char *)v->_[i]);
  
  //cee_del(s);
  //cee_del(s1);
  //cee_del(s2);
  cee_del(v);
  
  /* test set */
  struct cee_set * st = NULL;
  st = cee_set((cee_cmp_fun)strcmp);
  
  printf ("st: %p\n", st);
  cee_set_add(st, cee_str("a"));
  cee_set_add(st, cee_str("aabc"));
  char * p = cee_set_find(st, "aabc");
  printf ("%s\n", p);
  
  struct cee_vect * svals = NULL;
  svals = cee_set_values(st);
  for (i = 0; i < cee_vect_size(svals); i++)
    printf ("%d %s\n", i, svals->_[i]);
  
  cee_del(st);
  cee_del(svals);
  
  /* test map */
  struct cee_map * mp = NULL;
  mp = cee_map((cee_cmp_fun)strcmp);
  
  cee_map_add(mp, cee_str("1"), cee_box_i32(10));
  cee_map_add(mp, cee_str("2"), cee_box_i32(20));
  cee_map_add(mp, cee_str("3"), cee_box_i32(30));
  
  struct cee_box * t = cee_map_find(mp, "1");
  printf ("found value %d\n", cee_box_as_i32(t));
  
  struct cee_vect * keys = cee_map_keys(mp);
  for (i = 0; i < cee_vect_size(keys); i++)
    printf ("[%d] key:%s\n", i, (char *)keys->_[i]);
  
  cee_del(keys);
  cee_del(mp);
  
  /* test stack */
  struct cee_stack * sp = cee_stack(100);
  cee_stack_push(sp, cee_str("1"));
  cee_stack_push(sp, cee_str("2"));
  cee_stack_push(sp, cee_str("3"));
  printf ("%s\n", cee_stack_top(sp, 0));
  cee_del(sp);
  
  /* test diction */
  struct cee_dict * dict = cee_dict(1000);
  
  for (i = 0; i < 1000; i++)
    cee_dict_add(dict, cee_str("%d", i)->_, cee_str("value %d", i));

  struct cee_str * key = cee_str("999");
  printf ("%s\n", cee_dict_find(dict, key->_));
  cee_del(key);
  cee_del(dict);
  
  struct cee_n_tuple * t5 = 
    cee_n_tuple(5, cee_str("1"), cee_str("2"), cee_str("3"), 
                cee_str("4"), cee_str("5"));
  
  for (i = 0; i < 5; i++)
    printf("%d, %s\n", i, t5->_[i]);
  
  cee_del(t5);
  return 0;
}