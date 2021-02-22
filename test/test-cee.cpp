#include <stdio.h>
#include <string.h>

#include "orka-user-agent.hpp"
#include "orka-utils.h"

using namespace orka::user_agent;

void load(char * str, size_t len, void * ptr) {
  fprintf(stderr, "%.*s", (int)len, str);
}

int commit (char *base_url)
{
  dati data = {0};
  curl_global_init(CURL_GLOBAL_ALL);
  init(&data, base_url);
  struct sized_buffer body = {NULL, 0};
  body.start = "{ }";
  body.size = strlen(body.start);

  struct resp_handle handle = {.ok_cb = load, .ok_obj = NULL};

  run(&data, &handle, &body, NULL, HTTP_POST, "/echo?m=POST");
  run(&data, &handle, &body, NULL, HTTP_PATCH, "/echo?m=PATCH");
  run(&data, &handle, &body, NULL, HTTP_GET, "/echo?m=GET");
  run(&data, &handle, &body, NULL, HTTP_PUT, "/echo?m=PUT");
  run(&data, &handle, &body, NULL, HTTP_DELETE, "/echo?m=DELETE");

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

  struct orka_settings settings;
  orka_settings_init (&settings, config_file);

  commit("https://cee.studio");

  return 0;
}
