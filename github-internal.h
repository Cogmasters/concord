#ifndef GITHUB_INTERNAL_H
#define GITHUB_INTERNAL_H

#include "user-agent.h"
#include "cee-utils.h"
#include "json-actor.h"

struct github_presets {
  char *owner;
  char *username;
  char *token;
  char *repo;
  char *default_branch;
};

struct github_request_attr {
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
};

struct github_adapter {
  /** GITHUB_HTTP logging module */
  struct logconf conf;
  struct user_agent *ua;
};

void github_adapter_init(struct github_adapter *adapter,
                         struct logconf *conf,
                         struct github_presets *presets);

ORCAcode github_adapter_run(struct github_adapter *adapter,
                            struct github_request_attr *attr,
                            struct sized_buffer *body,
                            enum http_method method,
                            char endpoint_fmt[],
                            ...);

struct github {
  struct logconf conf;
  struct github_adapter adapter;
  struct github_presets presets;
};

#endif /* GITHUB_INTERNAL_H */
