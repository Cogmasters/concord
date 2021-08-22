/* This file is generated from specs/discord/guild.json, Please don't edit it. */
/**
 * @file specs-code/discord/guild.c
 * @see https://discord.com/developers/docs/resources/guild
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_guild_from_json(char *json, size_t len, struct discord_guild **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_guild *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.json:12:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                "(id):F,"
  /* specs/discord/guild.json:13:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name"}' */
                "(name):s,"
  /* specs/discord/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}' */
                "(icon):?s,"
  /* specs/discord/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}' */
                "(icon_hash):?s,"
  /* specs/discord/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}' */
                "(splash):?s,"
  /* specs/discord/guild.json:17:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}' */
                "(discovery_splash):?s,"
  /* specs/discord/guild.json:18:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}' */
                "(owner):b,"
  /* specs/discord/guild.json:19:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}' */
                "(owner_id):F,"
  /* specs/discord/guild.json:20:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}' */
                "(permissions):d,"
  /* specs/discord/guild.json:21:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "name":"region"}' */
                "(region):s,"
  /* specs/discord/guild.json:22:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}' */
                "(afk_channel_id):F,"
  /* specs/discord/guild.json:23:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}' */
                "(afk_timeout):d,"
  /* specs/discord/guild.json:24:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}' */
                "(widget_enabled):b,"
  /* specs/discord/guild.json:25:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}' */
                "(widget_channel_id):F,"
  /* specs/discord/guild.json:26:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}' */
                "(verification_level):d,"
  /* specs/discord/guild.json:28:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}' */
                "(default_message_notifications):d,"
  /* specs/discord/guild.json:30:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}' */
                "(explicit_content_filter):d,"
  /* specs/discord/guild.json:31:82
     '{"type":{"base":"struct discord_permissions_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}' */
  /* specs/discord/guild.json:33:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}' */
                "(emojis):F,"
  /* specs/discord/guild.json:34:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true, 
              "comment":"array of guild feature strings"}' */
  /* specs/discord/guild.json:36:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}' */
                "(mfa_level):d,"
  /* specs/discord/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}' */
                "(application_id):F,"
  /* specs/discord/guild.json:38:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}' */
                "(system_channel_id):F,"
  /* specs/discord/guild.json:39:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}' */
                "(system_channel_flags):d,"
  /* specs/discord/guild.json:40:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}' */
                "(rules_channel_id):F,"
  /* specs/discord/guild.json:41:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}' */
                "(joined_at):F,"
  /* specs/discord/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}' */
                "(large):b,"
  /* specs/discord/guild.json:43:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}' */
                "(unavailable):b,"
  /* specs/discord/guild.json:44:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}' */
                "(member_count):d,"
  /* specs/discord/guild.json:45:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true, 
         "comment":"array of partial voice state objects"}' */
  /* specs/discord/guild.json:47:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}' */
                "(members):F,"
  /* specs/discord/guild.json:48:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}' */
                "(channels):F,"
  /* specs/discord/guild.json:50:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}' */
  /* specs/discord/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}' */
                "(max_presences):d,"
  /* specs/discord/guild.json:53:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}' */
                "(max_members):d,"
  /* specs/discord/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}' */
                "(vanity_url):?s,"
  /* specs/discord/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}' */
                "(description):?s,"
  /* specs/discord/guild.json:56:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}' */
                "(banner):?s,"
  /* specs/discord/guild.json:57:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}' */
                "(premium_tier):d,"
  /* specs/discord/guild.json:58:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}' */
                "(premium_subscription_count):d,"
  /* specs/discord/guild.json:59:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "name":"preferred_locale"}' */
                "(preferred_locale):s,"
  /* specs/discord/guild.json:61:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}' */
                "(public_updates_channel_id):F,"
  /* specs/discord/guild.json:62:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}' */
                "(max_video_channel_users):d,"
  /* specs/discord/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}' */
                "(approximate_member_count):d,"
  /* specs/discord/guild.json:64:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}' */
                "(approximate_presence_count):d,"
  /* specs/discord/guild.json:65:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}' */
                "(welcome_screen):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.json:12:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                cee_strtoull, &p->id,
  /* specs/discord/guild.json:13:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name"}' */
                p->name,
  /* specs/discord/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}' */
                &p->icon,
  /* specs/discord/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}' */
                &p->icon_hash,
  /* specs/discord/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}' */
                &p->splash,
  /* specs/discord/guild.json:17:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}' */
                &p->discovery_splash,
  /* specs/discord/guild.json:18:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}' */
                &p->owner,
  /* specs/discord/guild.json:19:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}' */
                cee_strtoull, &p->owner_id,
  /* specs/discord/guild.json:20:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}' */
                &p->permissions,
  /* specs/discord/guild.json:21:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "name":"region"}' */
                p->region,
  /* specs/discord/guild.json:22:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}' */
                cee_strtoull, &p->afk_channel_id,
  /* specs/discord/guild.json:23:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}' */
                &p->afk_timeout,
  /* specs/discord/guild.json:24:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}' */
                &p->widget_enabled,
  /* specs/discord/guild.json:25:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}' */
                cee_strtoull, &p->widget_channel_id,
  /* specs/discord/guild.json:26:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}' */
                &p->verification_level,
  /* specs/discord/guild.json:28:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}' */
                &p->default_message_notifications,
  /* specs/discord/guild.json:30:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}' */
                &p->explicit_content_filter,
  /* specs/discord/guild.json:31:82
     '{"type":{"base":"struct discord_permissions_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}' */
  /* specs/discord/guild.json:33:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}' */
                discord_emoji_list_from_json, &p->emojis,
  /* specs/discord/guild.json:34:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true, 
              "comment":"array of guild feature strings"}' */
  /* specs/discord/guild.json:36:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}' */
                &p->mfa_level,
  /* specs/discord/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}' */
                cee_strtoull, &p->application_id,
  /* specs/discord/guild.json:38:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}' */
                cee_strtoull, &p->system_channel_id,
  /* specs/discord/guild.json:39:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}' */
                &p->system_channel_flags,
  /* specs/discord/guild.json:40:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}' */
                cee_strtoull, &p->rules_channel_id,
  /* specs/discord/guild.json:41:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}' */
                cee_iso8601_to_unix_ms, &p->joined_at,
  /* specs/discord/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}' */
                &p->large,
  /* specs/discord/guild.json:43:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}' */
                &p->unavailable,
  /* specs/discord/guild.json:44:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}' */
                &p->member_count,
  /* specs/discord/guild.json:45:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true, 
         "comment":"array of partial voice state objects"}' */
  /* specs/discord/guild.json:47:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}' */
                discord_guild_member_list_from_json, &p->members,
  /* specs/discord/guild.json:48:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}' */
                discord_channel_list_from_json, &p->channels,
  /* specs/discord/guild.json:50:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}' */
  /* specs/discord/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}' */
                &p->max_presences,
  /* specs/discord/guild.json:53:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}' */
                &p->max_members,
  /* specs/discord/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}' */
                &p->vanity_url,
  /* specs/discord/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}' */
                &p->description,
  /* specs/discord/guild.json:56:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}' */
                &p->banner,
  /* specs/discord/guild.json:57:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}' */
                &p->premium_tier,
  /* specs/discord/guild.json:58:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}' */
                &p->premium_subscription_count,
  /* specs/discord/guild.json:59:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "name":"preferred_locale"}' */
                p->preferred_locale,
  /* specs/discord/guild.json:61:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}' */
                cee_strtoull, &p->public_updates_channel_id,
  /* specs/discord/guild.json:62:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}' */
                &p->max_video_channel_users,
  /* specs/discord/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}' */
                &p->approximate_member_count,
  /* specs/discord/guild.json:64:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}' */
                &p->approximate_presence_count,
  /* specs/discord/guild.json:65:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}' */
                discord_guild_welcome_screen_from_json, &p->welcome_screen,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_use_default_inject_settings(struct discord_guild *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.json:12:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.json:13:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name"}' */
  p->__M.arg_switches[1] = p->name;

  /* specs/discord/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}' */
  p->__M.arg_switches[2] = p->icon;

  /* specs/discord/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}' */
  p->__M.arg_switches[3] = p->icon_hash;

  /* specs/discord/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}' */
  p->__M.arg_switches[4] = p->splash;

  /* specs/discord/guild.json:17:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}' */
  p->__M.arg_switches[5] = p->discovery_splash;

  /* specs/discord/guild.json:18:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}' */
  p->__M.arg_switches[6] = &p->owner;

  /* specs/discord/guild.json:19:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}' */
  p->__M.arg_switches[7] = &p->owner_id;

  /* specs/discord/guild.json:20:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}' */
  p->__M.arg_switches[8] = &p->permissions;

  /* specs/discord/guild.json:21:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "name":"region"}' */
  p->__M.arg_switches[9] = p->region;

  /* specs/discord/guild.json:22:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}' */
  p->__M.arg_switches[10] = &p->afk_channel_id;

  /* specs/discord/guild.json:23:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}' */
  p->__M.arg_switches[11] = &p->afk_timeout;

  /* specs/discord/guild.json:24:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}' */
  p->__M.arg_switches[12] = &p->widget_enabled;

  /* specs/discord/guild.json:25:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}' */
  p->__M.arg_switches[13] = &p->widget_channel_id;

  /* specs/discord/guild.json:26:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}' */
  p->__M.arg_switches[14] = &p->verification_level;

  /* specs/discord/guild.json:28:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}' */
  p->__M.arg_switches[15] = &p->default_message_notifications;

  /* specs/discord/guild.json:30:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}' */
  p->__M.arg_switches[16] = &p->explicit_content_filter;

  /* specs/discord/guild.json:31:82
     '{"type":{"base":"struct discord_permissions_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}' */

  /* specs/discord/guild.json:33:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}' */
  p->__M.arg_switches[18] = p->emojis;

  /* specs/discord/guild.json:34:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true, 
              "comment":"array of guild feature strings"}' */

  /* specs/discord/guild.json:36:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}' */
  p->__M.arg_switches[20] = &p->mfa_level;

  /* specs/discord/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}' */
  p->__M.arg_switches[21] = &p->application_id;

  /* specs/discord/guild.json:38:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}' */
  p->__M.arg_switches[22] = &p->system_channel_id;

  /* specs/discord/guild.json:39:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}' */
  p->__M.arg_switches[23] = &p->system_channel_flags;

  /* specs/discord/guild.json:40:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}' */
  p->__M.arg_switches[24] = &p->rules_channel_id;

  /* specs/discord/guild.json:41:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}' */
  p->__M.arg_switches[25] = &p->joined_at;

  /* specs/discord/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}' */
  p->__M.arg_switches[26] = &p->large;

  /* specs/discord/guild.json:43:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}' */
  p->__M.arg_switches[27] = &p->unavailable;

  /* specs/discord/guild.json:44:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}' */
  p->__M.arg_switches[28] = &p->member_count;

  /* specs/discord/guild.json:45:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true, 
         "comment":"array of partial voice state objects"}' */

  /* specs/discord/guild.json:47:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}' */
  p->__M.arg_switches[30] = p->members;

  /* specs/discord/guild.json:48:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}' */
  p->__M.arg_switches[31] = p->channels;

  /* specs/discord/guild.json:50:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}' */

  /* specs/discord/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}' */
  p->__M.arg_switches[33] = &p->max_presences;

  /* specs/discord/guild.json:53:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}' */
  p->__M.arg_switches[34] = &p->max_members;

  /* specs/discord/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}' */
  p->__M.arg_switches[35] = p->vanity_url;

  /* specs/discord/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}' */
  p->__M.arg_switches[36] = p->description;

  /* specs/discord/guild.json:56:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}' */
  p->__M.arg_switches[37] = p->banner;

  /* specs/discord/guild.json:57:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}' */
  p->__M.arg_switches[38] = &p->premium_tier;

  /* specs/discord/guild.json:58:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}' */
  p->__M.arg_switches[39] = &p->premium_subscription_count;

  /* specs/discord/guild.json:59:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "name":"preferred_locale"}' */
  p->__M.arg_switches[40] = p->preferred_locale;

  /* specs/discord/guild.json:61:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}' */
  p->__M.arg_switches[41] = &p->public_updates_channel_id;

  /* specs/discord/guild.json:62:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}' */
  p->__M.arg_switches[42] = &p->max_video_channel_users;

  /* specs/discord/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}' */
  p->__M.arg_switches[43] = &p->approximate_member_count;

  /* specs/discord/guild.json:64:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}' */
  p->__M.arg_switches[44] = &p->approximate_presence_count;

  /* specs/discord/guild.json:65:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}' */
  p->__M.arg_switches[45] = p->welcome_screen;

}

