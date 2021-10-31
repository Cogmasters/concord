/* This file is generated from specs/discord/channel.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/channel.endpoints-params.h
 * @see https://discord.com/developers/docs/resources/channel
 */


/* Modify Channel */
/* defined at specs/discord/channel.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_channel_params_init(struct discord_modify_channel_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_channel_params_cleanup(struct discord_modify_channel_params *)`
 *     * :code:`void discord_modify_channel_params_list_free(struct discord_modify_channel_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_channel_params_from_json(char *rbuf, size_t len, struct discord_modify_channel_params **)`
 *     * :code:`void discord_modify_channel_params_list_from_json(char *rbuf, size_t len, struct discord_modify_channel_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_channel_params_to_json(char *wbuf, size_t len, struct discord_modify_channel_params *)`
 *     * :code:`void discord_modify_channel_params_list_to_json(char *wbuf, size_t len, struct discord_modify_channel_params **)`
 * @endverbatim
 */
struct discord_modify_channel_params {
  /* specs/discord/channel.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *name;

  /* specs/discord/channel.endpoints-params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *icon;

  /* specs/discord/channel.endpoints-params.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  /* specs/discord/channel.endpoints-params.json:15:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int position;

  /* specs/discord/channel.endpoints-params.json:16:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *topic;

  /* specs/discord/channel.endpoints-params.json:17:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool nsfw;

  /* specs/discord/channel.endpoints-params.json:18:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int rate_limit_per_user;

  /* specs/discord/channel.endpoints-params.json:19:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int bitrate;

  /* specs/discord/channel.endpoints-params.json:20:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int user_limit;

  /* specs/discord/channel.endpoints-params.json:21:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
  struct discord_overwrite **permission_overwrites;

  /* specs/discord/channel.endpoints-params.json:22:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
  u64_snowflake_t parent_id;

  /* specs/discord/channel.endpoints-params.json:23:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *rtc_region;

  /* specs/discord/channel.endpoints-params.json:24:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int video_quality_mode;

  /* specs/discord/channel.endpoints-params.json:25:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool archived;

  /* specs/discord/channel.endpoints-params.json:26:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

  /* specs/discord/channel.endpoints-params.json:27:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool locked;

};
extern void discord_modify_channel_params_cleanup_v(void *p);
extern void discord_modify_channel_params_cleanup(struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_init_v(void *p);
extern void discord_modify_channel_params_init(struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_channel_params_from_json(char *json, size_t len, struct discord_modify_channel_params **pp);
extern size_t discord_modify_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_channel_params_to_json(char *json, size_t len, struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_list_free_v(void **p);
extern void discord_modify_channel_params_list_free(struct discord_modify_channel_params **p);
extern void discord_modify_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_channel_params_list_from_json(char *str, size_t len, struct discord_modify_channel_params ***p);
extern size_t discord_modify_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_channel_params_list_to_json(char *str, size_t len, struct discord_modify_channel_params **p);

/* Create Message */
/* defined at specs/discord/channel.endpoints-params.json:33:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_message_params_init(struct discord_create_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_message_params_cleanup(struct discord_create_message_params *)`
 *     * :code:`void discord_create_message_params_list_free(struct discord_create_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_message_params_from_json(char *rbuf, size_t len, struct discord_create_message_params **)`
 *     * :code:`void discord_create_message_params_list_from_json(char *rbuf, size_t len, struct discord_create_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_message_params_to_json(char *wbuf, size_t len, struct discord_create_message_params *)`
 *     * :code:`void discord_create_message_params_list_to_json(char *wbuf, size_t len, struct discord_create_message_params **)`
 * @endverbatim
 */
struct discord_create_message_params {
  /* specs/discord/channel.endpoints-params.json:36:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
  char *content; /**< the message contents (up to 2000 characters) */

  /* specs/discord/channel.endpoints-params.json:37:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  bool tts; /**< true if this is a TTS message */

