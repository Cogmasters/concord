#ifndef GITHUB_V3_UA_H
#define GITHUB_V3_UA_H

#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "http-common.h"


namespace github {
namespace v3 {
namespace user_agent {

struct dati {
  struct curl_slist *req_header; //the request header sent to the api
  struct sized_buffer resp_body; //the api response string
  struct api_header_s pairs; //the key/field pairs response header
  CURL *ehandle; //the curl's easy handle used to perform requests
  struct _settings_s settings;
};

extern void init(struct dati *data,
                 char username[],
                 char token[]);

extern void run(struct dati *data,
                struct resp_handle *resp_handle,
                struct sized_buffer *req_body,
                enum http_method http_method,
                char endpoint[],
                ...);

} // namespace user_agent
} // namespace v3
} // namespace github

#endif // GITHUB_V3_UA_H
