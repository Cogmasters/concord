/* This file is generated from specs/discord/channel.objects.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/channel#overwrite-object-overwrite-structure
*/


/* This method is disabled at specs/discord/channel.objects.json:9:30 */
void discord_channel_overwrite_from_json_disabled(char *json, size_t len, struct discord_channel_overwrite *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
                "(id):F,"
                "(type):d,"
                "(allow):s_as_hex_uint,"
                "(deny):s_as_hex_uint,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
                orka_strtoull, &p->id,
                &p->type,
                &p->allow,
                &p->deny,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_overwrite_use_default_inject_settings(struct discord_channel_overwrite *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[1] = &p->type;

  /* specs/discord/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  p->__M.arg_switches[2] = &p->allow;

  /* specs/discord/channel.objects.json:17:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  p->__M.arg_switches[3] = &p->deny;

}


/* This method is disabled at specs/discord/channel.objects.json:9:30 */
size_t discord_channel_overwrite_to_json_disabled(char *json, size_t len, struct discord_channel_overwrite *p)
{
  size_t r;
  discord_channel_overwrite_use_default_inject_settings(p);
  r=json_inject(json, len, 
                "(id):|F|,"
                "(type):d,"
                "(allow):s_as_hex_uint,"
                "(deny):s_as_hex_uint,"
                "@arg_switches:b",
                orka_ulltostr, &p->id,
                &p->type,
                &p->allow,
                &p->deny,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_overwrite_cleanup_v(void *p) {
  discord_channel_overwrite_cleanup((struct discord_channel_overwrite *)p);
}

void discord_channel_overwrite_init_v(void *p) {
  discord_channel_overwrite_init((struct discord_channel_overwrite *)p);
}

void discord_channel_overwrite_free_v(void *p) {
 discord_channel_overwrite_free((struct discord_channel_overwrite *)p);
};

void discord_channel_overwrite_from_json_v(char *json, size_t len, void *p) {
 discord_channel_overwrite_from_json(json, len, (struct discord_channel_overwrite*)p);
}

size_t discord_channel_overwrite_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_overwrite_to_json(json, len, (struct discord_channel_overwrite*)p);
}

void discord_channel_overwrite_list_free_v(void **p) {
  discord_channel_overwrite_list_free((struct discord_channel_overwrite**)p);
}

void discord_channel_overwrite_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_overwrite_list_from_json(str, len, (struct discord_channel_overwrite ***)p);
}

size_t discord_channel_overwrite_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_overwrite_list_to_json(str, len, (struct discord_channel_overwrite **)p);
}


void discord_channel_overwrite_cleanup(struct discord_channel_overwrite *d) {
  /* specs/discord/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/discord/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  //p->type is a scalar
  /* specs/discord/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  //p->allow is a scalar
  /* specs/discord/channel.objects.json:17:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  //p->deny is a scalar
}

void discord_channel_overwrite_init(struct discord_channel_overwrite *p) {
  memset(p, 0, sizeof(struct discord_channel_overwrite));
  /* specs/discord/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */

  /* specs/discord/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */

  /* specs/discord/channel.objects.json:17:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */

}
struct discord_channel_overwrite* discord_channel_overwrite_alloc() {
  struct discord_channel_overwrite *p= (struct discord_channel_overwrite*)malloc(sizeof(struct discord_channel_overwrite));
  discord_channel_overwrite_init(p);
  return p;
}

void discord_channel_overwrite_free(struct discord_channel_overwrite *p) {
  discord_channel_overwrite_cleanup(p);
  free(p);
}

void discord_channel_overwrite_list_free(struct discord_channel_overwrite **p) {
  ntl_free((void**)p, (vfvp)discord_channel_overwrite_cleanup);
}

void discord_channel_overwrite_list_from_json(char *str, size_t len, struct discord_channel_overwrite ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_overwrite);
  d.init_elem = discord_channel_overwrite_init_v;
  d.elem_from_buf = discord_channel_overwrite_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_overwrite_list_to_json(char *str, size_t len, struct discord_channel_overwrite **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_overwrite_to_json_v);
}


void discord_channel_reaction_from_json(char *json, size_t len, struct discord_channel_reaction *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:28:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
                "(count):d,"
  /* specs/discord/channel.objects.json:29:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
                "(me):b,"
  /* specs/discord/channel.objects.json:30:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}'
  */
                "(emoji):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:28:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
                &p->count,
  /* specs/discord/channel.objects.json:29:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
                &p->me,
  /* specs/discord/channel.objects.json:30:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}'
  */
                discord_emoji_from_json, p->emoji,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_reaction_use_default_inject_settings(struct discord_channel_reaction *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:28:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[0] = &p->count;

  /* specs/discord/channel.objects.json:29:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[1] = &p->me;

  /* specs/discord/channel.objects.json:30:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}'
  */
  p->__M.arg_switches[2] = p->emoji;

}

size_t discord_channel_reaction_to_json(char *json, size_t len, struct discord_channel_reaction *p)
{
  size_t r;
  discord_channel_reaction_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:28:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
                "(count):d,"
  /* specs/discord/channel.objects.json:29:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
                "(me):b,"
  /* specs/discord/channel.objects.json:30:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}'
  */
                "(emoji):F,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:28:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
                &p->count,
  /* specs/discord/channel.objects.json:29:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
                &p->me,
  /* specs/discord/channel.objects.json:30:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}'
  */
                discord_emoji_to_json, p->emoji,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_reaction_cleanup_v(void *p) {
  discord_channel_reaction_cleanup((struct discord_channel_reaction *)p);
}

void discord_channel_reaction_init_v(void *p) {
  discord_channel_reaction_init((struct discord_channel_reaction *)p);
}

void discord_channel_reaction_free_v(void *p) {
 discord_channel_reaction_free((struct discord_channel_reaction *)p);
};

void discord_channel_reaction_from_json_v(char *json, size_t len, void *p) {
 discord_channel_reaction_from_json(json, len, (struct discord_channel_reaction*)p);
}

size_t discord_channel_reaction_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_reaction_to_json(json, len, (struct discord_channel_reaction*)p);
}

void discord_channel_reaction_list_free_v(void **p) {
  discord_channel_reaction_list_free((struct discord_channel_reaction**)p);
}

void discord_channel_reaction_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_reaction_list_from_json(str, len, (struct discord_channel_reaction ***)p);
}

size_t discord_channel_reaction_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_reaction_list_to_json(str, len, (struct discord_channel_reaction **)p);
}


void discord_channel_reaction_cleanup(struct discord_channel_reaction *d) {
  /* specs/discord/channel.objects.json:28:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
  //p->count is a scalar
  /* specs/discord/channel.objects.json:29:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
  //p->me is a scalar
  /* specs/discord/channel.objects.json:30:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}'
  */
  if (d->emoji)
    discord_emoji_free(d->emoji);
}

void discord_channel_reaction_init(struct discord_channel_reaction *p) {
  memset(p, 0, sizeof(struct discord_channel_reaction));
  /* specs/discord/channel.objects.json:28:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */

  /* specs/discord/channel.objects.json:29:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */

  /* specs/discord/channel.objects.json:30:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}'
  */
  p->emoji = discord_emoji_alloc();

}
struct discord_channel_reaction* discord_channel_reaction_alloc() {
  struct discord_channel_reaction *p= (struct discord_channel_reaction*)malloc(sizeof(struct discord_channel_reaction));
  discord_channel_reaction_init(p);
  return p;
}

void discord_channel_reaction_free(struct discord_channel_reaction *p) {
  discord_channel_reaction_cleanup(p);
  free(p);
}

void discord_channel_reaction_list_free(struct discord_channel_reaction **p) {
  ntl_free((void**)p, (vfvp)discord_channel_reaction_cleanup);
}

void discord_channel_reaction_list_from_json(char *str, size_t len, struct discord_channel_reaction ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_reaction);
  d.init_elem = discord_channel_reaction_init_v;
  d.elem_from_buf = discord_channel_reaction_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_reaction_list_to_json(char *str, size_t len, struct discord_channel_reaction **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_reaction_to_json_v);
}


