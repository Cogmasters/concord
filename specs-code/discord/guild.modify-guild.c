/* This file is generated from specs/discord/guild.modify-guild.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_modify_guild_params_from_json(char *json, size_t len, struct discord_modify_guild_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.modify-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
                "(name):?s,"
  /* specs/discord/guild.modify-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
                "(region):?s,"
  /* specs/discord/guild.modify-guild.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
                "(verification_level):d,"
  /* specs/discord/guild.modify-guild.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
                "(default_message_notifications):d,"
  /* specs/discord/guild.modify-guild.json:19:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
                "(explicit_content_filter):d,"
  /* specs/discord/guild.modify-guild.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
                "(afk_channel_id):F,"
  /* specs/discord/guild.modify-guild.json:23:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
                "(afk_timeout):d,"
  /* specs/discord/guild.modify-guild.json:25:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
                "(icon):?s,"
  /* specs/discord/guild.modify-guild.json:27:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}'
  */
                "(owner_id):F,"
  /* specs/discord/guild.modify-guild.json:29:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}'
  */
                "(splash):?s,"
  /* specs/discord/guild.modify-guild.json:31:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}'
  */
                "(discovery_splash):?s,"
  /* specs/discord/guild.modify-guild.json:33:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}'
  */
                "(banner):?s,"
  /* specs/discord/guild.modify-guild.json:35:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
                "(system_channel_id):F,"
  /* specs/discord/guild.modify-guild.json:37:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, 
          "option":true, "inject_if_not":0, "comment":"system channel flags"}'
  */
                "(system_channel_flags):d,"
  /* specs/discord/guild.modify-guild.json:39:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}'
  */
                "(rules_channel_id):F,"
  /* specs/discord/guild.modify-guild.json:41:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}'
  */
                "(public_updates_channel_id):F,"
  /* specs/discord/guild.modify-guild.json:43:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}'
  */
                "(preferred_locale):?s,"
  /* specs/discord/guild.modify-guild.json:45:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, 
          "todo":true", "comment":"array of guild feature strings"}'
  */
  /* specs/discord/guild.modify-guild.json:47:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the description for the guild, if the guild is discoverable"}'
  */
                "(description):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.modify-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
                &p->name,
  /* specs/discord/guild.modify-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
                &p->region,
  /* specs/discord/guild.modify-guild.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
                &p->verification_level,
  /* specs/discord/guild.modify-guild.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
                &p->default_message_notifications,
  /* specs/discord/guild.modify-guild.json:19:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
                &p->explicit_content_filter,
  /* specs/discord/guild.modify-guild.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
                orka_strtoull, &p->afk_channel_id,
  /* specs/discord/guild.modify-guild.json:23:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
                &p->afk_timeout,
  /* specs/discord/guild.modify-guild.json:25:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
                &p->icon,
  /* specs/discord/guild.modify-guild.json:27:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}'
  */
                orka_strtoull, &p->owner_id,
  /* specs/discord/guild.modify-guild.json:29:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}'
  */
                &p->splash,
  /* specs/discord/guild.modify-guild.json:31:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}'
  */
                &p->discovery_splash,
  /* specs/discord/guild.modify-guild.json:33:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}'
  */
                &p->banner,
  /* specs/discord/guild.modify-guild.json:35:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
                orka_strtoull, &p->system_channel_id,
  /* specs/discord/guild.modify-guild.json:37:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, 
          "option":true, "inject_if_not":0, "comment":"system channel flags"}'
  */
                &p->system_channel_flags,
  /* specs/discord/guild.modify-guild.json:39:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}'
  */
                orka_strtoull, &p->rules_channel_id,
  /* specs/discord/guild.modify-guild.json:41:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}'
  */
                orka_strtoull, &p->public_updates_channel_id,
  /* specs/discord/guild.modify-guild.json:43:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}'
  */
                &p->preferred_locale,
  /* specs/discord/guild.modify-guild.json:45:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, 
          "todo":true", "comment":"array of guild feature strings"}'
  */
  /* specs/discord/guild.modify-guild.json:47:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the description for the guild, if the guild is discoverable"}'
  */
                &p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_modify_guild_params_use_default_inject_settings(struct discord_modify_guild_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.modify-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/guild.modify-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
  if (p->region != NULL)
    p->__M.arg_switches[1] = p->region;

  /* specs/discord/guild.modify-guild.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
  if (p->verification_level != 0)
    p->__M.arg_switches[2] = &p->verification_level;

  /* specs/discord/guild.modify-guild.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
  if (p->default_message_notifications != 0)
    p->__M.arg_switches[3] = &p->default_message_notifications;

  /* specs/discord/guild.modify-guild.json:19:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
  if (p->explicit_content_filter != 0)
    p->__M.arg_switches[4] = &p->explicit_content_filter;

  /* specs/discord/guild.modify-guild.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
  if (p->afk_channel_id != 0)
    p->__M.arg_switches[5] = &p->afk_channel_id;

  /* specs/discord/guild.modify-guild.json:23:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
  if (p->afk_timeout != 0)
    p->__M.arg_switches[6] = &p->afk_timeout;

  /* specs/discord/guild.modify-guild.json:25:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
  if (p->icon != NULL)
    p->__M.arg_switches[7] = p->icon;

  /* specs/discord/guild.modify-guild.json:27:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}'
  */
  if (p->owner_id != 0)
    p->__M.arg_switches[8] = &p->owner_id;

  /* specs/discord/guild.modify-guild.json:29:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}'
  */
  if (p->splash != NULL)
    p->__M.arg_switches[9] = p->splash;

  /* specs/discord/guild.modify-guild.json:31:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}'
  */
  if (p->discovery_splash != NULL)
    p->__M.arg_switches[10] = p->discovery_splash;

  /* specs/discord/guild.modify-guild.json:33:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}'
  */
  if (p->banner != NULL)
    p->__M.arg_switches[11] = p->banner;

  /* specs/discord/guild.modify-guild.json:35:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
  if (p->system_channel_id != 0)
    p->__M.arg_switches[12] = &p->system_channel_id;

  /* specs/discord/guild.modify-guild.json:37:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, 
          "option":true, "inject_if_not":0, "comment":"system channel flags"}'
  */
  if (p->system_channel_flags != 0)
    p->__M.arg_switches[13] = &p->system_channel_flags;

  /* specs/discord/guild.modify-guild.json:39:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}'
  */
  if (p->rules_channel_id != 0)
    p->__M.arg_switches[14] = &p->rules_channel_id;

  /* specs/discord/guild.modify-guild.json:41:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}'
  */
  if (p->public_updates_channel_id != 0)
    p->__M.arg_switches[15] = &p->public_updates_channel_id;

  /* specs/discord/guild.modify-guild.json:43:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}'
  */
  p->__M.arg_switches[16] = p->preferred_locale;

  /* specs/discord/guild.modify-guild.json:45:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, 
          "todo":true", "comment":"array of guild feature strings"}'
  */

  /* specs/discord/guild.modify-guild.json:47:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the description for the guild, if the guild is discoverable"}'
  */
  p->__M.arg_switches[18] = p->description;

}

