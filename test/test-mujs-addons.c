#include <stdio.h>
#include <stdlib.h>

#include "mujs.h"
#include "js-addons.h"

const char *handle=NULL; /* handle to stowed away js function */

void js_request(js_State *J)
{
  struct logconf config={};
  logconf_setup(&config, NULL);
  struct user_agent *ua = ua_init(&config);
  ua_set_url(ua, "http://www.example.com/");
  struct sized_buffer resp_body={};
  int nparam=0;
  js_ua_run(J, ua, &resp_body, &nparam);
  fprintf(stderr, "%.*s\n", (int)resp_body.size, resp_body.start);
  ua_cleanup(ua);
}

int main(void)
{
  js_State *J = js_newstate(NULL, NULL, JS_STRICT);
  js_newcfunction(J, &js_request, "request", 2);
  js_copy(J, 1);
  handle = js_ref(J);

  js_getregistry(J, handle);
  js_pushstring(J, "GET");
  js_pushstring(J, "index.html");
  if (js_pcall(J, 2)) {
    fprintf(stderr, "Error\n");
    return EXIT_FAILURE;
  }
  js_pop(J, 1);

  return EXIT_SUCCESS;
}
