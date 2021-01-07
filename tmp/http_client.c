#include <stdlib.h>
#include <string.h>
#include "http_client.h"


void print_response(FILE * fp, struct response * resp) {
  fprintf(fp, "code %d\n", resp->code);
  fprintf(fp, "status %ld\n", resp->status);
  fprintf(fp, "body: %s\n", resp->body);
  fprintf(fp, "body_size: %zd\n", resp->body_size);
  return;
}

static size_t callback(void* contents, size_t size, size_t nmemb, void* userp) {
  struct response * resp = (struct response *) userp;
  size_t real_size = size * nmemb;
  if (real_size) {
    //fprintf(stderr, "receive : %d,  %s\n", real_size, contents);
    if (resp->buffer_size < resp->body_size + real_size + 2) {
      resp->buffer_size *= 2;
      resp->body = realloc(resp->body, resp->buffer_size);
    }
    memcpy(resp->body + resp->body_size, contents, real_size);
    resp->body_size += real_size;
  }
  return real_size;
}

/*
   ~context() {
      if (curl != nullptr) curl_easy_cleanup(curl);
      if (chunk != nullptr) curl_slist_free_all(chunk);
   }
 */
void http_post_ext(struct response * resp,  char *url,
                   struct curl_slist * chunk,
                   char * body, size_t body_size)
{
  CURL * curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url);

  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body_size);

  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, resp);
  resp->code = curl_easy_perform(curl);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resp->status);
  curl_easy_cleanup(curl);
  return;
}

void http_get_ext(struct response * resp,
                  char * url,
                  struct curl_slist * chunk,
                  char * username,
                  char * password)
{
  CURL * curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, resp);

  if (username && password) {
    curl_easy_setopt(curl, CURLOPT_USERNAME, username);
    curl_easy_setopt(curl, CURLOPT_USERPWD, password);
  }

  resp->code = curl_easy_perform(curl);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resp->status);

  resp->content_type = NULL;
  curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &resp->content_type);
  curl_easy_cleanup(curl);
}


static char * app_json_headers[] = {
    "Content-Type: application/json; charset=utf-8",
    "Accept: application/json",
    "User-Agent: curl",
    NULL
};

void http_post(struct response * resp, char * url,
               char * headers[], size_t nheaders,
               char * body, size_t body_size)
{
  struct curl_slist * chunk = NULL;
  for (int i = 0; app_json_headers[i]; i++)
    chunk = curl_slist_append(chunk, app_json_headers[i]);
  for (int i = 0; i < nheaders; i++)
    chunk = curl_slist_append(chunk, headers[i]);
  http_post_ext(resp, url, chunk, body, body_size);
  curl_slist_free_all(chunk);
}

void http_get(struct response * resp,
              char * url,
              char * headers[], size_t nheaders,
              char * username,
              char * password) {
  struct curl_slist * chunk = NULL;
  for (int i = 0; app_json_headers[i]; i++)
    chunk = curl_slist_append(chunk, app_json_headers[i]);
  for (int i = 0; i < nheaders; i++)
    chunk = curl_slist_append(chunk, headers[i]);
  http_get_ext(resp, url, chunk, username, password);
  curl_slist_free_all(chunk);
}