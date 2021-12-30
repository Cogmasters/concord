/* This file is generated from discord/channel.params.json, Please don't edit it. */
/**
 * @file specs-code/discord/channel.params.h
 * @see https://discord.com/developers/docs/resources/channel
 */


/* Modify Channel */
/* defined at discord/channel.params.json:9:22 */
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

 *     * :code:`void discord_modify_channel_params_from_json(char *rbuf, size_t len, struct discord_modify_channel_params *)`
 *     * :code:`void discord_modify_channel_params_list_from_json(char *rbuf, size_t len, struct discord_modify_channel_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_channel_params_to_json(char *wbuf, size_t len, struct discord_modify_channel_params *)`
 *     * :code:`void discord_modify_channel_params_list_to_json(char *wbuf, size_t len, struct discord_modify_channel_params **)`
 * @endverbatim
 */
struct discord_modify_channel_params {
  /* discord/channel.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *name;

  /* discord/channel.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *icon;

  /* discord/channel.params.json:14:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
  enum discord_channel_types type;

  /* discord/channel.params.json:15:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int position;

  /* discord/channel.params.json:16:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *topic;

  /* discord/channel.params.json:17:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool nsfw;

  /* discord/channel.params.json:18:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int rate_limit_per_user;

  /* discord/channel.params.json:19:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int bitrate;

  /* discord/channel.params.json:20:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int user_limit;

  /* discord/channel.params.json:21:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
  struct discord_overwrite **permission_overwrites;

  /* discord/channel.params.json:22:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
  u64_snowflake_t parent_id;

  /* discord/channel.params.json:23:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *rtc_region;

  /* discord/channel.params.json:24:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int video_quality_mode;

  /* discord/channel.params.json:25:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool archived;

  /* discord/channel.params.json:26:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

  /* discord/channel.params.json:27:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool locked;

};
extern void discord_modify_channel_params_cleanup_v(void *p);
extern void discord_modify_channel_params_cleanup(struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_init_v(void *p);
extern void discord_modify_channel_params_init(struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_channel_params_from_json_p(char *json, size_t len, struct discord_modify_channel_params **pp);
extern void discord_modify_channel_params_from_json(char *json, size_t len, struct discord_modify_channel_params *p);
extern size_t discord_modify_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_channel_params_to_json(char *json, size_t len, struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_list_free_v(void **p);
extern void discord_modify_channel_params_list_free(struct discord_modify_channel_params **p);
extern void discord_modify_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_channel_params_list_from_json(char *str, size_t len, struct discord_modify_channel_params ***p);
extern size_t discord_modify_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_channel_params_list_to_json(char *str, size_t len, struct discord_modify_channel_params **p);

/* Create Message */
/* defined at discord/channel.params.json:33:22 */
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

 *     * :code:`void discord_create_message_params_from_json(char *rbuf, size_t len, struct discord_create_message_params *)`
 *     * :code:`void discord_create_message_params_list_from_json(char *rbuf, size_t len, struct discord_create_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_message_params_to_json(char *wbuf, size_t len, struct discord_create_message_params *)`
 *     * :code:`void discord_create_message_params_list_to_json(char *wbuf, size_t len, struct discord_create_message_params **)`
 * @endverbatim
 */
struct discord_create_message_params {
  /* discord/channel.params.json:36:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
  char *content; /**< the message contents (up to 2000 characters) */

  /* discord/channel.params.json:37:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  bool tts; /**< true if this is a TTS message */

  /* discord/channel.params.json:38:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
  struct discord_embed **embeds; /**< embedded rich content (up to 6000 characters) */

  /* discord/channel.params.json:39:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
  struct discord_embed *embed; /**< embedded rich content, deprecated in favor of embeds */

  /* discord/channel.params.json:40:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* discord/channel.params.json:41:20
     '{ "name": "message_reference", "type":{ "base":"struct discord_message_reference", "dec":"*" }, "comment":"include to make your message a reply", "inject_if_not":null }' */
  struct discord_message_reference *message_reference; /**< include to make your message a reply */

  /* discord/channel.params.json:42:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  struct discord_component **components; /**< the components to include with the message */

  /* discord/channel.params.json:43:20
     '{ "name": "sticker_ids", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"ids of up to 3 stickers in the server to send in the message", "inject_if_not":null }' */
  ja_u64 **sticker_ids; /**< ids of up to 3 stickers in the server to send in the message */

