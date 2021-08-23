/* This file is generated from specs/discord/invite.json, Please don't edit it. */
/**
 * @file specs-code/discord/invite.h
 * @see https://discord.com/developers/docs/resources/invite
 */



// Target User Types
// defined at specs/discord/invite.json:6:5
/**
 * @see https://discord.com/developers/docs/resources/invite#invite-object-target-user-types
 *
 * - <tt> char* discord_invite_target_user_types_print(enum discord_invite_target_user_types code) </tt>
 * - <tt> enum discord_invite_target_user_types discord_invite_target_user_types_eval(char *code_as_str) </tt>
 * - <tt> bool discord_invite_target_user_types_cmp(enum discord_invite_target_user_types code, char *code_as_str) </tt>
 */
enum discord_invite_target_user_types {
  DISCORD_INVITE_STREAM = 1,
};
extern char* discord_invite_target_user_types_print(enum discord_invite_target_user_types);
extern enum discord_invite_target_user_types discord_invite_target_user_types_eval(char*);
extern bool discord_invite_target_user_types_cmp(enum discord_invite_target_user_types, char*);

// Invite Structure
// defined at specs/discord/invite.json:19:22
/**
 * @see https://discord.com/developers/docs/resources/invite#invite-object-invite-structure
 *
 * - Initializer:
 *   - <tt> void discord_invite_init(struct discord_invite *) </tt>
 * - Cleanup:
 *   - <tt> void discord_invite_cleanup(struct discord_invite *) </tt>
 *   - <tt> void discord_invite_list_free(struct discord_invite **) </tt>
 * - JSON Decoder:
 *   - <tt> void discord_invite_from_json(char *rbuf, size_t len, struct discord_invite **) </tt>
 *   - <tt> void discord_invite_list_from_json(char *rbuf, size_t len, struct discord_invite ***) </tt>
 * - JSON Encoder:
 *   - <tt> void discord_invite_to_json(char *wbuf, size_t len, struct discord_invite *) </tt>
 *   - <tt> void discord_invite_list_to_json(char *wbuf, size_t len, struct discord_invite **) </tt>
 */
struct discord_invite {
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  char *code; ///< @todo fixed size limit

  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
  struct discord_guild *guild; ///< partial guild object

  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
  struct discord_channel *channel; ///< partial channel object

  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
  struct discord_user *inviter;

  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  struct discord_user *target_user; ///< partial user object

  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
  enum discord_invite_target_user_types target_user_type;

  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
  int approximate_presence_count;

  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
  int approximate_member_count;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[8];
    void *record_defined[8];
    void *record_null[8];
  } __M; // metadata
/// @endcond
};
extern void discord_invite_cleanup_v(void *p);
extern void discord_invite_cleanup(struct discord_invite *p);
extern void discord_invite_init_v(void *p);
extern void discord_invite_init(struct discord_invite *p);
extern void discord_invite_from_json_v(char *json, size_t len, void *pp);
extern void discord_invite_from_json(char *json, size_t len, struct discord_invite **pp);
extern size_t discord_invite_to_json_v(char *json, size_t len, void *p);
extern size_t discord_invite_to_json(char *json, size_t len, struct discord_invite *p);
extern size_t discord_invite_to_query_v(char *json, size_t len, void *p);
extern size_t discord_invite_to_query(char *json, size_t len, struct discord_invite *p);
extern void discord_invite_list_free_v(void **p);
extern void discord_invite_list_free(struct discord_invite **p);
extern void discord_invite_list_from_json_v(char *str, size_t len, void *p);
extern void discord_invite_list_from_json(char *str, size_t len, struct discord_invite ***p);
extern size_t discord_invite_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_invite_list_to_json(char *str, size_t len, struct discord_invite **p);

// Invite Metadata Structure
// defined at specs/discord/invite.json:36:22
/**
 * @see https://discord.com/developers/docs/resources/invite#invite-metadata-object
 *
 * - Initializer:
 *   - <tt> void discord_invite_metadata_init(struct discord_invite_metadata *) </tt>
 * - Cleanup:
 *   - <tt> void discord_invite_metadata_cleanup(struct discord_invite_metadata *) </tt>
 *   - <tt> void discord_invite_metadata_list_free(struct discord_invite_metadata **) </tt>
 * - JSON Decoder:
 *   - <tt> void discord_invite_metadata_from_json(char *rbuf, size_t len, struct discord_invite_metadata **) </tt>
 *   - <tt> void discord_invite_metadata_list_from_json(char *rbuf, size_t len, struct discord_invite_metadata ***) </tt>
 * - JSON Encoder:
 *   - <tt> void discord_invite_metadata_to_json(char *wbuf, size_t len, struct discord_invite_metadata *) </tt>
 *   - <tt> void discord_invite_metadata_list_to_json(char *wbuf, size_t len, struct discord_invite_metadata **) </tt>
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
extern void discord_invite_metadata_cleanup_v(void *p);
extern void discord_invite_metadata_cleanup(struct discord_invite_metadata *p);
extern void discord_invite_metadata_init_v(void *p);
extern void discord_invite_metadata_init(struct discord_invite_metadata *p);
extern void discord_invite_metadata_from_json_v(char *json, size_t len, void *pp);
extern void discord_invite_metadata_from_json(char *json, size_t len, struct discord_invite_metadata **pp);
extern size_t discord_invite_metadata_to_json_v(char *json, size_t len, void *p);
extern size_t discord_invite_metadata_to_json(char *json, size_t len, struct discord_invite_metadata *p);
extern size_t discord_invite_metadata_to_query_v(char *json, size_t len, void *p);
extern size_t discord_invite_metadata_to_query(char *json, size_t len, struct discord_invite_metadata *p);
extern void discord_invite_metadata_list_free_v(void **p);
extern void discord_invite_metadata_list_free(struct discord_invite_metadata **p);
extern void discord_invite_metadata_list_from_json_v(char *str, size_t len, void *p);
extern void discord_invite_metadata_list_from_json(char *str, size_t len, struct discord_invite_metadata ***p);
extern size_t discord_invite_metadata_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_invite_metadata_list_to_json(char *str, size_t len, struct discord_invite_metadata **p);
