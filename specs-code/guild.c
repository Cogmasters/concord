/* This file is generated from specs/guild.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#guild-object-guild-structure
*/

void discord_guild_from_json(char *json, size_t len, struct discord_guild *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.json:11:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
                "(id):F,"
  /* specs/guild.json:12:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name"}'
  */
                "(name):s,"
  /* specs/guild.json:13:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}'
  */
                "(icon):?s,"
  /* specs/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}'
  */
                "(icon_hash):?s,"
  /* specs/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}'
  */
                "(splash):?s,"
  /* specs/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}'
  */
                "(discovery_splash):?s,"
  /* specs/guild.json:17:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}'
  */
                "(owner):b,"
  /* specs/guild.json:18:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}'
  */
                "(owner_id):F,"
  /* specs/guild.json:19:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}'
  */
                "(permissions):d,"
  /* specs/guild.json:20:68
     '{"type":{"base":"char", "dec":"[MAX_REGION_LEN]"}, "name":"region"}'
  */
                "(region):s,"
  /* specs/guild.json:21:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}'
  */
                "(afk_channel_id):F,"
  /* specs/guild.json:22:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}'
  */
                "(afk_timeout):d,"
  /* specs/guild.json:23:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}'
  */
                "(widget_enabled):b,"
  /* specs/guild.json:24:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}'
  */
                "(widget_channel_id):F,"
  /* specs/guild.json:25:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}'
  */
                "(verification_level):d,"
  /* specs/guild.json:27:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}'
  */
                "(default_message_notifications):d,"
  /* specs/guild.json:29:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}'
  */
                "(explicit_content_filter):d,"
  /* specs/guild.json:30:76
     '{"type":{"base":"struct discord_guild_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}'
  */
  /* specs/guild.json:32:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}'
  */
                "(emojis):F,"
  /* specs/guild.json:33:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true", 
              "comment":"array of guild feature strings"}'
  */
  /* specs/guild.json:35:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}'
  */
                "(mfa_level):d,"
  /* specs/guild.json:36:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}'
  */
                "(application_id):F,"
  /* specs/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}'
  */
                "(system_channel_id):F,"
  /* specs/guild.json:38:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}'
  */
                "(system_channel_flags):d,"
  /* specs/guild.json:39:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}'
  */
                "(rules_channel_id):F,"
  /* specs/guild.json:40:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}'
  */
                "(joined_at):F,"
  /* specs/guild.json:41:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}'
  */
                "(large):b,"
  /* specs/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}'
  */
                "(unavailable):b,"
  /* specs/guild.json:43:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}'
  */
                "(member_count):d,"
  /* specs/guild.json:44:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true", 
         "comment":"array of partial voice state objects"}'
  */
  /* specs/guild.json:46:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}'
  */
                "(members):F,"
  /* specs/guild.json:47:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}'
  */
                "(channels):F,"
  /* specs/guild.json:49:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}'
  */
  /* specs/guild.json:51:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}'
  */
                "(max_presences):d,"
  /* specs/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}'
  */
                "(max_members):d,"
  /* specs/guild.json:53:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}'
  */
                "(vanity_url):?s,"
  /* specs/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}'
  */
                "(description):?s,"
  /* specs/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}'
  */
                "(banner):?s,"
  /* specs/guild.json:56:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}'
  */
                "(premium_tier):d,"
  /* specs/guild.json:57:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}'
  */
                "(premium_subscription_count):d,"
  /* specs/guild.json:58:68
     '{"type":{"base":"char", "dec":"[MAX_LOCALE_LEN]"}, "name":"preferred_locale"}'
  */
                "(preferred_locale):s,"
  /* specs/guild.json:60:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}'
  */
                "(public_updates_channel_id):F,"
  /* specs/guild.json:61:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}'
  */
                "(max_video_channel_users):d,"
  /* specs/guild.json:62:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}'
  */
                "(approximate_member_count):d,"
  /* specs/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}'
  */
                "(approximate_presence_count):d,"
  /* specs/guild.json:64:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}'
  */
                "(welcome_screen):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.json:11:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
                orka_strtoull, &p->id,
  /* specs/guild.json:12:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name"}'
  */
                p->name,
  /* specs/guild.json:13:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}'
  */
                &p->icon,
  /* specs/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}'
  */
                &p->icon_hash,
  /* specs/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}'
  */
                &p->splash,
  /* specs/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}'
  */
                &p->discovery_splash,
  /* specs/guild.json:17:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}'
  */
                &p->owner,
  /* specs/guild.json:18:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}'
  */
                orka_strtoull, &p->owner_id,
  /* specs/guild.json:19:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}'
  */
                &p->permissions,
  /* specs/guild.json:20:68
     '{"type":{"base":"char", "dec":"[MAX_REGION_LEN]"}, "name":"region"}'
  */
                p->region,
  /* specs/guild.json:21:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}'
  */
                orka_strtoull, &p->afk_channel_id,
  /* specs/guild.json:22:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}'
  */
                &p->afk_timeout,
  /* specs/guild.json:23:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}'
  */
                &p->widget_enabled,
  /* specs/guild.json:24:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}'
  */
                orka_strtoull, &p->widget_channel_id,
  /* specs/guild.json:25:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}'
  */
                &p->verification_level,
  /* specs/guild.json:27:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}'
  */
                &p->default_message_notifications,
  /* specs/guild.json:29:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}'
  */
                &p->explicit_content_filter,
  /* specs/guild.json:30:76
     '{"type":{"base":"struct discord_guild_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}'
  */
  /* specs/guild.json:32:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}'
  */
                discord_emoji_list_from_json, &p->emojis,
  /* specs/guild.json:33:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true", 
              "comment":"array of guild feature strings"}'
  */
  /* specs/guild.json:35:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}'
  */
                &p->mfa_level,
  /* specs/guild.json:36:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}'
  */
                orka_strtoull, &p->application_id,
  /* specs/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}'
  */
                orka_strtoull, &p->system_channel_id,
  /* specs/guild.json:38:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}'
  */
                &p->system_channel_flags,
  /* specs/guild.json:39:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}'
  */
                orka_strtoull, &p->rules_channel_id,
  /* specs/guild.json:40:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}'
  */
                orka_iso8601_to_unix_ms, &p->joined_at,
  /* specs/guild.json:41:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}'
  */
                &p->large,
  /* specs/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}'
  */
                &p->unavailable,
  /* specs/guild.json:43:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}'
  */
                &p->member_count,
  /* specs/guild.json:44:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true", 
         "comment":"array of partial voice state objects"}'
  */
  /* specs/guild.json:46:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}'
  */
                discord_guild_member_list_from_json, &p->members,
  /* specs/guild.json:47:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}'
  */
                discord_channel_list_from_json, &p->channels,
  /* specs/guild.json:49:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}'
  */
  /* specs/guild.json:51:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}'
  */
                &p->max_presences,
  /* specs/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}'
  */
                &p->max_members,
  /* specs/guild.json:53:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}'
  */
                &p->vanity_url,
  /* specs/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}'
  */
                &p->description,
  /* specs/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}'
  */
                &p->banner,
  /* specs/guild.json:56:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}'
  */
                &p->premium_tier,
  /* specs/guild.json:57:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}'
  */
                &p->premium_subscription_count,
  /* specs/guild.json:58:68
     '{"type":{"base":"char", "dec":"[MAX_LOCALE_LEN]"}, "name":"preferred_locale"}'
  */
                p->preferred_locale,
  /* specs/guild.json:60:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}'
  */
                orka_strtoull, &p->public_updates_channel_id,
  /* specs/guild.json:61:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}'
  */
                &p->max_video_channel_users,
  /* specs/guild.json:62:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}'
  */
                &p->approximate_member_count,
  /* specs/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}'
  */
                &p->approximate_presence_count,
  /* specs/guild.json:64:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}'
  */
                discord_guild_welcome_screen_from_json, p->welcome_screen,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_use_default_inject_settings(struct discord_guild *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.json:11:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/guild.json:12:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name"}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/guild.json:13:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}'
  */
  p->__M.arg_switches[2] = p->icon;

  /* specs/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}'
  */
  p->__M.arg_switches[3] = p->icon_hash;

  /* specs/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}'
  */
  p->__M.arg_switches[4] = p->splash;

  /* specs/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}'
  */
  p->__M.arg_switches[5] = p->discovery_splash;

  /* specs/guild.json:17:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}'
  */
  p->__M.arg_switches[6] = &p->owner;

  /* specs/guild.json:18:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}'
  */
  p->__M.arg_switches[7] = &p->owner_id;

  /* specs/guild.json:19:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}'
  */
  p->__M.arg_switches[8] = &p->permissions;

  /* specs/guild.json:20:68
     '{"type":{"base":"char", "dec":"[MAX_REGION_LEN]"}, "name":"region"}'
  */
  p->__M.arg_switches[9] = p->region;

  /* specs/guild.json:21:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}'
  */
  p->__M.arg_switches[10] = &p->afk_channel_id;

  /* specs/guild.json:22:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}'
  */
  p->__M.arg_switches[11] = &p->afk_timeout;

  /* specs/guild.json:23:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}'
  */
  p->__M.arg_switches[12] = &p->widget_enabled;

  /* specs/guild.json:24:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}'
  */
  p->__M.arg_switches[13] = &p->widget_channel_id;

  /* specs/guild.json:25:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}'
  */
  p->__M.arg_switches[14] = &p->verification_level;

  /* specs/guild.json:27:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}'
  */
  p->__M.arg_switches[15] = &p->default_message_notifications;

  /* specs/guild.json:29:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}'
  */
  p->__M.arg_switches[16] = &p->explicit_content_filter;

  /* specs/guild.json:30:76
     '{"type":{"base":"struct discord_guild_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}'
  */

  /* specs/guild.json:32:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}'
  */
  p->__M.arg_switches[18] = p->emojis;

  /* specs/guild.json:33:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true", 
              "comment":"array of guild feature strings"}'
  */

  /* specs/guild.json:35:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}'
  */
  p->__M.arg_switches[20] = &p->mfa_level;

  /* specs/guild.json:36:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}'
  */
  p->__M.arg_switches[21] = &p->application_id;

  /* specs/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}'
  */
  p->__M.arg_switches[22] = &p->system_channel_id;

  /* specs/guild.json:38:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}'
  */
  p->__M.arg_switches[23] = &p->system_channel_flags;

  /* specs/guild.json:39:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}'
  */
  p->__M.arg_switches[24] = &p->rules_channel_id;

  /* specs/guild.json:40:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}'
  */
  p->__M.arg_switches[25] = &p->joined_at;

  /* specs/guild.json:41:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}'
  */
  p->__M.arg_switches[26] = &p->large;

  /* specs/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}'
  */
  p->__M.arg_switches[27] = &p->unavailable;

  /* specs/guild.json:43:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}'
  */
  p->__M.arg_switches[28] = &p->member_count;

  /* specs/guild.json:44:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true", 
         "comment":"array of partial voice state objects"}'
  */

  /* specs/guild.json:46:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}'
  */
  p->__M.arg_switches[30] = p->members;

  /* specs/guild.json:47:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}'
  */
  p->__M.arg_switches[31] = p->channels;

  /* specs/guild.json:49:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}'
  */

  /* specs/guild.json:51:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}'
  */
  p->__M.arg_switches[33] = &p->max_presences;

  /* specs/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}'
  */
  p->__M.arg_switches[34] = &p->max_members;

  /* specs/guild.json:53:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}'
  */
  p->__M.arg_switches[35] = p->vanity_url;

  /* specs/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}'
  */
  p->__M.arg_switches[36] = p->description;

  /* specs/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}'
  */
  p->__M.arg_switches[37] = p->banner;

  /* specs/guild.json:56:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}'
  */
  p->__M.arg_switches[38] = &p->premium_tier;

  /* specs/guild.json:57:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}'
  */
  p->__M.arg_switches[39] = &p->premium_subscription_count;

  /* specs/guild.json:58:68
     '{"type":{"base":"char", "dec":"[MAX_LOCALE_LEN]"}, "name":"preferred_locale"}'
  */
  p->__M.arg_switches[40] = p->preferred_locale;

  /* specs/guild.json:60:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}'
  */
  p->__M.arg_switches[41] = &p->public_updates_channel_id;

  /* specs/guild.json:61:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}'
  */
  p->__M.arg_switches[42] = &p->max_video_channel_users;

  /* specs/guild.json:62:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}'
  */
  p->__M.arg_switches[43] = &p->approximate_member_count;

  /* specs/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}'
  */
  p->__M.arg_switches[44] = &p->approximate_presence_count;

  /* specs/guild.json:64:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}'
  */
  p->__M.arg_switches[45] = p->welcome_screen;

}

size_t discord_guild_to_json(char *json, size_t len, struct discord_guild *p)
{
  size_t r;
  discord_guild_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.json:11:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
                "(id):|F|,"
  /* specs/guild.json:12:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name"}'
  */
                "(name):s,"
  /* specs/guild.json:13:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}'
  */
                "(icon):s,"
  /* specs/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}'
  */
                "(icon_hash):s,"
  /* specs/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}'
  */
                "(splash):s,"
  /* specs/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}'
  */
                "(discovery_splash):s,"
  /* specs/guild.json:17:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}'
  */
                "(owner):b,"
  /* specs/guild.json:18:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}'
  */
                "(owner_id):|F|,"
  /* specs/guild.json:19:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}'
  */
                "(permissions):d,"
  /* specs/guild.json:20:68
     '{"type":{"base":"char", "dec":"[MAX_REGION_LEN]"}, "name":"region"}'
  */
                "(region):s,"
  /* specs/guild.json:21:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}'
  */
                "(afk_channel_id):|F|,"
  /* specs/guild.json:22:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}'
  */
                "(afk_timeout):d,"
  /* specs/guild.json:23:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}'
  */
                "(widget_enabled):b,"
  /* specs/guild.json:24:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}'
  */
                "(widget_channel_id):|F|,"
  /* specs/guild.json:25:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}'
  */
                "(verification_level):d,"
  /* specs/guild.json:27:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}'
  */
                "(default_message_notifications):d,"
  /* specs/guild.json:29:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}'
  */
                "(explicit_content_filter):d,"
  /* specs/guild.json:30:76
     '{"type":{"base":"struct discord_guild_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}'
  */
  /* specs/guild.json:32:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}'
  */
                "(emojis):F,"
  /* specs/guild.json:33:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true", 
              "comment":"array of guild feature strings"}'
  */
  /* specs/guild.json:35:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}'
  */
                "(mfa_level):d,"
  /* specs/guild.json:36:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}'
  */
                "(application_id):|F|,"
  /* specs/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}'
  */
                "(system_channel_id):|F|,"
  /* specs/guild.json:38:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}'
  */
                "(system_channel_flags):d,"
  /* specs/guild.json:39:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}'
  */
                "(rules_channel_id):|F|,"
  /* specs/guild.json:40:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}'
  */
                "(joined_at):|F|,"
  /* specs/guild.json:41:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}'
  */
                "(large):b,"
  /* specs/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}'
  */
                "(unavailable):b,"
  /* specs/guild.json:43:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}'
  */
                "(member_count):d,"
  /* specs/guild.json:44:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true", 
         "comment":"array of partial voice state objects"}'
  */
  /* specs/guild.json:46:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}'
  */
                "(members):F,"
  /* specs/guild.json:47:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}'
  */
                "(channels):F,"
  /* specs/guild.json:49:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}'
  */
  /* specs/guild.json:51:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}'
  */
                "(max_presences):d,"
  /* specs/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}'
  */
                "(max_members):d,"
  /* specs/guild.json:53:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}'
  */
                "(vanity_url):s,"
  /* specs/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}'
  */
                "(description):s,"
  /* specs/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}'
  */
                "(banner):s,"
  /* specs/guild.json:56:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}'
  */
                "(premium_tier):d,"
  /* specs/guild.json:57:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}'
  */
                "(premium_subscription_count):d,"
  /* specs/guild.json:58:68
     '{"type":{"base":"char", "dec":"[MAX_LOCALE_LEN]"}, "name":"preferred_locale"}'
  */
                "(preferred_locale):s,"
  /* specs/guild.json:60:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}'
  */
                "(public_updates_channel_id):|F|,"
  /* specs/guild.json:61:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}'
  */
                "(max_video_channel_users):d,"
  /* specs/guild.json:62:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}'
  */
                "(approximate_member_count):d,"
  /* specs/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}'
  */
                "(approximate_presence_count):d,"
  /* specs/guild.json:64:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}'
  */
                "(welcome_screen):F,"
                "@arg_switches:b",
  /* specs/guild.json:11:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
                orka_ulltostr, &p->id,
  /* specs/guild.json:12:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name"}'
  */
                p->name,
  /* specs/guild.json:13:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}'
  */
                p->icon,
  /* specs/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}'
  */
                p->icon_hash,
  /* specs/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}'
  */
                p->splash,
  /* specs/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}'
  */
                p->discovery_splash,
  /* specs/guild.json:17:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}'
  */
                &p->owner,
  /* specs/guild.json:18:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}'
  */
                orka_ulltostr, &p->owner_id,
  /* specs/guild.json:19:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}'
  */
                &p->permissions,
  /* specs/guild.json:20:68
     '{"type":{"base":"char", "dec":"[MAX_REGION_LEN]"}, "name":"region"}'
  */
                p->region,
  /* specs/guild.json:21:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}'
  */
                orka_ulltostr, &p->afk_channel_id,
  /* specs/guild.json:22:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}'
  */
                &p->afk_timeout,
  /* specs/guild.json:23:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}'
  */
                &p->widget_enabled,
  /* specs/guild.json:24:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}'
  */
                orka_ulltostr, &p->widget_channel_id,
  /* specs/guild.json:25:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}'
  */
                &p->verification_level,
  /* specs/guild.json:27:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}'
  */
                &p->default_message_notifications,
  /* specs/guild.json:29:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}'
  */
                &p->explicit_content_filter,
  /* specs/guild.json:30:76
     '{"type":{"base":"struct discord_guild_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}'
  */
  /* specs/guild.json:32:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}'
  */
                discord_emoji_list_to_json, p->emojis,
  /* specs/guild.json:33:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true", 
              "comment":"array of guild feature strings"}'
  */
  /* specs/guild.json:35:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}'
  */
                &p->mfa_level,
  /* specs/guild.json:36:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}'
  */
                orka_ulltostr, &p->application_id,
  /* specs/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}'
  */
                orka_ulltostr, &p->system_channel_id,
  /* specs/guild.json:38:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}'
  */
                &p->system_channel_flags,
  /* specs/guild.json:39:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}'
  */
                orka_ulltostr, &p->rules_channel_id,
  /* specs/guild.json:40:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}'
  */
                orka_unix_ms_to_iso8601, &p->joined_at,
  /* specs/guild.json:41:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}'
  */
                &p->large,
  /* specs/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}'
  */
                &p->unavailable,
  /* specs/guild.json:43:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}'
  */
                &p->member_count,
  /* specs/guild.json:44:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true", 
         "comment":"array of partial voice state objects"}'
  */
  /* specs/guild.json:46:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}'
  */
                discord_guild_member_list_to_json, p->members,
  /* specs/guild.json:47:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}'
  */
                discord_channel_list_to_json, p->channels,
  /* specs/guild.json:49:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}'
  */
  /* specs/guild.json:51:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}'
  */
                &p->max_presences,
  /* specs/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}'
  */
                &p->max_members,
  /* specs/guild.json:53:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}'
  */
                p->vanity_url,
  /* specs/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}'
  */
                p->description,
  /* specs/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}'
  */
                p->banner,
  /* specs/guild.json:56:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}'
  */
                &p->premium_tier,
  /* specs/guild.json:57:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}'
  */
                &p->premium_subscription_count,
  /* specs/guild.json:58:68
     '{"type":{"base":"char", "dec":"[MAX_LOCALE_LEN]"}, "name":"preferred_locale"}'
  */
                p->preferred_locale,
  /* specs/guild.json:60:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}'
  */
                orka_ulltostr, &p->public_updates_channel_id,
  /* specs/guild.json:61:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}'
  */
                &p->max_video_channel_users,
  /* specs/guild.json:62:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}'
  */
                &p->approximate_member_count,
  /* specs/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}'
  */
                &p->approximate_presence_count,
  /* specs/guild.json:64:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}'
  */
                discord_guild_welcome_screen_to_json, p->welcome_screen,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_cleanup_v(void *p) {
  discord_guild_cleanup((struct discord_guild *)p);
}

void discord_guild_init_v(void *p) {
  discord_guild_init((struct discord_guild *)p);
}

void discord_guild_free_v(void *p) {
 discord_guild_free((struct discord_guild *)p);
};

void discord_guild_from_json_v(char *json, size_t len, void *p) {
 discord_guild_from_json(json, len, (struct discord_guild*)p);
}

size_t discord_guild_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_to_json(json, len, (struct discord_guild*)p);
}

void discord_guild_list_free_v(void **p) {
  discord_guild_list_free((struct discord_guild**)p);
}

void discord_guild_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_list_from_json(str, len, (struct discord_guild ***)p);
}

