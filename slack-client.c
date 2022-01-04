#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "slack.h"
#include "slack-internal.h"

struct slack *
slack_config_init(const char config_file[])
{
  struct slack *new_client;
  FILE *fp;

  orca_global_init();

  fp = fopen(config_file, "rb");
  VASSERT_S(fp != NULL, "Couldn't open '%s': %s", config_file,
            strerror(errno));

  new_client = calloc(1, sizeof *new_client);
  logconf_setup(&new_client->conf, "SLACK", fp);

  fclose(fp);

  new_client->bot_token =
    logconf_get_field(&new_client->conf, "slack.bot_token");
  new_client->app_token =
    logconf_get_field(&new_client->conf, "slack.app_token");

  slack_webapi_init(&new_client->webapi, &new_client->conf,
                    &new_client->bot_token);
  slack_sm_init(&new_client->sm, &new_client->conf);

  return new_client;
}

void
slack_cleanup(struct slack *client)
{
  logconf_cleanup(&client->conf);
  slack_webapi_cleanup(&client->webapi);
  slack_sm_cleanup(&client->sm);

  free(client);
}

void
slack_run(struct slack *client)
{
  slack_sm_run(&client->sm);
}

void
slack_set_event_scheduler(struct slack *client, slack_on_scheduler callback)
{
  client->sm.cbs.scheduler = callback;
}

void
slack_set_on_idle(struct slack *client, slack_on_event callback)
{
  client->sm.cbs.on_hello = callback;
}

void
slack_set_on_hello(struct slack *client, slack_on_event callback)
{
  client->sm.cbs.on_hello = callback;
}

void
slack_set_on_message(struct slack *client, slack_on_event callback)
{
  client->sm.cbs.on_message = callback;
}

void
slack_set_on_block_actions(struct slack *client, slack_on_event callback)
{
  client->sm.cbs.on_block_actions = callback;
}

void
slack_set_on_message_actions(struct slack *client, slack_on_event callback)
{
  client->sm.cbs.on_message_actions = callback;
}

void
slack_set_on_view_closed(struct slack *client, slack_on_event callback)
{
  client->sm.cbs.on_view_closed = callback;
}

void
slack_set_on_view_submission(struct slack *client, slack_on_event callback)
{
  client->sm.cbs.on_view_submission = callback;
}
