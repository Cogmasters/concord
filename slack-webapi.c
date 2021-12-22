#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "slack.h"
#include "slack-internal.h"

/**
 * @brief Shortcut for setting request attributes expecting a raw JSON response
 *
 * @param ret_json pointer to `struct sized_buffer` to store JSON at
 */
#define REQUEST_ATTR_RAW_INIT(ret_json)                                       \
  {                                                                           \
    ret_json, 0, NULL,                                                        \
      (void (*)(char *, size_t, void *)) & cee_sized_buffer_from_json, NULL   \
  }

void
slack_webapi_init(struct slack_webapi *webapi,
                  struct logconf *conf,
                  struct sized_buffer *token)
{
  struct ua_attr attr = { 0 };

  attr.conf = conf;
  webapi->ua = ua_init(&attr);
  ua_set_url(webapi->ua, SLACK_BASE_API_URL);
  logconf_branch(&webapi->conf, conf, "SLACK_WEBAPI");

  if (STRNEQ("YOUR-BOT-TOKEN", token->start, token->size)) {
    token->start = NULL;
  }
  ASSERT_S(NULL != token->start, "Missing bot token");
}

void
slack_webapi_cleanup(struct slack_webapi *webapi)
{
  ua_cleanup(webapi->ua);
}

static ORCAcode
_slack_webapi_run_sync(struct slack_webapi *webapi,
                       struct slack_request_attr *attr,
                       struct sized_buffer *body,
                       enum http_method method,
                       char endpoint[])
{
  struct ua_conn_attr conn_attr = { method, body, endpoint };
  struct ua_conn *conn = ua_conn_start(webapi->ua);
  struct sized_buffer *token;
  char *content_type;
  char auth[256] = "";
  ORCAcode code;
  bool retry;

  /* populate conn with parameters */
  ua_conn_setup(conn, &conn_attr);

  /* select token-level */
  switch (attr->token_level) {
  case SLACK_TOKEN_APP:
    token = &CLIENT(webapi, webapi)->app_token;
    break;
  case SLACK_TOKEN_BOT:
  default:
    token = &CLIENT(webapi, webapi)->bot_token;
    break;
  }
  snprintf(auth, sizeof(auth), "Bearer %.*s", (int)token->size, token->start);
  ua_conn_add_header(conn, "Authorization", auth);

  if (attr->content_type)
    content_type = attr->content_type;
  else
    content_type = "application/x-www-form-urlencoded";
  ua_conn_add_header(conn, "Content-Type", content_type);

  do {
    /* perform blocking request, and check results */
    switch (code = ua_conn_easy_perform(conn)) {
    case ORCA_OK: {
      struct ua_info info = { 0 };
      struct sized_buffer body;

      ua_info_extract(conn, &info);

      body = ua_info_get_body(&info);
      if (ORCA_OK == info.code && attr->obj) {
        if (attr->init) attr->init(attr->obj);

        attr->from_json(body.start, body.size, attr->obj);
      }

      ua_info_cleanup(&info);

      retry = false;
    } break;
    case ORCA_CURLE_INTERNAL:
      logconf_error(&webapi->conf, "Curl internal error, will retry again");
      retry = true;
      break;
    default:
      logconf_error(&webapi->conf, "ORCA code: %d", code);
      retry = false;
      break;
    }

    ua_conn_reset(conn);
  } while (retry);

  ua_conn_stop(conn);

  return code;
}

/* template function for performing requests */
ORCAcode
slack_webapi_run(struct slack_webapi *webapi,
                 struct slack_request_attr *attr,
                 struct sized_buffer *body,
                 enum http_method method,
                 char endpoint_fmt[],
                 ...)
{
  static struct slack_request_attr blank_attr = { 0 };
  char endpoint[2048];
  va_list args;
  size_t ret;

  /* have it point somewhere */
  if (!attr) attr = &blank_attr;

  va_start(args, endpoint_fmt);

  ret = vsnprintf(endpoint, sizeof(endpoint), endpoint_fmt, args);
  ASSERT_S(ret < sizeof(endpoint), "Out of bounds write attempt");

  va_end(args);

  return _slack_webapi_run_sync(webapi, attr, body, method, endpoint);
}

/******************************************************************************
 * Functions specific to Slack Apps
 ******************************************************************************/

ORCAcode
slack_apps_connections_open(struct slack *client, struct sized_buffer *ret)
{
  struct slack_request_attr attr = REQUEST_ATTR_RAW_INIT(ret);

  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->bot_token.start),
              ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->app_token.start),
              ORCA_BAD_PARAMETER);

  attr.token_level = SLACK_TOKEN_APP;

  return slack_webapi_run(&client->webapi, &attr, NULL, HTTP_POST,
                          "/apps.connections.open");
}

/******************************************************************************
 * Functions specific to Slack Auth
 ******************************************************************************/

ORCAcode
slack_auth_test(struct slack *client, struct sized_buffer *ret)
{
  struct slack_request_attr attr = REQUEST_ATTR_RAW_INIT(ret);

  return slack_webapi_run(&client->webapi, &attr, NULL, HTTP_POST,
                          "/auth.test");
}

/******************************************************************************
 * Functions specific to Slack Chat
 ******************************************************************************/

ORCAcode
slack_chat_post_message(struct slack *client,
                        struct slack_chat_post_message_params *params,
                        struct sized_buffer *ret)
{
  struct slack_request_attr attr = REQUEST_ATTR_RAW_INIT(ret);
  struct sized_buffer body;
  char buf[16384]; /**< @todo dynamic buffer */

  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->channel), ORCA_BAD_PARAMETER);

  body.size = slack_chat_post_message_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  attr.content_type = "application/json";

  return slack_webapi_run(&client->webapi, &attr, &body, HTTP_POST,
                          "/chat.postMessage");
}

/******************************************************************************
 * Functions specific to Slack Users
 ******************************************************************************/

ORCAcode
slack_users_info(struct slack *client,
                 struct slack_users_info_params *params,
                 struct sized_buffer *ret)
{
  struct slack_request_attr attr = REQUEST_ATTR_RAW_INIT(ret);
  struct sized_buffer body;
  char buf[4096];
  size_t len;

  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->user), ORCA_BAD_PARAMETER);

  len = snprintf(buf, sizeof(buf), "user=%s", params->user);
  ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");

  if (params->token) {
    len += snprintf(buf + len, sizeof(buf) - len, "&token=%s", params->token);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");
  }
  if (params->include_locale) {
    len += snprintf(buf + len, sizeof(buf) - len, "&include_locale=true");
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");
  }

  body.start = buf;
  body.size = len;

  return slack_webapi_run(&client->webapi, &attr, &body, HTTP_POST,
                          "/users.info");
}
