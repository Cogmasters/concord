/* This file is generated from specs/guild.role.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions#role-object-role-structure
*/

/* Title: Role Tags Structure */
/* This is defined at specs/guild.role.json:9:22 */
struct discord_guild_role_tags_dati {
  /* specs/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t bot_id;

  /* specs/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t integration_id;

  /* specs/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
  int premium_subscriber;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
extern void discord_guild_role_tags_dati_cleanup_v(void *p);
extern void discord_guild_role_tags_dati_cleanup(struct discord_guild_role_tags_dati *p);
extern void discord_guild_role_tags_dati_init_v(void *p);
extern void discord_guild_role_tags_dati_init(struct discord_guild_role_tags_dati *p);
extern struct discord_guild_role_tags_dati * discord_guild_role_tags_dati_alloc();
extern void discord_guild_role_tags_dati_free_v(void *p);
extern void discord_guild_role_tags_dati_free(struct discord_guild_role_tags_dati *p);
extern void discord_guild_role_tags_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_role_tags_dati_from_json(char *json, size_t len, struct discord_guild_role_tags_dati *p);
extern size_t discord_guild_role_tags_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_role_tags_dati_to_json(char *json, size_t len, struct discord_guild_role_tags_dati *p);
extern size_t discord_guild_role_tags_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_role_tags_dati_to_query(char *json, size_t len, struct discord_guild_role_tags_dati *p);
extern void discord_guild_role_tags_dati_list_free_v(void **p);
extern void discord_guild_role_tags_dati_list_free(struct discord_guild_role_tags_dati **p);
extern void discord_guild_role_tags_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_role_tags_dati_list_from_json(char *str, size_t len, struct discord_guild_role_tags_dati ***p);
extern size_t discord_guild_role_tags_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_role_tags_dati_list_to_json(char *str, size_t len, struct discord_guild_role_tags_dati **p);

/* Title: Role Object */
/* This is defined at specs/guild.role.json:20:22 */
struct discord_guild_role_dati {
  /* specs/guild.role.json:23:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/guild.role.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
  char name[MAX_NAME_LEN];

  /* specs/guild.role.json:25:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
  int color;

  /* specs/guild.role.json:26:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
  bool hoist;

  /* specs/guild.role.json:27:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
  int position;

  /* specs/guild.role.json:28:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
  char *permissions;

  /* specs/guild.role.json:29:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
  bool managed;

  /* specs/guild.role.json:30:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
  bool mentionable;

  /* specs/guild.role.json:31:20
     '{ "name": "tags", "type":{"base":"struct discord_guild_role_tags_dati", "dec":"*"}}'
  */
  struct discord_guild_role_tags_dati *tags;

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
extern void discord_guild_role_dati_cleanup_v(void *p);
extern void discord_guild_role_dati_cleanup(struct discord_guild_role_dati *p);
extern void discord_guild_role_dati_init_v(void *p);
extern void discord_guild_role_dati_init(struct discord_guild_role_dati *p);
extern struct discord_guild_role_dati * discord_guild_role_dati_alloc();
extern void discord_guild_role_dati_free_v(void *p);
extern void discord_guild_role_dati_free(struct discord_guild_role_dati *p);
extern void discord_guild_role_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_role_dati_from_json(char *json, size_t len, struct discord_guild_role_dati *p);
extern size_t discord_guild_role_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_role_dati_to_json(char *json, size_t len, struct discord_guild_role_dati *p);
extern size_t discord_guild_role_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_role_dati_to_query(char *json, size_t len, struct discord_guild_role_dati *p);
extern void discord_guild_role_dati_list_free_v(void **p);
extern void discord_guild_role_dati_list_free(struct discord_guild_role_dati **p);
extern void discord_guild_role_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_role_dati_list_from_json(char *str, size_t len, struct discord_guild_role_dati ***p);
extern size_t discord_guild_role_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_role_dati_list_to_json(char *str, size_t len, struct discord_guild_role_dati **p);
