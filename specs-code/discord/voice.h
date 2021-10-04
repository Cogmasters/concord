/* This file is generated from specs/discord/voice.json, Please don't edit it. */
/**
 * @file specs-code/discord/voice.h
 * @see https://discord.com/developers/docs/resources/voice
 */


/* Voice State Structure */
/* defined at specs/discord/voice.json:10:22 */
/**
 * @see https://discord.com/developers/docs/resources/voice#voice-state-object-voice-state-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_voice_state_init(struct discord_voice_state *)`
 *   * Cleanup:

 *     * :code:`void discord_voice_state_cleanup(struct discord_voice_state *)`
 *     * :code:`void discord_voice_state_list_free(struct discord_voice_state **)`
 *   * JSON Decoder:

 *     * :code:`void discord_voice_state_from_json(char *rbuf, size_t len, struct discord_voice_state **)`
 *     * :code:`void discord_voice_state_list_from_json(char *rbuf, size_t len, struct discord_voice_state ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_voice_state_to_json(char *wbuf, size_t len, struct discord_voice_state *)`
 *     * :code:`void discord_voice_state_list_to_json(char *wbuf, size_t len, struct discord_voice_state **)`
 * @endverbatim
 */
struct discord_voice_state {
  /* specs/discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t guild_id;

  /* specs/discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t channel_id;

  /* specs/discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t user_id;

  /* specs/discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
  struct discord_guild_member *member;

  /* specs/discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
  char *session_id;

  /* specs/discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
  bool deaf;

  /* specs/discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
  bool mute;

  /* specs/discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
  bool self_deaf;

  /* specs/discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
  bool self_mute;

  /* specs/discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
  bool self_stream;

  /* specs/discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
  bool self_video;

  /* specs/discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
  bool supress;

};
extern void discord_voice_state_cleanup_v(void *p);
extern void discord_voice_state_cleanup(struct discord_voice_state *p);
extern void discord_voice_state_init_v(void *p);
extern void discord_voice_state_init(struct discord_voice_state *p);
extern void discord_voice_state_from_json_v(char *json, size_t len, void *pp);
extern void discord_voice_state_from_json(char *json, size_t len, struct discord_voice_state **pp);
extern size_t discord_voice_state_to_json_v(char *json, size_t len, void *p);
extern size_t discord_voice_state_to_json(char *json, size_t len, struct discord_voice_state *p);
extern void discord_voice_state_list_free_v(void **p);
extern void discord_voice_state_list_free(struct discord_voice_state **p);
extern void discord_voice_state_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_state_list_from_json(char *str, size_t len, struct discord_voice_state ***p);
extern size_t discord_voice_state_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_state_list_to_json(char *str, size_t len, struct discord_voice_state **p);

/* Voice Region Structure */
/* defined at specs/discord/voice.json:31:22 */
/**
 * @see https://discord.com/developers/docs/resources/voice#voice-region-object-voice-region-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_voice_region_init(struct discord_voice_region *)`
 *   * Cleanup:

 *     * :code:`void discord_voice_region_cleanup(struct discord_voice_region *)`
 *     * :code:`void discord_voice_region_list_free(struct discord_voice_region **)`
 *   * JSON Decoder:

 *     * :code:`void discord_voice_region_from_json(char *rbuf, size_t len, struct discord_voice_region **)`
 *     * :code:`void discord_voice_region_list_from_json(char *rbuf, size_t len, struct discord_voice_region ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_voice_region_to_json(char *wbuf, size_t len, struct discord_voice_region *)`
 *     * :code:`void discord_voice_region_list_to_json(char *wbuf, size_t len, struct discord_voice_region **)`
 * @endverbatim
 */
struct discord_voice_region {
  /* specs/discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
  char *id;

  /* specs/discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
  bool vip;

  /* specs/discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
  bool optimal;

  /* specs/discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
  bool deprecated;

  /* specs/discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
  bool custom;

};
extern void discord_voice_region_cleanup_v(void *p);
extern void discord_voice_region_cleanup(struct discord_voice_region *p);
extern void discord_voice_region_init_v(void *p);
extern void discord_voice_region_init(struct discord_voice_region *p);
extern void discord_voice_region_from_json_v(char *json, size_t len, void *pp);
extern void discord_voice_region_from_json(char *json, size_t len, struct discord_voice_region **pp);
extern size_t discord_voice_region_to_json_v(char *json, size_t len, void *p);
extern size_t discord_voice_region_to_json(char *json, size_t len, struct discord_voice_region *p);
extern void discord_voice_region_list_free_v(void **p);
extern void discord_voice_region_list_free(struct discord_voice_region **p);
extern void discord_voice_region_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_region_list_from_json(char *str, size_t len, struct discord_voice_region ***p);
extern size_t discord_voice_region_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_region_list_to_json(char *str, size_t len, struct discord_voice_region **p);
