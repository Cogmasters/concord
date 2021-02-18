#include "json-actor.c"
#include <string.h>

static struct stack stack = { .array = {0}, .top = 0, .actor = INJECTOR };

int main ()
{
  struct value value;
  char * next_pos;
  parse_value(&stack, "d", strlen("d"), &value, &next_pos);

  char * t = "(k):d";
  struct access_path_value kv;
  memset(&kv, 0, sizeof (struct access_path_value));
  parse_access_path_value(&stack, t, strlen(t), &kv, &kv.path);

  print_access_path_value(stderr, &kv);

  t = "\" aaaaaa\t \"";
  char * p = NULL;
  enum value_type type;
  if (is_primitive(&stack, t, strlen(t), &p, &type)) {
    fprintf (stderr, "is primitive\n");
  }
  t = "(k):| aaaa\r\naa\t |";
  parse_access_path_value(&stack, t, strlen(t), &kv, &kv.path);
  print_access_path_value(stderr, &kv);

  struct composite_value cv;
  memset(&cv, 0, sizeof(struct composite_value));
  t = "{ (k) : d, (n): 102,  (f): 102.30, }";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);

  memset(&cv, 0, sizeof(struct composite_value));
  t = "{ (k)(j):d  (k)(j)(1):s }";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);

  memset(&cv, 0, sizeof(struct composite_value));
  t = "{ (k)(j): { (a) : d } }";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);

  memset(&cv, 0, sizeof(struct composite_value));
  t = "[ d, f, lf,  lld, .*s, ?s, ]";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);


  memset(&cv, 0, sizeof(struct composite_value));
  t = "[ F 1 0.1 ]";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);

  memset(&cv, 0, sizeof(struct composite_value));
  t = "[ # ]";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);

  memset(&cv, 0, sizeof(struct composite_value));
  t = "[ true, false, true ]";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);


  memset(&cv, 0, sizeof(struct composite_value));
  t = "[ true false true null ] .@";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);


  memset(&cv, 0, sizeof(struct composite_value));
  t = "{ (k1):d (k2):true (k3):f  (k4):F (k5):L } .@";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);


  struct operand_addrs rec;
  memset(&cv, 0, sizeof(struct composite_value));
  memset(&rec, 0, sizeof(struct operand_addrs));

  t = "{ (k1):d,  (k2):true, (k3):f, (k4):F, (k5):[L], (k6):T, (k7):{ (k8):T }, (k9):null, } .@";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);
  get_composite_value_operand_addrs(&cv, &rec);
  for (size_t i = 0; i < rec.pos; i++)
    fprintf (stderr, "%p ", rec.addrs[i]);

  memset(&cv, 0, sizeof(struct composite_value));
  t = "{ }";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);

  memset(&cv, 0, sizeof(struct composite_value));
  t = "[ ]";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);


  memset(&cv, 0, sizeof(struct composite_value));
  t = "[ F_nullable ] @";
  parse_composite_value(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);


  memset(&cv, 0, sizeof(struct composite_value));
  t = " (k): F_nullable, (v): d, (h): f, @";
  parse_actor(&stack, t, strlen(t), &cv);
  fprintf (stderr, "\n");
  print_composite_value(stderr, &cv);


  t = " (k):d (v):d ";
  parse_query_string(&stack, t, strlen(t), &cv._.pairs);
  return 0;
}