size_t discord_guild_to_json(char *json, size_t len, struct discord_guild *p)
{
  size_t r;
  discord_guild_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.json:12:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                "(id):|F|,"
  /* specs/discord/guild.json:13:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name"}' */
                "(name):s,"
  /* specs/discord/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}' */
                "(icon):s,"
  /* specs/discord/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}' */
                "(icon_hash):s,"
  /* specs/discord/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}' */
                "(splash):s,"
  /* specs/discord/guild.json:17:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}' */
                "(discovery_splash):s,"
  /* specs/discord/guild.json:18:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}' */
                "(owner):b,"
  /* specs/discord/guild.json:19:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}' */
                "(owner_id):|F|,"
  /* specs/discord/guild.json:20:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}' */
                "(permissions):d,"
  /* specs/discord/guild.json:21:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "name":"region"}' */
                "(region):s,"
  /* specs/discord/guild.json:22:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}' */
                "(afk_channel_id):|F|,"
  /* specs/discord/guild.json:23:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}' */
                "(afk_timeout):d,"
  /* specs/discord/guild.json:24:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}' */
                "(widget_enabled):b,"
  /* specs/discord/guild.json:25:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}' */
                "(widget_channel_id):|F|,"
  /* specs/discord/guild.json:26:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}' */
                "(verification_level):d,"
  /* specs/discord/guild.json:28:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}' */
                "(default_message_notifications):d,"
  /* specs/discord/guild.json:30:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}' */
                "(explicit_content_filter):d,"
  /* specs/discord/guild.json:31:82
     '{"type":{"base":"struct discord_permissions_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}' */
  /* specs/discord/guild.json:33:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}' */
                "(emojis):F,"
  /* specs/discord/guild.json:34:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true, 
              "comment":"array of guild feature strings"}' */
  /* specs/discord/guild.json:36:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}' */
                "(mfa_level):d,"
  /* specs/discord/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}' */
                "(application_id):|F|,"
  /* specs/discord/guild.json:38:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}' */
                "(system_channel_id):|F|,"
  /* specs/discord/guild.json:39:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}' */
                "(system_channel_flags):d,"
  /* specs/discord/guild.json:40:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}' */
                "(rules_channel_id):|F|,"
  /* specs/discord/guild.json:41:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}' */
                "(joined_at):|F|,"
  /* specs/discord/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}' */
                "(large):b,"
  /* specs/discord/guild.json:43:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}' */
                "(unavailable):b,"
  /* specs/discord/guild.json:44:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}' */
                "(member_count):d,"
  /* specs/discord/guild.json:45:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true, 
         "comment":"array of partial voice state objects"}' */
  /* specs/discord/guild.json:47:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}' */
                "(members):F,"
  /* specs/discord/guild.json:48:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}' */
                "(channels):F,"
  /* specs/discord/guild.json:50:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}' */
  /* specs/discord/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}' */
                "(max_presences):d,"
  /* specs/discord/guild.json:53:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}' */
                "(max_members):d,"
  /* specs/discord/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}' */
                "(vanity_url):s,"
  /* specs/discord/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}' */
                "(description):s,"
  /* specs/discord/guild.json:56:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}' */
                "(banner):s,"
  /* specs/discord/guild.json:57:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}' */
                "(premium_tier):d,"
  /* specs/discord/guild.json:58:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}' */
                "(premium_subscription_count):d,"
  /* specs/discord/guild.json:59:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "name":"preferred_locale"}' */
                "(preferred_locale):s,"
  /* specs/discord/guild.json:61:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}' */
                "(public_updates_channel_id):|F|,"
  /* specs/discord/guild.json:62:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}' */
                "(max_video_channel_users):d,"
  /* specs/discord/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}' */
                "(approximate_member_count):d,"
  /* specs/discord/guild.json:64:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}' */
                "(approximate_presence_count):d,"
  /* specs/discord/guild.json:65:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}' */
                "(welcome_screen):F,"
                "@arg_switches:b",
  /* specs/discord/guild.json:12:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/guild.json:13:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name"}' */
                p->name,
  /* specs/discord/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}' */
                p->icon,
  /* specs/discord/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}' */
                p->icon_hash,
  /* specs/discord/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}' */
                p->splash,
  /* specs/discord/guild.json:17:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}' */
                p->discovery_splash,
  /* specs/discord/guild.json:18:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}' */
                &p->owner,
  /* specs/discord/guild.json:19:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}' */
                cee_ulltostr, &p->owner_id,
  /* specs/discord/guild.json:20:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}' */
                &p->permissions,
  /* specs/discord/guild.json:21:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "name":"region"}' */
                p->region,
  /* specs/discord/guild.json:22:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}' */
                cee_ulltostr, &p->afk_channel_id,
  /* specs/discord/guild.json:23:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}' */
                &p->afk_timeout,
  /* specs/discord/guild.json:24:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}' */
                &p->widget_enabled,
  /* specs/discord/guild.json:25:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}' */
                cee_ulltostr, &p->widget_channel_id,
  /* specs/discord/guild.json:26:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}' */
                &p->verification_level,
  /* specs/discord/guild.json:28:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}' */
                &p->default_message_notifications,
  /* specs/discord/guild.json:30:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}' */
                &p->explicit_content_filter,
  /* specs/discord/guild.json:31:82
     '{"type":{"base":"struct discord_permissions_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}' */
  /* specs/discord/guild.json:33:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}' */
                discord_emoji_list_to_json, p->emojis,
  /* specs/discord/guild.json:34:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true, 
              "comment":"array of guild feature strings"}' */
  /* specs/discord/guild.json:36:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}' */
                &p->mfa_level,
  /* specs/discord/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}' */
                cee_ulltostr, &p->application_id,
  /* specs/discord/guild.json:38:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}' */
                cee_ulltostr, &p->system_channel_id,
  /* specs/discord/guild.json:39:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}' */
                &p->system_channel_flags,
  /* specs/discord/guild.json:40:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}' */
                cee_ulltostr, &p->rules_channel_id,
  /* specs/discord/guild.json:41:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}' */
                cee_unix_ms_to_iso8601, &p->joined_at,
  /* specs/discord/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}' */
                &p->large,
  /* specs/discord/guild.json:43:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}' */
                &p->unavailable,
  /* specs/discord/guild.json:44:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}' */
                &p->member_count,
  /* specs/discord/guild.json:45:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true, 
         "comment":"array of partial voice state objects"}' */
  /* specs/discord/guild.json:47:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}' */
                discord_guild_member_list_to_json, p->members,
  /* specs/discord/guild.json:48:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}' */
                discord_channel_list_to_json, p->channels,
  /* specs/discord/guild.json:50:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}' */
  /* specs/discord/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}' */
                &p->max_presences,
  /* specs/discord/guild.json:53:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}' */
                &p->max_members,
  /* specs/discord/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}' */
                p->vanity_url,
  /* specs/discord/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}' */
                p->description,
  /* specs/discord/guild.json:56:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}' */
                p->banner,
  /* specs/discord/guild.json:57:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}' */
                &p->premium_tier,
  /* specs/discord/guild.json:58:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}' */
                &p->premium_subscription_count,
  /* specs/discord/guild.json:59:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "name":"preferred_locale"}' */
                p->preferred_locale,
  /* specs/discord/guild.json:61:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}' */
                cee_ulltostr, &p->public_updates_channel_id,
  /* specs/discord/guild.json:62:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}' */
                &p->max_video_channel_users,
  /* specs/discord/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}' */
                &p->approximate_member_count,
  /* specs/discord/guild.json:64:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}' */
                &p->approximate_presence_count,
  /* specs/discord/guild.json:65:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}' */
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

void discord_guild_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_from_json(json, len, (struct discord_guild**)pp);
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
  /* specs/discord/guild.json:12:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  // p->id is a scalar
  /* specs/discord/guild.json:13:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name"}' */
  // p->name is a scalar
  /* specs/discord/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}' */
  if (d->icon)
    free(d->icon);
  /* specs/discord/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}' */
  if (d->icon_hash)
    free(d->icon_hash);
  /* specs/discord/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}' */
  if (d->splash)
    free(d->splash);
  /* specs/discord/guild.json:17:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}' */
  if (d->discovery_splash)
    free(d->discovery_splash);
  /* specs/discord/guild.json:18:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}' */
  // p->owner is a scalar
  /* specs/discord/guild.json:19:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}' */
  // p->owner_id is a scalar
  /* specs/discord/guild.json:20:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}' */
  // p->permissions is a scalar
  /* specs/discord/guild.json:21:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "name":"region"}' */
  // p->region is a scalar
  /* specs/discord/guild.json:22:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}' */
  // p->afk_channel_id is a scalar
  /* specs/discord/guild.json:23:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}' */
  // p->afk_timeout is a scalar
  /* specs/discord/guild.json:24:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}' */
  // p->widget_enabled is a scalar
  /* specs/discord/guild.json:25:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}' */
  // p->widget_channel_id is a scalar
  /* specs/discord/guild.json:26:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}' */
  // p->verification_level is a scalar
  /* specs/discord/guild.json:28:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}' */
  // p->default_message_notifications is a scalar
  /* specs/discord/guild.json:30:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}' */
  // p->explicit_content_filter is a scalar
  /* specs/discord/guild.json:31:82
     '{"type":{"base":"struct discord_permissions_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}' */
  // @todo p->(null)
  /* specs/discord/guild.json:33:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}' */
  if (d->emojis)
    discord_emoji_list_free(d->emojis);
  /* specs/discord/guild.json:34:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true, 
              "comment":"array of guild feature strings"}' */
  // @todo p->(null)
  /* specs/discord/guild.json:36:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}' */
  // p->mfa_level is a scalar
  /* specs/discord/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}' */
  // p->application_id is a scalar
  /* specs/discord/guild.json:38:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}' */
  // p->system_channel_id is a scalar
  /* specs/discord/guild.json:39:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}' */
  // p->system_channel_flags is a scalar
  /* specs/discord/guild.json:40:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}' */
  // p->rules_channel_id is a scalar
  /* specs/discord/guild.json:41:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}' */
  // p->joined_at is a scalar
  /* specs/discord/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}' */
  // p->large is a scalar
  /* specs/discord/guild.json:43:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}' */
  // p->unavailable is a scalar
  /* specs/discord/guild.json:44:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}' */
  // p->member_count is a scalar
  /* specs/discord/guild.json:45:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true, 
         "comment":"array of partial voice state objects"}' */
  // @todo p->(null)
  /* specs/discord/guild.json:47:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}' */
  if (d->members)
    discord_guild_member_list_free(d->members);
  /* specs/discord/guild.json:48:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}' */
  if (d->channels)
    discord_channel_list_free(d->channels);
  /* specs/discord/guild.json:50:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}' */
  // @todo p->(null)
  /* specs/discord/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}' */
  // p->max_presences is a scalar
  /* specs/discord/guild.json:53:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}' */
  // p->max_members is a scalar
  /* specs/discord/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}' */
  if (d->vanity_url)
    free(d->vanity_url);
  /* specs/discord/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}' */
  if (d->description)
    free(d->description);
  /* specs/discord/guild.json:56:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}' */
  if (d->banner)
    free(d->banner);
  /* specs/discord/guild.json:57:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}' */
  // p->premium_tier is a scalar
  /* specs/discord/guild.json:58:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}' */
  // p->premium_subscription_count is a scalar
  /* specs/discord/guild.json:59:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "name":"preferred_locale"}' */
  // p->preferred_locale is a scalar
  /* specs/discord/guild.json:61:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}' */
  // p->public_updates_channel_id is a scalar
  /* specs/discord/guild.json:62:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}' */
  // p->max_video_channel_users is a scalar
  /* specs/discord/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}' */
  // p->approximate_member_count is a scalar
  /* specs/discord/guild.json:64:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}' */
  // p->approximate_presence_count is a scalar
  /* specs/discord/guild.json:65:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}' */
  if (d->welcome_screen) {
    discord_guild_welcome_screen_cleanup(d->welcome_screen);
    free(d->welcome_screen);
  }
}

