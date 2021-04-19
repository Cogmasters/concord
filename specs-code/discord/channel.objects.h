/* This file is generated from specs/discord/channel.objects.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#overwrite-object-overwrite-structure
*/

/* Title: Overwrite Structure */
/* This is defined at specs/discord/channel.objects.json:10:22 */
struct discord_channel_overwrite {
  /* specs/discord/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  /* specs/discord/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  enum discord_permissions_bitwise_flags allow; // permission bit set

  /* specs/discord/channel.objects.json:17:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  enum discord_permissions_bitwise_flags deny; // permission bit set

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
extern void discord_channel_overwrite_cleanup_v(void *p);
extern void discord_channel_overwrite_cleanup(struct discord_channel_overwrite *p);
extern void discord_channel_overwrite_init_v(void *p);
extern void discord_channel_overwrite_init(struct discord_channel_overwrite *p);
extern struct discord_channel_overwrite * discord_channel_overwrite_alloc();
extern void discord_channel_overwrite_free_v(void *p);
extern void discord_channel_overwrite_free(struct discord_channel_overwrite *p);
extern void discord_channel_overwrite_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_overwrite_from_json(char *json, size_t len, struct discord_channel_overwrite *p);
extern size_t discord_channel_overwrite_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_overwrite_to_json(char *json, size_t len, struct discord_channel_overwrite *p);
extern size_t discord_channel_overwrite_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_overwrite_to_query(char *json, size_t len, struct discord_channel_overwrite *p);
extern void discord_channel_overwrite_list_free_v(void **p);
extern void discord_channel_overwrite_list_free(struct discord_channel_overwrite **p);
extern void discord_channel_overwrite_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_overwrite_list_from_json(char *str, size_t len, struct discord_channel_overwrite ***p);
extern size_t discord_channel_overwrite_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_overwrite_list_to_json(char *str, size_t len, struct discord_channel_overwrite **p);

/* https://discord.com/developers/docs/resources/channel#reaction-object-reaction-structure */
/* This is defined at specs/discord/channel.objects.json:24:22 */
struct discord_channel_reaction {
  /* specs/discord/channel.objects.json:27:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
  int count;

  /* specs/discord/channel.objects.json:28:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
  bool me;

  /* specs/discord/channel.objects.json:29:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}'
  */
  struct discord_emoji *emoji; // partial emoji object

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
extern void discord_channel_reaction_cleanup_v(void *p);
extern void discord_channel_reaction_cleanup(struct discord_channel_reaction *p);
extern void discord_channel_reaction_init_v(void *p);
extern void discord_channel_reaction_init(struct discord_channel_reaction *p);
extern struct discord_channel_reaction * discord_channel_reaction_alloc();
extern void discord_channel_reaction_free_v(void *p);
extern void discord_channel_reaction_free(struct discord_channel_reaction *p);
extern void discord_channel_reaction_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_reaction_from_json(char *json, size_t len, struct discord_channel_reaction *p);
extern size_t discord_channel_reaction_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_reaction_to_json(char *json, size_t len, struct discord_channel_reaction *p);
extern size_t discord_channel_reaction_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_reaction_to_query(char *json, size_t len, struct discord_channel_reaction *p);
extern void discord_channel_reaction_list_free_v(void **p);
extern void discord_channel_reaction_list_free(struct discord_channel_reaction **p);
extern void discord_channel_reaction_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_reaction_list_from_json(char *str, size_t len, struct discord_channel_reaction ***p);
extern size_t discord_channel_reaction_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_reaction_list_to_json(char *str, size_t len, struct discord_channel_reaction **p);

/* Title: Followed Channel Structure */
/* https://discord.com/developers/docs/resources/channel#followed-channel-object-followed-channel-structure */
/* This is defined at specs/discord/channel.objects.json:36:22 */
struct discord_channel_followed_channel {
  /* specs/discord/channel.objects.json:39:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.objects.json:40:20
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
extern void discord_channel_followed_channel_cleanup_v(void *p);
extern void discord_channel_followed_channel_cleanup(struct discord_channel_followed_channel *p);
extern void discord_channel_followed_channel_init_v(void *p);
extern void discord_channel_followed_channel_init(struct discord_channel_followed_channel *p);
extern struct discord_channel_followed_channel * discord_channel_followed_channel_alloc();
extern void discord_channel_followed_channel_free_v(void *p);
extern void discord_channel_followed_channel_free(struct discord_channel_followed_channel *p);
extern void discord_channel_followed_channel_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_followed_channel_from_json(char *json, size_t len, struct discord_channel_followed_channel *p);
extern size_t discord_channel_followed_channel_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_followed_channel_to_json(char *json, size_t len, struct discord_channel_followed_channel *p);
extern size_t discord_channel_followed_channel_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_followed_channel_to_query(char *json, size_t len, struct discord_channel_followed_channel *p);
extern void discord_channel_followed_channel_list_free_v(void **p);
extern void discord_channel_followed_channel_list_free(struct discord_channel_followed_channel **p);
extern void discord_channel_followed_channel_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_followed_channel_list_from_json(char *str, size_t len, struct discord_channel_followed_channel ***p);
extern size_t discord_channel_followed_channel_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_followed_channel_list_to_json(char *str, size_t len, struct discord_channel_followed_channel **p);

/* https://discord.com/developers/docs/resources/channel#attachment-object */
/* This is defined at specs/discord/channel.objects.json:46:22 */
struct discord_channel_attachment {
  /* specs/discord/channel.objects.json:49:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/channel.objects.json:50:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
  char filename[256];

  /* specs/discord/channel.objects.json:51:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
  int size;

  /* specs/discord/channel.objects.json:52:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  char url[MAX_URL_LEN];

  /* specs/discord/channel.objects.json:53:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/discord/channel.objects.json:54:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
  int height;

  /* specs/discord/channel.objects.json:55:20
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
extern void discord_channel_attachment_cleanup_v(void *p);
extern void discord_channel_attachment_cleanup(struct discord_channel_attachment *p);
extern void discord_channel_attachment_init_v(void *p);
extern void discord_channel_attachment_init(struct discord_channel_attachment *p);
extern struct discord_channel_attachment * discord_channel_attachment_alloc();
extern void discord_channel_attachment_free_v(void *p);
extern void discord_channel_attachment_free(struct discord_channel_attachment *p);
extern void discord_channel_attachment_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_attachment_from_json(char *json, size_t len, struct discord_channel_attachment *p);
extern size_t discord_channel_attachment_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_attachment_to_json(char *json, size_t len, struct discord_channel_attachment *p);
extern size_t discord_channel_attachment_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_attachment_to_query(char *json, size_t len, struct discord_channel_attachment *p);
extern void discord_channel_attachment_list_free_v(void **p);
extern void discord_channel_attachment_list_free(struct discord_channel_attachment **p);
extern void discord_channel_attachment_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_attachment_list_from_json(char *str, size_t len, struct discord_channel_attachment ***p);
extern size_t discord_channel_attachment_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_attachment_list_to_json(char *str, size_t len, struct discord_channel_attachment **p);

/* Title: Channel Mention Structure */
/* https://discord.com/developers/docs/resources/channel#channel-mention-object-channel-mention-structure */
/* This is defined at specs/discord/channel.objects.json:62:22 */
struct discord_channel_mention {
  /* specs/discord/channel.objects.json:65:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/channel.objects.json:66:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.objects.json:67:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}'
  */
  enum discord_channel_types type;

