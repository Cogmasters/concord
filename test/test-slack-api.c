#include <stdio.h>
#include <stdlib.h>

#include "slack-common.h"

void print_json_cb(char str[], size_t len, void *data) {
  fprintf(stderr, "%.*s", (int)len, str);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  struct slack_adapter adapter = {0};
  slack_adapter_init(&adapter, NULL, config_file);

  struct resp_handle resp_handle = { .ok_cb = &print_json_cb };

  slack_adapter_run(
    &adapter,
    &resp_handle,
    NULL,
    HTTP_GET, "/conversations.list?limit=50");

  slack_adapter_cleanup(&adapter);
}
