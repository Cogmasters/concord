/* This file is generated from specs/discord/webhook.json, Please don't edit it. */
/**
 * @file specs-code/discord/webhook.h
 * @see https://discord.com/developers/docs/resources/webhook
 */


/* Webhook Structure */
/* defined at specs/discord/webhook.json:9:22 */
/**
 * @see https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_webhook_init(struct discord_webhook *)`
 *   * Cleanup:

 *     * :code:`void discord_webhook_cleanup(struct discord_webhook *)`
 *     * :code:`void discord_webhook_list_free(struct discord_webhook **)`
 *   * JSON Decoder:

 *     * :code:`void discord_webhook_from_json(char *rbuf, size_t len, struct discord_webhook **)`
 *     * :code:`void discord_webhook_list_from_json(char *rbuf, size_t len, struct discord_webhook ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_webhook_to_json(char *wbuf, size_t len, struct discord_webhook *)`
 *     * :code:`void discord_webhook_list_to_json(char *wbuf, size_t len, struct discord_webhook **)`
 * @endverbatim
 */
struct discord_webhook {
  /* specs/discord/webhook.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the id of the webhook" }' */
  u64_snowflake_t id; /**< the id of the webhook */

  /* specs/discord/webhook.json:13:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }, "comment":"the type of the webhook" }' */
  enum discord_webhook_types type; /**< the type of the webhook */

  /* specs/discord/webhook.json:14:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the guild id this webhook is for, if any", "inject_if_not":0 }' */
  u64_snowflake_t guild_id; /**< the guild id this webhook is for, if any */

  /* specs/discord/webhook.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the channel id this webhook is for, if any", "inject_if_not":0 }' */
  u64_snowflake_t channel_id; /**< the channel id this webhook is for, if any */

  /* specs/discord/webhook.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "comment":"the user this webhook was created by (not returned when getting a webhook with its token", "inject_if_not":null }' */
  struct discord_user *user; /**< the user this webhook was created by (not returned when getting a webhook with its token */

  /* specs/discord/webhook.json:17:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*", "comment":"the default name of the webhook", "inject_if_not":null }}' */
  char *name;

  /* specs/discord/webhook.json:18:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"the default user avatar has of the webhook", "inject_if_not":null }' */
  char *avatar; /**< the default user avatar has of the webhook */

  /* specs/discord/webhook.json:19:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"the secure token of the webhook (returned for Incoming Webhooks)", "inject_if_not":null }' */
  char *token; /**< the secure token of the webhook (returned for Incoming Webhooks) */

  /* specs/discord/webhook.json:20:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the bot/OAuth2 application that created this webhook", "inject_if_not":0 }' */
  u64_snowflake_t application_id; /**< the bot/OAuth2 application that created this webhook */

  /* specs/discord/webhook.json:21:20
     '{ "name": "source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }, "comment":"the guild of the channel that this webhook is following (returned for Channel Follower Webhook)", "inject_if_not":null }' */
  struct discord_guild *source_guild; /**< the guild of the channel that this webhook is following (returned for Channel Follower Webhook) */

  /* specs/discord/webhook.json:22:20
     '{ "name": "source_channel", "type":{ "base":"struct discord_channel", "dec":"*" }, "comment":"the channel that this webhook is following (returned for Channel Follower Webhooks)", "inject_if_not":null }' */
  struct discord_channel *source_channel; /**< the channel that this webhook is following (returned for Channel Follower Webhooks) */

  /* specs/discord/webhook.json:23:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "comment":"the url used for executing the webhook (returned by the webhooks OAuth2 flow)", "inject_if_not":null }' */
  char *url; /**< the url used for executing the webhook (returned by the webhooks OAuth2 flow) */

};
extern void discord_webhook_cleanup_v(void *p);
extern void discord_webhook_cleanup(struct discord_webhook *p);
extern void discord_webhook_init_v(void *p);
extern void discord_webhook_init(struct discord_webhook *p);
extern void discord_webhook_from_json_v(char *json, size_t len, void *pp);
extern void discord_webhook_from_json(char *json, size_t len, struct discord_webhook **pp);
extern size_t discord_webhook_to_json_v(char *json, size_t len, void *p);
extern size_t discord_webhook_to_json(char *json, size_t len, struct discord_webhook *p);
extern void discord_webhook_list_free_v(void **p);
extern void discord_webhook_list_free(struct discord_webhook **p);
extern void discord_webhook_list_from_json_v(char *str, size_t len, void *p);
extern void discord_webhook_list_from_json(char *str, size_t len, struct discord_webhook ***p);
extern size_t discord_webhook_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_webhook_list_to_json(char *str, size_t len, struct discord_webhook **p);


/* Webhook Types */
/* defined at specs/discord/webhook.json:26:5 */
/**
 * @see https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_webhook_types_print(enum discord_webhook_types code)`
 *   * :code:`enum discord_webhook_types discord_webhook_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_webhook_types {
  DISCORD_WEBHOOK_INCOMING = 1, /**< Incoming Webhooks can post messages to channels with a generated token */
  DISCORD_WEBHOOK_CHANNEL_FOLLOWER = 2, /**< Channel Follower Webhooks are internal webhooks used with Channel Following to post new messages int channels */
  DISCORD_WEBHOOK_APPLICATION = 3, /**< Application webhooks are webhooks used with interactions */
};
extern char* discord_webhook_types_print(enum discord_webhook_types);
extern enum discord_webhook_types discord_webhook_types_eval(char*);
extern void discord_webhook_types_list_free_v(void **p);
extern void discord_webhook_types_list_free(enum discord_webhook_types **p);
extern void discord_webhook_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_webhook_types_list_from_json(char *str, size_t len, enum discord_webhook_types ***p);
extern size_t discord_webhook_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_webhook_types_list_to_json(char *str, size_t len, enum discord_webhook_types **p);