  /* specs/discord/channel.endpoints-params.json:38:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
  struct discord_embed **embeds; /**< embedded rich content (up to 6000 characters) */

  /* specs/discord/channel.endpoints-params.json:39:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
  struct discord_embed *embed; /**< embedded rich content, deprecated in favor of embeds */

  /* specs/discord/channel.endpoints-params.json:40:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/channel.endpoints-params.json:41:20
     '{ "name": "message_reference", "type":{ "base":"struct discord_message_reference", "dec":"*" }, "comment":"include to make your message a reply", "inject_if_not":null }' */
  struct discord_message_reference *message_reference; /**< include to make your message a reply */

  /* specs/discord/channel.endpoints-params.json:42:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  struct discord_component **components; /**< the components to include with the message */

  /* specs/discord/channel.endpoints-params.json:43:20
     '{ "name": "sticker_ids", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"ids of up to 3 stickers in the server to send in the message", "inject_if_not":null }' */
  ja_u64 **sticker_ids; /**< ids of up to 3 stickers in the server to send in the message */

  /* specs/discord/channel.endpoints-params.json:44:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attachment objects with filename and description", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attachment objects with filename and description */

};
extern void discord_create_message_params_cleanup_v(void *p);
extern void discord_create_message_params_cleanup(struct discord_create_message_params *p);
extern void discord_create_message_params_init_v(void *p);
extern void discord_create_message_params_init(struct discord_create_message_params *p);
extern void discord_create_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_message_params_from_json(char *json, size_t len, struct discord_create_message_params **pp);
extern size_t discord_create_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_message_params_to_json(char *json, size_t len, struct discord_create_message_params *p);
extern void discord_create_message_params_list_free_v(void **p);
extern void discord_create_message_params_list_free(struct discord_create_message_params **p);
extern void discord_create_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_message_params_list_from_json(char *str, size_t len, struct discord_create_message_params ***p);
extern size_t discord_create_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_message_params_list_to_json(char *str, size_t len, struct discord_create_message_params **p);

/* Get Channel Messages */
/* defined at specs/discord/channel.endpoints-params.json:50:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_get_channel_messages_params_init(struct discord_get_channel_messages_params *)`
 *   * Cleanup:

 *     * :code:`void discord_get_channel_messages_params_cleanup(struct discord_get_channel_messages_params *)`
 *     * :code:`void discord_get_channel_messages_params_list_free(struct discord_get_channel_messages_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_get_channel_messages_params_from_json(char *rbuf, size_t len, struct discord_get_channel_messages_params **)`
 *     * :code:`void discord_get_channel_messages_params_list_from_json(char *rbuf, size_t len, struct discord_get_channel_messages_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_get_channel_messages_params_to_json(char *wbuf, size_t len, struct discord_get_channel_messages_params *)`
 *     * :code:`void discord_get_channel_messages_params_list_to_json(char *wbuf, size_t len, struct discord_get_channel_messages_params **)`
 * @endverbatim
 */
struct discord_get_channel_messages_params {
  /* specs/discord/channel.endpoints-params.json:53:20
     '{ "name": "around", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages around this message ID", "inject_if_not":0 }' */
  u64_snowflake_t around; /**< get messages around this message ID */

  /* specs/discord/channel.endpoints-params.json:54:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages before this message ID", "inject_if_not":0 }' */
  u64_snowflake_t before; /**< get messages before this message ID */

  /* specs/discord/channel.endpoints-params.json:55:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages after this message ID", "inject_if_not":0 }' */
  u64_snowflake_t after; /**< get messages after this message ID */

