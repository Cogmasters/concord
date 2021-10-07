/* This file is generated from specs/discord/emoji.json, Please don't edit it. */
/**
 * @file specs-code/discord/emoji.h
 * @see https://discord.com/developers/docs/resources/emoji
 */


/* Emoji Structure */
/* defined at specs/discord/emoji.json:9:22 */
/**
 * @see https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_emoji_init(struct discord_emoji *)`
 *   * Cleanup:

 *     * :code:`void discord_emoji_cleanup(struct discord_emoji *)`
 *     * :code:`void discord_emoji_list_free(struct discord_emoji **)`
 *   * JSON Decoder:

 *     * :code:`void discord_emoji_from_json(char *rbuf, size_t len, struct discord_emoji **)`
 *     * :code:`void discord_emoji_list_from_json(char *rbuf, size_t len, struct discord_emoji ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_emoji_to_json(char *wbuf, size_t len, struct discord_emoji *)`
 *     * :code:`void discord_emoji_list_to_json(char *wbuf, size_t len, struct discord_emoji **)`
 * @endverbatim
 */
struct discord_emoji {
  /* specs/discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"emoji id"}' */
  u64_snowflake_t id; /**< emoji id */

  /* specs/discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"emoji name"}' */
  char *name; /**< emoji name */

  /* specs/discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl"}, "option":true, "comment":"roles allowed to use this emoji" }' */
  struct discord_role **roles; /**< roles allowed to use this emoji */

  /* specs/discord/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true, "comment":"user that created this emoji" }' */
  struct discord_user *user; /**< user that created this emoji */

  /* specs/discord/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji must be wrapped in colons" }' */
  bool require_colons; /**< whether this emoji must be wrapped in colons */

  /* specs/discord/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is managed" }' */
  bool managed; /**< whether this emoji is managed */

  /* specs/discord/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is animated" }' */
  bool animated; /**< whether this emoji is animated */

  /* specs/discord/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true, "whether this emoji can be used, may be false due to loss of Server Boosts" }' */
  bool available;

};
extern void discord_emoji_cleanup_v(void *p);
extern void discord_emoji_cleanup(struct discord_emoji *p);
extern void discord_emoji_init_v(void *p);
extern void discord_emoji_init(struct discord_emoji *p);
extern void discord_emoji_from_json_v(char *json, size_t len, void *pp);
extern void discord_emoji_from_json(char *json, size_t len, struct discord_emoji **pp);
extern size_t discord_emoji_to_json_v(char *json, size_t len, void *p);
extern size_t discord_emoji_to_json(char *json, size_t len, struct discord_emoji *p);
extern void discord_emoji_list_free_v(void **p);
extern void discord_emoji_list_free(struct discord_emoji **p);
extern void discord_emoji_list_from_json_v(char *str, size_t len, void *p);
extern void discord_emoji_list_from_json(char *str, size_t len, struct discord_emoji ***p);
extern size_t discord_emoji_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_emoji_list_to_json(char *str, size_t len, struct discord_emoji **p);