  /* discord/channel.params.json:44:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attachment objects with filename and description", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attachment objects with filename and description */

};
extern void discord_create_message_params_cleanup_v(void *p);
extern void discord_create_message_params_cleanup(struct discord_create_message_params *p);
extern void discord_create_message_params_init_v(void *p);
extern void discord_create_message_params_init(struct discord_create_message_params *p);
extern void discord_create_message_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_message_params_from_json_p(char *json, size_t len, struct discord_create_message_params **pp);
extern void discord_create_message_params_from_json(char *json, size_t len, struct discord_create_message_params *p);
extern size_t discord_create_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_message_params_to_json(char *json, size_t len, struct discord_create_message_params *p);
extern void discord_create_message_params_list_free_v(void **p);
extern void discord_create_message_params_list_free(struct discord_create_message_params **p);
extern void discord_create_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_message_params_list_from_json(char *str, size_t len, struct discord_create_message_params ***p);
extern size_t discord_create_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_message_params_list_to_json(char *str, size_t len, struct discord_create_message_params **p);

/* Get Channel Messages */
/* defined at discord/channel.params.json:50:22 */
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

 *     * :code:`void discord_get_channel_messages_params_from_json(char *rbuf, size_t len, struct discord_get_channel_messages_params *)`
 *     * :code:`void discord_get_channel_messages_params_list_from_json(char *rbuf, size_t len, struct discord_get_channel_messages_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_get_channel_messages_params_to_json(char *wbuf, size_t len, struct discord_get_channel_messages_params *)`
 *     * :code:`void discord_get_channel_messages_params_list_to_json(char *wbuf, size_t len, struct discord_get_channel_messages_params **)`
 * @endverbatim
 */
struct discord_get_channel_messages_params {
  /* discord/channel.params.json:53:20
     '{ "name": "around", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages around this message ID", "inject_if_not":0 }' */
  u64_snowflake_t around; /**< get messages around this message ID */

  /* discord/channel.params.json:54:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages before this message ID", "inject_if_not":0 }' */
  u64_snowflake_t before; /**< get messages before this message ID */

  /* discord/channel.params.json:55:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages after this message ID", "inject_if_not":0 }' */
  u64_snowflake_t after; /**< get messages after this message ID */

  /* discord/channel.params.json:56:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query", "default_value":50, "comment":"max number of messages to return (1-100)", "inject_if_not":0 }' */
  int limit; /**< max number of messages to return (1-100) */

};
extern void discord_get_channel_messages_params_cleanup_v(void *p);
extern void discord_get_channel_messages_params_cleanup(struct discord_get_channel_messages_params *p);
extern void discord_get_channel_messages_params_init_v(void *p);
extern void discord_get_channel_messages_params_init(struct discord_get_channel_messages_params *p);
extern void discord_get_channel_messages_params_from_json_v(char *json, size_t len, void *p);
extern void discord_get_channel_messages_params_from_json_p(char *json, size_t len, struct discord_get_channel_messages_params **pp);
extern void discord_get_channel_messages_params_from_json(char *json, size_t len, struct discord_get_channel_messages_params *p);
extern size_t discord_get_channel_messages_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_channel_messages_params_to_json(char *json, size_t len, struct discord_get_channel_messages_params *p);
extern void discord_get_channel_messages_params_list_free_v(void **p);
extern void discord_get_channel_messages_params_list_free(struct discord_get_channel_messages_params **p);
extern void discord_get_channel_messages_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_channel_messages_params_list_from_json(char *str, size_t len, struct discord_get_channel_messages_params ***p);
extern size_t discord_get_channel_messages_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_channel_messages_params_list_to_json(char *str, size_t len, struct discord_get_channel_messages_params **p);

/* Get Reactions */
/* defined at discord/channel.params.json:62:22 */
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