  /* specs/discord/channel.endpoints-params.json:56:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query", "default_value":50, "comment":"max number of messages to return (1-100)", "inject_if_not":0 }' */
  int limit; /**< max number of messages to return (1-100) */

};
extern void discord_get_channel_messages_params_cleanup_v(void *p);
extern void discord_get_channel_messages_params_cleanup(struct discord_get_channel_messages_params *p);
extern void discord_get_channel_messages_params_init_v(void *p);
extern void discord_get_channel_messages_params_init(struct discord_get_channel_messages_params *p);
extern void discord_get_channel_messages_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_channel_messages_params_from_json(char *json, size_t len, struct discord_get_channel_messages_params **pp);
extern size_t discord_get_channel_messages_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_channel_messages_params_to_json(char *json, size_t len, struct discord_get_channel_messages_params *p);
extern void discord_get_channel_messages_params_list_free_v(void **p);
extern void discord_get_channel_messages_params_list_free(struct discord_get_channel_messages_params **p);
extern void discord_get_channel_messages_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_channel_messages_params_list_from_json(char *str, size_t len, struct discord_get_channel_messages_params ***p);
extern size_t discord_get_channel_messages_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_channel_messages_params_list_to_json(char *str, size_t len, struct discord_get_channel_messages_params **p);

/* Get Reactions */
/* defined at specs/discord/channel.endpoints-params.json:62:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_get_reactions_params_init(struct discord_get_reactions_params *)`
 *   * Cleanup:

 *     * :code:`void discord_get_reactions_params_cleanup(struct discord_get_reactions_params *)`
 *     * :code:`void discord_get_reactions_params_list_free(struct discord_get_reactions_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_get_reactions_params_from_json(char *rbuf, size_t len, struct discord_get_reactions_params **)`
 *     * :code:`void discord_get_reactions_params_list_from_json(char *rbuf, size_t len, struct discord_get_reactions_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_get_reactions_params_to_json(char *wbuf, size_t len, struct discord_get_reactions_params *)`
 *     * :code:`void discord_get_reactions_params_list_to_json(char *wbuf, size_t len, struct discord_get_reactions_params **)`
 * @endverbatim
 */
struct discord_get_reactions_params {
  /* specs/discord/channel.endpoints-params.json:65:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
  u64_snowflake_t after;

  /* specs/discord/channel.endpoints-params.json:66:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
  int limit;

};
extern void discord_get_reactions_params_cleanup_v(void *p);
extern void discord_get_reactions_params_cleanup(struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_init_v(void *p);
extern void discord_get_reactions_params_init(struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_reactions_params_from_json(char *json, size_t len, struct discord_get_reactions_params **pp);
extern size_t discord_get_reactions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_reactions_params_to_json(char *json, size_t len, struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_list_free_v(void **p);
extern void discord_get_reactions_params_list_free(struct discord_get_reactions_params **p);
extern void discord_get_reactions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_reactions_params_list_from_json(char *str, size_t len, struct discord_get_reactions_params ***p);
extern size_t discord_get_reactions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_reactions_params_list_to_json(char *str, size_t len, struct discord_get_reactions_params **p);

/* Edit Channel Permissions */
/* defined at specs/discord/channel.endpoints-params.json:72:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_channel_permissions_params_init(struct discord_edit_channel_permissions_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_channel_permissions_params_cleanup(struct discord_edit_channel_permissions_params *)`
 *     * :code:`void discord_edit_channel_permissions_params_list_free(struct discord_edit_channel_permissions_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_channel_permissions_params_from_json(char *rbuf, size_t len, struct discord_edit_channel_permissions_params **)`
 *     * :code:`void discord_edit_channel_permissions_params_list_from_json(char *rbuf, size_t len, struct discord_edit_channel_permissions_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_channel_permissions_params_to_json(char *wbuf, size_t len, struct discord_edit_channel_permissions_params *)`
 *     * :code:`void discord_edit_channel_permissions_params_list_to_json(char *wbuf, size_t len, struct discord_edit_channel_permissions_params **)`
 * @endverbatim
 */
struct discord_edit_channel_permissions_params {
  /* specs/discord/channel.endpoints-params.json:75:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_bitwise_permission_flags"}, "comment":"permission bit set" }' */
  enum discord_bitwise_permission_flags allow; /**< permission bit set */

  /* specs/discord/channel.endpoints-params.json:76:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_bitwise_permission_flags"}, "comment":"permission bit set" }' */
  enum discord_bitwise_permission_flags deny; /**< permission bit set */

