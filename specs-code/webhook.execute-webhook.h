/* This file is generated from specs/webhook.execute-webhook.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/webhook#execute-webhook */
/* This is defined at specs/webhook.execute-webhook.json:8:22 */
struct discord_execute_webhook_params {
  /* specs/webhook.execute-webhook.json:12:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"name of the webhook(1-80) chars",
          "required":"one of content, file, embeds"
        }'
  */
  bool wait; // name of the webhook(1-80) chars

  /* specs/webhook.execute-webhook.json:16:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"the message contents (up to 2000 characters",
          "required":false
        }'
  */
  char content[2000+1]; // the message contents (up to 2000 characters

  /* specs/webhook.execute-webhook.json:20:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }'
  */
  char *username; // override the default username of the webhook

  /* specs/webhook.execute-webhook.json:24:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }'
  */
  char *avatar_url; // override the default avatar of the webhook

  /* specs/webhook.execute-webhook.json:26:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }'
  */
  bool tts; // true if this is a TTS message

  /* specs/webhook.execute-webhook.json:30:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }'
  */
  char *file; // the contents of the file being sent

  /* specs/webhook.execute-webhook.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_channel_embed", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }'
  */
  struct discord_channel_embed *embeds; // embedded rich content

  /* specs/webhook.execute-webhook.json:38:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }'
  */
  char *payload_json; // See message create

  /* specs/webhook.execute-webhook.json:42:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }'
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
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
};
extern void discord_execute_webhook_params_cleanup_v(void *p);
extern void discord_execute_webhook_params_cleanup(struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_init_v(void *p);
extern void discord_execute_webhook_params_init(struct discord_execute_webhook_params *p);
extern struct discord_execute_webhook_params * discord_execute_webhook_params_alloc();
extern void discord_execute_webhook_params_free_v(void *p);
extern void discord_execute_webhook_params_free(struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_from_json_v(char *json, size_t len, void *p);
extern void discord_execute_webhook_params_from_json(char *json, size_t len, struct discord_execute_webhook_params *p);
extern size_t discord_execute_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_execute_webhook_params_to_json(char *json, size_t len, struct discord_execute_webhook_params *p);
extern size_t discord_execute_webhook_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_execute_webhook_params_to_query(char *json, size_t len, struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_list_free_v(void **p);
extern void discord_execute_webhook_params_list_free(struct discord_execute_webhook_params **p);
extern void discord_execute_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_execute_webhook_params_list_from_json(char *str, size_t len, struct discord_execute_webhook_params ***p);
extern size_t discord_execute_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_execute_webhook_params_list_to_json(char *str, size_t len, struct discord_execute_webhook_params **p);
