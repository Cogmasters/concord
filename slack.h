#ifndef SLACK_H
#define SLACK_H

#include <stdbool.h>
#include "json-actor-boxed.h"
#include "common.h"
#include "logconf.h"

/* see specs/slack/ for specs */
#include "specs-code/slack/one-specs.h"

#define SLACK_BASE_API_URL "https://slack.com/api"

struct slack; /* forward declaration */

/** @todo generate as specs */
enum slack_sm_types {
  SLACK_SOCKETMODE_TYPE_NONE = 0,
  /* EVENTS API ENUMS */
  SLACK_SOCKETMODE_TYPE_MESSAGE,
  /* INTERACTION ENUMS */
  SLACK_SOCKETMODE_TYPE_BLOCK_ACTIONS,
  SLACK_SOCKETMODE_TYPE_MESSAGE_ACTIONS,
  SLACK_SOCKETMODE_TYPE_VIEW_CLOSED,
  SLACK_SOCKETMODE_TYPE_VIEW_SUBMISSION
};

typedef void (*slack_on_event)(struct slack *client,
                               const char payload[],
                               size_t len);

struct slack *slack_config_init(const char config_file[]);
void slack_cleanup(struct slack *client);

void slack_set_on_idle(struct slack *client, slack_on_event callback);
void slack_set_on_hello(struct slack *client, slack_on_event callback);
void slack_set_on_message(struct slack *client, slack_on_event callback);
void slack_set_on_block_actions(struct slack *client, slack_on_event callback);
void slack_set_on_message_actions(struct slack *client,
                                  slack_on_event callback);
void slack_set_on_view_closed(struct slack *client, slack_on_event callback);
void slack_set_on_view_submission(struct slack *client,
                                  slack_on_event callback);

void slack_run(struct slack *client);

ORCAcode slack_apps_connections_open(struct slack *client,
                                     struct sized_buffer *ret);

ORCAcode slack_auth_test(struct slack *client, struct sized_buffer *ret);

ORCAcode slack_chat_post_message(struct slack *client,
                                 struct slack_chat_post_message_params *params,
                                 struct sized_buffer *ret);

ORCAcode slack_users_info(struct slack *client,
                          struct slack_users_info_params *params,
                          struct sized_buffer *ret);

typedef enum slack_event_scheduler {
  /** this event has been handled */
  SLACK_EVENT_IGNORE,
  /** handle this event in main thread */
  SLACK_EVENT_MAIN_THREAD,
  /** handle this event in a worker thread */
  SLACK_EVENT_WORKER_THREAD
} slack_event_scheduler_t;

typedef slack_event_scheduler_t (*slack_on_scheduler)(
  struct slack *client,
  struct sized_buffer *event_data,
  enum slack_sm_types type);

void slack_set_event_scheduler(struct slack *client,
                               slack_on_scheduler callback);

#endif /* SLACK_H */
