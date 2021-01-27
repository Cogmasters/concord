#ifndef GITHUB_V3_UA_H
#define GITHUB_V3_UA_H

#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "json-scanf.h"
#include "http-common.h"


namespace github {
namespace v3 {
namespace user_agent {

struct dati {
  struct curl_slist *req_header; //the request header sent to the api
  struct api_resbody_s body; //the api response string
  struct api_header_s pairs; //the key/field pairs response header
  CURL *ehandle; //the curl's easy handle used to perform requests
  struct _settings_s settings;
};

extern void init(struct dati * data,
                 char username[],
                 char token[]);

extern void run(struct dati * data,
                struct resp_handle * handle,
                struct api_resbody_s * body,
                enum http_method http_method,
                char endpoint[],
                ...);

} // user_agent
} // v3
} // github

#endif //GITHUB_V3_UA_H