  /* specs/discord/channel.objects.json:68:20
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
extern void discord_channel_mention_cleanup_v(void *p);
extern void discord_channel_mention_cleanup(struct discord_channel_mention *p);
extern void discord_channel_mention_init_v(void *p);
extern void discord_channel_mention_init(struct discord_channel_mention *p);
extern struct discord_channel_mention * discord_channel_mention_alloc();
extern void discord_channel_mention_free_v(void *p);
extern void discord_channel_mention_free(struct discord_channel_mention *p);
extern void discord_channel_mention_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_mention_from_json(char *json, size_t len, struct discord_channel_mention *p);
extern size_t discord_channel_mention_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_mention_to_json(char *json, size_t len, struct discord_channel_mention *p);
extern size_t discord_channel_mention_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_mention_to_query(char *json, size_t len, struct discord_channel_mention *p);
extern void discord_channel_mention_list_free_v(void **p);
extern void discord_channel_mention_list_free(struct discord_channel_mention **p);
extern void discord_channel_mention_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_mention_list_from_json(char *str, size_t len, struct discord_channel_mention ***p);
extern size_t discord_channel_mention_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_mention_list_to_json(char *str, size_t len, struct discord_channel_mention **p);

/* Title: Allowed Mentions Structure */
/* https://discord.com/developers/docs/resources/channel#allowed-mentions-object-allowed-mentions-structure */
/* This is defined at specs/discord/channel.objects.json:75:22 */
struct discord_channel_allowed_mentions {
  /* specs/discord/channel.objects.json:78:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
  ja_str **parse;

  /* specs/discord/channel.objects.json:79:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  ja_u64 **roles; // list of snowflakes

  /* specs/discord/channel.objects.json:80:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  ja_u64 **users; // list of snowflakes

  /* specs/discord/channel.objects.json:81:20
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
extern void discord_channel_allowed_mentions_cleanup_v(void *p);
extern void discord_channel_allowed_mentions_cleanup(struct discord_channel_allowed_mentions *p);
extern void discord_channel_allowed_mentions_init_v(void *p);
extern void discord_channel_allowed_mentions_init(struct discord_channel_allowed_mentions *p);
extern struct discord_channel_allowed_mentions * discord_channel_allowed_mentions_alloc();
extern void discord_channel_allowed_mentions_free_v(void *p);
extern void discord_channel_allowed_mentions_free(struct discord_channel_allowed_mentions *p);
extern void discord_channel_allowed_mentions_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_allowed_mentions_from_json(char *json, size_t len, struct discord_channel_allowed_mentions *p);
extern size_t discord_channel_allowed_mentions_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_allowed_mentions_to_json(char *json, size_t len, struct discord_channel_allowed_mentions *p);
extern size_t discord_channel_allowed_mentions_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_allowed_mentions_to_query(char *json, size_t len, struct discord_channel_allowed_mentions *p);
extern void discord_channel_allowed_mentions_list_free_v(void **p);
extern void discord_channel_allowed_mentions_list_free(struct discord_channel_allowed_mentions **p);
extern void discord_channel_allowed_mentions_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_allowed_mentions_list_from_json(char *str, size_t len, struct discord_channel_allowed_mentions ***p);
extern size_t discord_channel_allowed_mentions_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_allowed_mentions_list_to_json(char *str, size_t len, struct discord_channel_allowed_mentions **p);

/* Title: Embed Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-structure */
/* This is defined at specs/discord/channel.objects.json:87:22 */
struct discord_embed {
  /* specs/discord/channel.objects.json:90:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  char title[EMBED_TITLE_LEN];

  /* specs/discord/channel.objects.json:92:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
  char type[32];

  /* specs/discord/channel.objects.json:94:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  char description[EMBED_DESCRIPTION_LEN];

  /* specs/discord/channel.objects.json:96:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/discord/channel.objects.json:98:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
  u64_unix_ms_t timestamp;

  /* specs/discord/channel.objects.json:100:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
  int color;

  /* specs/discord/channel.objects.json:101:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  struct discord_embed_footer *footer;

  /* specs/discord/channel.objects.json:103:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_embed_image *image;

  /* specs/discord/channel.objects.json:104:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_embed_thumbnail *thumbnail;

  /* specs/discord/channel.objects.json:105:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_embed_video *video;

  /* specs/discord/channel.objects.json:106:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_embed_provider *provider;

  /* specs/discord/channel.objects.json:107:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_embed_author *author;

  /* specs/discord/channel.objects.json:108:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
  struct discord_embed_field **fields;

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
extern void discord_embed_cleanup_v(void *p);
extern void discord_embed_cleanup(struct discord_embed *p);
extern void discord_embed_init_v(void *p);
extern void discord_embed_init(struct discord_embed *p);
extern struct discord_embed * discord_embed_alloc();
extern void discord_embed_free_v(void *p);
extern void discord_embed_free(struct discord_embed *p);
extern void discord_embed_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_from_json(char *json, size_t len, struct discord_embed *p);
extern size_t discord_embed_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_to_json(char *json, size_t len, struct discord_embed *p);
extern size_t discord_embed_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_to_query(char *json, size_t len, struct discord_embed *p);
extern void discord_embed_list_free_v(void **p);
extern void discord_embed_list_free(struct discord_embed **p);
extern void discord_embed_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_list_from_json(char *str, size_t len, struct discord_embed ***p);
extern size_t discord_embed_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_list_to_json(char *str, size_t len, struct discord_embed **p);

/* Title: Embed Thumbnail Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure */
/* This is defined at specs/discord/channel.objects.json:116:22 */
struct discord_embed_thumbnail {
  /* specs/discord/channel.objects.json:118:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/discord/channel.objects.json:119:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/discord/channel.objects.json:120:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/discord/channel.objects.json:121:20
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
extern void discord_embed_thumbnail_cleanup_v(void *p);
extern void discord_embed_thumbnail_cleanup(struct discord_embed_thumbnail *p);
extern void discord_embed_thumbnail_init_v(void *p);
extern void discord_embed_thumbnail_init(struct discord_embed_thumbnail *p);
extern struct discord_embed_thumbnail * discord_embed_thumbnail_alloc();
extern void discord_embed_thumbnail_free_v(void *p);
extern void discord_embed_thumbnail_free(struct discord_embed_thumbnail *p);
extern void discord_embed_thumbnail_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_thumbnail_from_json(char *json, size_t len, struct discord_embed_thumbnail *p);
extern size_t discord_embed_thumbnail_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_thumbnail_to_json(char *json, size_t len, struct discord_embed_thumbnail *p);
extern size_t discord_embed_thumbnail_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_thumbnail_to_query(char *json, size_t len, struct discord_embed_thumbnail *p);
extern void discord_embed_thumbnail_list_free_v(void **p);
extern void discord_embed_thumbnail_list_free(struct discord_embed_thumbnail **p);
extern void discord_embed_thumbnail_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_thumbnail_list_from_json(char *str, size_t len, struct discord_embed_thumbnail ***p);
extern size_t discord_embed_thumbnail_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_thumbnail_list_to_json(char *str, size_t len, struct discord_embed_thumbnail **p);

/* Title: Embed Thumbnail Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-video-structure */
/* This is defined at specs/discord/channel.objects.json:128:22 */
struct discord_embed_video {
  /* specs/discord/channel.objects.json:130:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/discord/channel.objects.json:131:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/discord/channel.objects.json:132:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/discord/channel.objects.json:133:20
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
extern void discord_embed_video_cleanup_v(void *p);
extern void discord_embed_video_cleanup(struct discord_embed_video *p);
extern void discord_embed_video_init_v(void *p);
extern void discord_embed_video_init(struct discord_embed_video *p);
extern struct discord_embed_video * discord_embed_video_alloc();
extern void discord_embed_video_free_v(void *p);
extern void discord_embed_video_free(struct discord_embed_video *p);
extern void discord_embed_video_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_video_from_json(char *json, size_t len, struct discord_embed_video *p);
extern size_t discord_embed_video_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_video_to_json(char *json, size_t len, struct discord_embed_video *p);
extern size_t discord_embed_video_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_video_to_query(char *json, size_t len, struct discord_embed_video *p);
extern void discord_embed_video_list_free_v(void **p);
extern void discord_embed_video_list_free(struct discord_embed_video **p);
extern void discord_embed_video_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_video_list_from_json(char *str, size_t len, struct discord_embed_video ***p);
extern size_t discord_embed_video_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_video_list_to_json(char *str, size_t len, struct discord_embed_video **p);

/* Title: Embed Image Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-image-structure */
/* This is defined at specs/discord/channel.objects.json:140:22 */
struct discord_embed_image {
  /* specs/discord/channel.objects.json:142:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/discord/channel.objects.json:143:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/discord/channel.objects.json:144:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/discord/channel.objects.json:145:20
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
extern void discord_embed_image_cleanup_v(void *p);
extern void discord_embed_image_cleanup(struct discord_embed_image *p);
extern void discord_embed_image_init_v(void *p);
extern void discord_embed_image_init(struct discord_embed_image *p);
extern struct discord_embed_image * discord_embed_image_alloc();
extern void discord_embed_image_free_v(void *p);
extern void discord_embed_image_free(struct discord_embed_image *p);
extern void discord_embed_image_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_image_from_json(char *json, size_t len, struct discord_embed_image *p);
extern size_t discord_embed_image_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_image_to_json(char *json, size_t len, struct discord_embed_image *p);
extern size_t discord_embed_image_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_image_to_query(char *json, size_t len, struct discord_embed_image *p);
extern void discord_embed_image_list_free_v(void **p);
extern void discord_embed_image_list_free(struct discord_embed_image **p);
extern void discord_embed_image_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_image_list_from_json(char *str, size_t len, struct discord_embed_image ***p);
extern size_t discord_embed_image_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_image_list_to_json(char *str, size_t len, struct discord_embed_image **p);

/* Title: Embed Provider Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-provider-structure */
/* This is defined at specs/discord/channel.objects.json:152:22 */
struct discord_embed_provider {
  /* specs/discord/channel.objects.json:154:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
  char name[EMBED_AUTHOR_NAME_LEN];

  /* specs/discord/channel.objects.json:155:20
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
extern void discord_embed_provider_cleanup_v(void *p);
extern void discord_embed_provider_cleanup(struct discord_embed_provider *p);
extern void discord_embed_provider_init_v(void *p);
extern void discord_embed_provider_init(struct discord_embed_provider *p);
extern struct discord_embed_provider * discord_embed_provider_alloc();
extern void discord_embed_provider_free_v(void *p);
extern void discord_embed_provider_free(struct discord_embed_provider *p);
extern void discord_embed_provider_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_provider_from_json(char *json, size_t len, struct discord_embed_provider *p);
extern size_t discord_embed_provider_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_provider_to_json(char *json, size_t len, struct discord_embed_provider *p);
extern size_t discord_embed_provider_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_provider_to_query(char *json, size_t len, struct discord_embed_provider *p);
extern void discord_embed_provider_list_free_v(void **p);
extern void discord_embed_provider_list_free(struct discord_embed_provider **p);
extern void discord_embed_provider_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_provider_list_from_json(char *str, size_t len, struct discord_embed_provider ***p);
extern size_t discord_embed_provider_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_provider_list_to_json(char *str, size_t len, struct discord_embed_provider **p);

/* Title: Embed Author Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure */
/* This is defined at specs/discord/channel.objects.json:162:22 */
struct discord_embed_author {
  /* specs/discord/channel.objects.json:164:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
  char name[EMBED_AUTHOR_NAME_LEN];

  /* specs/discord/channel.objects.json:165:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/discord/channel.objects.json:166:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char icon_url[MAX_URL_LEN];

  /* specs/discord/channel.objects.json:167:20
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
extern void discord_embed_author_cleanup_v(void *p);
extern void discord_embed_author_cleanup(struct discord_embed_author *p);
extern void discord_embed_author_init_v(void *p);
extern void discord_embed_author_init(struct discord_embed_author *p);
extern struct discord_embed_author * discord_embed_author_alloc();
extern void discord_embed_author_free_v(void *p);
extern void discord_embed_author_free(struct discord_embed_author *p);
extern void discord_embed_author_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_author_from_json(char *json, size_t len, struct discord_embed_author *p);
extern size_t discord_embed_author_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_author_to_json(char *json, size_t len, struct discord_embed_author *p);
extern size_t discord_embed_author_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_author_to_query(char *json, size_t len, struct discord_embed_author *p);
extern void discord_embed_author_list_free_v(void **p);
extern void discord_embed_author_list_free(struct discord_embed_author **p);
extern void discord_embed_author_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_author_list_from_json(char *str, size_t len, struct discord_embed_author ***p);
extern size_t discord_embed_author_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_author_list_to_json(char *str, size_t len, struct discord_embed_author **p);

/* Title: Embed Footer Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure */
/* This is defined at specs/discord/channel.objects.json:174:22 */
struct discord_embed_footer {
  /* specs/discord/channel.objects.json:176:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
  char text[EMBED_FOOTER_TEXT_LEN];

  /* specs/discord/channel.objects.json:177:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  char icon_url[MAX_URL_LEN];

  /* specs/discord/channel.objects.json:179:20
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
extern void discord_embed_footer_cleanup_v(void *p);
extern void discord_embed_footer_cleanup(struct discord_embed_footer *p);
extern void discord_embed_footer_init_v(void *p);
extern void discord_embed_footer_init(struct discord_embed_footer *p);
extern struct discord_embed_footer * discord_embed_footer_alloc();
extern void discord_embed_footer_free_v(void *p);
extern void discord_embed_footer_free(struct discord_embed_footer *p);
extern void discord_embed_footer_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_footer_from_json(char *json, size_t len, struct discord_embed_footer *p);
extern size_t discord_embed_footer_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_footer_to_json(char *json, size_t len, struct discord_embed_footer *p);
extern size_t discord_embed_footer_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_footer_to_query(char *json, size_t len, struct discord_embed_footer *p);
extern void discord_embed_footer_list_free_v(void **p);
extern void discord_embed_footer_list_free(struct discord_embed_footer **p);
extern void discord_embed_footer_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_footer_list_from_json(char *str, size_t len, struct discord_embed_footer ***p);
extern size_t discord_embed_footer_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_footer_list_to_json(char *str, size_t len, struct discord_embed_footer **p);

/* Title: Embed Field Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure */
/* This is defined at specs/discord/channel.objects.json:187:22 */
struct discord_embed_field {
  /* specs/discord/channel.objects.json:189:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
  char name[EMBED_FIELD_NAME_LEN];

  /* specs/discord/channel.objects.json:190:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
  char value[EMBED_FIELD_VALUE_LEN];

  /* specs/discord/channel.objects.json:191:20
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
extern void discord_embed_field_cleanup_v(void *p);
extern void discord_embed_field_cleanup(struct discord_embed_field *p);
extern void discord_embed_field_init_v(void *p);
extern void discord_embed_field_init(struct discord_embed_field *p);
extern struct discord_embed_field * discord_embed_field_alloc();
extern void discord_embed_field_free_v(void *p);
extern void discord_embed_field_free(struct discord_embed_field *p);
extern void discord_embed_field_from_json_v(char *json, size_t len, void *p);
extern void discord_embed_field_from_json(char *json, size_t len, struct discord_embed_field *p);
extern size_t discord_embed_field_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_field_to_json(char *json, size_t len, struct discord_embed_field *p);
extern size_t discord_embed_field_to_query_v(char *json, size_t len, void *p);
extern size_t discord_embed_field_to_query(char *json, size_t len, struct discord_embed_field *p);
extern void discord_embed_field_list_free_v(void **p);
extern void discord_embed_field_list_free(struct discord_embed_field **p);
extern void discord_embed_field_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_field_list_from_json(char *str, size_t len, struct discord_embed_field ***p);
extern size_t discord_embed_field_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_field_list_to_json(char *str, size_t len, struct discord_embed_field **p);
