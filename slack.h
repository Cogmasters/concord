#ifndef SLACK_H
#define SLACK_H

#include <stdbool.h>

#include "json-actor-boxed.h"

struct slack; // forward declaration

typedef void (idle_cb)(struct slack *client, char payload[], size_t len);

struct slack* slack_config_init(const char config_file[]);
void slack_cleanup(struct slack *client);

void slack_on_idle(struct slack *client, idle_cb *callback);
void slack_on_hello(struct slack *client, idle_cb *callback);
void slack_on_message(struct slack *client, idle_cb *callback);
void slack_send_message(struct slack *client, char channel[], char text[]);

void slack_rtm_connect(struct slack *client);
void slack_rtm_run(struct slack *client);
void slack_rtm_shutdown(struct slack *client);

void slack_apps_connections_open(struct slack *client);
void slack_socketmode_run(struct slack *client);
void slack_socketmode_shutdown(struct slack *client);

#endif // SLACK_H
