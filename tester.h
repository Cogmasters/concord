#ifndef CEE_H
#define CEE_H

#include "http-common.h"

namespace tester {
namespace user_agent {

struct data {
  struct curl_slist *req_header; //the request header sent to the api
  struct api_resbody_s body; //the api response string
  struct api_header_s pairs; //the key/field pairs response header
  CURL *ehandle; //the curl's easy handle used to perform requests
  char *base_url;
  struct _settings_s settings;
};

extern void init(struct data *api, char *base_url);

extern void run(struct data *api,
                struct resp_handle *handle,
                struct api_resbody_s *body,
                enum http_method http_method,
                char endpoint[],
                ...);

} // namespace user_agent
} // namespace tester

#endif //CEE_H
