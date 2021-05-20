#include <stdio.h>
#include <string.h>
#include "json-struct.c"
#include "json-scanf.h"

int main ()
{
  char *ns ="["
    "[\"A\", \"B\"],"
    "[\"A\", \"B\"],"
    "[\"1\", \"2\"]"
    "]";

  NTL_T(name_t) **namespaces = NULL;
  struct ntl_deserializer d0_alias = {
    .elem_size = sizeof(void*),
    .elem_from_buf = (vcpsvp)namespace_from_json,
    .init_elem = NULL,
    .ntl_recipient_p = (ntl_t *)&namespaces
  };
  extract_ntl_from_json(ns, strlen(ns), &d0_alias);
  fprintf(stderr, "%d\n", ntl_length((ntl_t)namespaces));
  fprintf(stderr, "%d\n", ntl_length((ntl_t)*(namespaces[0])));
}
