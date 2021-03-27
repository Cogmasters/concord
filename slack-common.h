#ifndef SLACK_COMMON_H
#define SLACK_COMMON_H

#include "user-agent.h"
#include "orka-utils.h"

struct slack_adapter {
  struct user_agent_s *ua;
};

void slack_adapter_init(struct slack_adapter *adapter, const char token[], const char config_file[]);
void slack_adapter_cleanup(struct slack_adapter *adapter);

void slack_adapter_run(
  struct slack_adapter *adapter, 
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method, char endpoint[], ...);

#endif // SLACK_COMMON_H

