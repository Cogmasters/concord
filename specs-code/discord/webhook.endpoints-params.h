/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/webhook.endpoints-params.h
 * @see https://discord.com/developers/docs/resources/webhook
 */


// Create Webhook
// defined at specs/discord/webhook.endpoints-params.json:9:22
/**
 * - Initializer:
 *   - <tt> void discord_create_webhook_params_init(struct discord_create_webhook_params *) </tt>
 * - Cleanup:
 *   - <tt> void discord_create_webhook_params_cleanup(struct discord_create_webhook_params *) </tt>
 *   - <tt> void discord_create_webhook_params_list_free(struct discord_create_webhook_params **) </tt>
 * - JSON Decoder:
 *   - <tt> void discord_create_webhook_params_from_json(char *rbuf, size_t len, struct discord_create_webhook_params **) </tt>
 *   - <tt> void discord_create_webhook_params_list_from_json(char *rbuf, size_t len, struct discord_create_webhook_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> void discord_create_webhook_params_to_json(char *wbuf, size_t len, struct discord_create_webhook_params *) </tt>
 *   - <tt> void discord_create_webhook_params_list_to_json(char *wbuf, size_t len, struct discord_create_webhook_params **) </tt>
 */
struct discord_create_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  char *name; ///< name of the webhook(1-80) chars

  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  char *avatar; ///< base64 image for the default webhook avatar

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};
extern void discord_create_webhook_params_cleanup_v(void *p);
extern void discord_create_webhook_params_cleanup(struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_init_v(void *p);
extern void discord_create_webhook_params_init(struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_webhook_params_from_json(char *json, size_t len, struct discord_create_webhook_params **pp);
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

// Modify Webhook
// defined at specs/discord/webhook.endpoints-params.json:19:22
/**
 * - Initializer:
 *   - <tt> void discord_modify_webhook_params_init(struct discord_modify_webhook_params *) </tt>
 * - Cleanup:
 *   - <tt> void discord_modify_webhook_params_cleanup(struct discord_modify_webhook_params *) </tt>
 *   - <tt> void discord_modify_webhook_params_list_free(struct discord_modify_webhook_params **) </tt>
 * - JSON Decoder:
 *   - <tt> void discord_modify_webhook_params_from_json(char *rbuf, size_t len, struct discord_modify_webhook_params **) </tt>
 *   - <tt> void discord_modify_webhook_params_list_from_json(char *rbuf, size_t len, struct discord_modify_webhook_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> void discord_modify_webhook_params_to_json(char *wbuf, size_t len, struct discord_modify_webhook_params *) </tt>
 *   - <tt> void discord_modify_webhook_params_list_to_json(char *wbuf, size_t len, struct discord_modify_webhook_params **) </tt>
 */
struct discord_modify_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  char *name; ///< name of the webhook(1-80) chars

  /* specs/discord/webhook.endpoints-params.json:23:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  char *avatar; ///< base64 image for the default webhook avatar

  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the new channel id this webhook should be moved to" }' */
  u64_snowflake_t channel_id; ///< the new channel id this webhook should be moved to

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};
extern void discord_modify_webhook_params_cleanup_v(void *p);
extern void discord_modify_webhook_params_cleanup(struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_init_v(void *p);
extern void discord_modify_webhook_params_init(struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_webhook_params_from_json(char *json, size_t len, struct discord_modify_webhook_params **pp);
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

// Execute Webhook
// defined at specs/discord/webhook.endpoints-params.json:30:22
/**
 * - Initializer:
 *   - <tt> void discord_execute_webhook_params_init(struct discord_execute_webhook_params *) </tt>
 * - Cleanup:
 *   - <tt> void discord_execute_webhook_params_cleanup(struct discord_execute_webhook_params *) </tt>
 *   - <tt> void discord_execute_webhook_params_list_free(struct discord_execute_webhook_params **) </tt>
 * - JSON Decoder:
 *   - <tt> void discord_execute_webhook_params_from_json(char *rbuf, size_t len, struct discord_execute_webhook_params **) </tt>
 *   - <tt> void discord_execute_webhook_params_list_from_json(char *rbuf, size_t len, struct discord_execute_webhook_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> void discord_execute_webhook_params_to_json(char *wbuf, size_t len, struct discord_execute_webhook_params *) </tt>
 *   - <tt> void discord_execute_webhook_params_list_to_json(char *wbuf, size_t len, struct discord_execute_webhook_params **) </tt>
 */
struct discord_execute_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:34:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)",
          "required":"one of content, file, embeds"
        }' */
  bool wait; ///< cannot unescape an ill-formed-string 	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that i

  /* specs/discord/webhook.endpoints-params.json:38:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the message contents (up to 2000 characters)",
          "required":false
        }' */
  char *content; ///< the message contents (up to 2000 characters)

  /* specs/discord/webhook.endpoints-params.json:42:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }' */
  char *username; ///< override the default username of the webhook

  /* specs/discord/webhook.endpoints-params.json:46:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }' */
  char *avatar_url; ///< override the default avatar of the webhook

  /* specs/discord/webhook.endpoints-params.json:48:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }' */
  bool tts; ///< true if this is a TTS message

  /* specs/discord/webhook.endpoints-params.json:52:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }' */
  char *file; ///< the contents of the file being sent

  /* specs/discord/webhook.endpoints-params.json:56:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }' */
  struct discord_embed *embeds; ///< embedded rich content

  /* specs/discord/webhook.endpoints-params.json:60:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }' */
  char *payload_json; ///< See message create

  /* specs/discord/webhook.endpoints-params.json:64:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }' */
  struct discord_channel_allowed_mentions *allowed_mentions; ///< allowed mentions for the message

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
/// @endcond
};
extern void discord_execute_webhook_params_cleanup_v(void *p);
extern void discord_execute_webhook_params_cleanup(struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_init_v(void *p);
extern void discord_execute_webhook_params_init(struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_execute_webhook_params_from_json(char *json, size_t len, struct discord_execute_webhook_params **pp);
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

// Edit Webhook Message
// defined at specs/discord/webhook.endpoints-params.json:74:22
/**
 * - Initializer:
 *   - <tt> void discord_edit_webhook_message_params_init(struct discord_edit_webhook_message_params *) </tt>
 * - Cleanup:
 *   - <tt> void discord_edit_webhook_message_params_cleanup(struct discord_edit_webhook_message_params *) </tt>
 *   - <tt> void discord_edit_webhook_message_params_list_free(struct discord_edit_webhook_message_params **) </tt>
 * - JSON Decoder:
 *   - <tt> void discord_edit_webhook_message_params_from_json(char *rbuf, size_t len, struct discord_edit_webhook_message_params **) </tt>
 *   - <tt> void discord_edit_webhook_message_params_list_from_json(char *rbuf, size_t len, struct discord_edit_webhook_message_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> void discord_edit_webhook_message_params_to_json(char *wbuf, size_t len, struct discord_edit_webhook_message_params *) </tt>
 *   - <tt> void discord_edit_webhook_message_params_list_to_json(char *wbuf, size_t len, struct discord_edit_webhook_message_params **) </tt>
 */
struct discord_edit_webhook_message_params {
  /* specs/discord/webhook.endpoints-params.json:77:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars" }' */
  char *content; ///< name of the webhook(1-2000) chars

  /* specs/discord/webhook.endpoints-params.json:78:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects" }' */
  struct discord_embed **embeds; ///< array of up to 10 embeds objects

  /* specs/discord/webhook.endpoints-params.json:79:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message" }' */
  struct discord_channel_allowed_mentions *allowed_mentions; ///< allowed mentions for the message

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};
extern void discord_edit_webhook_message_params_cleanup_v(void *p);
extern void discord_edit_webhook_message_params_cleanup(struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_init_v(void *p);
extern void discord_edit_webhook_message_params_init(struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_webhook_message_params_from_json(char *json, size_t len, struct discord_edit_webhook_message_params **pp);
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
