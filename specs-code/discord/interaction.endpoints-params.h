/* This file is generated from specs/discord/interaction.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/interaction.endpoints-params.h
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding
 */


/* Edit Original Interaction Response */
/* defined at specs/discord/interaction.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_original_interaction_response_params_init(struct discord_edit_original_interaction_response_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_original_interaction_response_params_cleanup(struct discord_edit_original_interaction_response_params *)`
 *     * :code:`void discord_edit_original_interaction_response_params_list_free(struct discord_edit_original_interaction_response_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_original_interaction_response_params_from_json(char *rbuf, size_t len, struct discord_edit_original_interaction_response_params **)`
 *     * :code:`void discord_edit_original_interaction_response_params_list_from_json(char *rbuf, size_t len, struct discord_edit_original_interaction_response_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_original_interaction_response_params_to_json(char *wbuf, size_t len, struct discord_edit_original_interaction_response_params *)`
 *     * :code:`void discord_edit_original_interaction_response_params_list_to_json(char *wbuf, size_t len, struct discord_edit_original_interaction_response_params **)`
 * @endverbatim
 */
struct discord_edit_original_interaction_response_params {
  /* specs/discord/interaction.endpoints-params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  char *content; /**< name of the webhook(1-2000) chars */

  /* specs/discord/interaction.endpoints-params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  struct discord_embed **embeds; /**< array of up to 10 embeds objects */

  /* specs/discord/interaction.endpoints-params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
  char *payload_json; /**< JSON encoded body of non-file params (multipart/form-data only) */

  /* specs/discord/interaction.endpoints-params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/interaction.endpoints-params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

  /* specs/discord/interaction.endpoints-params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  struct discord_component **components; /**< the components to include with the message */

};
extern void discord_edit_original_interaction_response_params_cleanup_v(void *p);
extern void discord_edit_original_interaction_response_params_cleanup(struct discord_edit_original_interaction_response_params *p);
extern void discord_edit_original_interaction_response_params_init_v(void *p);
extern void discord_edit_original_interaction_response_params_init(struct discord_edit_original_interaction_response_params *p);
extern void discord_edit_original_interaction_response_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_original_interaction_response_params_from_json(char *json, size_t len, struct discord_edit_original_interaction_response_params **pp);
extern size_t discord_edit_original_interaction_response_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_original_interaction_response_params_to_json(char *json, size_t len, struct discord_edit_original_interaction_response_params *p);
extern void discord_edit_original_interaction_response_params_list_free_v(void **p);
extern void discord_edit_original_interaction_response_params_list_free(struct discord_edit_original_interaction_response_params **p);
extern void discord_edit_original_interaction_response_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_original_interaction_response_params_list_from_json(char *str, size_t len, struct discord_edit_original_interaction_response_params ***p);
extern size_t discord_edit_original_interaction_response_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_original_interaction_response_params_list_to_json(char *str, size_t len, struct discord_edit_original_interaction_response_params **p);

/* Create Followup Message */
/* defined at specs/discord/interaction.endpoints-params.json:23:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_followup_message_params_init(struct discord_create_followup_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_followup_message_params_cleanup(struct discord_create_followup_message_params *)`
 *     * :code:`void discord_create_followup_message_params_list_free(struct discord_create_followup_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_followup_message_params_from_json(char *rbuf, size_t len, struct discord_create_followup_message_params **)`
 *     * :code:`void discord_create_followup_message_params_list_from_json(char *rbuf, size_t len, struct discord_create_followup_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_followup_message_params_to_json(char *wbuf, size_t len, struct discord_create_followup_message_params *)`
 *     * :code:`void discord_create_followup_message_params_list_to_json(char *wbuf, size_t len, struct discord_create_followup_message_params **)`
 * @endverbatim
 */
struct discord_create_followup_message_params {
  /* specs/discord/interaction.endpoints-params.json:27:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)", "default_value":true }' */
  bool wait; /**< cannot unescape an ill-formed-string 	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that i */

  /* specs/discord/interaction.endpoints-params.json:28:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */
  u64_snowflake_t thread_id; /**< Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived */

  /* specs/discord/interaction.endpoints-params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
  char *content; /**< the message contents (up to 2000 characters) */

  /* specs/discord/interaction.endpoints-params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
  char *username; /**< override the default username of the webhook */

