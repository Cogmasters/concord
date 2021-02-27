#ifndef REDDIT_V3_UA_H
#define REDDIT_V3_UA_H

#include "user-agent.h"

namespace reddit {
namespace v1 {
namespace user_agent {

struct dati {
  struct user_agent_s common;
  char *base_url;
  char *username;
};

extern void init(struct dati *ua, char *username, char *password);

extern void run(struct dati *ua,
                struct resp_handle *resp_handle,
                struct sized_buffer *req_body,
                enum http_method http_method,
                char endpoint[], ...);

} // namespace user_agent
} // namespace v1
} // namespace reddit

#endif // REDDIT_V3_UA_H
