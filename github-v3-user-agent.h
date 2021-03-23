#ifndef GITHUB_V3_UA_H
#define GITHUB_V3_UA_H

#include "user-agent.h"


//namespace github {
//namespace v3 {
//namespace user_agent {

struct github_v3_user_agent_dati {
  struct user_agent_s common;
  char *username;
  char *token;
};

extern void github_v3_user_agent_init(struct github_v3_user_agent_dati *data,
                 char username[],
                 char token[]);

extern void github_v3_user_agent_run(struct github_v3_user_agent_dati *ua,
                struct resp_handle *resp_handle,
                struct sized_buffer *req_body,
                enum http_method http_method,
                char endpoint[],
                ...);

//} // namespace user_agent
//} // namespace v3
//} // namespace github

#endif // GITHUB_V3_UA_H
