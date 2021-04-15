#ifndef REDDIT_INTERNAL_H
#define REDDIT_INTERNAL_H


#include "json-actor.h"
#include "json-actor-boxed.h"

#include "logconf.h"
#include "user-agent.h"
#include "websockets.h"
#include "orka-utils.h"

struct reddit_adapter {
  struct user_agent *ua;
  struct reddit *p_client;
};

/* ADAPTER PRIVATE FUNCTIONS */
void reddit_adapter_init(struct reddit_adapter *adapter, struct logconf *config);
void reddit_adapter_cleanup(struct reddit_adapter *adapter);

void reddit_adapter_run(
  struct reddit_adapter *adapter, 
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method, char endpoint[], ...);

struct reddit {
  struct sized_buffer username;
  struct sized_buffer password;
  struct sized_buffer client_id;
  struct sized_buffer client_secret;

  struct reddit_adapter adapter;
  struct logconf config;
};

#endif // REDDIT_INTERNAL_H
