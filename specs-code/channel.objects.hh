/* This file is generated from specs/channel.objects.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#overwrite-object-overwrite-structure
*/

namespace overwrite {
/* Title: Overwrite Structure */
/* This is defined at specs/channel.objects.json:10:22 */
struct dati {
  /* specs/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  /* specs/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"permissions::bitwise_flags"}, "comment":"permission bit set"}'
  */
  permissions::bitwise_flags allow; // permission bit set

  /* specs/channel.objects.json:16:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"permissions::bitwise_flags"}, "comment":"permission bit set"}'
  */
  permissions::bitwise_flags deny; // permission bit set

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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace overwrite

namespace reaction {
/* https://discord.com/developers/docs/resources/channel#reaction-object-reaction-structure */
/* This is defined at specs/channel.objects.json:22:22 */
struct dati {
  /* specs/channel.objects.json:25:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
  int count;

  /* specs/channel.objects.json:26:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
  bool me;

  /* specs/channel.objects.json:27:20
     '{ "name": "emoji", "type":{ "base":"discord::emoji::dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
  discord::emoji::dati *emoji; // partial emoji object

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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace reaction

namespace followed_channel {
/* Title: Followed Channel Structure */
/* https://discord.com/developers/docs/resources/channel#followed-channel-object-followed-channel-structure */
/* This is defined at specs/channel.objects.json:34:22 */
struct dati {
  /* specs/channel.objects.json:37:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t channel_id;

  /* specs/channel.objects.json:38:20
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace followed_channel

namespace attachment {
/* https://discord.com/developers/docs/resources/channel#attachment-object */
/* This is defined at specs/channel.objects.json:44:22 */
struct dati {
  /* specs/channel.objects.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/channel.objects.json:48:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
  char filename[256];

  /* specs/channel.objects.json:49:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
  int size;

  /* specs/channel.objects.json:50:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:51:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/channel.objects.json:52:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
  int height;

  /* specs/channel.objects.json:53:20
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace attachment

namespace mention {
/* Title: Channel Mention Structure */
/* https://discord.com/developers/docs/resources/channel#channel-mention-object-channel-mention-structure */
/* This is defined at specs/channel.objects.json:60:22 */
struct dati {
  /* specs/channel.objects.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/channel.objects.json:64:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t guild_id;

  /* specs/channel.objects.json:65:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::channel::types::code" }}'
  */
  discord::channel::types::code type;

  /* specs/channel.objects.json:66:20
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace mention

namespace allowed_mentions {
/* Title: Allowed Mentions Structure */
/* https://discord.com/developers/docs/resources/channel#allowed-mentions-object-allowed-mentions-structure */
/* This is defined at specs/channel.objects.json:73:22 */
struct dati {
  /* specs/channel.objects.json:76:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
  ja_str **parse;

  /* specs/channel.objects.json:77:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  ja_u64 **roles; // list of snowflakes

  /* specs/channel.objects.json:78:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  ja_u64 **users; // list of snowflakes

  /* specs/channel.objects.json:79:20
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace allowed_mentions

namespace embed {
/* Title: Embed Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-structure */
/* This is defined at specs/channel.objects.json:86:22 */
struct dati {
  /* specs/channel.objects.json:89:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  char title[EMBED_TITLE_LEN];

  /* specs/channel.objects.json:91:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
  char type[32];

  /* specs/channel.objects.json:93:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  char description[EMBED_DESCRIPTION_LEN];

  /* specs/channel.objects.json:95:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:97:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
  u64_unix_ms_t timestamp;

  /* specs/channel.objects.json:99:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
  int color;

  /* specs/channel.objects.json:100:20
     '{ "name": "footer", "type":{ "base":"discord::channel::embed::footer::dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  discord::channel::embed::footer::dati *footer;

  /* specs/channel.objects.json:102:20
     '{ "name": "image", "type":{ "base":"discord::channel::embed::image::dati", "dec":"*"}, "inject_if_not":null}'
  */
  discord::channel::embed::image::dati *image;

  /* specs/channel.objects.json:103:20
     '{ "name": "thumbnail", "type":{ "base":"discord::channel::embed::thumbnail::dati", "dec":"*"}, "inject_if_not":null}'
  */
  discord::channel::embed::thumbnail::dati *thumbnail;

  /* specs/channel.objects.json:104:20
     '{ "name": "video", "type":{ "base":"discord::channel::embed::video::dati", "dec":"*"}, "inject_if_not":null}'
  */
  discord::channel::embed::video::dati *video;

  /* specs/channel.objects.json:105:20
     '{ "name": "provider", "type":{ "base":"discord::channel::embed::provider::dati", "dec":"*"}, "inject_if_not":null}'
  */
  discord::channel::embed::provider::dati *provider;

  /* specs/channel.objects.json:106:20
     '{ "name": "author", "type":{ "base":"discord::channel::embed::author::dati", "dec":"*"}, "inject_if_not":null}'
  */
  discord::channel::embed::author::dati *author;

  /* specs/channel.objects.json:107:20
     '{ "name": "fields", "type":{ "base":"discord::channel::embed::field::dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
  discord::channel::embed::field::dati **fields;

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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace embed

namespace embed {
namespace thumbnail {
/* Title: Embed Thumbnail Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure */
/* This is defined at specs/channel.objects.json:116:22 */
struct dati {
  /* specs/channel.objects.json:118:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:119:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/channel.objects.json:120:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/channel.objects.json:121:20
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace thumbnail
} // namespace embed

namespace embed {
namespace provider {
/* Title: Embed Provider Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-provider-structure */
/* This is defined at specs/channel.objects.json:128:22 */
struct dati {
  /* specs/channel.objects.json:130:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
  char name[EMBED_AUTHOR_NAME_LEN];

  /* specs/channel.objects.json:131:20
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace provider
} // namespace embed

namespace embed {
namespace author {
/* Title: Embed Author Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure */
/* This is defined at specs/channel.objects.json:138:22 */
struct dati {
  /* specs/channel.objects.json:140:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
  char name[EMBED_AUTHOR_NAME_LEN];

  /* specs/channel.objects.json:141:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:142:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char icon_url[MAX_URL_LEN];

  /* specs/channel.objects.json:143:20
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace author
} // namespace embed

namespace embed {
namespace footer {
/* Title: Embed Footer Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure */
/* This is defined at specs/channel.objects.json:150:22 */
struct dati {
  /* specs/channel.objects.json:152:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
  char text[EMBED_FOOTER_TEXT_LEN];

  /* specs/channel.objects.json:153:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  char icon_url[MAX_URL_LEN];

  /* specs/channel.objects.json:155:20
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace footer
} // namespace embed

namespace embed {
namespace field {
/* Title: Embed Field Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure */
/* This is defined at specs/channel.objects.json:163:22 */
struct dati {
  /* specs/channel.objects.json:165:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
  char name[EMBED_FIELD_NAME_LEN];

  /* specs/channel.objects.json:166:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
  char value[EMBED_FIELD_VALUE_LEN];

  /* specs/channel.objects.json:167:20
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
} // namespace field
} // namespace embed
