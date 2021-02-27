#ifndef GITHUB_V3_UA_H
#define GITHUB_V3_UA_H

#include "orka-user-agent.hpp"


namespace github {
namespace v3 {
namespace user_agent {

struct dati {
  orka::user_agent::dati common;
  char *username;
  char *token;
};

extern void init(struct dati *data,
                 char username[],
                 char token[]);

extern void run(struct dati *ua,
                struct resp_handle *resp_handle,
                struct sized_buffer *req_body,
                enum http_method http_method,
                char endpoint[],
                ...);

} // namespace user_agent
} // namespace v3
} // namespace github

#endif // GITHUB_V3_UA_H