void discord_thread_metadata_from_json(char *json, size_t len, struct discord_thread_metadata *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:40:20
     '{ "name": "archived", "type":{ "base":"bool" }}'
  */
                "(archived):b,"
  /* specs/discord/channel.objects.json:41:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(archiver_id):F,"
  /* specs/discord/channel.objects.json:42:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}'
  */
                "(auto_archive_duration):d,"
  /* specs/discord/channel.objects.json:43:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(archive_timestamp):F,"
  /* specs/discord/channel.objects.json:44:20
     '{ "name": "locked", "type":{ "base":"bool" }}'
  */
                "(locked):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:40:20
     '{ "name": "archived", "type":{ "base":"bool" }}'
  */
                &p->archived,
  /* specs/discord/channel.objects.json:41:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->archiver_id,
  /* specs/discord/channel.objects.json:42:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}'
  */
                &p->auto_archive_duration,
  /* specs/discord/channel.objects.json:43:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_iso8601_to_unix_ms, &p->archive_timestamp,
  /* specs/discord/channel.objects.json:44:20
     '{ "name": "locked", "type":{ "base":"bool" }}'
  */
                &p->locked,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_thread_metadata_use_default_inject_settings(struct discord_thread_metadata *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:40:20
     '{ "name": "archived", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[0] = &p->archived;

  /* specs/discord/channel.objects.json:41:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[1] = &p->archiver_id;

  /* specs/discord/channel.objects.json:42:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[2] = &p->auto_archive_duration;

  /* specs/discord/channel.objects.json:43:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  p->__M.arg_switches[3] = &p->archive_timestamp;

  /* specs/discord/channel.objects.json:44:20
     '{ "name": "locked", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[4] = &p->locked;

}

size_t discord_thread_metadata_to_json(char *json, size_t len, struct discord_thread_metadata *p)
{
  size_t r;
  discord_thread_metadata_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:40:20
     '{ "name": "archived", "type":{ "base":"bool" }}'
  */
                "(archived):b,"
  /* specs/discord/channel.objects.json:41:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(archiver_id):|F|,"
  /* specs/discord/channel.objects.json:42:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}'
  */
                "(auto_archive_duration):d,"
  /* specs/discord/channel.objects.json:43:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(archive_timestamp):|F|,"
  /* specs/discord/channel.objects.json:44:20
     '{ "name": "locked", "type":{ "base":"bool" }}'
  */
                "(locked):b,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:40:20
     '{ "name": "archived", "type":{ "base":"bool" }}'
  */
                &p->archived,
  /* specs/discord/channel.objects.json:41:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->archiver_id,
  /* specs/discord/channel.objects.json:42:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}'
  */
                &p->auto_archive_duration,
  /* specs/discord/channel.objects.json:43:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_unix_ms_to_iso8601, &p->archive_timestamp,
  /* specs/discord/channel.objects.json:44:20
     '{ "name": "locked", "type":{ "base":"bool" }}'
  */
                &p->locked,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_thread_metadata_cleanup_v(void *p) {
  discord_thread_metadata_cleanup((struct discord_thread_metadata *)p);
}

void discord_thread_metadata_init_v(void *p) {
  discord_thread_metadata_init((struct discord_thread_metadata *)p);
}

void discord_thread_metadata_free_v(void *p) {
 discord_thread_metadata_free((struct discord_thread_metadata *)p);
};

void discord_thread_metadata_from_json_v(char *json, size_t len, void *p) {
 discord_thread_metadata_from_json(json, len, (struct discord_thread_metadata*)p);
}

size_t discord_thread_metadata_to_json_v(char *json, size_t len, void *p) {
  return discord_thread_metadata_to_json(json, len, (struct discord_thread_metadata*)p);
}

void discord_thread_metadata_list_free_v(void **p) {
  discord_thread_metadata_list_free((struct discord_thread_metadata**)p);
}

void discord_thread_metadata_list_from_json_v(char *str, size_t len, void *p) {
  discord_thread_metadata_list_from_json(str, len, (struct discord_thread_metadata ***)p);
}

size_t discord_thread_metadata_list_to_json_v(char *str, size_t len, void *p){
  return discord_thread_metadata_list_to_json(str, len, (struct discord_thread_metadata **)p);
}


void discord_thread_metadata_cleanup(struct discord_thread_metadata *d) {
  /* specs/discord/channel.objects.json:40:20
     '{ "name": "archived", "type":{ "base":"bool" }}'
  */
  //p->archived is a scalar
  /* specs/discord/channel.objects.json:41:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->archiver_id is a scalar
  /* specs/discord/channel.objects.json:42:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}'
  */
  //p->auto_archive_duration is a scalar
  /* specs/discord/channel.objects.json:43:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  //p->archive_timestamp is a scalar
  /* specs/discord/channel.objects.json:44:20
     '{ "name": "locked", "type":{ "base":"bool" }}'
  */
  //p->locked is a scalar
}

void discord_thread_metadata_init(struct discord_thread_metadata *p) {
  memset(p, 0, sizeof(struct discord_thread_metadata));
  /* specs/discord/channel.objects.json:40:20
     '{ "name": "archived", "type":{ "base":"bool" }}'
  */

  /* specs/discord/channel.objects.json:41:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/channel.objects.json:42:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}'
  */

  /* specs/discord/channel.objects.json:43:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */

  /* specs/discord/channel.objects.json:44:20
     '{ "name": "locked", "type":{ "base":"bool" }}'
  */

}
struct discord_thread_metadata* discord_thread_metadata_alloc() {
  struct discord_thread_metadata *p= (struct discord_thread_metadata*)malloc(sizeof(struct discord_thread_metadata));
  discord_thread_metadata_init(p);
  return p;
}

void discord_thread_metadata_free(struct discord_thread_metadata *p) {
  discord_thread_metadata_cleanup(p);
  free(p);
}

void discord_thread_metadata_list_free(struct discord_thread_metadata **p) {
  ntl_free((void**)p, (vfvp)discord_thread_metadata_cleanup);
}

void discord_thread_metadata_list_from_json(char *str, size_t len, struct discord_thread_metadata ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_thread_metadata);
  d.init_elem = discord_thread_metadata_init_v;
  d.elem_from_buf = discord_thread_metadata_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_thread_metadata_list_to_json(char *str, size_t len, struct discord_thread_metadata **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_thread_metadata_to_json_v);
}


void discord_thread_member_from_json(char *json, size_t len, struct discord_thread_member *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:54:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/discord/channel.objects.json:55:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(user_id):F,"
  /* specs/discord/channel.objects.json:56:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(join_timestamp):F,"
  /* specs/discord/channel.objects.json:57:20
     '{ "name": "flags", "type":{ "base":"int" }}'
  */
                "(flags):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:54:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/discord/channel.objects.json:55:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->user_id,
  /* specs/discord/channel.objects.json:56:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_iso8601_to_unix_ms, &p->join_timestamp,
  /* specs/discord/channel.objects.json:57:20
     '{ "name": "flags", "type":{ "base":"int" }}'
  */
                &p->flags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_thread_member_use_default_inject_settings(struct discord_thread_member *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:54:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/channel.objects.json:55:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[1] = &p->user_id;

  /* specs/discord/channel.objects.json:56:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  p->__M.arg_switches[2] = &p->join_timestamp;

  /* specs/discord/channel.objects.json:57:20
     '{ "name": "flags", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[3] = &p->flags;

}

size_t discord_thread_member_to_json(char *json, size_t len, struct discord_thread_member *p)
{
  size_t r;
  discord_thread_member_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:54:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/discord/channel.objects.json:55:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(user_id):|F|,"
  /* specs/discord/channel.objects.json:56:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(join_timestamp):|F|,"
  /* specs/discord/channel.objects.json:57:20
     '{ "name": "flags", "type":{ "base":"int" }}'
  */
                "(flags):d,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:54:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/discord/channel.objects.json:55:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->user_id,
  /* specs/discord/channel.objects.json:56:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_unix_ms_to_iso8601, &p->join_timestamp,
  /* specs/discord/channel.objects.json:57:20
     '{ "name": "flags", "type":{ "base":"int" }}'
  */
                &p->flags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_thread_member_cleanup_v(void *p) {
  discord_thread_member_cleanup((struct discord_thread_member *)p);
}

void discord_thread_member_init_v(void *p) {
  discord_thread_member_init((struct discord_thread_member *)p);
}

void discord_thread_member_free_v(void *p) {
 discord_thread_member_free((struct discord_thread_member *)p);
};

void discord_thread_member_from_json_v(char *json, size_t len, void *p) {
 discord_thread_member_from_json(json, len, (struct discord_thread_member*)p);
}

size_t discord_thread_member_to_json_v(char *json, size_t len, void *p) {
  return discord_thread_member_to_json(json, len, (struct discord_thread_member*)p);
}

void discord_thread_member_list_free_v(void **p) {
  discord_thread_member_list_free((struct discord_thread_member**)p);
}

void discord_thread_member_list_from_json_v(char *str, size_t len, void *p) {
  discord_thread_member_list_from_json(str, len, (struct discord_thread_member ***)p);
}

size_t discord_thread_member_list_to_json_v(char *str, size_t len, void *p){
  return discord_thread_member_list_to_json(str, len, (struct discord_thread_member **)p);
}


void discord_thread_member_cleanup(struct discord_thread_member *d) {
  /* specs/discord/channel.objects.json:54:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/discord/channel.objects.json:55:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->user_id is a scalar
  /* specs/discord/channel.objects.json:56:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  //p->join_timestamp is a scalar
  /* specs/discord/channel.objects.json:57:20
     '{ "name": "flags", "type":{ "base":"int" }}'
  */
  //p->flags is a scalar
}

void discord_thread_member_init(struct discord_thread_member *p) {
  memset(p, 0, sizeof(struct discord_thread_member));
  /* specs/discord/channel.objects.json:54:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/channel.objects.json:55:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/channel.objects.json:56:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */

  /* specs/discord/channel.objects.json:57:20
     '{ "name": "flags", "type":{ "base":"int" }}'
  */

}
struct discord_thread_member* discord_thread_member_alloc() {
  struct discord_thread_member *p= (struct discord_thread_member*)malloc(sizeof(struct discord_thread_member));
  discord_thread_member_init(p);
  return p;
}

void discord_thread_member_free(struct discord_thread_member *p) {
  discord_thread_member_cleanup(p);
  free(p);
}

void discord_thread_member_list_free(struct discord_thread_member **p) {
  ntl_free((void**)p, (vfvp)discord_thread_member_cleanup);
}

void discord_thread_member_list_from_json(char *str, size_t len, struct discord_thread_member ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_thread_member);
  d.init_elem = discord_thread_member_init_v;
  d.elem_from_buf = discord_thread_member_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_thread_member_list_to_json(char *str, size_t len, struct discord_thread_member **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_thread_member_to_json_v);
}


void discord_channel_followed_channel_from_json(char *json, size_t len, struct discord_channel_followed_channel *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:67:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(channel_id):F,"
  /* specs/discord/channel.objects.json:68:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(webhook_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:67:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->channel_id,
  /* specs/discord/channel.objects.json:68:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->webhook_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_followed_channel_use_default_inject_settings(struct discord_channel_followed_channel *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:67:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->channel_id;

  /* specs/discord/channel.objects.json:68:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[1] = &p->webhook_id;

}

size_t discord_channel_followed_channel_to_json(char *json, size_t len, struct discord_channel_followed_channel *p)
{
  size_t r;
  discord_channel_followed_channel_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:67:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(channel_id):|F|,"
  /* specs/discord/channel.objects.json:68:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(webhook_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:67:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->channel_id,
  /* specs/discord/channel.objects.json:68:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->webhook_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_followed_channel_cleanup_v(void *p) {
  discord_channel_followed_channel_cleanup((struct discord_channel_followed_channel *)p);
}

void discord_channel_followed_channel_init_v(void *p) {
  discord_channel_followed_channel_init((struct discord_channel_followed_channel *)p);
}

void discord_channel_followed_channel_free_v(void *p) {
 discord_channel_followed_channel_free((struct discord_channel_followed_channel *)p);
};

void discord_channel_followed_channel_from_json_v(char *json, size_t len, void *p) {
 discord_channel_followed_channel_from_json(json, len, (struct discord_channel_followed_channel*)p);
}

size_t discord_channel_followed_channel_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_followed_channel_to_json(json, len, (struct discord_channel_followed_channel*)p);
}

void discord_channel_followed_channel_list_free_v(void **p) {
  discord_channel_followed_channel_list_free((struct discord_channel_followed_channel**)p);
}

void discord_channel_followed_channel_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_followed_channel_list_from_json(str, len, (struct discord_channel_followed_channel ***)p);
}

size_t discord_channel_followed_channel_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_followed_channel_list_to_json(str, len, (struct discord_channel_followed_channel **)p);
}


void discord_channel_followed_channel_cleanup(struct discord_channel_followed_channel *d) {
  /* specs/discord/channel.objects.json:67:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->channel_id is a scalar
  /* specs/discord/channel.objects.json:68:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->webhook_id is a scalar
}

void discord_channel_followed_channel_init(struct discord_channel_followed_channel *p) {
  memset(p, 0, sizeof(struct discord_channel_followed_channel));
  /* specs/discord/channel.objects.json:67:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/channel.objects.json:68:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

}
struct discord_channel_followed_channel* discord_channel_followed_channel_alloc() {
  struct discord_channel_followed_channel *p= (struct discord_channel_followed_channel*)malloc(sizeof(struct discord_channel_followed_channel));
  discord_channel_followed_channel_init(p);
  return p;
}

void discord_channel_followed_channel_free(struct discord_channel_followed_channel *p) {
  discord_channel_followed_channel_cleanup(p);
  free(p);
}

void discord_channel_followed_channel_list_free(struct discord_channel_followed_channel **p) {
  ntl_free((void**)p, (vfvp)discord_channel_followed_channel_cleanup);
}

void discord_channel_followed_channel_list_from_json(char *str, size_t len, struct discord_channel_followed_channel ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_followed_channel);
  d.init_elem = discord_channel_followed_channel_init_v;
  d.elem_from_buf = discord_channel_followed_channel_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_followed_channel_list_to_json(char *str, size_t len, struct discord_channel_followed_channel **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_followed_channel_to_json_v);
}


void discord_channel_attachment_from_json(char *json, size_t len, struct discord_channel_attachment *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:77:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/discord/channel.objects.json:78:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
                "(filename):s,"
  /* specs/discord/channel.objects.json:79:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
                "(size):d,"
  /* specs/discord/channel.objects.json:80:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}'
  */
                "(url):?s,"
  /* specs/discord/channel.objects.json:81:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}'
  */
                "(proxy_url):?s,"
  /* specs/discord/channel.objects.json:82:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
                "(height):d,"
  /* specs/discord/channel.objects.json:83:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:77:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/discord/channel.objects.json:78:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
                p->filename,
  /* specs/discord/channel.objects.json:79:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
                &p->size,
  /* specs/discord/channel.objects.json:80:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->url,
  /* specs/discord/channel.objects.json:81:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->proxy_url,
  /* specs/discord/channel.objects.json:82:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
                &p->height,
  /* specs/discord/channel.objects.json:83:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_attachment_use_default_inject_settings(struct discord_channel_attachment *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:77:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/channel.objects.json:78:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
  p->__M.arg_switches[1] = p->filename;

  /* specs/discord/channel.objects.json:79:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[2] = &p->size;

  /* specs/discord/channel.objects.json:80:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[3] = p->url;

  /* specs/discord/channel.objects.json:81:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[4] = p->proxy_url;

  /* specs/discord/channel.objects.json:82:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
  p->__M.arg_switches[5] = &p->height;

  /* specs/discord/channel.objects.json:83:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
  p->__M.arg_switches[6] = &p->width;

}

size_t discord_channel_attachment_to_json(char *json, size_t len, struct discord_channel_attachment *p)
{
  size_t r;
  discord_channel_attachment_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:77:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/discord/channel.objects.json:78:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
                "(filename):s,"
  /* specs/discord/channel.objects.json:79:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
                "(size):d,"
  /* specs/discord/channel.objects.json:80:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}'
  */
                "(url):s,"
  /* specs/discord/channel.objects.json:81:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}'
  */
                "(proxy_url):s,"
  /* specs/discord/channel.objects.json:82:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
                "(height):d,"
  /* specs/discord/channel.objects.json:83:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
                "(width):d,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:77:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/discord/channel.objects.json:78:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
                p->filename,
  /* specs/discord/channel.objects.json:79:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
                &p->size,
  /* specs/discord/channel.objects.json:80:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}'
  */
                p->url,
  /* specs/discord/channel.objects.json:81:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}'
  */
                p->proxy_url,
  /* specs/discord/channel.objects.json:82:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
                &p->height,
  /* specs/discord/channel.objects.json:83:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_attachment_cleanup_v(void *p) {
  discord_channel_attachment_cleanup((struct discord_channel_attachment *)p);
}

void discord_channel_attachment_init_v(void *p) {
  discord_channel_attachment_init((struct discord_channel_attachment *)p);
}

void discord_channel_attachment_free_v(void *p) {
 discord_channel_attachment_free((struct discord_channel_attachment *)p);
};

void discord_channel_attachment_from_json_v(char *json, size_t len, void *p) {
 discord_channel_attachment_from_json(json, len, (struct discord_channel_attachment*)p);
}

size_t discord_channel_attachment_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_attachment_to_json(json, len, (struct discord_channel_attachment*)p);
}

void discord_channel_attachment_list_free_v(void **p) {
  discord_channel_attachment_list_free((struct discord_channel_attachment**)p);
}

void discord_channel_attachment_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_attachment_list_from_json(str, len, (struct discord_channel_attachment ***)p);
}

size_t discord_channel_attachment_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_attachment_list_to_json(str, len, (struct discord_channel_attachment **)p);
}


void discord_channel_attachment_cleanup(struct discord_channel_attachment *d) {
  /* specs/discord/channel.objects.json:77:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/discord/channel.objects.json:78:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
  //p->filename is a scalar
  /* specs/discord/channel.objects.json:79:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
  //p->size is a scalar
  /* specs/discord/channel.objects.json:80:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->url)
    free(d->url);
  /* specs/discord/channel.objects.json:81:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->proxy_url)
    free(d->proxy_url);
  /* specs/discord/channel.objects.json:82:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
  //p->height is a scalar
  /* specs/discord/channel.objects.json:83:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
  //p->width is a scalar
}

void discord_channel_attachment_init(struct discord_channel_attachment *p) {
  memset(p, 0, sizeof(struct discord_channel_attachment));
  /* specs/discord/channel.objects.json:77:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/channel.objects.json:78:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */

  /* specs/discord/channel.objects.json:79:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */

  /* specs/discord/channel.objects.json:80:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/discord/channel.objects.json:81:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/discord/channel.objects.json:82:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */

  /* specs/discord/channel.objects.json:83:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */

}
struct discord_channel_attachment* discord_channel_attachment_alloc() {
  struct discord_channel_attachment *p= (struct discord_channel_attachment*)malloc(sizeof(struct discord_channel_attachment));
  discord_channel_attachment_init(p);
  return p;
}

void discord_channel_attachment_free(struct discord_channel_attachment *p) {
  discord_channel_attachment_cleanup(p);
  free(p);
}

void discord_channel_attachment_list_free(struct discord_channel_attachment **p) {
  ntl_free((void**)p, (vfvp)discord_channel_attachment_cleanup);
}

void discord_channel_attachment_list_from_json(char *str, size_t len, struct discord_channel_attachment ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_attachment);
  d.init_elem = discord_channel_attachment_init_v;
  d.elem_from_buf = discord_channel_attachment_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_attachment_list_to_json(char *str, size_t len, struct discord_channel_attachment **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_attachment_to_json_v);
}


void discord_channel_mention_from_json(char *json, size_t len, struct discord_channel_mention *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:93:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/discord/channel.objects.json:94:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(guild_id):F,"
  /* specs/discord/channel.objects.json:95:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}'
  */
                "(type):d,"
  /* specs/discord/channel.objects.json:96:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:93:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/discord/channel.objects.json:94:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->guild_id,
  /* specs/discord/channel.objects.json:95:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}'
  */
                &p->type,
  /* specs/discord/channel.objects.json:96:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_mention_use_default_inject_settings(struct discord_channel_mention *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:93:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/channel.objects.json:94:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[1] = &p->guild_id;

  /* specs/discord/channel.objects.json:95:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}'
  */
  p->__M.arg_switches[2] = &p->type;

  /* specs/discord/channel.objects.json:96:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[3] = p->name;

}

size_t discord_channel_mention_to_json(char *json, size_t len, struct discord_channel_mention *p)
{
  size_t r;
  discord_channel_mention_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:93:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/discord/channel.objects.json:94:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(guild_id):|F|,"
  /* specs/discord/channel.objects.json:95:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}'
  */
                "(type):d,"
  /* specs/discord/channel.objects.json:96:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):s,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:93:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/discord/channel.objects.json:94:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->guild_id,
  /* specs/discord/channel.objects.json:95:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}'
  */
                &p->type,
  /* specs/discord/channel.objects.json:96:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_mention_cleanup_v(void *p) {
  discord_channel_mention_cleanup((struct discord_channel_mention *)p);
}

void discord_channel_mention_init_v(void *p) {
  discord_channel_mention_init((struct discord_channel_mention *)p);
}

void discord_channel_mention_free_v(void *p) {
 discord_channel_mention_free((struct discord_channel_mention *)p);
};

void discord_channel_mention_from_json_v(char *json, size_t len, void *p) {
 discord_channel_mention_from_json(json, len, (struct discord_channel_mention*)p);
}

size_t discord_channel_mention_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_mention_to_json(json, len, (struct discord_channel_mention*)p);
}

void discord_channel_mention_list_free_v(void **p) {
  discord_channel_mention_list_free((struct discord_channel_mention**)p);
}

void discord_channel_mention_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_mention_list_from_json(str, len, (struct discord_channel_mention ***)p);
}

size_t discord_channel_mention_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_mention_list_to_json(str, len, (struct discord_channel_mention **)p);
}


void discord_channel_mention_cleanup(struct discord_channel_mention *d) {
  /* specs/discord/channel.objects.json:93:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/discord/channel.objects.json:94:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->guild_id is a scalar
  /* specs/discord/channel.objects.json:95:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}'
  */
  //p->type is a scalar
  /* specs/discord/channel.objects.json:96:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->name)
    free(d->name);
}

void discord_channel_mention_init(struct discord_channel_mention *p) {
  memset(p, 0, sizeof(struct discord_channel_mention));
  /* specs/discord/channel.objects.json:93:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/channel.objects.json:94:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/channel.objects.json:95:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}'
  */

  /* specs/discord/channel.objects.json:96:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */

}
struct discord_channel_mention* discord_channel_mention_alloc() {
  struct discord_channel_mention *p= (struct discord_channel_mention*)malloc(sizeof(struct discord_channel_mention));
  discord_channel_mention_init(p);
  return p;
}

void discord_channel_mention_free(struct discord_channel_mention *p) {
  discord_channel_mention_cleanup(p);
  free(p);
}

void discord_channel_mention_list_free(struct discord_channel_mention **p) {
  ntl_free((void**)p, (vfvp)discord_channel_mention_cleanup);
}

void discord_channel_mention_list_from_json(char *str, size_t len, struct discord_channel_mention ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_mention);
  d.init_elem = discord_channel_mention_init_v;
  d.elem_from_buf = discord_channel_mention_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_mention_list_to_json(char *str, size_t len, struct discord_channel_mention **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_mention_to_json_v);
}


