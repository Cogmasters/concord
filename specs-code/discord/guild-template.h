/* This file is generated from specs/discord/guild-template.json, Please don't edit it. */
/**
 * @file specs-code/discord/guild-template.h
 * @see https://discord.com/developers/docs/resources/guild-template
 */


/* Guild Template Structure */
/* defined at specs/discord/guild-template.json:9:22 */
/**
 * @see https://discord.com/developers/docs/resources/guild-template#guild-template-object-guild-template-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_template_init(struct discord_guild_template *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_template_cleanup(struct discord_guild_template *)`
 *     * :code:`void discord_guild_template_list_free(struct discord_guild_template **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_template_from_json(char *rbuf, size_t len, struct discord_guild_template **)`
 *     * :code:`void discord_guild_template_list_from_json(char *rbuf, size_t len, struct discord_guild_template ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_template_to_json(char *wbuf, size_t len, struct discord_guild_template *)`
 *     * :code:`void discord_guild_template_list_to_json(char *wbuf, size_t len, struct discord_guild_template **)`
 * @endverbatim
 */
struct discord_guild_template {
  /* specs/discord/guild-template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
  char *code;

  /* specs/discord/guild-template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/guild-template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
  char *description;

  /* specs/discord/guild-template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
  int usage_count;

  /* specs/discord/guild-template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t creator_id;

  /* specs/discord/guild-template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
  struct discord_user *creator;

  /* specs/discord/guild-template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t created_at;

  /* specs/discord/guild-template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t updated_at;

  /* specs/discord/guild-template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t source_guild_id;

  /* specs/discord/guild-template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
  struct discord_guild *serialized_source_guild;

  /* specs/discord/guild-template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
  json_char_t* is_dirty;

};
extern void discord_guild_template_cleanup_v(void *p);
extern void discord_guild_template_cleanup(struct discord_guild_template *p);
extern void discord_guild_template_init_v(void *p);
extern void discord_guild_template_init(struct discord_guild_template *p);
extern void discord_guild_template_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_template_from_json(char *json, size_t len, struct discord_guild_template **pp);
extern size_t discord_guild_template_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_template_to_json(char *json, size_t len, struct discord_guild_template *p);
extern void discord_guild_template_list_free_v(void **p);
extern void discord_guild_template_list_free(struct discord_guild_template **p);
extern void discord_guild_template_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_template_list_from_json(char *str, size_t len, struct discord_guild_template ***p);
extern size_t discord_guild_template_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_template_list_to_json(char *str, size_t len, struct discord_guild_template **p);