void discord_guild_init(struct discord_guild *p) {
  memset(p, 0, sizeof(struct discord_guild));
  /* specs/discord/guild.json:12:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */

  /* specs/discord/guild.json:13:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name"}' */

  /* specs/discord/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}' */

  /* specs/discord/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}' */

  /* specs/discord/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}' */

  /* specs/discord/guild.json:17:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}' */

  /* specs/discord/guild.json:18:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}' */

  /* specs/discord/guild.json:19:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}' */

  /* specs/discord/guild.json:20:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}' */

  /* specs/discord/guild.json:21:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "name":"region"}' */

  /* specs/discord/guild.json:22:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}' */

  /* specs/discord/guild.json:23:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}' */

  /* specs/discord/guild.json:24:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}' */

  /* specs/discord/guild.json:25:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}' */

  /* specs/discord/guild.json:26:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}' */

  /* specs/discord/guild.json:28:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}' */

  /* specs/discord/guild.json:30:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}' */

  /* specs/discord/guild.json:31:82
     '{"type":{"base":"struct discord_permissions_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}' */

  /* specs/discord/guild.json:33:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}' */

  /* specs/discord/guild.json:34:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true, 
              "comment":"array of guild feature strings"}' */

  /* specs/discord/guild.json:36:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}' */

  /* specs/discord/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}' */

  /* specs/discord/guild.json:38:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}' */

  /* specs/discord/guild.json:39:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}' */

  /* specs/discord/guild.json:40:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}' */

  /* specs/discord/guild.json:41:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}' */

  /* specs/discord/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}' */

  /* specs/discord/guild.json:43:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}' */

  /* specs/discord/guild.json:44:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}' */

  /* specs/discord/guild.json:45:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true, 
         "comment":"array of partial voice state objects"}' */

  /* specs/discord/guild.json:47:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}' */

  /* specs/discord/guild.json:48:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}' */

  /* specs/discord/guild.json:50:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}' */

  /* specs/discord/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}' */

  /* specs/discord/guild.json:53:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}' */

  /* specs/discord/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}' */

  /* specs/discord/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}' */

  /* specs/discord/guild.json:56:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}' */

  /* specs/discord/guild.json:57:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}' */

  /* specs/discord/guild.json:58:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}' */

  /* specs/discord/guild.json:59:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "name":"preferred_locale"}' */

  /* specs/discord/guild.json:61:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}' */

  /* specs/discord/guild.json:62:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}' */

  /* specs/discord/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}' */

  /* specs/discord/guild.json:64:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}' */

  /* specs/discord/guild.json:65:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}' */
  p->welcome_screen = malloc(sizeof *p->welcome_screen);
  discord_guild_welcome_screen_init(p->welcome_screen);

}
void discord_guild_list_free(struct discord_guild **p) {
  ntl_free((void**)p, (vfvp)discord_guild_cleanup);
}

void discord_guild_list_from_json(char *str, size_t len, struct discord_guild ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_list_to_json(char *str, size_t len, struct discord_guild **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_to_json_v);
}



