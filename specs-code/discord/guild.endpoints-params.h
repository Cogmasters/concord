/* This file is generated from specs/discord/guild.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/guild.endpoints-params.h
 * @see https://discord.com/developers/docs/resources/guild
 */


// Create Guild
// defined at specs/discord/guild.endpoints-params.json:10:22
/**
 * @see https://discord.com/developers/docs/resources/guild#create-guild
 *
 * - Initializer:
 *   - <tt> discord_create_guild_params_init(struct discord_create_guild_params *) </tt>
 * - Cleanup:
 *   - <tt> discord_create_guild_params_cleanup(struct discord_create_guild_params *) </tt>
 *   - <tt> discord_create_guild_params_list_free(struct discord_create_guild_params **) </tt>
 * - JSON Decoder:
 *   - <tt> discord_create_guild_params_from_json(char *rbuf, size_t len, struct discord_create_guild_params **) </tt>
 *   - <tt> discord_create_guild_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_create_guild_params_to_json(char *wbuf, size_t len, struct discord_create_guild_params *) </tt>
 *   - <tt> discord_create_guild_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_params **) </tt>
 */
struct discord_create_guild_params {
  /* specs/discord/guild.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  char *name; ///< name of the guild (2-100) characters

  /* specs/discord/guild.endpoints-params.json:14:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  char *region; ///< voice region id

  /* specs/discord/guild.endpoints-params.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  char *icon; ///< base64 128x1128 image for the guild icon

  /* specs/discord/guild.endpoints-params.json:16:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  int verification_level; ///< verification level

  /* specs/discord/guild.endpoints-params.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  int default_message_notifications; ///< default message notification level

  /* specs/discord/guild.endpoints-params.json:18:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  int explicit_content_filter; ///< explicit content filter level

  /* specs/discord/guild.endpoints-params.json:19:20
     '{ "name": "roles", "type":{ "base":"int" }, "todo":true, "comment":"new guild roles" }' */
  // @todo roles new guild roles;