 *     * :code:`void discord_get_reactions_params_from_json(char *rbuf, size_t len, struct discord_get_reactions_params *)`
 *     * :code:`void discord_get_reactions_params_list_from_json(char *rbuf, size_t len, struct discord_get_reactions_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_get_reactions_params_to_json(char *wbuf, size_t len, struct discord_get_reactions_params *)`
 *     * :code:`void discord_get_reactions_params_list_to_json(char *wbuf, size_t len, struct discord_get_reactions_params **)`
 * @endverbatim
 */
struct discord_get_reactions_params {
  /* discord/channel.params.json:65:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
  u64_snowflake_t after;

  /* discord/channel.params.json:66:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
  int limit;

};
extern void discord_get_reactions_params_cleanup_v(void *p);
extern void discord_get_reactions_params_cleanup(struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_init_v(void *p);
extern void discord_get_reactions_params_init(struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_from_json_v(char *json, size_t len, void *p);
extern void discord_get_reactions_params_from_json_p(char *json, size_t len, struct discord_get_reactions_params **pp);
extern void discord_get_reactions_params_from_json(char *json, size_t len, struct discord_get_reactions_params *p);
extern size_t discord_get_reactions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_reactions_params_to_json(char *json, size_t len, struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_list_free_v(void **p);
extern void discord_get_reactions_params_list_free(struct discord_get_reactions_params **p);
extern void discord_get_reactions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_reactions_params_list_from_json(char *str, size_t len, struct discord_get_reactions_params ***p);
extern size_t discord_get_reactions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_reactions_params_list_to_json(char *str, size_t len, struct discord_get_reactions_params **p);

/* Edit Channel Permissions */
/* defined at discord/channel.params.json:72:22 */
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

 *     * :code:`void discord_edit_channel_permissions_params_from_json(char *rbuf, size_t len, struct discord_edit_channel_permissions_params *)`
 *     * :code:`void discord_edit_channel_permissions_params_list_from_json(char *rbuf, size_t len, struct discord_edit_channel_permissions_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_channel_permissions_params_to_json(char *wbuf, size_t len, struct discord_edit_channel_permissions_params *)`
 *     * :code:`void discord_edit_channel_permissions_params_list_to_json(char *wbuf, size_t len, struct discord_edit_channel_permissions_params **)`
 * @endverbatim
 */
struct discord_edit_channel_permissions_params {
  /* discord/channel.params.json:75:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"enum discord_bitwise_permission_flags"}, "comment":"permission bit set" }' */
  uint64_t allow; /**< permission bit set */

  /* discord/channel.params.json:76:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"enum discord_bitwise_permission_flags"}, "comment":"permission bit set" }' */
  uint64_t deny; /**< permission bit set */

