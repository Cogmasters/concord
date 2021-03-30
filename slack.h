#ifndef SLACK_H
#define SLACK_H

#include <stdbool.h>

#include "json-actor-boxed.h"

struct slack* slack_config_init(const char config_file[]);
void slack_cleanup(struct slack *client);

void slack_apps_connections_open(struct slack *client);

#endif // SLACK_H