void discord_channel_allowed_mentions_from_json(char *json, size_t len, struct discord_channel_allowed_mentions *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:106:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
                "(parse):F,"
  /* specs/discord/channel.objects.json:107:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                "(roles):F,"
  /* specs/discord/channel.objects.json:108:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                "(users):F,"
  /* specs/discord/channel.objects.json:109:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
                "(replied_user):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:106:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
                ja_str_list_from_json, &p->parse,
  /* specs/discord/channel.objects.json:107:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                ja_u64_list_from_json, &p->roles,
  /* specs/discord/channel.objects.json:108:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                ja_u64_list_from_json, &p->users,
  /* specs/discord/channel.objects.json:109:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
                &p->replied_user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_allowed_mentions_use_default_inject_settings(struct discord_channel_allowed_mentions *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:106:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
  p->__M.arg_switches[0] = p->parse;

  /* specs/discord/channel.objects.json:107:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  p->__M.arg_switches[1] = p->roles;

  /* specs/discord/channel.objects.json:108:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  p->__M.arg_switches[2] = p->users;

  /* specs/discord/channel.objects.json:109:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[3] = &p->replied_user;

}

size_t discord_channel_allowed_mentions_to_json(char *json, size_t len, struct discord_channel_allowed_mentions *p)
{
  size_t r;
  discord_channel_allowed_mentions_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:106:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
                "(parse):F,"
  /* specs/discord/channel.objects.json:107:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                "(roles):F,"
  /* specs/discord/channel.objects.json:108:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                "(users):F,"
  /* specs/discord/channel.objects.json:109:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
                "(replied_user):b,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:106:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
                ja_str_list_to_json, p->parse,
  /* specs/discord/channel.objects.json:107:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                ja_u64_list_to_json, p->roles,
  /* specs/discord/channel.objects.json:108:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                ja_u64_list_to_json, p->users,
  /* specs/discord/channel.objects.json:109:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
                &p->replied_user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_allowed_mentions_cleanup_v(void *p) {
  discord_channel_allowed_mentions_cleanup((struct discord_channel_allowed_mentions *)p);
}

void discord_channel_allowed_mentions_init_v(void *p) {
  discord_channel_allowed_mentions_init((struct discord_channel_allowed_mentions *)p);
}

void discord_channel_allowed_mentions_free_v(void *p) {
 discord_channel_allowed_mentions_free((struct discord_channel_allowed_mentions *)p);
};

void discord_channel_allowed_mentions_from_json_v(char *json, size_t len, void *p) {
 discord_channel_allowed_mentions_from_json(json, len, (struct discord_channel_allowed_mentions*)p);
}

size_t discord_channel_allowed_mentions_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_allowed_mentions_to_json(json, len, (struct discord_channel_allowed_mentions*)p);
}

void discord_channel_allowed_mentions_list_free_v(void **p) {
  discord_channel_allowed_mentions_list_free((struct discord_channel_allowed_mentions**)p);
}

void discord_channel_allowed_mentions_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_allowed_mentions_list_from_json(str, len, (struct discord_channel_allowed_mentions ***)p);
}

size_t discord_channel_allowed_mentions_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_allowed_mentions_list_to_json(str, len, (struct discord_channel_allowed_mentions **)p);
}


void discord_channel_allowed_mentions_cleanup(struct discord_channel_allowed_mentions *d) {
  /* specs/discord/channel.objects.json:106:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
  if (d->parse)
    ja_str_list_free(d->parse);
  /* specs/discord/channel.objects.json:107:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* specs/discord/channel.objects.json:108:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  if (d->users)
    ja_u64_list_free(d->users);
  /* specs/discord/channel.objects.json:109:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
  //p->replied_user is a scalar
}

void discord_channel_allowed_mentions_init(struct discord_channel_allowed_mentions *p) {
  memset(p, 0, sizeof(struct discord_channel_allowed_mentions));
  /* specs/discord/channel.objects.json:106:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */

  /* specs/discord/channel.objects.json:107:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */

  /* specs/discord/channel.objects.json:108:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */

  /* specs/discord/channel.objects.json:109:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */

}
struct discord_channel_allowed_mentions* discord_channel_allowed_mentions_alloc() {
  struct discord_channel_allowed_mentions *p= (struct discord_channel_allowed_mentions*)malloc(sizeof(struct discord_channel_allowed_mentions));
  discord_channel_allowed_mentions_init(p);
  return p;
}

