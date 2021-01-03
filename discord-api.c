#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> //for usleep
#include <stdarg.h>

#include <libdiscord.h>
#include "discord-common.h"


/* initialize curl_slist's request header utility
 * @todo create distinction between bot and bearer token */
static struct curl_slist*
_discord_reqheader_init(char token[])
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

  return new_header;
}

/* a simple http header parser, splits key/field pairs at ':'
 * see: https://curl.se/libcurl/c/CURLOPT_HEADERFUNCTION.html */
static size_t
_curl_resheader_cb(char *content, size_t size, size_t nmemb, void *p_userdata)
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
_curl_resbody_cb(char *content, size_t size, size_t nmemb, void *p_userdata)
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
_discord_easy_init(struct discord_api_s *api)
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
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEFUNCTION, &_curl_resbody_cb);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to response body to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEDATA, &api->res_body);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set response header callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERFUNCTION, &_curl_resheader_cb);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to response header to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERDATA, &api->res_pairs);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  return new_ehandle;
}

void
Discord_api_init(struct discord_api_s *api, char token[])
{
  api->req_header = _discord_reqheader_init(token);
  api->easy_handle = _discord_easy_init(api);
  api->res_body.str = NULL;
  api->res_body.size = 0;
  api->res_pairs.size = 0;
}

void
Discord_api_cleanup(struct discord_api_s *api)
{
  curl_slist_free_all(api->req_header);
  curl_easy_cleanup(api->easy_handle); 

  if (api->res_body.str) {
    free(api->res_body.str);
  }
}

/* set specific http method used for the request */
static void
_discord_set_method(struct discord_api_s *api, enum http_method method)
{
  CURLcode ecode;
  switch (method) {
  case DELETE:
      ecode = curl_easy_setopt(api->easy_handle, CURLOPT_CUSTOMREQUEST, "DELETE");
      break;
  case GET:
      ecode = curl_easy_setopt(api->easy_handle, CURLOPT_HTTPGET, 1L);
      break;
  case POST:
      ecode = curl_easy_setopt(api->easy_handle, CURLOPT_POST, 1L);
      break;
  case PATCH:
      ecode = curl_easy_setopt(api->easy_handle, CURLOPT_CUSTOMREQUEST, "PATCH");
      break;
  case PUT:
      ecode = curl_easy_setopt(api->easy_handle, CURLOPT_UPLOAD, 1L);
      break;
  default:
      ERROR("Unknown http method (code: %d)", method);
  }
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
}

/* set specific url used for request */
static void
_discord_set_url(struct discord_api_s *api, char endpoint[])
{
  char base_url[MAX_URL_LEN] = BASE_API_URL;

  CURLcode ecode = curl_easy_setopt(api->easy_handle, CURLOPT_URL, strcat(base_url, endpoint));
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
}

/* perform the request */
static void
_discord_perform_request(
  struct discord_api_s *api,
  void **p_object, 
  discord_load_obj_ft *load_cb)
{
  //try to perform the request and analyze output
  enum discord_http_code http_code; //the http response code
  char *url = NULL; //the request URL
  CURLcode ecode;
  do {
    //perform the request
    ecode = curl_easy_perform(api->easy_handle);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    //get response's http code
    ecode = curl_easy_getinfo(api->easy_handle, CURLINFO_RESPONSE_CODE, &http_code);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    //get request's url
    ecode = curl_easy_getinfo(api->easy_handle, CURLINFO_EFFECTIVE_URL, &url);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    D_PRINT("Request URL: %s", url);

    switch (http_code) {
    case HTTP_OK:
        (*load_cb)(p_object, &api->res_body);
        D_NOTOP_PUTS("Object loaded with API response"); 

        //clean response for next iteration
        free(api->res_body.str);
        api->res_body.str = NULL;
        api->res_body.size = 0;

        return; /* DONE */
    case HTTP_TOO_MANY_REQUESTS:
    /* @todo dealing with ratelimits solely by checking for
     *  HTTP_TOO_MANY REQUESTS is not discord compliant */
     {
        char message[256] = {0};
        long long retry_after;

        jscon_scanf(api->res_body.str,
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
        ERROR_MIN(CURL_NO_RESPONSE);
    default:
        ERROR("Unknown HTTP code %d", http_code);
    }
  } while (HTTP_OK != http_code);
}

/* template function for performing requests */
void
Discord_api_request(
  struct discord_api_s *api, 
  void **p_object, 
  discord_load_obj_ft *load_cb,
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
  _discord_set_method(api, http_method);
  //set the request URL
  _discord_set_url(api, url_route);
  //perform the request
  _discord_perform_request(api, p_object, load_cb);
}
