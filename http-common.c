#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "http-common.h"
#include "orka-utils.h"

/* attempt to get value from matching header field */
char*
get_header_value(struct api_header_s *pairs, char header_field[])
{
  for (int i=0; i < pairs->size; ++i) {
    if (STREQ(header_field, pairs->field[i])) {
      return pairs->value[i]; //found header field, return its value
    }
  }

  return NULL; //couldn't find header field
}

char*
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
      CASE_RETURN_STR(HTTP_UNPROCESSABLE_ENTITY);
      CASE_RETURN_STR(HTTP_TOO_MANY_REQUESTS);
      CASE_RETURN_STR(HTTP_GATEWAY_UNAVAILABLE);
  default:
      if (code >= 500) return "5xx SERVER ERROR";

      ERR("Invalid HTTP response code (code: %d)", code);
  }
  return NULL;
}

char*
http_reason_print(enum http_code code)
{
  switch (code) {
  case HTTP_OK:
      return "The request was completed succesfully.";
  case HTTP_CREATED:
      return "The entity was created succesfully.";
  case HTTP_NO_CONTENT:
      return "The request completed succesfully but returned no content.";
  case HTTP_NOT_MODIFIED:
      return "The entity was not modified (no action was taken).";
  case HTTP_BAD_REQUEST:
      return "The request was improperly formatted, or the server couldn't understand it.";
  case HTTP_UNAUTHORIZED:
      return "The Authorization header was missing or invalid.";
  case HTTP_FORBIDDEN:
      return "The Authorization token you passed did not have permission to the resource.";
  case HTTP_NOT_FOUND:
      return "The resource at the location specified doesn't exist.";
  case HTTP_METHOD_NOT_ALLOWED:
      return "The HTTP method used is not valid for the location specified.";
  case HTTP_TOO_MANY_REQUESTS:
      return "You got ratelimited.";
  case HTTP_GATEWAY_UNAVAILABLE:
      return "There was not a gateway available to process your request. Wait a bit and retry.";
  case CURL_NO_RESPONSE:
      return "Curl couldn't fetch a HTTP response.";
  default:
      if (code >= 500) {
        return "The server had an error processing your request.";
      }
      return "Unknown HTTP method.";
  }
}

char*
http_method_print(enum http_method method)
{
  switch(method) {
      CASE_RETURN_STR(HTTP_DELETE);
      CASE_RETURN_STR(HTTP_GET);
      CASE_RETURN_STR(HTTP_POST);
      CASE_RETURN_STR(HTTP_PATCH);
      CASE_RETURN_STR(HTTP_PUT);
  default:
      ERR("Invalid HTTP method (code: %d)", method);
  }
}

/* set specific http method used for the request */
void
set_method(CURL *ehandle, enum http_method method, struct sized_buffer *body)
{
  // resets existing CUSTOMREQUEST
  curl_easy_setopt(ehandle, CURLOPT_CUSTOMREQUEST, NULL);

  CURLcode ecode;
  switch (method) {
  case HTTP_DELETE:
      ecode = curl_easy_setopt(ehandle, CURLOPT_CUSTOMREQUEST, "DELETE");
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
  case HTTP_GET:
      ecode = curl_easy_setopt(ehandle, CURLOPT_HTTPGET, 1L);
      ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
      break;
  case HTTP_POST:
      curl_easy_setopt(ehandle, CURLOPT_POST, 1L);
      //set ptr to payload that will be sent via POST/PUT
      curl_easy_setopt(ehandle, CURLOPT_POSTFIELDS, body->start);
      curl_easy_setopt(ehandle, CURLOPT_POSTFIELDSIZE, body->size);
      break;
  case HTTP_PATCH:
      curl_easy_setopt(ehandle, CURLOPT_CUSTOMREQUEST, "PATCH");
      curl_easy_setopt(ehandle, CURLOPT_POSTFIELDS, body->start);
      curl_easy_setopt(ehandle, CURLOPT_POSTFIELDSIZE, body->size);
      break;
  case HTTP_PUT:
      curl_easy_setopt(ehandle, CURLOPT_CUSTOMREQUEST, "PUT");
      curl_easy_setopt(ehandle, CURLOPT_POSTFIELDS, body->start);
      curl_easy_setopt(ehandle, CURLOPT_POSTFIELDSIZE, body->size);
      break;
  default:
      ERR("Unknown http method (code: %d)", method);
  }
}

void
set_url(CURL *ehandle, char *base_api_url, char endpoint[])
{
  char base_url[MAX_URL_LEN];
  int ret = snprintf(base_url, sizeof(base_url), "%s%s", base_api_url, endpoint);
  ASSERT_S(ret < (int)sizeof(base_url), "Out of bounds write attempt");

  CURLcode ecode = curl_easy_setopt(ehandle, CURLOPT_URL, base_url);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
}

