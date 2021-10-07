/* This file is generated from specs/discord/invite.json, Please don't edit it. */
/**
 * @file specs-code/discord/invite.h
 * @see https://discord.com/developers/docs/resources/invite
 */



/* Target User Types */
/* defined at specs/discord/invite.json:6:5 */
/**
 * @see https://discord.com/developers/docs/resources/invite#invite-object-target-user-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_invite_target_user_types_print(enum discord_invite_target_user_types code)`
 *   * :code:`enum discord_invite_target_user_types discord_invite_target_user_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_invite_target_user_types {
  DISCORD_INVITE_STREAM = 1,
};
extern char* discord_invite_target_user_types_print(enum discord_invite_target_user_types);
extern enum discord_invite_target_user_types discord_invite_target_user_types_eval(char*);
extern void discord_invite_target_user_types_list_free_v(void **p);
extern void discord_invite_target_user_types_list_free(enum discord_invite_target_user_types **p);
extern void discord_invite_target_user_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_invite_target_user_types_list_from_json(char *str, size_t len, enum discord_invite_target_user_types ***p);
extern size_t discord_invite_target_user_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_invite_target_user_types_list_to_json(char *str, size_t len, enum discord_invite_target_user_types **p);

/* Invite Structure */
/* defined at specs/discord/invite.json:19:22 */
/**
 * @see https://discord.com/developers/docs/resources/invite#invite-object-invite-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_invite_init(struct discord_invite *)`
 *   * Cleanup:

 *     * :code:`void discord_invite_cleanup(struct discord_invite *)`
 *     * :code:`void discord_invite_list_free(struct discord_invite **)`
 *   * JSON Decoder:

 *     * :code:`void discord_invite_from_json(char *rbuf, size_t len, struct discord_invite **)`
 *     * :code:`void discord_invite_list_from_json(char *rbuf, size_t len, struct discord_invite ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_invite_to_json(char *wbuf, size_t len, struct discord_invite *)`
 *     * :code:`void discord_invite_list_to_json(char *wbuf, size_t len, struct discord_invite **)`
 * @endverbatim
 */
struct discord_invite {
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }}' */
  char *code;

  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
  struct discord_guild *guild; /**< partial guild object */

  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
  struct discord_channel *channel; /**< partial channel object */

  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
  struct discord_user *inviter;

  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  struct discord_user *target_user; /**< partial user object */

  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
  enum discord_invite_target_user_types target_user_type;

  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
  int approximate_presence_count;

  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
  int approximate_member_count;

};
extern void discord_invite_cleanup_v(void *p);
extern void discord_invite_cleanup(struct discord_invite *p);
extern void discord_invite_init_v(void *p);
extern void discord_invite_init(struct discord_invite *p);
extern void discord_invite_from_json_v(char *json, size_t len, void *pp);
extern void discord_invite_from_json(char *json, size_t len, struct discord_invite **pp);
extern size_t discord_invite_to_json_v(char *json, size_t len, void *p);
extern size_t discord_invite_to_json(char *json, size_t len, struct discord_invite *p);
extern void discord_invite_list_free_v(void **p);
extern void discord_invite_list_free(struct discord_invite **p);
extern void discord_invite_list_from_json_v(char *str, size_t len, void *p);
extern void discord_invite_list_from_json(char *str, size_t len, struct discord_invite ***p);
extern size_t discord_invite_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_invite_list_to_json(char *str, size_t len, struct discord_invite **p);

/* Invite Metadata Structure */
/* defined at specs/discord/invite.json:36:22 */
/**
 * @see https://discord.com/developers/docs/resources/invite#invite-metadata-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_invite_metadata_init(struct discord_invite_metadata *)`
 *   * Cleanup:

 *     * :code:`void discord_invite_metadata_cleanup(struct discord_invite_metadata *)`
 *     * :code:`void discord_invite_metadata_list_free(struct discord_invite_metadata **)`
 *   * JSON Decoder:

 *     * :code:`void discord_invite_metadata_from_json(char *rbuf, size_t len, struct discord_invite_metadata **)`
 *     * :code:`void discord_invite_metadata_list_from_json(char *rbuf, size_t len, struct discord_invite_metadata ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_invite_metadata_to_json(char *wbuf, size_t len, struct discord_invite_metadata *)`
 *     * :code:`void discord_invite_metadata_list_to_json(char *wbuf, size_t len, struct discord_invite_metadata **)`
 * @endverbatim
 */
struct discord_invite_metadata {
  /* specs/discord/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}' */
  int user;

  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  int max_uses;

  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  int max_age;

  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}' */
  int temporary;

  /* specs/discord/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
  u64_unix_ms_t created_at;

};
extern void discord_invite_metadata_cleanup_v(void *p);
extern void discord_invite_metadata_cleanup(struct discord_invite_metadata *p);
extern void discord_invite_metadata_init_v(void *p);
extern void discord_invite_metadata_init(struct discord_invite_metadata *p);
extern void discord_invite_metadata_from_json_v(char *json, size_t len, void *pp);
extern void discord_invite_metadata_from_json(char *json, size_t len, struct discord_invite_metadata **pp);
extern size_t discord_invite_metadata_to_json_v(char *json, size_t len, void *p);
extern size_t discord_invite_metadata_to_json(char *json, size_t len, struct discord_invite_metadata *p);
extern void discord_invite_metadata_list_free_v(void **p);
extern void discord_invite_metadata_list_free(struct discord_invite_metadata **p);
extern void discord_invite_metadata_list_from_json_v(char *str, size_t len, void *p);
extern void discord_invite_metadata_list_from_json(char *str, size_t len, struct discord_invite_metadata ***p);
extern size_t discord_invite_metadata_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_invite_metadata_list_to_json(char *str, size_t len, struct discord_invite_metadata **p);
