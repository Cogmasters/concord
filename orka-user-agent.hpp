#ifndef ORKA_H
#define ORKA_H

#include "http-common.h"

namespace orka {
namespace user_agent {

struct dati {
  struct curl_slist *req_header; //the request header sent to the api
  struct sized_buffer resp_body; //the api response string
  struct api_header_s pairs; //the key/field pairs response header
  CURL *ehandle; //the curl's easy handle used to perform requests
  char *base_url;
  struct _settings_s settings;
};

void init(struct dati *ua, char *base_url);
void cleanup(struct dati *ua);

void vrun(
  struct dati *ua,
  struct resp_handle *handle,
  struct sized_buffer *req_body,
  struct perform_cbs *cbs,
  enum http_method http_method, char endpoint[], va_list ap);

void run(
  struct dati *ua,
  struct resp_handle *handle,
  struct sized_buffer *req_body,
  struct perform_cbs *cbs,
  enum http_method http_method, char endpoint[], ...);

} // namespace user_agent
} // namespace orka




#endif //ORKA_H
