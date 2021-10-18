/* This file is generated from specs/discord/sticker.json, Please don't edit it. */
/**
 * @file specs-code/discord/sticker.h
 * @see (null)
 */



/* Sticker Types */
/* defined at specs/discord/sticker.json:5:5 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_sticker_types_print(enum discord_sticker_types code)`
 *   * :code:`enum discord_sticker_types discord_sticker_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_sticker_types {
  DISCORD_STICKER_STANDARD = 1, /**< an official sticker in a pack, part of Nitro or in a removed purchasable pack */
  DISCORD_STICKER_GUILD = 2, /**< a sticker uploaded to a Boosted guild for the guild's members */
};
extern char* discord_sticker_types_print(enum discord_sticker_types);
extern enum discord_sticker_types discord_sticker_types_eval(char*);
extern void discord_sticker_types_list_free_v(void **p);
extern void discord_sticker_types_list_free(enum discord_sticker_types **p);
extern void discord_sticker_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_sticker_types_list_from_json(char *str, size_t len, enum discord_sticker_types ***p);
extern size_t discord_sticker_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_sticker_types_list_to_json(char *str, size_t len, enum discord_sticker_types **p);


/* Sticker Format Types */
/* defined at specs/discord/sticker.json:15:5 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_sticker_format_types_print(enum discord_sticker_format_types code)`
 *   * :code:`enum discord_sticker_format_types discord_sticker_format_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_sticker_format_types {
  DISCORD_STICKER_PNG = 1,
  DISCORD_STICKER_APNG = 2,
  DISCORD_STICKER_LOTTIE = 3,
};
extern char* discord_sticker_format_types_print(enum discord_sticker_format_types);
extern enum discord_sticker_format_types discord_sticker_format_types_eval(char*);
extern void discord_sticker_format_types_list_free_v(void **p);
extern void discord_sticker_format_types_list_free(enum discord_sticker_format_types **p);
extern void discord_sticker_format_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_sticker_format_types_list_from_json(char *str, size_t len, enum discord_sticker_format_types ***p);
extern size_t discord_sticker_format_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_sticker_format_types_list_to_json(char *str, size_t len, enum discord_sticker_format_types **p);

/* Sticker Structure */
/* defined at specs/discord/sticker.json:28:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_sticker_init(struct discord_sticker *)`
 *   * Cleanup:

 *     * :code:`void discord_sticker_cleanup(struct discord_sticker *)`
 *     * :code:`void discord_sticker_list_free(struct discord_sticker **)`
 *   * JSON Decoder:

 *     * :code:`void discord_sticker_from_json(char *rbuf, size_t len, struct discord_sticker **)`
 *     * :code:`void discord_sticker_list_from_json(char *rbuf, size_t len, struct discord_sticker ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_sticker_to_json(char *wbuf, size_t len, struct discord_sticker *)`
 *     * :code:`void discord_sticker_list_to_json(char *wbuf, size_t len, struct discord_sticker **)`
 * @endverbatim
 */
struct discord_sticker {
  /* specs/discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
  u64_snowflake_t id; /**< id of the sticker */

  /* specs/discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
  u64_snowflake_t pack_id; /**< for standard stickers, id of the pack the sticker is from */

  /* specs/discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
  char *name; /**< name of the sticker */

  /* specs/discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
  char *description; /**< description of the sticker */

  /* specs/discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  char *tags; /**< autocomplete/suggestion tags for the sticker (max 200 characters) */

  /* specs/discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
  char *asset; /**< Deprecated previously the sticker asset hash, now an empty string */

  /* specs/discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
  enum discord_sticker_types type; /**< type of sticker */

  /* specs/discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
  enum discord_sticker_format_types format_type; /**< type of sticker format */

  /* specs/discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
  bool available; /**< whether this guild sticker can be used, may be false due to loss of Server Boosts */

  /* specs/discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
  u64_snowflake_t guild_id; /**< id of the guild that owns this sticker */

  /* specs/discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
  struct discord_user *user; /**< the user that uploaded the guild sticker */

  /* specs/discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
  int sort_value; /**< the standard sticker's sort order within its pack */

};
extern void discord_sticker_cleanup_v(void *p);
extern void discord_sticker_cleanup(struct discord_sticker *p);
extern void discord_sticker_init_v(void *p);
extern void discord_sticker_init(struct discord_sticker *p);
extern void discord_sticker_from_json_v(char *json, size_t len, void *pp);
extern void discord_sticker_from_json(char *json, size_t len, struct discord_sticker **pp);
extern size_t discord_sticker_to_json_v(char *json, size_t len, void *p);
extern size_t discord_sticker_to_json(char *json, size_t len, struct discord_sticker *p);
extern void discord_sticker_list_free_v(void **p);
extern void discord_sticker_list_free(struct discord_sticker **p);
extern void discord_sticker_list_from_json_v(char *str, size_t len, void *p);
extern void discord_sticker_list_from_json(char *str, size_t len, struct discord_sticker ***p);
extern size_t discord_sticker_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_sticker_list_to_json(char *str, size_t len, struct discord_sticker **p);