enum discord_guild_default_message_notification_level discord_guild_default_message_notification_level_eval(char *s){
  if(strcasecmp("ALL_MESSAGES", s) == 0) return DISCORD_GUILD_ALL_MESSAGES;
  if(strcasecmp("ONLY_MENTIONS", s) == 0) return DISCORD_GUILD_ONLY_MENTIONS;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_guild_default_message_notification_level_print(enum discord_guild_default_message_notification_level v){

  switch (v) {
  case DISCORD_GUILD_ALL_MESSAGES: return "ALL_MESSAGES";
  case DISCORD_GUILD_ONLY_MENTIONS: return "ONLY_MENTIONS";
  }

  return NULL;
}
bool discord_guild_default_message_notification_level_cmp(enum discord_guild_default_message_notification_level v, char *s) {
  enum discord_guild_default_message_notification_level v1 = discord_guild_default_message_notification_level_eval(s);
  return v == v1;
}


enum discord_guild_explicit_content_filter_level discord_guild_explicit_content_filter_level_eval(char *s){
  if(strcasecmp("DISABLED", s) == 0) return DISCORD_GUILD_DISABLED;
  if(strcasecmp("MEMBERS_WITHOUT_ROLES", s) == 0) return DISCORD_GUILD_MEMBERS_WITHOUT_ROLES;
  if(strcasecmp("ALL_MEMBERS", s) == 0) return DISCORD_GUILD_ALL_MEMBERS;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_guild_explicit_content_filter_level_print(enum discord_guild_explicit_content_filter_level v){

  switch (v) {
  case DISCORD_GUILD_DISABLED: return "DISABLED";
  case DISCORD_GUILD_MEMBERS_WITHOUT_ROLES: return "MEMBERS_WITHOUT_ROLES";
  case DISCORD_GUILD_ALL_MEMBERS: return "ALL_MEMBERS";
  }

  return NULL;
}
bool discord_guild_explicit_content_filter_level_cmp(enum discord_guild_explicit_content_filter_level v, char *s) {
  enum discord_guild_explicit_content_filter_level v1 = discord_guild_explicit_content_filter_level_eval(s);
  return v == v1;
}


enum discord_guild_mfa_level discord_guild_mfa_level_eval(char *s){
  if(strcasecmp("DISCORD_MFA_NONE", s) == 0) return DISCORD_GUILD_DISCORD_MFA_NONE;
  if(strcasecmp("ELEVATED", s) == 0) return DISCORD_GUILD_ELEVATED;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_guild_mfa_level_print(enum discord_guild_mfa_level v){

  switch (v) {
  case DISCORD_GUILD_DISCORD_MFA_NONE: return "DISCORD_MFA_NONE";
  case DISCORD_GUILD_ELEVATED: return "ELEVATED";
  }

  return NULL;
}
bool discord_guild_mfa_level_cmp(enum discord_guild_mfa_level v, char *s) {
  enum discord_guild_mfa_level v1 = discord_guild_mfa_level_eval(s);
  return v == v1;
}


enum discord_guild_verification_level discord_guild_verification_level_eval(char *s){
  if(strcasecmp("DISCORD_VL_NONE", s) == 0) return DISCORD_GUILD_DISCORD_VL_NONE;
  if(strcasecmp("LOW", s) == 0) return DISCORD_GUILD_LOW;
  if(strcasecmp("MEDIUM", s) == 0) return DISCORD_GUILD_MEDIUM;
  if(strcasecmp("HIGH", s) == 0) return DISCORD_GUILD_HIGH;
  if(strcasecmp("VERY_HIGH", s) == 0) return DISCORD_GUILD_VERY_HIGH;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_guild_verification_level_print(enum discord_guild_verification_level v){

  switch (v) {
  case DISCORD_GUILD_DISCORD_VL_NONE: return "DISCORD_VL_NONE";
  case DISCORD_GUILD_LOW: return "LOW";
  case DISCORD_GUILD_MEDIUM: return "MEDIUM";
  case DISCORD_GUILD_HIGH: return "HIGH";
  case DISCORD_GUILD_VERY_HIGH: return "VERY_HIGH";
  }

  return NULL;
}
bool discord_guild_verification_level_cmp(enum discord_guild_verification_level v, char *s) {
  enum discord_guild_verification_level v1 = discord_guild_verification_level_eval(s);
  return v == v1;
}


enum discord_guild_premium_tier discord_guild_premium_tier_eval(char *s){
  if(strcasecmp("DISCORD_PREMIUM_NONE", s) == 0) return DISCORD_GUILD_DISCORD_PREMIUM_NONE;
  if(strcasecmp("TIER_1", s) == 0) return DISCORD_GUILD_TIER_1;
  if(strcasecmp("TIER_2", s) == 0) return DISCORD_GUILD_TIER_2;
  if(strcasecmp("TIER_3", s) == 0) return DISCORD_GUILD_TIER_3;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_guild_premium_tier_print(enum discord_guild_premium_tier v){

  switch (v) {
  case DISCORD_GUILD_DISCORD_PREMIUM_NONE: return "DISCORD_PREMIUM_NONE";
  case DISCORD_GUILD_TIER_1: return "TIER_1";
  case DISCORD_GUILD_TIER_2: return "TIER_2";
  case DISCORD_GUILD_TIER_3: return "TIER_3";
  }

  return NULL;
}
bool discord_guild_premium_tier_cmp(enum discord_guild_premium_tier v, char *s) {
  enum discord_guild_premium_tier v1 = discord_guild_premium_tier_eval(s);
  return v == v1;
}


enum discord_guild_system_channel_flags discord_guild_system_channel_flags_eval(char *s){
  if(strcasecmp("SUPRESS_JOIN_NOTIFICATIONS", s) == 0) return DISCORD_GUILD_SUPRESS_JOIN_NOTIFICATIONS;
  if(strcasecmp("SUPRESS_PREMIUM_SUBSCRIPTIONS", s) == 0) return DISCORD_GUILD_SUPRESS_PREMIUM_SUBSCRIPTIONS;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_guild_system_channel_flags_print(enum discord_guild_system_channel_flags v){

  switch (v) {
  case DISCORD_GUILD_SUPRESS_JOIN_NOTIFICATIONS: return "SUPRESS_JOIN_NOTIFICATIONS";
  case DISCORD_GUILD_SUPRESS_PREMIUM_SUBSCRIPTIONS: return "SUPRESS_PREMIUM_SUBSCRIPTIONS";
  }

  return NULL;
}
bool discord_guild_system_channel_flags_cmp(enum discord_guild_system_channel_flags v, char *s) {
  enum discord_guild_system_channel_flags v1 = discord_guild_system_channel_flags_eval(s);
  return v == v1;
}


enum discord_guild_features discord_guild_features_eval(char *s){
  if(strcasecmp("INVITE_SPLASH", s) == 0) return DISCORD_GUILD_INVITE_SPLASH;
  if(strcasecmp("VIP_REGIONS", s) == 0) return DISCORD_GUILD_VIP_REGIONS;
  if(strcasecmp("VANITY_URL", s) == 0) return DISCORD_GUILD_VANITY_URL;
  if(strcasecmp("VERIFIED", s) == 0) return DISCORD_GUILD_VERIFIED;
  if(strcasecmp("PARTNERED", s) == 0) return DISCORD_GUILD_PARTNERED;
  if(strcasecmp("COMMUNITY", s) == 0) return DISCORD_GUILD_COMMUNITY;
  if(strcasecmp("COMMERCE", s) == 0) return DISCORD_GUILD_COMMERCE;
  if(strcasecmp("NEWS", s) == 0) return DISCORD_GUILD_NEWS;
  if(strcasecmp("DISCOVERABLE", s) == 0) return DISCORD_GUILD_DISCOVERABLE;
  if(strcasecmp("FEATURABLE", s) == 0) return DISCORD_GUILD_FEATURABLE;
  if(strcasecmp("ANIMATED_ICON", s) == 0) return DISCORD_GUILD_ANIMATED_ICON;
  if(strcasecmp("BANNER", s) == 0) return DISCORD_GUILD_BANNER;
  if(strcasecmp("WELCOME_SCREEN_ENABLED", s) == 0) return DISCORD_GUILD_WELCOME_SCREEN_ENABLED;
  if(strcasecmp("MEMBER_VERIFICATION_GATE_ENABLED", s) == 0) return DISCORD_GUILD_MEMBER_VERIFICATION_GATE_ENABLED;
  if(strcasecmp("PREVIEW_ENABLED", s) == 0) return DISCORD_GUILD_PREVIEW_ENABLED;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_guild_features_print(enum discord_guild_features v){

  switch (v) {
  case DISCORD_GUILD_INVITE_SPLASH: return "INVITE_SPLASH";
  case DISCORD_GUILD_VIP_REGIONS: return "VIP_REGIONS";
  case DISCORD_GUILD_VANITY_URL: return "VANITY_URL";
  case DISCORD_GUILD_VERIFIED: return "VERIFIED";
  case DISCORD_GUILD_PARTNERED: return "PARTNERED";
  case DISCORD_GUILD_COMMUNITY: return "COMMUNITY";
  case DISCORD_GUILD_COMMERCE: return "COMMERCE";
  case DISCORD_GUILD_NEWS: return "NEWS";
  case DISCORD_GUILD_DISCOVERABLE: return "DISCOVERABLE";
  case DISCORD_GUILD_FEATURABLE: return "FEATURABLE";
  case DISCORD_GUILD_ANIMATED_ICON: return "ANIMATED_ICON";
  case DISCORD_GUILD_BANNER: return "BANNER";
  case DISCORD_GUILD_WELCOME_SCREEN_ENABLED: return "WELCOME_SCREEN_ENABLED";
  case DISCORD_GUILD_MEMBER_VERIFICATION_GATE_ENABLED: return "MEMBER_VERIFICATION_GATE_ENABLED";
  case DISCORD_GUILD_PREVIEW_ENABLED: return "PREVIEW_ENABLED";
  }

  return NULL;
}
bool discord_guild_features_cmp(enum discord_guild_features v, char *s) {
  enum discord_guild_features v1 = discord_guild_features_eval(s);
  return v == v1;
}

void discord_guild_unavailable_from_json(char *json, size_t len, struct discord_guild_unavailable **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_guild_unavailable *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.json:163:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):F,"
  /* specs/discord/guild.json:164:18
     '{"name":"unavailable", "type":{"base":"bool"}}' */
                "(unavailable):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.json:163:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->id,
  /* specs/discord/guild.json:164:18
     '{"name":"unavailable", "type":{"base":"bool"}}' */
                &p->unavailable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_unavailable_use_default_inject_settings(struct discord_guild_unavailable *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.json:163:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.json:164:18
     '{"name":"unavailable", "type":{"base":"bool"}}' */
  p->__M.arg_switches[1] = &p->unavailable;

}

size_t discord_guild_unavailable_to_json(char *json, size_t len, struct discord_guild_unavailable *p)
{
  size_t r;
  discord_guild_unavailable_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.json:163:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):|F|,"
  /* specs/discord/guild.json:164:18
     '{"name":"unavailable", "type":{"base":"bool"}}' */
                "(unavailable):b,"
                "@arg_switches:b",
  /* specs/discord/guild.json:163:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->id,
  /* specs/discord/guild.json:164:18
     '{"name":"unavailable", "type":{"base":"bool"}}' */
                &p->unavailable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_unavailable_cleanup_v(void *p) {
  discord_guild_unavailable_cleanup((struct discord_guild_unavailable *)p);
}

void discord_guild_unavailable_init_v(void *p) {
  discord_guild_unavailable_init((struct discord_guild_unavailable *)p);
}

void discord_guild_unavailable_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_unavailable_from_json(json, len, (struct discord_guild_unavailable**)pp);
}

size_t discord_guild_unavailable_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_unavailable_to_json(json, len, (struct discord_guild_unavailable*)p);
}

void discord_guild_unavailable_list_free_v(void **p) {
  discord_guild_unavailable_list_free((struct discord_guild_unavailable**)p);
}

void discord_guild_unavailable_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_unavailable_list_from_json(str, len, (struct discord_guild_unavailable ***)p);
}

size_t discord_guild_unavailable_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_unavailable_list_to_json(str, len, (struct discord_guild_unavailable **)p);
}


void discord_guild_unavailable_cleanup(struct discord_guild_unavailable *d) {
  /* specs/discord/guild.json:163:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->id is a scalar
  /* specs/discord/guild.json:164:18
     '{"name":"unavailable", "type":{"base":"bool"}}' */
  // p->unavailable is a scalar
}

void discord_guild_unavailable_init(struct discord_guild_unavailable *p) {
  memset(p, 0, sizeof(struct discord_guild_unavailable));
  /* specs/discord/guild.json:163:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/guild.json:164:18
     '{"name":"unavailable", "type":{"base":"bool"}}' */

}
void discord_guild_unavailable_list_free(struct discord_guild_unavailable **p) {
  ntl_free((void**)p, (vfvp)discord_guild_unavailable_cleanup);
}

void discord_guild_unavailable_list_from_json(char *str, size_t len, struct discord_guild_unavailable ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_unavailable);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_unavailable_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_unavailable_list_to_json(char *str, size_t len, struct discord_guild_unavailable **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_unavailable_to_json_v);
}


void discord_guild_preview_from_json(char *json, size_t len, struct discord_guild_preview **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_guild_preview *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.json:173:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):F,"
  /* specs/discord/guild.json:174:18
     '{"name":"name", "type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
                "(name):s,"
  /* specs/discord/guild.json:175:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}' */
                "(icon):?s,"
  /* specs/discord/guild.json:176:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
                "(splash):?s,"
  /* specs/discord/guild.json:177:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
                "(discovery_splash):?s,"
  /* specs/discord/guild.json:178:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}' */
                "(emojis):F,"
  /* specs/discord/guild.json:179:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}' */
  /* specs/discord/guild.json:180:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}' */
                "(approximate_member_count):d,"
  /* specs/discord/guild.json:181:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}' */
                "(approximate_presence_count):d,"
  /* specs/discord/guild.json:182:18
     '{"name":"description", "type":{"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
                "(description):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.json:173:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->id,
  /* specs/discord/guild.json:174:18
     '{"name":"name", "type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
                p->name,
  /* specs/discord/guild.json:175:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}' */
                &p->icon,
  /* specs/discord/guild.json:176:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
                &p->splash,
  /* specs/discord/guild.json:177:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
                &p->discovery_splash,
  /* specs/discord/guild.json:178:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}' */
                discord_emoji_list_from_json, &p->emojis,
  /* specs/discord/guild.json:179:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}' */
  /* specs/discord/guild.json:180:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}' */
                &p->approximate_member_count,
  /* specs/discord/guild.json:181:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}' */
                &p->approximate_presence_count,
  /* specs/discord/guild.json:182:18
     '{"name":"description", "type":{"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
                p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_preview_use_default_inject_settings(struct discord_guild_preview *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.json:173:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.json:174:18
     '{"name":"name", "type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
  p->__M.arg_switches[1] = p->name;

  /* specs/discord/guild.json:175:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}' */
  p->__M.arg_switches[2] = p->icon;

  /* specs/discord/guild.json:176:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
  p->__M.arg_switches[3] = p->splash;

  /* specs/discord/guild.json:177:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
  p->__M.arg_switches[4] = p->discovery_splash;

  /* specs/discord/guild.json:178:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}' */
  p->__M.arg_switches[5] = p->emojis;

  /* specs/discord/guild.json:179:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}' */

  /* specs/discord/guild.json:180:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}' */
  p->__M.arg_switches[7] = &p->approximate_member_count;

  /* specs/discord/guild.json:181:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}' */
  p->__M.arg_switches[8] = &p->approximate_presence_count;

