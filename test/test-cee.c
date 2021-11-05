#include <stdio.h>
#include <string.h>

#include "user-agent.h"
#include "cee-utils.h"

void load(char *str, size_t len, void *ptr)
{
  fprintf(stderr, "%.*s", (int)len, str);
}

int commit(char *base_url, struct logconf *config)
{
  struct user_agent *data = ua_init(config);
  ua_set_url(data, base_url);

  curl_global_init(CURL_GLOBAL_ALL);
  struct sized_buffer body = { .start = "{ }", .size = 3 };
  struct ua_resp_handle handle = { .ok_cb = load, .ok_obj = NULL };
  struct ua_info info = { 0 };

  ua_run(data, &info, &handle, &body, HTTP_POST, "/echo?m=POST");
  ua_run(data, &info, &handle, &body, HTTP_PATCH, "/echo?m=PATCH");
  ua_run(data, &info, &handle, &body, HTTP_GET, "/echo?m=GET");
  ua_run(data, &info, &handle, &body, HTTP_PUT, "/echo?m=PUT");
  ua_run(data, &info, &handle, &body, HTTP_DELETE, "/echo?m=DELETE");

  curl_global_cleanup();

  return 0;
}

int main(int argc, char *argv[])
{
  char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "../config.json";

  struct logconf config;
  FILE *fp = fopen(config_file, "rb");
  logconf_setup(&config, "CEE_HTTP", fp);
  fclose(fp);

  commit("https://cee.studio", &config);

  return 0;
}
