#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> //for usleep
#include <stdarg.h>

#include <libdiscord.h>
#include "discord-common.h"

#define BASE_API_URL "https://discord.com/api"

/* initialize curl_slist's request header utility
 * @todo create distinction between bot and bearer token */
static struct curl_slist*
reqheader_init(char token[])
{
  char auth[MAX_HEADER_LEN] = "Authorization: Bot "; 

  struct curl_slist *new_header = NULL;
  void *tmp; //for checking potential allocation error

  new_header = curl_slist_append(new_header,"X-RateLimit-Precision: millisecond");
  ASSERT_S(NULL != new_header, "Out of memory");

  tmp = curl_slist_append(new_header, strcat(auth, token));
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header,"User-Agent: libdiscord (http://github.com/cee-studio/libdiscord, v"LIBDISCORD_VERSION")");
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header,"Content-Type: application/json");
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header,"Accept: application/json");
  ASSERT_S(NULL != tmp, "Out of memory");

  return new_header;
}

/* a simple http header parser, splits key/field pairs at ':'
 * see: https://curl.se/libcurl/c/CURLOPT_HEADERFUNCTION.html */
static size_t
curl_resheader_cb(char *content, size_t size, size_t nmemb, void *p_userdata)
{
  size_t realsize = size * nmemb;
  struct api_header_s *res_pairs = p_userdata;

  char *ptr;
  if ( !(ptr = strchr(content, ':')) ) { //ptr is NULL if can't find ':' token match
    return realsize;
  }

  *ptr = '\0'; //replace ':' with '\0' to isolate key
  
  res_pairs->key[res_pairs->size] = content;

  if ( !(ptr = strstr(ptr+1, "\r\n")) ) {//ptr is NULL if can't find CRLF match
    return realsize;
  }

  *ptr = '\0'; //replace CRLF with '\0' to isolate key

  //try to catch space tokens at start of field and adjust position
  int offset = 1; //start after key's '\0'
  while (isspace(content[strlen(content) + offset])) {
    ++offset;
  }

  res_pairs->field[res_pairs->size] = &content[strlen(content) + offset];

  ++res_pairs->size; //update header amount of key/field pairs
  ASSERT_S(res_pairs->size < MAX_HEADER_SIZE, "Stack overflow");

  return realsize;
}

/* get api response body string
 * see: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
static size_t
curl_resbody_cb(char *content, size_t size, size_t nmemb, void *p_userdata)
{
  size_t realsize = size * nmemb;
  struct api_response_s *res_body = p_userdata;

  //update response body string size
  char *tmp = realloc(res_body->str, res_body->size + realsize + 1);
  ASSERT_S(NULL != tmp, "Out of memory");

  res_body->str = tmp;
  memcpy(res_body->str + res_body->size, content, realsize);
  res_body->size += realsize;
  res_body->str[res_body->size] = '\0';

  return realsize;
}

/* initialize curl's easy handle with some default opt */
static CURL*
custom_easy_init(struct discord_api_s *api)
{
  CURL *new_ehandle = curl_easy_init();
  ASSERT_S(NULL != new_ehandle, "Out of memory");

  CURLcode ecode;
  /* uncomment for verbose */
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_VERBOSE, 2L);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
  /* * * * * * * * * * * * */

  //set ptr to request header we will be using for API communication
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HTTPHEADER, api->req_header);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //enable follow redirections
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 1L);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set response body callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEFUNCTION, &curl_resbody_cb);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to response body to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEDATA, &api->res_body);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set response header callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERFUNCTION, &curl_resheader_cb);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to response header to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERDATA, &api->res_pairs);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  return new_ehandle;
}

void
Discord_api_init(struct discord_api_s *api, char token[])
{
  api->req_header = reqheader_init(token);
  api->ehandle = custom_easy_init(api);
  api->res_body.str = NULL;
  api->res_body.size = 0;
  api->res_pairs.size = 0;
}

void
Discord_api_cleanup(struct discord_api_s *api)
{
  curl_slist_free_all(api->req_header);
  curl_easy_cleanup(api->ehandle); 

  if (api->res_body.str)
    free(api->res_body.str);
}

/* set specific http method used for the request */
static void
set_method(struct discord_api_s *api, enum http_method method)
{
  CURLcode ecode;
  switch (method) {
  case DELETE:
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_CUSTOMREQUEST, "DELETE");
      break;
  case GET:
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_HTTPGET, 1L);
      break;
  case POST:
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_POST, 1L);
      break;
  case PATCH:
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_CUSTOMREQUEST, "PATCH");
      break;
  case PUT:
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_UPLOAD, 1L);
      break;
  default:
      ERROR("Unknown http method (code: %d)", method);
  }
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
}

/* set specific url used for request */
static void
set_url(struct discord_api_s *api, char endpoint[])
{
  char base_url[MAX_URL_LEN] = BASE_API_URL;

  CURLcode ecode = curl_easy_setopt(api->ehandle, CURLOPT_URL, strcat(base_url, endpoint));
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
}