  /* specs/discord/channel.endpoints-params.json:77:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

};
extern void discord_edit_channel_permissions_params_cleanup_v(void *p);
extern void discord_edit_channel_permissions_params_cleanup(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_init_v(void *p);
extern void discord_edit_channel_permissions_params_init(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_channel_permissions_params_from_json(char *json, size_t len, struct discord_edit_channel_permissions_params **pp);
extern size_t discord_edit_channel_permissions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_to_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_list_free_v(void **p);
extern void discord_edit_channel_permissions_params_list_free(struct discord_edit_channel_permissions_params **p);
extern void discord_edit_channel_permissions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_channel_permissions_params_list_from_json(char *str, size_t len, struct discord_edit_channel_permissions_params ***p);
extern size_t discord_edit_channel_permissions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_list_to_json(char *str, size_t len, struct discord_edit_channel_permissions_params **p);

/* Edit Message */
/* defined at specs/discord/channel.endpoints-params.json:83:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_edit_message_params_init(struct discord_edit_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_edit_message_params_cleanup(struct discord_edit_message_params *)`
 *     * :code:`void discord_edit_message_params_list_free(struct discord_edit_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_edit_message_params_from_json(char *rbuf, size_t len, struct discord_edit_message_params **)`
 *     * :code:`void discord_edit_message_params_list_from_json(char *rbuf, size_t len, struct discord_edit_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_message_params_to_json(char *wbuf, size_t len, struct discord_edit_message_params *)`
 *     * :code:`void discord_edit_message_params_list_to_json(char *wbuf, size_t len, struct discord_edit_message_params **)`
 * @endverbatim
 */
struct discord_edit_message_params {
  /* specs/discord/channel.endpoints-params.json:86:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
  char *content; /**< the message contents (up to 2000 characters) */

  /* specs/discord/channel.endpoints-params.json:87:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
  struct discord_embed **embeds; /**< embedded rich content (up to 6000 characters) */

  /* specs/discord/channel.endpoints-params.json:88:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
  struct discord_embed *embed; /**< embedded rich content, deprecated in favor of embeds */

  /* specs/discord/channel.endpoints-params.json:89:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_message_flags" }, "comment":"edit the flags of a message", "inject_if_not":0 }' */
  enum discord_message_flags flags; /**< edit the flags of a message */