  /* specs/discord/guild.json:182:18
     '{"name":"description", "type":{"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
  p->__M.arg_switches[9] = p->description;

}

size_t discord_guild_preview_to_json(char *json, size_t len, struct discord_guild_preview *p)
{
  size_t r;
  discord_guild_preview_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.json:173:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):|F|,"
  /* specs/discord/guild.json:174:18
     '{"name":"name", "type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
                "(name):s,"
  /* specs/discord/guild.json:175:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}' */
                "(icon):s,"
  /* specs/discord/guild.json:176:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
                "(splash):s,"
  /* specs/discord/guild.json:177:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
                "(discovery_splash):s,"
  /* specs/discord/guild.json:178:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}' */
                "(emojis):F,"
  /* specs/discord/guild.json:179:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}' */
  /* specs/discord/guild.json:180:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}' */
                "(approximate_member_count):d,"
  /* specs/discord/guild.json:181:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}' */
                "(approximate_presence_count):d,"
  /* specs/discord/guild.json:182:18
     '{"name":"description", "type":{"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
                "(description):s,"
                "@arg_switches:b",
  /* specs/discord/guild.json:173:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->id,
  /* specs/discord/guild.json:174:18
     '{"name":"name", "type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
                p->name,
  /* specs/discord/guild.json:175:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}' */
                p->icon,
  /* specs/discord/guild.json:176:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
                p->splash,
  /* specs/discord/guild.json:177:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
                p->discovery_splash,
  /* specs/discord/guild.json:178:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}' */
                discord_emoji_list_to_json, p->emojis,
  /* specs/discord/guild.json:179:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}' */
  /* specs/discord/guild.json:180:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}' */
                &p->approximate_member_count,
  /* specs/discord/guild.json:181:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}' */
                &p->approximate_presence_count,
  /* specs/discord/guild.json:182:18
     '{"name":"description", "type":{"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
                p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_preview_cleanup_v(void *p) {
  discord_guild_preview_cleanup((struct discord_guild_preview *)p);
}

void discord_guild_preview_init_v(void *p) {
  discord_guild_preview_init((struct discord_guild_preview *)p);
}

void discord_guild_preview_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_preview_from_json(json, len, (struct discord_guild_preview**)pp);
}

size_t discord_guild_preview_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_preview_to_json(json, len, (struct discord_guild_preview*)p);
}

void discord_guild_preview_list_free_v(void **p) {
  discord_guild_preview_list_free((struct discord_guild_preview**)p);
}

void discord_guild_preview_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_preview_list_from_json(str, len, (struct discord_guild_preview ***)p);
}

size_t discord_guild_preview_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_preview_list_to_json(str, len, (struct discord_guild_preview **)p);
}


void discord_guild_preview_cleanup(struct discord_guild_preview *d) {
  /* specs/discord/guild.json:173:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->id is a scalar
  /* specs/discord/guild.json:174:18
     '{"name":"name", "type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
  // p->name is a scalar
  /* specs/discord/guild.json:175:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}' */
  if (d->icon)
    free(d->icon);
  /* specs/discord/guild.json:176:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
  if (d->splash)
    free(d->splash);
  /* specs/discord/guild.json:177:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
  if (d->discovery_splash)
    free(d->discovery_splash);
  /* specs/discord/guild.json:178:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}' */
  if (d->emojis)
    discord_emoji_list_free(d->emojis);
  /* specs/discord/guild.json:179:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}' */
  // @todo p->(null)
  /* specs/discord/guild.json:180:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}' */
  // p->approximate_member_count is a scalar
  /* specs/discord/guild.json:181:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}' */
  // p->approximate_presence_count is a scalar
  /* specs/discord/guild.json:182:18
     '{"name":"description", "type":{"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
  // p->description is a scalar
}

void discord_guild_preview_init(struct discord_guild_preview *p) {
  memset(p, 0, sizeof(struct discord_guild_preview));
  /* specs/discord/guild.json:173:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/guild.json:174:18
     '{"name":"name", "type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */

  /* specs/discord/guild.json:175:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}' */

  /* specs/discord/guild.json:176:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */

  /* specs/discord/guild.json:177:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */

  /* specs/discord/guild.json:178:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}' */

  /* specs/discord/guild.json:179:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}' */

  /* specs/discord/guild.json:180:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}' */

  /* specs/discord/guild.json:181:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}' */

  /* specs/discord/guild.json:182:18
     '{"name":"description", "type":{"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */

}
void discord_guild_preview_list_free(struct discord_guild_preview **p) {
  ntl_free((void**)p, (vfvp)discord_guild_preview_cleanup);
}

void discord_guild_preview_list_from_json(char *str, size_t len, struct discord_guild_preview ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_preview);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_preview_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_preview_list_to_json(char *str, size_t len, struct discord_guild_preview **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_preview_to_json_v);
}


void discord_guild_widget_from_json(char *json, size_t len, struct discord_guild_widget **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_guild_widget *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.json:191:18
     '{"name":"enabled", "type":{"base":"bool"}}' */
                "(enabled):b,"
  /* specs/discord/guild.json:192:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}}' */
                "(channel_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.json:191:18
     '{"name":"enabled", "type":{"base":"bool"}}' */
                &p->enabled,
  /* specs/discord/guild.json:192:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}}' */
                cee_strtoull, &p->channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_widget_use_default_inject_settings(struct discord_guild_widget *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.json:191:18
     '{"name":"enabled", "type":{"base":"bool"}}' */
  p->__M.arg_switches[0] = &p->enabled;

  /* specs/discord/guild.json:192:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}}' */
  p->__M.arg_switches[1] = &p->channel_id;

}

size_t discord_guild_widget_to_json(char *json, size_t len, struct discord_guild_widget *p)
{
  size_t r;
  discord_guild_widget_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.json:191:18
     '{"name":"enabled", "type":{"base":"bool"}}' */
                "(enabled):b,"
  /* specs/discord/guild.json:192:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}}' */
                "(channel_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/guild.json:191:18
     '{"name":"enabled", "type":{"base":"bool"}}' */
                &p->enabled,
  /* specs/discord/guild.json:192:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}}' */
                cee_ulltostr, &p->channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_widget_cleanup_v(void *p) {
  discord_guild_widget_cleanup((struct discord_guild_widget *)p);
}

void discord_guild_widget_init_v(void *p) {
  discord_guild_widget_init((struct discord_guild_widget *)p);
}

void discord_guild_widget_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_widget_from_json(json, len, (struct discord_guild_widget**)pp);
}

size_t discord_guild_widget_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_widget_to_json(json, len, (struct discord_guild_widget*)p);
}

void discord_guild_widget_list_free_v(void **p) {
  discord_guild_widget_list_free((struct discord_guild_widget**)p);
}

void discord_guild_widget_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_widget_list_from_json(str, len, (struct discord_guild_widget ***)p);
}

size_t discord_guild_widget_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_widget_list_to_json(str, len, (struct discord_guild_widget **)p);
}


void discord_guild_widget_cleanup(struct discord_guild_widget *d) {
  /* specs/discord/guild.json:191:18
     '{"name":"enabled", "type":{"base":"bool"}}' */
  // p->enabled is a scalar
  /* specs/discord/guild.json:192:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}}' */
  // p->channel_id is a scalar
}

void discord_guild_widget_init(struct discord_guild_widget *p) {
  memset(p, 0, sizeof(struct discord_guild_widget));
  /* specs/discord/guild.json:191:18
     '{"name":"enabled", "type":{"base":"bool"}}' */

  /* specs/discord/guild.json:192:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}}' */

}
void discord_guild_widget_list_free(struct discord_guild_widget **p) {
  ntl_free((void**)p, (vfvp)discord_guild_widget_cleanup);
}

void discord_guild_widget_list_from_json(char *str, size_t len, struct discord_guild_widget ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_widget);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_widget_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_widget_list_to_json(char *str, size_t len, struct discord_guild_widget **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_widget_to_json_v);
}


void discord_guild_member_from_json(char *json, size_t len, struct discord_guild_member **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_guild_member *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.json:202:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
                "(user):F,"
  /* specs/discord/guild.json:203:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "option":true}' */
                "(nick):s,"
  /* specs/discord/guild.json:204:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}' */
                "(roles):F,"
  /* specs/discord/guild.json:205:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(joined_at):F,"
  /* specs/discord/guild.json:206:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(premium_since):F,"
  /* specs/discord/guild.json:207:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
                "(deaf):b,"
  /* specs/discord/guild.json:208:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
                "(mute):b,"
  /* specs/discord/guild.json:209:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}' */
                "(pending):b,"
  /* specs/discord/guild.json:210:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}' */
                "(permissions):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.json:202:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
                discord_user_from_json, &p->user,
  /* specs/discord/guild.json:203:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "option":true}' */
                p->nick,
  /* specs/discord/guild.json:204:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}' */
                ja_u64_list_from_json, &p->roles,
  /* specs/discord/guild.json:205:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_iso8601_to_unix_ms, &p->joined_at,
  /* specs/discord/guild.json:206:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_iso8601_to_unix_ms, &p->premium_since,
  /* specs/discord/guild.json:207:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
                &p->deaf,
  /* specs/discord/guild.json:208:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
                &p->mute,
  /* specs/discord/guild.json:209:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}' */
                &p->pending,
  /* specs/discord/guild.json:210:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}' */
                &p->permissions,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_member_use_default_inject_settings(struct discord_guild_member *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.json:202:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
  p->__M.arg_switches[0] = p->user;

  /* specs/discord/guild.json:203:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "option":true}' */
  p->__M.arg_switches[1] = p->nick;

  /* specs/discord/guild.json:204:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}' */
  p->__M.arg_switches[2] = p->roles;

  /* specs/discord/guild.json:205:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  p->__M.arg_switches[3] = &p->joined_at;

  /* specs/discord/guild.json:206:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  p->__M.arg_switches[4] = &p->premium_since;

  /* specs/discord/guild.json:207:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
  p->__M.arg_switches[5] = &p->deaf;

  /* specs/discord/guild.json:208:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
  p->__M.arg_switches[6] = &p->mute;

  /* specs/discord/guild.json:209:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}' */
  p->__M.arg_switches[7] = &p->pending;

  /* specs/discord/guild.json:210:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}' */
  p->__M.arg_switches[8] = p->permissions;

}

size_t discord_guild_member_to_json(char *json, size_t len, struct discord_guild_member *p)
{
  size_t r;
  discord_guild_member_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.json:202:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
                "(user):F,"
  /* specs/discord/guild.json:203:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "option":true}' */
                "(nick):s,"
  /* specs/discord/guild.json:204:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}' */
                "(roles):F,"
  /* specs/discord/guild.json:205:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(joined_at):|F|,"
  /* specs/discord/guild.json:206:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(premium_since):|F|,"
  /* specs/discord/guild.json:207:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
                "(deaf):b,"
  /* specs/discord/guild.json:208:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
                "(mute):b,"
  /* specs/discord/guild.json:209:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}' */
                "(pending):b,"
  /* specs/discord/guild.json:210:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}' */
                "(permissions):s,"
                "@arg_switches:b",
  /* specs/discord/guild.json:202:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
                discord_user_to_json, p->user,
  /* specs/discord/guild.json:203:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "option":true}' */
                p->nick,
  /* specs/discord/guild.json:204:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}' */
                ja_u64_list_to_json, p->roles,
  /* specs/discord/guild.json:205:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_unix_ms_to_iso8601, &p->joined_at,
  /* specs/discord/guild.json:206:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_unix_ms_to_iso8601, &p->premium_since,
  /* specs/discord/guild.json:207:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
                &p->deaf,
  /* specs/discord/guild.json:208:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
                &p->mute,
  /* specs/discord/guild.json:209:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}' */
                &p->pending,
  /* specs/discord/guild.json:210:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}' */
                p->permissions,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_member_cleanup_v(void *p) {
  discord_guild_member_cleanup((struct discord_guild_member *)p);
}

void discord_guild_member_init_v(void *p) {
  discord_guild_member_init((struct discord_guild_member *)p);
}

void discord_guild_member_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_member_from_json(json, len, (struct discord_guild_member**)pp);
}

size_t discord_guild_member_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_member_to_json(json, len, (struct discord_guild_member*)p);
}

