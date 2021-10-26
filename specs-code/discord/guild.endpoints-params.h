/* This file is generated from specs/discord/guild.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/guild.endpoints-params.h
 * @see https://discord.com/developers/docs/resources/guild
 */


/* Create Guild */
/* defined at specs/discord/guild.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_params_init(struct discord_create_guild_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_params_cleanup(struct discord_create_guild_params *)`
 *     * :code:`void discord_create_guild_params_list_free(struct discord_create_guild_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_params_from_json(char *rbuf, size_t len, struct discord_create_guild_params **)`
 *     * :code:`void discord_create_guild_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_params_to_json(char *wbuf, size_t len, struct discord_create_guild_params *)`
 *     * :code:`void discord_create_guild_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_params **)`
 * @endverbatim
 */
struct discord_create_guild_params {
  /* specs/discord/guild.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  char *name; /**< name of the guild (2-100) characters */

  /* specs/discord/guild.endpoints-params.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  char *region; /**< voice region id */

  /* specs/discord/guild.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  char *icon; /**< base64 128x1128 image for the guild icon */

  /* specs/discord/guild.endpoints-params.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  int verification_level; /**< verification level */

  /* specs/discord/guild.endpoints-params.json:16:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  int default_message_notifications; /**< default message notification level */

  /* specs/discord/guild.endpoints-params.json:17:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  int explicit_content_filter; /**< explicit content filter level */

  /* specs/discord/guild.endpoints-params.json:18:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"new guild roles" }' */
  struct discord_role **roles; /**< new guild roles */

  /* specs/discord/guild.endpoints-params.json:19:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
  struct discord_channel **channels; /**< array of partial channel objects */

  /* specs/discord/guild.endpoints-params.json:20:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  u64_snowflake_t afk_channel_id; /**< id for afk channel */

  /* specs/discord/guild.endpoints-params.json:21:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  int afk_timeout; /**< afk timeout in seconds */

  /* specs/discord/guild.endpoints-params.json:22:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  u64_snowflake_t system_channel_id; /**< the id of the channel where guild notices such as welcome messages and boost events are posted */

};
extern void discord_create_guild_params_cleanup_v(void *p);
extern void discord_create_guild_params_cleanup(struct discord_create_guild_params *p);
extern void discord_create_guild_params_init_v(void *p);
extern void discord_create_guild_params_init(struct discord_create_guild_params *p);
extern void discord_create_guild_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_params_from_json(char *json, size_t len, struct discord_create_guild_params **pp);
extern size_t discord_create_guild_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_params_to_json(char *json, size_t len, struct discord_create_guild_params *p);
extern void discord_create_guild_params_list_free_v(void **p);
extern void discord_create_guild_params_list_free(struct discord_create_guild_params **p);
extern void discord_create_guild_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_params_list_from_json(char *str, size_t len, struct discord_create_guild_params ***p);
extern size_t discord_create_guild_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_params_list_to_json(char *str, size_t len, struct discord_create_guild_params **p);

/* Modify Guild */
/* defined at specs/discord/guild.endpoints-params.json:28:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_params_init(struct discord_modify_guild_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_params_cleanup(struct discord_modify_guild_params *)`
 *     * :code:`void discord_modify_guild_params_list_free(struct discord_modify_guild_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_params **)`
 *     * :code:`void discord_modify_guild_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_params *)`
 *     * :code:`void discord_modify_guild_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_params **)`
 * @endverbatim
 */
struct discord_modify_guild_params {
  /* specs/discord/guild.endpoints-params.json:31:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  char *name; /**< name of the guild (2-100) characters */

  /* specs/discord/guild.endpoints-params.json:32:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  char *region; /**< voice region id */

  /* specs/discord/guild.endpoints-params.json:33:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  int verification_level; /**< verification level */

  /* specs/discord/guild.endpoints-params.json:34:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  int default_message_notifications; /**< default message notification level */

  /* specs/discord/guild.endpoints-params.json:35:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  int explicit_content_filter; /**< explicit content filter level */

  /* specs/discord/guild.endpoints-params.json:36:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  u64_snowflake_t afk_channel_id; /**< id for afk channel */

  /* specs/discord/guild.endpoints-params.json:37:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  int afk_timeout; /**< afk timeout in seconds */

  /* specs/discord/guild.endpoints-params.json:38:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  char *icon; /**< base64 128x1128 image for the guild icon */

  /* specs/discord/guild.endpoints-params.json:39:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
  u64_snowflake_t owner_id; /**< user id to transfer guild ownership to (must be owner) */