static size_t
curl_resheader_cb(char *str, size_t size, size_t nmemb, void *p_userdata)
{
  size_t realsize = size * nmemb;
  struct api_header_s *pairs = (struct api_header_s *)p_userdata;

  char *ptr;
  if (!(ptr = strchr(str, ':'))) { //returns if can't find ':' token match
    return realsize;
  }

  *ptr = '\0'; //replace ':' with '\0' to separate field from value

  int ret = snprintf(pairs->field[pairs->size], MAX_HEADER_LEN, "%s", str);
  ASSERT_S(ret < MAX_HEADER_LEN, "oob of paris->field");

  if (!(ptr = strstr(ptr + 1, "\r\n"))) {//returns if can't find CRLF match
    return realsize;
  }

  *ptr = '\0'; //replace CRLF with '\0' to isolate field

  //adjust offset to start of value
  int offset = 1; //offset starts after '\0' separator token
  while (isspace(str[strlen(str) + offset])) {
    ++offset;
  }

  //get the value part from string
  ret = snprintf(pairs->value[pairs->size], MAX_HEADER_LEN, "%s",
                 &str[strlen(str) + offset]);
  ASSERT_S(ret < MAX_HEADER_LEN, "oob write attempt");

  ++pairs->size; //update header amount of field/value pairs
  ASSERT_S(pairs->size < MAX_HEADER_SIZE, "oob write of pairs");

  return realsize;
}

/* get api response body string
* see: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
static size_t
curl_resbody_cb(char *str, size_t size, size_t nmemb, void *p_userdata)
{
  size_t realsize = size * nmemb;
  struct sized_buffer *body = (struct sized_buffer *)p_userdata;

  //update response body string size
  char *tmp = (char *)realloc(body->start, body->size + realsize + 1);
  body->start = tmp;
  memcpy(body->start + body->size, str, realsize);
  body->size += realsize;
  body->start[body->size] = '\0';
  return realsize;
}

void
json_dump(const char *text, struct _settings_s *settings, const char *data)
{
  if (NULL == settings->f_json_dump) return;
  FILE *f_dump = settings->f_json_dump;

  char timestr[64] = {0};
  orka_timestamp_str(timestr, sizeof(timestr));

  fprintf(f_dump, "\r\r\r\r%s - %s\n%s\n", text, timestr, data);
  fflush(f_dump);
}

static void
curl_dump(const char *text, FILE *f_dump, unsigned char *ptr, size_t size)
{
  const unsigned int WIDTH = 0x10;

  char timestr[64] = {0};
  orka_timestamp_str(timestr, sizeof(timestr));

  fprintf(f_dump, "\r\r\r\r%s %10.10ld bytes (0x%8.8lx) - %s\n%s\n",
          text, (long)size, (long)size, timestr, ptr);

  for(size_t i=0; i < size; i += WIDTH)
  {
    fprintf(f_dump, "%4.4lx: ", (long)i);

    //show hex to the left
    for(size_t c = 0; c < WIDTH; c++) {
      if(i+c < size)
        fprintf(f_dump, "%02x ", ptr[i+c]);
      else
        fputs("   ", f_dump);
    }

    //show data on the right
    for(size_t c = 0; (c < WIDTH) && (i+c < size); c++) {
      char x = (ptr[i+c] >= 0x20 && ptr[i+c] < 0x80) ? ptr[i+c] : '.';
      fputc(x, f_dump);
    }

    fputc('\n', f_dump); //newline
  }

  fflush(f_dump);
}

int
curl_debug_cb(
  CURL *ehandle,
  curl_infotype type,
  char *data,
  size_t size,
  void *p_userdata)
{
  struct _settings_s *settings = (struct _settings_s *)p_userdata;
  if (NULL == settings->f_curl_dump) return 0;

  FILE *f_dump = settings->f_curl_dump;

  const char *text = NULL;
  switch (type) {
  case CURLINFO_TEXT:
    {
      char timestr[64] = {0};
      orka_timestamp_str(timestr, sizeof(timestr));

      fprintf(f_dump, "\r\r\r\rCURL INFO - %s\n%s\n", timestr, data);
      fflush(f_dump);
    }
  /* fallthrough */
  default:
      return 0;
  case CURLINFO_HEADER_OUT:
      text = "SEND HEADER";
      break;
  case CURLINFO_DATA_OUT:
      text = "SEND DATA";
      break;
  case CURLINFO_SSL_DATA_OUT:
      text = "SEND SSL DATA";
      break;
  case CURLINFO_HEADER_IN:
      text = "RECEIVE HEADER";
      break;
  case CURLINFO_DATA_IN:
      text = "RECEIVE DATA";
      break;
  case CURLINFO_SSL_DATA_IN:
      text = "RECEIVE SSL DATA";
      break;
  }

  curl_dump(text, f_dump, (unsigned char*)data, size);

  return 0;

  (void)ehandle;
}

CURL*
custom_easy_init(struct _settings_s *settings,
                 struct curl_slist *req_header,
                 struct api_header_s *pairs,
                 struct sized_buffer *body)
{
  CURL *new_ehandle = curl_easy_init();

  CURLcode ecode;
  /* DEBUG ONLY FUNCTIONS */
  //set debug callback
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGFUNCTION, curl_debug_cb));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to settings containing dump files
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGDATA, settings));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //enable verbose
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_VERBOSE, 1L));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
  /* * * * * * * * * * * */

  //set ptr to request header we will be using for API communication
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HTTPHEADER, req_header);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //enable follow redirections
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 1L);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set response body callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEFUNCTION,
                           &curl_resbody_cb);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to response body to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEDATA, body);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set response header callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERFUNCTION,
                           &curl_resheader_cb);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to response header to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERDATA, pairs);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  return new_ehandle;
}
