/* This file is generated from specs/discord/channel.list-joined-private-archived-threads.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#list-joined-private-archived-threads */
/* This is defined at specs/discord/channel.list-joined-private-archived-threads.json:8:22 */
struct discord_list_joined_private_archived_threads_params {
  /* specs/discord/channel.list-joined-private-archived-threads.json:11:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "inject_if_not":0}'
  */
  u64_unix_ms_t before;

  /* specs/discord/channel.list-joined-private-archived-threads.json:12:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
  int limit;

  /* specs/discord/channel.list-joined-private-archived-threads.json:13:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }'
  */
  struct discord_channel **threads;

  /* specs/discord/channel.list-joined-private-archived-threads.json:14:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }'
  */
  struct discord_thread_member **members;

  /* specs/discord/channel.list-joined-private-archived-threads.json:15:20
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
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
};
extern void discord_list_joined_private_archived_threads_params_cleanup_v(void *p);
extern void discord_list_joined_private_archived_threads_params_cleanup(struct discord_list_joined_private_archived_threads_params *p);
extern void discord_list_joined_private_archived_threads_params_init_v(void *p);
extern void discord_list_joined_private_archived_threads_params_init(struct discord_list_joined_private_archived_threads_params *p);
extern struct discord_list_joined_private_archived_threads_params * discord_list_joined_private_archived_threads_params_alloc();
extern void discord_list_joined_private_archived_threads_params_free_v(void *p);
extern void discord_list_joined_private_archived_threads_params_free(struct discord_list_joined_private_archived_threads_params *p);
extern void discord_list_joined_private_archived_threads_params_from_json_v(char *json, size_t len, void *p);
extern void discord_list_joined_private_archived_threads_params_from_json(char *json, size_t len, struct discord_list_joined_private_archived_threads_params *p);
extern size_t discord_list_joined_private_archived_threads_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_list_joined_private_archived_threads_params_to_json(char *json, size_t len, struct discord_list_joined_private_archived_threads_params *p);
extern size_t discord_list_joined_private_archived_threads_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_list_joined_private_archived_threads_params_to_query(char *json, size_t len, struct discord_list_joined_private_archived_threads_params *p);
extern void discord_list_joined_private_archived_threads_params_list_free_v(void **p);
extern void discord_list_joined_private_archived_threads_params_list_free(struct discord_list_joined_private_archived_threads_params **p);
extern void discord_list_joined_private_archived_threads_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_list_joined_private_archived_threads_params_list_from_json(char *str, size_t len, struct discord_list_joined_private_archived_threads_params ***p);
extern size_t discord_list_joined_private_archived_threads_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_list_joined_private_archived_threads_params_list_to_json(char *str, size_t len, struct discord_list_joined_private_archived_threads_params **p);
