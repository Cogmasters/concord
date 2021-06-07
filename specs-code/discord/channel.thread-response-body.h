/* This file is generated from specs/discord/channel.thread-response-body.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#list-active-threads-response-body */
/* This is defined at specs/discord/channel.thread-response-body.json:8:22 */
struct discord_thread_response_body {
  /* specs/discord/channel.thread-response-body.json:11:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }'
  */
  struct discord_channel **threads;

  /* specs/discord/channel.thread-response-body.json:12:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }'
  */
  struct discord_thread_member **members;

  /* specs/discord/channel.thread-response-body.json:13:20
     '{ "name": "has_more", "type":{ "base":"bool" } }'
  */
  bool has_more;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
extern void discord_thread_response_body_cleanup_v(void *p);
extern void discord_thread_response_body_cleanup(struct discord_thread_response_body *p);
extern void discord_thread_response_body_init_v(void *p);
extern void discord_thread_response_body_init(struct discord_thread_response_body *p);
extern struct discord_thread_response_body * discord_thread_response_body_alloc();
extern void discord_thread_response_body_free_v(void *p);
extern void discord_thread_response_body_free(struct discord_thread_response_body *p);
extern void discord_thread_response_body_from_json_v(char *json, size_t len, void *p);
extern void discord_thread_response_body_from_json(char *json, size_t len, struct discord_thread_response_body *p);
extern size_t discord_thread_response_body_to_json_v(char *json, size_t len, void *p);
extern size_t discord_thread_response_body_to_json(char *json, size_t len, struct discord_thread_response_body *p);
extern size_t discord_thread_response_body_to_query_v(char *json, size_t len, void *p);
extern size_t discord_thread_response_body_to_query(char *json, size_t len, struct discord_thread_response_body *p);
extern void discord_thread_response_body_list_free_v(void **p);
extern void discord_thread_response_body_list_free(struct discord_thread_response_body **p);
extern void discord_thread_response_body_list_from_json_v(char *str, size_t len, void *p);
extern void discord_thread_response_body_list_from_json(char *str, size_t len, struct discord_thread_response_body ***p);
extern size_t discord_thread_response_body_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_thread_response_body_list_to_json(char *str, size_t len, struct discord_thread_response_body **p);
