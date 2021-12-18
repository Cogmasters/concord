#ifndef REDDIT_INTERNAL_H
#define REDDIT_INTERNAL_H

#include "json-actor.h"
#include "json-actor-boxed.h"

#include "user-agent.h"
#include "websockets.h"
#include "cee-utils.h"

struct reddit_request_attr {
  /** the object itself */
  void *obj;
  /** size of `obj` in bytes */
  size_t size;
  /** initialize `obj` fields */
  void (*init)(void *obj);
  /** callback for filling `obj` with JSON values */
  void (*from_json)(char *json, size_t len, void *obj);
  /** perform a cleanup on `obj` */
  void (*cleanup)(void *obj);
  /** override default URL */
  char *base_url;
};

struct reddit_adapter {
  struct logconf conf;
  struct user_agent *ua;
  char *auth;
};

void reddit_adapter_init(struct reddit_adapter *adapter, struct logconf *conf);
void reddit_adapter_cleanup(struct reddit_adapter *adapter);

ORCAcode reddit_adapter_run(struct reddit_adapter *adapter,
                            struct reddit_request_attr *attr,
                            struct sized_buffer *body,
                            enum http_method method,
                            char endpoint[],
                            ...);

struct reddit {
  struct logconf conf;

  struct sized_buffer username;
  struct sized_buffer password;
  struct sized_buffer client_id;
  struct sized_buffer client_secret;

  struct reddit_adapter adapter;
};

#endif /* REDDIT_INTERNAL_H */