/* Sticker Item Structure */
/* defined at specs/discord/sticker.json:47:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_sticker_item_init(struct discord_sticker_item *)`
 *   * Cleanup:

 *     * :code:`void discord_sticker_item_cleanup(struct discord_sticker_item *)`
 *     * :code:`void discord_sticker_item_list_free(struct discord_sticker_item **)`
 *   * JSON Decoder:

 *     * :code:`void discord_sticker_item_from_json(char *rbuf, size_t len, struct discord_sticker_item **)`
 *     * :code:`void discord_sticker_item_list_from_json(char *rbuf, size_t len, struct discord_sticker_item ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_sticker_item_to_json(char *wbuf, size_t len, struct discord_sticker_item *)`
 *     * :code:`void discord_sticker_item_list_to_json(char *wbuf, size_t len, struct discord_sticker_item **)`
 * @endverbatim
 */
struct discord_sticker_item {
  /* specs/discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
  u64_snowflake_t id; /**< id of the sticker */

  /* specs/discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
  char *name; /**< name of the sticker */

  /* specs/discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
  enum discord_sticker_format_types format_type; /**< type of sticker format */

};
extern void discord_sticker_item_cleanup_v(void *p);
extern void discord_sticker_item_cleanup(struct discord_sticker_item *p);
extern void discord_sticker_item_init_v(void *p);
extern void discord_sticker_item_init(struct discord_sticker_item *p);
extern void discord_sticker_item_from_json_v(char *json, size_t len, void *pp);
extern void discord_sticker_item_from_json(char *json, size_t len, struct discord_sticker_item **pp);
extern size_t discord_sticker_item_to_json_v(char *json, size_t len, void *p);
extern size_t discord_sticker_item_to_json(char *json, size_t len, struct discord_sticker_item *p);
extern void discord_sticker_item_list_free_v(void **p);
extern void discord_sticker_item_list_free(struct discord_sticker_item **p);
extern void discord_sticker_item_list_from_json_v(char *str, size_t len, void *p);
extern void discord_sticker_item_list_from_json(char *str, size_t len, struct discord_sticker_item ***p);
extern size_t discord_sticker_item_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_sticker_item_list_to_json(char *str, size_t len, struct discord_sticker_item **p);

/* Sticker Pack Structure */
/* defined at specs/discord/sticker.json:57:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_sticker_pack_init(struct discord_sticker_pack *)`
 *   * Cleanup:

 *     * :code:`void discord_sticker_pack_cleanup(struct discord_sticker_pack *)`
 *     * :code:`void discord_sticker_pack_list_free(struct discord_sticker_pack **)`
 *   * JSON Decoder:

 *     * :code:`void discord_sticker_pack_from_json(char *rbuf, size_t len, struct discord_sticker_pack **)`
 *     * :code:`void discord_sticker_pack_list_from_json(char *rbuf, size_t len, struct discord_sticker_pack ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_sticker_pack_to_json(char *wbuf, size_t len, struct discord_sticker_pack *)`
 *     * :code:`void discord_sticker_pack_list_to_json(char *wbuf, size_t len, struct discord_sticker_pack **)`
 * @endverbatim
 */
struct discord_sticker_pack {
  /* specs/discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
  u64_snowflake_t id; /**< id of the sticker pack */

  /* specs/discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
  struct discord_sticker **stickers; /**< the stickers in the pack */

  /* specs/discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
  char *name; /**< name of the sticker pack */

  /* specs/discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
  u64_snowflake_t sku_id; /**< id of the pack's SKU */

  /* specs/discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
  u64_snowflake_t cover_sticker_id; /**< id of a sticker in the pack which is shown as the pack's icon */

  /* specs/discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
  char *description; /**< description of the sticker pack */

  /* specs/discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
  u64_snowflake_t banner_asset_id; /**< id of the sticker pack's banner image */

};
extern void discord_sticker_pack_cleanup_v(void *p);
extern void discord_sticker_pack_cleanup(struct discord_sticker_pack *p);
extern void discord_sticker_pack_init_v(void *p);
extern void discord_sticker_pack_init(struct discord_sticker_pack *p);
extern void discord_sticker_pack_from_json_v(char *json, size_t len, void *pp);
extern void discord_sticker_pack_from_json(char *json, size_t len, struct discord_sticker_pack **pp);
extern size_t discord_sticker_pack_to_json_v(char *json, size_t len, void *p);
extern size_t discord_sticker_pack_to_json(char *json, size_t len, struct discord_sticker_pack *p);
extern void discord_sticker_pack_list_free_v(void **p);
extern void discord_sticker_pack_list_free(struct discord_sticker_pack **p);
extern void discord_sticker_pack_list_from_json_v(char *str, size_t len, void *p);
extern void discord_sticker_pack_list_from_json(char *str, size_t len, struct discord_sticker_pack ***p);
extern size_t discord_sticker_pack_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_sticker_pack_list_to_json(char *str, size_t len, struct discord_sticker_pack **p);
