#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H
#include <curl/curl.h>

struct response {
  CURLcode code;
  long status;
  char * body;
  size_t buffer_size;
  size_t body_size;
  char * prefix;
  char * content_type;
};

extern void http_get_ext(struct response * resp,
                         char * url,
                         struct curl_slist * chunk,
                         char * username,
                         char * password);

extern void http_post_ext(struct response * resp,
                          char *url,
                          struct curl_slist * chunk,
                          char * body, size_t body_size);


extern void http_post(struct response * resp, char * url,
                      char * headers[], size_t nheaders,
                      char * body, size_t body_size);

extern void http_get(struct response * resp,
                     char * url,
                     char * headers[], size_t nheaders,
                     char * username, char * password);

extern void print_response(FILE * fp, struct response * resp);
#endif // HTTP_CLIENT_H