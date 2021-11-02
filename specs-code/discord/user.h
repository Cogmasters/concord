/* This file is generated from specs/discord/user.json, Please don't edit it. */
/**
 * @file specs-code/discord/user.h
 * @see https://discord.com/developers/docs/resources/user
 */



/* User Flags */
/* defined at specs/discord/user.json:6:7 */
/**
 * @see https://discord.com/developers/docs/resources/user#user-object-user-flags
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_user_flags_print(enum discord_user_flags code)`
 *   * :code:`enum discord_user_flags discord_user_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_user_flags {
  DISCORD_USER_DISCORD_EMPLOYEE = 1, /**< 1 << 0 */
  DISCORD_USER_PARTNERED_SERVER_OWNER = 2, /**< 1 << 2 */
  DISCORD_USER_HYPESQUAD_EVENTS = 4, /**< 1 << 3 */
  DISCORD_USER_BUG_HUNTER_LEVEL_1 = 8, /**< 1 << 4 */
  DISCORD_USER_HOUSE_BRAVERY = 32, /**< 1 << 6 */
  DISCORD_USER_HOUSE_BRILLIANCE = 64, /**< 1 << 7 */
  DISCORD_USER_HOUSE_BALANCE = 128, /**< 1 << 8 */
  DISCORD_USER_EARLY_SUPPORTER = 256, /**< 1 << 9 */
  DISCORD_USER_TEAM_USER = 512, /**< 1 << 10 */
  DISCORD_USER_SYSTEM = 4096, /**< 1 << 12 */
  DISCORD_USER_BUG_HUNTER_LEVEL_2 = 16384, /**< 1 << 14 */
  DISCORD_USER_VERIFIED_BOT = 65536, /**< 1 << 16 */
  DISCORD_USER_EARLY_VERIFIED_BOT_DEVELOPER = 131072, /**< 1 << 17 */
};
extern char* discord_user_flags_print(enum discord_user_flags);
extern enum discord_user_flags discord_user_flags_eval(char*);
extern void discord_user_flags_list_free_v(void **p);
extern void discord_user_flags_list_free(enum discord_user_flags **p);
extern void discord_user_flags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_user_flags_list_from_json(char *str, size_t len, enum discord_user_flags ***p);
extern size_t discord_user_flags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_user_flags_list_to_json(char *str, size_t len, enum discord_user_flags **p);


/* Premium Types */
/* defined at specs/discord/user.json:28:7 */
/**
 * @see https://discord.com/developers/docs/resources/user#user-object-premium-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_user_premium_types_print(enum discord_user_premium_types code)`
 *   * :code:`enum discord_user_premium_types discord_user_premium_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_user_premium_types {
  DISCORD_USER_NITRO_CLASSIC = 0,
  DISCORD_USER_NITRO = 1,
};
extern char* discord_user_premium_types_print(enum discord_user_premium_types);
extern enum discord_user_premium_types discord_user_premium_types_eval(char*);
extern void discord_user_premium_types_list_free_v(void **p);
extern void discord_user_premium_types_list_free(enum discord_user_premium_types **p);
extern void discord_user_premium_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_user_premium_types_list_from_json(char *str, size_t len, enum discord_user_premium_types ***p);
extern size_t discord_user_premium_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_user_premium_types_list_to_json(char *str, size_t len, enum discord_user_premium_types **p);

/* User Structure */
/* defined at specs/discord/user.json:41:28 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_user_init(struct discord_user *)`
 *   * Cleanup:

 *     * :code:`void discord_user_cleanup(struct discord_user *)`
 *     * :code:`void discord_user_list_free(struct discord_user **)`
 *   * JSON Decoder:

 *     * :code:`void discord_user_from_json(char *rbuf, size_t len, struct discord_user **)`
 *     * :code:`void discord_user_list_from_json(char *rbuf, size_t len, struct discord_user ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_user_to_json(char *wbuf, size_t len, struct discord_user *)`
 *     * :code:`void discord_user_list_to_json(char *wbuf, size_t len, struct discord_user **)`
 * @endverbatim
 */
struct discord_user {
  /* specs/discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  u64_snowflake_t id;

  /* specs/discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
  char *username;

  /* specs/discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
  char *discriminator;

  /* specs/discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
  char avatar[ORCA_LIMITS_SHA256];

  /* specs/discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
  bool bot;

  /* specs/discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
  bool System;

  /* specs/discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
  bool mfa_enabled;

  /* specs/discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"[ORCA_LIMITS_LOCALE]" }}' */
  char locale[ORCA_LIMITS_LOCALE];

