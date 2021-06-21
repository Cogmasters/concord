/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/webhook.endpoints-params.h
 * @author cee-studio
 * @date 21 Jun 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/webhook
 */


/**
 * @brief Create Webhook
 *
 * @see https://discord.com/developers/docs/resources/webhook#create-webhook
 * @note defined at specs/discord/webhook.endpoints-params.json:10:22
 */
struct discord_create_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  char *name; // name of the webhook(1-80) chars

  /* specs/discord/webhook.endpoints-params.json:14:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
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
extern void discord_create_webhook_params_cleanup_v(void *p);
extern void discord_create_webhook_params_cleanup(struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_init_v(void *p);
extern void discord_create_webhook_params_init(struct discord_create_webhook_params *p);
extern struct discord_create_webhook_params * discord_create_webhook_params_alloc();
extern void discord_create_webhook_params_free_v(void *p);
extern void discord_create_webhook_params_free(struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_webhook_params_from_json(char *json, size_t len, struct discord_create_webhook_params *p);
extern size_t discord_create_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_webhook_params_to_json(char *json, size_t len, struct discord_create_webhook_params *p);
extern size_t discord_create_webhook_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_webhook_params_to_query(char *json, size_t len, struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_list_free_v(void **p);
extern void discord_create_webhook_params_list_free(struct discord_create_webhook_params **p);
extern void discord_create_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_webhook_params_list_from_json(char *str, size_t len, struct discord_create_webhook_params ***p);
extern size_t discord_create_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_webhook_params_list_to_json(char *str, size_t len, struct discord_create_webhook_params **p);

/**
 * @brief Modify Webhook
 *
 * @see https://discord.com/developers/docs/resources/webhook#modify-webhook
 * @note defined at specs/discord/webhook.endpoints-params.json:21:22
 */
struct discord_modify_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  char *name; // name of the webhook(1-80) chars

  /* specs/discord/webhook.endpoints-params.json:25:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  char *avatar; // base64 image for the default webhook avatar

  /* specs/discord/webhook.endpoints-params.json:26:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the new channel id this webhook should be moved to" }' */
  u64_snowflake_t channel_id; // the new channel id this webhook should be moved to

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
extern void discord_modify_webhook_params_cleanup_v(void *p);
extern void discord_modify_webhook_params_cleanup(struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_init_v(void *p);
extern void discord_modify_webhook_params_init(struct discord_modify_webhook_params *p);
extern struct discord_modify_webhook_params * discord_modify_webhook_params_alloc();
extern void discord_modify_webhook_params_free_v(void *p);
extern void discord_modify_webhook_params_free(struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_webhook_params_from_json(char *json, size_t len, struct discord_modify_webhook_params *p);
extern size_t discord_modify_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_webhook_params_to_json(char *json, size_t len, struct discord_modify_webhook_params *p);
extern size_t discord_modify_webhook_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_webhook_params_to_query(char *json, size_t len, struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_list_free_v(void **p);
extern void discord_modify_webhook_params_list_free(struct discord_modify_webhook_params **p);
extern void discord_modify_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_webhook_params_list_from_json(char *str, size_t len, struct discord_modify_webhook_params ***p);
extern size_t discord_modify_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_webhook_params_list_to_json(char *str, size_t len, struct discord_modify_webhook_params **p);

/**
 * @brief Execute Webhook
 *
 * @see https://discord.com/developers/docs/resources/webhook#execute-webhook
 * @note defined at specs/discord/webhook.endpoints-params.json:33:22
 */
struct discord_execute_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:37:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)",
          "required":"one of content, file, embeds"
        }' */
  bool wait; // cannot unescape an ill-formed-string 	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that i

  /* specs/discord/webhook.endpoints-params.json:41:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the message contents (up to 2000 characters)",
          "required":false
        }' */
  char *content; // the message contents (up to 2000 characters)

  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }' */
  char *username; // override the default username of the webhook

  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }' */
  char *avatar_url; // override the default avatar of the webhook

  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }' */
  bool tts; // true if this is a TTS message

  /* specs/discord/webhook.endpoints-params.json:55:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }' */
  char *file; // the contents of the file being sent

  /* specs/discord/webhook.endpoints-params.json:59:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }' */
  struct discord_embed *embeds; // embedded rich content

  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }' */
  char *payload_json; // See message create

  /* specs/discord/webhook.endpoints-params.json:67:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }' */
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

/**
 * @brief Edit Webhook Message
 *
 * @see https://discord.com/developers/docs/resources/webhook#edit-webhook-message
 * @note defined at specs/discord/webhook.endpoints-params.json:78:22
 */
struct discord_edit_webhook_message_params {
  /* specs/discord/webhook.endpoints-params.json:81:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars" }' */
  char *content; // name of the webhook(1-2000) chars

  /* specs/discord/webhook.endpoints-params.json:82:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects" }' */
  struct discord_embed **embeds; // array of up to 10 embeds objects

  /* specs/discord/webhook.endpoints-params.json:83:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message" }' */
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
extern void discord_edit_webhook_message_params_cleanup_v(void *p);
extern void discord_edit_webhook_message_params_cleanup(struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_init_v(void *p);
extern void discord_edit_webhook_message_params_init(struct discord_edit_webhook_message_params *p);
extern struct discord_edit_webhook_message_params * discord_edit_webhook_message_params_alloc();
extern void discord_edit_webhook_message_params_free_v(void *p);
extern void discord_edit_webhook_message_params_free(struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_from_json_v(char *json, size_t len, void *p);
extern void discord_edit_webhook_message_params_from_json(char *json, size_t len, struct discord_edit_webhook_message_params *p);
extern size_t discord_edit_webhook_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_webhook_message_params_to_json(char *json, size_t len, struct discord_edit_webhook_message_params *p);
extern size_t discord_edit_webhook_message_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_edit_webhook_message_params_to_query(char *json, size_t len, struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_list_free_v(void **p);
extern void discord_edit_webhook_message_params_list_free(struct discord_edit_webhook_message_params **p);
extern void discord_edit_webhook_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_webhook_message_params_list_from_json(char *str, size_t len, struct discord_edit_webhook_message_params ***p);
extern size_t discord_edit_webhook_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_webhook_message_params_list_to_json(char *str, size_t len, struct discord_edit_webhook_message_params **p);