size_t discord_modify_guild_params_to_json(char *json, size_t len, struct discord_modify_guild_params *p)
{
  size_t r;
  discord_modify_guild_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.modify-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
                "(name):s,"
  /* specs/discord/guild.modify-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
                "(region):s,"
  /* specs/discord/guild.modify-guild.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
                "(verification_level):d,"
  /* specs/discord/guild.modify-guild.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
                "(default_message_notifications):d,"
  /* specs/discord/guild.modify-guild.json:19:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
                "(explicit_content_filter):d,"
  /* specs/discord/guild.modify-guild.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
                "(afk_channel_id):|F|,"
  /* specs/discord/guild.modify-guild.json:23:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
                "(afk_timeout):d,"
  /* specs/discord/guild.modify-guild.json:25:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
                "(icon):s,"
  /* specs/discord/guild.modify-guild.json:27:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}'
  */
                "(owner_id):|F|,"
  /* specs/discord/guild.modify-guild.json:29:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}'
  */
                "(splash):s,"
  /* specs/discord/guild.modify-guild.json:31:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}'
  */
                "(discovery_splash):s,"
  /* specs/discord/guild.modify-guild.json:33:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}'
  */
                "(banner):s,"
  /* specs/discord/guild.modify-guild.json:35:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
                "(system_channel_id):|F|,"
  /* specs/discord/guild.modify-guild.json:37:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, 
          "option":true, "inject_if_not":0, "comment":"system channel flags"}'
  */
                "(system_channel_flags):d,"
  /* specs/discord/guild.modify-guild.json:39:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}'
  */
                "(rules_channel_id):|F|,"
  /* specs/discord/guild.modify-guild.json:41:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}'
  */
                "(public_updates_channel_id):|F|,"
  /* specs/discord/guild.modify-guild.json:43:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}'
  */
                "(preferred_locale):s,"
  /* specs/discord/guild.modify-guild.json:45:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, 
          "todo":true", "comment":"array of guild feature strings"}'
  */
  /* specs/discord/guild.modify-guild.json:47:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the description for the guild, if the guild is discoverable"}'
  */
                "(description):s,"
                "@arg_switches:b",
  /* specs/discord/guild.modify-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
                p->name,
  /* specs/discord/guild.modify-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
                p->region,
  /* specs/discord/guild.modify-guild.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
                &p->verification_level,
  /* specs/discord/guild.modify-guild.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
                &p->default_message_notifications,
  /* specs/discord/guild.modify-guild.json:19:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
                &p->explicit_content_filter,
  /* specs/discord/guild.modify-guild.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
                orka_ulltostr, &p->afk_channel_id,
  /* specs/discord/guild.modify-guild.json:23:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
                &p->afk_timeout,
  /* specs/discord/guild.modify-guild.json:25:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
                p->icon,
  /* specs/discord/guild.modify-guild.json:27:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}'
  */
                orka_ulltostr, &p->owner_id,
  /* specs/discord/guild.modify-guild.json:29:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}'
  */
                p->splash,
  /* specs/discord/guild.modify-guild.json:31:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}'
  */
                p->discovery_splash,
  /* specs/discord/guild.modify-guild.json:33:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}'
  */
                p->banner,
  /* specs/discord/guild.modify-guild.json:35:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
                orka_ulltostr, &p->system_channel_id,
  /* specs/discord/guild.modify-guild.json:37:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, 
          "option":true, "inject_if_not":0, "comment":"system channel flags"}'
  */
                &p->system_channel_flags,
  /* specs/discord/guild.modify-guild.json:39:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}'
  */
                orka_ulltostr, &p->rules_channel_id,
  /* specs/discord/guild.modify-guild.json:41:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}'
  */
                orka_ulltostr, &p->public_updates_channel_id,
  /* specs/discord/guild.modify-guild.json:43:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}'
  */
                p->preferred_locale,
  /* specs/discord/guild.modify-guild.json:45:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, 
          "todo":true", "comment":"array of guild feature strings"}'
  */
  /* specs/discord/guild.modify-guild.json:47:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the description for the guild, if the guild is discoverable"}'
  */
                p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_guild_params_cleanup_v(void *p) {
  discord_modify_guild_params_cleanup((struct discord_modify_guild_params *)p);
}

void discord_modify_guild_params_init_v(void *p) {
  discord_modify_guild_params_init((struct discord_modify_guild_params *)p);
}

void discord_modify_guild_params_free_v(void *p) {
 discord_modify_guild_params_free((struct discord_modify_guild_params *)p);
};

void discord_modify_guild_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_guild_params_from_json(json, len, (struct discord_modify_guild_params*)p);
}