  /* specs/discord/channel.endpoints-params.json:90:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* specs/discord/channel.endpoints-params.json:91:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

  /* specs/discord/channel.endpoints-params.json:92:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  struct discord_component **components; /**< the components to include with the message */

};
extern void discord_edit_message_params_cleanup_v(void *p);
extern void discord_edit_message_params_cleanup(struct discord_edit_message_params *p);
extern void discord_edit_message_params_init_v(void *p);
extern void discord_edit_message_params_init(struct discord_edit_message_params *p);
extern void discord_edit_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_edit_message_params_from_json(char *json, size_t len, struct discord_edit_message_params **pp);
extern size_t discord_edit_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_message_params_to_json(char *json, size_t len, struct discord_edit_message_params *p);
extern void discord_edit_message_params_list_free_v(void **p);
extern void discord_edit_message_params_list_free(struct discord_edit_message_params **p);
extern void discord_edit_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_message_params_list_from_json(char *str, size_t len, struct discord_edit_message_params ***p);
extern size_t discord_edit_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_message_params_list_to_json(char *str, size_t len, struct discord_edit_message_params **p);

/* Follow News Channel */
/* defined at specs/discord/channel.endpoints-params.json:98:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_follow_news_channel_params_init(struct discord_follow_news_channel_params *)`
 *   * Cleanup:

 *     * :code:`void discord_follow_news_channel_params_cleanup(struct discord_follow_news_channel_params *)`
 *     * :code:`void discord_follow_news_channel_params_list_free(struct discord_follow_news_channel_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_follow_news_channel_params_from_json(char *rbuf, size_t len, struct discord_follow_news_channel_params **)`
 *     * :code:`void discord_follow_news_channel_params_list_from_json(char *rbuf, size_t len, struct discord_follow_news_channel_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_follow_news_channel_params_to_json(char *wbuf, size_t len, struct discord_follow_news_channel_params *)`
 *     * :code:`void discord_follow_news_channel_params_list_to_json(char *wbuf, size_t len, struct discord_follow_news_channel_params **)`
 * @endverbatim
 */
struct discord_follow_news_channel_params {
  /* specs/discord/channel.endpoints-params.json:101:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  u64_snowflake_t webhook_channel_id;

};
extern void discord_follow_news_channel_params_cleanup_v(void *p);
extern void discord_follow_news_channel_params_cleanup(struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_init_v(void *p);
extern void discord_follow_news_channel_params_init(struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_follow_news_channel_params_from_json(char *json, size_t len, struct discord_follow_news_channel_params **pp);
extern size_t discord_follow_news_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_follow_news_channel_params_to_json(char *json, size_t len, struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_list_free_v(void **p);
extern void discord_follow_news_channel_params_list_free(struct discord_follow_news_channel_params **p);
extern void discord_follow_news_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_follow_news_channel_params_list_from_json(char *str, size_t len, struct discord_follow_news_channel_params ***p);
extern size_t discord_follow_news_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_follow_news_channel_params_list_to_json(char *str, size_t len, struct discord_follow_news_channel_params **p);

/* Create Channel Invite */
/* defined at specs/discord/channel.endpoints-params.json:107:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_channel_invite_params_init(struct discord_create_channel_invite_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_channel_invite_params_cleanup(struct discord_create_channel_invite_params *)`
 *     * :code:`void discord_create_channel_invite_params_list_free(struct discord_create_channel_invite_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_channel_invite_params_from_json(char *rbuf, size_t len, struct discord_create_channel_invite_params **)`
 *     * :code:`void discord_create_channel_invite_params_list_from_json(char *rbuf, size_t len, struct discord_create_channel_invite_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_channel_invite_params_to_json(char *wbuf, size_t len, struct discord_create_channel_invite_params *)`
 *     * :code:`void discord_create_channel_invite_params_list_to_json(char *wbuf, size_t len, struct discord_create_channel_invite_params **)`
 * @endverbatim
 */
struct discord_create_channel_invite_params {
  /* specs/discord/channel.endpoints-params.json:110:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  int max_age;

  /* specs/discord/channel.endpoints-params.json:111:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  int max_uses;

  /* specs/discord/channel.endpoints-params.json:112:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
  bool temporary;

  /* specs/discord/channel.endpoints-params.json:113:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
  bool unique;

  /* specs/discord/channel.endpoints-params.json:114:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
  int target_type;

  /* specs/discord/channel.endpoints-params.json:115:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  u64_snowflake_t target_user_id;

  /* specs/discord/channel.endpoints-params.json:116:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  u64_snowflake_t target_application_id;

};
extern void discord_create_channel_invite_params_cleanup_v(void *p);
extern void discord_create_channel_invite_params_cleanup(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_init_v(void *p);
extern void discord_create_channel_invite_params_init(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_channel_invite_params_from_json(char *json, size_t len, struct discord_create_channel_invite_params **pp);
extern size_t discord_create_channel_invite_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_channel_invite_params_to_json(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_list_free_v(void **p);
extern void discord_create_channel_invite_params_list_free(struct discord_create_channel_invite_params **p);
extern void discord_create_channel_invite_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_channel_invite_params_list_from_json(char *str, size_t len, struct discord_create_channel_invite_params ***p);
extern size_t discord_create_channel_invite_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_channel_invite_params_list_to_json(char *str, size_t len, struct discord_create_channel_invite_params **p);

/* Group DM Add Recipient */
/* defined at specs/discord/channel.endpoints-params.json:122:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params *)`
 *   * Cleanup:

 *     * :code:`void discord_group_dm_add_recipient_params_cleanup(struct discord_group_dm_add_recipient_params *)`
 *     * :code:`void discord_group_dm_add_recipient_params_list_free(struct discord_group_dm_add_recipient_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_group_dm_add_recipient_params_from_json(char *rbuf, size_t len, struct discord_group_dm_add_recipient_params **)`
 *     * :code:`void discord_group_dm_add_recipient_params_list_from_json(char *rbuf, size_t len, struct discord_group_dm_add_recipient_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_group_dm_add_recipient_params_to_json(char *wbuf, size_t len, struct discord_group_dm_add_recipient_params *)`
 *     * :code:`void discord_group_dm_add_recipient_params_list_to_json(char *wbuf, size_t len, struct discord_group_dm_add_recipient_params **)`
 * @endverbatim
 */
struct discord_group_dm_add_recipient_params {
  /* specs/discord/channel.endpoints-params.json:125:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
  char *access_token;

  /* specs/discord/channel.endpoints-params.json:126:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

};
extern void discord_group_dm_add_recipient_params_cleanup_v(void *p);
extern void discord_group_dm_add_recipient_params_cleanup(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_init_v(void *p);
extern void discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_group_dm_add_recipient_params_from_json(char *json, size_t len, struct discord_group_dm_add_recipient_params **pp);
extern size_t discord_group_dm_add_recipient_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_to_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_list_free_v(void **p);
extern void discord_group_dm_add_recipient_params_list_free(struct discord_group_dm_add_recipient_params **p);
extern void discord_group_dm_add_recipient_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_group_dm_add_recipient_params_list_from_json(char *str, size_t len, struct discord_group_dm_add_recipient_params ***p);
extern size_t discord_group_dm_add_recipient_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_list_to_json(char *str, size_t len, struct discord_group_dm_add_recipient_params **p);

/* Start Thread with Message */
/* defined at specs/discord/channel.endpoints-params.json:132:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_start_thread_with_message_params_init(struct discord_start_thread_with_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_start_thread_with_message_params_cleanup(struct discord_start_thread_with_message_params *)`
 *     * :code:`void discord_start_thread_with_message_params_list_free(struct discord_start_thread_with_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_start_thread_with_message_params_from_json(char *rbuf, size_t len, struct discord_start_thread_with_message_params **)`
 *     * :code:`void discord_start_thread_with_message_params_list_from_json(char *rbuf, size_t len, struct discord_start_thread_with_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_start_thread_with_message_params_to_json(char *wbuf, size_t len, struct discord_start_thread_with_message_params *)`
 *     * :code:`void discord_start_thread_with_message_params_list_to_json(char *wbuf, size_t len, struct discord_start_thread_with_message_params **)`
 * @endverbatim
 */
struct discord_start_thread_with_message_params {
  /* specs/discord/channel.endpoints-params.json:135:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *name;

  /* specs/discord/channel.endpoints-params.json:136:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

};
extern void discord_start_thread_with_message_params_cleanup_v(void *p);
extern void discord_start_thread_with_message_params_cleanup(struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_init_v(void *p);
extern void discord_start_thread_with_message_params_init(struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_start_thread_with_message_params_from_json(char *json, size_t len, struct discord_start_thread_with_message_params **pp);
extern size_t discord_start_thread_with_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_with_message_params_to_json(char *json, size_t len, struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_list_free_v(void **p);
extern void discord_start_thread_with_message_params_list_free(struct discord_start_thread_with_message_params **p);
extern void discord_start_thread_with_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_start_thread_with_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_with_message_params ***p);
extern size_t discord_start_thread_with_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_start_thread_with_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_with_message_params **p);

/* Start Thread without Message */
/* defined at specs/discord/channel.endpoints-params.json:142:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_start_thread_without_message_params_init(struct discord_start_thread_without_message_params *)`
 *   * Cleanup:

 *     * :code:`void discord_start_thread_without_message_params_cleanup(struct discord_start_thread_without_message_params *)`
 *     * :code:`void discord_start_thread_without_message_params_list_free(struct discord_start_thread_without_message_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_start_thread_without_message_params_from_json(char *rbuf, size_t len, struct discord_start_thread_without_message_params **)`
 *     * :code:`void discord_start_thread_without_message_params_list_from_json(char *rbuf, size_t len, struct discord_start_thread_without_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_start_thread_without_message_params_to_json(char *wbuf, size_t len, struct discord_start_thread_without_message_params *)`
 *     * :code:`void discord_start_thread_without_message_params_list_to_json(char *wbuf, size_t len, struct discord_start_thread_without_message_params **)`
 * @endverbatim
 */
struct discord_start_thread_without_message_params {
  /* specs/discord/channel.endpoints-params.json:145:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
  char *name;

  /* specs/discord/channel.endpoints-params.json:146:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

  /* specs/discord/channel.endpoints-params.json:147:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
  enum discord_channel_types type;

};
extern void discord_start_thread_without_message_params_cleanup_v(void *p);
extern void discord_start_thread_without_message_params_cleanup(struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_init_v(void *p);
extern void discord_start_thread_without_message_params_init(struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_start_thread_without_message_params_from_json(char *json, size_t len, struct discord_start_thread_without_message_params **pp);
extern size_t discord_start_thread_without_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_to_json(char *json, size_t len, struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_list_free_v(void **p);
extern void discord_start_thread_without_message_params_list_free(struct discord_start_thread_without_message_params **p);
extern void discord_start_thread_without_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_start_thread_without_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_without_message_params ***p);
extern size_t discord_start_thread_without_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_without_message_params **p);

/* List Active Threads */
/* defined at specs/discord/channel.endpoints-params.json:153:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_thread_response_body_init(struct discord_thread_response_body *)`
 *   * Cleanup:

 *     * :code:`void discord_thread_response_body_cleanup(struct discord_thread_response_body *)`
 *     * :code:`void discord_thread_response_body_list_free(struct discord_thread_response_body **)`
 *   * JSON Decoder:

 *     * :code:`void discord_thread_response_body_from_json(char *rbuf, size_t len, struct discord_thread_response_body **)`
 *     * :code:`void discord_thread_response_body_list_from_json(char *rbuf, size_t len, struct discord_thread_response_body ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_thread_response_body_to_json(char *wbuf, size_t len, struct discord_thread_response_body *)`
 *     * :code:`void discord_thread_response_body_list_to_json(char *wbuf, size_t len, struct discord_thread_response_body **)`
 * @endverbatim
 */
struct discord_thread_response_body {
  /* specs/discord/channel.endpoints-params.json:156:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
  struct discord_channel **threads;

  /* specs/discord/channel.endpoints-params.json:157:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
  struct discord_thread_member **members;

  /* specs/discord/channel.endpoints-params.json:158:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
  bool has_more;

};
extern void discord_thread_response_body_cleanup_v(void *p);
extern void discord_thread_response_body_cleanup(struct discord_thread_response_body *p);
extern void discord_thread_response_body_init_v(void *p);
extern void discord_thread_response_body_init(struct discord_thread_response_body *p);
extern void discord_thread_response_body_from_json_v(char *json, size_t len, void *pp);
extern void discord_thread_response_body_from_json(char *json, size_t len, struct discord_thread_response_body **pp);
extern size_t discord_thread_response_body_to_json_v(char *json, size_t len, void *p);
extern size_t discord_thread_response_body_to_json(char *json, size_t len, struct discord_thread_response_body *p);
extern void discord_thread_response_body_list_free_v(void **p);
extern void discord_thread_response_body_list_free(struct discord_thread_response_body **p);
extern void discord_thread_response_body_list_from_json_v(char *str, size_t len, void *p);
extern void discord_thread_response_body_list_from_json(char *str, size_t len, struct discord_thread_response_body ***p);
extern size_t discord_thread_response_body_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_thread_response_body_list_to_json(char *str, size_t len, struct discord_thread_response_body **p);
