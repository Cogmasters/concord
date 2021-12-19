#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "reddit.h"
#include "reddit-internal.h"
#include "cee-utils.h"

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

static void
setopt_cb(struct ua_conn *conn, void *p_client)
{
  CURL *ehandle = ua_conn_get_easy_handle(conn);
  struct reddit *client = p_client;
  char client_id[512], client_secret[512], ua[512];
  int ret;

  ret = snprintf(client_id, sizeof(client_id), "%.*s",
                 (int)client->client_id.size, client->client_id.start);
  ASSERT_S(ret < sizeof(client_id), "Out of bounds write attempt");

  ret = snprintf(client_secret, sizeof(client_secret), "%.*s",
                 (int)client->client_secret.size, client->client_secret.start);
  ASSERT_S(ret < sizeof(client_secret), "Out of bounds write attempt");

  ret = snprintf(ua, sizeof(ua),
                 "orca:github.com/cee-studio/orca:v.0 (by /u/%.*s)",
                 (int)client->username.size, client->username.start);
  ASSERT_S(ret < sizeof(ua), "Out of bounds write attempt");

  ua_conn_add_header(conn, "User-Agent", ua);
  ua_conn_add_header(conn, "Content-Type",
                     "application/x-www-form-urlencoded");

  curl_easy_setopt(ehandle, CURLOPT_USERNAME, client_id);
  curl_easy_setopt(ehandle, CURLOPT_PASSWORD, client_secret);
}

void
reddit_adapter_init(struct reddit_adapter *adapter, struct logconf *conf)
{
  struct reddit *client = CONTAINEROF(adapter, struct reddit, adapter);
  struct ua_attr attr = { 0 };

  attr.conf = conf;
  adapter->ua = ua_init(&attr);

  logconf_branch(&adapter->conf, conf, "REDDIT_HTTP");
  ua_set_url(adapter->ua, REDDIT_BASE_OAUTH_URL);

  ua_set_opt(adapter->ua, client, &setopt_cb);
}

void
reddit_adapter_cleanup(struct reddit_adapter *adapter)
{
  if (adapter->auth) free(adapter->auth);
  ua_cleanup(adapter->ua);
}

