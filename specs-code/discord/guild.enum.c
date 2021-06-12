/* This file is generated from specs/discord/guild.enum.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/


enum discord_guild_default_message_notification_level discord_guild_default_message_notification_level_from_string(char *s){
  if(strcasecmp("ALL_MESSAGES", s) == 0) return DISCORD_GUILD_ALL_MESSAGES;
  if(strcasecmp("ONLY_MENTIONS", s) == 0) return DISCORD_GUILD_ONLY_MENTIONS;
  abort();
}
char* discord_guild_default_message_notification_level_to_string(enum discord_guild_default_message_notification_level v){
  if (v == DISCORD_GUILD_ALL_MESSAGES) return "ALL_MESSAGES";
  if (v == DISCORD_GUILD_ONLY_MENTIONS) return "ONLY_MENTIONS";

  return (void*)0;
}
bool discord_guild_default_message_notification_level_has(enum discord_guild_default_message_notification_level v, char *s) {
  enum discord_guild_default_message_notification_level v1 = discord_guild_default_message_notification_level_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}


enum discord_guild_explicit_content_filter_level discord_guild_explicit_content_filter_level_from_string(char *s){
  if(strcasecmp("DISABLED", s) == 0) return DISCORD_GUILD_DISABLED;
  if(strcasecmp("MEMBERS_WITHOUT_ROLES", s) == 0) return DISCORD_GUILD_MEMBERS_WITHOUT_ROLES;
  if(strcasecmp("ALL_MEMBERS", s) == 0) return DISCORD_GUILD_ALL_MEMBERS;
  abort();
}
char* discord_guild_explicit_content_filter_level_to_string(enum discord_guild_explicit_content_filter_level v){
  if (v == DISCORD_GUILD_DISABLED) return "DISABLED";
  if (v == DISCORD_GUILD_MEMBERS_WITHOUT_ROLES) return "MEMBERS_WITHOUT_ROLES";
  if (v == DISCORD_GUILD_ALL_MEMBERS) return "ALL_MEMBERS";

  return (void*)0;
}
bool discord_guild_explicit_content_filter_level_has(enum discord_guild_explicit_content_filter_level v, char *s) {
  enum discord_guild_explicit_content_filter_level v1 = discord_guild_explicit_content_filter_level_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}


enum discord_guild_mfa_level discord_guild_mfa_level_from_string(char *s){
  if(strcasecmp("DISCORD_MFA_NONE", s) == 0) return DISCORD_GUILD_DISCORD_MFA_NONE;
  if(strcasecmp("ELEVATED", s) == 0) return DISCORD_GUILD_ELEVATED;
  abort();
}
char* discord_guild_mfa_level_to_string(enum discord_guild_mfa_level v){
  if (v == DISCORD_GUILD_DISCORD_MFA_NONE) return "DISCORD_MFA_NONE";
  if (v == DISCORD_GUILD_ELEVATED) return "ELEVATED";

  return (void*)0;
}
bool discord_guild_mfa_level_has(enum discord_guild_mfa_level v, char *s) {
  enum discord_guild_mfa_level v1 = discord_guild_mfa_level_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}


enum discord_guild_verification_level discord_guild_verification_level_from_string(char *s){
  if(strcasecmp("DISCORD_VL_NONE", s) == 0) return DISCORD_GUILD_DISCORD_VL_NONE;
  if(strcasecmp("LOW", s) == 0) return DISCORD_GUILD_LOW;
  if(strcasecmp("MEDIUM", s) == 0) return DISCORD_GUILD_MEDIUM;
  if(strcasecmp("HIGH", s) == 0) return DISCORD_GUILD_HIGH;
  if(strcasecmp("VERY_HIGH", s) == 0) return DISCORD_GUILD_VERY_HIGH;
  abort();
}
char* discord_guild_verification_level_to_string(enum discord_guild_verification_level v){
  if (v == DISCORD_GUILD_DISCORD_VL_NONE) return "DISCORD_VL_NONE";
  if (v == DISCORD_GUILD_LOW) return "LOW";
  if (v == DISCORD_GUILD_MEDIUM) return "MEDIUM";
  if (v == DISCORD_GUILD_HIGH) return "HIGH";
  if (v == DISCORD_GUILD_VERY_HIGH) return "VERY_HIGH";

  return (void*)0;
}
bool discord_guild_verification_level_has(enum discord_guild_verification_level v, char *s) {
  enum discord_guild_verification_level v1 = discord_guild_verification_level_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}


enum discord_guild_premium_tier discord_guild_premium_tier_from_string(char *s){
  if(strcasecmp("DISCORD_PREMIUM_NONE", s) == 0) return DISCORD_GUILD_DISCORD_PREMIUM_NONE;
  if(strcasecmp("TIER_1", s) == 0) return DISCORD_GUILD_TIER_1;
  if(strcasecmp("TIER_2", s) == 0) return DISCORD_GUILD_TIER_2;
  if(strcasecmp("TIER_3", s) == 0) return DISCORD_GUILD_TIER_3;
  abort();
}
char* discord_guild_premium_tier_to_string(enum discord_guild_premium_tier v){
  if (v == DISCORD_GUILD_DISCORD_PREMIUM_NONE) return "DISCORD_PREMIUM_NONE";
  if (v == DISCORD_GUILD_TIER_1) return "TIER_1";
  if (v == DISCORD_GUILD_TIER_2) return "TIER_2";
  if (v == DISCORD_GUILD_TIER_3) return "TIER_3";

  return (void*)0;
}
bool discord_guild_premium_tier_has(enum discord_guild_premium_tier v, char *s) {
  enum discord_guild_premium_tier v1 = discord_guild_premium_tier_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}


enum discord_guild_system_channel_flags discord_guild_system_channel_flags_from_string(char *s){
  if(strcasecmp("SUPRESS_JOIN_NOTIFICATIONS", s) == 0) return DISCORD_GUILD_SUPRESS_JOIN_NOTIFICATIONS;
  if(strcasecmp("SUPRESS_PREMIUM_SUBSCRIPTIONS", s) == 0) return DISCORD_GUILD_SUPRESS_PREMIUM_SUBSCRIPTIONS;
  abort();
}
char* discord_guild_system_channel_flags_to_string(enum discord_guild_system_channel_flags v){
  if (v == DISCORD_GUILD_SUPRESS_JOIN_NOTIFICATIONS) return "SUPRESS_JOIN_NOTIFICATIONS";
  if (v == DISCORD_GUILD_SUPRESS_PREMIUM_SUBSCRIPTIONS) return "SUPRESS_PREMIUM_SUBSCRIPTIONS";

  return (void*)0;
}
bool discord_guild_system_channel_flags_has(enum discord_guild_system_channel_flags v, char *s) {
  enum discord_guild_system_channel_flags v1 = discord_guild_system_channel_flags_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}


enum discord_guild_guild_features discord_guild_guild_features_from_string(char *s){
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
  abort();
}
char* discord_guild_guild_features_to_string(enum discord_guild_guild_features v){
  if (v == DISCORD_GUILD_INVITE_SPLASH) return "INVITE_SPLASH";
  if (v == DISCORD_GUILD_VIP_REGIONS) return "VIP_REGIONS";
  if (v == DISCORD_GUILD_VANITY_URL) return "VANITY_URL";
  if (v == DISCORD_GUILD_VERIFIED) return "VERIFIED";
  if (v == DISCORD_GUILD_PARTNERED) return "PARTNERED";
  if (v == DISCORD_GUILD_COMMUNITY) return "COMMUNITY";
  if (v == DISCORD_GUILD_COMMERCE) return "COMMERCE";
  if (v == DISCORD_GUILD_NEWS) return "NEWS";
  if (v == DISCORD_GUILD_DISCOVERABLE) return "DISCOVERABLE";
  if (v == DISCORD_GUILD_FEATURABLE) return "FEATURABLE";
  if (v == DISCORD_GUILD_ANIMATED_ICON) return "ANIMATED_ICON";
  if (v == DISCORD_GUILD_BANNER) return "BANNER";
  if (v == DISCORD_GUILD_WELCOME_SCREEN_ENABLED) return "WELCOME_SCREEN_ENABLED";
  if (v == DISCORD_GUILD_MEMBER_VERIFICATION_GATE_ENABLED) return "MEMBER_VERIFICATION_GATE_ENABLED";
  if (v == DISCORD_GUILD_PREVIEW_ENABLED) return "PREVIEW_ENABLED";

  return (void*)0;
}
bool discord_guild_guild_features_has(enum discord_guild_guild_features v, char *s) {
  enum discord_guild_guild_features v1 = discord_guild_guild_features_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_guild_unavailable_from_json(char *json, size_t len, struct discord_guild_unavailable *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):F,"
  /* specs/discord/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
                "(unavailable):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->id,
  /* specs/discord/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
                &p->unavailable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_unavailable_use_default_inject_settings(struct discord_guild_unavailable *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
  p->__M.arg_switches[1] = &p->unavailable;

}

size_t discord_guild_unavailable_to_json(char *json, size_t len, struct discord_guild_unavailable *p)
{
  size_t r;
  discord_guild_unavailable_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):|F|,"
  /* specs/discord/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
                "(unavailable):b,"
                "@arg_switches:b",
  /* specs/discord/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->id,
  /* specs/discord/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
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

void discord_guild_unavailable_free_v(void *p) {
 discord_guild_unavailable_free((struct discord_guild_unavailable *)p);
};

void discord_guild_unavailable_from_json_v(char *json, size_t len, void *p) {
 discord_guild_unavailable_from_json(json, len, (struct discord_guild_unavailable*)p);
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
  /* specs/discord/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->id is a scalar
  /* specs/discord/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
  //p->unavailable is a scalar
}

void discord_guild_unavailable_init(struct discord_guild_unavailable *p) {
  memset(p, 0, sizeof(struct discord_guild_unavailable));
  /* specs/discord/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/discord/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */

}
struct discord_guild_unavailable* discord_guild_unavailable_alloc() {
  struct discord_guild_unavailable *p= (struct discord_guild_unavailable*)malloc(sizeof(struct discord_guild_unavailable));
  discord_guild_unavailable_init(p);
  return p;
}