  /* specs/discord/guild.endpoints-params.json:20:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
  struct discord_channel **channels; ///< array of partial channel objects

  /* specs/discord/guild.endpoints-params.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  u64_snowflake_t afk_channel_id; ///< id for afk channel

  /* specs/discord/guild.endpoints-params.json:22:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  int afk_timeout; ///< afk timeout in seconds

  /* specs/discord/guild.endpoints-params.json:23:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  u64_snowflake_t system_channel_id; ///< the id of the channel where guild notices such as welcome messages and boost events are posted

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[11];
    void *record_defined[11];
    void *record_null[11];
  } __M; // metadata
/// @endcond
};
extern void discord_create_guild_params_cleanup_v(void *p);
extern void discord_create_guild_params_cleanup(struct discord_create_guild_params *p);
extern void discord_create_guild_params_init_v(void *p);
extern void discord_create_guild_params_init(struct discord_create_guild_params *p);
extern void discord_create_guild_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_params_from_json(char *json, size_t len, struct discord_create_guild_params **pp);
extern size_t discord_create_guild_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_params_to_json(char *json, size_t len, struct discord_create_guild_params *p);
extern size_t discord_create_guild_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_params_to_query(char *json, size_t len, struct discord_create_guild_params *p);
extern void discord_create_guild_params_list_free_v(void **p);
extern void discord_create_guild_params_list_free(struct discord_create_guild_params **p);
extern void discord_create_guild_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_params_list_from_json(char *str, size_t len, struct discord_create_guild_params ***p);
extern size_t discord_create_guild_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_params_list_to_json(char *str, size_t len, struct discord_create_guild_params **p);

// Modify Guild
// defined at specs/discord/guild.endpoints-params.json:30:22
/**
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-json-params
 *
 * - Initializer:
 *   - <tt> discord_modify_guild_params_init(struct discord_modify_guild_params *) </tt>
 * - Cleanup:
 *   - <tt> discord_modify_guild_params_cleanup(struct discord_modify_guild_params *) </tt>
 *   - <tt> discord_modify_guild_params_list_free(struct discord_modify_guild_params **) </tt>
 * - JSON Decoder:
 *   - <tt> discord_modify_guild_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_params **) </tt>
 *   - <tt> discord_modify_guild_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_modify_guild_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_params *) </tt>
 *   - <tt> discord_modify_guild_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_params **) </tt>
 */
struct discord_modify_guild_params {
  /* specs/discord/guild.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  char *name; ///< name of the guild (2-100) characters

  /* specs/discord/guild.endpoints-params.json:34:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  char *region; ///< voice region id

  /* specs/discord/guild.endpoints-params.json:35:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  int verification_level; ///< verification level

  /* specs/discord/guild.endpoints-params.json:36:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  int default_message_notifications; ///< default message notification level

  /* specs/discord/guild.endpoints-params.json:37:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  int explicit_content_filter; ///< explicit content filter level

  /* specs/discord/guild.endpoints-params.json:38:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  u64_snowflake_t afk_channel_id; ///< id for afk channel

  /* specs/discord/guild.endpoints-params.json:39:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  int afk_timeout; ///< afk timeout in seconds

  /* specs/discord/guild.endpoints-params.json:40:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  char *icon; ///< base64 128x1128 image for the guild icon

  /* specs/discord/guild.endpoints-params.json:41:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
  u64_snowflake_t owner_id; ///< user id to transfer guild ownership to (must be owner)

  /* specs/discord/guild.endpoints-params.json:42:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
  char *splash; ///< base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature

  /* specs/discord/guild.endpoints-params.json:43:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
  char *discovery_splash; ///< base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)

  /* specs/discord/guild.endpoints-params.json:44:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
  char *banner; ///< cannot unescape an ill-formed-string 	base64 16:9 png/jpeg image for the guild banner (wh

  /* specs/discord/guild.endpoints-params.json:45:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  u64_snowflake_t system_channel_id; ///< cannot unescape an ill-formed-string 	the id of the channel where guild notices such as welcome

  /* specs/discord/guild.endpoints-params.json:46:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
  enum discord_guild_system_channel_flags system_channel_flags; ///< system channel flags

  /* specs/discord/guild.endpoints-params.json:47:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
  u64_snowflake_t rules_channel_id; ///< the id of the channel where Community guilds display rules and/or guidelines

  /* specs/discord/guild.endpoints-params.json:48:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
  u64_snowflake_t public_updates_channel_id; ///< the id of the channel where admins and moderators of Community guilds receive notices from Discord

  /* specs/discord/guild.endpoints-params.json:49:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
  char *preferred_locale; ///< the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to "en-US"

  /* specs/discord/guild.endpoints-params.json:50:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "todo":true, "comment":"array of guild feature strings"}' */
  // @todo features array of guild feature strings;

  /* specs/discord/guild.endpoints-params.json:51:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
  char *description; ///< the description for the guild, if the guild is discoverable

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[19];
    void *record_defined[19];
    void *record_null[19];
  } __M; // metadata
/// @endcond
};
extern void discord_modify_guild_params_cleanup_v(void *p);
extern void discord_modify_guild_params_cleanup(struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_init_v(void *p);
extern void discord_modify_guild_params_init(struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_params_from_json(char *json, size_t len, struct discord_modify_guild_params **pp);
extern size_t discord_modify_guild_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_params_to_json(char *json, size_t len, struct discord_modify_guild_params *p);
extern size_t discord_modify_guild_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_params_to_query(char *json, size_t len, struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_list_free_v(void **p);
extern void discord_modify_guild_params_list_free(struct discord_modify_guild_params **p);
extern void discord_modify_guild_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_params_list_from_json(char *str, size_t len, struct discord_modify_guild_params ***p);
extern size_t discord_modify_guild_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_params_list_to_json(char *str, size_t len, struct discord_modify_guild_params **p);

// Create Guild Channel
// defined at specs/discord/guild.endpoints-params.json:58:22
/**
 * @see https://discord.com/developers/docs/resources/guild#create-guild-channel
 *
 * - Initializer:
 *   - <tt> discord_create_guild_channel_params_init(struct discord_create_guild_channel_params *) </tt>
 * - Cleanup:
 *   - <tt> discord_create_guild_channel_params_cleanup(struct discord_create_guild_channel_params *) </tt>
 *   - <tt> discord_create_guild_channel_params_list_free(struct discord_create_guild_channel_params **) </tt>
 * - JSON Decoder:
 *   - <tt> discord_create_guild_channel_params_from_json(char *rbuf, size_t len, struct discord_create_guild_channel_params **) </tt>
 *   - <tt> discord_create_guild_channel_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_channel_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_create_guild_channel_params_to_json(char *wbuf, size_t len, struct discord_create_guild_channel_params *) </tt>
 *   - <tt> discord_create_guild_channel_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_channel_params **) </tt>
 */
struct discord_create_guild_channel_params {
  /* specs/discord/guild.endpoints-params.json:61:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/guild.endpoints-params.json:62:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  /* specs/discord/guild.endpoints-params.json:63:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
  char *topic;

  /* specs/discord/guild.endpoints-params.json:64:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
  int bitrate;

  /* specs/discord/guild.endpoints-params.json:65:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
  int user_limit;

  /* specs/discord/guild.endpoints-params.json:66:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
  int rate_limit_per_user;

  /* specs/discord/guild.endpoints-params.json:67:20
     '{ "name": "position", "type":{ "base":"int" } }' */
  int position;

