/* This file is generated from specs/channel.objects.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#overwrite-object-overwrite-structure
*/

/* Title: Overwrite Structure */
/* This is defined at specs/channel.objects.json:10:22 */
struct discord_channel_overwrite_dati {
  /* specs/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  /* specs/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  discord_permissions_bitwise_flags allow; // permission bit set

  /* specs/channel.objects.json:17:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  discord_permissions_bitwise_flags deny; // permission bit set

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
};
extern void discord_channel_overwrite_dati_cleanup_v(void *p);
extern void discord_channel_overwrite_dati_cleanup(struct discord_channel_overwrite_dati *p);
extern void discord_channel_overwrite_dati_init_v(void *p);
extern void discord_channel_overwrite_dati_init(struct discord_channel_overwrite_dati *p);
extern struct discord_channel_overwrite_dati * discord_channel_overwrite_dati_alloc();
extern void discord_channel_overwrite_dati_free_v(void *p);
extern void discord_channel_overwrite_dati_free(struct discord_channel_overwrite_dati *p);
extern void discord_channel_overwrite_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_overwrite_dati_from_json(char *json, size_t len, struct discord_channel_overwrite_dati *p);
extern size_t discord_channel_overwrite_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_overwrite_dati_to_json(char *json, size_t len, struct discord_channel_overwrite_dati *p);
extern size_t discord_channel_overwrite_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_overwrite_dati_to_query(char *json, size_t len, struct discord_channel_overwrite_dati *p);
extern void discord_channel_overwrite_dati_list_free_v(void **p);
extern void discord_channel_overwrite_dati_list_free(struct discord_channel_overwrite_dati **p);
extern void discord_channel_overwrite_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_overwrite_dati_list_from_json(char *str, size_t len, struct discord_channel_overwrite_dati ***p);
extern size_t discord_channel_overwrite_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_overwrite_dati_list_to_json(char *str, size_t len, struct discord_channel_overwrite_dati **p);

/* https://discord.com/developers/docs/resources/channel#reaction-object-reaction-structure */
/* This is defined at specs/channel.objects.json:24:22 */
struct discord_channel_reaction_dati {
  /* specs/channel.objects.json:27:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
  int count;

  /* specs/channel.objects.json:28:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
  bool me;

  /* specs/channel.objects.json:29:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji_dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
  struct discord_emoji_dati *emoji; // partial emoji object

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
extern void discord_channel_reaction_dati_cleanup_v(void *p);
extern void discord_channel_reaction_dati_cleanup(struct discord_channel_reaction_dati *p);
extern void discord_channel_reaction_dati_init_v(void *p);
extern void discord_channel_reaction_dati_init(struct discord_channel_reaction_dati *p);
extern struct discord_channel_reaction_dati * discord_channel_reaction_dati_alloc();
extern void discord_channel_reaction_dati_free_v(void *p);
extern void discord_channel_reaction_dati_free(struct discord_channel_reaction_dati *p);
extern void discord_channel_reaction_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_reaction_dati_from_json(char *json, size_t len, struct discord_channel_reaction_dati *p);
extern size_t discord_channel_reaction_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_reaction_dati_to_json(char *json, size_t len, struct discord_channel_reaction_dati *p);
extern size_t discord_channel_reaction_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_reaction_dati_to_query(char *json, size_t len, struct discord_channel_reaction_dati *p);
extern void discord_channel_reaction_dati_list_free_v(void **p);
extern void discord_channel_reaction_dati_list_free(struct discord_channel_reaction_dati **p);
extern void discord_channel_reaction_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_reaction_dati_list_from_json(char *str, size_t len, struct discord_channel_reaction_dati ***p);
extern size_t discord_channel_reaction_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_reaction_dati_list_to_json(char *str, size_t len, struct discord_channel_reaction_dati **p);

/* Title: Followed Channel Structure */
/* https://discord.com/developers/docs/resources/channel#followed-channel-object-followed-channel-structure */
/* This is defined at specs/channel.objects.json:36:22 */
struct discord_channel_followed_channel_dati {
  /* specs/channel.objects.json:39:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t channel_id;

  /* specs/channel.objects.json:40:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t webhook_id;

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
extern void discord_channel_followed_channel_dati_cleanup_v(void *p);
extern void discord_channel_followed_channel_dati_cleanup(struct discord_channel_followed_channel_dati *p);
extern void discord_channel_followed_channel_dati_init_v(void *p);
extern void discord_channel_followed_channel_dati_init(struct discord_channel_followed_channel_dati *p);
extern struct discord_channel_followed_channel_dati * discord_channel_followed_channel_dati_alloc();
extern void discord_channel_followed_channel_dati_free_v(void *p);
extern void discord_channel_followed_channel_dati_free(struct discord_channel_followed_channel_dati *p);
extern void discord_channel_followed_channel_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_followed_channel_dati_from_json(char *json, size_t len, struct discord_channel_followed_channel_dati *p);
extern size_t discord_channel_followed_channel_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_followed_channel_dati_to_json(char *json, size_t len, struct discord_channel_followed_channel_dati *p);
extern size_t discord_channel_followed_channel_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_followed_channel_dati_to_query(char *json, size_t len, struct discord_channel_followed_channel_dati *p);
extern void discord_channel_followed_channel_dati_list_free_v(void **p);
extern void discord_channel_followed_channel_dati_list_free(struct discord_channel_followed_channel_dati **p);
extern void discord_channel_followed_channel_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_followed_channel_dati_list_from_json(char *str, size_t len, struct discord_channel_followed_channel_dati ***p);
extern size_t discord_channel_followed_channel_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_followed_channel_dati_list_to_json(char *str, size_t len, struct discord_channel_followed_channel_dati **p);

/* https://discord.com/developers/docs/resources/channel#attachment-object */
/* This is defined at specs/channel.objects.json:46:22 */
struct discord_channel_attachment_dati {
  /* specs/channel.objects.json:49:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/channel.objects.json:50:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
  char filename[256];

  /* specs/channel.objects.json:51:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
  int size;

  /* specs/channel.objects.json:52:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:53:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/channel.objects.json:54:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
  int height;

  /* specs/channel.objects.json:55:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
  int width;

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
extern void discord_channel_attachment_dati_cleanup_v(void *p);
extern void discord_channel_attachment_dati_cleanup(struct discord_channel_attachment_dati *p);
extern void discord_channel_attachment_dati_init_v(void *p);
extern void discord_channel_attachment_dati_init(struct discord_channel_attachment_dati *p);
extern struct discord_channel_attachment_dati * discord_channel_attachment_dati_alloc();
extern void discord_channel_attachment_dati_free_v(void *p);
extern void discord_channel_attachment_dati_free(struct discord_channel_attachment_dati *p);
extern void discord_channel_attachment_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_attachment_dati_from_json(char *json, size_t len, struct discord_channel_attachment_dati *p);
extern size_t discord_channel_attachment_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_attachment_dati_to_json(char *json, size_t len, struct discord_channel_attachment_dati *p);
extern size_t discord_channel_attachment_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_attachment_dati_to_query(char *json, size_t len, struct discord_channel_attachment_dati *p);
extern void discord_channel_attachment_dati_list_free_v(void **p);
extern void discord_channel_attachment_dati_list_free(struct discord_channel_attachment_dati **p);
extern void discord_channel_attachment_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_attachment_dati_list_from_json(char *str, size_t len, struct discord_channel_attachment_dati ***p);
extern size_t discord_channel_attachment_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_attachment_dati_list_to_json(char *str, size_t len, struct discord_channel_attachment_dati **p);

/* Title: Channel Mention Structure */
/* https://discord.com/developers/docs/resources/channel#channel-mention-object-channel-mention-structure */
/* This is defined at specs/channel.objects.json:62:22 */
struct discord_channel_mention_dati {
  /* specs/channel.objects.json:65:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/channel.objects.json:66:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t guild_id;

  /* specs/channel.objects.json:67:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types_code" }}'
  */
  enum discord_channel_types_code type;

