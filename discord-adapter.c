#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "discord.h"
#include "discord-internal.h"

#include "orka-utils.h"

#define BASE_API_URL "https://discord.com/api/v9"


void
discord_adapter_init(struct discord_adapter *adapter, struct logconf *config, struct sized_buffer *token)
{
  adapter->ua = ua_init(config);
  ua_set_url(adapter->ua, BASE_API_URL);
  logconf_add_id(config, adapter->ua, "DISCORD_HTTP");

  if (STRNEQ("YOUR-BOT-TOKEN", token->start, token->size)) {
    token->start = NULL;
  }
  ASSERT_S(NULL != token->start, "Missing bot token");

  char auth[128];
  int ret = snprintf(auth, sizeof(auth), "Bot %.*s", (int)token->size, token->start);
  ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");

  ua_reqheader_add(adapter->ua, "Authorization", auth);

  if (pthread_mutex_init(&adapter->ratelimit.lock, NULL))
    ERR("Couldn't initialize pthread mutex");

  discord_buckets_init(adapter);
}

void
discord_adapter_cleanup(struct discord_adapter *adapter)
{
  ua_cleanup(adapter->ua);
  pthread_mutex_destroy(&adapter->ratelimit.lock);
  discord_buckets_cleanup(adapter);
}

/**
 * JSON ERROR CODES
 * https://discord.com/developers/docs/topics/opcodes-and-status-codes#json-json-error-codes 
 */
static void
json_error_cb(char *str, size_t len, void *p_err)
{
  int code=0; // last error code received
  char message[256]=""; // meaning of the error received
  json_extract(str, len, \
      "(message):.*s (code):d", sizeof(message), message, &code);
  log_error(ANSICOLOR("(JSON Error %d) %s", ANSI_BG_RED)   \
            " - See Discord's JSON Error Codes\n\t\t%.*s", \
            code, message, (int)len, str);
}

/* template function for performing requests */
ORCAcode
discord_adapter_run(
  struct discord_adapter *adapter, 
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method, char endpoint[], ...)
{
  va_list args;
  va_start(args, endpoint);

  /* IF UNSET, SET TO DEFAULT ERROR HANDLING CALLBACKS */
  if (resp_handle && !resp_handle->err_cb) {
    resp_handle->err_cb = &json_error_cb;
    resp_handle->err_obj = NULL;
  }

  struct discord_bucket *bucket;
  pthread_mutex_lock(&adapter->ratelimit.lock);
  bucket = discord_bucket_try_get(adapter, endpoint);
  pthread_mutex_unlock(&adapter->ratelimit.lock);

  ORCAcode code;
  bool keepalive=true;
  while (keepalive) 
  {
    discord_bucket_try_cooldown(bucket);

    struct ua_info info;
    code = ua_vrun(
      adapter->ua,
      &info,
      resp_handle,
      req_body,
      http_method, endpoint, args);

    switch (code) {
    case ORCA_OK:
    case ORCA_UNUSUAL_HTTP_CODE:
    case ORCA_NO_RESPONSE:
        keepalive = false;
        break;
    case HTTP_FORBIDDEN:
    case HTTP_NOT_FOUND:
    case HTTP_BAD_REQUEST:
        keepalive = false; 
        break;
    case HTTP_UNAUTHORIZED:
    case HTTP_METHOD_NOT_ALLOWED:
        ERR("Aborting after %s received", http_code_print(code));
        break;
    case HTTP_TOO_MANY_REQUESTS: {
        char message[256]="";
        double retry_after=-1; // seconds

        struct sized_buffer body = ua_info_get_resp_body(&info);
        json_extract(body.start, body.size,         \
                    "(message):s (retry_after):lf", \
                    message, &retry_after);

        if (retry_after != -1) { // retry after attribute received
          log_warn("%s (wait: %.2lf ms)", message, 1000*retry_after);
          ua_block_ms(adapter->ua, (uint64_t)(1000*retry_after));
        }
        else { // no retry after included, we should abort
          ERR("(NO RETRY-AFTER INCLUDED) %s", message);
        }
       break; }
    default:
        if (code >= 500) // server related error, retry
          ua_block_ms(adapter->ua, 5000); // wait for 5 seconds
        break;
    }

    pthread_mutex_lock(&adapter->ratelimit.lock);
    discord_bucket_build(adapter, bucket, endpoint, &info);
    pthread_mutex_unlock(&adapter->ratelimit.lock);
    
    ua_info_cleanup(&info);
  }

  va_end(args);

  return code;
}
