#include <string.h>

#include "slack.h"
#include "slack-internal.h"

ORCAcode
slack_chat_post_message(struct slack *client,
                        struct slack_chat_post_message_params *params,
                        struct sized_buffer *p_resp_body)
{
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(params->channel)) {
    log_error("Missing 'params.channel'");
    return ORCA_MISSING_PARAMETER;
  }

  char *payload = NULL;
  size_t ret = json_ainject(&payload,
                            "(token):s"
                            "(channel):s"
#if 0
                "(as_user):b"
#endif
                            "(icon_url):s"
                            "(icon_emoji):s"
                            "(text):s"
                            "(thread_ts):s"
                            "(username):s",
                            params->token, params->channel,
#if 0
                &params->as_user,
#endif
                            params->icon_url, params->icon_emoji, params->text,
                            params->thread_ts, params->username);

  if (!payload) {
    log_error("Couldn't create payload");
    return ORCA_BAD_PARAMETER;
  }

  ua_reqheader_add(client->webapi.ua, "Content-type", "application/json");

  ORCAcode code;
  code = slack_webapi_run(&client->webapi, p_resp_body,
                          &(struct sized_buffer){ payload, ret }, HTTP_POST,
                          "/chat.postMessage");

  ua_reqheader_add(client->webapi.ua, "Content-type",
                   "application/x-www-form-urlencoded");

  free(payload);

  return code;
}