size_t discord_modify_guild_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_guild_params_to_json(json, len, (struct discord_modify_guild_params*)p);
}

void discord_modify_guild_params_list_free_v(void **p) {
  discord_modify_guild_params_list_free((struct discord_modify_guild_params**)p);
}

void discord_modify_guild_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_guild_params_list_from_json(str, len, (struct discord_modify_guild_params ***)p);
}

size_t discord_modify_guild_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_guild_params_list_to_json(str, len, (struct discord_modify_guild_params **)p);
}


void discord_modify_guild_params_cleanup(struct discord_modify_guild_params *d) {
  /* specs/discord/guild.modify-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
  if (d->name)
    free(d->name);
  /* specs/discord/guild.modify-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
  if (d->region)
    free(d->region);
  /* specs/discord/guild.modify-guild.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
  //p->verification_level is a scalar
  /* specs/discord/guild.modify-guild.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
  //p->default_message_notifications is a scalar
  /* specs/discord/guild.modify-guild.json:19:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
  //p->explicit_content_filter is a scalar
  /* specs/discord/guild.modify-guild.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
  //p->afk_channel_id is a scalar
  /* specs/discord/guild.modify-guild.json:23:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
  //p->afk_timeout is a scalar
  /* specs/discord/guild.modify-guild.json:25:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
  if (d->icon)
    free(d->icon);
  /* specs/discord/guild.modify-guild.json:27:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}'
  */
  //p->owner_id is a scalar
  /* specs/discord/guild.modify-guild.json:29:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}'
  */
  if (d->splash)
    free(d->splash);
  /* specs/discord/guild.modify-guild.json:31:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}'
  */
  if (d->discovery_splash)
    free(d->discovery_splash);
  /* specs/discord/guild.modify-guild.json:33:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}'
  */
  if (d->banner)
    free(d->banner);
  /* specs/discord/guild.modify-guild.json:35:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
  //p->system_channel_id is a scalar
  /* specs/discord/guild.modify-guild.json:37:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, 
          "option":true, "inject_if_not":0, "comment":"system channel flags"}'
  */
  //p->system_channel_flags is a scalar
  /* specs/discord/guild.modify-guild.json:39:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}'
  */
  //p->rules_channel_id is a scalar
  /* specs/discord/guild.modify-guild.json:41:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}'
  */
  //p->public_updates_channel_id is a scalar
  /* specs/discord/guild.modify-guild.json:43:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}'
  */
  if (d->preferred_locale)
    free(d->preferred_locale);
  /* specs/discord/guild.modify-guild.json:45:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, 
          "todo":true", "comment":"array of guild feature strings"}'
  */
  //@todo p->(null)
  /* specs/discord/guild.modify-guild.json:47:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the description for the guild, if the guild is discoverable"}'
  */
  if (d->description)
    free(d->description);
}