void discord_guild_member_list_free_v(void **p) {
  discord_guild_member_list_free((struct discord_guild_member**)p);
}

void discord_guild_member_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_member_list_from_json(str, len, (struct discord_guild_member ***)p);
}

size_t discord_guild_member_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_member_list_to_json(str, len, (struct discord_guild_member **)p);
}


void discord_guild_member_cleanup(struct discord_guild_member *d) {
  /* specs/discord/guild.json:202:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
  if (d->user) {
    discord_user_cleanup(d->user);
    free(d->user);
  }
  /* specs/discord/guild.json:203:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "option":true}' */
  // p->nick is a scalar
  /* specs/discord/guild.json:204:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}' */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* specs/discord/guild.json:205:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  // p->joined_at is a scalar
  /* specs/discord/guild.json:206:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  // p->premium_since is a scalar
  /* specs/discord/guild.json:207:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
  // p->deaf is a scalar
  /* specs/discord/guild.json:208:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
  // p->mute is a scalar
  /* specs/discord/guild.json:209:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}' */
  // p->pending is a scalar
  /* specs/discord/guild.json:210:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}' */
  if (d->permissions)
    free(d->permissions);
}

void discord_guild_member_init(struct discord_guild_member *p) {
  memset(p, 0, sizeof(struct discord_guild_member));
  /* specs/discord/guild.json:202:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
  p->user = malloc(sizeof *p->user);
  discord_user_init(p->user);

  /* specs/discord/guild.json:203:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "option":true}' */

  /* specs/discord/guild.json:204:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}' */

  /* specs/discord/guild.json:205:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */

  /* specs/discord/guild.json:206:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */

  /* specs/discord/guild.json:207:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */

  /* specs/discord/guild.json:208:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */

  /* specs/discord/guild.json:209:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}' */

  /* specs/discord/guild.json:210:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}' */

}
void discord_guild_member_list_free(struct discord_guild_member **p) {
  ntl_free((void**)p, (vfvp)discord_guild_member_cleanup);
}

void discord_guild_member_list_from_json(char *str, size_t len, struct discord_guild_member ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_member);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_member_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_member_list_to_json(char *str, size_t len, struct discord_guild_member **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_member_to_json_v);
}


void discord_guild_integration_from_json(char *json, size_t len, struct discord_guild_integration **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_guild_integration *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.json:220:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* specs/discord/guild.json:221:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* specs/discord/guild.json:222:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                "(type):?s,"
  /* specs/discord/guild.json:223:20
     '{ "name": "enabled", "type":{ "base":"bool"}}' */
                "(enabled):b,"
  /* specs/discord/guild.json:224:20
     '{ "name": "syncing", "type":{ "base":"bool"}}' */
                "(syncing):b,"
  /* specs/discord/guild.json:225:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(role_id):F,"
  /* specs/discord/guild.json:226:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}' */
                "(enable_emotions):b,"
  /* specs/discord/guild.json:227:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}' */
                "(expire_behavior):d,"
  /* specs/discord/guild.json:228:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}' */
                "(expire_grace_period):d,"
  /* specs/discord/guild.json:229:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}' */
                "(user):F,"
  /* specs/discord/guild.json:230:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}' */
                "(account):F,"
  /* specs/discord/guild.json:231:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
                "(synced_at):F,"
  /* specs/discord/guild.json:232:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}' */
                "(subscriber_count):d,"
  /* specs/discord/guild.json:233:20
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
                "(revoked):b,"
  /* specs/discord/guild.json:234:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}' */
                "(application):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.json:220:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->id,
  /* specs/discord/guild.json:221:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                &p->name,
  /* specs/discord/guild.json:222:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                &p->type,
  /* specs/discord/guild.json:223:20
     '{ "name": "enabled", "type":{ "base":"bool"}}' */
                &p->enabled,
  /* specs/discord/guild.json:224:20
     '{ "name": "syncing", "type":{ "base":"bool"}}' */
                &p->syncing,
  /* specs/discord/guild.json:225:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->role_id,
  /* specs/discord/guild.json:226:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}' */
                &p->enable_emotions,
  /* specs/discord/guild.json:227:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}' */
                &p->expire_behavior,
  /* specs/discord/guild.json:228:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}' */
                &p->expire_grace_period,
  /* specs/discord/guild.json:229:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}' */
                discord_user_from_json, &p->user,
  /* specs/discord/guild.json:230:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}' */
                discord_guild_integration_account_from_json, &p->account,
  /* specs/discord/guild.json:231:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
                cee_iso8601_to_unix_ms, &p->synced_at,
  /* specs/discord/guild.json:232:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}' */
                &p->subscriber_count,
  /* specs/discord/guild.json:233:20
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
                &p->revoked,
  /* specs/discord/guild.json:234:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}' */
                discord_guild_integration_application_from_json, &p->application,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_integration_use_default_inject_settings(struct discord_guild_integration *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.json:220:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.json:221:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[1] = p->name;

  /* specs/discord/guild.json:222:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[2] = p->type;

  /* specs/discord/guild.json:223:20
     '{ "name": "enabled", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[3] = &p->enabled;

  /* specs/discord/guild.json:224:20
     '{ "name": "syncing", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[4] = &p->syncing;

  /* specs/discord/guild.json:225:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[5] = &p->role_id;

  /* specs/discord/guild.json:226:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[6] = &p->enable_emotions;

  /* specs/discord/guild.json:227:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}' */
  p->__M.arg_switches[7] = &p->expire_behavior;

  /* specs/discord/guild.json:228:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}' */
  p->__M.arg_switches[8] = &p->expire_grace_period;

  /* specs/discord/guild.json:229:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}' */
  p->__M.arg_switches[9] = p->user;

  /* specs/discord/guild.json:230:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}' */
  p->__M.arg_switches[10] = p->account;

  /* specs/discord/guild.json:231:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
  p->__M.arg_switches[11] = &p->synced_at;

  /* specs/discord/guild.json:232:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}' */
  p->__M.arg_switches[12] = &p->subscriber_count;

  /* specs/discord/guild.json:233:20
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[13] = &p->revoked;

  /* specs/discord/guild.json:234:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}' */
  p->__M.arg_switches[14] = p->application;

}

size_t discord_guild_integration_to_json(char *json, size_t len, struct discord_guild_integration *p)
{
  size_t r;
  discord_guild_integration_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.json:220:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* specs/discord/guild.json:221:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):s,"
  /* specs/discord/guild.json:222:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                "(type):s,"
  /* specs/discord/guild.json:223:20
     '{ "name": "enabled", "type":{ "base":"bool"}}' */
                "(enabled):b,"
  /* specs/discord/guild.json:224:20
     '{ "name": "syncing", "type":{ "base":"bool"}}' */
                "(syncing):b,"
  /* specs/discord/guild.json:225:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(role_id):|F|,"
  /* specs/discord/guild.json:226:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}' */
                "(enable_emotions):b,"
  /* specs/discord/guild.json:227:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}' */
                "(expire_behavior):d,"
  /* specs/discord/guild.json:228:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}' */
                "(expire_grace_period):d,"
  /* specs/discord/guild.json:229:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}' */
                "(user):F,"
  /* specs/discord/guild.json:230:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}' */
                "(account):F,"
  /* specs/discord/guild.json:231:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
                "(synced_at):|F|,"
  /* specs/discord/guild.json:232:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}' */
                "(subscriber_count):d,"
  /* specs/discord/guild.json:233:20
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
                "(revoked):b,"
  /* specs/discord/guild.json:234:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}' */
                "(application):F,"
                "@arg_switches:b",
  /* specs/discord/guild.json:220:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->id,
  /* specs/discord/guild.json:221:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                p->name,
  /* specs/discord/guild.json:222:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                p->type,
  /* specs/discord/guild.json:223:20
     '{ "name": "enabled", "type":{ "base":"bool"}}' */
                &p->enabled,
  /* specs/discord/guild.json:224:20
     '{ "name": "syncing", "type":{ "base":"bool"}}' */
                &p->syncing,
  /* specs/discord/guild.json:225:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->role_id,
  /* specs/discord/guild.json:226:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}' */
                &p->enable_emotions,
  /* specs/discord/guild.json:227:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}' */
                &p->expire_behavior,
  /* specs/discord/guild.json:228:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}' */
                &p->expire_grace_period,
  /* specs/discord/guild.json:229:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}' */
                discord_user_to_json, p->user,
  /* specs/discord/guild.json:230:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}' */
                discord_guild_integration_account_to_json, p->account,
  /* specs/discord/guild.json:231:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
                cee_unix_ms_to_iso8601, &p->synced_at,
  /* specs/discord/guild.json:232:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}' */
                &p->subscriber_count,
  /* specs/discord/guild.json:233:20
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
                &p->revoked,
  /* specs/discord/guild.json:234:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}' */
                discord_guild_integration_application_to_json, p->application,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_integration_cleanup_v(void *p) {
  discord_guild_integration_cleanup((struct discord_guild_integration *)p);
}

void discord_guild_integration_init_v(void *p) {
  discord_guild_integration_init((struct discord_guild_integration *)p);
}

void discord_guild_integration_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_integration_from_json(json, len, (struct discord_guild_integration**)pp);
}

size_t discord_guild_integration_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_integration_to_json(json, len, (struct discord_guild_integration*)p);
}

void discord_guild_integration_list_free_v(void **p) {
  discord_guild_integration_list_free((struct discord_guild_integration**)p);
}

void discord_guild_integration_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_integration_list_from_json(str, len, (struct discord_guild_integration ***)p);
}

size_t discord_guild_integration_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_integration_list_to_json(str, len, (struct discord_guild_integration **)p);
}


