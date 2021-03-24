/* This file is generated from specs/user.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/user#user-object
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


enum discord_user_premium_types {
  DISCORD_USER_NITRO_CLASSIC = 0,
  DISCORD_USER_NITRO = 1,
};

/* Title: User Structure */
/* This is defined at specs/user.json:42:18 */
struct discord_user {
  /* specs/user.json:45:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
  u64_snowflake_t id;

  /* specs/user.json:46:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
  char username[MAX_USERNAME_LEN];

  /* specs/user.json:47:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
  char discriminator[MAX_DISCRIMINATOR_LEN];

  /* specs/user.json:48:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
  char avatar[MAX_SHA256_LEN];

  /* specs/user.json:49:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
  bool bot;

  /* specs/user.json:50:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
  bool System;

  /* specs/user.json:51:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
  bool mfa_enabled;

  /* specs/user.json:52:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
  char locale[MAX_LOCALE_LEN];

  /* specs/user.json:53:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  bool verified;

  /* specs/user.json:54:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
  char email[MAX_EMAIL_LEN];

  /* specs/user.json:55:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
  enum discord_user_flags flags;

  /* specs/user.json:56:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}'
  */
  enum discord_user_premium_types premium_type;

  /* specs/user.json:57:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
  enum discord_user_flags public_flags;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[13];
    void *record_defined[13];
    void *record_null[13];
  } __M; // metadata
};
extern void discord_user_cleanup_v(void *p);
extern void discord_user_cleanup(struct discord_user *p);
extern void discord_user_init_v(void *p);
extern void discord_user_init(struct discord_user *p);
extern struct discord_user * discord_user_alloc();
extern void discord_user_free_v(void *p);
extern void discord_user_free(struct discord_user *p);
extern void discord_user_from_json_v(char *json, size_t len, void *p);
extern void discord_user_from_json(char *json, size_t len, struct discord_user *p);
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

/* Title: Connection Structure */
/* https://discord.com/developers/docs/resources/user#connection-object-connection-structure */
/* This is defined at specs/user.json:74:18 */
struct discord_connection {
  /* specs/user.json:77:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *id; // @todo fixed size limit

  /* specs/user.json:78:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  char *name;

  /* specs/user.json:79:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
  char *type;

  /* specs/user.json:80:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
  bool revoked;

  /* specs/user.json:81:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration", "dec":"ntl"}, "todo":true}'
  */
  //@todo integrations (null);

  /* specs/user.json:82:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  bool verified;

  /* specs/user.json:83:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
  bool friend_sync;

  /* specs/user.json:84:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
  bool show_activity;

  /* specs/user.json:85:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types" }}'
  */
  enum discord_user_connection_visibility_types visibility;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
};
extern void discord_connection_cleanup_v(void *p);
extern void discord_connection_cleanup(struct discord_connection *p);
extern void discord_connection_init_v(void *p);
extern void discord_connection_init(struct discord_connection *p);
extern struct discord_connection * discord_connection_alloc();
extern void discord_connection_free_v(void *p);
extern void discord_connection_free(struct discord_connection *p);
extern void discord_connection_from_json_v(char *json, size_t len, void *p);
extern void discord_connection_from_json(char *json, size_t len, struct discord_connection *p);
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
