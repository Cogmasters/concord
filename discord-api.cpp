#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> //for usleep
#include <stdarg.h>


namespace discord {
namespace v8 {
namespace api {

struct response_body {
  char *str; //the response str
  size_t size; //the response str length
};

#define MAX_HEADER_SIZE 100
#define MAX_HEADER_LEN  512

struct header_pairs {
  char field[MAX_HEADER_SIZE][MAX_HEADER_LEN];
  char value[MAX_HEADER_SIZE][MAX_HEADER_LEN];
  int size;
};

struct data {
  struct curl_slist *req_header; //the request header sent to the api

  struct response_body body; //the api response string
  struct header_pairs pairs; //the key/field pairs response header
  CURL *ehandle; //the curl's easy handle used to perform requests

  struct settings { //@todo this whole struct is temporary
    char *token;
    FILE *f_json_dump;
    FILE *f_curl_dump;
  } settings;
};

static void
sleep_ms(const long long delay_ms)
{
  const struct timespec t = {
          .tv_sec = delay_ms / 1000,
          .tv_nsec = (delay_ms % 1000) * 1e6
  };

  nanosleep(&t, NULL);
}

static char*
http_code_print(enum http_code code)
{
  switch (code) {
    CASE_RETURN_STR(HTTP_OK);
    CASE_RETURN_STR(HTTP_CREATED);
    CASE_RETURN_STR(HTTP_NO_CONTENT);
    CASE_RETURN_STR(HTTP_NOT_MODIFIED);
    CASE_RETURN_STR(HTTP_BAD_REQUEST);
    CASE_RETURN_STR(HTTP_UNAUTHORIZED);
    CASE_RETURN_STR(HTTP_FORBIDDEN);
    CASE_RETURN_STR(HTTP_NOT_FOUND);
    CASE_RETURN_STR(HTTP_METHOD_NOT_ALLOWED);
    CASE_RETURN_STR(HTTP_TOO_MANY_REQUESTS);
    CASE_RETURN_STR(HTTP_GATEWAY_UNAVAILABLE);
    default:
      if (code >= 500) {
        return "5xx SERVER ERROR";
      }
      ERROR("Invalid HTTP response code (code: %d)", code);
  }
}

/* initialize curl_slist's request header utility
 * @todo create distinction between bot and bearer token */
static struct curl_slist*
reqheader_init(char token[])
{
  char auth[MAX_HEADER_LEN];
  int ret = snprintf(auth, MAX_HEADER_LEN, "Authorization: Bot %s", token);
  ASSERT_S(ret < (int)sizeof(auth), "Out of bounds write attempt");

  struct curl_slist *new_header = NULL;
  void *tmp; //for checking potential allocation error

  new_header = curl_slist_append(new_header,"X-RateLimit-Precision: millisecond");
  ASSERT_S(NULL != new_header, "Out of memory");

  tmp = curl_slist_append(new_header,"Accept: application/json");
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header, auth);
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header,"User-Agent: orca (http://github.com/cee-studio/orca, v"LIBDISCORD_VERSION")");
  ASSERT_S(NULL != tmp, "Out of memory");

  tmp = curl_slist_append(new_header,"Content-Type: application/json");
  ASSERT_S(NULL != tmp, "Out of memory");

