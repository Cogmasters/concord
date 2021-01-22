#include "tester.h"
#include "settings.h"

using namespace tester::user_agent;

void load(void * ptr, char * str, size_t len) {
  json_scanf(str, len, "[object][sha]%?s", ptr);
}

void load_file_sha(void * ptr, char * str, size_t len) {
  json_scanf(str, len, "[sha]%?s", ptr);
}

int commit (char * base_url)
{
  data data = {0};
  curl_global_init(CURL_GLOBAL_ALL);
  init (&data, base_url);
  struct api_resbody_s  body = { 0, 0 };
  body.str = "{ }";
  body.size = strlen(body.str);


  run(&data, NULL, NULL, &body, POST, "/echo?m=POST");
  run(&data, NULL, NULL, &body, PATCH, "/echo?m=PATCH");
  run(&data, NULL, NULL, &body, GET, "/echo?m=GET");
  run(&data, NULL, NULL, &body, PUT, "/echo?m=PUT");
  run(&data, NULL, NULL, &body, DELETE, "/echo?m=DELETE");

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