static ORCAcode
_reddit_adapter_run_sync(struct reddit_adapter *adapter,
                         struct reddit_request_attr *attr,
                         struct sized_buffer *body,
                         enum http_method method,
                         char endpoint[])
{
  struct ua_conn_attr conn_attr = { method, body, endpoint, attr->base_url };
  struct ua_conn *conn = ua_conn_start(adapter->ua);
  ORCAcode code;
  bool retry;

  /* populate conn with parameters */
  ua_conn_setup(conn, &conn_attr);

  if (adapter->auth) {
    ua_conn_add_header(conn, "Authorization", adapter->auth);
  }

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
      logconf_error(&adapter->conf, "Curl internal error, will retry again");
      retry = true;
      break;
    default:
      logconf_error(&adapter->conf, "ORCA code: %d", code);
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
reddit_adapter_run(struct reddit_adapter *adapter,
                   struct reddit_request_attr *attr,
                   struct sized_buffer *body,
                   enum http_method method,
                   char endpoint_fmt[],
                   ...)
{
  static struct reddit_request_attr blank_attr = { 0 };
  char endpoint[2048];
  va_list args;
  int ret;

  /* have it point somewhere */
  if (!attr) attr = &blank_attr;

  va_start(args, endpoint_fmt);

  ret = vsnprintf(endpoint, sizeof(endpoint), endpoint_fmt, args);
  ASSERT_S(ret < sizeof(endpoint), "Out of bounds write attempt");

  va_end(args);

  return _reddit_adapter_run_sync(adapter, attr, body, method, endpoint);
}

/******************************************************************************
 * Functions specific to Reddit Auth
 ******************************************************************************/

ORCAcode
reddit_access_token(struct reddit *client,
                    struct reddit_access_token_params *params,
                    struct sized_buffer *ret)
{
  struct reddit_request_attr attr = REQUEST_ATTR_RAW_INIT(ret);
  struct sized_buffer body;
  char buf[1024];
  size_t len = 0;
  ORCAcode code;

  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->grant_type),
              ORCA_BAD_PARAMETER);

  len += snprintf(buf, sizeof(buf), "grant_type=%s", params->grant_type);
  ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");

  if (STREQ(params->grant_type, "password")) { // script apps
    if (IS_EMPTY_STRING(params->username)) {
      ORCA_EXPECT(client, client->username.size != 0, ORCA_BAD_PARAMETER);

      len += snprintf(buf + len, sizeof(buf) - len, "&username=%.*s",
                      (int)client->username.size, client->username.start);
    }
    else {
      len += snprintf(buf + len, sizeof(buf) - len, "&username=%s",
                      params->username);
    }

    if (IS_EMPTY_STRING(params->password)) {
      ORCA_EXPECT(client, client->password.size != 0, ORCA_BAD_PARAMETER);

      len += snprintf(buf + len, sizeof(buf) - len, "&password=%.*s",
                      (int)client->password.size, client->password.start);
    }
    else {
      len += snprintf(buf + len, sizeof(buf) - len, "&password=%s",
                      params->password);
    }
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");
  }
  else if (STREQ(params->grant_type, "authorization_code")) { // web apps
    ORCA_EXPECT(client, !IS_EMPTY_STRING(params->code), ORCA_BAD_PARAMETER);
    ORCA_EXPECT(client, !IS_EMPTY_STRING(params->redirect_uri),
                ORCA_BAD_PARAMETER);

    len += snprintf(buf + len, sizeof(buf) - len, "&code=%s&redirect_uri=%s",
                    params->code, params->redirect_uri);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");
  }
  else if (!STREQ(params->grant_type, "refresh_token")) {
    logconf_error(&client->conf, "Unknown 'grant_type' value (%s)",
                  params->grant_type);
    return ORCA_BAD_PARAMETER;
  }

  body.start = buf;
  body.size = len;

  attr.base_url = REDDIT_BASE_API_URL;

  code = reddit_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                            "/api/v1/access_token");

  if (ORCA_OK == code) {
    char access_token[64], token_type[64], auth[256];
    int len;

    json_extract(ret->start, ret->size,
                 "(access_token):.*s"
                 "(token_type):.*s",
                 sizeof(access_token), access_token, sizeof(token_type),
                 token_type);

    len = snprintf(auth, sizeof(auth), "%s %s", token_type, access_token);
    ASSERT_S(len < sizeof(auth), "Out of bounds write attempt");

    if (!client->adapter.auth) {
      client->adapter.auth = malloc(sizeof(auth));
    }
    memcpy(client->adapter.auth, auth, sizeof(auth));
    client->adapter.auth[len] = '\0';
  }

  return code;
}

/******************************************************************************
 * Functions specific to Reddit Links & Comments
 ******************************************************************************/

ORCAcode
reddit_comment(struct reddit *client,
               struct reddit_comment_params *params,
               struct sized_buffer *ret)
{
  struct reddit_request_attr attr = REQUEST_ATTR_RAW_INIT(ret);
  struct sized_buffer body;
  char *text_url_encoded;
  char buf[4096];
  size_t len = 0;

  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->text), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->thing_id), ORCA_BAD_PARAMETER);

  text_url_encoded = url_encode(params->text);

  len += snprintf(buf, sizeof(buf), "text=%s", text_url_encoded);
  ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");

  free(text_url_encoded);

  len +=
    snprintf(buf + len, sizeof(buf) - len, "&thing_id=%s", params->thing_id);
  ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");

  if (params->api_type) {
    len +=
      snprintf(buf + len, sizeof(buf) - len, "&api_type=%s", params->api_type);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");
  }
  if (params->return_rtjson) {
    len += snprintf(buf + len, sizeof(buf) - len, "&return_rtjson=%d",
                    params->return_rtjson);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");
  }
  if (params->richtext_json) {
    len += snprintf(buf + len, sizeof(buf) - len, "&richtext_json=%s",
                    params->richtext_json);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");
  }
  if (params->uh) {
    len += snprintf(buf + len, sizeof(buf) - len, "&uh=%s", params->uh);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");
  }

  body.start = buf;
  body.size = len;

  return reddit_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                            "/api/comment");
}

