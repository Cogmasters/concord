#ifndef JS_USER_AGENT_H
#define JS_USER_AGENT_H

void jsua_log(char *fmt, ...);
void jsua_init(js_State *J);

ORCAcode jsua_run(struct js_State *J,
                  struct user_agent *ua,
                  struct ua_info *p_info);

#endif /* JS_USER_AGENT_H */