  return new_header;
}

/* a simple http header parser, splits field/value pairs at ':'
 * see: https://curl.se/libcurl/c/CURLOPT_HEADERFUNCTION.html */
static size_t
curl_resheader_cb(char *str, size_t size, size_t nmemb, void *p_userdata)
{
  size_t realsize = size * nmemb;
  struct header_pairs *pairs = p_userdata;

  char *ptr;
  if ( !(ptr = strchr(str, ':')) ) { //returns if can't find ':' token match
    return realsize;
  }

  *ptr = '\0'; //replace ':' with '\0' to separate field from value
  
  int ret;
  ret = snprintf(pairs->field[pairs->size], MAX_HEADER_LEN, "%s", str);
  ASSERT_S(ret < MAX_HEADER_LEN, "Out of bounds write attempt");

  if ( !(ptr = strstr(ptr+1, "\r\n")) ) {//returns if can't find CRLF match
    return realsize;
  }

  *ptr = '\0'; //replace CRLF with '\0' to isolate field

  //adjust offset to start of value
  int offset = 1; //offset starts after '\0' separator token
  while (isspace(str[strlen(str) + offset])) {
    ++offset;
  }

  //get the value part from string
  ret = snprintf(pairs->value[pairs->size], MAX_HEADER_LEN, "%s", &str[strlen(str) + offset]);
  ASSERT_S(ret < MAX_HEADER_LEN, "Out of bounds write attempt");

  ++pairs->size; //update header amount of field/value pairs
  ASSERT_S(pairs->size < MAX_HEADER_SIZE, "Out of bounds write attempt");

  return realsize;
}

/* get api response body string
* see: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
static size_t
curl_resbody_cb(char *str, size_t size, size_t nmemb, void *p_userdata)
{
  size_t realsize = size * nmemb;
  struct response_body *body = p_userdata;

  //update response body string size
  char *tmp = realloc(body->str, body->size + realsize + 1);
  ASSERT_S(NULL != tmp, "Out of memory");

  body->str = tmp;
  memcpy(body->str + body->size, str, realsize);
  body->size += realsize;
  body->str[body->size] = '\0';

  return realsize;
}

/* initialize curl's easy handle with some default opt */
static CURL*
custom_easy_init(struct data *api)
{
  CURL *new_ehandle = curl_easy_init();
  ASSERT_S(NULL != new_ehandle, "Out of memory");

  CURLcode ecode;
  /* DEBUG ONLY FUNCTIONS */
  //set debug callback
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGFUNCTION, &Discord_utils_debug_cb));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to settings containing dump files
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGDATA, &api->p_client->settings));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //enable verbose
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_VERBOSE, 1L));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
  /* * * * * * * * * * * */

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
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEDATA, &api->body);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set response header callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERFUNCTION, &curl_resheader_cb);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to response header to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERDATA, &api->pairs);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  return new_ehandle;
}

void
init(struct data *api, char username[], char token[])
{
  api->req_header = reqheader_init();
  api->ehandle = custom_easy_init(api);
}

void
cleanup(struct data *api)
{
  curl_slist_free_all(api->req_header);
  curl_easy_cleanup(api->ehandle);

  if (api->body.str) {
    free(api->body.str);
  }
}

/* set specific http method used for the request */
static void
set_method(struct data *api, enum http_method method, char postfields[])
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
      //set ptr to payload that will be sent via POST/PUT
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_POSTFIELDS,
                               postfields);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
    case PATCH:
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_CUSTOMREQUEST, "PATCH");
      break;
    case PUT:
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_UPLOAD, 1L);
      ecode = curl_easy_setopt(api->ehandle, CURLOPT_POSTFIELDS,
                               postfields);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
    default:
      ERROR("Unknown http method (code: %d)", method);
  }
}

/* set specific url used for request */
static void
set_url(struct data *api, char base_url[], char endpoint[])
{
  char url[MAX_URL_LEN];
  int ret = snprintf(url, sizeof(url), "%s%s", base_url, endpoint);
  ASSERT_S(ret < (int) sizeof(url), "oob of base_url");

  CURLcode ecode = curl_easy_setopt(api->ehandle, CURLOPT_URL, url);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
}