void discord_guild_unavailable_free(struct discord_guild_unavailable *p) {
  discord_guild_unavailable_cleanup(p);
  free(p);
}

void discord_guild_unavailable_list_free(struct discord_guild_unavailable **p) {
  ntl_free((void**)p, (vfvp)discord_guild_unavailable_cleanup);
}

void discord_guild_unavailable_list_from_json(char *str, size_t len, struct discord_guild_unavailable ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_unavailable);
  d.init_elem = discord_guild_unavailable_init_v;
  d.elem_from_buf = discord_guild_unavailable_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_unavailable_list_to_json(char *str, size_t len, struct discord_guild_unavailable **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_unavailable_to_json_v);
}


void discord_guild_preview_from_json(char *json, size_t len, struct discord_guild_preview *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):F,"
  /* specs/discord/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                "(name):s,"
  /* specs/discord/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(icon):?s,"
  /* specs/discord/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(splash):?s,"
  /* specs/discord/guild.enum.json:106:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(discovery_splash):?s,"
  /* specs/discord/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
                "(emojis):F,"
  /* specs/discord/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  /* specs/discord/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
                "(approximate_member_count):d,"
  /* specs/discord/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
                "(approximate_presence_count):d,"
  /* specs/discord/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                "(description):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->id,
  /* specs/discord/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                p->name,
  /* specs/discord/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                &p->icon,
  /* specs/discord/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                &p->splash,
  /* specs/discord/guild.enum.json:106:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                &p->discovery_splash,
  /* specs/discord/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
                discord_emoji_list_from_json, &p->emojis,
  /* specs/discord/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  /* specs/discord/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
                &p->approximate_member_count,
  /* specs/discord/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
                &p->approximate_presence_count,
  /* specs/discord/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_preview_use_default_inject_settings(struct discord_guild_preview *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/discord/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  p->__M.arg_switches[2] = p->icon;

  /* specs/discord/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  p->__M.arg_switches[3] = p->splash;

  /* specs/discord/guild.enum.json:106:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  p->__M.arg_switches[4] = p->discovery_splash;

  /* specs/discord/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
  p->__M.arg_switches[5] = p->emojis;

  /* specs/discord/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */

  /* specs/discord/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
  p->__M.arg_switches[7] = &p->approximate_member_count;

  /* specs/discord/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
  p->__M.arg_switches[8] = &p->approximate_presence_count;

  /* specs/discord/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
  p->__M.arg_switches[9] = p->description;

}

size_t discord_guild_preview_to_json(char *json, size_t len, struct discord_guild_preview *p)
{
  size_t r;
  discord_guild_preview_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):|F|,"
  /* specs/discord/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                "(name):s,"
  /* specs/discord/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(icon):s,"
  /* specs/discord/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(splash):s,"
  /* specs/discord/guild.enum.json:106:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(discovery_splash):s,"
  /* specs/discord/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
                "(emojis):F,"
  /* specs/discord/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  /* specs/discord/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
                "(approximate_member_count):d,"
  /* specs/discord/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
                "(approximate_presence_count):d,"
  /* specs/discord/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                "(description):s,"
                "@arg_switches:b",
  /* specs/discord/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->id,
  /* specs/discord/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                p->name,
  /* specs/discord/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                p->icon,
  /* specs/discord/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                p->splash,
  /* specs/discord/guild.enum.json:106:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                p->discovery_splash,
  /* specs/discord/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
                discord_emoji_list_to_json, p->emojis,
  /* specs/discord/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  /* specs/discord/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
                &p->approximate_member_count,
  /* specs/discord/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
                &p->approximate_presence_count,
  /* specs/discord/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
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

void discord_guild_preview_free_v(void *p) {
 discord_guild_preview_free((struct discord_guild_preview *)p);
};

void discord_guild_preview_from_json_v(char *json, size_t len, void *p) {
 discord_guild_preview_from_json(json, len, (struct discord_guild_preview*)p);
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
  /* specs/discord/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->id is a scalar
  /* specs/discord/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  //p->name is a scalar
  /* specs/discord/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  if (d->icon)
    free(d->icon);
  /* specs/discord/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  if (d->splash)
    free(d->splash);
  /* specs/discord/guild.enum.json:106:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  if (d->discovery_splash)
    free(d->discovery_splash);
  /* specs/discord/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
  if (d->emojis)
    discord_emoji_list_free(d->emojis);
  /* specs/discord/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  //@todo p->(null)
  /* specs/discord/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
  //p->approximate_member_count is a scalar
  /* specs/discord/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
  //p->approximate_presence_count is a scalar
  /* specs/discord/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
  //p->description is a scalar
}

void discord_guild_preview_init(struct discord_guild_preview *p) {
  memset(p, 0, sizeof(struct discord_guild_preview));
  /* specs/discord/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/discord/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */

  /* specs/discord/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */

  /* specs/discord/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */

  /* specs/discord/guild.enum.json:106:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */

  /* specs/discord/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */

  /* specs/discord/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */

  /* specs/discord/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */

  /* specs/discord/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */

  /* specs/discord/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */

}
struct discord_guild_preview* discord_guild_preview_alloc() {
  struct discord_guild_preview *p= (struct discord_guild_preview*)malloc(sizeof(struct discord_guild_preview));
  discord_guild_preview_init(p);
  return p;
}

