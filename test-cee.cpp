#include "tester.h"
#include "settings.h"

using namespace tester::user_agent;

void load(void * ptr, char * str, size_t len) {
  fprintf(stderr, "%.*s", len, str);
}


int commit (char * base_url)
{
  data data = {0};
  curl_global_init(CURL_GLOBAL_ALL);
  init (&data, base_url);
  struct api_resbody_s  body = { 0, 0 };
  body.str = "{ }";
  body.size = strlen(body.str);

  struct resp_handle handle = { .cb = load, .obj = NULL };


  run(&data, &handle, &body, POST, "/echo?m=POST");
  run(&data, &handle, &body, PATCH, "/echo?m=PATCH");
  run(&data, &handle, &body, GET, "/echo?m=GET");
  run(&data, &handle, &body, PUT, "/echo?m=PUT");
  run(&data, &handle, &body, DELETE, "/echo?m=DELETE");

  curl_global_cleanup();
  return 0;
}

int main (int argc, char ** argv)
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  struct bot_settings settings;
  bot_settings_init (&settings, config_file);

  commit("https://cee.studio");
  return 0;
}