size_t discord_guild_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_list_to_json(str, len, (struct discord_guild **)p);
}


void discord_guild_cleanup(struct discord_guild *d) {
  /* specs/guild.json:11:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  //p->id is a scalar
  /* specs/guild.json:12:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name"}'
  */
  //p->name is a scalar
  /* specs/guild.json:13:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}'
  */
  if (d->icon)
    free(d->icon);
  /* specs/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}'
  */
  if (d->icon_hash)
    free(d->icon_hash);
  /* specs/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}'
  */
  if (d->splash)
    free(d->splash);
  /* specs/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}'
  */
  if (d->discovery_splash)
    free(d->discovery_splash);
  /* specs/guild.json:17:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}'
  */
  //p->owner is a scalar
  /* specs/guild.json:18:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}'
  */
  //p->owner_id is a scalar
  /* specs/guild.json:19:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}'
  */
  //p->permissions is a scalar
  /* specs/guild.json:20:68
     '{"type":{"base":"char", "dec":"[MAX_REGION_LEN]"}, "name":"region"}'
  */
  //p->region is a scalar
  /* specs/guild.json:21:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}'
  */
  //p->afk_channel_id is a scalar
  /* specs/guild.json:22:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}'
  */
  //p->afk_timeout is a scalar
  /* specs/guild.json:23:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}'
  */
  //p->widget_enabled is a scalar
  /* specs/guild.json:24:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}'
  */
  //p->widget_channel_id is a scalar
  /* specs/guild.json:25:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}'
  */
  //p->verification_level is a scalar
  /* specs/guild.json:27:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}'
  */
  //p->default_message_notifications is a scalar
  /* specs/guild.json:29:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}'
  */
  //p->explicit_content_filter is a scalar
  /* specs/guild.json:30:76
     '{"type":{"base":"struct discord_guild_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}'
  */
  //@todo p->(null)
  /* specs/guild.json:32:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}'
  */
  if (d->emojis)
    discord_emoji_list_free(d->emojis);
  /* specs/guild.json:33:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true", 
              "comment":"array of guild feature strings"}'
  */
  //@todo p->(null)
  /* specs/guild.json:35:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}'
  */
  //p->mfa_level is a scalar
  /* specs/guild.json:36:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}'
  */
  //p->application_id is a scalar
  /* specs/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}'
  */
  //p->system_channel_id is a scalar
  /* specs/guild.json:38:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}'
  */
  //p->system_channel_flags is a scalar
  /* specs/guild.json:39:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}'
  */
  //p->rules_channel_id is a scalar
  /* specs/guild.json:40:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}'
  */
  //p->joined_at is a scalar
  /* specs/guild.json:41:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}'
  */
  //p->large is a scalar
  /* specs/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}'
  */
  //p->unavailable is a scalar
  /* specs/guild.json:43:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}'
  */
  //p->member_count is a scalar
  /* specs/guild.json:44:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true", 
         "comment":"array of partial voice state objects"}'
  */
  //@todo p->(null)
  /* specs/guild.json:46:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}'
  */
  if (d->members)
    discord_guild_member_list_free(d->members);
  /* specs/guild.json:47:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}'
  */
  if (d->channels)
    discord_channel_list_free(d->channels);
  /* specs/guild.json:49:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}'
  */
  //@todo p->(null)
  /* specs/guild.json:51:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}'
  */
  //p->max_presences is a scalar
  /* specs/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}'
  */
  //p->max_members is a scalar
  /* specs/guild.json:53:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}'
  */
  if (d->vanity_url)
    free(d->vanity_url);
  /* specs/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}'
  */
  if (d->description)
    free(d->description);
  /* specs/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}'
  */
  if (d->banner)
    free(d->banner);
  /* specs/guild.json:56:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}'
  */
  //p->premium_tier is a scalar
  /* specs/guild.json:57:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}'
  */
  //p->premium_subscription_count is a scalar
  /* specs/guild.json:58:68
     '{"type":{"base":"char", "dec":"[MAX_LOCALE_LEN]"}, "name":"preferred_locale"}'
  */
  //p->preferred_locale is a scalar
  /* specs/guild.json:60:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}'
  */
  //p->public_updates_channel_id is a scalar
  /* specs/guild.json:61:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}'
  */
  //p->max_video_channel_users is a scalar
  /* specs/guild.json:62:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}'
  */
  //p->approximate_member_count is a scalar
  /* specs/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}'
  */
  //p->approximate_presence_count is a scalar
  /* specs/guild.json:64:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}'
  */
  if (d->welcome_screen)
    discord_guild_welcome_screen_free(d->welcome_screen);
}

