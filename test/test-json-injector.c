#include "json-actor.c"
#include <string.h>

int main () {
  char * pos;
  pos = json_injector("[ true false true]");
  fprintf(stderr, "%s\n", pos);
  free(pos);

  pos = json_injector("[ null 1]");
  fprintf(stderr, "%s\n", pos);
  free(pos);

  pos = json_injector("[ null \"abc\"]");
  fprintf(stderr, "%s\n", pos);
  free(pos);

  pos = json_injector("{ [k]:null [b]:\"abc\"}");
  fprintf(stderr, "%s\n", pos);
  free(pos);


  pos = json_injector("{ [k]:null [x]:\"abc\"}");
  fprintf(stderr, "%s\n", pos);
  free(pos);
}
