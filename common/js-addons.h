#include "mujs.h"
#include "user-agent.h"

ORCAcode js_ua_run(js_State *J, struct user_agent *ua, struct sized_buffer *resp_body, int *p_nparam);
