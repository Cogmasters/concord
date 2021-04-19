/* This file is generated from specs/discord/guild.member.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-member-object
*/

/* This is defined at specs/discord/guild.member.json:7:22 */
struct discord_guild_member {
  /* specs/discord/guild.member.json:10:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
  struct discord_user *user;

  /* specs/discord/guild.member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}, "option":true}'
  */
  char nick[MAX_NAME_LEN];

  /* specs/discord/guild.member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}'
  */
  ja_u64 **roles; // array of role object ids

  /* specs/discord/guild.member.json:13:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t joined_at;

  /* specs/discord/guild.member.json:14:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t premium_since;

  /* specs/discord/guild.member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
  bool deaf;

  /* specs/discord/guild.member.json:16:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
  bool mute;

  /* specs/discord/guild.member.json:17:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}'
  */
  bool pending;

  /* specs/discord/guild.member.json:18:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}'
  */
  char *permissions;

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
extern void discord_guild_member_cleanup_v(void *p);
extern void discord_guild_member_cleanup(struct discord_guild_member *p);
extern void discord_guild_member_init_v(void *p);
extern void discord_guild_member_init(struct discord_guild_member *p);
extern struct discord_guild_member * discord_guild_member_alloc();
extern void discord_guild_member_free_v(void *p);
extern void discord_guild_member_free(struct discord_guild_member *p);
extern void discord_guild_member_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_member_from_json(char *json, size_t len, struct discord_guild_member *p);
extern size_t discord_guild_member_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_member_to_json(char *json, size_t len, struct discord_guild_member *p);
extern size_t discord_guild_member_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_member_to_query(char *json, size_t len, struct discord_guild_member *p);
extern void discord_guild_member_list_free_v(void **p);
extern void discord_guild_member_list_free(struct discord_guild_member **p);
extern void discord_guild_member_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_member_list_from_json(char *str, size_t len, struct discord_guild_member ***p);
extern size_t discord_guild_member_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_member_list_to_json(char *str, size_t len, struct discord_guild_member **p);
