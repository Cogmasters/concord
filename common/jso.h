void jso_log(char *fmt, ...);
void jso_init(js_State *J);

ORCAcode jso_ua_run(struct js_State *J, struct user_agent *ua, struct ua_info *p_info, int *p_nparam);