void discord_channel_allowed_mentions_free(struct discord_channel_allowed_mentions *p) {
  discord_channel_allowed_mentions_cleanup(p);
  free(p);
}

void discord_channel_allowed_mentions_list_free(struct discord_channel_allowed_mentions **p) {
  ntl_free((void**)p, (vfvp)discord_channel_allowed_mentions_cleanup);
}

void discord_channel_allowed_mentions_list_from_json(char *str, size_t len, struct discord_channel_allowed_mentions ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_allowed_mentions);
  d.init_elem = discord_channel_allowed_mentions_init_v;
  d.elem_from_buf = discord_channel_allowed_mentions_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_allowed_mentions_list_to_json(char *str, size_t len, struct discord_channel_allowed_mentions **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_allowed_mentions_to_json_v);
}


void discord_embed_from_json(char *json, size_t len, struct discord_embed *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:118:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(title):s,"
  /* specs/discord/channel.objects.json:120:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(type):s,"
  /* specs/discord/channel.objects.json:122:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                "(description):s,"
  /* specs/discord/channel.objects.json:124:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"},
          "option":true, "inject_if_not":""}'
  */
                "(url):?s,"
  /* specs/discord/channel.objects.json:126:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
                "(timestamp):F,"
  /* specs/discord/channel.objects.json:128:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
                "(color):d,"
  /* specs/discord/channel.objects.json:129:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(footer):F,"
  /* specs/discord/channel.objects.json:131:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}'
  */
                "(image):F,"
  /* specs/discord/channel.objects.json:132:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}'
  */
                "(thumbnail):F,"
  /* specs/discord/channel.objects.json:133:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}'
  */
                "(video):F,"
  /* specs/discord/channel.objects.json:134:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}'
  */
                "(provider):F,"
  /* specs/discord/channel.objects.json:135:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}'
  */
                "(author):F,"
  /* specs/discord/channel.objects.json:136:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
                "(fields):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:118:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->title,
  /* specs/discord/channel.objects.json:120:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->type,
  /* specs/discord/channel.objects.json:122:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                p->description,
  /* specs/discord/channel.objects.json:124:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"},
          "option":true, "inject_if_not":""}'
  */
                &p->url,
  /* specs/discord/channel.objects.json:126:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
                orka_iso8601_to_unix_ms, &p->timestamp,
  /* specs/discord/channel.objects.json:128:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
                &p->color,
  /* specs/discord/channel.objects.json:129:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                discord_embed_footer_from_json, p->footer,
  /* specs/discord/channel.objects.json:131:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}'
  */
                discord_embed_image_from_json, p->image,
  /* specs/discord/channel.objects.json:132:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}'
  */
                discord_embed_thumbnail_from_json, p->thumbnail,
  /* specs/discord/channel.objects.json:133:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}'
  */
                discord_embed_video_from_json, p->video,
  /* specs/discord/channel.objects.json:134:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}'
  */
                discord_embed_provider_from_json, p->provider,
  /* specs/discord/channel.objects.json:135:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}'
  */
                discord_embed_author_from_json, p->author,
  /* specs/discord/channel.objects.json:136:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
                discord_embed_field_list_from_json, &p->fields,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_use_default_inject_settings(struct discord_embed *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:118:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->title) != 0)
    p->__M.arg_switches[0] = p->title;

  /* specs/discord/channel.objects.json:120:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->type) != 0)
    p->__M.arg_switches[1] = p->type;

  /* specs/discord/channel.objects.json:122:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->description) != 0)
    p->__M.arg_switches[2] = p->description;

  /* specs/discord/channel.objects.json:124:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"},
          "option":true, "inject_if_not":""}'
  */
  if (p->url != NULL && strlen(p->url) != 0)
    p->__M.arg_switches[3] = p->url;

  /* specs/discord/channel.objects.json:126:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
  if (p->timestamp != 0)
    p->__M.arg_switches[4] = &p->timestamp;

  /* specs/discord/channel.objects.json:128:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
  if (p->color != 0)
    p->__M.arg_switches[5] = &p->color;

  /* specs/discord/channel.objects.json:129:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (p->footer != NULL)
    p->__M.arg_switches[6] = p->footer;

  /* specs/discord/channel.objects.json:131:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->image != NULL)
    p->__M.arg_switches[7] = p->image;

  /* specs/discord/channel.objects.json:132:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->thumbnail != NULL)
    p->__M.arg_switches[8] = p->thumbnail;

  /* specs/discord/channel.objects.json:133:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->video != NULL)
    p->__M.arg_switches[9] = p->video;

  /* specs/discord/channel.objects.json:134:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->provider != NULL)
    p->__M.arg_switches[10] = p->provider;

  /* specs/discord/channel.objects.json:135:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->author != NULL)
    p->__M.arg_switches[11] = p->author;

  /* specs/discord/channel.objects.json:136:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
  if (p->fields != NULL)
    p->__M.arg_switches[12] = p->fields;

}

size_t discord_embed_to_json(char *json, size_t len, struct discord_embed *p)
{
  size_t r;
  discord_embed_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:118:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(title):s,"
  /* specs/discord/channel.objects.json:120:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(type):s,"
  /* specs/discord/channel.objects.json:122:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                "(description):s,"
  /* specs/discord/channel.objects.json:124:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"},
          "option":true, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/discord/channel.objects.json:126:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
                "(timestamp):|F|,"
  /* specs/discord/channel.objects.json:128:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
                "(color):d,"
  /* specs/discord/channel.objects.json:129:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(footer):F,"
  /* specs/discord/channel.objects.json:131:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}'
  */
                "(image):F,"
  /* specs/discord/channel.objects.json:132:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}'
  */
                "(thumbnail):F,"
  /* specs/discord/channel.objects.json:133:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}'
  */
                "(video):F,"
  /* specs/discord/channel.objects.json:134:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}'
  */
                "(provider):F,"
  /* specs/discord/channel.objects.json:135:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}'
  */
                "(author):F,"
  /* specs/discord/channel.objects.json:136:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
                "(fields):F,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:118:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->title,
  /* specs/discord/channel.objects.json:120:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->type,
  /* specs/discord/channel.objects.json:122:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                p->description,
  /* specs/discord/channel.objects.json:124:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"},
          "option":true, "inject_if_not":""}'
  */
                p->url,
  /* specs/discord/channel.objects.json:126:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
                orka_unix_ms_to_iso8601, &p->timestamp,
  /* specs/discord/channel.objects.json:128:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
                &p->color,
  /* specs/discord/channel.objects.json:129:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                discord_embed_footer_to_json, p->footer,
  /* specs/discord/channel.objects.json:131:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}'
  */
                discord_embed_image_to_json, p->image,
  /* specs/discord/channel.objects.json:132:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}'
  */
                discord_embed_thumbnail_to_json, p->thumbnail,
  /* specs/discord/channel.objects.json:133:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}'
  */
                discord_embed_video_to_json, p->video,
  /* specs/discord/channel.objects.json:134:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}'
  */
                discord_embed_provider_to_json, p->provider,
  /* specs/discord/channel.objects.json:135:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}'
  */
                discord_embed_author_to_json, p->author,
  /* specs/discord/channel.objects.json:136:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
                discord_embed_field_list_to_json, p->fields,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_cleanup_v(void *p) {
  discord_embed_cleanup((struct discord_embed *)p);
}

void discord_embed_init_v(void *p) {
  discord_embed_init((struct discord_embed *)p);
}

void discord_embed_free_v(void *p) {
 discord_embed_free((struct discord_embed *)p);
};

void discord_embed_from_json_v(char *json, size_t len, void *p) {
 discord_embed_from_json(json, len, (struct discord_embed*)p);
}

size_t discord_embed_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_to_json(json, len, (struct discord_embed*)p);
}

void discord_embed_list_free_v(void **p) {
  discord_embed_list_free((struct discord_embed**)p);
}

void discord_embed_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_list_from_json(str, len, (struct discord_embed ***)p);
}

size_t discord_embed_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_list_to_json(str, len, (struct discord_embed **)p);
}


void discord_embed_cleanup(struct discord_embed *d) {
  /* specs/discord/channel.objects.json:118:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  //p->title is a scalar
  /* specs/discord/channel.objects.json:120:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
  //p->type is a scalar
  /* specs/discord/channel.objects.json:122:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  //p->description is a scalar
  /* specs/discord/channel.objects.json:124:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"},
          "option":true, "inject_if_not":""}'
  */
  if (d->url)
    free(d->url);
  /* specs/discord/channel.objects.json:126:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
  //p->timestamp is a scalar
  /* specs/discord/channel.objects.json:128:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
  //p->color is a scalar
  /* specs/discord/channel.objects.json:129:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (d->footer)
    discord_embed_footer_free(d->footer);
  /* specs/discord/channel.objects.json:131:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->image)
    discord_embed_image_free(d->image);
  /* specs/discord/channel.objects.json:132:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->thumbnail)
    discord_embed_thumbnail_free(d->thumbnail);
  /* specs/discord/channel.objects.json:133:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->video)
    discord_embed_video_free(d->video);
  /* specs/discord/channel.objects.json:134:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->provider)
    discord_embed_provider_free(d->provider);
  /* specs/discord/channel.objects.json:135:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->author)
    discord_embed_author_free(d->author);
  /* specs/discord/channel.objects.json:136:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
  if (d->fields)
    discord_embed_field_list_free(d->fields);
}

void discord_embed_init(struct discord_embed *p) {
  memset(p, 0, sizeof(struct discord_embed));
  /* specs/discord/channel.objects.json:118:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:120:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:122:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:124:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"},
          "option":true, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:126:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */

  /* specs/discord/channel.objects.json:128:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */

  /* specs/discord/channel.objects.json:129:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  p->footer = discord_embed_footer_alloc();

  /* specs/discord/channel.objects.json:131:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}'
  */
  p->image = discord_embed_image_alloc();

  /* specs/discord/channel.objects.json:132:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}'
  */
  p->thumbnail = discord_embed_thumbnail_alloc();

  /* specs/discord/channel.objects.json:133:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}'
  */
  p->video = discord_embed_video_alloc();

  /* specs/discord/channel.objects.json:134:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}'
  */
  p->provider = discord_embed_provider_alloc();

  /* specs/discord/channel.objects.json:135:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}'
  */
  p->author = discord_embed_author_alloc();

  /* specs/discord/channel.objects.json:136:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */

}
struct discord_embed* discord_embed_alloc() {
  struct discord_embed *p= (struct discord_embed*)malloc(sizeof(struct discord_embed));
  discord_embed_init(p);
  return p;
}

