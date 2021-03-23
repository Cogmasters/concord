/* This file is generated from specs/voice.json, Please don't edit it. */
/*
(null)
*/

/* Title: Voice State Object */
/* https://discord.com/developers/docs/resources/voice#voice-state-object-voice-state-structure */
/* This is defined at specs/voice.json:9:22 */
struct discord_voice_dati {
  /* specs/voice.json:12:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t guild_id;

  /* specs/voice.json:13:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t channel_id;

  /* specs/voice.json:14:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t user_id;

  /* specs/voice.json:15:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member_dati", "dec":"*" }}'
  */
  struct discord_guild_member_dati *member;

  /* specs/voice.json:16:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}'
  */
  char *session_id;

  /* specs/voice.json:17:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
  bool deaf;

  /* specs/voice.json:18:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
  bool mute;

  /* specs/voice.json:19:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}'
  */
  bool self_deaf;

  /* specs/voice.json:20:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}'
  */
  bool self_mute;

  /* specs/voice.json:21:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}'
  */
  bool self_stream;

  /* specs/voice.json:22:20
     '{ "name": "self_video", "type":{ "base":"bool" }}'
  */
  bool self_video;

  /* specs/voice.json:23:20
     '{ "name": "supress", "type":{ "base":"bool" }}'
  */
  bool supress;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[12];
    void *record_defined[12];
    void *record_null[12];
  } __M; // metadata
};
extern void discord_voice_dati_cleanup_v(void *p);
extern void discord_voice_dati_cleanup(struct discord_voice_dati *p);
extern void discord_voice_dati_init_v(void *p);
extern void discord_voice_dati_init(struct discord_voice_dati *p);
extern struct discord_voice_dati * discord_voice_dati_alloc();
extern void discord_voice_dati_free_v(void *p);
extern void discord_voice_dati_free(struct discord_voice_dati *p);
extern void discord_voice_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_voice_dati_from_json(char *json, size_t len, struct discord_voice_dati *p);
extern size_t discord_voice_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_voice_dati_to_json(char *json, size_t len, struct discord_voice_dati *p);
extern size_t discord_voice_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_voice_dati_to_query(char *json, size_t len, struct discord_voice_dati *p);
extern void discord_voice_dati_list_free_v(void **p);
extern void discord_voice_dati_list_free(struct discord_voice_dati **p);
extern void discord_voice_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_dati_list_from_json(char *str, size_t len, struct discord_voice_dati ***p);
extern size_t discord_voice_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_dati_list_to_json(char *str, size_t len, struct discord_voice_dati **p);

/* Title: Voice Region Object */
/* https://discord.com/developers/docs/resources/voice#voice-region-object-voice-region-structure */
/* This is defined at specs/voice.json:30:22 */
struct discord_voice_region_dati {
  /* specs/voice.json:33:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
  char *id; // @todo fixed size limit

  /* specs/voice.json:34:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
  char *name; // @todo fixed size limit

  /* specs/voice.json:35:20
     '{ "name": "vip", "type":{ "base":"bool" }}'
  */
  bool vip;

  /* specs/voice.json:36:20
     '{ "name": "optimal", "type":{ "base":"bool" }}'
  */
  bool optimal;

  /* specs/voice.json:37:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}'
  */
  bool deprecated;

  /* specs/voice.json:38:20
     '{ "name": "custom", "type":{ "base":"bool" }}'
  */
  bool custom;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
};
extern void discord_voice_region_dati_cleanup_v(void *p);
extern void discord_voice_region_dati_cleanup(struct discord_voice_region_dati *p);
extern void discord_voice_region_dati_init_v(void *p);
extern void discord_voice_region_dati_init(struct discord_voice_region_dati *p);
extern struct discord_voice_region_dati * discord_voice_region_dati_alloc();
extern void discord_voice_region_dati_free_v(void *p);
extern void discord_voice_region_dati_free(struct discord_voice_region_dati *p);
extern void discord_voice_region_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_voice_region_dati_from_json(char *json, size_t len, struct discord_voice_region_dati *p);
extern size_t discord_voice_region_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_voice_region_dati_to_json(char *json, size_t len, struct discord_voice_region_dati *p);
extern size_t discord_voice_region_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_voice_region_dati_to_query(char *json, size_t len, struct discord_voice_region_dati *p);
extern void discord_voice_region_dati_list_free_v(void **p);
extern void discord_voice_region_dati_list_free(struct discord_voice_region_dati **p);
extern void discord_voice_region_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_region_dati_list_from_json(char *str, size_t len, struct discord_voice_region_dati ***p);
extern size_t discord_voice_region_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_region_dati_list_to_json(char *str, size_t len, struct discord_voice_region_dati **p);
