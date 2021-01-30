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
  char * base_url;
  char * username;
};

extern void init(struct dati * data, char * username, char * password);

extern void run(struct dati * data,
                struct resp_handle * handle,
                struct api_resbody_s * body,
                enum http_method http_method,
                char endpoint[],
                ...);

} // user_agent
} // v3
} // reddit

#endif //REDDIT_V3_UA_H
