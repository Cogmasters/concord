#ifndef REDDIT_H
#define REDDIT_H

#include "user-agent.h"

struct reddit_user_agent {
  struct user_agent_s * common;
  char *base_url;
  char *username;
};

extern void reddit_user_init(struct dati *ua, char *username, char *password);

extern void run(struct reddit_user_agent *ua,
                struct resp_handle *resp_handle,
                struct sized_buffer *req_body,
                enum http_method http_method,
                char endpoint[], ...);

#endif // REDDIT_H