  /* discord/channel.params.json:77:20
     '{ "name": "type", "type":{ "base":"int", "int_alias": "enum discord_channel_types" }}' */
  enum discord_channel_types type;

};
extern void discord_edit_channel_permissions_params_cleanup_v(void *p);
extern void discord_edit_channel_permissions_params_cleanup(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_init_v(void *p);
extern void discord_edit_channel_permissions_params_init(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_from_json_v(char *json, size_t len, void *p);
extern void discord_edit_channel_permissions_params_from_json_p(char *json, size_t len, struct discord_edit_channel_permissions_params **pp);
extern void discord_edit_channel_permissions_params_from_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern size_t discord_edit_channel_permissions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_to_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_list_free_v(void **p);
extern void discord_edit_channel_permissions_params_list_free(struct discord_edit_channel_permissions_params **p);
extern void discord_edit_channel_permissions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_channel_permissions_params_list_from_json(char *str, size_t len, struct discord_edit_channel_permissions_params ***p);
extern size_t discord_edit_channel_permissions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_list_to_json(char *str, size_t len, struct discord_edit_channel_permissions_params **p);

/* Edit Message */
/* defined at discord/channel.params.json:83:22 */
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

 *     * :code:`void discord_edit_message_params_from_json(char *rbuf, size_t len, struct discord_edit_message_params *)`
 *     * :code:`void discord_edit_message_params_list_from_json(char *rbuf, size_t len, struct discord_edit_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_edit_message_params_to_json(char *wbuf, size_t len, struct discord_edit_message_params *)`
 *     * :code:`void discord_edit_message_params_list_to_json(char *wbuf, size_t len, struct discord_edit_message_params **)`
 * @endverbatim
 */
struct discord_edit_message_params {
  /* discord/channel.params.json:86:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
  char *content; /**< the message contents (up to 2000 characters) */

  /* discord/channel.params.json:87:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
  struct discord_embed **embeds; /**< embedded rich content (up to 6000 characters) */

  /* discord/channel.params.json:88:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
  struct discord_embed *embed; /**< embedded rich content, deprecated in favor of embeds */

  /* discord/channel.params.json:89:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_message_flags" }, "comment":"edit the flags of a message", "inject_if_not":0 }' */
  enum discord_message_flags flags; /**< edit the flags of a message */

  /* discord/channel.params.json:90:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  struct discord_allowed_mentions *allowed_mentions; /**< allowed mentions for the message */

  /* discord/channel.params.json:91:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  struct discord_attachment **attachments; /**< attached files to keep */

  /* discord/channel.params.json:92:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  struct discord_component **components; /**< the components to include with the message */

};
extern void discord_edit_message_params_cleanup_v(void *p);
extern void discord_edit_message_params_cleanup(struct discord_edit_message_params *p);
extern void discord_edit_message_params_init_v(void *p);
extern void discord_edit_message_params_init(struct discord_edit_message_params *p);
extern void discord_edit_message_params_from_json_v(char *json, size_t len, void *p);
extern void discord_edit_message_params_from_json_p(char *json, size_t len, struct discord_edit_message_params **pp);
extern void discord_edit_message_params_from_json(char *json, size_t len, struct discord_edit_message_params *p);
extern size_t discord_edit_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_message_params_to_json(char *json, size_t len, struct discord_edit_message_params *p);
extern void discord_edit_message_params_list_free_v(void **p);
extern void discord_edit_message_params_list_free(struct discord_edit_message_params **p);
extern void discord_edit_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_message_params_list_from_json(char *str, size_t len, struct discord_edit_message_params ***p);
extern size_t discord_edit_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_message_params_list_to_json(char *str, size_t len, struct discord_edit_message_params **p);

/* Follow News Channel */
/* defined at discord/channel.params.json:98:22 */
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

 *     * :code:`void discord_follow_news_channel_params_from_json(char *rbuf, size_t len, struct discord_follow_news_channel_params *)`
 *     * :code:`void discord_follow_news_channel_params_list_from_json(char *rbuf, size_t len, struct discord_follow_news_channel_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_follow_news_channel_params_to_json(char *wbuf, size_t len, struct discord_follow_news_channel_params *)`
 *     * :code:`void discord_follow_news_channel_params_list_to_json(char *wbuf, size_t len, struct discord_follow_news_channel_params **)`
 * @endverbatim
 */
struct discord_follow_news_channel_params {
  /* discord/channel.params.json:101:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  u64_snowflake_t webhook_channel_id;

};
extern void discord_follow_news_channel_params_cleanup_v(void *p);
extern void discord_follow_news_channel_params_cleanup(struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_init_v(void *p);
extern void discord_follow_news_channel_params_init(struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_from_json_v(char *json, size_t len, void *p);
extern void discord_follow_news_channel_params_from_json_p(char *json, size_t len, struct discord_follow_news_channel_params **pp);
extern void discord_follow_news_channel_params_from_json(char *json, size_t len, struct discord_follow_news_channel_params *p);
extern size_t discord_follow_news_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_follow_news_channel_params_to_json(char *json, size_t len, struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_list_free_v(void **p);
extern void discord_follow_news_channel_params_list_free(struct discord_follow_news_channel_params **p);
extern void discord_follow_news_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_follow_news_channel_params_list_from_json(char *str, size_t len, struct discord_follow_news_channel_params ***p);
extern size_t discord_follow_news_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_follow_news_channel_params_list_to_json(char *str, size_t len, struct discord_follow_news_channel_params **p);

/* Create Channel Invite */
/* defined at discord/channel.params.json:107:22 */
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

 *     * :code:`void discord_create_channel_invite_params_from_json(char *rbuf, size_t len, struct discord_create_channel_invite_params *)`
 *     * :code:`void discord_create_channel_invite_params_list_from_json(char *rbuf, size_t len, struct discord_create_channel_invite_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_channel_invite_params_to_json(char *wbuf, size_t len, struct discord_create_channel_invite_params *)`
 *     * :code:`void discord_create_channel_invite_params_list_to_json(char *wbuf, size_t len, struct discord_create_channel_invite_params **)`
 * @endverbatim
 */
struct discord_create_channel_invite_params {
  /* discord/channel.params.json:110:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  int max_age;

  /* discord/channel.params.json:111:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  int max_uses;

  /* discord/channel.params.json:112:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
  bool temporary;

  /* discord/channel.params.json:113:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
  bool unique;

  /* discord/channel.params.json:114:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
  int target_type;

  /* discord/channel.params.json:115:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  u64_snowflake_t target_user_id;

  /* discord/channel.params.json:116:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  u64_snowflake_t target_application_id;

};
extern void discord_create_channel_invite_params_cleanup_v(void *p);
extern void discord_create_channel_invite_params_cleanup(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_init_v(void *p);
extern void discord_create_channel_invite_params_init(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_channel_invite_params_from_json_p(char *json, size_t len, struct discord_create_channel_invite_params **pp);
extern void discord_create_channel_invite_params_from_json(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern size_t discord_create_channel_invite_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_channel_invite_params_to_json(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_list_free_v(void **p);
extern void discord_create_channel_invite_params_list_free(struct discord_create_channel_invite_params **p);
extern void discord_create_channel_invite_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_channel_invite_params_list_from_json(char *str, size_t len, struct discord_create_channel_invite_params ***p);
extern size_t discord_create_channel_invite_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_channel_invite_params_list_to_json(char *str, size_t len, struct discord_create_channel_invite_params **p);

/* Group DM Add Recipient */
/* defined at discord/channel.params.json:122:22 */
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

 *     * :code:`void discord_group_dm_add_recipient_params_from_json(char *rbuf, size_t len, struct discord_group_dm_add_recipient_params *)`
 *     * :code:`void discord_group_dm_add_recipient_params_list_from_json(char *rbuf, size_t len, struct discord_group_dm_add_recipient_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_group_dm_add_recipient_params_to_json(char *wbuf, size_t len, struct discord_group_dm_add_recipient_params *)`
 *     * :code:`void discord_group_dm_add_recipient_params_list_to_json(char *wbuf, size_t len, struct discord_group_dm_add_recipient_params **)`
 * @endverbatim
 */
struct discord_group_dm_add_recipient_params {
  /* discord/channel.params.json:125:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
  char *access_token;

  /* discord/channel.params.json:126:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

};
extern void discord_group_dm_add_recipient_params_cleanup_v(void *p);
extern void discord_group_dm_add_recipient_params_cleanup(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_init_v(void *p);
extern void discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_from_json_v(char *json, size_t len, void *p);
extern void discord_group_dm_add_recipient_params_from_json_p(char *json, size_t len, struct discord_group_dm_add_recipient_params **pp);
extern void discord_group_dm_add_recipient_params_from_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern size_t discord_group_dm_add_recipient_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_to_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_list_free_v(void **p);
extern void discord_group_dm_add_recipient_params_list_free(struct discord_group_dm_add_recipient_params **p);
extern void discord_group_dm_add_recipient_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_group_dm_add_recipient_params_list_from_json(char *str, size_t len, struct discord_group_dm_add_recipient_params ***p);
extern size_t discord_group_dm_add_recipient_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_list_to_json(char *str, size_t len, struct discord_group_dm_add_recipient_params **p);

/* Start Thread with Message */
/* defined at discord/channel.params.json:132:22 */
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

 *     * :code:`void discord_start_thread_with_message_params_from_json(char *rbuf, size_t len, struct discord_start_thread_with_message_params *)`
 *     * :code:`void discord_start_thread_with_message_params_list_from_json(char *rbuf, size_t len, struct discord_start_thread_with_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_start_thread_with_message_params_to_json(char *wbuf, size_t len, struct discord_start_thread_with_message_params *)`
 *     * :code:`void discord_start_thread_with_message_params_list_to_json(char *wbuf, size_t len, struct discord_start_thread_with_message_params **)`
 * @endverbatim
 */
struct discord_start_thread_with_message_params {
  /* discord/channel.params.json:135:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *name;

  /* discord/channel.params.json:136:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

};
extern void discord_start_thread_with_message_params_cleanup_v(void *p);
extern void discord_start_thread_with_message_params_cleanup(struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_init_v(void *p);
extern void discord_start_thread_with_message_params_init(struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_from_json_v(char *json, size_t len, void *p);
extern void discord_start_thread_with_message_params_from_json_p(char *json, size_t len, struct discord_start_thread_with_message_params **pp);
extern void discord_start_thread_with_message_params_from_json(char *json, size_t len, struct discord_start_thread_with_message_params *p);
extern size_t discord_start_thread_with_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_with_message_params_to_json(char *json, size_t len, struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_list_free_v(void **p);
extern void discord_start_thread_with_message_params_list_free(struct discord_start_thread_with_message_params **p);
extern void discord_start_thread_with_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_start_thread_with_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_with_message_params ***p);
extern size_t discord_start_thread_with_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_start_thread_with_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_with_message_params **p);

/* Start Thread without Message */
/* defined at discord/channel.params.json:142:22 */
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

 *     * :code:`void discord_start_thread_without_message_params_from_json(char *rbuf, size_t len, struct discord_start_thread_without_message_params *)`
 *     * :code:`void discord_start_thread_without_message_params_list_from_json(char *rbuf, size_t len, struct discord_start_thread_without_message_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_start_thread_without_message_params_to_json(char *wbuf, size_t len, struct discord_start_thread_without_message_params *)`
 *     * :code:`void discord_start_thread_without_message_params_list_to_json(char *wbuf, size_t len, struct discord_start_thread_without_message_params **)`
 * @endverbatim
 */
struct discord_start_thread_without_message_params {
  /* discord/channel.params.json:145:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
  char *name;

  /* discord/channel.params.json:146:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

  /* discord/channel.params.json:147:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
  enum discord_channel_types type;

};
extern void discord_start_thread_without_message_params_cleanup_v(void *p);
extern void discord_start_thread_without_message_params_cleanup(struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_init_v(void *p);
extern void discord_start_thread_without_message_params_init(struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_from_json_v(char *json, size_t len, void *p);
extern void discord_start_thread_without_message_params_from_json_p(char *json, size_t len, struct discord_start_thread_without_message_params **pp);
extern void discord_start_thread_without_message_params_from_json(char *json, size_t len, struct discord_start_thread_without_message_params *p);
extern size_t discord_start_thread_without_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_to_json(char *json, size_t len, struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_list_free_v(void **p);
extern void discord_start_thread_without_message_params_list_free(struct discord_start_thread_without_message_params **p);
extern void discord_start_thread_without_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_start_thread_without_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_without_message_params ***p);
extern size_t discord_start_thread_without_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_without_message_params **p);

/* List Active Threads */
/* defined at discord/channel.params.json:153:22 */
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

 *     * :code:`void discord_thread_response_body_from_json(char *rbuf, size_t len, struct discord_thread_response_body *)`
 *     * :code:`void discord_thread_response_body_list_from_json(char *rbuf, size_t len, struct discord_thread_response_body ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_thread_response_body_to_json(char *wbuf, size_t len, struct discord_thread_response_body *)`
 *     * :code:`void discord_thread_response_body_list_to_json(char *wbuf, size_t len, struct discord_thread_response_body **)`
 * @endverbatim
 */
struct discord_thread_response_body {
  /* discord/channel.params.json:156:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
  struct discord_channel **threads;

  /* discord/channel.params.json:157:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
  struct discord_thread_member **members;

  /* discord/channel.params.json:158:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
  bool has_more;

};
extern void discord_thread_response_body_cleanup_v(void *p);
extern void discord_thread_response_body_cleanup(struct discord_thread_response_body *p);
extern void discord_thread_response_body_init_v(void *p);
extern void discord_thread_response_body_init(struct discord_thread_response_body *p);
extern void discord_thread_response_body_from_json_v(char *json, size_t len, void *p);
extern void discord_thread_response_body_from_json_p(char *json, size_t len, struct discord_thread_response_body **pp);
extern void discord_thread_response_body_from_json(char *json, size_t len, struct discord_thread_response_body *p);
extern size_t discord_thread_response_body_to_json_v(char *json, size_t len, void *p);
extern size_t discord_thread_response_body_to_json(char *json, size_t len, struct discord_thread_response_body *p);
extern void discord_thread_response_body_list_free_v(void **p);
extern void discord_thread_response_body_list_free(struct discord_thread_response_body **p);
extern void discord_thread_response_body_list_from_json_v(char *str, size_t len, void *p);
extern void discord_thread_response_body_list_from_json(char *str, size_t len, struct discord_thread_response_body ***p);
extern size_t discord_thread_response_body_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_thread_response_body_list_to_json(char *str, size_t len, struct discord_thread_response_body **p);
