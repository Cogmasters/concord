#ifndef CEE_H
#define CEE_H
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "json-common.h"
#include "json-scanf.h"
#include "http-common.h"


typedef void (load_obj_cb)(void *p_obj, char *str, size_t len);

namespace tester {
namespace user_agent {

struct data {
  struct curl_slist *req_header; //the request header sent to the api
  struct api_resbody_s body; //the api response string
  struct api_header_s pairs; //the key/field pairs response header
  CURL *ehandle; //the curl's easy handle used to perform requests
  char * base_url;
  struct _settings_s settings;
};

extern void init(struct data *api, char * base_url);

extern void run(struct data *api,
                void *p_object,
                load_obj_cb *load_cb,
                struct api_resbody_s * body,
                enum http_method http_method,
                char endpoint[],
                ...);

} // user_agent
} // github
#endif //CEE_H
