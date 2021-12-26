#ifndef SLACK_INTERNAL_H
#define SLACK_INTERNAL_H

#include <pthread.h>

#include "json-actor.h"
#include "json-actor-boxed.h"

#include "user-agent.h"
#include "websockets.h"
#include "cee-utils.h"

/** @brief Get client from its nested field */
#define CLIENT(ptr, path) CONTAINEROF(ptr, struct slack, path)

struct slack_request_attr {
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

  /** client token-level */
  enum {
    SLACK_TOKEN_BOT = 0,
    SLACK_TOKEN_APP,
  } token_level;

  /** override default content-type */
  char *content_type;
};

struct slack_webapi {
  struct user_agent *ua;
  struct logconf conf;
};

/* ADAPTER PRIVATE FUNCTIONS */
void slack_webapi_init(struct slack_webapi *webapi,
                       struct logconf *conf,
                       struct sized_buffer *token);

void slack_webapi_cleanup(struct slack_webapi *webapi);

ORCAcode slack_webapi_run(struct slack_webapi *webapi,
                          struct slack_request_attr *attr,
                          struct sized_buffer *body,
                          enum http_method method,
                          char endpoint_fmt[],
                          ...);

struct slack_sm {
  struct websockets *ws;
  struct logconf conf;
  CURLM *mhandle;

  bool is_ready;

  /* SOCKETMODE HEARTBEAT STRUCT */
  struct {
    uint64_t tstamp;
    long interval_ms;
  } hbeat;

  /* CALLBACKS STRUCTURE */
  struct {
    /** trigers in every event loop iteration */
    slack_on_event on_idle;
    /** triggers when connections first establishes */
    slack_on_event on_hello;

    /* EVENT API CALLBACKS */
    /** triggers when a message is sent */
    slack_on_event on_message;

    /* INTERACTION CALLBACKS */
    /** triggers when a block_action interaction occurs */
    slack_on_event on_block_actions;
    /** triggers when a message_action interaction occurs */
    slack_on_event on_message_actions;
    /** triggers when a view_closed interaction occurs */
    slack_on_event on_view_closed;
    /** triggers when a view_submission interaction occurs */
    slack_on_event on_view_submission;

    /**
     * Handle context on how each event callback is executed
     * @see slack_set_scheduler() */
    slack_on_scheduler scheduler;
  } cbs;
};

void slack_sm_init(struct slack_sm *sm, struct logconf *conf);
void slack_sm_cleanup(struct slack_sm *sm);
void slack_sm_run(struct slack_sm *sm);

struct slack {
  struct sized_buffer bot_token;
  struct sized_buffer app_token;

  struct slack_webapi webapi;
  struct slack_sm sm;

  struct logconf conf;
};

struct slack_event {
  /** a copy of payload data */
  struct sized_buffer data;
  /** the sm client */
  struct slack_sm *sm;
  char str_type[64];
  enum slack_sm_types type;
  slack_on_event on_event;
};

#endif /* SLACK_INTERNAL_H */