void discord_guild_integration_cleanup(struct discord_guild_integration *d) {
  /* specs/discord/guild.json:220:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->id is a scalar
  /* specs/discord/guild.json:221:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* specs/discord/guild.json:222:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  if (d->type)
    free(d->type);
  /* specs/discord/guild.json:223:20
     '{ "name": "enabled", "type":{ "base":"bool"}}' */
  // p->enabled is a scalar
  /* specs/discord/guild.json:224:20
     '{ "name": "syncing", "type":{ "base":"bool"}}' */
  // p->syncing is a scalar
  /* specs/discord/guild.json:225:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->role_id is a scalar
  /* specs/discord/guild.json:226:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}' */
  // p->enable_emotions is a scalar
  /* specs/discord/guild.json:227:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}' */
  // p->expire_behavior is a scalar
  /* specs/discord/guild.json:228:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}' */
  // p->expire_grace_period is a scalar
  /* specs/discord/guild.json:229:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}' */
  if (d->user) {
    discord_user_cleanup(d->user);
    free(d->user);
  }
  /* specs/discord/guild.json:230:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}' */
  if (d->account) {
    discord_guild_integration_account_cleanup(d->account);
    free(d->account);
  }
  /* specs/discord/guild.json:231:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
  // p->synced_at is a scalar
  /* specs/discord/guild.json:232:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}' */
  // p->subscriber_count is a scalar
  /* specs/discord/guild.json:233:20
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
  // p->revoked is a scalar
  /* specs/discord/guild.json:234:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}' */
  if (d->application) {
    discord_guild_integration_application_cleanup(d->application);
    free(d->application);
  }
}

void discord_guild_integration_init(struct discord_guild_integration *p) {
  memset(p, 0, sizeof(struct discord_guild_integration));
  /* specs/discord/guild.json:220:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/guild.json:221:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/discord/guild.json:222:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/discord/guild.json:223:20
     '{ "name": "enabled", "type":{ "base":"bool"}}' */

  /* specs/discord/guild.json:224:20
     '{ "name": "syncing", "type":{ "base":"bool"}}' */

  /* specs/discord/guild.json:225:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/guild.json:226:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}' */

  /* specs/discord/guild.json:227:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}' */

  /* specs/discord/guild.json:228:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}' */

  /* specs/discord/guild.json:229:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}' */
  p->user = malloc(sizeof *p->user);
  discord_user_init(p->user);

  /* specs/discord/guild.json:230:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}' */
  p->account = malloc(sizeof *p->account);
  discord_guild_integration_account_init(p->account);

  /* specs/discord/guild.json:231:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */

  /* specs/discord/guild.json:232:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}' */

  /* specs/discord/guild.json:233:20
     '{ "name": "revoked", "type":{ "base":"bool"}}' */

  /* specs/discord/guild.json:234:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}' */
  p->application = malloc(sizeof *p->application);
  discord_guild_integration_application_init(p->application);

}
void discord_guild_integration_list_free(struct discord_guild_integration **p) {
  ntl_free((void**)p, (vfvp)discord_guild_integration_cleanup);
}

void discord_guild_integration_list_from_json(char *str, size_t len, struct discord_guild_integration ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_integration);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_integration_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_integration_list_to_json(char *str, size_t len, struct discord_guild_integration **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_integration_to_json_v);
}



enum discord_guild_integration_expire_behaviors discord_guild_integration_expire_behaviors_eval(char *s){
  if(strcasecmp("REMOVE_ROLE", s) == 0) return DISCORD_GUILD_INTEGRATION_REMOVE_ROLE;
  if(strcasecmp("KICK", s) == 0) return DISCORD_GUILD_INTEGRATION_KICK;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_guild_integration_expire_behaviors_print(enum discord_guild_integration_expire_behaviors v){

  switch (v) {
  case DISCORD_GUILD_INTEGRATION_REMOVE_ROLE: return "REMOVE_ROLE";
  case DISCORD_GUILD_INTEGRATION_KICK: return "KICK";
  }

  return NULL;
}
bool discord_guild_integration_expire_behaviors_cmp(enum discord_guild_integration_expire_behaviors v, char *s) {
  enum discord_guild_integration_expire_behaviors v1 = discord_guild_integration_expire_behaviors_eval(s);
  return v == v1;
}

void discord_guild_integration_account_from_json(char *json, size_t len, struct discord_guild_integration_account **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_guild_integration_account *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.json:253:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* specs/discord/guild.json:254:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.json:253:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->id,
  /* specs/discord/guild.json:254:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_integration_account_use_default_inject_settings(struct discord_guild_integration_account *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.json:253:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.json:254:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[1] = p->name;

}

size_t discord_guild_integration_account_to_json(char *json, size_t len, struct discord_guild_integration_account *p)
{
  size_t r;
  discord_guild_integration_account_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.json:253:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* specs/discord/guild.json:254:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
                "@arg_switches:b",
  /* specs/discord/guild.json:253:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->id,
  /* specs/discord/guild.json:254:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_integration_account_cleanup_v(void *p) {
  discord_guild_integration_account_cleanup((struct discord_guild_integration_account *)p);
}

void discord_guild_integration_account_init_v(void *p) {
  discord_guild_integration_account_init((struct discord_guild_integration_account *)p);
}

void discord_guild_integration_account_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_integration_account_from_json(json, len, (struct discord_guild_integration_account**)pp);
}

size_t discord_guild_integration_account_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_integration_account_to_json(json, len, (struct discord_guild_integration_account*)p);
}

void discord_guild_integration_account_list_free_v(void **p) {
  discord_guild_integration_account_list_free((struct discord_guild_integration_account**)p);
}

void discord_guild_integration_account_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_integration_account_list_from_json(str, len, (struct discord_guild_integration_account ***)p);
}

size_t discord_guild_integration_account_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_integration_account_list_to_json(str, len, (struct discord_guild_integration_account **)p);
}


void discord_guild_integration_account_cleanup(struct discord_guild_integration_account *d) {
  /* specs/discord/guild.json:253:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->id is a scalar
  /* specs/discord/guild.json:254:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
}

void discord_guild_integration_account_init(struct discord_guild_integration_account *p) {
  memset(p, 0, sizeof(struct discord_guild_integration_account));
  /* specs/discord/guild.json:253:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/guild.json:254:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */

}
void discord_guild_integration_account_list_free(struct discord_guild_integration_account **p) {
  ntl_free((void**)p, (vfvp)discord_guild_integration_account_cleanup);
}

void discord_guild_integration_account_list_from_json(char *str, size_t len, struct discord_guild_integration_account ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_integration_account);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_integration_account_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_integration_account_list_to_json(char *str, size_t len, struct discord_guild_integration_account **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_integration_account_to_json_v);
}


