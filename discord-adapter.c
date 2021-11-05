#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "discord.h"
#include "discord-internal.h"

#include "cee-utils.h"

void
discord_adapter_init(struct discord_adapter *adapter,
                     struct logconf *conf,
                     struct sized_buffer *token)
{
  adapter->ua = ua_init(conf);
  ua_set_url(adapter->ua, DISCORD_API_BASE_URL);

  adapter->ratelimit = calloc(1, sizeof *adapter->ratelimit);
  if (pthread_mutex_init(&adapter->ratelimit->lock, NULL))
    ERR("Couldn't initialize pthread mutex");

  logconf_branch(&adapter->ratelimit->conf, conf, "DISCORD_RATELIMIT");
  if (!token->size) { /* no token means a webhook-only client */
    logconf_branch(&adapter->conf, conf, "DISCORD_WEBHOOK");
  }
  else {
    logconf_branch(&adapter->conf, conf, "DISCORD_HTTP");

    char auth[128];
    int ret =
      snprintf(auth, sizeof(auth), "Bot %.*s", (int)token->size, token->start);
    ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");

    ua_reqheader_add(adapter->ua, "Authorization", auth);
  }
}

void
discord_adapter_cleanup(struct discord_adapter *adapter)
{
  ua_cleanup(adapter->ua);
  discord_buckets_cleanup(adapter);
  pthread_mutex_destroy(&adapter->ratelimit->lock);
  free(adapter->ratelimit);
  ua_info_cleanup(&adapter->err.info);
}

/**
 * JSON ERROR CODES
 * https://discord.com/developers/docs/topics/opcodes-and-status-codes#json-json-error-codes
 */
static void
json_error_cb(char *str, size_t len, void *p_adapter)
{
  struct discord_adapter *adapter = p_adapter;
  char message[256] = "";

  json_extract(str, len, "(message):.*s (code):d", sizeof(message), message,
               &adapter->err.jsoncode);
  logconf_error(
    &adapter->conf,
    ANSICOLOR("(JSON Error %d) %s",
              ANSI_BG_RED) " - See Discord's JSON Error Codes\n\t\t%.*s",
    adapter->err.jsoncode, message, (int)len, str);

  snprintf(adapter->err.jsonstr, sizeof(adapter->err.jsonstr), "%.*s",
           (int)len, str);
}

static ORCAcode
_discord_perform_request(struct discord_adapter *adapter,
                         struct ua_resp_handle *resp_handle,
                         struct sized_buffer *req_body,
                         enum http_method http_method,
                         char endpoint[],
                         struct discord_bucket *bucket,
                         const char route[])
{
  bool keepalive = true;
  long delay_ms;
  ORCAcode code;

  /* if unset, set to default error handling callbacks */
  if (resp_handle && !resp_handle->err_cb) {
    resp_handle->err_cb = &json_error_cb;
    resp_handle->err_obj = adapter;
  }

  do {
    ua_info_cleanup(&adapter->err.info);
    delay_ms = discord_bucket_get_cooldown(adapter, bucket);
    if (delay_ms > 0) {
      logconf_info(&adapter->ratelimit->conf,
                   "[%.4s] RATELIMITING (wait %ld ms)", bucket->hash,
                   delay_ms);
      cee_sleep_ms(delay_ms);
    }

    code = ua_run(adapter->ua, &adapter->err.info, resp_handle, req_body,
                  http_method, endpoint);

    if (code != ORCA_HTTP_CODE) {
      keepalive = false;
    }
    else {
      switch (adapter->err.info.httpcode) {
      case HTTP_FORBIDDEN:
      case HTTP_NOT_FOUND:
      case HTTP_BAD_REQUEST:
        keepalive = false;
        code = ORCA_DISCORD_JSON_CODE;
        break;
      case HTTP_UNAUTHORIZED:
        keepalive = false;
        logconf_fatal(
          &adapter->conf,
          "UNAUTHORIZED: Please provide a valid authentication token");
        code = ORCA_DISCORD_BAD_AUTH;
        break;
      case HTTP_METHOD_NOT_ALLOWED:
        keepalive = false;
        logconf_fatal(&adapter->conf,
                      "METHOD_NOT_ALLOWED: The server couldn't recognize the "
                      "received HTTP method");
        break;
      case HTTP_TOO_MANY_REQUESTS: {
        bool is_global = false;
        char message[256] = "";
        double retry_after = -1; /* seconds */

        struct sized_buffer body = ua_info_get_body(&adapter->err.info);
        json_extract(body.start, body.size,
                     "(global):b (message):s (retry_after):lf", &is_global,
                     message, &retry_after);
        VASSERT_S(retry_after != -1, "(NO RETRY-AFTER INCLUDED) %s", message);

        retry_after *= 1000;

        if (is_global) {
          logconf_warn(&adapter->conf,
                       "429 GLOBAL RATELIMITING (wait: %.2lf ms) : %s",
                       retry_after, message);
          ua_block_ms(adapter->ua, (uint64_t)retry_after);
        }
        else {
          logconf_warn(&adapter->conf,
                       "429 RATELIMITING (wait: %.2lf ms) : %s", retry_after,
                       message);
          cee_sleep_ms((long)retry_after);
        }
        break;
      }
      default:
        if (adapter->err.info.httpcode >=
            500) /* server related error, retry */
          ua_block_ms(adapter->ua, 5000); /* wait for 5 seconds */
        break;
      }
    }
    discord_bucket_build(adapter, bucket, route, code, &adapter->err.info);
  } while (keepalive);

  return code;
}

/* template function for performing requests */
ORCAcode
discord_adapter_run(struct discord_adapter *adapter,
                    struct ua_resp_handle *resp_handle,
                    struct sized_buffer *req_body,
                    enum http_method http_method,
                    char endpoint_fmt[],
                    ...)
{
  va_list args;
  char endpoint[2048];
  int ret;

  /* Determine which ratelimit group (aka bucket) a request belongs to
   * by checking its route.
   * see:  https://discord.com/developers/docs/topics/rate-limits */
  const char *route;
  struct discord_bucket *bucket;

  /* build the endpoint string */
  va_start(args, endpoint_fmt);
  ret = vsnprintf(endpoint, sizeof(endpoint), endpoint_fmt, args);
  ASSERT_S(ret < sizeof(endpoint), "Out of bounds write attempt");
  va_end(args);

  /* check if 'route' is a major parameter (channel, guild or webhook),
   * if not use the raw endpoint_fmt as a route */
  if (strstr(endpoint_fmt, "/channels/%"))
    route = "@channel";
  else if (strstr(endpoint_fmt, "/guilds/%"))
    route = "@guild";
  else if (strstr(endpoint_fmt, "/webhook/%"))
    route = "@webhook";
  else
    route = endpoint_fmt;

  if ((bucket = discord_bucket_try_get(adapter, route)) != NULL) {
    ORCAcode code;
    pthread_mutex_lock(&bucket->lock);
    code = _discord_perform_request(adapter, resp_handle, req_body,
                                    http_method, endpoint, bucket, route);
    pthread_mutex_unlock(&bucket->lock);
    return code;
  }
  return _discord_perform_request(adapter, resp_handle, req_body, http_method,
                                  endpoint, NULL, route);
}