  /* specs/discord/guild.endpoints-params.json:40:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
  char *splash; /**< base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature */

  /* specs/discord/guild.endpoints-params.json:41:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
  char *discovery_splash; /**< base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature) */

  /* specs/discord/guild.endpoints-params.json:42:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
  char *banner; /**< cannot unescape an ill-formed-string 	base64 16:9 png/jpeg image for the guild banner (wh */

  /* specs/discord/guild.endpoints-params.json:43:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  u64_snowflake_t system_channel_id; /**< cannot unescape an ill-formed-string 	the id of the channel where guild notices such as welcome */

  /* specs/discord/guild.endpoints-params.json:44:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
  enum discord_system_channel_flags system_channel_flags; /**< system channel flags */

  /* specs/discord/guild.endpoints-params.json:45:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
  u64_snowflake_t rules_channel_id; /**< the id of the channel where Community guilds display rules and/or guidelines */

  /* specs/discord/guild.endpoints-params.json:46:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
  u64_snowflake_t public_updates_channel_id; /**< the id of the channel where admins and moderators of Community guilds receive notices from Discord */

  /* specs/discord/guild.endpoints-params.json:47:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
  char *preferred_locale; /**< the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to "en-US" */

  /* specs/discord/guild.endpoints-params.json:48:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "comment":"array of guild feature strings"}' */
  ja_str **features; /**< array of guild feature strings */

  /* specs/discord/guild.endpoints-params.json:49:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
  char *description; /**< the description for the guild, if the guild is discoverable */

};
extern void discord_modify_guild_params_cleanup_v(void *p);
extern void discord_modify_guild_params_cleanup(struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_init_v(void *p);
extern void discord_modify_guild_params_init(struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_params_from_json(char *json, size_t len, struct discord_modify_guild_params **pp);
extern size_t discord_modify_guild_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_params_to_json(char *json, size_t len, struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_list_free_v(void **p);
extern void discord_modify_guild_params_list_free(struct discord_modify_guild_params **p);
extern void discord_modify_guild_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_params_list_from_json(char *str, size_t len, struct discord_modify_guild_params ***p);
extern size_t discord_modify_guild_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_params_list_to_json(char *str, size_t len, struct discord_modify_guild_params **p);

/* Create Guild Channel */
/* defined at specs/discord/guild.endpoints-params.json:55:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_channel_params_init(struct discord_create_guild_channel_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_channel_params_cleanup(struct discord_create_guild_channel_params *)`
 *     * :code:`void discord_create_guild_channel_params_list_free(struct discord_create_guild_channel_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_channel_params_from_json(char *rbuf, size_t len, struct discord_create_guild_channel_params **)`
 *     * :code:`void discord_create_guild_channel_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_channel_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_channel_params_to_json(char *wbuf, size_t len, struct discord_create_guild_channel_params *)`
 *     * :code:`void discord_create_guild_channel_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_channel_params **)`
 * @endverbatim
 */
struct discord_create_guild_channel_params {
  /* specs/discord/guild.endpoints-params.json:58:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/guild.endpoints-params.json:59:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  /* specs/discord/guild.endpoints-params.json:60:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
  char *topic;

  /* specs/discord/guild.endpoints-params.json:61:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
  int bitrate;

  /* specs/discord/guild.endpoints-params.json:62:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
  int user_limit;

  /* specs/discord/guild.endpoints-params.json:63:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
  int rate_limit_per_user;

  /* specs/discord/guild.endpoints-params.json:64:20
     '{ "name": "position", "type":{ "base":"int" } }' */
  int position;

  /* specs/discord/guild.endpoints-params.json:65:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
  struct discord_overwrite **permission_overwrites;

  /* specs/discord/guild.endpoints-params.json:66:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  u64_snowflake_t parent_id;

  /* specs/discord/guild.endpoints-params.json:67:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
  bool nsfw;

};
extern void discord_create_guild_channel_params_cleanup_v(void *p);
extern void discord_create_guild_channel_params_cleanup(struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_init_v(void *p);
extern void discord_create_guild_channel_params_init(struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_channel_params_from_json(char *json, size_t len, struct discord_create_guild_channel_params **pp);
extern size_t discord_create_guild_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_channel_params_to_json(char *json, size_t len, struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_list_free_v(void **p);
extern void discord_create_guild_channel_params_list_free(struct discord_create_guild_channel_params **p);
extern void discord_create_guild_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_channel_params_list_from_json(char *str, size_t len, struct discord_create_guild_channel_params ***p);
extern size_t discord_create_guild_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_channel_params_list_to_json(char *str, size_t len, struct discord_create_guild_channel_params **p);

/* Modify Guild Channel Positions */
/* defined at specs/discord/guild.endpoints-params.json:73:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_channel_positions_params_init(struct discord_modify_guild_channel_positions_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_channel_positions_params_cleanup(struct discord_modify_guild_channel_positions_params *)`
 *     * :code:`void discord_modify_guild_channel_positions_params_list_free(struct discord_modify_guild_channel_positions_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_channel_positions_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_channel_positions_params **)`
 *     * :code:`void discord_modify_guild_channel_positions_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_channel_positions_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_channel_positions_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_channel_positions_params *)`
 *     * :code:`void discord_modify_guild_channel_positions_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_channel_positions_params **)`
 * @endverbatim
 */
struct discord_modify_guild_channel_positions_params {
  /* specs/discord/guild.endpoints-params.json:76:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
  u64_snowflake_t id; /**< channel id */

  /* specs/discord/guild.endpoints-params.json:77:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
  int position; /**< sorting position of the channel */

  /* specs/discord/guild.endpoints-params.json:78:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
  bool lock_permissions; /**< syncs the permission overwrites with the new parent, if moving to a new category */

  /* specs/discord/guild.endpoints-params.json:79:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
  u64_snowflake_t parent_id; /**< the new parent ID for the channel that is moved */

};
extern void discord_modify_guild_channel_positions_params_cleanup_v(void *p);
extern void discord_modify_guild_channel_positions_params_cleanup(struct discord_modify_guild_channel_positions_params *p);
extern void discord_modify_guild_channel_positions_params_init_v(void *p);
extern void discord_modify_guild_channel_positions_params_init(struct discord_modify_guild_channel_positions_params *p);
extern void discord_modify_guild_channel_positions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_channel_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params **pp);
extern size_t discord_modify_guild_channel_positions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_channel_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params *p);
extern void discord_modify_guild_channel_positions_params_list_free_v(void **p);
extern void discord_modify_guild_channel_positions_params_list_free(struct discord_modify_guild_channel_positions_params **p);
extern void discord_modify_guild_channel_positions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_channel_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params ***p);
extern size_t discord_modify_guild_channel_positions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_channel_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params **p);