  /* specs/discord/interaction.endpoints-params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
  char *avatar_url; /**< override the default avatar of the webhook */

  /* specs/discord/interaction.endpoints-params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  bool tts; /**< true if this is a TTS message */

  /* specs/discord/interaction.endpoints-params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

  /* specs/discord/interaction.endpoints-params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
  struct discord_embed *embeds; /**< embedded rich content */

  /* specs/discord/interaction.endpoints-params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
  char *payload_json; /**< JSON encoded body of non-file params */

  /* specs/discord/interaction.endpoints-params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/interaction.endpoints-params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
  struct discord_component **components; /**< the components to include with the message */

  /* specs/discord/interaction.endpoints-params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
  int flags; /**< can be set to 64 to send a ephemeral message */

};
extern void discord_create_followup_message_params_cleanup_v(void *p);
extern void discord_create_followup_message_params_cleanup(struct discord_create_followup_message_params *p);
extern void discord_create_followup_message_params_init_v(void *p);
extern void discord_create_followup_message_params_init(struct discord_create_followup_message_params *p);
extern void discord_create_followup_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_followup_message_params_from_json(char *json, size_t len, struct discord_create_followup_message_params **pp);
extern size_t discord_create_followup_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_followup_message_params_to_json(char *json, size_t len, struct discord_create_followup_message_params *p);
extern void discord_create_followup_message_params_list_free_v(void **p);
extern void discord_create_followup_message_params_list_free(struct discord_create_followup_message_params **p);
extern void discord_create_followup_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_followup_message_params_list_from_json(char *str, size_t len, struct discord_create_followup_message_params ***p);
extern size_t discord_create_followup_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_followup_message_params_list_to_json(char *str, size_t len, struct discord_create_followup_message_params **p);

/* Edit Followup Message */
/* defined at specs/discord/interaction.endpoints-params.json:44:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_followup_message_params_init(struct discord_edit_followup_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_followup_message_params_cleanup(struct discord_edit_followup_message_params *)`
 *     * :code:`void discord_edit_followup_message_params_list_free(struct discord_edit_followup_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_followup_message_params_from_json(char *rbuf, size_t len, struct discord_edit_followup_message_params **)`
 *     * :code:`void discord_edit_followup_message_params_list_from_json(char *rbuf, size_t len, struct discord_edit_followup_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_followup_message_params_to_json(char *wbuf, size_t len, struct discord_edit_followup_message_params *)`
 *     * :code:`void discord_edit_followup_message_params_list_to_json(char *wbuf, size_t len, struct discord_edit_followup_message_params **)`
 * @endverbatim
 */
struct discord_edit_followup_message_params {
  /* specs/discord/interaction.endpoints-params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  char *content; /**< name of the webhook(1-2000) chars */

  /* specs/discord/interaction.endpoints-params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  struct discord_embed **embeds; /**< array of up to 10 embeds objects */

  /* specs/discord/interaction.endpoints-params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
  char *payload_json; /**< JSON encoded body of non-file params (multipart/form-data only) */

  /* specs/discord/interaction.endpoints-params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/interaction.endpoints-params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

  /* specs/discord/interaction.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  struct discord_component **components; /**< the components to include with the message */

};
extern void discord_edit_followup_message_params_cleanup_v(void *p);
extern void discord_edit_followup_message_params_cleanup(struct discord_edit_followup_message_params *p);
extern void discord_edit_followup_message_params_init_v(void *p);
extern void discord_edit_followup_message_params_init(struct discord_edit_followup_message_params *p);
extern void discord_edit_followup_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_followup_message_params_from_json(char *json, size_t len, struct discord_edit_followup_message_params **pp);
extern size_t discord_edit_followup_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_followup_message_params_to_json(char *json, size_t len, struct discord_edit_followup_message_params *p);
extern void discord_edit_followup_message_params_list_free_v(void **p);
extern void discord_edit_followup_message_params_list_free(struct discord_edit_followup_message_params **p);
extern void discord_edit_followup_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_followup_message_params_list_from_json(char *str, size_t len, struct discord_edit_followup_message_params ***p);
extern size_t discord_edit_followup_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_followup_message_params_list_to_json(char *str, size_t len, struct discord_edit_followup_message_params **p);
