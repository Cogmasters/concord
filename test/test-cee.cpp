#include <stdio.h>
#include <string.h>

#include "user-agent.h"
#include "orka-utils.h"

void load(char * str, size_t len, void * ptr) {
  fprintf(stderr, "%.*s", (int)len, str);
}

int commit (char *base_url)
{
  struct user_agent_s data;
  ua_init(&data, base_url);

  curl_global_init(CURL_GLOBAL_ALL);
  struct sized_buffer body = {NULL, 0};
  body.start = "{ }";
  body.size = strlen(body.start);

  struct resp_handle handle = {.ok_cb = load, .ok_obj = NULL};

  ua_run(&data, &handle, &body, NULL, HTTP_POST, "/echo?m=POST");
  ua_run(&data, &handle, &body, NULL, HTTP_PATCH, "/echo?m=PATCH");
  ua_run(&data, &handle, &body, NULL, HTTP_GET, "/echo?m=GET");
  ua_run(&data, &handle, &body, NULL, HTTP_PUT, "/echo?m=PUT");
  ua_run(&data, &handle, &body, NULL, HTTP_DELETE, "/echo?m=DELETE");

  curl_global_cleanup();

  return 0;
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  struct orka_debug debug;
  orka_debug_init(&debug, "CEE HTTP", config_file);

  commit("https://cee.studio");

  return 0;
}
