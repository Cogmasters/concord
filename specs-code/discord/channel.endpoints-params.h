/* This file is generated from specs/discord/channel.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/channel.endpoints-params.h
 * @author cee-studio
 * @date 21 Jun 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/channel
 */


/**
 * @brief Modify Channel
 *
 * @see https://discord.com/developers/docs/resources/channel#modify-channel
 * @note defined at specs/discord/channel.endpoints-params.json:10:22
 */
struct discord_modify_channel_params {
  /* specs/discord/channel.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *name;

  /* specs/discord/channel.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *icon;

  /* specs/discord/channel.endpoints-params.json:15:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  /* specs/discord/channel.endpoints-params.json:16:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int position;

  /* specs/discord/channel.endpoints-params.json:17:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *topic;

  /* specs/discord/channel.endpoints-params.json:18:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool nsfw;

  /* specs/discord/channel.endpoints-params.json:19:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int rate_limit_per_user;

  /* specs/discord/channel.endpoints-params.json:20:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int bitrate;

  /* specs/discord/channel.endpoints-params.json:21:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int user_limit;

  /* specs/discord/channel.endpoints-params.json:22:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
  struct discord_channel_overwrite **permission_overwrites;

  /* specs/discord/channel.endpoints-params.json:23:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
  u64_snowflake_t parent_id;

  /* specs/discord/channel.endpoints-params.json:24:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *rtc_region;

  /* specs/discord/channel.endpoints-params.json:25:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int video_quality_mode;

  /* specs/discord/channel.endpoints-params.json:26:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool archived;

  /* specs/discord/channel.endpoints-params.json:27:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

  /* specs/discord/channel.endpoints-params.json:28:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
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

/**
 * @brief Get Reactions
 *
 * @see https://discord.com/developers/docs/resources/channel#get-reactions
 * @note defined at specs/discord/channel.endpoints-params.json:35:22
 */
struct discord_get_reactions_params {
  /* specs/discord/channel.endpoints-params.json:38:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
  u64_snowflake_t after;

  /* specs/discord/channel.endpoints-params.json:39:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
  int limit;

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
extern void discord_get_reactions_params_cleanup_v(void *p);
extern void discord_get_reactions_params_cleanup(struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_init_v(void *p);
extern void discord_get_reactions_params_init(struct discord_get_reactions_params *p);
extern struct discord_get_reactions_params * discord_get_reactions_params_alloc();
extern void discord_get_reactions_params_free_v(void *p);
extern void discord_get_reactions_params_free(struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_from_json_v(char *json, size_t len, void *p);
extern void discord_get_reactions_params_from_json(char *json, size_t len, struct discord_get_reactions_params *p);
extern size_t discord_get_reactions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_reactions_params_to_json(char *json, size_t len, struct discord_get_reactions_params *p);
extern size_t discord_get_reactions_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_get_reactions_params_to_query(char *json, size_t len, struct discord_get_reactions_params *p);
extern void discord_get_reactions_params_list_free_v(void **p);
extern void discord_get_reactions_params_list_free(struct discord_get_reactions_params **p);
extern void discord_get_reactions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_reactions_params_list_from_json(char *str, size_t len, struct discord_get_reactions_params ***p);
extern size_t discord_get_reactions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_reactions_params_list_to_json(char *str, size_t len, struct discord_get_reactions_params **p);

/**
 * @brief Edit Channel Permissions
 *
 * @see https://discord.com/developers/docs/resources/channel#edit-channel-permissions
 * @note defined at specs/discord/channel.endpoints-params.json:46:22
 */
struct discord_edit_channel_permissions_params {
  /* specs/discord/channel.endpoints-params.json:49:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
  enum discord_permissions_bitwise_flags allow; // permission bit set

  /* specs/discord/channel.endpoints-params.json:50:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
  enum discord_permissions_bitwise_flags deny; // permission bit set

  /* specs/discord/channel.endpoints-params.json:51:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
extern void discord_edit_channel_permissions_params_cleanup_v(void *p);
extern void discord_edit_channel_permissions_params_cleanup(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_init_v(void *p);
extern void discord_edit_channel_permissions_params_init(struct discord_edit_channel_permissions_params *p);
extern struct discord_edit_channel_permissions_params * discord_edit_channel_permissions_params_alloc();
extern void discord_edit_channel_permissions_params_free_v(void *p);
extern void discord_edit_channel_permissions_params_free(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_from_json_v(char *json, size_t len, void *p);
extern void discord_edit_channel_permissions_params_from_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern size_t discord_edit_channel_permissions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_to_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern size_t discord_edit_channel_permissions_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_to_query(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_list_free_v(void **p);
extern void discord_edit_channel_permissions_params_list_free(struct discord_edit_channel_permissions_params **p);
extern void discord_edit_channel_permissions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_channel_permissions_params_list_from_json(char *str, size_t len, struct discord_edit_channel_permissions_params ***p);
extern size_t discord_edit_channel_permissions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_list_to_json(char *str, size_t len, struct discord_edit_channel_permissions_params **p);

/**
 * @brief Follow News Channel
 *
 * @see https://discord.com/developers/docs/resources/channel#follow-news-channel
 * @note defined at specs/discord/channel.endpoints-params.json:58:22
 */
struct discord_follow_news_channel_params {
  /* specs/discord/channel.endpoints-params.json:61:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  u64_snowflake_t webhook_channel_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[1];
    void *record_defined[1];
    void *record_null[1];
  } __M; // metadata
};
extern void discord_follow_news_channel_params_cleanup_v(void *p);
extern void discord_follow_news_channel_params_cleanup(struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_init_v(void *p);
extern void discord_follow_news_channel_params_init(struct discord_follow_news_channel_params *p);
extern struct discord_follow_news_channel_params * discord_follow_news_channel_params_alloc();
extern void discord_follow_news_channel_params_free_v(void *p);
extern void discord_follow_news_channel_params_free(struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_from_json_v(char *json, size_t len, void *p);
extern void discord_follow_news_channel_params_from_json(char *json, size_t len, struct discord_follow_news_channel_params *p);
extern size_t discord_follow_news_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_follow_news_channel_params_to_json(char *json, size_t len, struct discord_follow_news_channel_params *p);
extern size_t discord_follow_news_channel_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_follow_news_channel_params_to_query(char *json, size_t len, struct discord_follow_news_channel_params *p);
extern void discord_follow_news_channel_params_list_free_v(void **p);
extern void discord_follow_news_channel_params_list_free(struct discord_follow_news_channel_params **p);
extern void discord_follow_news_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_follow_news_channel_params_list_from_json(char *str, size_t len, struct discord_follow_news_channel_params ***p);
extern size_t discord_follow_news_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_follow_news_channel_params_list_to_json(char *str, size_t len, struct discord_follow_news_channel_params **p);

/**
 * @brief Create Channel Invite
 *
 * @see https://discord.com/developers/docs/resources/channel#create-channel-invite
 * @note defined at specs/discord/channel.endpoints-params.json:68:22
 */
struct discord_create_channel_invite_params {
  /* specs/discord/channel.endpoints-params.json:71:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  int max_age;

  /* specs/discord/channel.endpoints-params.json:72:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  int max_uses;

  /* specs/discord/channel.endpoints-params.json:73:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
  bool temporary;

  /* specs/discord/channel.endpoints-params.json:74:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
  bool unique;

  /* specs/discord/channel.endpoints-params.json:75:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
  int target_type;

  /* specs/discord/channel.endpoints-params.json:76:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  u64_snowflake_t target_user_id;

  /* specs/discord/channel.endpoints-params.json:77:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  u64_snowflake_t target_application_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
};
extern void discord_create_channel_invite_params_cleanup_v(void *p);
extern void discord_create_channel_invite_params_cleanup(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_init_v(void *p);
extern void discord_create_channel_invite_params_init(struct discord_create_channel_invite_params *p);
extern struct discord_create_channel_invite_params * discord_create_channel_invite_params_alloc();
extern void discord_create_channel_invite_params_free_v(void *p);
extern void discord_create_channel_invite_params_free(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_channel_invite_params_from_json(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern size_t discord_create_channel_invite_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_channel_invite_params_to_json(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern size_t discord_create_channel_invite_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_channel_invite_params_to_query(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_list_free_v(void **p);
extern void discord_create_channel_invite_params_list_free(struct discord_create_channel_invite_params **p);
extern void discord_create_channel_invite_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_channel_invite_params_list_from_json(char *str, size_t len, struct discord_create_channel_invite_params ***p);
extern size_t discord_create_channel_invite_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_channel_invite_params_list_to_json(char *str, size_t len, struct discord_create_channel_invite_params **p);

/**
 * @brief Group DM Add Recipient
 *
 * @see https://discord.com/developers/docs/resources/channel#group-dm-add-recipient
 * @note defined at specs/discord/channel.endpoints-params.json:84:22
 */
struct discord_group_dm_add_recipient_params {
  /* specs/discord/channel.endpoints-params.json:87:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
  char *access_token;

  /* specs/discord/channel.endpoints-params.json:88:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

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
extern void discord_group_dm_add_recipient_params_cleanup_v(void *p);
extern void discord_group_dm_add_recipient_params_cleanup(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_init_v(void *p);
extern void discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params *p);
extern struct discord_group_dm_add_recipient_params * discord_group_dm_add_recipient_params_alloc();
extern void discord_group_dm_add_recipient_params_free_v(void *p);
extern void discord_group_dm_add_recipient_params_free(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_from_json_v(char *json, size_t len, void *p);
extern void discord_group_dm_add_recipient_params_from_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern size_t discord_group_dm_add_recipient_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_to_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern size_t discord_group_dm_add_recipient_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_to_query(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_list_free_v(void **p);
extern void discord_group_dm_add_recipient_params_list_free(struct discord_group_dm_add_recipient_params **p);
extern void discord_group_dm_add_recipient_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_group_dm_add_recipient_params_list_from_json(char *str, size_t len, struct discord_group_dm_add_recipient_params ***p);
extern size_t discord_group_dm_add_recipient_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_list_to_json(char *str, size_t len, struct discord_group_dm_add_recipient_params **p);

/**
 * @brief Start Thread with Message
 *
 * @see https://discord.com/developers/docs/resources/channel#start-thread-with-message-json-params
 * @note defined at specs/discord/channel.endpoints-params.json:95:22
 */
struct discord_start_thread_with_message_params {
  /* specs/discord/channel.endpoints-params.json:98:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *name;

  /* specs/discord/channel.endpoints-params.json:99:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

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
extern void discord_start_thread_with_message_params_cleanup_v(void *p);
extern void discord_start_thread_with_message_params_cleanup(struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_init_v(void *p);
extern void discord_start_thread_with_message_params_init(struct discord_start_thread_with_message_params *p);
extern struct discord_start_thread_with_message_params * discord_start_thread_with_message_params_alloc();
extern void discord_start_thread_with_message_params_free_v(void *p);
extern void discord_start_thread_with_message_params_free(struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_from_json_v(char *json, size_t len, void *p);
extern void discord_start_thread_with_message_params_from_json(char *json, size_t len, struct discord_start_thread_with_message_params *p);
extern size_t discord_start_thread_with_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_with_message_params_to_json(char *json, size_t len, struct discord_start_thread_with_message_params *p);
extern size_t discord_start_thread_with_message_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_with_message_params_to_query(char *json, size_t len, struct discord_start_thread_with_message_params *p);
extern void discord_start_thread_with_message_params_list_free_v(void **p);
extern void discord_start_thread_with_message_params_list_free(struct discord_start_thread_with_message_params **p);
extern void discord_start_thread_with_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_start_thread_with_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_with_message_params ***p);
extern size_t discord_start_thread_with_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_start_thread_with_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_with_message_params **p);

/**
 * @brief Start Thread without Message
 *
 * @see https://discord.com/developers/docs/resources/channel#start-thread-without-message-json-params
 * @note defined at specs/discord/channel.endpoints-params.json:106:22
 */
struct discord_start_thread_without_message_params {
  /* specs/discord/channel.endpoints-params.json:109:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
  char *name;

  /* specs/discord/channel.endpoints-params.json:110:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

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
extern void discord_start_thread_without_message_params_cleanup_v(void *p);
extern void discord_start_thread_without_message_params_cleanup(struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_init_v(void *p);
extern void discord_start_thread_without_message_params_init(struct discord_start_thread_without_message_params *p);
extern struct discord_start_thread_without_message_params * discord_start_thread_without_message_params_alloc();
extern void discord_start_thread_without_message_params_free_v(void *p);
extern void discord_start_thread_without_message_params_free(struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_from_json_v(char *json, size_t len, void *p);
extern void discord_start_thread_without_message_params_from_json(char *json, size_t len, struct discord_start_thread_without_message_params *p);
extern size_t discord_start_thread_without_message_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_to_json(char *json, size_t len, struct discord_start_thread_without_message_params *p);
extern size_t discord_start_thread_without_message_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_to_query(char *json, size_t len, struct discord_start_thread_without_message_params *p);
extern void discord_start_thread_without_message_params_list_free_v(void **p);
extern void discord_start_thread_without_message_params_list_free(struct discord_start_thread_without_message_params **p);
extern void discord_start_thread_without_message_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_start_thread_without_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_without_message_params ***p);
extern size_t discord_start_thread_without_message_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_start_thread_without_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_without_message_params **p);

/**
 * @brief List Active Threads
 *
 * @see https://discord.com/developers/docs/resources/channel#list-active-threads-response-body
 * @note defined at specs/discord/channel.endpoints-params.json:117:22
 */
struct discord_thread_response_body {
  /* specs/discord/channel.endpoints-params.json:120:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
  struct discord_channel **threads;

  /* specs/discord/channel.endpoints-params.json:121:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
  struct discord_thread_member **members;

  /* specs/discord/channel.endpoints-params.json:122:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
  bool has_more;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
extern void discord_thread_response_body_cleanup_v(void *p);
extern void discord_thread_response_body_cleanup(struct discord_thread_response_body *p);
extern void discord_thread_response_body_init_v(void *p);
extern void discord_thread_response_body_init(struct discord_thread_response_body *p);
extern struct discord_thread_response_body * discord_thread_response_body_alloc();
extern void discord_thread_response_body_free_v(void *p);
extern void discord_thread_response_body_free(struct discord_thread_response_body *p);
extern void discord_thread_response_body_from_json_v(char *json, size_t len, void *p);
extern void discord_thread_response_body_from_json(char *json, size_t len, struct discord_thread_response_body *p);
extern size_t discord_thread_response_body_to_json_v(char *json, size_t len, void *p);
extern size_t discord_thread_response_body_to_json(char *json, size_t len, struct discord_thread_response_body *p);
extern size_t discord_thread_response_body_to_query_v(char *json, size_t len, void *p);
extern size_t discord_thread_response_body_to_query(char *json, size_t len, struct discord_thread_response_body *p);
extern void discord_thread_response_body_list_free_v(void **p);
extern void discord_thread_response_body_list_free(struct discord_thread_response_body **p);
extern void discord_thread_response_body_list_from_json_v(char *str, size_t len, void *p);
extern void discord_thread_response_body_list_from_json(char *str, size_t len, struct discord_thread_response_body ***p);
extern size_t discord_thread_response_body_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_thread_response_body_list_to_json(char *str, size_t len, struct discord_thread_response_body **p);
