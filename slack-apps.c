#include <string.h>

#include "slack.h"
#include "slack-internal.h"

ORCAcode
slack_apps_connections_open(struct slack *client,
                            struct sized_buffer *p_resp_body)
{

  ASSERT_S(NULL != client->bot_token.start, "Missing bot token");
  ASSERT_S(NULL != client->app_token.start, "Missing app token");

  char auth[128] = "";
  size_t ret;

  ret = snprintf(auth, sizeof(auth), "Bearer %.*s",
                 (int)client->app_token.size, client->app_token.start);
  ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");
  ua_reqheader_add(client->webapi.ua, "Authorization", auth);

  ORCAcode code;
  code = slack_webapi_run(&client->webapi, p_resp_body, NULL, HTTP_POST,
                          "/apps.connections.open");

  ret = snprintf(auth, sizeof(auth), "Bearer %.*s",
                 (int)client->bot_token.size, client->bot_token.start);
  ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");
  ua_reqheader_add(client->webapi.ua, "Authorization", auth);

  return code;
}
