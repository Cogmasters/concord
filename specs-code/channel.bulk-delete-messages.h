/* This file is generated from specs/channel.bulk-delete-messages.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#bulk-delete-messages */
/* This is defined at specs/channel.bulk-delete-messages.json:8:22 */
struct discord_channel_bulk_delete_messages_params {
  /* specs/channel.bulk-delete-messages.json:11:20
     '{ "name": "messages", "type":{ "base":"ja_u64", "dec":"ntl" }}'
  */
  ja_u64 **messages;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[1];
    void *record_defined[1];
    void *record_null[1];
  } __M; // metadata
};
extern void discord_channel_bulk_delete_messages_params_cleanup_v(void *p);
extern void discord_channel_bulk_delete_messages_params_cleanup(struct discord_channel_bulk_delete_messages_params *p);
extern void discord_channel_bulk_delete_messages_params_init_v(void *p);
extern void discord_channel_bulk_delete_messages_params_init(struct discord_channel_bulk_delete_messages_params *p);
extern struct discord_channel_bulk_delete_messages_params * discord_channel_bulk_delete_messages_params_alloc();
extern void discord_channel_bulk_delete_messages_params_free_v(void *p);
extern void discord_channel_bulk_delete_messages_params_free(struct discord_channel_bulk_delete_messages_params *p);
extern void discord_channel_bulk_delete_messages_params_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_bulk_delete_messages_params_from_json(char *json, size_t len, struct discord_channel_bulk_delete_messages_params *p);
extern size_t discord_channel_bulk_delete_messages_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_bulk_delete_messages_params_to_json(char *json, size_t len, struct discord_channel_bulk_delete_messages_params *p);
extern size_t discord_channel_bulk_delete_messages_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_bulk_delete_messages_params_to_query(char *json, size_t len, struct discord_channel_bulk_delete_messages_params *p);
extern void discord_channel_bulk_delete_messages_params_list_free_v(void **p);
extern void discord_channel_bulk_delete_messages_params_list_free(struct discord_channel_bulk_delete_messages_params **p);
extern void discord_channel_bulk_delete_messages_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_bulk_delete_messages_params_list_from_json(char *str, size_t len, struct discord_channel_bulk_delete_messages_params ***p);
extern size_t discord_channel_bulk_delete_messages_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_bulk_delete_messages_params_list_to_json(char *str, size_t len, struct discord_channel_bulk_delete_messages_params **p);
