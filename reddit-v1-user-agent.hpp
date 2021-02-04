#ifndef REDDIT_V3_UA_H
#define REDDIT_V3_UA_H

#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "json-scanf.h"
#include "http-common.h"
#include "orka-user-agent.hpp"

namespace reddit {
namespace v1 {
namespace user_agent {

struct dati {
  orka::user_agent::dati ua;
  char *base_url;
  char *username;
};

extern void init(struct dati *data, char *username, char *password);

extern void run(struct dati *api,
                struct resp_handle *resp_handle,
                struct sized_buffer *req_body,
                enum http_method http_method,
                char endpoint[],
                ...);

} // namespace user_agent
} // namespace v1
} // namespace reddit

#endif // REDDIT_V3_UA_H