void discord_guild_integration_application_from_json(char *json, size_t len, struct discord_guild_integration_application **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_guild_integration_application *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.json:263:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* specs/discord/guild.json:264:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,"
  /* specs/discord/guild.json:265:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
                "(icon):s,"
  /* specs/discord/guild.json:266:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}' */
                "(description):?s,"
  /* specs/discord/guild.json:267:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}' */
                "(summary):?s,"
  /* specs/discord/guild.json:268:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
                "(bot):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.json:263:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->id,
  /* specs/discord/guild.json:264:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name,
  /* specs/discord/guild.json:265:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
                p->icon,
  /* specs/discord/guild.json:266:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}' */
                &p->description,
  /* specs/discord/guild.json:267:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}' */
                &p->summary,
  /* specs/discord/guild.json:268:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
                discord_user_from_json, &p->bot,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_integration_application_use_default_inject_settings(struct discord_guild_integration_application *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.json:263:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.json:264:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[1] = p->name;

  /* specs/discord/guild.json:265:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
  p->__M.arg_switches[2] = p->icon;

  /* specs/discord/guild.json:266:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[3] = p->description;

  /* specs/discord/guild.json:267:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[4] = p->summary;

  /* specs/discord/guild.json:268:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
  p->__M.arg_switches[5] = p->bot;

}

size_t discord_guild_integration_application_to_json(char *json, size_t len, struct discord_guild_integration_application *p)
{
  size_t r;
  discord_guild_integration_application_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.json:263:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* specs/discord/guild.json:264:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
  /* specs/discord/guild.json:265:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
                "(icon):s,"
  /* specs/discord/guild.json:266:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}' */
                "(description):s,"
  /* specs/discord/guild.json:267:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}' */
                "(summary):s,"
  /* specs/discord/guild.json:268:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
                "(bot):F,"
                "@arg_switches:b",
  /* specs/discord/guild.json:263:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->id,
  /* specs/discord/guild.json:264:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
  /* specs/discord/guild.json:265:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
                p->icon,
  /* specs/discord/guild.json:266:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}' */
                p->description,
  /* specs/discord/guild.json:267:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}' */
                p->summary,
  /* specs/discord/guild.json:268:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
                discord_user_to_json, p->bot,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_integration_application_cleanup_v(void *p) {
  discord_guild_integration_application_cleanup((struct discord_guild_integration_application *)p);
}

void discord_guild_integration_application_init_v(void *p) {
  discord_guild_integration_application_init((struct discord_guild_integration_application *)p);
}

void discord_guild_integration_application_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_integration_application_from_json(json, len, (struct discord_guild_integration_application**)pp);
}

size_t discord_guild_integration_application_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_integration_application_to_json(json, len, (struct discord_guild_integration_application*)p);
}

void discord_guild_integration_application_list_free_v(void **p) {
  discord_guild_integration_application_list_free((struct discord_guild_integration_application**)p);
}

void discord_guild_integration_application_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_integration_application_list_from_json(str, len, (struct discord_guild_integration_application ***)p);
}

size_t discord_guild_integration_application_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_integration_application_list_to_json(str, len, (struct discord_guild_integration_application **)p);
}


void discord_guild_integration_application_cleanup(struct discord_guild_integration_application *d) {
  /* specs/discord/guild.json:263:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->id is a scalar
  /* specs/discord/guild.json:264:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
  /* specs/discord/guild.json:265:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
  // p->icon is a scalar
  /* specs/discord/guild.json:266:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}' */
  if (d->description)
    free(d->description);
  /* specs/discord/guild.json:267:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}' */
  if (d->summary)
    free(d->summary);
  /* specs/discord/guild.json:268:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
  if (d->bot) {
    discord_user_cleanup(d->bot);
    free(d->bot);
  }
}

void discord_guild_integration_application_init(struct discord_guild_integration_application *p) {
  memset(p, 0, sizeof(struct discord_guild_integration_application));
  /* specs/discord/guild.json:263:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/guild.json:264:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/guild.json:265:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */

  /* specs/discord/guild.json:266:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/guild.json:267:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/guild.json:268:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
  p->bot = malloc(sizeof *p->bot);
  discord_user_init(p->bot);

}
void discord_guild_integration_application_list_free(struct discord_guild_integration_application **p) {
  ntl_free((void**)p, (vfvp)discord_guild_integration_application_cleanup);
}

void discord_guild_integration_application_list_from_json(char *str, size_t len, struct discord_guild_integration_application ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_integration_application);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_integration_application_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_integration_application_list_to_json(char *str, size_t len, struct discord_guild_integration_application **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_integration_application_to_json_v);
}


void discord_guild_ban_from_json(char *json, size_t len, struct discord_guild_ban **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_guild_ban *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.json:278:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[DISCORD_MAX_REASON_LEN]" }}' */
                "(reason):s,"
  /* specs/discord/guild.json:279:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
                "(user):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.json:278:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[DISCORD_MAX_REASON_LEN]" }}' */
                p->reason,
  /* specs/discord/guild.json:279:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
                discord_user_from_json, &p->user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_ban_use_default_inject_settings(struct discord_guild_ban *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.json:278:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[DISCORD_MAX_REASON_LEN]" }}' */
  p->__M.arg_switches[0] = p->reason;

  /* specs/discord/guild.json:279:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  p->__M.arg_switches[1] = p->user;

}

size_t discord_guild_ban_to_json(char *json, size_t len, struct discord_guild_ban *p)
{
  size_t r;
  discord_guild_ban_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.json:278:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[DISCORD_MAX_REASON_LEN]" }}' */
                "(reason):s,"
  /* specs/discord/guild.json:279:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
                "(user):F,"
                "@arg_switches:b",
  /* specs/discord/guild.json:278:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[DISCORD_MAX_REASON_LEN]" }}' */
                p->reason,
  /* specs/discord/guild.json:279:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
                discord_user_to_json, p->user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_ban_cleanup_v(void *p) {
  discord_guild_ban_cleanup((struct discord_guild_ban *)p);
}

void discord_guild_ban_init_v(void *p) {
  discord_guild_ban_init((struct discord_guild_ban *)p);
}

void discord_guild_ban_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_ban_from_json(json, len, (struct discord_guild_ban**)pp);
}

size_t discord_guild_ban_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_ban_to_json(json, len, (struct discord_guild_ban*)p);
}

void discord_guild_ban_list_free_v(void **p) {
  discord_guild_ban_list_free((struct discord_guild_ban**)p);
}

void discord_guild_ban_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_ban_list_from_json(str, len, (struct discord_guild_ban ***)p);
}

size_t discord_guild_ban_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_ban_list_to_json(str, len, (struct discord_guild_ban **)p);
}


void discord_guild_ban_cleanup(struct discord_guild_ban *d) {
  /* specs/discord/guild.json:278:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[DISCORD_MAX_REASON_LEN]" }}' */
  // p->reason is a scalar
  /* specs/discord/guild.json:279:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  if (d->user) {
    discord_user_cleanup(d->user);
    free(d->user);
  }
}

void discord_guild_ban_init(struct discord_guild_ban *p) {
  memset(p, 0, sizeof(struct discord_guild_ban));
  /* specs/discord/guild.json:278:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[DISCORD_MAX_REASON_LEN]" }}' */

  /* specs/discord/guild.json:279:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  p->user = malloc(sizeof *p->user);
  discord_user_init(p->user);

}
void discord_guild_ban_list_free(struct discord_guild_ban **p) {
  ntl_free((void**)p, (vfvp)discord_guild_ban_cleanup);
}

void discord_guild_ban_list_from_json(char *str, size_t len, struct discord_guild_ban ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_ban);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_ban_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_ban_list_to_json(char *str, size_t len, struct discord_guild_ban **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_ban_to_json_v);
}


void discord_guild_welcome_screen_from_json(char *json, size_t len, struct discord_guild_welcome_screen **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_guild_welcome_screen *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.json:289:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
                "(description):?s,"
  /* specs/discord/guild.json:290:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_channel", "dec":"ntl" }, "todo":false }' */
                "(welcome_channels):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.json:289:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
                &p->description,
  /* specs/discord/guild.json:290:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_channel", "dec":"ntl" }, "todo":false }' */
                discord_guild_welcome_screen_channel_list_from_json, &p->welcome_channels,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_welcome_screen_use_default_inject_settings(struct discord_guild_welcome_screen *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.json:289:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  p->__M.arg_switches[0] = p->description;

  /* specs/discord/guild.json:290:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_channel", "dec":"ntl" }, "todo":false }' */
  p->__M.arg_switches[1] = p->welcome_channels;

}

size_t discord_guild_welcome_screen_to_json(char *json, size_t len, struct discord_guild_welcome_screen *p)
{
  size_t r;
  discord_guild_welcome_screen_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.json:289:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
                "(description):s,"
  /* specs/discord/guild.json:290:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_channel", "dec":"ntl" }, "todo":false }' */
                "(welcome_channels):F,"
                "@arg_switches:b",
  /* specs/discord/guild.json:289:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
                p->description,
  /* specs/discord/guild.json:290:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_channel", "dec":"ntl" }, "todo":false }' */
                discord_guild_welcome_screen_channel_list_to_json, p->welcome_channels,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_welcome_screen_cleanup_v(void *p) {
  discord_guild_welcome_screen_cleanup((struct discord_guild_welcome_screen *)p);
}

void discord_guild_welcome_screen_init_v(void *p) {
  discord_guild_welcome_screen_init((struct discord_guild_welcome_screen *)p);
}

void discord_guild_welcome_screen_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_welcome_screen_from_json(json, len, (struct discord_guild_welcome_screen**)pp);
}

size_t discord_guild_welcome_screen_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_welcome_screen_to_json(json, len, (struct discord_guild_welcome_screen*)p);
}

void discord_guild_welcome_screen_list_free_v(void **p) {
  discord_guild_welcome_screen_list_free((struct discord_guild_welcome_screen**)p);
}

void discord_guild_welcome_screen_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_welcome_screen_list_from_json(str, len, (struct discord_guild_welcome_screen ***)p);
}

size_t discord_guild_welcome_screen_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_welcome_screen_list_to_json(str, len, (struct discord_guild_welcome_screen **)p);
}


void discord_guild_welcome_screen_cleanup(struct discord_guild_welcome_screen *d) {
  /* specs/discord/guild.json:289:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  if (d->description)
    free(d->description);
  /* specs/discord/guild.json:290:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_channel", "dec":"ntl" }, "todo":false }' */
  if (d->welcome_channels)
    discord_guild_welcome_screen_channel_list_free(d->welcome_channels);
}

void discord_guild_welcome_screen_init(struct discord_guild_welcome_screen *p) {
  memset(p, 0, sizeof(struct discord_guild_welcome_screen));
  /* specs/discord/guild.json:289:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */

  /* specs/discord/guild.json:290:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_channel", "dec":"ntl" }, "todo":false }' */

}
void discord_guild_welcome_screen_list_free(struct discord_guild_welcome_screen **p) {
  ntl_free((void**)p, (vfvp)discord_guild_welcome_screen_cleanup);
}

void discord_guild_welcome_screen_list_from_json(char *str, size_t len, struct discord_guild_welcome_screen ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_welcome_screen);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_welcome_screen_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_welcome_screen_list_to_json(char *str, size_t len, struct discord_guild_welcome_screen **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_welcome_screen_to_json_v);
}


void discord_guild_welcome_screen_channel_from_json(char *json, size_t len, struct discord_guild_welcome_screen_channel **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_guild_welcome_screen_channel *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.json:300:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(channel_id):F,"
  /* specs/discord/guild.json:301:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
                "(description):?s,"
  /* specs/discord/guild.json:302:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(emoji_id):F,"
  /* specs/discord/guild.json:303:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}' */
                "(emoji_name):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.json:300:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/guild.json:301:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
                &p->description,
  /* specs/discord/guild.json:302:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->emoji_id,
  /* specs/discord/guild.json:303:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}' */
                &p->emoji_name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_welcome_screen_channel_use_default_inject_settings(struct discord_guild_welcome_screen_channel *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.json:300:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[0] = &p->channel_id;

  /* specs/discord/guild.json:301:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[1] = p->description;

  /* specs/discord/guild.json:302:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[2] = &p->emoji_id;

  /* specs/discord/guild.json:303:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[3] = p->emoji_name;

}

size_t discord_guild_welcome_screen_channel_to_json(char *json, size_t len, struct discord_guild_welcome_screen_channel *p)
{
  size_t r;
  discord_guild_welcome_screen_channel_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.json:300:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(channel_id):|F|,"
  /* specs/discord/guild.json:301:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
                "(description):s,"
  /* specs/discord/guild.json:302:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(emoji_id):|F|,"
  /* specs/discord/guild.json:303:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}' */
                "(emoji_name):s,"
                "@arg_switches:b",
  /* specs/discord/guild.json:300:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/guild.json:301:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
                p->description,
  /* specs/discord/guild.json:302:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->emoji_id,
  /* specs/discord/guild.json:303:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}' */
                p->emoji_name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_welcome_screen_channel_cleanup_v(void *p) {
  discord_guild_welcome_screen_channel_cleanup((struct discord_guild_welcome_screen_channel *)p);
}

void discord_guild_welcome_screen_channel_init_v(void *p) {
  discord_guild_welcome_screen_channel_init((struct discord_guild_welcome_screen_channel *)p);
}

void discord_guild_welcome_screen_channel_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_welcome_screen_channel_from_json(json, len, (struct discord_guild_welcome_screen_channel**)pp);
}

size_t discord_guild_welcome_screen_channel_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_welcome_screen_channel_to_json(json, len, (struct discord_guild_welcome_screen_channel*)p);
}

void discord_guild_welcome_screen_channel_list_free_v(void **p) {
  discord_guild_welcome_screen_channel_list_free((struct discord_guild_welcome_screen_channel**)p);
}

void discord_guild_welcome_screen_channel_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_welcome_screen_channel_list_from_json(str, len, (struct discord_guild_welcome_screen_channel ***)p);
}

size_t discord_guild_welcome_screen_channel_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_welcome_screen_channel_list_to_json(str, len, (struct discord_guild_welcome_screen_channel **)p);
}


void discord_guild_welcome_screen_channel_cleanup(struct discord_guild_welcome_screen_channel *d) {
  /* specs/discord/guild.json:300:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->channel_id is a scalar
  /* specs/discord/guild.json:301:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
  if (d->description)
    free(d->description);
  /* specs/discord/guild.json:302:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->emoji_id is a scalar
  /* specs/discord/guild.json:303:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->emoji_name)
    free(d->emoji_name);
}

void discord_guild_welcome_screen_channel_init(struct discord_guild_welcome_screen_channel *p) {
  memset(p, 0, sizeof(struct discord_guild_welcome_screen_channel));
  /* specs/discord/guild.json:300:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/guild.json:301:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/guild.json:302:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/guild.json:303:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}' */

}
void discord_guild_welcome_screen_channel_list_free(struct discord_guild_welcome_screen_channel **p) {
  ntl_free((void**)p, (vfvp)discord_guild_welcome_screen_channel_cleanup);
}

void discord_guild_welcome_screen_channel_list_from_json(char *str, size_t len, struct discord_guild_welcome_screen_channel ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_welcome_screen_channel);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_welcome_screen_channel_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_welcome_screen_channel_list_to_json(char *str, size_t len, struct discord_guild_welcome_screen_channel **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_welcome_screen_channel_to_json_v);
}