  /* specs/discord/guild.endpoints-params.json:68:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
  struct discord_channel_overwrite **permission_overwrites;

  /* specs/discord/guild.endpoints-params.json:69:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  u64_snowflake_t parent_id;

  /* specs/discord/guild.endpoints-params.json:70:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
  bool nsfw;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[10];
    void *record_defined[10];
    void *record_null[10];
  } __M; // metadata
/// @endcond
};
extern void discord_create_guild_channel_params_cleanup_v(void *p);
extern void discord_create_guild_channel_params_cleanup(struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_init_v(void *p);
extern void discord_create_guild_channel_params_init(struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_channel_params_from_json(char *json, size_t len, struct discord_create_guild_channel_params **pp);
extern size_t discord_create_guild_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_channel_params_to_json(char *json, size_t len, struct discord_create_guild_channel_params *p);
extern size_t discord_create_guild_channel_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_channel_params_to_query(char *json, size_t len, struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_list_free_v(void **p);
extern void discord_create_guild_channel_params_list_free(struct discord_create_guild_channel_params **p);
extern void discord_create_guild_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_channel_params_list_from_json(char *str, size_t len, struct discord_create_guild_channel_params ***p);
extern size_t discord_create_guild_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_channel_params_list_to_json(char *str, size_t len, struct discord_create_guild_channel_params **p);

// Modify Guild Channel Positions
// defined at specs/discord/guild.endpoints-params.json:77:22
/**
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-channel-positions-json-params
 *
 * - Initializer:
 *   - <tt> discord_modify_guild_channel_positions_params_init(struct discord_modify_guild_channel_positions_params *) </tt>
 * - Cleanup:
 *   - <tt> discord_modify_guild_channel_positions_params_cleanup(struct discord_modify_guild_channel_positions_params *) </tt>
 *   - <tt> discord_modify_guild_channel_positions_params_list_free(struct discord_modify_guild_channel_positions_params **) </tt>
 * - JSON Decoder:
 *   - <tt> discord_modify_guild_channel_positions_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_channel_positions_params **) </tt>
 *   - <tt> discord_modify_guild_channel_positions_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_channel_positions_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_modify_guild_channel_positions_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_channel_positions_params *) </tt>
 *   - <tt> discord_modify_guild_channel_positions_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_channel_positions_params **) </tt>
 */
struct discord_modify_guild_channel_positions_params {
  /* specs/discord/guild.endpoints-params.json:80:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
  u64_snowflake_t id; ///< channel id

  /* specs/discord/guild.endpoints-params.json:81:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
  int position; ///< sorting position of the channel

  /* specs/discord/guild.endpoints-params.json:82:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
  bool lock_permissions; ///< syncs the permission overwrites with the new parent, if moving to a new category

  /* specs/discord/guild.endpoints-params.json:83:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
  u64_snowflake_t parent_id; ///< the new parent ID for the channel that is moved

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};
extern void discord_modify_guild_channel_positions_params_cleanup_v(void *p);
extern void discord_modify_guild_channel_positions_params_cleanup(struct discord_modify_guild_channel_positions_params *p);
extern void discord_modify_guild_channel_positions_params_init_v(void *p);
extern void discord_modify_guild_channel_positions_params_init(struct discord_modify_guild_channel_positions_params *p);
extern void discord_modify_guild_channel_positions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_channel_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params **pp);
extern size_t discord_modify_guild_channel_positions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_channel_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params *p);
extern size_t discord_modify_guild_channel_positions_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_channel_positions_params_to_query(char *json, size_t len, struct discord_modify_guild_channel_positions_params *p);
extern void discord_modify_guild_channel_positions_params_list_free_v(void **p);
extern void discord_modify_guild_channel_positions_params_list_free(struct discord_modify_guild_channel_positions_params **p);
extern void discord_modify_guild_channel_positions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_channel_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params ***p);
extern size_t discord_modify_guild_channel_positions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_channel_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params **p);

// Search Guild Members
// defined at specs/discord/guild.endpoints-params.json:90:22
/**
 * @see https://discord.com/developers/docs/resources/guild#search-guild-members-query-string-params
 *
 * - Initializer:
 *   - <tt> discord_search_guild_members_params_init(struct discord_search_guild_members_params *) </tt>
 * - Cleanup:
 *   - <tt> discord_search_guild_members_params_cleanup(struct discord_search_guild_members_params *) </tt>
 *   - <tt> discord_search_guild_members_params_list_free(struct discord_search_guild_members_params **) </tt>
 * - JSON Decoder:
 *   - <tt> discord_search_guild_members_params_from_json(char *rbuf, size_t len, struct discord_search_guild_members_params **) </tt>
 *   - <tt> discord_search_guild_members_params_list_from_json(char *rbuf, size_t len, struct discord_search_guild_members_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_search_guild_members_params_to_json(char *wbuf, size_t len, struct discord_search_guild_members_params *) </tt>
 *   - <tt> discord_search_guild_members_params_list_to_json(char *wbuf, size_t len, struct discord_search_guild_members_params **) </tt>
 */
struct discord_search_guild_members_params {
  /* specs/discord/guild.endpoints-params.json:93:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
  char *query; ///< Query string to match username(s) and nickname(s) against.

  /* specs/discord/guild.endpoints-params.json:94:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
  int limit; ///< max number of members to return (1-1000)

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
extern void discord_search_guild_members_params_cleanup_v(void *p);
extern void discord_search_guild_members_params_cleanup(struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_init_v(void *p);
extern void discord_search_guild_members_params_init(struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_search_guild_members_params_from_json(char *json, size_t len, struct discord_search_guild_members_params **pp);
extern size_t discord_search_guild_members_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_search_guild_members_params_to_json(char *json, size_t len, struct discord_search_guild_members_params *p);
extern size_t discord_search_guild_members_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_search_guild_members_params_to_query(char *json, size_t len, struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_list_free_v(void **p);
extern void discord_search_guild_members_params_list_free(struct discord_search_guild_members_params **p);
extern void discord_search_guild_members_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_search_guild_members_params_list_from_json(char *str, size_t len, struct discord_search_guild_members_params ***p);
extern size_t discord_search_guild_members_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_search_guild_members_params_list_to_json(char *str, size_t len, struct discord_search_guild_members_params **p);

// Add Guild Member
// defined at specs/discord/guild.endpoints-params.json:101:22
/**
 * @see https://discord.com/developers/docs/resources/guild#add-guild-member-json-params
 *
 * - Initializer:
 *   - <tt> discord_add_guild_member_params_init(struct discord_add_guild_member_params *) </tt>
 * - Cleanup:
 *   - <tt> discord_add_guild_member_params_cleanup(struct discord_add_guild_member_params *) </tt>
 *   - <tt> discord_add_guild_member_params_list_free(struct discord_add_guild_member_params **) </tt>
 * - JSON Decoder:
 *   - <tt> discord_add_guild_member_params_from_json(char *rbuf, size_t len, struct discord_add_guild_member_params **) </tt>
 *   - <tt> discord_add_guild_member_params_list_from_json(char *rbuf, size_t len, struct discord_add_guild_member_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_add_guild_member_params_to_json(char *wbuf, size_t len, struct discord_add_guild_member_params *) </tt>
 *   - <tt> discord_add_guild_member_params_list_to_json(char *wbuf, size_t len, struct discord_add_guild_member_params **) </tt>
 */
struct discord_add_guild_member_params {
  /* specs/discord/guild.endpoints-params.json:104:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *access_token;

  /* specs/discord/guild.endpoints-params.json:105:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *nick;

  /* specs/discord/guild.endpoints-params.json:106:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **roles;

  /* specs/discord/guild.endpoints-params.json:107:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool mute;

  /* specs/discord/guild.endpoints-params.json:108:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool deaf;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};
extern void discord_add_guild_member_params_cleanup_v(void *p);
extern void discord_add_guild_member_params_cleanup(struct discord_add_guild_member_params *p);
extern void discord_add_guild_member_params_init_v(void *p);
extern void discord_add_guild_member_params_init(struct discord_add_guild_member_params *p);
extern void discord_add_guild_member_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_add_guild_member_params_from_json(char *json, size_t len, struct discord_add_guild_member_params **pp);
extern size_t discord_add_guild_member_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_add_guild_member_params_to_json(char *json, size_t len, struct discord_add_guild_member_params *p);
extern size_t discord_add_guild_member_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_add_guild_member_params_to_query(char *json, size_t len, struct discord_add_guild_member_params *p);
extern void discord_add_guild_member_params_list_free_v(void **p);
extern void discord_add_guild_member_params_list_free(struct discord_add_guild_member_params **p);
extern void discord_add_guild_member_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_add_guild_member_params_list_from_json(char *str, size_t len, struct discord_add_guild_member_params ***p);
extern size_t discord_add_guild_member_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_add_guild_member_params_list_to_json(char *str, size_t len, struct discord_add_guild_member_params **p);

// Modify Guild Member
// defined at specs/discord/guild.endpoints-params.json:115:22
/**
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-member
 *
 * - Initializer:
 *   - <tt> discord_modify_guild_member_params_init(struct discord_modify_guild_member_params *) </tt>
 * - Cleanup:
 *   - <tt> discord_modify_guild_member_params_cleanup(struct discord_modify_guild_member_params *) </tt>
 *   - <tt> discord_modify_guild_member_params_list_free(struct discord_modify_guild_member_params **) </tt>
 * - JSON Decoder:
 *   - <tt> discord_modify_guild_member_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_member_params **) </tt>
 *   - <tt> discord_modify_guild_member_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_member_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_modify_guild_member_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_member_params *) </tt>
 *   - <tt> discord_modify_guild_member_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_member_params **) </tt>
 */
struct discord_modify_guild_member_params {
  /* specs/discord/guild.endpoints-params.json:118:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

  /* specs/discord/guild.endpoints-params.json:119:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **roles;

  /* specs/discord/guild.endpoints-params.json:120:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool mute;

  /* specs/discord/guild.endpoints-params.json:121:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool deaf;

  /* specs/discord/guild.endpoints-params.json:122:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  u64_snowflake_t channel_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};
extern void discord_modify_guild_member_params_cleanup_v(void *p);
extern void discord_modify_guild_member_params_cleanup(struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_init_v(void *p);
extern void discord_modify_guild_member_params_init(struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_member_params_from_json(char *json, size_t len, struct discord_modify_guild_member_params **pp);
extern size_t discord_modify_guild_member_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_member_params_to_json(char *json, size_t len, struct discord_modify_guild_member_params *p);
extern size_t discord_modify_guild_member_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_member_params_to_query(char *json, size_t len, struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_list_free_v(void **p);
extern void discord_modify_guild_member_params_list_free(struct discord_modify_guild_member_params **p);
extern void discord_modify_guild_member_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_member_params_list_from_json(char *str, size_t len, struct discord_modify_guild_member_params ***p);
extern size_t discord_modify_guild_member_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_member_params_list_to_json(char *str, size_t len, struct discord_modify_guild_member_params **p);

// Create Guild Role
// defined at specs/discord/guild.endpoints-params.json:129:22
/**
 * @see https://discord.com/developers/docs/resources/guild#create-guild-role
 *
 * - Initializer:
 *   - <tt> discord_create_guild_role_params_init(struct discord_create_guild_role_params *) </tt>
 * - Cleanup:
 *   - <tt> discord_create_guild_role_params_cleanup(struct discord_create_guild_role_params *) </tt>
 *   - <tt> discord_create_guild_role_params_list_free(struct discord_create_guild_role_params **) </tt>
 * - JSON Decoder:
 *   - <tt> discord_create_guild_role_params_from_json(char *rbuf, size_t len, struct discord_create_guild_role_params **) </tt>
 *   - <tt> discord_create_guild_role_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_role_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_create_guild_role_params_to_json(char *wbuf, size_t len, struct discord_create_guild_role_params *) </tt>
 *   - <tt> discord_create_guild_role_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_role_params **) </tt>
 */
struct discord_create_guild_role_params {
  /* specs/discord/guild.endpoints-params.json:132:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/guild.endpoints-params.json:133:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "inject_if_not":0}' */
  enum discord_permissions_bitwise_flags permissions;

