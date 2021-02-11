#include "json-actor.c"
#include <string.h>

int main ()
{
  struct value value;
  char * next_pos;
  parse_value(&stack, "d", strlen("d"), &value, &next_pos);

  char * t = "[k]:d";
  struct apath_value kv;
  memset(&kv, 0, sizeof (struct apath_value));
  parse_apath_value(&stack, t, strlen(t), &kv, &kv.path);

  print_apath_value(&kv);

  t = "\" aaaaaa \"";
  char * p = NULL;
  if (is_primitive(t, strlen(t), &p)) {
    fprintf (stderr, "is primitive\n");
  }
  t = "[k]:\" aaaaaa \"";
  parse_apath_value(&stack, t, strlen(t), &kv, &kv.path);
  print_apath_value(&kv);

  struct complex_value cv;
  memset(&cv, 0, sizeof(struct complex_value));
  t = "{ [k] : d  [n]: 102  [f]: 102.30 }";
  parse_expr(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_complex_value(&cv);


  memset(&cv, 0, sizeof(struct complex_value));
  t = "{ [k][j] : d }";
  parse_expr(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_complex_value(&cv);

  memset(&cv, 0, sizeof(struct complex_value));
  t = "{ [k][j]: { [a] : d } }";
  parse_expr(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_complex_value(&cv);

  memset(&cv, 0, sizeof(struct complex_value));
  t = "[ d f lf  lld ]";
  parse_expr(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_complex_value(&cv);


  memset(&cv, 0, sizeof(struct complex_value));
  t = "[ F ]";
  parse_expr(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_complex_value(&cv);

  memset(&cv, 0, sizeof(struct complex_value));
  t = "[ L ]";
  parse_expr(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_complex_value(&cv);

  memset(&cv, 0, sizeof(struct complex_value));
  t = "[ true false true ]";
  parse_expr(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_complex_value(&cv);


  memset(&cv, 0, sizeof(struct complex_value));
  t = "[true false true null] .E";
  parse_expr(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_complex_value(&cv);


  memset(&cv, 0, sizeof(struct complex_value));
  t = "{ [k1]:d [k2]:true [k3]:f  [k4]:F [k5]:L } .E";
  parse_expr(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_complex_value(&cv);


  memset(&cv, 0, sizeof(struct complex_value));
  t = "{ [k1]:d  [k2]:true [k3]:f [k4]:F [k5]:[L] [k6]:T [k7]:{ [k8]:T } [k9]:null } .E";
  parse_expr(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_complex_value(&cv);

  return 0;
}