/* List Guild Members */
/* defined at specs/discord/guild.endpoints-params.json:85:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_list_guild_members_params_init(struct discord_list_guild_members_params *)`
 *   * Cleanup:

 *     * :code:`void discord_list_guild_members_params_cleanup(struct discord_list_guild_members_params *)`
 *     * :code:`void discord_list_guild_members_params_list_free(struct discord_list_guild_members_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_list_guild_members_params_from_json(char *rbuf, size_t len, struct discord_list_guild_members_params **)`
 *     * :code:`void discord_list_guild_members_params_list_from_json(char *rbuf, size_t len, struct discord_list_guild_members_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_list_guild_members_params_to_json(char *wbuf, size_t len, struct discord_list_guild_members_params *)`
 *     * :code:`void discord_list_guild_members_params_list_to_json(char *wbuf, size_t len, struct discord_list_guild_members_params **)`
 * @endverbatim
 */
struct discord_list_guild_members_params {
  /* specs/discord/guild.endpoints-params.json:88:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max numbers of members to return (1-1000)", "default_value":1 }' */
  int limit; /**< max numbers of members to return (1-1000) */

  /* specs/discord/guild.endpoints-params.json:89:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment": "the highest user id in the previous page"}' */
  u64_snowflake_t after; /**< the highest user id in the previous page */

};
extern void discord_list_guild_members_params_cleanup_v(void *p);
extern void discord_list_guild_members_params_cleanup(struct discord_list_guild_members_params *p);
extern void discord_list_guild_members_params_init_v(void *p);
extern void discord_list_guild_members_params_init(struct discord_list_guild_members_params *p);
extern void discord_list_guild_members_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_list_guild_members_params_from_json(char *json, size_t len, struct discord_list_guild_members_params **pp);
extern size_t discord_list_guild_members_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_list_guild_members_params_to_json(char *json, size_t len, struct discord_list_guild_members_params *p);
extern void discord_list_guild_members_params_list_free_v(void **p);
extern void discord_list_guild_members_params_list_free(struct discord_list_guild_members_params **p);
extern void discord_list_guild_members_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_list_guild_members_params_list_from_json(char *str, size_t len, struct discord_list_guild_members_params ***p);
extern size_t discord_list_guild_members_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_list_guild_members_params_list_to_json(char *str, size_t len, struct discord_list_guild_members_params **p);

