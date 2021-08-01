/* This file is generated from specs/discord/user.json, Please don't edit it. */
/**
 * @file specs-code/discord/user.h
 * @see https://discord.com/developers/docs/resources/user
 */



enum discord_user_flags {
  DISCORD_USER_DISCORD_EMPLOYEE = 1, // 1 << 0
  DISCORD_USER_PARTNERED_SERVER_OWNER = 2, // 1 << 2
  DISCORD_USER_HYPESQUAD_EVENTS = 4, // 1 << 3
  DISCORD_USER_BUG_HUNTER_LEVEL_1 = 8, // 1 << 4
  DISCORD_USER_HOUSE_BRAVERY = 32, // 1 << 6
  DISCORD_USER_HOUSE_BRILLIANCE = 64, // 1 << 7
  DISCORD_USER_HOUSE_BALANCE = 128, // 1 << 8
  DISCORD_USER_EARLY_SUPPORTER = 256, // 1 << 9
  DISCORD_USER_TEAM_USER = 512, // 1 << 10
  DISCORD_USER_SYSTEM = 4096, // 1 << 12
  DISCORD_USER_BUG_HUNTER_LEVEL_2 = 16384, // 1 << 14
  DISCORD_USER_VERIFIED_BOT = 65536, // 1 << 16
  DISCORD_USER_EARLY_VERIFIED_BOT_DEVELOPER = 131072, // 1 << 17
};
extern char* discord_user_flags_to_string(enum discord_user_flags);
extern enum discord_user_flags discord_user_flags_from_string(char*);
extern bool discord_user_flags_has(enum discord_user_flags, char*);


enum discord_user_premium_types {
  DISCORD_USER_NITRO_CLASSIC = 0,
  DISCORD_USER_NITRO = 1,
};
extern char* discord_user_premium_types_to_string(enum discord_user_premium_types);
extern enum discord_user_premium_types discord_user_premium_types_from_string(char*);
extern bool discord_user_premium_types_has(enum discord_user_premium_types, char*);

// User Structure
// defined at specs/discord/user.json:42:28
/**
 * - Initializer:
 *   - <tt>discord_user_init(struct discord_user*)</tt>
 * - Cleanup:
 *   - <tt>discord_user_cleanup(struct discord_user*)</tt>
 *   - <tt>discord_user_list_free(struct discord_user**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_user_from_json(char *rbuf, size_t len, struct discord_user**)</tt>
 *   - <tt>discord_user_list_from_json(char *rbuf, size_t len, struct discord_user***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_user_to_json(char *wbuf, size_t len, struct discord_user *p)</tt>
 *   - <tt>discord_user_list_to_json(char *wbuf, size_t len, struct discord_user**)</tt>
 */
struct discord_user {
  /* specs/discord/user.json:45:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  u64_snowflake_t id;

  /* specs/discord/user.json:46:24
     '{ "name": "username", "type":{ "base":"char", "dec":"[DISCORD_MAX_USERNAME_LEN]"}}' */
  char username[DISCORD_MAX_USERNAME_LEN];

  /* specs/discord/user.json:47:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[DISCORD_MAX_DISCRIMINATOR_LEN]" }}' */
  char discriminator[DISCORD_MAX_DISCRIMINATOR_LEN];

  /* specs/discord/user.json:48:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}' */
  char avatar[MAX_SHA256_LEN];

  /* specs/discord/user.json:49:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
  bool bot;

  /* specs/discord/user.json:50:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
  bool System;

  /* specs/discord/user.json:51:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
  bool mfa_enabled;

  /* specs/discord/user.json:52:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}' */
  char locale[MAX_LOCALE_LEN];

  /* specs/discord/user.json:53:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  bool verified;

  /* specs/discord/user.json:54:24
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}' */
  char email[MAX_EMAIL_LEN];

