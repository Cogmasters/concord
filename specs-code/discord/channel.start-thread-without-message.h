/* This file is generated from specs/discord/channel.start-thread-without-message.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#start-thread-without-message-json-params */
/* This is defined at specs/discord/channel.start-thread-without-message.json:8:22 */
struct discord_start_thread_without_message_params {
  /* specs/discord/channel.start-thread-without-message.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }'
  */
  char *name;

  /* specs/discord/channel.start-thread-without-message.json:12:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
  int auto_archive_duration;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
};
extern void discord_start_thread_without_message_params_cleanup_v(void *p);
extern void discord_start_thread_without_message_params_cleanup(struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_init_v(void *p);
extern void discord_start_thread_without_message_params_init(struct discord_start_thread_without_message_params *p);
extern struct discord_start_thread_without_message_params * discord_start_thread_without_message_params_alloc();
extern void discord_start_thread_without_message_params_free_v(void *p);
extern void discord_start_thread_without_message_params_free(struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_from_json_v(char *json, size_t len, void *p);
extern void discord_start_thread_without_message_params_from_json(char *json, size_t len, struct discord_start_thread_without_message_params *p);
extern size_t discord_start_thread_without_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_to_json(char *json, size_t len, struct discord_start_thread_without_message_params *p);
extern size_t discord_start_thread_without_message_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_to_query(char *json, size_t len, struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_list_free_v(void **p);
extern void discord_start_thread_without_message_params_list_free(struct discord_start_thread_without_message_params **p);
extern void discord_start_thread_without_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_start_thread_without_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_without_message_params ***p);
extern size_t discord_start_thread_without_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_without_message_params **p);
