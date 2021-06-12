/* This file is generated from specs/discord/guild.modify-guild.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#modify-guild-json-params */
/* This is defined at specs/discord/guild.modify-guild.json:8:22 */
struct discord_modify_guild_params {
  /* specs/discord/guild.modify-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
  char *name; // name of the guild (2-100) characters

  /* specs/discord/guild.modify-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
  char *region; // voice region id

  /* specs/discord/guild.modify-guild.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
  int verification_level; // verification level

  /* specs/discord/guild.modify-guild.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
  int default_message_notifications; // default message notification level

  /* specs/discord/guild.modify-guild.json:19:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
  int explicit_content_filter; // explicit content filter level

  /* specs/discord/guild.modify-guild.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
  u64_snowflake_t afk_channel_id; // id for afk channel

  /* specs/discord/guild.modify-guild.json:23:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
  int afk_timeout; // afk timeout in seconds

  /* specs/discord/guild.modify-guild.json:25:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
  char *icon; // base64 128x1128 image for the guild icon

  /* specs/discord/guild.modify-guild.json:27:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}'
  */
  u64_snowflake_t owner_id; // user id to transfer guild ownership to (must be owner)

  /* specs/discord/guild.modify-guild.json:29:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}'
  */
  char *splash; // base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature

  /* specs/discord/guild.modify-guild.json:31:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}'
  */
  char *discovery_splash; // base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)

  /* specs/discord/guild.modify-guild.json:33:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}'
  */
  char *banner; // cannot unescape an ill-formed-string 	base64 16:9 png/jpeg image for the guild banner (wh

  /* specs/discord/guild.modify-guild.json:35:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
  u64_snowflake_t system_channel_id; // cannot unescape an ill-formed-string 	the id of the channel where guild notices such as welcome

  /* specs/discord/guild.modify-guild.json:37:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, 
          "option":true, "inject_if_not":0, "comment":"system channel flags"}'
  */
  enum discord_guild_system_channel_flags system_channel_flags; // system channel flags

  /* specs/discord/guild.modify-guild.json:39:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}'
  */
  u64_snowflake_t rules_channel_id; // the id of the channel where Community guilds display rules and/or guidelines

  /* specs/discord/guild.modify-guild.json:41:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}'
  */
  u64_snowflake_t public_updates_channel_id; // the id of the channel where admins and moderators of Community guilds receive notices from Discord

  /* specs/discord/guild.modify-guild.json:43:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}'
  */
  char *preferred_locale; // the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to "en-US"

  /* specs/discord/guild.modify-guild.json:45:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, 
          "todo":true", "comment":"array of guild feature strings"}'
  */
  //@todo features array of guild feature strings;

  /* specs/discord/guild.modify-guild.json:47:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the description for the guild, if the guild is discoverable"}'
  */
  char *description; // the description for the guild, if the guild is discoverable

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[19];
    void *record_defined[19];
    void *record_null[19];
  } __M; // metadata
};
extern void discord_modify_guild_params_cleanup_v(void *p);
extern void discord_modify_guild_params_cleanup(struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_init_v(void *p);
extern void discord_modify_guild_params_init(struct discord_modify_guild_params *p);
extern struct discord_modify_guild_params * discord_modify_guild_params_alloc();
extern void discord_modify_guild_params_free_v(void *p);
extern void discord_modify_guild_params_free(struct discord_modify_guild_params *p);
extern void discord_modify_guild_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_guild_params_from_json(char *json, size_t len, struct discord_modify_guild_params *p);
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