void discord_modify_guild_params_init(struct discord_modify_guild_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_params));
  /* specs/discord/guild.modify-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "comment":"name of the guild (2-100) characters"}'
  */

  /* specs/discord/guild.modify-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */

  /* specs/discord/guild.modify-guild.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */

  /* specs/discord/guild.modify-guild.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */

  /* specs/discord/guild.modify-guild.json:19:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */

  /* specs/discord/guild.modify-guild.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */

  /* specs/discord/guild.modify-guild.json:23:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */

  /* specs/discord/guild.modify-guild.json:25:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */

  /* specs/discord/guild.modify-guild.json:27:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}'
  */

  /* specs/discord/guild.modify-guild.json:29:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}'
  */

  /* specs/discord/guild.modify-guild.json:31:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}'
  */

  /* specs/discord/guild.modify-guild.json:33:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}'
  */

  /* specs/discord/guild.modify-guild.json:35:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */

  /* specs/discord/guild.modify-guild.json:37:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, 
          "option":true, "inject_if_not":0, "comment":"system channel flags"}'
  */

  /* specs/discord/guild.modify-guild.json:39:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}'
  */

  /* specs/discord/guild.modify-guild.json:41:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}'
  */

  /* specs/discord/guild.modify-guild.json:43:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}'
  */

  /* specs/discord/guild.modify-guild.json:45:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, 
          "todo":true", "comment":"array of guild feature strings"}'
  */

  /* specs/discord/guild.modify-guild.json:47:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the description for the guild, if the guild is discoverable"}'
  */

}
struct discord_modify_guild_params* discord_modify_guild_params_alloc() {
  struct discord_modify_guild_params *p= (struct discord_modify_guild_params*)malloc(sizeof(struct discord_modify_guild_params));
  discord_modify_guild_params_init(p);
  return p;
}

void discord_modify_guild_params_free(struct discord_modify_guild_params *p) {
  discord_modify_guild_params_cleanup(p);
  free(p);
}

void discord_modify_guild_params_list_free(struct discord_modify_guild_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_guild_params_cleanup);
}

void discord_modify_guild_params_list_from_json(char *str, size_t len, struct discord_modify_guild_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_params);
  d.init_elem = discord_modify_guild_params_init_v;
  d.elem_from_buf = discord_modify_guild_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_modify_guild_params_list_to_json(char *str, size_t len, struct discord_modify_guild_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_guild_params_to_json_v);
}