  /* specs/channel.objects.json:68:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
};
extern void discord_channel_mention_dati_cleanup_v(void *p);
extern void discord_channel_mention_dati_cleanup(struct discord_channel_mention_dati *p);
extern void discord_channel_mention_dati_init_v(void *p);
extern void discord_channel_mention_dati_init(struct discord_channel_mention_dati *p);
extern struct discord_channel_mention_dati * discord_channel_mention_dati_alloc();
extern void discord_channel_mention_dati_free_v(void *p);
extern void discord_channel_mention_dati_free(struct discord_channel_mention_dati *p);
extern void discord_channel_mention_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_mention_dati_from_json(char *json, size_t len, struct discord_channel_mention_dati *p);
extern size_t discord_channel_mention_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_mention_dati_to_json(char *json, size_t len, struct discord_channel_mention_dati *p);
extern size_t discord_channel_mention_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_mention_dati_to_query(char *json, size_t len, struct discord_channel_mention_dati *p);
extern void discord_channel_mention_dati_list_free_v(void **p);
extern void discord_channel_mention_dati_list_free(struct discord_channel_mention_dati **p);
extern void discord_channel_mention_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_mention_dati_list_from_json(char *str, size_t len, struct discord_channel_mention_dati ***p);
extern size_t discord_channel_mention_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_mention_dati_list_to_json(char *str, size_t len, struct discord_channel_mention_dati **p);

/* Title: Allowed Mentions Structure */
/* https://discord.com/developers/docs/resources/channel#allowed-mentions-object-allowed-mentions-structure */
/* This is defined at specs/channel.objects.json:75:22 */
struct discord_channel_allowed_mentions_dati {
  /* specs/channel.objects.json:78:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
  ja_str **parse;

  /* specs/channel.objects.json:79:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  ja_u64 **roles; // list of snowflakes

  /* specs/channel.objects.json:80:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  ja_u64 **users; // list of snowflakes

  /* specs/channel.objects.json:81:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
  bool replied_user;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
};
extern void discord_channel_allowed_mentions_dati_cleanup_v(void *p);
extern void discord_channel_allowed_mentions_dati_cleanup(struct discord_channel_allowed_mentions_dati *p);
extern void discord_channel_allowed_mentions_dati_init_v(void *p);
extern void discord_channel_allowed_mentions_dati_init(struct discord_channel_allowed_mentions_dati *p);
extern struct discord_channel_allowed_mentions_dati * discord_channel_allowed_mentions_dati_alloc();
extern void discord_channel_allowed_mentions_dati_free_v(void *p);
extern void discord_channel_allowed_mentions_dati_free(struct discord_channel_allowed_mentions_dati *p);
extern void discord_channel_allowed_mentions_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_allowed_mentions_dati_from_json(char *json, size_t len, struct discord_channel_allowed_mentions_dati *p);
extern size_t discord_channel_allowed_mentions_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_allowed_mentions_dati_to_json(char *json, size_t len, struct discord_channel_allowed_mentions_dati *p);
extern size_t discord_channel_allowed_mentions_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_allowed_mentions_dati_to_query(char *json, size_t len, struct discord_channel_allowed_mentions_dati *p);
extern void discord_channel_allowed_mentions_dati_list_free_v(void **p);
extern void discord_channel_allowed_mentions_dati_list_free(struct discord_channel_allowed_mentions_dati **p);
extern void discord_channel_allowed_mentions_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_allowed_mentions_dati_list_from_json(char *str, size_t len, struct discord_channel_allowed_mentions_dati ***p);
extern size_t discord_channel_allowed_mentions_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_allowed_mentions_dati_list_to_json(char *str, size_t len, struct discord_channel_allowed_mentions_dati **p);

/* Title: Embed Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-structure */
/* This is defined at specs/channel.objects.json:88:22 */
struct discord_channel_embed_dati {
  /* specs/channel.objects.json:91:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  char title[EMBED_TITLE_LEN];

  /* specs/channel.objects.json:93:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
  char type[32];

  /* specs/channel.objects.json:95:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  char description[EMBED_DESCRIPTION_LEN];

  /* specs/channel.objects.json:97:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:99:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
  u64_unix_ms_t timestamp;

  /* specs/channel.objects.json:101:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
  int color;

  /* specs/channel.objects.json:102:20
     '{ "name": "footer", "type":{ "base":"struct discord_channel_embed_footer_dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  struct discord_channel_embed_footer_dati *footer;

  /* specs/channel.objects.json:104:20
     '{ "name": "image", "type":{ "base":"struct discord_channel_embed_image_dati", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_channel_embed_image_dati *image;

  /* specs/channel.objects.json:105:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_channel_embed_thumbnail_dati", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_channel_embed_thumbnail_dati *thumbnail;

  /* specs/channel.objects.json:106:20
     '{ "name": "video", "type":{ "base":"struct discord_channel_embed_video_dati", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_channel_embed_video_dati *video;

  /* specs/channel.objects.json:107:20
     '{ "name": "provider", "type":{ "base":"struct discord_channel_embed_provider_dati", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_channel_embed_provider_dati *provider;

  /* specs/channel.objects.json:108:20
     '{ "name": "author", "type":{ "base":"struct discord_channel_embed_author_dati", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_channel_embed_author_dati *author;

  /* specs/channel.objects.json:109:20
     '{ "name": "fields", "type":{ "base":"struct discord_channel_embed_field_dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
  struct discord_channel_embed_field_dati **fields;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[13];
    void *record_defined[13];
    void *record_null[13];
  } __M; // metadata
};
extern void discord_channel_embed_dati_cleanup_v(void *p);
extern void discord_channel_embed_dati_cleanup(struct discord_channel_embed_dati *p);
extern void discord_channel_embed_dati_init_v(void *p);
extern void discord_channel_embed_dati_init(struct discord_channel_embed_dati *p);
extern struct discord_channel_embed_dati * discord_channel_embed_dati_alloc();
extern void discord_channel_embed_dati_free_v(void *p);
extern void discord_channel_embed_dati_free(struct discord_channel_embed_dati *p);
extern void discord_channel_embed_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_embed_dati_from_json(char *json, size_t len, struct discord_channel_embed_dati *p);
extern size_t discord_channel_embed_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_dati_to_json(char *json, size_t len, struct discord_channel_embed_dati *p);
extern size_t discord_channel_embed_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_dati_to_query(char *json, size_t len, struct discord_channel_embed_dati *p);
extern void discord_channel_embed_dati_list_free_v(void **p);
extern void discord_channel_embed_dati_list_free(struct discord_channel_embed_dati **p);
extern void discord_channel_embed_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_embed_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_dati ***p);
extern size_t discord_channel_embed_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_embed_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_dati **p);

/* Title: Embed Thumbnail Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure */
/* This is defined at specs/channel.objects.json:119:22 */
struct discord_channel_embed_thumbnail_dati {
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int width;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
};
extern void discord_channel_embed_thumbnail_dati_cleanup_v(void *p);
extern void discord_channel_embed_thumbnail_dati_cleanup(struct discord_channel_embed_thumbnail_dati *p);
extern void discord_channel_embed_thumbnail_dati_init_v(void *p);
extern void discord_channel_embed_thumbnail_dati_init(struct discord_channel_embed_thumbnail_dati *p);
extern struct discord_channel_embed_thumbnail_dati * discord_channel_embed_thumbnail_dati_alloc();
extern void discord_channel_embed_thumbnail_dati_free_v(void *p);
extern void discord_channel_embed_thumbnail_dati_free(struct discord_channel_embed_thumbnail_dati *p);
extern void discord_channel_embed_thumbnail_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_embed_thumbnail_dati_from_json(char *json, size_t len, struct discord_channel_embed_thumbnail_dati *p);
extern size_t discord_channel_embed_thumbnail_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_thumbnail_dati_to_json(char *json, size_t len, struct discord_channel_embed_thumbnail_dati *p);
extern size_t discord_channel_embed_thumbnail_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_thumbnail_dati_to_query(char *json, size_t len, struct discord_channel_embed_thumbnail_dati *p);
extern void discord_channel_embed_thumbnail_dati_list_free_v(void **p);
extern void discord_channel_embed_thumbnail_dati_list_free(struct discord_channel_embed_thumbnail_dati **p);
extern void discord_channel_embed_thumbnail_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_embed_thumbnail_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_thumbnail_dati ***p);
extern size_t discord_channel_embed_thumbnail_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_embed_thumbnail_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_thumbnail_dati **p);

/* Title: Embed Thumbnail Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure */
/* This is defined at specs/channel.objects.json:119:22 */
struct discord_channel_embed_video_dati {
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int width;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
};
extern void discord_channel_embed_video_dati_cleanup_v(void *p);
extern void discord_channel_embed_video_dati_cleanup(struct discord_channel_embed_video_dati *p);
extern void discord_channel_embed_video_dati_init_v(void *p);
extern void discord_channel_embed_video_dati_init(struct discord_channel_embed_video_dati *p);
extern struct discord_channel_embed_video_dati * discord_channel_embed_video_dati_alloc();
extern void discord_channel_embed_video_dati_free_v(void *p);
extern void discord_channel_embed_video_dati_free(struct discord_channel_embed_video_dati *p);
extern void discord_channel_embed_video_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_embed_video_dati_from_json(char *json, size_t len, struct discord_channel_embed_video_dati *p);
extern size_t discord_channel_embed_video_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_video_dati_to_json(char *json, size_t len, struct discord_channel_embed_video_dati *p);
extern size_t discord_channel_embed_video_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_video_dati_to_query(char *json, size_t len, struct discord_channel_embed_video_dati *p);
extern void discord_channel_embed_video_dati_list_free_v(void **p);
extern void discord_channel_embed_video_dati_list_free(struct discord_channel_embed_video_dati **p);
extern void discord_channel_embed_video_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_embed_video_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_video_dati ***p);
extern size_t discord_channel_embed_video_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_embed_video_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_video_dati **p);

/* Title: Embed Thumbnail Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure */
/* This is defined at specs/channel.objects.json:119:22 */
struct discord_channel_embed_image_dati {
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int width;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
};
extern void discord_channel_embed_image_dati_cleanup_v(void *p);
extern void discord_channel_embed_image_dati_cleanup(struct discord_channel_embed_image_dati *p);
extern void discord_channel_embed_image_dati_init_v(void *p);
extern void discord_channel_embed_image_dati_init(struct discord_channel_embed_image_dati *p);
extern struct discord_channel_embed_image_dati * discord_channel_embed_image_dati_alloc();
extern void discord_channel_embed_image_dati_free_v(void *p);
extern void discord_channel_embed_image_dati_free(struct discord_channel_embed_image_dati *p);
extern void discord_channel_embed_image_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_embed_image_dati_from_json(char *json, size_t len, struct discord_channel_embed_image_dati *p);
extern size_t discord_channel_embed_image_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_image_dati_to_json(char *json, size_t len, struct discord_channel_embed_image_dati *p);
extern size_t discord_channel_embed_image_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_image_dati_to_query(char *json, size_t len, struct discord_channel_embed_image_dati *p);
extern void discord_channel_embed_image_dati_list_free_v(void **p);
extern void discord_channel_embed_image_dati_list_free(struct discord_channel_embed_image_dati **p);
extern void discord_channel_embed_image_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_embed_image_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_image_dati ***p);
extern size_t discord_channel_embed_image_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_embed_image_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_image_dati **p);

/* Title: Embed Provider Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-provider-structure */
/* This is defined at specs/channel.objects.json:131:22 */
struct discord_channel_embed_provider_dati {
  /* specs/channel.objects.json:133:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
  char name[EMBED_AUTHOR_NAME_LEN];

  /* specs/channel.objects.json:134:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

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
extern void discord_channel_embed_provider_dati_cleanup_v(void *p);
extern void discord_channel_embed_provider_dati_cleanup(struct discord_channel_embed_provider_dati *p);
extern void discord_channel_embed_provider_dati_init_v(void *p);
extern void discord_channel_embed_provider_dati_init(struct discord_channel_embed_provider_dati *p);
extern struct discord_channel_embed_provider_dati * discord_channel_embed_provider_dati_alloc();
extern void discord_channel_embed_provider_dati_free_v(void *p);
extern void discord_channel_embed_provider_dati_free(struct discord_channel_embed_provider_dati *p);
extern void discord_channel_embed_provider_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_embed_provider_dati_from_json(char *json, size_t len, struct discord_channel_embed_provider_dati *p);
extern size_t discord_channel_embed_provider_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_provider_dati_to_json(char *json, size_t len, struct discord_channel_embed_provider_dati *p);
extern size_t discord_channel_embed_provider_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_provider_dati_to_query(char *json, size_t len, struct discord_channel_embed_provider_dati *p);
extern void discord_channel_embed_provider_dati_list_free_v(void **p);
extern void discord_channel_embed_provider_dati_list_free(struct discord_channel_embed_provider_dati **p);
extern void discord_channel_embed_provider_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_embed_provider_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_provider_dati ***p);
extern size_t discord_channel_embed_provider_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_embed_provider_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_provider_dati **p);

/* Title: Embed Author Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure */
/* This is defined at specs/channel.objects.json:141:22 */
struct discord_channel_embed_author_dati {
  /* specs/channel.objects.json:143:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
  char name[EMBED_AUTHOR_NAME_LEN];

  /* specs/channel.objects.json:144:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:145:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char icon_url[MAX_URL_LEN];

  /* specs/channel.objects.json:146:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char proxy_icon_url[MAX_URL_LEN];

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
};
extern void discord_channel_embed_author_dati_cleanup_v(void *p);
extern void discord_channel_embed_author_dati_cleanup(struct discord_channel_embed_author_dati *p);
extern void discord_channel_embed_author_dati_init_v(void *p);
extern void discord_channel_embed_author_dati_init(struct discord_channel_embed_author_dati *p);
extern struct discord_channel_embed_author_dati * discord_channel_embed_author_dati_alloc();
extern void discord_channel_embed_author_dati_free_v(void *p);
extern void discord_channel_embed_author_dati_free(struct discord_channel_embed_author_dati *p);
extern void discord_channel_embed_author_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_embed_author_dati_from_json(char *json, size_t len, struct discord_channel_embed_author_dati *p);
extern size_t discord_channel_embed_author_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_author_dati_to_json(char *json, size_t len, struct discord_channel_embed_author_dati *p);
extern size_t discord_channel_embed_author_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_author_dati_to_query(char *json, size_t len, struct discord_channel_embed_author_dati *p);
extern void discord_channel_embed_author_dati_list_free_v(void **p);
extern void discord_channel_embed_author_dati_list_free(struct discord_channel_embed_author_dati **p);
extern void discord_channel_embed_author_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_embed_author_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_author_dati ***p);
extern size_t discord_channel_embed_author_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_embed_author_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_author_dati **p);

/* Title: Embed Footer Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure */
/* This is defined at specs/channel.objects.json:153:22 */
struct discord_channel_embed_footer_dati {
  /* specs/channel.objects.json:155:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
  char text[EMBED_FOOTER_TEXT_LEN];

  /* specs/channel.objects.json:156:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  char icon_url[MAX_URL_LEN];

  /* specs/channel.objects.json:158:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  char proxy_icon_url[MAX_URL_LEN];

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
extern void discord_channel_embed_footer_dati_cleanup_v(void *p);
extern void discord_channel_embed_footer_dati_cleanup(struct discord_channel_embed_footer_dati *p);
extern void discord_channel_embed_footer_dati_init_v(void *p);
extern void discord_channel_embed_footer_dati_init(struct discord_channel_embed_footer_dati *p);
extern struct discord_channel_embed_footer_dati * discord_channel_embed_footer_dati_alloc();
extern void discord_channel_embed_footer_dati_free_v(void *p);
extern void discord_channel_embed_footer_dati_free(struct discord_channel_embed_footer_dati *p);
extern void discord_channel_embed_footer_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_embed_footer_dati_from_json(char *json, size_t len, struct discord_channel_embed_footer_dati *p);
extern size_t discord_channel_embed_footer_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_footer_dati_to_json(char *json, size_t len, struct discord_channel_embed_footer_dati *p);
extern size_t discord_channel_embed_footer_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_footer_dati_to_query(char *json, size_t len, struct discord_channel_embed_footer_dati *p);
extern void discord_channel_embed_footer_dati_list_free_v(void **p);
extern void discord_channel_embed_footer_dati_list_free(struct discord_channel_embed_footer_dati **p);
extern void discord_channel_embed_footer_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_embed_footer_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_footer_dati ***p);
extern size_t discord_channel_embed_footer_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_embed_footer_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_footer_dati **p);

/* Title: Embed Field Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure */
/* This is defined at specs/channel.objects.json:166:22 */
struct discord_channel_embed_field_dati {
  /* specs/channel.objects.json:168:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
  char name[EMBED_FIELD_NAME_LEN];

  /* specs/channel.objects.json:169:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
  char value[EMBED_FIELD_VALUE_LEN];

  /* specs/channel.objects.json:170:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
  bool Inline;

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
extern void discord_channel_embed_field_dati_cleanup_v(void *p);
extern void discord_channel_embed_field_dati_cleanup(struct discord_channel_embed_field_dati *p);
extern void discord_channel_embed_field_dati_init_v(void *p);
extern void discord_channel_embed_field_dati_init(struct discord_channel_embed_field_dati *p);
extern struct discord_channel_embed_field_dati * discord_channel_embed_field_dati_alloc();
extern void discord_channel_embed_field_dati_free_v(void *p);
extern void discord_channel_embed_field_dati_free(struct discord_channel_embed_field_dati *p);
extern void discord_channel_embed_field_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_embed_field_dati_from_json(char *json, size_t len, struct discord_channel_embed_field_dati *p);
extern size_t discord_channel_embed_field_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_field_dati_to_json(char *json, size_t len, struct discord_channel_embed_field_dati *p);
extern size_t discord_channel_embed_field_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_embed_field_dati_to_query(char *json, size_t len, struct discord_channel_embed_field_dati *p);
extern void discord_channel_embed_field_dati_list_free_v(void **p);
extern void discord_channel_embed_field_dati_list_free(struct discord_channel_embed_field_dati **p);
extern void discord_channel_embed_field_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_embed_field_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_field_dati ***p);
extern size_t discord_channel_embed_field_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_embed_field_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_field_dati **p);
