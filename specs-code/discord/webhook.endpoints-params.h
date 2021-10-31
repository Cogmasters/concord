/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/webhook.endpoints-params.h
 * @see https://discord.com/developers/docs/resources/webhook
 */


/* Create Webhook */
/* defined at specs/discord/webhook.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_webhook_params_init(struct discord_create_webhook_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_webhook_params_cleanup(struct discord_create_webhook_params *)`
 *     * :code:`void discord_create_webhook_params_list_free(struct discord_create_webhook_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_webhook_params_from_json(char *rbuf, size_t len, struct discord_create_webhook_params **)`
 *     * :code:`void discord_create_webhook_params_list_from_json(char *rbuf, size_t len, struct discord_create_webhook_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_webhook_params_to_json(char *wbuf, size_t len, struct discord_create_webhook_params *)`
 *     * :code:`void discord_create_webhook_params_list_to_json(char *wbuf, size_t len, struct discord_create_webhook_params **)`
 * @endverbatim
 */
struct discord_create_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  char *name; /**< name of the webhook(1-80) chars */

  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  char *avatar; /**< base64 image for the default webhook avatar */

};
extern void discord_create_webhook_params_cleanup_v(void *p);
extern void discord_create_webhook_params_cleanup(struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_init_v(void *p);
extern void discord_create_webhook_params_init(struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_webhook_params_from_json(char *json, size_t len, struct discord_create_webhook_params **pp);
extern size_t discord_create_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_webhook_params_to_json(char *json, size_t len, struct discord_create_webhook_params *p);
extern void discord_create_webhook_params_list_free_v(void **p);
extern void discord_create_webhook_params_list_free(struct discord_create_webhook_params **p);
extern void discord_create_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_webhook_params_list_from_json(char *str, size_t len, struct discord_create_webhook_params ***p);
extern size_t discord_create_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_webhook_params_list_to_json(char *str, size_t len, struct discord_create_webhook_params **p);

/* Modify Webhook */
/* defined at specs/discord/webhook.endpoints-params.json:19:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_webhook_params_init(struct discord_modify_webhook_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_webhook_params_cleanup(struct discord_modify_webhook_params *)`
 *     * :code:`void discord_modify_webhook_params_list_free(struct discord_modify_webhook_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_webhook_params_from_json(char *rbuf, size_t len, struct discord_modify_webhook_params **)`
 *     * :code:`void discord_modify_webhook_params_list_from_json(char *rbuf, size_t len, struct discord_modify_webhook_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_webhook_params_to_json(char *wbuf, size_t len, struct discord_modify_webhook_params *)`
 *     * :code:`void discord_modify_webhook_params_list_to_json(char *wbuf, size_t len, struct discord_modify_webhook_params **)`
 * @endverbatim
 */
struct discord_modify_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
  char *name; /**< name of the webhook(1-80) chars */

  /* specs/discord/webhook.endpoints-params.json:23:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  char *avatar; /**< base64 image for the default webhook avatar */

  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment":"the new channel id this webhook should be moved to" }' */
  u64_snowflake_t channel_id; /**< the new channel id this webhook should be moved to */

};
extern void discord_modify_webhook_params_cleanup_v(void *p);
extern void discord_modify_webhook_params_cleanup(struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_init_v(void *p);
extern void discord_modify_webhook_params_init(struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_webhook_params_from_json(char *json, size_t len, struct discord_modify_webhook_params **pp);
extern size_t discord_modify_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_webhook_params_to_json(char *json, size_t len, struct discord_modify_webhook_params *p);
extern void discord_modify_webhook_params_list_free_v(void **p);
extern void discord_modify_webhook_params_list_free(struct discord_modify_webhook_params **p);
extern void discord_modify_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_webhook_params_list_from_json(char *str, size_t len, struct discord_modify_webhook_params ***p);
extern size_t discord_modify_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_webhook_params_list_to_json(char *str, size_t len, struct discord_modify_webhook_params **p);

/* Modify Webhook with Token */
/* defined at specs/discord/webhook.endpoints-params.json:30:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_webhook_with_token_params_init(struct discord_modify_webhook_with_token_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_webhook_with_token_params_cleanup(struct discord_modify_webhook_with_token_params *)`
 *     * :code:`void discord_modify_webhook_with_token_params_list_free(struct discord_modify_webhook_with_token_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_webhook_with_token_params_from_json(char *rbuf, size_t len, struct discord_modify_webhook_with_token_params **)`
 *     * :code:`void discord_modify_webhook_with_token_params_list_from_json(char *rbuf, size_t len, struct discord_modify_webhook_with_token_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_webhook_with_token_params_to_json(char *wbuf, size_t len, struct discord_modify_webhook_with_token_params *)`
 *     * :code:`void discord_modify_webhook_with_token_params_list_to_json(char *wbuf, size_t len, struct discord_modify_webhook_with_token_params **)`
 * @endverbatim
 */
struct discord_modify_webhook_with_token_params {
  /* specs/discord/webhook.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
  char *name; /**< name of the webhook(1-80) chars */

  /* specs/discord/webhook.endpoints-params.json:34:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  char *avatar; /**< base64 image for the default webhook avatar */

};
extern void discord_modify_webhook_with_token_params_cleanup_v(void *p);
extern void discord_modify_webhook_with_token_params_cleanup(struct discord_modify_webhook_with_token_params *p);
extern void discord_modify_webhook_with_token_params_init_v(void *p);
extern void discord_modify_webhook_with_token_params_init(struct discord_modify_webhook_with_token_params *p);
extern void discord_modify_webhook_with_token_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_webhook_with_token_params_from_json(char *json, size_t len, struct discord_modify_webhook_with_token_params **pp);
extern size_t discord_modify_webhook_with_token_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_webhook_with_token_params_to_json(char *json, size_t len, struct discord_modify_webhook_with_token_params *p);
extern void discord_modify_webhook_with_token_params_list_free_v(void **p);
extern void discord_modify_webhook_with_token_params_list_free(struct discord_modify_webhook_with_token_params **p);
extern void discord_modify_webhook_with_token_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_webhook_with_token_params_list_from_json(char *str, size_t len, struct discord_modify_webhook_with_token_params ***p);
extern size_t discord_modify_webhook_with_token_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_webhook_with_token_params_list_to_json(char *str, size_t len, struct discord_modify_webhook_with_token_params **p);

/* Execute Webhook */
/* defined at specs/discord/webhook.endpoints-params.json:40:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_execute_webhook_params_init(struct discord_execute_webhook_params *)`
 *   * Cleanup:

 *     * :code:`void discord_execute_webhook_params_cleanup(struct discord_execute_webhook_params *)`
 *     * :code:`void discord_execute_webhook_params_list_free(struct discord_execute_webhook_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_execute_webhook_params_from_json(char *rbuf, size_t len, struct discord_execute_webhook_params **)`
 *     * :code:`void discord_execute_webhook_params_list_from_json(char *rbuf, size_t len, struct discord_execute_webhook_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_execute_webhook_params_to_json(char *wbuf, size_t len, struct discord_execute_webhook_params *)`
 *     * :code:`void discord_execute_webhook_params_list_to_json(char *wbuf, size_t len, struct discord_execute_webhook_params **)`
 * @endverbatim
 */
struct discord_execute_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:44:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)" }' */
  bool wait; /**< cannot unescape an ill-formed-string 	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that i */

  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */
  u64_snowflake_t thread_id; /**< Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived */

  /* specs/discord/webhook.endpoints-params.json:46:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
  char *content; /**< the message contents (up to 2000 characters) */

  /* specs/discord/webhook.endpoints-params.json:47:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
  char *username; /**< override the default username of the webhook */

  /* specs/discord/webhook.endpoints-params.json:48:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
  char *avatar_url; /**< override the default avatar of the webhook */

  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  bool tts; /**< true if this is a TTS message */

  /* specs/discord/webhook.endpoints-params.json:50:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
  struct discord_embed *embeds; /**< embedded rich content */

  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/webhook.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
  struct discord_component **components; /**< the components to include with the message */

  /* specs/discord/webhook.endpoints-params.json:53:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

};
extern void discord_execute_webhook_params_cleanup_v(void *p);
extern void discord_execute_webhook_params_cleanup(struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_init_v(void *p);
extern void discord_execute_webhook_params_init(struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_execute_webhook_params_from_json(char *json, size_t len, struct discord_execute_webhook_params **pp);
extern size_t discord_execute_webhook_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_execute_webhook_params_to_json(char *json, size_t len, struct discord_execute_webhook_params *p);
extern void discord_execute_webhook_params_list_free_v(void **p);
extern void discord_execute_webhook_params_list_free(struct discord_execute_webhook_params **p);
extern void discord_execute_webhook_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_execute_webhook_params_list_from_json(char *str, size_t len, struct discord_execute_webhook_params ***p);
extern size_t discord_execute_webhook_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_execute_webhook_params_list_to_json(char *str, size_t len, struct discord_execute_webhook_params **p);

/* Edit Webhook Message */
/* defined at specs/discord/webhook.endpoints-params.json:59:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_webhook_message_params_init(struct discord_edit_webhook_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_webhook_message_params_cleanup(struct discord_edit_webhook_message_params *)`
 *     * :code:`void discord_edit_webhook_message_params_list_free(struct discord_edit_webhook_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_webhook_message_params_from_json(char *rbuf, size_t len, struct discord_edit_webhook_message_params **)`
 *     * :code:`void discord_edit_webhook_message_params_list_from_json(char *rbuf, size_t len, struct discord_edit_webhook_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_webhook_message_params_to_json(char *wbuf, size_t len, struct discord_edit_webhook_message_params *)`
 *     * :code:`void discord_edit_webhook_message_params_list_to_json(char *wbuf, size_t len, struct discord_edit_webhook_message_params **)`
 * @endverbatim
 */
struct discord_edit_webhook_message_params {
  /* specs/discord/webhook.endpoints-params.json:62:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  char *content; /**< name of the webhook(1-2000) chars */

  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  struct discord_embed **embeds; /**< array of up to 10 embeds objects */

  /* specs/discord/webhook.endpoints-params.json:64:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/webhook.endpoints-params.json:65:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

  /* specs/discord/webhook.endpoints-params.json:66:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  struct discord_component **components; /**< the components to include with the message */

};
extern void discord_edit_webhook_message_params_cleanup_v(void *p);
extern void discord_edit_webhook_message_params_cleanup(struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_init_v(void *p);
extern void discord_edit_webhook_message_params_init(struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_webhook_message_params_from_json(char *json, size_t len, struct discord_edit_webhook_message_params **pp);
extern size_t discord_edit_webhook_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_webhook_message_params_to_json(char *json, size_t len, struct discord_edit_webhook_message_params *p);
extern void discord_edit_webhook_message_params_list_free_v(void **p);
extern void discord_edit_webhook_message_params_list_free(struct discord_edit_webhook_message_params **p);
extern void discord_edit_webhook_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_webhook_message_params_list_from_json(char *str, size_t len, struct discord_edit_webhook_message_params ***p);
extern size_t discord_edit_webhook_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_webhook_message_params_list_to_json(char *str, size_t len, struct discord_edit_webhook_message_params **p);
