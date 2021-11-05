#ifndef REDDIT_INTERNAL_H
#define REDDIT_INTERNAL_H

#include "json-actor.h"
#include "json-actor-boxed.h"

#include "user-agent.h"
#include "websockets.h"
#include "cee-utils.h"

#define BASE_API_URL   "https://www.reddit.com"
#define BASE_OAUTH_URL "https://oauth.reddit.com"

struct reddit_adapter {
  struct user_agent *ua;
  struct logconf conf;
  struct reddit *p_client;
};

/* ADAPTER PRIVATE FUNCTIONS */
void reddit_adapter_init(struct reddit_adapter *adapter, struct logconf *conf);
void reddit_adapter_cleanup(struct reddit_adapter *adapter);

ORCAcode reddit_adapter_run(struct reddit_adapter *adapter,
                            struct sized_buffer *resp_body,
                            struct sized_buffer *req_body,
                            enum http_method http_method,
                            char endpoint[],
                            ...);

struct reddit {
  struct sized_buffer username;
  struct sized_buffer password;
  struct sized_buffer client_id;
  struct sized_buffer client_secret;

  struct reddit_adapter adapter;
  struct logconf conf;
};

#endif /* REDDIT_INTERNAL_H */
