#ifndef GITHUB_ADAPTER_H
#define GITHUB_ADAPTER_H

#include "user-agent.h"

struct github_adapter {
  struct user_agent_s *ua;
  char *username;
  char *token;
};

extern void github_adapter_init(
  struct github_adapter *adapter,
  char username[],
  char token[]);

extern void github_adapter_run(
  struct github_adapter *adapter,
  struct resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method,
  char endpoint[],
  ...);

#endif // GITHUB_ADAPTER_H
