#include "slack.h"
#include "slack-common.h"

struct slack* 
slack_config_init(const char config_file[])
{
  struct slack *new_client = calloc(1, sizeof *new_client);
  slack_adapter_init(&new_client->adapter, config_file);
  slack_apps_connections_open(new_client);
  slack_socketmode_init(&new_client->sm, config_file);

  return new_client;
}

void 
slack_cleanup(struct slack *client)
{
  slack_adapter_cleanup(&client->adapter);
  slack_socketmode_cleanup(&client->sm);
  free(client);
}

void
slack_run(struct slack *client)
{
  ws_run(client->sm.ws);
}
