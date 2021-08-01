/* This file is generated from specs/discord/webhook.json, Please don't edit it. */
/**
 * @file specs-code/discord/webhook.h
 * @see https://discord.com/developers/docs/resources/webhook
 */


// Webhook Structure
// defined at specs/discord/webhook.json:9:22
/**
 * @see https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
 * - Initializer:
 *   - <tt> discord_webhook_init(struct discord_webhook*) </tt>
 * - Cleanup:
 *   - <tt> discord_webhook_cleanup(struct discord_webhook*) discord_webhook_list_free(struct discord_webhook**) </tt>
 * - JSON Decoder:
 *   - <tt> discord_webhook_from_json(struct discord_webhook**) discord_webhook_list_from_json(struct discord_webhook***) </tt>
 * - JSON Encoder:
 *   - <tt> discord_webhook_to_json(struct discord_webhook*) discord_webhook_list_to_json(struct discord_webhook**) </tt>
 */
struct discord_webhook {
  /* specs/discord/webhook.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/webhook.json:13:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }}' */
  enum discord_webhook_types type;

  /* specs/discord/webhook.json:14:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t guild_id;

  /* specs/discord/webhook.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t channel_id;

  /* specs/discord/webhook.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }}' */
  struct discord_user *user;

  /* specs/discord/webhook.json:17:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_WEBHOOK_NAME_LEN]" }}' */
  char name[DISCORD_WEBHOOK_NAME_LEN];

  /* specs/discord/webhook.json:18:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  char *avatar; ///< @todo fixed size limit

  /* specs/discord/webhook.json:19:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  char *token; ///< @todo fixed size limit

  /* specs/discord/webhook.json:20:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t application_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
/// @endcond
};
extern void discord_webhook_cleanup_v(void *p);
extern void discord_webhook_cleanup(struct discord_webhook *p);
extern void discord_webhook_init_v(void *p);
extern void discord_webhook_init(struct discord_webhook *p);
extern void discord_webhook_from_json_v(char *json, size_t len, void *pp);
extern void discord_webhook_from_json(char *json, size_t len, struct discord_webhook **pp);
extern size_t discord_webhook_to_json_v(char *json, size_t len, void *p);
extern size_t discord_webhook_to_json(char *json, size_t len, struct discord_webhook *p);
extern size_t discord_webhook_to_query_v(char *json, size_t len, void *p);
extern size_t discord_webhook_to_query(char *json, size_t len, struct discord_webhook *p);
extern void discord_webhook_list_free_v(void **p);
extern void discord_webhook_list_free(struct discord_webhook **p);
extern void discord_webhook_list_from_json_v(char *str, size_t len, void *p);
extern void discord_webhook_list_from_json(char *str, size_t len, struct discord_webhook ***p);
extern size_t discord_webhook_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_webhook_list_to_json(char *str, size_t len, struct discord_webhook **p);


enum discord_webhook_types {
  DISCORD_WEBHOOK_INCOMING = 1,
  DISCORD_WEBHOOK_CHANNEL_FOLLOWER = 2,
};
extern char* discord_webhook_types_to_string(enum discord_webhook_types);
extern enum discord_webhook_types discord_webhook_types_from_string(char*);
extern bool discord_webhook_types_has(enum discord_webhook_types, char*);
