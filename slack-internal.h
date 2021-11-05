#ifndef SLACK_INTERNAL_H
#define SLACK_INTERNAL_H

#include <pthread.h>

#include "json-actor.h"
#include "json-actor-boxed.h"

#include "logconf.h" /* struct logconf */
#include "user-agent.h"
#include "websockets.h"
#include "cee-utils.h"

struct slack_webapi {
  struct user_agent *ua;
  struct logconf conf;

  struct slack *p_client;
};

/* ADAPTER PRIVATE FUNCTIONS */
void slack_webapi_init(struct slack_webapi *webapi,
                       struct logconf *conf,
                       struct sized_buffer *token);
void slack_webapi_cleanup(struct slack_webapi *webapi);

ORCAcode slack_webapi_run(struct slack_webapi *webapi,
                          struct sized_buffer *p_resp_body,
                          struct sized_buffer *req_body,
                          enum http_method http_method,
                          char endpoint_fmt[],
                          ...);

struct slack_sm {
  struct websockets *ws;
  struct logconf conf;

  bool is_ready;

  /* SOCKETMODE HEARTBEAT STRUCT */
  struct {
    uint64_t tstamp;
    long interval_ms;
  } hbeat;

  /* CALLBACKS STRUCTURE */
  struct {
    /** trigers in every event loop iteration */
    slack_idle_cb on_idle;
    /** triggers when connections first establishes */
    slack_idle_cb on_hello;
    /* EVENT API CALLBACKS */
    /** triggers when a message is sent */
    slack_idle_cb on_message;
    /* INTERACTION CALLBACKS */
    /** triggers when a block_action interaction occurs */
    slack_idle_cb on_block_actions;
    /** triggers when a message_action interaction occurs */
    slack_idle_cb on_message_actions;
    /** triggers when a view_closed interaction occurs */
    slack_idle_cb on_view_closed;
    /** triggers when a view_submission interaction occurs */
    slack_idle_cb on_view_submission;
  } cbs;

  /** Handle context on how each event callback is executed @see
   * slack_set_event_handler() */
  slack_event_mode_cb event_handler;

  struct slack *p_client;
};

/* SOCKET MODE PRIVATE FUNCTIONS */
void slack_sm_init(struct slack_sm *sm, struct logconf *conf);
void slack_sm_cleanup(struct slack_sm *sm);

struct slack {
  struct sized_buffer bot_token;
  struct sized_buffer app_token;

  struct slack_webapi webapi;
  struct slack_sm sm;

  struct logconf conf;
};

struct slack_event_cxt {
  /** the thread id */
  pthread_t tid;
  /** a copy of payload data */
  struct sized_buffer data;
  /** the sm client */
  struct slack_sm *p_sm;
  char str_type[64];
  enum slack_sm_types type;
  void (*on_event)(struct slack_sm *sm, struct sized_buffer *data);
  bool is_main_thread;
};

#endif /* SLACK_INTERNAL_H */