  /* specs/discord/guild.endpoints-params.json:134:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
  int color;

  /* specs/discord/guild.endpoints-params.json:135:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool hoist;

  /* specs/discord/guild.endpoints-params.json:136:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool mentionable;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};
extern void discord_create_guild_role_params_cleanup_v(void *p);
extern void discord_create_guild_role_params_cleanup(struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_init_v(void *p);
extern void discord_create_guild_role_params_init(struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_role_params_from_json(char *json, size_t len, struct discord_create_guild_role_params **pp);
extern size_t discord_create_guild_role_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_role_params_to_json(char *json, size_t len, struct discord_create_guild_role_params *p);
extern size_t discord_create_guild_role_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_role_params_to_query(char *json, size_t len, struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_list_free_v(void **p);
extern void discord_create_guild_role_params_list_free(struct discord_create_guild_role_params **p);
extern void discord_create_guild_role_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_role_params_list_from_json(char *str, size_t len, struct discord_create_guild_role_params ***p);
extern size_t discord_create_guild_role_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_role_params_list_to_json(char *str, size_t len, struct discord_create_guild_role_params **p);

// Modify Guild Role Positions
// defined at specs/discord/guild.endpoints-params.json:143:22
/**
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-role-positions-json-params
 *
 * - Initializer:
 *   - <tt> discord_modify_guild_role_positions_params_init(struct discord_modify_guild_role_positions_params *) </tt>
 * - Cleanup:
 *   - <tt> discord_modify_guild_role_positions_params_cleanup(struct discord_modify_guild_role_positions_params *) </tt>
 *   - <tt> discord_modify_guild_role_positions_params_list_free(struct discord_modify_guild_role_positions_params **) </tt>
 * - JSON Decoder:
 *   - <tt> discord_modify_guild_role_positions_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_positions_params **) </tt>
 *   - <tt> discord_modify_guild_role_positions_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_positions_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_modify_guild_role_positions_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_positions_params *) </tt>
 *   - <tt> discord_modify_guild_role_positions_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_positions_params **) </tt>
 */
struct discord_modify_guild_role_positions_params {
  /* specs/discord/guild.endpoints-params.json:146:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
  u64_snowflake_t id; ///< role

  /* specs/discord/guild.endpoints-params.json:147:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
  int position; ///< sorting position of the role

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
extern void discord_modify_guild_role_positions_params_cleanup_v(void *p);
extern void discord_modify_guild_role_positions_params_cleanup(struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_init_v(void *p);
extern void discord_modify_guild_role_positions_params_init(struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_role_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_role_positions_params **pp);
extern size_t discord_modify_guild_role_positions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_role_positions_params *p);
extern size_t discord_modify_guild_role_positions_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_positions_params_to_query(char *json, size_t len, struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_list_free_v(void **p);
extern void discord_modify_guild_role_positions_params_list_free(struct discord_modify_guild_role_positions_params **p);
extern void discord_modify_guild_role_positions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_role_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_positions_params ***p);
extern size_t discord_modify_guild_role_positions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_role_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_positions_params **p);

// Modify Guild Role
// defined at specs/discord/guild.endpoints-params.json:154:22
/**
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-role-json-params
 *
 * - Initializer:
 *   - <tt> discord_modify_guild_role_params_init(struct discord_modify_guild_role_params *) </tt>
 * - Cleanup:
 *   - <tt> discord_modify_guild_role_params_cleanup(struct discord_modify_guild_role_params *) </tt>
 *   - <tt> discord_modify_guild_role_params_list_free(struct discord_modify_guild_role_params **) </tt>
 * - JSON Decoder:
 *   - <tt> discord_modify_guild_role_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_params **) </tt>
 *   - <tt> discord_modify_guild_role_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_modify_guild_role_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_params *) </tt>
 *   - <tt> discord_modify_guild_role_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_params **) </tt>
 */
struct discord_modify_guild_role_params {
  /* specs/discord/guild.endpoints-params.json:157:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
  char *name; ///< name of the role

  /* specs/discord/guild.endpoints-params.json:158:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
  enum discord_permissions_bitwise_flags permissions; ///< bitwise value of the enabled/disabled permissions

  /* specs/discord/guild.endpoints-params.json:159:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
  int color; ///< RGB color value

  /* specs/discord/guild.endpoints-params.json:160:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
  bool hoist; ///< whether the role should be displayed separately in the sidebar

  /* specs/discord/guild.endpoints-params.json:161:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
  bool mentionable; ///< whether the role should be mentionable

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};
extern void discord_modify_guild_role_params_cleanup_v(void *p);
extern void discord_modify_guild_role_params_cleanup(struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_init_v(void *p);
extern void discord_modify_guild_role_params_init(struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_role_params_from_json(char *json, size_t len, struct discord_modify_guild_role_params **pp);
extern size_t discord_modify_guild_role_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_params_to_json(char *json, size_t len, struct discord_modify_guild_role_params *p);
extern size_t discord_modify_guild_role_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_params_to_query(char *json, size_t len, struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_list_free_v(void **p);
extern void discord_modify_guild_role_params_list_free(struct discord_modify_guild_role_params **p);
extern void discord_modify_guild_role_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_role_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_params ***p);
extern size_t discord_modify_guild_role_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_role_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_params **p);

// Get Guild Prune Count
// defined at specs/discord/guild.endpoints-params.json:168:22
/**
 * @see https://discord.com/developers/docs/resources/guild#get-guild-prune-count-query-string-params
 *
 * - Initializer:
 *   - <tt> discord_get_guild_prune_count_params_init(struct discord_get_guild_prune_count_params *) </tt>
 * - Cleanup:
 *   - <tt> discord_get_guild_prune_count_params_cleanup(struct discord_get_guild_prune_count_params *) </tt>
 *   - <tt> discord_get_guild_prune_count_params_list_free(struct discord_get_guild_prune_count_params **) </tt>
 * - JSON Decoder:
 *   - <tt> discord_get_guild_prune_count_params_from_json(char *rbuf, size_t len, struct discord_get_guild_prune_count_params **) </tt>
 *   - <tt> discord_get_guild_prune_count_params_list_from_json(char *rbuf, size_t len, struct discord_get_guild_prune_count_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_get_guild_prune_count_params_to_json(char *wbuf, size_t len, struct discord_get_guild_prune_count_params *) </tt>
 *   - <tt> discord_get_guild_prune_count_params_list_to_json(char *wbuf, size_t len, struct discord_get_guild_prune_count_params **) </tt>
 */
struct discord_get_guild_prune_count_params {
  /* specs/discord/guild.endpoints-params.json:171:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  int days;

  /* specs/discord/guild.endpoints-params.json:172:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **include_roles;

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
extern void discord_get_guild_prune_count_params_cleanup_v(void *p);
extern void discord_get_guild_prune_count_params_cleanup(struct discord_get_guild_prune_count_params *p);
extern void discord_get_guild_prune_count_params_init_v(void *p);
extern void discord_get_guild_prune_count_params_init(struct discord_get_guild_prune_count_params *p);
extern void discord_get_guild_prune_count_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_guild_prune_count_params_from_json(char *json, size_t len, struct discord_get_guild_prune_count_params **pp);
extern size_t discord_get_guild_prune_count_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_guild_prune_count_params_to_json(char *json, size_t len, struct discord_get_guild_prune_count_params *p);
extern size_t discord_get_guild_prune_count_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_get_guild_prune_count_params_to_query(char *json, size_t len, struct discord_get_guild_prune_count_params *p);
extern void discord_get_guild_prune_count_params_list_free_v(void **p);
extern void discord_get_guild_prune_count_params_list_free(struct discord_get_guild_prune_count_params **p);
extern void discord_get_guild_prune_count_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_guild_prune_count_params_list_from_json(char *str, size_t len, struct discord_get_guild_prune_count_params ***p);
extern size_t discord_get_guild_prune_count_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_guild_prune_count_params_list_to_json(char *str, size_t len, struct discord_get_guild_prune_count_params **p);

// Begin Guild Prune
// defined at specs/discord/guild.endpoints-params.json:179:22
/**
 * @see https://discord.com/developers/docs/resources/guild#begin-guild-prune-json-params
 *
 * - Initializer:
 *   - <tt> discord_begin_guild_prune_params_init(struct discord_begin_guild_prune_params *) </tt>
 * - Cleanup:
 *   - <tt> discord_begin_guild_prune_params_cleanup(struct discord_begin_guild_prune_params *) </tt>
 *   - <tt> discord_begin_guild_prune_params_list_free(struct discord_begin_guild_prune_params **) </tt>
 * - JSON Decoder:
 *   - <tt> discord_begin_guild_prune_params_from_json(char *rbuf, size_t len, struct discord_begin_guild_prune_params **) </tt>
 *   - <tt> discord_begin_guild_prune_params_list_from_json(char *rbuf, size_t len, struct discord_begin_guild_prune_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_begin_guild_prune_params_to_json(char *wbuf, size_t len, struct discord_begin_guild_prune_params *) </tt>
 *   - <tt> discord_begin_guild_prune_params_list_to_json(char *wbuf, size_t len, struct discord_begin_guild_prune_params **) </tt>
 */
struct discord_begin_guild_prune_params {
  /* specs/discord/guild.endpoints-params.json:182:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  int days;

  /* specs/discord/guild.endpoints-params.json:183:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool compute_prune_count;

  /* specs/discord/guild.endpoints-params.json:184:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **include_roles;

  /* specs/discord/guild.endpoints-params.json:185:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *reason;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};
extern void discord_begin_guild_prune_params_cleanup_v(void *p);
extern void discord_begin_guild_prune_params_cleanup(struct discord_begin_guild_prune_params *p);
extern void discord_begin_guild_prune_params_init_v(void *p);
extern void discord_begin_guild_prune_params_init(struct discord_begin_guild_prune_params *p);
extern void discord_begin_guild_prune_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_begin_guild_prune_params_from_json(char *json, size_t len, struct discord_begin_guild_prune_params **pp);
extern size_t discord_begin_guild_prune_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_begin_guild_prune_params_to_json(char *json, size_t len, struct discord_begin_guild_prune_params *p);
extern size_t discord_begin_guild_prune_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_begin_guild_prune_params_to_query(char *json, size_t len, struct discord_begin_guild_prune_params *p);
extern void discord_begin_guild_prune_params_list_free_v(void **p);
extern void discord_begin_guild_prune_params_list_free(struct discord_begin_guild_prune_params **p);
extern void discord_begin_guild_prune_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_begin_guild_prune_params_list_from_json(char *str, size_t len, struct discord_begin_guild_prune_params ***p);
extern size_t discord_begin_guild_prune_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_begin_guild_prune_params_list_to_json(char *str, size_t len, struct discord_begin_guild_prune_params **p);