void discord_embed_free(struct discord_embed *p) {
  discord_embed_cleanup(p);
  free(p);
}

void discord_embed_list_free(struct discord_embed **p) {
  ntl_free((void**)p, (vfvp)discord_embed_cleanup);
}

void discord_embed_list_from_json(char *str, size_t len, struct discord_embed ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed);
  d.init_elem = discord_embed_init_v;
  d.elem_from_buf = discord_embed_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_embed_list_to_json(char *str, size_t len, struct discord_embed **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_to_json_v);
}


void discord_embed_thumbnail_from_json(char *json, size_t len, struct discord_embed_thumbnail *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:146:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(url):?s,"
  /* specs/discord/channel.objects.json:147:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(proxy_url):?s,"
  /* specs/discord/channel.objects.json:148:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/discord/channel.objects.json:149:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:146:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                &p->url,
  /* specs/discord/channel.objects.json:147:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                &p->proxy_url,
  /* specs/discord/channel.objects.json:148:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/discord/channel.objects.json:149:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_thumbnail_use_default_inject_settings(struct discord_embed_thumbnail *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:146:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (p->url != NULL && strlen(p->url) != 0)
    p->__M.arg_switches[0] = p->url;

  /* specs/discord/channel.objects.json:147:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (p->proxy_url != NULL && strlen(p->proxy_url) != 0)
    p->__M.arg_switches[1] = p->proxy_url;

  /* specs/discord/channel.objects.json:148:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->height != 0)
    p->__M.arg_switches[2] = &p->height;

  /* specs/discord/channel.objects.json:149:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->width != 0)
    p->__M.arg_switches[3] = &p->width;

}

size_t discord_embed_thumbnail_to_json(char *json, size_t len, struct discord_embed_thumbnail *p)
{
  size_t r;
  discord_embed_thumbnail_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:146:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/discord/channel.objects.json:147:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(proxy_url):s,"
  /* specs/discord/channel.objects.json:148:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/discord/channel.objects.json:149:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:146:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/discord/channel.objects.json:147:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                p->proxy_url,
  /* specs/discord/channel.objects.json:148:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/discord/channel.objects.json:149:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_thumbnail_cleanup_v(void *p) {
  discord_embed_thumbnail_cleanup((struct discord_embed_thumbnail *)p);
}

void discord_embed_thumbnail_init_v(void *p) {
  discord_embed_thumbnail_init((struct discord_embed_thumbnail *)p);
}

void discord_embed_thumbnail_free_v(void *p) {
 discord_embed_thumbnail_free((struct discord_embed_thumbnail *)p);
};

void discord_embed_thumbnail_from_json_v(char *json, size_t len, void *p) {
 discord_embed_thumbnail_from_json(json, len, (struct discord_embed_thumbnail*)p);
}

size_t discord_embed_thumbnail_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_thumbnail_to_json(json, len, (struct discord_embed_thumbnail*)p);
}

void discord_embed_thumbnail_list_free_v(void **p) {
  discord_embed_thumbnail_list_free((struct discord_embed_thumbnail**)p);
}

void discord_embed_thumbnail_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_thumbnail_list_from_json(str, len, (struct discord_embed_thumbnail ***)p);
}

size_t discord_embed_thumbnail_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_thumbnail_list_to_json(str, len, (struct discord_embed_thumbnail **)p);
}


void discord_embed_thumbnail_cleanup(struct discord_embed_thumbnail *d) {
  /* specs/discord/channel.objects.json:146:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (d->url)
    free(d->url);
  /* specs/discord/channel.objects.json:147:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (d->proxy_url)
    free(d->proxy_url);
  /* specs/discord/channel.objects.json:148:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->height is a scalar
  /* specs/discord/channel.objects.json:149:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->width is a scalar
}

void discord_embed_thumbnail_init(struct discord_embed_thumbnail *p) {
  memset(p, 0, sizeof(struct discord_embed_thumbnail));
  /* specs/discord/channel.objects.json:146:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:147:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:148:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/discord/channel.objects.json:149:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */

}
struct discord_embed_thumbnail* discord_embed_thumbnail_alloc() {
  struct discord_embed_thumbnail *p= (struct discord_embed_thumbnail*)malloc(sizeof(struct discord_embed_thumbnail));
  discord_embed_thumbnail_init(p);
  return p;
}

