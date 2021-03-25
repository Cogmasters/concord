#ifndef GITHUB_V3_ADAPTER_H
#define GITHUB_V3_ADAPTER_H

#include "user-agent.h"

struct github_v3_adapter {
  struct user_agent_s *ua;
  char *username;
  char *token;
};

extern void github_v3_adapter_init(
  struct github_v3_adapter *adapter,
  char username[],
  char token[]);

extern void github_v3_adapter_run(
  struct github_v3_adapter *adapter,
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method,
  char endpoint[],
  ...);

#endif // GITHUB_V3_ADAPTER_H
