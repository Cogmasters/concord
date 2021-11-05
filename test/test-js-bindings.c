#include <stdio.h>
#include <stdlib.h>

#include "user-agent.h"

#include "mujs.h"
#include "js_user-agent.h"

const char *handle = NULL; /* handle to stowed away js function */
const char *g_config_file;

void js_request(js_State *J)
{
  struct logconf config = { 0 };
  logconf_setup(&config, "JS_TEST", NULL);

  struct user_agent *ua = ua_init(&config);
  ua_set_url(ua, "http://www.example.com/");

  if (ORCA_OK == jsua_run(J, ua, NULL)) {
    printf("Request was a success!\n");
  }

  ua_cleanup(ua);
}

int main(void)
{
  log_set_quiet(true);

  js_State *J = js_newstate(NULL, NULL, JS_STRICT);
  jsua_init(J);

  /* TEST USER-AGENT BINDING */
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

  return EXIT_SUCCESS;
}
