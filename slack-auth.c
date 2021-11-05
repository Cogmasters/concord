#include "slack.h"
#include "slack-internal.h"

ORCAcode
slack_auth_test(struct slack *client, struct sized_buffer *p_resp_body)
{
  return slack_webapi_run(&client->webapi, p_resp_body, NULL, HTTP_POST,
                          "/auth.test");
}