void discord_guild_init(struct discord_guild *p) {
  memset(p, 0, sizeof(struct discord_guild));
  /* specs/guild.json:11:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */

  /* specs/guild.json:12:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name"}'
  */

  /* specs/guild.json:13:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}'
  */

  /* specs/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}'
  */

  /* specs/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}'
  */

  /* specs/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}'
  */

  /* specs/guild.json:17:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}'
  */

  /* specs/guild.json:18:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}'
  */

  /* specs/guild.json:19:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}'
  */

  /* specs/guild.json:20:68
     '{"type":{"base":"char", "dec":"[MAX_REGION_LEN]"}, "name":"region"}'
  */

  /* specs/guild.json:21:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}'
  */

  /* specs/guild.json:22:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}'
  */

  /* specs/guild.json:23:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}'
  */

  /* specs/guild.json:24:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}'
  */

  /* specs/guild.json:25:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}'
  */

  /* specs/guild.json:27:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}'
  */

  /* specs/guild.json:29:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}'
  */

  /* specs/guild.json:30:76
     '{"type":{"base":"struct discord_guild_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}'
  */

  /* specs/guild.json:32:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}'
  */

  /* specs/guild.json:33:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true", 
              "comment":"array of guild feature strings"}'
  */

  /* specs/guild.json:35:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}'
  */

  /* specs/guild.json:36:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}'
  */

  /* specs/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}'
  */

  /* specs/guild.json:38:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}'
  */

  /* specs/guild.json:39:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}'
  */

  /* specs/guild.json:40:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}'
  */

  /* specs/guild.json:41:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}'
  */

  /* specs/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}'
  */

  /* specs/guild.json:43:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}'
  */

  /* specs/guild.json:44:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true", 
         "comment":"array of partial voice state objects"}'
  */

  /* specs/guild.json:46:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}'
  */

  /* specs/guild.json:47:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}'
  */

  /* specs/guild.json:49:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}'
  */

  /* specs/guild.json:51:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}'
  */

  /* specs/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}'
  */

  /* specs/guild.json:53:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}'
  */

  /* specs/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}'
  */

  /* specs/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}'
  */

  /* specs/guild.json:56:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}'
  */

  /* specs/guild.json:57:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}'
  */

  /* specs/guild.json:58:68
     '{"type":{"base":"char", "dec":"[MAX_LOCALE_LEN]"}, "name":"preferred_locale"}'
  */

  /* specs/guild.json:60:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}'
  */

  /* specs/guild.json:61:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}'
  */

  /* specs/guild.json:62:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}'
  */

  /* specs/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}'
  */

  /* specs/guild.json:64:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}'
  */
  p->welcome_screen = discord_guild_welcome_screen_alloc();

}
struct discord_guild* discord_guild_alloc() {
  struct discord_guild *p= (struct discord_guild*)malloc(sizeof(struct discord_guild));
  discord_guild_init(p);
  return p;
}

void discord_guild_free(struct discord_guild *p) {
  discord_guild_cleanup(p);
  free(p);
}

void discord_guild_list_free(struct discord_guild **p) {
  ntl_free((void**)p, (vfvp)discord_guild_cleanup);
}

void discord_guild_list_from_json(char *str, size_t len, struct discord_guild ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild);
  d.init_elem = discord_guild_init_v;
  d.elem_from_buf = discord_guild_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_list_to_json(char *str, size_t len, struct discord_guild **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_to_json_v);
}