void discord_embed_thumbnail_free(struct discord_embed_thumbnail *p) {
  discord_embed_thumbnail_cleanup(p);
  free(p);
}

void discord_embed_thumbnail_list_free(struct discord_embed_thumbnail **p) {
  ntl_free((void**)p, (vfvp)discord_embed_thumbnail_cleanup);
}

void discord_embed_thumbnail_list_from_json(char *str, size_t len, struct discord_embed_thumbnail ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_thumbnail);
  d.init_elem = discord_embed_thumbnail_init_v;
  d.elem_from_buf = discord_embed_thumbnail_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_embed_thumbnail_list_to_json(char *str, size_t len, struct discord_embed_thumbnail **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_thumbnail_to_json_v);
}


void discord_embed_video_from_json(char *json, size_t len, struct discord_embed_video *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:158:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(url):?s,"
  /* specs/discord/channel.objects.json:159:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(proxy_url):?s,"
  /* specs/discord/channel.objects.json:160:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/discord/channel.objects.json:161:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:158:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                &p->url,
  /* specs/discord/channel.objects.json:159:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                &p->proxy_url,
  /* specs/discord/channel.objects.json:160:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/discord/channel.objects.json:161:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_video_use_default_inject_settings(struct discord_embed_video *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:158:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (p->url != NULL && strlen(p->url) != 0)
    p->__M.arg_switches[0] = p->url;

  /* specs/discord/channel.objects.json:159:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (p->proxy_url != NULL && strlen(p->proxy_url) != 0)
    p->__M.arg_switches[1] = p->proxy_url;

  /* specs/discord/channel.objects.json:160:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->height != 0)
    p->__M.arg_switches[2] = &p->height;

  /* specs/discord/channel.objects.json:161:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->width != 0)
    p->__M.arg_switches[3] = &p->width;

}

size_t discord_embed_video_to_json(char *json, size_t len, struct discord_embed_video *p)
{
  size_t r;
  discord_embed_video_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:158:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/discord/channel.objects.json:159:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(proxy_url):s,"
  /* specs/discord/channel.objects.json:160:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/discord/channel.objects.json:161:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:158:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/discord/channel.objects.json:159:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                p->proxy_url,
  /* specs/discord/channel.objects.json:160:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/discord/channel.objects.json:161:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_video_cleanup_v(void *p) {
  discord_embed_video_cleanup((struct discord_embed_video *)p);
}

void discord_embed_video_init_v(void *p) {
  discord_embed_video_init((struct discord_embed_video *)p);
}

void discord_embed_video_free_v(void *p) {
 discord_embed_video_free((struct discord_embed_video *)p);
};

void discord_embed_video_from_json_v(char *json, size_t len, void *p) {
 discord_embed_video_from_json(json, len, (struct discord_embed_video*)p);
}

size_t discord_embed_video_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_video_to_json(json, len, (struct discord_embed_video*)p);
}

void discord_embed_video_list_free_v(void **p) {
  discord_embed_video_list_free((struct discord_embed_video**)p);
}

void discord_embed_video_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_video_list_from_json(str, len, (struct discord_embed_video ***)p);
}

size_t discord_embed_video_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_video_list_to_json(str, len, (struct discord_embed_video **)p);
}


void discord_embed_video_cleanup(struct discord_embed_video *d) {
  /* specs/discord/channel.objects.json:158:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (d->url)
    free(d->url);
  /* specs/discord/channel.objects.json:159:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (d->proxy_url)
    free(d->proxy_url);
  /* specs/discord/channel.objects.json:160:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->height is a scalar
  /* specs/discord/channel.objects.json:161:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->width is a scalar
}

void discord_embed_video_init(struct discord_embed_video *p) {
  memset(p, 0, sizeof(struct discord_embed_video));
  /* specs/discord/channel.objects.json:158:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:159:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:160:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/discord/channel.objects.json:161:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */

}
struct discord_embed_video* discord_embed_video_alloc() {
  struct discord_embed_video *p= (struct discord_embed_video*)malloc(sizeof(struct discord_embed_video));
  discord_embed_video_init(p);
  return p;
}

void discord_embed_video_free(struct discord_embed_video *p) {
  discord_embed_video_cleanup(p);
  free(p);
}

void discord_embed_video_list_free(struct discord_embed_video **p) {
  ntl_free((void**)p, (vfvp)discord_embed_video_cleanup);
}

void discord_embed_video_list_from_json(char *str, size_t len, struct discord_embed_video ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_video);
  d.init_elem = discord_embed_video_init_v;
  d.elem_from_buf = discord_embed_video_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_embed_video_list_to_json(char *str, size_t len, struct discord_embed_video **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_video_to_json_v);
}


