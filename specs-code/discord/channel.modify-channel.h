/* This file is generated from specs/discord/channel.modify-channel.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#modify-channel */
/* This is defined at specs/discord/channel.modify-channel.json:8:22 */
struct discord_modify_channel_params {
  /* specs/discord/channel.modify-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  char *name;

  /* specs/discord/channel.modify-channel.json:12:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  char *icon;

  /* specs/discord/channel.modify-channel.json:13:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  /* specs/discord/channel.modify-channel.json:14:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
  int position;

  /* specs/discord/channel.modify-channel.json:15:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  char *topic;

  /* specs/discord/channel.modify-channel.json:16:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool nsfw;

  /* specs/discord/channel.modify-channel.json:17:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int rate_limit_per_user;

  /* specs/discord/channel.modify-channel.json:18:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int bitrate;

  /* specs/discord/channel.modify-channel.json:19:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int user_limit;

  /* specs/discord/channel.modify-channel.json:20:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}'
  */
  struct discord_channel_overwrite **permission_overwrites;

  /* specs/discord/channel.modify-channel.json:21:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
  u64_snowflake_t parent_id;

  /* specs/discord/channel.modify-channel.json:22:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  char *rtc_region;

  /* specs/discord/channel.modify-channel.json:23:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int video_quality_mode;

  /* specs/discord/channel.modify-channel.json:24:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }'
  */
  bool archived;

  /* specs/discord/channel.modify-channel.json:25:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int auto_archive_duration;

  /* specs/discord/channel.modify-channel.json:26:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool locked;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[16];
    void *record_defined[16];
    void *record_null[16];
  } __M; // metadata
};
extern void discord_modify_channel_params_cleanup_v(void *p);
extern void discord_modify_channel_params_cleanup(struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_init_v(void *p);
extern void discord_modify_channel_params_init(struct discord_modify_channel_params *p);
extern struct discord_modify_channel_params * discord_modify_channel_params_alloc();
extern void discord_modify_channel_params_free_v(void *p);
extern void discord_modify_channel_params_free(struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_channel_params_from_json(char *json, size_t len, struct discord_modify_channel_params *p);
extern size_t discord_modify_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_channel_params_to_json(char *json, size_t len, struct discord_modify_channel_params *p);
extern size_t discord_modify_channel_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_channel_params_to_query(char *json, size_t len, struct discord_modify_channel_params *p);
extern void discord_modify_channel_params_list_free_v(void **p);
extern void discord_modify_channel_params_list_free(struct discord_modify_channel_params **p);
extern void discord_modify_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_channel_params_list_from_json(char *str, size_t len, struct discord_modify_channel_params ***p);
extern size_t discord_modify_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_channel_params_list_to_json(char *str, size_t len, struct discord_modify_channel_params **p);