  /* specs/discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  bool verified;

  /* specs/discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"[ORCA_LIMITS_EMAIL]" }}' */
  char email[ORCA_LIMITS_EMAIL];

  /* specs/discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  enum discord_user_flags flags;

  /* specs/discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
  char banner[ORCA_LIMITS_SHA256];

  /* specs/discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
  enum discord_user_premium_types premium_type;

  /* specs/discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  enum discord_user_flags public_flags;

};
extern void discord_user_cleanup_v(void *p);
extern void discord_user_cleanup(struct discord_user *p);
extern void discord_user_init_v(void *p);
extern void discord_user_init(struct discord_user *p);
extern void discord_user_from_json_v(char *json, size_t len, void *pp);
extern void discord_user_from_json(char *json, size_t len, struct discord_user **pp);
extern size_t discord_user_to_json_v(char *json, size_t len, void *p);
extern size_t discord_user_to_json(char *json, size_t len, struct discord_user *p);
extern void discord_user_list_free_v(void **p);
extern void discord_user_list_free(struct discord_user **p);
extern void discord_user_list_from_json_v(char *str, size_t len, void *p);
extern void discord_user_list_from_json(char *str, size_t len, struct discord_user ***p);
extern size_t discord_user_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_user_list_to_json(char *str, size_t len, struct discord_user **p);


/* Visbility Types */
/* defined at specs/discord/user.json:60:7 */
/**
 * @see https://discord.com/developers/docs/resources/user#connection-object-visibility-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_visibility_types_print(enum discord_visibility_types code)`
 *   * :code:`enum discord_visibility_types discord_visibility_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_visibility_types {
  DISCORD_VISIBILITY_NONE = 0,
  DISCORD_VISIBILITY_EVERYONE = 1,
};
extern char* discord_visibility_types_print(enum discord_visibility_types);
extern enum discord_visibility_types discord_visibility_types_eval(char*);
extern void discord_visibility_types_list_free_v(void **p);
extern void discord_visibility_types_list_free(enum discord_visibility_types **p);
extern void discord_visibility_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_visibility_types_list_from_json(char *str, size_t len, enum discord_visibility_types ***p);
extern size_t discord_visibility_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_visibility_types_list_to_json(char *str, size_t len, enum discord_visibility_types **p);

/* Connection Structure */
/* defined at specs/discord/user.json:74:28 */
/**
 * @see https://discord.com/developers/docs/resources/user#connection-object-connection-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_connection_init(struct discord_connection *)`
 *   * Cleanup:

 *     * :code:`void discord_connection_cleanup(struct discord_connection *)`
 *     * :code:`void discord_connection_list_free(struct discord_connection **)`
 *   * JSON Decoder:

 *     * :code:`void discord_connection_from_json(char *rbuf, size_t len, struct discord_connection **)`
 *     * :code:`void discord_connection_list_from_json(char *rbuf, size_t len, struct discord_connection ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_connection_to_json(char *wbuf, size_t len, struct discord_connection *)`
 *     * :code:`void discord_connection_list_to_json(char *wbuf, size_t len, struct discord_connection **)`
 * @endverbatim
 */
struct discord_connection {
  /* specs/discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
  char *id;

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
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
  struct discord_integration **integrations;

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
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
  enum discord_visibility_types visibility;

};
extern void discord_connection_cleanup_v(void *p);
extern void discord_connection_cleanup(struct discord_connection *p);
extern void discord_connection_init_v(void *p);
extern void discord_connection_init(struct discord_connection *p);
extern void discord_connection_from_json_v(char *json, size_t len, void *pp);
extern void discord_connection_from_json(char *json, size_t len, struct discord_connection **pp);
extern size_t discord_connection_to_json_v(char *json, size_t len, void *p);
extern size_t discord_connection_to_json(char *json, size_t len, struct discord_connection *p);
extern void discord_connection_list_free_v(void **p);
extern void discord_connection_list_free(struct discord_connection **p);
extern void discord_connection_list_from_json_v(char *str, size_t len, void *p);
extern void discord_connection_list_from_json(char *str, size_t len, struct discord_connection ***p);
extern size_t discord_connection_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_connection_list_to_json(char *str, size_t len, struct discord_connection **p);