void discord_embed_image_from_json(char *json, size_t len, struct discord_embed_image *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:170:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(url):?s,"
  /* specs/discord/channel.objects.json:171:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(proxy_url):?s,"
  /* specs/discord/channel.objects.json:172:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/discord/channel.objects.json:173:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:170:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                &p->url,
  /* specs/discord/channel.objects.json:171:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                &p->proxy_url,
  /* specs/discord/channel.objects.json:172:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/discord/channel.objects.json:173:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_image_use_default_inject_settings(struct discord_embed_image *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:170:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (p->url != NULL && strlen(p->url) != 0)
    p->__M.arg_switches[0] = p->url;

  /* specs/discord/channel.objects.json:171:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (p->proxy_url != NULL && strlen(p->proxy_url) != 0)
    p->__M.arg_switches[1] = p->proxy_url;

  /* specs/discord/channel.objects.json:172:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->height != 0)
    p->__M.arg_switches[2] = &p->height;

  /* specs/discord/channel.objects.json:173:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->width != 0)
    p->__M.arg_switches[3] = &p->width;

}

size_t discord_embed_image_to_json(char *json, size_t len, struct discord_embed_image *p)
{
  size_t r;
  discord_embed_image_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:170:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/discord/channel.objects.json:171:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(proxy_url):s,"
  /* specs/discord/channel.objects.json:172:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/discord/channel.objects.json:173:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:170:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/discord/channel.objects.json:171:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                p->proxy_url,
  /* specs/discord/channel.objects.json:172:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/discord/channel.objects.json:173:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_image_cleanup_v(void *p) {
  discord_embed_image_cleanup((struct discord_embed_image *)p);
}

void discord_embed_image_init_v(void *p) {
  discord_embed_image_init((struct discord_embed_image *)p);
}

void discord_embed_image_free_v(void *p) {
 discord_embed_image_free((struct discord_embed_image *)p);
};

void discord_embed_image_from_json_v(char *json, size_t len, void *p) {
 discord_embed_image_from_json(json, len, (struct discord_embed_image*)p);
}

size_t discord_embed_image_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_image_to_json(json, len, (struct discord_embed_image*)p);
}

void discord_embed_image_list_free_v(void **p) {
  discord_embed_image_list_free((struct discord_embed_image**)p);
}

void discord_embed_image_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_image_list_from_json(str, len, (struct discord_embed_image ***)p);
}

size_t discord_embed_image_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_image_list_to_json(str, len, (struct discord_embed_image **)p);
}


void discord_embed_image_cleanup(struct discord_embed_image *d) {
  /* specs/discord/channel.objects.json:170:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (d->url)
    free(d->url);
  /* specs/discord/channel.objects.json:171:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (d->proxy_url)
    free(d->proxy_url);
  /* specs/discord/channel.objects.json:172:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->height is a scalar
  /* specs/discord/channel.objects.json:173:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->width is a scalar
}

void discord_embed_image_init(struct discord_embed_image *p) {
  memset(p, 0, sizeof(struct discord_embed_image));
  /* specs/discord/channel.objects.json:170:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:171:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:172:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/discord/channel.objects.json:173:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */

}
struct discord_embed_image* discord_embed_image_alloc() {
  struct discord_embed_image *p= (struct discord_embed_image*)malloc(sizeof(struct discord_embed_image));
  discord_embed_image_init(p);
  return p;
}

void discord_embed_image_free(struct discord_embed_image *p) {
  discord_embed_image_cleanup(p);
  free(p);
}

void discord_embed_image_list_free(struct discord_embed_image **p) {
  ntl_free((void**)p, (vfvp)discord_embed_image_cleanup);
}

void discord_embed_image_list_from_json(char *str, size_t len, struct discord_embed_image ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_image);
  d.init_elem = discord_embed_image_init_v;
  d.elem_from_buf = discord_embed_image_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_embed_image_list_to_json(char *str, size_t len, struct discord_embed_image **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_image_to_json_v);
}


void discord_embed_provider_from_json(char *json, size_t len, struct discord_embed_provider *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:182:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/discord/channel.objects.json:183:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":""}'
  */
                "(url):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:182:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
                p->name,
  /* specs/discord/channel.objects.json:183:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":""}'
  */
                &p->url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_provider_use_default_inject_settings(struct discord_embed_provider *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:182:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
  if (strlen(p->name) != 0)
    p->__M.arg_switches[0] = p->name;

  /* specs/discord/channel.objects.json:183:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":""}'
  */
  if (p->url != NULL && strlen(p->url) != 0)
    p->__M.arg_switches[1] = p->url;

}

size_t discord_embed_provider_to_json(char *json, size_t len, struct discord_embed_provider *p)
{
  size_t r;
  discord_embed_provider_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:182:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/discord/channel.objects.json:183:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":""}'
  */
                "(url):s,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:182:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
                p->name,
  /* specs/discord/channel.objects.json:183:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":""}'
  */
                p->url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_provider_cleanup_v(void *p) {
  discord_embed_provider_cleanup((struct discord_embed_provider *)p);
}

void discord_embed_provider_init_v(void *p) {
  discord_embed_provider_init((struct discord_embed_provider *)p);
}

void discord_embed_provider_free_v(void *p) {
 discord_embed_provider_free((struct discord_embed_provider *)p);
};

void discord_embed_provider_from_json_v(char *json, size_t len, void *p) {
 discord_embed_provider_from_json(json, len, (struct discord_embed_provider*)p);
}

size_t discord_embed_provider_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_provider_to_json(json, len, (struct discord_embed_provider*)p);
}

void discord_embed_provider_list_free_v(void **p) {
  discord_embed_provider_list_free((struct discord_embed_provider**)p);
}

void discord_embed_provider_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_provider_list_from_json(str, len, (struct discord_embed_provider ***)p);
}

size_t discord_embed_provider_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_provider_list_to_json(str, len, (struct discord_embed_provider **)p);
}


void discord_embed_provider_cleanup(struct discord_embed_provider *d) {
  /* specs/discord/channel.objects.json:182:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
  //p->name is a scalar
  /* specs/discord/channel.objects.json:183:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":""}'
  */
  if (d->url)
    free(d->url);
}

void discord_embed_provider_init(struct discord_embed_provider *p) {
  memset(p, 0, sizeof(struct discord_embed_provider));
  /* specs/discord/channel.objects.json:182:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:183:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":""}'
  */

}
struct discord_embed_provider* discord_embed_provider_alloc() {
  struct discord_embed_provider *p= (struct discord_embed_provider*)malloc(sizeof(struct discord_embed_provider));
  discord_embed_provider_init(p);
  return p;
}

void discord_embed_provider_free(struct discord_embed_provider *p) {
  discord_embed_provider_cleanup(p);
  free(p);
}

void discord_embed_provider_list_free(struct discord_embed_provider **p) {
  ntl_free((void**)p, (vfvp)discord_embed_provider_cleanup);
}

void discord_embed_provider_list_from_json(char *str, size_t len, struct discord_embed_provider ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_provider);
  d.init_elem = discord_embed_provider_init_v;
  d.elem_from_buf = discord_embed_provider_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_embed_provider_list_to_json(char *str, size_t len, struct discord_embed_provider **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_provider_to_json_v);
}


void discord_embed_author_from_json(char *json, size_t len, struct discord_embed_author *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:192:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/discord/channel.objects.json:193:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(url):?s,"
  /* specs/discord/channel.objects.json:194:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(icon_url):?s,"
  /* specs/discord/channel.objects.json:195:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(proxy_icon_url):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:192:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
                p->name,
  /* specs/discord/channel.objects.json:193:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                &p->url,
  /* specs/discord/channel.objects.json:194:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                &p->icon_url,
  /* specs/discord/channel.objects.json:195:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                &p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_author_use_default_inject_settings(struct discord_embed_author *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:192:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->name) != 0)
    p->__M.arg_switches[0] = p->name;

  /* specs/discord/channel.objects.json:193:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (p->url != NULL && strlen(p->url) != 0)
    p->__M.arg_switches[1] = p->url;

  /* specs/discord/channel.objects.json:194:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (p->icon_url != NULL && strlen(p->icon_url) != 0)
    p->__M.arg_switches[2] = p->icon_url;

  /* specs/discord/channel.objects.json:195:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (p->proxy_icon_url != NULL && strlen(p->proxy_icon_url) != 0)
    p->__M.arg_switches[3] = p->proxy_icon_url;

}

size_t discord_embed_author_to_json(char *json, size_t len, struct discord_embed_author *p)
{
  size_t r;
  discord_embed_author_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:192:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/discord/channel.objects.json:193:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/discord/channel.objects.json:194:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(icon_url):s,"
  /* specs/discord/channel.objects.json:195:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                "(proxy_icon_url):s,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:192:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
                p->name,
  /* specs/discord/channel.objects.json:193:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/discord/channel.objects.json:194:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                p->icon_url,
  /* specs/discord/channel.objects.json:195:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
                p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_author_cleanup_v(void *p) {
  discord_embed_author_cleanup((struct discord_embed_author *)p);
}

void discord_embed_author_init_v(void *p) {
  discord_embed_author_init((struct discord_embed_author *)p);
}

void discord_embed_author_free_v(void *p) {
 discord_embed_author_free((struct discord_embed_author *)p);
};

void discord_embed_author_from_json_v(char *json, size_t len, void *p) {
 discord_embed_author_from_json(json, len, (struct discord_embed_author*)p);
}

size_t discord_embed_author_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_author_to_json(json, len, (struct discord_embed_author*)p);
}

void discord_embed_author_list_free_v(void **p) {
  discord_embed_author_list_free((struct discord_embed_author**)p);
}

void discord_embed_author_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_author_list_from_json(str, len, (struct discord_embed_author ***)p);
}

size_t discord_embed_author_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_author_list_to_json(str, len, (struct discord_embed_author **)p);
}


void discord_embed_author_cleanup(struct discord_embed_author *d) {
  /* specs/discord/channel.objects.json:192:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
  //p->name is a scalar
  /* specs/discord/channel.objects.json:193:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (d->url)
    free(d->url);
  /* specs/discord/channel.objects.json:194:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (d->icon_url)
    free(d->icon_url);
  /* specs/discord/channel.objects.json:195:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  if (d->proxy_icon_url)
    free(d->proxy_icon_url);
}

void discord_embed_author_init(struct discord_embed_author *p) {
  memset(p, 0, sizeof(struct discord_embed_author));
  /* specs/discord/channel.objects.json:192:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:193:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:194:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:195:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */

}
struct discord_embed_author* discord_embed_author_alloc() {
  struct discord_embed_author *p= (struct discord_embed_author*)malloc(sizeof(struct discord_embed_author));
  discord_embed_author_init(p);
  return p;
}

