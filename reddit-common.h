#ifndef REDDIT_COMMON_H
#define REDDIT_COMMON_H


#include "json-actor.h"
#include "json-actor-boxed.h"

#include "user-agent.h"
#include "websockets.h"
#include "orka-utils.h"

struct reddit_adapter {
  struct user_agent *ua;
  struct reddit *p_client;
};

/* ADAPTER PRIVATE FUNCTIONS */
void reddit_adapter_config_init(struct reddit_adapter *adapter, const char config_file[]);
void reddit_adapter_cleanup(struct reddit_adapter *adapter);

void reddit_adapter_run(
  struct reddit_adapter *adapter, 
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method, char endpoint[], ...);

struct reddit {
  struct reddit_adapter adapter;
};

#endif // REDDIT_COMMON_H
