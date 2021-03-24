/* This file is generated from specs/webhook.edit-webhook-message.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/webhook#edit-webhook-message */
/* This is defined at specs/webhook.edit-webhook-message.json:8:22 */
struct discord_webhook_edit_webhook_message_params {
  /* specs/webhook.edit-webhook-message.json:11:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"name of the webhook(1-2000) chars" }'
  */
  char content[2000+1]; // name of the webhook(1-2000) chars

  /* specs/webhook.edit-webhook-message.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_channel_embed", "dec":"ntl" }, 
          "comment":"array of up to 10 embeds objects" }'
  */
  struct discord_channel_embed **embeds; // array of up to 10 embeds objects

  /* specs/webhook.edit-webhook-message.json:15:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" }, 
          "comment":"allowed mentions for the message" }'
  */
  struct discord_channel_allowed_mentions *allowed_mentions; // allowed mentions for the message

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
extern void discord_webhook_edit_webhook_message_params_cleanup_v(void *p);
extern void discord_webhook_edit_webhook_message_params_cleanup(struct discord_webhook_edit_webhook_message_params *p);
extern void discord_webhook_edit_webhook_message_params_init_v(void *p);
extern void discord_webhook_edit_webhook_message_params_init(struct discord_webhook_edit_webhook_message_params *p);
extern struct discord_webhook_edit_webhook_message_params * discord_webhook_edit_webhook_message_params_alloc();
extern void discord_webhook_edit_webhook_message_params_free_v(void *p);
extern void discord_webhook_edit_webhook_message_params_free(struct discord_webhook_edit_webhook_message_params *p);
extern void discord_webhook_edit_webhook_message_params_from_json_v(char *json, size_t len, void *p);
extern void discord_webhook_edit_webhook_message_params_from_json(char *json, size_t len, struct discord_webhook_edit_webhook_message_params *p);
extern size_t discord_webhook_edit_webhook_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_webhook_edit_webhook_message_params_to_json(char *json, size_t len, struct discord_webhook_edit_webhook_message_params *p);
extern size_t discord_webhook_edit_webhook_message_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_webhook_edit_webhook_message_params_to_query(char *json, size_t len, struct discord_webhook_edit_webhook_message_params *p);
extern void discord_webhook_edit_webhook_message_params_list_free_v(void **p);
extern void discord_webhook_edit_webhook_message_params_list_free(struct discord_webhook_edit_webhook_message_params **p);
extern void discord_webhook_edit_webhook_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_webhook_edit_webhook_message_params_list_from_json(char *str, size_t len, struct discord_webhook_edit_webhook_message_params ***p);
extern size_t discord_webhook_edit_webhook_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_webhook_edit_webhook_message_params_list_to_json(char *str, size_t len, struct discord_webhook_edit_webhook_message_params **p);