void discord_embed_author_free(struct discord_embed_author *p) {
  discord_embed_author_cleanup(p);
  free(p);
}

void discord_embed_author_list_free(struct discord_embed_author **p) {
  ntl_free((void**)p, (vfvp)discord_embed_author_cleanup);
}

void discord_embed_author_list_from_json(char *str, size_t len, struct discord_embed_author ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_author);
  d.init_elem = discord_embed_author_init_v;
  d.elem_from_buf = discord_embed_author_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_embed_author_list_to_json(char *str, size_t len, struct discord_embed_author **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_author_to_json_v);
}


void discord_embed_footer_from_json(char *json, size_t len, struct discord_embed_footer *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:204:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
                "(text):s,"
  /* specs/discord/channel.objects.json:205:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":""}'
  */
                "(icon_url):?s,"
  /* specs/discord/channel.objects.json:207:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, 
          "option":true, "inject_if_not":""}'
  */
                "(proxy_icon_url):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:204:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
                p->text,
  /* specs/discord/channel.objects.json:205:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":""}'
  */
                &p->icon_url,
  /* specs/discord/channel.objects.json:207:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, 
          "option":true, "inject_if_not":""}'
  */
                &p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_footer_use_default_inject_settings(struct discord_embed_footer *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:204:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
  if (strlen(p->text) != 0)
    p->__M.arg_switches[0] = p->text;

  /* specs/discord/channel.objects.json:205:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":""}'
  */
  if (p->icon_url != NULL && strlen(p->icon_url) != 0)
    p->__M.arg_switches[1] = p->icon_url;

  /* specs/discord/channel.objects.json:207:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, 
          "option":true, "inject_if_not":""}'
  */
  if (p->proxy_icon_url != NULL && strlen(p->proxy_icon_url) != 0)
    p->__M.arg_switches[2] = p->proxy_icon_url;

}

size_t discord_embed_footer_to_json(char *json, size_t len, struct discord_embed_footer *p)
{
  size_t r;
  discord_embed_footer_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:204:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
                "(text):s,"
  /* specs/discord/channel.objects.json:205:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":""}'
  */
                "(icon_url):s,"
  /* specs/discord/channel.objects.json:207:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, 
          "option":true, "inject_if_not":""}'
  */
                "(proxy_icon_url):s,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:204:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
                p->text,
  /* specs/discord/channel.objects.json:205:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":""}'
  */
                p->icon_url,
  /* specs/discord/channel.objects.json:207:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, 
          "option":true, "inject_if_not":""}'
  */
                p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_footer_cleanup_v(void *p) {
  discord_embed_footer_cleanup((struct discord_embed_footer *)p);
}

void discord_embed_footer_init_v(void *p) {
  discord_embed_footer_init((struct discord_embed_footer *)p);
}

void discord_embed_footer_free_v(void *p) {
 discord_embed_footer_free((struct discord_embed_footer *)p);
};

void discord_embed_footer_from_json_v(char *json, size_t len, void *p) {
 discord_embed_footer_from_json(json, len, (struct discord_embed_footer*)p);
}

size_t discord_embed_footer_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_footer_to_json(json, len, (struct discord_embed_footer*)p);
}

void discord_embed_footer_list_free_v(void **p) {
  discord_embed_footer_list_free((struct discord_embed_footer**)p);
}

void discord_embed_footer_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_footer_list_from_json(str, len, (struct discord_embed_footer ***)p);
}

size_t discord_embed_footer_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_footer_list_to_json(str, len, (struct discord_embed_footer **)p);
}


void discord_embed_footer_cleanup(struct discord_embed_footer *d) {
  /* specs/discord/channel.objects.json:204:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
  //p->text is a scalar
  /* specs/discord/channel.objects.json:205:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":""}'
  */
  if (d->icon_url)
    free(d->icon_url);
  /* specs/discord/channel.objects.json:207:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, 
          "option":true, "inject_if_not":""}'
  */
  if (d->proxy_icon_url)
    free(d->proxy_icon_url);
}

void discord_embed_footer_init(struct discord_embed_footer *p) {
  memset(p, 0, sizeof(struct discord_embed_footer));
  /* specs/discord/channel.objects.json:204:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:205:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:207:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, 
          "option":true, "inject_if_not":""}'
  */

}
struct discord_embed_footer* discord_embed_footer_alloc() {
  struct discord_embed_footer *p= (struct discord_embed_footer*)malloc(sizeof(struct discord_embed_footer));
  discord_embed_footer_init(p);
  return p;
}

void discord_embed_footer_free(struct discord_embed_footer *p) {
  discord_embed_footer_cleanup(p);
  free(p);
}

void discord_embed_footer_list_free(struct discord_embed_footer **p) {
  ntl_free((void**)p, (vfvp)discord_embed_footer_cleanup);
}

void discord_embed_footer_list_from_json(char *str, size_t len, struct discord_embed_footer ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_footer);
  d.init_elem = discord_embed_footer_init_v;
  d.elem_from_buf = discord_embed_footer_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_embed_footer_list_to_json(char *str, size_t len, struct discord_embed_footer **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_footer_to_json_v);
}


void discord_embed_field_from_json(char *json, size_t len, struct discord_embed_field *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.objects.json:217:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/discord/channel.objects.json:218:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
                "(value):s,"
  /* specs/discord/channel.objects.json:219:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
                "(inline):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.objects.json:217:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
                p->name,
  /* specs/discord/channel.objects.json:218:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
                p->value,
  /* specs/discord/channel.objects.json:219:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
                &p->Inline,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_field_use_default_inject_settings(struct discord_embed_field *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.objects.json:217:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->name) != 0)
    p->__M.arg_switches[0] = p->name;

  /* specs/discord/channel.objects.json:218:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->value) != 0)
    p->__M.arg_switches[1] = p->value;

  /* specs/discord/channel.objects.json:219:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
  p->__M.arg_switches[2] = &p->Inline;

}

size_t discord_embed_field_to_json(char *json, size_t len, struct discord_embed_field *p)
{
  size_t r;
  discord_embed_field_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.objects.json:217:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/discord/channel.objects.json:218:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
                "(value):s,"
  /* specs/discord/channel.objects.json:219:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
                "(inline):b,"
                "@arg_switches:b",
  /* specs/discord/channel.objects.json:217:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
                p->name,
  /* specs/discord/channel.objects.json:218:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
                p->value,
  /* specs/discord/channel.objects.json:219:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
                &p->Inline,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_field_cleanup_v(void *p) {
  discord_embed_field_cleanup((struct discord_embed_field *)p);
}

void discord_embed_field_init_v(void *p) {
  discord_embed_field_init((struct discord_embed_field *)p);
}

void discord_embed_field_free_v(void *p) {
 discord_embed_field_free((struct discord_embed_field *)p);
};

void discord_embed_field_from_json_v(char *json, size_t len, void *p) {
 discord_embed_field_from_json(json, len, (struct discord_embed_field*)p);
}

size_t discord_embed_field_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_field_to_json(json, len, (struct discord_embed_field*)p);
}

void discord_embed_field_list_free_v(void **p) {
  discord_embed_field_list_free((struct discord_embed_field**)p);
}

void discord_embed_field_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_field_list_from_json(str, len, (struct discord_embed_field ***)p);
}

size_t discord_embed_field_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_field_list_to_json(str, len, (struct discord_embed_field **)p);
}


void discord_embed_field_cleanup(struct discord_embed_field *d) {
  /* specs/discord/channel.objects.json:217:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
  //p->name is a scalar
  /* specs/discord/channel.objects.json:218:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
  //p->value is a scalar
  /* specs/discord/channel.objects.json:219:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
  //p->Inline is a scalar
}

void discord_embed_field_init(struct discord_embed_field *p) {
  memset(p, 0, sizeof(struct discord_embed_field));
  /* specs/discord/channel.objects.json:217:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:218:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */

  /* specs/discord/channel.objects.json:219:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */

}
struct discord_embed_field* discord_embed_field_alloc() {
  struct discord_embed_field *p= (struct discord_embed_field*)malloc(sizeof(struct discord_embed_field));
  discord_embed_field_init(p);
  return p;
}

void discord_embed_field_free(struct discord_embed_field *p) {
  discord_embed_field_cleanup(p);
  free(p);
}

void discord_embed_field_list_free(struct discord_embed_field **p) {
  ntl_free((void**)p, (vfvp)discord_embed_field_cleanup);
}

void discord_embed_field_list_from_json(char *str, size_t len, struct discord_embed_field ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_field);
  d.init_elem = discord_embed_field_init_v;
  d.elem_from_buf = discord_embed_field_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_embed_field_list_to_json(char *str, size_t len, struct discord_embed_field **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_field_to_json_v);
}