void discord_guild_preview_free(struct discord_guild_preview *p) {
  discord_guild_preview_cleanup(p);
  free(p);
}

void discord_guild_preview_list_free(struct discord_guild_preview **p) {
  ntl_free((void**)p, (vfvp)discord_guild_preview_cleanup);
}

void discord_guild_preview_list_from_json(char *str, size_t len, struct discord_guild_preview ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_preview);
  d.init_elem = discord_guild_preview_init_v;
  d.elem_from_buf = discord_guild_preview_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_preview_list_to_json(char *str, size_t len, struct discord_guild_preview **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_preview_to_json_v);
}


void discord_guild_widget_from_json(char *json, size_t len, struct discord_guild_widget *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
                "(enabled):b,"
  /* specs/discord/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
                "(channel_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
                &p->enabled,
  /* specs/discord/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
                orka_strtoull, &p->channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_widget_use_default_inject_settings(struct discord_guild_widget *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
  p->__M.arg_switches[0] = &p->enabled;

  /* specs/discord/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
  p->__M.arg_switches[1] = &p->channel_id;

}

size_t discord_guild_widget_to_json(char *json, size_t len, struct discord_guild_widget *p)
{
  size_t r;
  discord_guild_widget_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
                "(enabled):b,"
  /* specs/discord/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
                "(channel_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
                &p->enabled,
  /* specs/discord/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
                orka_ulltostr, &p->channel_id,
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

void discord_guild_widget_free_v(void *p) {
 discord_guild_widget_free((struct discord_guild_widget *)p);
};

void discord_guild_widget_from_json_v(char *json, size_t len, void *p) {
 discord_guild_widget_from_json(json, len, (struct discord_guild_widget*)p);
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
  /* specs/discord/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
  //p->enabled is a scalar
  /* specs/discord/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
  //p->channel_id is a scalar
}

void discord_guild_widget_init(struct discord_guild_widget *p) {
  memset(p, 0, sizeof(struct discord_guild_widget));
  /* specs/discord/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */

  /* specs/discord/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */

}
struct discord_guild_widget* discord_guild_widget_alloc() {
  struct discord_guild_widget *p= (struct discord_guild_widget*)malloc(sizeof(struct discord_guild_widget));
  discord_guild_widget_init(p);
  return p;
}

void discord_guild_widget_free(struct discord_guild_widget *p) {
  discord_guild_widget_cleanup(p);
  free(p);
}

void discord_guild_widget_list_free(struct discord_guild_widget **p) {
  ntl_free((void**)p, (vfvp)discord_guild_widget_cleanup);
}

void discord_guild_widget_list_from_json(char *str, size_t len, struct discord_guild_widget ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_widget);
  d.init_elem = discord_guild_widget_init_v;
  d.elem_from_buf = discord_guild_widget_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_widget_list_to_json(char *str, size_t len, struct discord_guild_widget **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_widget_to_json_v);
}

