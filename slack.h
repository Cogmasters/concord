#ifndef SLACK_H
#define SLACK_H

#include <stdbool.h>
#include "json-actor-boxed.h"
#include "types.h"
#include "logconf.h"

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

typedef enum slack_event_handling_mode (*slack_event_mode_cb)(
  struct slack *client,
  struct sized_buffer *event_data,
  enum slack_sm_types type);

typedef void (*slack_idle_cb)(struct slack *client,
                              const char payload[],
                              const size_t len);

struct slack *slack_config_init(const char config_file[]);
void slack_cleanup(struct slack *client);

enum slack_event_handling_mode {
  /** this event has been handled */
  SLACK_EVENT_IGNORE,
  /** handle this event in main thread */
  SLACK_EVENT_MAIN_THREAD,
  /** handle this event in a child thread */
  SLACK_EVENT_CHILD_THREAD
};

void slack_sm_set_event_handler(struct slack *client, slack_event_mode_cb fn);
void slack_sm_set_on_idle(struct slack *client, slack_idle_cb callback);
void slack_sm_set_on_hello(struct slack *client, slack_idle_cb callback);
void slack_sm_set_on_message(struct slack *client, slack_idle_cb callback);
void slack_sm_set_on_block_actions(struct slack *client,
                                   slack_idle_cb callback);
void slack_sm_set_on_message_actions(struct slack *client,
                                     slack_idle_cb callback);
void slack_sm_set_on_view_closed(struct slack *client, slack_idle_cb callback);
void slack_sm_set_on_view_submission(struct slack *client,
                                     slack_idle_cb callback);

void slack_sm_run(struct slack *client);
void slack_sm_shutdown(struct slack *client);

ORCAcode slack_apps_connections_open(struct slack *client,
                                     struct sized_buffer *p_resp);
ORCAcode slack_auth_test(struct slack *client, struct sized_buffer *p_resp);

/* https://api.slack.com/methods/chat.postMessage */
struct slack_chat_post_message_params {
  char *token;
  char *channel;
  bool as_user;
  /* @todo attachments */
  /* @todo blocks */
  char *container_id;
  char *draft_id;
  char *file_annotation;
  char *icon_emoji;
  char *icon_url;
  bool link_names;
  bool mrkdwn;
  char *parse;
  bool reply_broadcast;
  char *text;
  char *thread_ts;
  bool unfurl_links;
  bool unfurl_media;
  char *username;
};
ORCAcode slack_chat_post_message(struct slack *client,
                                 struct slack_chat_post_message_params *params,
                                 struct sized_buffer *p_resp);

/* https://api.slack.com/methods/users.info */
struct slack_users_info_params {
  char *token;
  char *user;
  bool include_locale;
};
ORCAcode slack_users_info(struct slack *client,
                          struct slack_users_info_params *params,
                          struct sized_buffer *p_resp);

#endif /* SLACK_H */