/* perform the request */
static void
perform_request(
  struct data *api,
  void *p_object, 
  load_obj_cb *load_cb,
  char endpoint[])
{
  enum { //possible actions taken after a http response code
    DONE, RETRY, ABORT
  } action;

  //attempt to fetch a bucket handling connections from this endpoint
  struct bucket *bucket = Discord_ratelimit_tryget_bucket(api, endpoint);
  do {
    if (bucket) { //bucket exists, we will check for pending delays
      long long delay_ms = Discord_ratelimit_delay(bucket, true);
      D_PRINT("RATELIMITING (reach bucket's connection threshold):\n\t"
              "\tEndpoint:\t%s\n\t"
              "\tBucket:\t\t%s\n\t"
              "\tWait for:\t%lld ms",
              endpoint, bucket->hash, delay_ms);

      sleep_ms(delay_ms); //sleep for delay amount (if any)
    }


    CURLcode ecode;
    //perform the connection
    ecode = curl_easy_perform(api->ehandle);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    //get response's code
    const enum http_code code;
    ecode = curl_easy_getinfo(api->ehandle, CURLINFO_RESPONSE_CODE, &code);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    //get request's url
    const char *url = NULL;
    ecode = curl_easy_getinfo(api->ehandle, CURLINFO_EFFECTIVE_URL, &url);
    ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

    D_PRINT("Request URL: %s", url);


    const char *reason; //verbose reason of http code
    switch (code) {
    case HTTP_OK:
        reason = "The request was completed succesfully.";
        action = DONE;

        if (p_object && load_cb) {
          (*load_cb)(p_object, api->body.str, api->body.size);
        }

        break;
    case HTTP_CREATED:
        reason = "The entity was created succesfully.";
        action = DONE;
        break;
    case HTTP_NO_CONTENT:
        reason = "The request completed succesfully but returned no content.";
        action = DONE;
        break;
    case HTTP_NOT_MODIFIED:
        reason = "The entity was not modified (no action was taken).";
        action = DONE;
        break;
    case HTTP_BAD_REQUEST:
        reason = "The request was improperly formatted, or the server couldn't understand it.";
        action = ABORT;
        break;
    case HTTP_UNAUTHORIZED:
        reason = "The Authorization header was missing or invalid.";
        action = ABORT;
        break;
    case HTTP_FORBIDDEN:
        reason = "The Authorization token you passed did not have permission to the resource.";
        action = DONE;
        break;
    case HTTP_NOT_FOUND:
        reason = "The resource at the location specified doesn't exist.";
        action = ABORT;
        break;
    case HTTP_METHOD_NOT_ALLOWED:
        reason = "The HTTP method used is not valid for the location specified.";
        action = ABORT;
        break;
    case HTTP_TOO_MANY_REQUESTS:
    /* @todo dealing with ratelimits solely by checking for
     *  HTTP_TOO_MANY REQUESTS is not discord compliant */
     {
        reason = "You got ratelimited.";
        action = RETRY;

        char message[256];
        long long retry_after;

        json_scanf(api->body.str, api->body.size,
                    "[message]%s [retry_after]%lld",
                    message, &retry_after);

        D_NOTOP_PRINT("Ratelimit Message: %s (wait: %lld ms)",
            message, retry_after);

        sleep_ms(retry_after);

        break;
     }
    case HTTP_GATEWAY_UNAVAILABLE:
        reason = "There was not a gateway available to process your request. Wait a bit and retry.";
        action = RETRY;

        sleep_ms(5000); //wait a bit
        break;
    case CURL_NO_RESPONSE:
        reason = "Curl couldn't fetch a HTTP response.";
        action = DONE;
        break;
    default:
        if (code >= 500) {
          reason = "The server had an error processing your request.";
          action = RETRY;
        }
        else {
          reason = "Unknown HTTP method.";
          action = ABORT;
        }

        break;
    }

    switch (action) {
    case DONE:
        //build and updates bucket's rate limiting information
        Discord_ratelimit_build_bucket(api, bucket, endpoint);
    /* fall through */    
    case RETRY:
        D_NOTOP_PRINT("(%d)%s - %s", code, http_code_print(code), reason);

        //reset the size of response body and header pairs for a fresh start
        api->body.size = 0;
        api->pairs.size = 0;

        break;
    case ABORT: default:
        ERROR("(%d)%s - %s", code, http_code_print(code), reason);
    }

  } while (RETRY == action);
}

/* template function for performing requests */
void 
run(
  struct data *api,
  void *p_object,
  load_obj_cb *load_cb,
  char postfields[],
  enum http_method method,
  char endpoint[],
  ...)
{
  //create the url route
  va_list args;
  va_start (args, endpoint);
  char url[MAX_URL_LEN];
  int ret = vsnprintf(url, sizeof(url), endpoint, args);
  ASSERT_S(ret < (int) sizeof(url), "oob write of url");
  va_end(args);

  set_method(api, method, postfields); //set the request method
  set_url(api, url); //set the request URL
  perform_request(api, p_object, load_cb, endpoint); //perform the request
}

} // namespace api
} // namespace v8
} // namespace discord
