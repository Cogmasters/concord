/* This file is generated from specs/discord/guild.search-guild-members.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#search-guild-members-query-string-params */
/* This is defined at specs/discord/guild.search-guild-members.json:8:22 */
struct discord_search_guild_members_params {
  /* specs/discord/guild.search-guild-members.json:11:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null
          "comment": "Query string to match username(s) and nickname(s) against." }'
  */
  char *query;

  /* specs/discord/guild.search-guild-members.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, 
          "comment": "max number of members to return (1-1000)"}'
  */
  int limit; // max number of members to return (1-1000)

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
};
extern void discord_search_guild_members_params_cleanup_v(void *p);
extern void discord_search_guild_members_params_cleanup(struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_init_v(void *p);
extern void discord_search_guild_members_params_init(struct discord_search_guild_members_params *p);
extern struct discord_search_guild_members_params * discord_search_guild_members_params_alloc();
extern void discord_search_guild_members_params_free_v(void *p);
extern void discord_search_guild_members_params_free(struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_from_json_v(char *json, size_t len, void *p);
extern void discord_search_guild_members_params_from_json(char *json, size_t len, struct discord_search_guild_members_params *p);
extern size_t discord_search_guild_members_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_search_guild_members_params_to_json(char *json, size_t len, struct discord_search_guild_members_params *p);
extern size_t discord_search_guild_members_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_search_guild_members_params_to_query(char *json, size_t len, struct discord_search_guild_members_params *p);
extern void discord_search_guild_members_params_list_free_v(void **p);
extern void discord_search_guild_members_params_list_free(struct discord_search_guild_members_params **p);
extern void discord_search_guild_members_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_search_guild_members_params_list_from_json(char *str, size_t len, struct discord_search_guild_members_params ***p);
extern size_t discord_search_guild_members_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_search_guild_members_params_list_to_json(char *str, size_t len, struct discord_search_guild_members_params **p);
