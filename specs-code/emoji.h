/* This file is generated from specs/emoji.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure
*/

/* Title: Emoji Structure */
/* This is defined at specs/emoji.json:8:22 */
struct discord_emoji_dati {
  /* specs/emoji.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/emoji.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  char name[MAX_NAME_LEN];

  /* specs/emoji.json:13:20
     '{ "name": "roles", "type":{ "base":"struct discord_guild_role_dati", "dec":"ntl"}, "option":true,
          "todo":true }'
  */
  //@todo roles (null);

  /* specs/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*" }, "option":true }'
  */
  struct discord_user_dati *user;

  /* specs/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}'
  */
  bool require_colons;

  /* specs/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}'
  */
  bool managed;

  /* specs/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}'
  */
  bool animated;

  /* specs/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}'
  */
  bool available;

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
extern void discord_emoji_dati_cleanup_v(void *p);
extern void discord_emoji_dati_cleanup(struct discord_emoji_dati *p);
extern void discord_emoji_dati_init_v(void *p);
extern void discord_emoji_dati_init(struct discord_emoji_dati *p);
extern struct discord_emoji_dati * discord_emoji_dati_alloc();
extern void discord_emoji_dati_free_v(void *p);
extern void discord_emoji_dati_free(struct discord_emoji_dati *p);
extern void discord_emoji_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_emoji_dati_from_json(char *json, size_t len, struct discord_emoji_dati *p);
extern size_t discord_emoji_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_emoji_dati_to_json(char *json, size_t len, struct discord_emoji_dati *p);
extern size_t discord_emoji_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_emoji_dati_to_query(char *json, size_t len, struct discord_emoji_dati *p);
extern void discord_emoji_dati_list_free_v(void **p);
extern void discord_emoji_dati_list_free(struct discord_emoji_dati **p);
extern void discord_emoji_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_emoji_dati_list_from_json(char *str, size_t len, struct discord_emoji_dati ***p);
extern size_t discord_emoji_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_emoji_dati_list_to_json(char *str, size_t len, struct discord_emoji_dati **p);