  /* specs/discord/user.json:55:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  enum discord_user_flags flags;

  /* specs/discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
  enum discord_user_premium_types premium_type;

  /* specs/discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  enum discord_user_flags public_flags;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[13];
    void *record_defined[13];
    void *record_null[13];
  } __M; // metadata
/// @endcond
};
extern void discord_user_cleanup_v(void *p);
extern void discord_user_cleanup(struct discord_user *p);
extern void discord_user_init_v(void *p);
extern void discord_user_init(struct discord_user *p);
extern void discord_user_from_json_v(char *json, size_t len, void *pp);
extern void discord_user_from_json(char *json, size_t len, struct discord_user **pp);
extern size_t discord_user_to_json_v(char *json, size_t len, void *p);
extern size_t discord_user_to_json(char *json, size_t len, struct discord_user *p);
extern size_t discord_user_to_query_v(char *json, size_t len, void *p);
extern size_t discord_user_to_query(char *json, size_t len, struct discord_user *p);
extern void discord_user_list_free_v(void **p);
extern void discord_user_list_free(struct discord_user **p);
extern void discord_user_list_from_json_v(char *str, size_t len, void *p);
extern void discord_user_list_from_json(char *str, size_t len, struct discord_user ***p);
extern size_t discord_user_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_user_list_to_json(char *str, size_t len, struct discord_user **p);


enum discord_user_connection_visibility_types {
  DISCORD_USER_CONNECTION_NONE = 0,
  DISCORD_USER_CONNECTION_EVERYONE = 1,
};
extern char* discord_user_connection_visibility_types_to_string(enum discord_user_connection_visibility_types);
extern enum discord_user_connection_visibility_types discord_user_connection_visibility_types_from_string(char*);
extern bool discord_user_connection_visibility_types_has(enum discord_user_connection_visibility_types, char*);

// Connection Structure
// defined at specs/discord/user.json:74:28
/**
 * @see https://discord.com/developers/docs/resources/user#connection-object-connection-structure
 * - Initializer:
 *   - <tt>discord_connection_init(struct discord_connection*)</tt>
 * - Cleanup:
 *   - <tt>discord_connection_cleanup(struct discord_connection*)</tt>
 *   - <tt>discord_connection_list_free(struct discord_connection**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_connection_from_json(char *rbuf, size_t len, struct discord_connection**)</tt>
 *   - <tt>discord_connection_list_from_json(char *rbuf, size_t len, struct discord_connection***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_connection_to_json(char *wbuf, size_t len, struct discord_connection *p)</tt>
 *   - <tt>discord_connection_list_to_json(char *wbuf, size_t len, struct discord_connection**)</tt>
 */
struct discord_connection {
  /* specs/discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  char *id; ///< @todo fixed size limit

  /* specs/discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  char *type;

  /* specs/discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
  bool revoked;

  /* specs/discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration", "dec":"ntl"}}' */
  struct discord_guild_integration **integrations;

  /* specs/discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  bool verified;

  /* specs/discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
  bool friend_sync;

  /* specs/discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
  bool show_activity;

  /* specs/discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types" }}' */
  enum discord_user_connection_visibility_types visibility;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
/// @endcond
};
extern void discord_connection_cleanup_v(void *p);
extern void discord_connection_cleanup(struct discord_connection *p);
extern void discord_connection_init_v(void *p);
extern void discord_connection_init(struct discord_connection *p);
extern void discord_connection_from_json_v(char *json, size_t len, void *pp);
extern void discord_connection_from_json(char *json, size_t len, struct discord_connection **pp);
extern size_t discord_connection_to_json_v(char *json, size_t len, void *p);
extern size_t discord_connection_to_json(char *json, size_t len, struct discord_connection *p);
extern size_t discord_connection_to_query_v(char *json, size_t len, void *p);
extern size_t discord_connection_to_query(char *json, size_t len, struct discord_connection *p);
extern void discord_connection_list_free_v(void **p);
extern void discord_connection_list_free(struct discord_connection **p);
extern void discord_connection_list_from_json_v(char *str, size_t len, void *p);
extern void discord_connection_list_from_json(char *str, size_t len, struct discord_connection ***p);
extern size_t discord_connection_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_connection_list_to_json(char *str, size_t len, struct discord_connection **p);
