/* This file is generated from specs/invite.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/invite#invite-object
*/


enum discord_invite_target_user_types_code {
  DISCORD_INVITE_TARGET_USER_TYPES_STREAM = 1,
};

/* Title: Invite Structure */
/* https://discord.com/developers/docs/resources/invite#invite-object-invite-structure */
/* This is defined at specs/invite.json:19:22 */
struct discord_invite_dati {
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *code; // @todo fixed size limit

  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild_dati", "dec":"*"}, "comment":"partial guild object"}'
  */
  struct discord_guild_dati *guild; // partial guild object

  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel_dati", "dec":"*"}, "comment":"partial channel object"}'
  */
  struct discord_channel_dati *channel; // partial channel object

  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user_dati", "dec":"*"}}'
  */
  struct discord_user_dati *inviter;

  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
  struct discord_user_dati *target_user; // partial user object

  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types_code" }}'
  */
  enum discord_invite_target_user_types_code target_user_type;

  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
  int approximate_presence_count;

  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
  int approximate_member_count;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[8];
    void *record_defined[8];
    void *record_null[8];
  } __M; // metadata
};
extern void discord_invite_dati_cleanup_v(void *p);
extern void discord_invite_dati_cleanup(struct discord_invite_dati *p);
extern void discord_invite_dati_init_v(void *p);
extern void discord_invite_dati_init(struct discord_invite_dati *p);
extern struct discord_invite_dati * discord_invite_dati_alloc();
extern void discord_invite_dati_free_v(void *p);
extern void discord_invite_dati_free(struct discord_invite_dati *p);
extern void discord_invite_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_invite_dati_from_json(char *json, size_t len, struct discord_invite_dati *p);
extern size_t discord_invite_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_invite_dati_to_json(char *json, size_t len, struct discord_invite_dati *p);
extern size_t discord_invite_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_invite_dati_to_query(char *json, size_t len, struct discord_invite_dati *p);
extern void discord_invite_dati_list_free_v(void **p);
extern void discord_invite_dati_list_free(struct discord_invite_dati **p);
extern void discord_invite_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_invite_dati_list_from_json(char *str, size_t len, struct discord_invite_dati ***p);
extern size_t discord_invite_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_invite_dati_list_to_json(char *str, size_t len, struct discord_invite_dati **p);

/* Title: Invite Metadata Structure */
/* https://discord.com/developers/docs/resources/invite#invite-metadata-object */
/* This is defined at specs/invite.json:36:22 */
struct discord_invite_metadata_dati {
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
  int user;

  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
  int max_uses;

  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
  int max_age;

  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
  int temporary;

  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  u64_unix_ms_t created_at;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
};
extern void discord_invite_metadata_dati_cleanup_v(void *p);
extern void discord_invite_metadata_dati_cleanup(struct discord_invite_metadata_dati *p);
extern void discord_invite_metadata_dati_init_v(void *p);
extern void discord_invite_metadata_dati_init(struct discord_invite_metadata_dati *p);
extern struct discord_invite_metadata_dati * discord_invite_metadata_dati_alloc();
extern void discord_invite_metadata_dati_free_v(void *p);
extern void discord_invite_metadata_dati_free(struct discord_invite_metadata_dati *p);
extern void discord_invite_metadata_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_invite_metadata_dati_from_json(char *json, size_t len, struct discord_invite_metadata_dati *p);
extern size_t discord_invite_metadata_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_invite_metadata_dati_to_json(char *json, size_t len, struct discord_invite_metadata_dati *p);
extern size_t discord_invite_metadata_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_invite_metadata_dati_to_query(char *json, size_t len, struct discord_invite_metadata_dati *p);
extern void discord_invite_metadata_dati_list_free_v(void **p);
extern void discord_invite_metadata_dati_list_free(struct discord_invite_metadata_dati **p);
extern void discord_invite_metadata_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_invite_metadata_dati_list_from_json(char *str, size_t len, struct discord_invite_metadata_dati ***p);
extern size_t discord_invite_metadata_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_invite_metadata_dati_list_to_json(char *str, size_t len, struct discord_invite_metadata_dati **p);
