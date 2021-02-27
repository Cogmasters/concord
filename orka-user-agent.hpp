#ifndef ORKA_H
#define ORKA_H

#include "http-common.h"

namespace orka {
namespace user_agent {

typedef ua_handle_s dati;

void init(dati *ua, char *base_url);
void cleanup(dati *ua);

void vrun(
  dati *ua,
  struct resp_handle *handle,
  struct sized_buffer *req_body,
  struct perform_cbs *cbs,
  enum http_method http_method, char endpoint[], va_list ap);

void run(
  dati *ua,
  struct resp_handle *handle,
  struct sized_buffer *req_body,
  struct perform_cbs *cbs,
  enum http_method http_method, char endpoint[], ...);

} // namespace user_agent
} // namespace orka




#endif //ORKA_H
