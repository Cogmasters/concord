#ifndef GITHUB_INTERNAL_H
#define GITHUB_INTERNAL_H

#include "user-agent.h"

struct github_presets {
  char *owner;
  char *username;
  char *token;
  char *repo;
  char *default_branch;
};

struct github_adapter {
  struct user_agent *ua;
};

void github_adapter_init(struct github_adapter *adapter,
                         struct logconf *conf,
                         struct github_presets *presets);

ORCAcode github_adapter_run(struct github_adapter *adapter,
                            struct ua_resp_handle *resp_handle,
                            struct sized_buffer *req_body,
                            enum http_method http_method,
                            char endpoint_fmt[],
                            ...);

struct github {
  struct logconf conf;
  struct github_adapter adapter;
  struct github_presets presets;
};

#endif /* GITHUB_INTERNAL_H */