/* perform the request */
static void
perform_request(
  struct discord_api_s *api,
  void **p_object, 
  discord_load_obj_cb *load_cb,
  char send_payload[])
{
  CURLcode ecode;

  //store send payload in curl internals
  if (NULL != send_payload) {
    //set ptr to payload that will be sent via POST/PUT
    ecode = curl_easy_setopt(api->ehandle, CURLOPT_POSTFIELDS, send_payload);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
  }

  //try to perform the request and analyze output
  enum discord_http_code http_code; //the http response code
  char *url = NULL; //the request URL
  do {
    //perform the request
    ecode = curl_easy_perform(api->ehandle);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    //get response's http code
    ecode = curl_easy_getinfo(api->ehandle, CURLINFO_RESPONSE_CODE, &http_code);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    //get request's url
    ecode = curl_easy_getinfo(api->ehandle, CURLINFO_EFFECTIVE_URL, &url);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    D_PRINT("Request URL: %s", url);

    switch (http_code) {
    case HTTP_OK:
        if (NULL == load_cb) return;

        (*load_cb)(p_object, api->res_body.str);

        //clean response for next iteration
        free(api->res_body.str);
        api->res_body.str = NULL;
        api->res_body.size = 0;

        break; /* DONE */
    case HTTP_TOO_MANY_REQUESTS:
    /* @todo dealing with ratelimits solely by checking for
     *  HTTP_TOO_MANY REQUESTS is not discord compliant */
     {
        char message[256] = {0};
        long long retry_after;

        json_scanf(api->res_body.str,
                    "%s[message]" \
                    "%lld[retry_after]",
                    message,
                    &retry_after);

        D_PRINT("%s", message);

        usleep(retry_after*1000);

        //clean response for next iteration
        free(api->res_body.str);
        api->res_body.str = NULL;
        api->res_body.size = 0;

        break;
     }
    case CURL_NO_RESPONSE: //@todo implement circumvention
        ERROR("Curl couldn't fetch a HTTP response");
    default:
        ERROR("Unknown HTTP response code %d", http_code);
    }
  } while (HTTP_OK != http_code);

  api->res_pairs.size = 0; //reset header size for the next iteration
}

void
Discord_api_load_message(void **p_message, char *str)
{
  discord_message_t *message = *p_message;

  char str_author[512];
  char str_mentions[512];
  char str_referenced_message[512];

/*
  json_scanf(str,
     "%s[id]" \
     "%s[channel_id]" \
     "%s[guild_id]" \
     "%S[author]" \
     "%s[content]" \
     "%s[timestamp]" \
     "%s[edited_timestamp]" \
     "%b[tts]" \
     "%b[mention_everyone]" \
     "%S[mentions]" \
     "%s[nonce]" \
     "%b[pinned]" \
     "%s[webhook_id]" \
     "%d[type]" \
     "%d[flags]" \
     "%S[referenced_message]",
      message->id,
      message->channel_id,
      message->guild_id,
      str_author,
      message->content,
      message->timestamp,
      message->edited_timestamp,
      &message->tts,
      &message->mention_everyone,
      str_mentions,
      message->nonce,
      &message->pinned,
      message->webhook_id,
      &message->flags,
      str_referenced_message);
*/

  json_scanf(str, 
              "%s[content]" \
              "%s[channel_id]" \
              "%S[author]", 
              message->content, 
              message->channel_id,
              str_author);

  if (NULL == message->author) {
    message->author = discord_user_init();
    ASSERT_S(NULL != message->author, "Out of memory");
  }

  Discord_api_load_user((void**)&message->author, str_author);

  *p_message = message;

  D_PUTS("Message loaded with API response"); 
}

void
Discord_api_load_guild(void **p_guild, char *str)
{
  discord_guild_t *guild = *p_guild;

  json_scanf(str,
     "%s[id]" \
     "%s[name]" \
     "%s[icon]" \
     "%b[owner]" \
     "%d[permissions]" \
     "%s[permissions_new]",
      guild->id,
      guild->name,
      guild->icon,
      &guild->owner,
      &guild->permissions,
      guild->permissions_new);

  *p_guild = guild;

  D_PUTS("Guild loaded with API response"); 
}

void
Discord_api_load_user(void **p_user, char *str)
{
  discord_user_t *user = *p_user;

  json_scanf(str,
     "%s[id]" \
     "%s[username]" \
     "%s[discriminator]" \
     "%s[avatar]" \
     "%b[bot]" \
     "%b[system]" \
     "%b[mfa_enabled]" \
     "%s[locale]" \
     "%b[verified]" \
     "%s[email]" \
     "%d[flags]" \
     "%d[premium_type]" \
     "%d[public_flags]",
      user->id,
      user->username,
      user->discriminator,
      user->avatar,
      &user->bot,
      &user->sys,
      &user->mfa_enabled,
      user->locale,
      &user->verified,
      user->email,
      &user->flags,
      &user->premium_type,
      &user->public_flags);

  *p_user = user;

  D_PUTS("User loaded with API response"); 
}

/* template function for performing requests */
void
Discord_api_request(
  struct discord_api_s *api, 
  void **p_object, 
  discord_load_obj_cb *load_cb,
  char send_payload[],
  enum http_method http_method,
  char endpoint[],
  ...)
{
  //create the url route
  va_list args;
  va_start (args, endpoint);

  char url_route[MAX_URL_LEN];
  vsprintf(url_route, endpoint, args);

  va_end(args);

  //set the request method
  set_method(api, http_method);
  //set the request URL
  set_url(api, url_route);
  //perform the request
  perform_request(api, p_object, load_cb, send_payload);
}