/* Search Guild Members */
/* defined at specs/discord/guild.endpoints-params.json:95:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_search_guild_members_params_init(struct discord_search_guild_members_params *)`
 *   * Cleanup:

 *     * :code:`void discord_search_guild_members_params_cleanup(struct discord_search_guild_members_params *)`
 *     * :code:`void discord_search_guild_members_params_list_free(struct discord_search_guild_members_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_search_guild_members_params_from_json(char *rbuf, size_t len, struct discord_search_guild_members_params **)`
 *     * :code:`void discord_search_guild_members_params_list_from_json(char *rbuf, size_t len, struct discord_search_guild_members_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_search_guild_members_params_to_json(char *wbuf, size_t len, struct discord_search_guild_members_params *)`
 *     * :code:`void discord_search_guild_members_params_list_to_json(char *wbuf, size_t len, struct discord_search_guild_members_params **)`
 * @endverbatim
 */
struct discord_search_guild_members_params {
  /* specs/discord/guild.endpoints-params.json:98:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
  char *query; /**< Query string to match username(s) and nickname(s) against. */

  /* specs/discord/guild.endpoints-params.json:99:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
  int limit; /**< max number of members to return (1-1000) */

};
extern void discord_search_guild_members_params_cleanup_v(void *p);
extern void discord_search_guild_members_params_cleanup(struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_init_v(void *p);
extern void discord_search_guild_members_params_init(struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_search_guild_members_params_from_json(char *json, size_t len, struct discord_search_guild_members_params **pp);
extern size_t discord_search_guild_members_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_search_guild_members_params_to_json(char *json, size_t len, struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_list_free_v(void **p);
extern void discord_search_guild_members_params_list_free(struct discord_search_guild_members_params **p);
extern void discord_search_guild_members_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_search_guild_members_params_list_from_json(char *str, size_t len, struct discord_search_guild_members_params ***p);
extern size_t discord_search_guild_members_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_search_guild_members_params_list_to_json(char *str, size_t len, struct discord_search_guild_members_params **p);

/* Add Guild Member */
/* defined at specs/discord/guild.endpoints-params.json:105:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_add_guild_member_params_init(struct discord_add_guild_member_params *)`
 *   * Cleanup:

 *     * :code:`void discord_add_guild_member_params_cleanup(struct discord_add_guild_member_params *)`
 *     * :code:`void discord_add_guild_member_params_list_free(struct discord_add_guild_member_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_add_guild_member_params_from_json(char *rbuf, size_t len, struct discord_add_guild_member_params **)`
 *     * :code:`void discord_add_guild_member_params_list_from_json(char *rbuf, size_t len, struct discord_add_guild_member_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_add_guild_member_params_to_json(char *wbuf, size_t len, struct discord_add_guild_member_params *)`
 *     * :code:`void discord_add_guild_member_params_list_to_json(char *wbuf, size_t len, struct discord_add_guild_member_params **)`
 * @endverbatim
 */
struct discord_add_guild_member_params {
  /* specs/discord/guild.endpoints-params.json:108:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *access_token;

  /* specs/discord/guild.endpoints-params.json:109:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *nick;

  /* specs/discord/guild.endpoints-params.json:110:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **roles;

  /* specs/discord/guild.endpoints-params.json:111:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool mute;

  /* specs/discord/guild.endpoints-params.json:112:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool deaf;

};
extern void discord_add_guild_member_params_cleanup_v(void *p);
extern void discord_add_guild_member_params_cleanup(struct discord_add_guild_member_params *p);
extern void discord_add_guild_member_params_init_v(void *p);
extern void discord_add_guild_member_params_init(struct discord_add_guild_member_params *p);
extern void discord_add_guild_member_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_add_guild_member_params_from_json(char *json, size_t len, struct discord_add_guild_member_params **pp);
extern size_t discord_add_guild_member_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_add_guild_member_params_to_json(char *json, size_t len, struct discord_add_guild_member_params *p);
extern void discord_add_guild_member_params_list_free_v(void **p);
extern void discord_add_guild_member_params_list_free(struct discord_add_guild_member_params **p);
extern void discord_add_guild_member_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_add_guild_member_params_list_from_json(char *str, size_t len, struct discord_add_guild_member_params ***p);
extern size_t discord_add_guild_member_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_add_guild_member_params_list_to_json(char *str, size_t len, struct discord_add_guild_member_params **p);

/* Modify Guild Member */
/* defined at specs/discord/guild.endpoints-params.json:118:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_member_params_init(struct discord_modify_guild_member_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_member_params_cleanup(struct discord_modify_guild_member_params *)`
 *     * :code:`void discord_modify_guild_member_params_list_free(struct discord_modify_guild_member_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_member_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_member_params **)`
 *     * :code:`void discord_modify_guild_member_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_member_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_member_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_member_params *)`
 *     * :code:`void discord_modify_guild_member_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_member_params **)`
 * @endverbatim
 */
struct discord_modify_guild_member_params {
  /* specs/discord/guild.endpoints-params.json:121:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

  /* specs/discord/guild.endpoints-params.json:122:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **roles;

  /* specs/discord/guild.endpoints-params.json:123:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool mute;

  /* specs/discord/guild.endpoints-params.json:124:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool deaf;

  /* specs/discord/guild.endpoints-params.json:125:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  u64_snowflake_t channel_id;

};
extern void discord_modify_guild_member_params_cleanup_v(void *p);
extern void discord_modify_guild_member_params_cleanup(struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_init_v(void *p);
extern void discord_modify_guild_member_params_init(struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_member_params_from_json(char *json, size_t len, struct discord_modify_guild_member_params **pp);
extern size_t discord_modify_guild_member_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_member_params_to_json(char *json, size_t len, struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_list_free_v(void **p);
extern void discord_modify_guild_member_params_list_free(struct discord_modify_guild_member_params **p);
extern void discord_modify_guild_member_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_member_params_list_from_json(char *str, size_t len, struct discord_modify_guild_member_params ***p);
extern size_t discord_modify_guild_member_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_member_params_list_to_json(char *str, size_t len, struct discord_modify_guild_member_params **p);

/* Modify Current Member */
/* defined at specs/discord/guild.endpoints-params.json:131:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_current_member_params_init(struct discord_modify_current_member_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_current_member_params_cleanup(struct discord_modify_current_member_params *)`
 *     * :code:`void discord_modify_current_member_params_list_free(struct discord_modify_current_member_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_current_member_params_from_json(char *rbuf, size_t len, struct discord_modify_current_member_params **)`
 *     * :code:`void discord_modify_current_member_params_list_from_json(char *rbuf, size_t len, struct discord_modify_current_member_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_current_member_params_to_json(char *wbuf, size_t len, struct discord_modify_current_member_params *)`
 *     * :code:`void discord_modify_current_member_params_list_to_json(char *wbuf, size_t len, struct discord_modify_current_member_params **)`
 * @endverbatim
 */
struct discord_modify_current_member_params {
  /* specs/discord/guild.endpoints-params.json:134:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

};
extern void discord_modify_current_member_params_cleanup_v(void *p);
extern void discord_modify_current_member_params_cleanup(struct discord_modify_current_member_params *p);
extern void discord_modify_current_member_params_init_v(void *p);
extern void discord_modify_current_member_params_init(struct discord_modify_current_member_params *p);
extern void discord_modify_current_member_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_current_member_params_from_json(char *json, size_t len, struct discord_modify_current_member_params **pp);
extern size_t discord_modify_current_member_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_current_member_params_to_json(char *json, size_t len, struct discord_modify_current_member_params *p);
extern void discord_modify_current_member_params_list_free_v(void **p);
extern void discord_modify_current_member_params_list_free(struct discord_modify_current_member_params **p);
extern void discord_modify_current_member_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_current_member_params_list_from_json(char *str, size_t len, struct discord_modify_current_member_params ***p);
extern size_t discord_modify_current_member_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_current_member_params_list_to_json(char *str, size_t len, struct discord_modify_current_member_params **p);

/* Modify Current User Nick */
/* defined at specs/discord/guild.endpoints-params.json:140:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_current_user_nick_params_init(struct discord_modify_current_user_nick_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_current_user_nick_params_cleanup(struct discord_modify_current_user_nick_params *)`
 *     * :code:`void discord_modify_current_user_nick_params_list_free(struct discord_modify_current_user_nick_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_current_user_nick_params_from_json(char *rbuf, size_t len, struct discord_modify_current_user_nick_params **)`
 *     * :code:`void discord_modify_current_user_nick_params_list_from_json(char *rbuf, size_t len, struct discord_modify_current_user_nick_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_current_user_nick_params_to_json(char *wbuf, size_t len, struct discord_modify_current_user_nick_params *)`
 *     * :code:`void discord_modify_current_user_nick_params_list_to_json(char *wbuf, size_t len, struct discord_modify_current_user_nick_params **)`
 * @endverbatim
 */
struct discord_modify_current_user_nick_params {
  /* specs/discord/guild.endpoints-params.json:143:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

};
extern void discord_modify_current_user_nick_params_cleanup_v(void *p);
extern void discord_modify_current_user_nick_params_cleanup(struct discord_modify_current_user_nick_params *p);
extern void discord_modify_current_user_nick_params_init_v(void *p);
extern void discord_modify_current_user_nick_params_init(struct discord_modify_current_user_nick_params *p);
extern void discord_modify_current_user_nick_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_current_user_nick_params_from_json(char *json, size_t len, struct discord_modify_current_user_nick_params **pp);
extern size_t discord_modify_current_user_nick_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_current_user_nick_params_to_json(char *json, size_t len, struct discord_modify_current_user_nick_params *p);
extern void discord_modify_current_user_nick_params_list_free_v(void **p);
extern void discord_modify_current_user_nick_params_list_free(struct discord_modify_current_user_nick_params **p);
extern void discord_modify_current_user_nick_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_current_user_nick_params_list_from_json(char *str, size_t len, struct discord_modify_current_user_nick_params ***p);
extern size_t discord_modify_current_user_nick_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_current_user_nick_params_list_to_json(char *str, size_t len, struct discord_modify_current_user_nick_params **p);

/* Create Guild Ban */
/* defined at specs/discord/guild.endpoints-params.json:149:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_ban_params_init(struct discord_create_guild_ban_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_ban_params_cleanup(struct discord_create_guild_ban_params *)`
 *     * :code:`void discord_create_guild_ban_params_list_free(struct discord_create_guild_ban_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_ban_params_from_json(char *rbuf, size_t len, struct discord_create_guild_ban_params **)`
 *     * :code:`void discord_create_guild_ban_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_ban_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_ban_params_to_json(char *wbuf, size_t len, struct discord_create_guild_ban_params *)`
 *     * :code:`void discord_create_guild_ban_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_ban_params **)`
 * @endverbatim
 */
struct discord_create_guild_ban_params {
  /* specs/discord/guild.endpoints-params.json:152:20
     '{ "name": "delete_message_days", "type":{ "base":"int" }, "comment":"number of days to delete messages for(0-7)"}' */
  int delete_message_days; /**< number of days to delete messages for(0-7) */

  /* specs/discord/guild.endpoints-params.json:153:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "comment":"reason for the ban (deprecated)", "inject_if_not":null }' */
  char *reason; /**< reason for the ban (deprecated) */

};
extern void discord_create_guild_ban_params_cleanup_v(void *p);
extern void discord_create_guild_ban_params_cleanup(struct discord_create_guild_ban_params *p);
extern void discord_create_guild_ban_params_init_v(void *p);
extern void discord_create_guild_ban_params_init(struct discord_create_guild_ban_params *p);
extern void discord_create_guild_ban_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_ban_params_from_json(char *json, size_t len, struct discord_create_guild_ban_params **pp);
extern size_t discord_create_guild_ban_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_ban_params_to_json(char *json, size_t len, struct discord_create_guild_ban_params *p);
extern void discord_create_guild_ban_params_list_free_v(void **p);
extern void discord_create_guild_ban_params_list_free(struct discord_create_guild_ban_params **p);
extern void discord_create_guild_ban_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_ban_params_list_from_json(char *str, size_t len, struct discord_create_guild_ban_params ***p);
extern size_t discord_create_guild_ban_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_ban_params_list_to_json(char *str, size_t len, struct discord_create_guild_ban_params **p);

/* Create Guild Role */
/* defined at specs/discord/guild.endpoints-params.json:159:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_role_params_init(struct discord_create_guild_role_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_role_params_cleanup(struct discord_create_guild_role_params *)`
 *     * :code:`void discord_create_guild_role_params_list_free(struct discord_create_guild_role_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_role_params_from_json(char *rbuf, size_t len, struct discord_create_guild_role_params **)`
 *     * :code:`void discord_create_guild_role_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_role_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_role_params_to_json(char *wbuf, size_t len, struct discord_create_guild_role_params *)`
 *     * :code:`void discord_create_guild_role_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_role_params **)`
 * @endverbatim
 */
struct discord_create_guild_role_params {
  /* specs/discord/guild.endpoints-params.json:162:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/guild.endpoints-params.json:163:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_bitwise_permission_flags" }, "inject_if_not":0}' */
  enum discord_bitwise_permission_flags permissions;

  /* specs/discord/guild.endpoints-params.json:164:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
  int color;

  /* specs/discord/guild.endpoints-params.json:165:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool hoist;

  /* specs/discord/guild.endpoints-params.json:166:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool mentionable;

};
extern void discord_create_guild_role_params_cleanup_v(void *p);
extern void discord_create_guild_role_params_cleanup(struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_init_v(void *p);
extern void discord_create_guild_role_params_init(struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_role_params_from_json(char *json, size_t len, struct discord_create_guild_role_params **pp);
extern size_t discord_create_guild_role_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_role_params_to_json(char *json, size_t len, struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_list_free_v(void **p);
extern void discord_create_guild_role_params_list_free(struct discord_create_guild_role_params **p);
extern void discord_create_guild_role_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_role_params_list_from_json(char *str, size_t len, struct discord_create_guild_role_params ***p);
extern size_t discord_create_guild_role_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_role_params_list_to_json(char *str, size_t len, struct discord_create_guild_role_params **p);

/* Modify Guild Role Positions */
/* defined at specs/discord/guild.endpoints-params.json:172:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_role_positions_params_init(struct discord_modify_guild_role_positions_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_role_positions_params_cleanup(struct discord_modify_guild_role_positions_params *)`
 *     * :code:`void discord_modify_guild_role_positions_params_list_free(struct discord_modify_guild_role_positions_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_role_positions_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_positions_params **)`
 *     * :code:`void discord_modify_guild_role_positions_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_positions_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_role_positions_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_positions_params *)`
 *     * :code:`void discord_modify_guild_role_positions_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_positions_params **)`
 * @endverbatim
 */
struct discord_modify_guild_role_positions_params {
  /* specs/discord/guild.endpoints-params.json:175:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
  u64_snowflake_t id; /**< role */

  /* specs/discord/guild.endpoints-params.json:176:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
  int position; /**< sorting position of the role */

};
extern void discord_modify_guild_role_positions_params_cleanup_v(void *p);
extern void discord_modify_guild_role_positions_params_cleanup(struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_init_v(void *p);
extern void discord_modify_guild_role_positions_params_init(struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_role_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_role_positions_params **pp);
extern size_t discord_modify_guild_role_positions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_list_free_v(void **p);
extern void discord_modify_guild_role_positions_params_list_free(struct discord_modify_guild_role_positions_params **p);
extern void discord_modify_guild_role_positions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_role_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_positions_params ***p);
extern size_t discord_modify_guild_role_positions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_role_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_positions_params **p);

/* Modify Guild Role */
/* defined at specs/discord/guild.endpoints-params.json:182:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_role_params_init(struct discord_modify_guild_role_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_role_params_cleanup(struct discord_modify_guild_role_params *)`
 *     * :code:`void discord_modify_guild_role_params_list_free(struct discord_modify_guild_role_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_role_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_params **)`
 *     * :code:`void discord_modify_guild_role_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_role_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_params *)`
 *     * :code:`void discord_modify_guild_role_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_params **)`
 * @endverbatim
 */
struct discord_modify_guild_role_params {
  /* specs/discord/guild.endpoints-params.json:185:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
  char *name; /**< name of the role */

  /* specs/discord/guild.endpoints-params.json:186:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_bitwise_permission_flags" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
  enum discord_bitwise_permission_flags permissions; /**< bitwise value of the enabled/disabled permissions */

  /* specs/discord/guild.endpoints-params.json:187:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
  int color; /**< RGB color value */

  /* specs/discord/guild.endpoints-params.json:188:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
  bool hoist; /**< whether the role should be displayed separately in the sidebar */

  /* specs/discord/guild.endpoints-params.json:189:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
  bool mentionable; /**< whether the role should be mentionable */

};
extern void discord_modify_guild_role_params_cleanup_v(void *p);
extern void discord_modify_guild_role_params_cleanup(struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_init_v(void *p);
extern void discord_modify_guild_role_params_init(struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_role_params_from_json(char *json, size_t len, struct discord_modify_guild_role_params **pp);
extern size_t discord_modify_guild_role_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_params_to_json(char *json, size_t len, struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_list_free_v(void **p);
extern void discord_modify_guild_role_params_list_free(struct discord_modify_guild_role_params **p);
extern void discord_modify_guild_role_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_role_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_params ***p);
extern size_t discord_modify_guild_role_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_role_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_params **p);

/* Get Guild Prune Count */
/* defined at specs/discord/guild.endpoints-params.json:195:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_get_guild_prune_count_params_init(struct discord_get_guild_prune_count_params *)`
 *   * Cleanup:

 *     * :code:`void discord_get_guild_prune_count_params_cleanup(struct discord_get_guild_prune_count_params *)`
 *     * :code:`void discord_get_guild_prune_count_params_list_free(struct discord_get_guild_prune_count_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_get_guild_prune_count_params_from_json(char *rbuf, size_t len, struct discord_get_guild_prune_count_params **)`
 *     * :code:`void discord_get_guild_prune_count_params_list_from_json(char *rbuf, size_t len, struct discord_get_guild_prune_count_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_get_guild_prune_count_params_to_json(char *wbuf, size_t len, struct discord_get_guild_prune_count_params *)`
 *     * :code:`void discord_get_guild_prune_count_params_list_to_json(char *wbuf, size_t len, struct discord_get_guild_prune_count_params **)`
 * @endverbatim
 */
struct discord_get_guild_prune_count_params {
  /* specs/discord/guild.endpoints-params.json:198:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  int days;

  /* specs/discord/guild.endpoints-params.json:199:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **include_roles;

};
extern void discord_get_guild_prune_count_params_cleanup_v(void *p);
extern void discord_get_guild_prune_count_params_cleanup(struct discord_get_guild_prune_count_params *p);
extern void discord_get_guild_prune_count_params_init_v(void *p);
extern void discord_get_guild_prune_count_params_init(struct discord_get_guild_prune_count_params *p);
extern void discord_get_guild_prune_count_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_guild_prune_count_params_from_json(char *json, size_t len, struct discord_get_guild_prune_count_params **pp);
extern size_t discord_get_guild_prune_count_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_guild_prune_count_params_to_json(char *json, size_t len, struct discord_get_guild_prune_count_params *p);
extern void discord_get_guild_prune_count_params_list_free_v(void **p);
extern void discord_get_guild_prune_count_params_list_free(struct discord_get_guild_prune_count_params **p);
extern void discord_get_guild_prune_count_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_guild_prune_count_params_list_from_json(char *str, size_t len, struct discord_get_guild_prune_count_params ***p);
extern size_t discord_get_guild_prune_count_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_guild_prune_count_params_list_to_json(char *str, size_t len, struct discord_get_guild_prune_count_params **p);

/* Begin Guild Prune */
/* defined at specs/discord/guild.endpoints-params.json:205:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_begin_guild_prune_params_init(struct discord_begin_guild_prune_params *)`
 *   * Cleanup:

 *     * :code:`void discord_begin_guild_prune_params_cleanup(struct discord_begin_guild_prune_params *)`
 *     * :code:`void discord_begin_guild_prune_params_list_free(struct discord_begin_guild_prune_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_begin_guild_prune_params_from_json(char *rbuf, size_t len, struct discord_begin_guild_prune_params **)`
 *     * :code:`void discord_begin_guild_prune_params_list_from_json(char *rbuf, size_t len, struct discord_begin_guild_prune_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_begin_guild_prune_params_to_json(char *wbuf, size_t len, struct discord_begin_guild_prune_params *)`
 *     * :code:`void discord_begin_guild_prune_params_list_to_json(char *wbuf, size_t len, struct discord_begin_guild_prune_params **)`
 * @endverbatim
 */
struct discord_begin_guild_prune_params {
  /* specs/discord/guild.endpoints-params.json:208:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  int days;

  /* specs/discord/guild.endpoints-params.json:209:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool compute_prune_count;

  /* specs/discord/guild.endpoints-params.json:210:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **include_roles;

  /* specs/discord/guild.endpoints-params.json:211:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *reason;

};
extern void discord_begin_guild_prune_params_cleanup_v(void *p);
extern void discord_begin_guild_prune_params_cleanup(struct discord_begin_guild_prune_params *p);
extern void discord_begin_guild_prune_params_init_v(void *p);
extern void discord_begin_guild_prune_params_init(struct discord_begin_guild_prune_params *p);
extern void discord_begin_guild_prune_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_begin_guild_prune_params_from_json(char *json, size_t len, struct discord_begin_guild_prune_params **pp);
extern size_t discord_begin_guild_prune_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_begin_guild_prune_params_to_json(char *json, size_t len, struct discord_begin_guild_prune_params *p);
extern void discord_begin_guild_prune_params_list_free_v(void **p);
extern void discord_begin_guild_prune_params_list_free(struct discord_begin_guild_prune_params **p);
extern void discord_begin_guild_prune_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_begin_guild_prune_params_list_from_json(char *str, size_t len, struct discord_begin_guild_prune_params ***p);
extern size_t discord_begin_guild_prune_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_begin_guild_prune_params_list_to_json(char *str, size_t len, struct discord_begin_guild_prune_params **p);
