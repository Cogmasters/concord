/* This file is generated from specs/webhook.create-webhook.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/webhook#create-webhook */
/* This is defined at specs/webhook.create-webhook.json:8:22 */
struct discord_webhook_create_webhook_params {
  /* specs/webhook.create-webhook.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[80+1]" }, 
          "comment":"name of the webhook(1-80) chars" }'
  */
  char name[80+1]; // name of the webhook(1-80) chars

  /* specs/webhook.create-webhook.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, 
          "inject_if_not":null, 
          "comment":"base64 image for the default webhook avatar" }'
  */
  char *avatar; // base64 image for the default webhook avatar

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
extern void discord_webhook_create_webhook_params_cleanup_v(void *p);
extern void discord_webhook_create_webhook_params_cleanup(struct discord_webhook_create_webhook_params *p);
extern void discord_webhook_create_webhook_params_init_v(void *p);
extern void discord_webhook_create_webhook_params_init(struct discord_webhook_create_webhook_params *p);
extern struct discord_webhook_create_webhook_params * discord_webhook_create_webhook_params_alloc();
extern void discord_webhook_create_webhook_params_free_v(void *p);
extern void discord_webhook_create_webhook_params_free(struct discord_webhook_create_webhook_params *p);
extern void discord_webhook_create_webhook_params_from_json_v(char *json, size_t len, void *p);
extern void discord_webhook_create_webhook_params_from_json(char *json, size_t len, struct discord_webhook_create_webhook_params *p);
extern size_t discord_webhook_create_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_webhook_create_webhook_params_to_json(char *json, size_t len, struct discord_webhook_create_webhook_params *p);
extern size_t discord_webhook_create_webhook_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_webhook_create_webhook_params_to_query(char *json, size_t len, struct discord_webhook_create_webhook_params *p);
extern void discord_webhook_create_webhook_params_list_free_v(void **p);
extern void discord_webhook_create_webhook_params_list_free(struct discord_webhook_create_webhook_params **p);
extern void discord_webhook_create_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_webhook_create_webhook_params_list_from_json(char *str, size_t len, struct discord_webhook_create_webhook_params ***p);
extern size_t discord_webhook_create_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_webhook_create_webhook_params_list_to_json(char *str, size_t len, struct discord_webhook_create_webhook_params **p);