/******************************************************************************
 * Functions specific to Reddit Search
 ******************************************************************************/

ORCAcode
reddit_search(struct reddit *client,
              struct reddit_search_params *params,
              char subreddit[],
              struct sized_buffer *ret)
{
  struct reddit_request_attr attr = REQUEST_ATTR_RAW_INIT(ret);
  char *q_url_encoded;
  char query[1024];
  size_t len = 0;

  ORCA_EXPECT(client, !IS_EMPTY_STRING(subreddit), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, cee_str_bounds_check(params->category, 5) != 0,
              ORCA_BAD_PARAMETER,
              "Category should be no longer than 5 characters");
  ORCA_EXPECT(client, cee_str_bounds_check(params->q, 512) > 0,
              ORCA_BAD_PARAMETER,
              "Keywords should be no longer than 512 characters");
  ORCA_EXPECT(client,
              IS_EMPTY_STRING(params->show) || STREQ(params->show, "all"),
              ORCA_BAD_PARAMETER, "'show' should be NULL or \"all\"");
  ORCA_EXPECT(client,
              IS_EMPTY_STRING(params->type)
                || strstr("sr,link,user", params->type),
              ORCA_BAD_PARAMETER);

  if (!params->limit) // default is 25
    params->limit = 25;
  else if (params->limit > 100)
    params->limit = 100;

  len += snprintf(query, sizeof(query), "limit=%d", params->limit);
  ASSERT_S(len < sizeof(query), "Out of bounds write attempt");

  q_url_encoded = url_encode(params->q);

  len += snprintf(query + len, sizeof(query) - len, "&q=%s", q_url_encoded);
  ASSERT_S(len < sizeof(query), "Out of bounds write attempt");

  free(q_url_encoded);

  if (true == params->restrict_sr) {
    len += snprintf(query + len, sizeof(query) - len, "&restrict_sr=1");
    ASSERT_S(len < sizeof(query), "Out of bounds write attempt");
  }
  if (!IS_EMPTY_STRING(params->t)) {
    ORCA_EXPECT(client, strstr("hour,day,week,month,year,all", params->t),
                ORCA_BAD_PARAMETER);

    len += snprintf(query + len, sizeof(query) - len, "&t=%s", params->t);
    ASSERT_S(len < sizeof(query), "Out of bounds write attempt");
  }
  if (!IS_EMPTY_STRING(params->sort)) {
    ORCA_EXPECT(client, strstr("relevance,hot,top,new,comments", params->sort),
                ORCA_BAD_PARAMETER);

    len +=
      snprintf(query + len, sizeof(query) - len, "&sort=%s", params->sort);
    ASSERT_S(len < sizeof(query), "Out of bounds write attempt");
  }
  if (params->before) {
    ORCA_EXPECT(client, IS_EMPTY_STRING(params->after), ORCA_BAD_PARAMETER,
                "Can't have 'after' and 'before' set at the same time");

    len +=
      snprintf(query + len, sizeof(query) - len, "&before=%s", params->before);
    ASSERT_S(len < sizeof(query), "Out of bounds write attempt");
  }
  if (params->after) {
    ORCA_EXPECT(client, IS_EMPTY_STRING(params->before), ORCA_BAD_PARAMETER,
                "Can't have 'after' and 'before' set at the same time");

    len +=
      snprintf(query + len, sizeof(query) - len, "&after=%s", params->after);
    ASSERT_S(len < sizeof(query), "Out of bounds write attempt");
  }

  return reddit_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                            "/r/%s/search.json?raw_json=1%s", subreddit,
                            query);
}
