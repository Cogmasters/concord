/* This file is generated from specs/guild.welcome_screen.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#welcome-screen-object
*/

void discord_guild_welcome_screen_screen_channel_dati_from_json(char *json, size_t len, struct discord_guild_welcome_screen_screen_channel_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.welcome_screen.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(channel_id):F,"
  /* specs/guild.welcome_screen.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
                "(description):?s,"
  /* specs/guild.welcome_screen.json:16:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(emoji_id):F,"
  /* specs/guild.welcome_screen.json:17:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(emoji_name):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.welcome_screen.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->channel_id,
  /* specs/guild.welcome_screen.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->description,
  /* specs/guild.welcome_screen.json:16:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->emoji_id,
  /* specs/guild.welcome_screen.json:17:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->emoji_name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_welcome_screen_screen_channel_dati_use_default_inject_settings(struct discord_guild_welcome_screen_screen_channel_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.welcome_screen.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->channel_id;

  /* specs/guild.welcome_screen.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[1] = p->description;

  /* specs/guild.welcome_screen.json:16:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[2] = &p->emoji_id;

  /* specs/guild.welcome_screen.json:17:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[3] = p->emoji_name;

}

size_t discord_guild_welcome_screen_screen_channel_dati_to_json(char *json, size_t len, struct discord_guild_welcome_screen_screen_channel_dati *p)
{
  size_t r;
  discord_guild_welcome_screen_screen_channel_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.welcome_screen.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(channel_id):|F|,"
  /* specs/guild.welcome_screen.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
                "(description):s,"
  /* specs/guild.welcome_screen.json:16:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(emoji_id):|F|,"
  /* specs/guild.welcome_screen.json:17:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(emoji_name):s,"
                "@arg_switches:b",
  /* specs/guild.welcome_screen.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->channel_id,
  /* specs/guild.welcome_screen.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
                p->description,
  /* specs/guild.welcome_screen.json:16:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->emoji_id,
  /* specs/guild.welcome_screen.json:17:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}'
  */
                p->emoji_name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_welcome_screen_screen_channel_dati_cleanup_v(void *p) {
  discord_guild_welcome_screen_screen_channel_dati_cleanup((struct discord_guild_welcome_screen_screen_channel_dati *)p);
}

void discord_guild_welcome_screen_screen_channel_dati_init_v(void *p) {
  discord_guild_welcome_screen_screen_channel_dati_init((struct discord_guild_welcome_screen_screen_channel_dati *)p);
}

void discord_guild_welcome_screen_screen_channel_dati_free_v(void *p) {
 discord_guild_welcome_screen_screen_channel_dati_free((struct discord_guild_welcome_screen_screen_channel_dati *)p);
};

void discord_guild_welcome_screen_screen_channel_dati_from_json_v(char *json, size_t len, void *p) {
 discord_guild_welcome_screen_screen_channel_dati_from_json(json, len, (struct discord_guild_welcome_screen_screen_channel_dati*)p);
}

size_t discord_guild_welcome_screen_screen_channel_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_welcome_screen_screen_channel_dati_to_json(json, len, (struct discord_guild_welcome_screen_screen_channel_dati*)p);
}

void discord_guild_welcome_screen_screen_channel_dati_list_free_v(void **p) {
  discord_guild_welcome_screen_screen_channel_dati_list_free((struct discord_guild_welcome_screen_screen_channel_dati**)p);
}

void discord_guild_welcome_screen_screen_channel_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_welcome_screen_screen_channel_dati_list_from_json(str, len, (struct discord_guild_welcome_screen_screen_channel_dati ***)p);
}

size_t discord_guild_welcome_screen_screen_channel_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_welcome_screen_screen_channel_dati_list_to_json(str, len, (struct discord_guild_welcome_screen_screen_channel_dati **)p);
}


void discord_guild_welcome_screen_screen_channel_dati_cleanup(struct discord_guild_welcome_screen_screen_channel_dati *d) {
  /* specs/guild.welcome_screen.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->channel_id is a scalar
  /* specs/guild.welcome_screen.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->description)
    free(d->description);
  /* specs/guild.welcome_screen.json:16:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->emoji_id is a scalar
  /* specs/guild.welcome_screen.json:17:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->emoji_name)
    free(d->emoji_name);
}

void discord_guild_welcome_screen_screen_channel_dati_init(struct discord_guild_welcome_screen_screen_channel_dati *p) {
  memset(p, 0, sizeof(struct discord_guild_welcome_screen_screen_channel_dati));
  /* specs/guild.welcome_screen.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/guild.welcome_screen.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/guild.welcome_screen.json:16:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/guild.welcome_screen.json:17:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}'
  */

}
struct discord_guild_welcome_screen_screen_channel_dati* discord_guild_welcome_screen_screen_channel_dati_alloc() {
  struct discord_guild_welcome_screen_screen_channel_dati *p= (struct discord_guild_welcome_screen_screen_channel_dati*)malloc(sizeof(struct discord_guild_welcome_screen_screen_channel_dati));
  discord_guild_welcome_screen_screen_channel_dati_init(p);
  return p;
}

void discord_guild_welcome_screen_screen_channel_dati_free(struct discord_guild_welcome_screen_screen_channel_dati *p) {
  discord_guild_welcome_screen_screen_channel_dati_cleanup(p);
  free(p);
}

void discord_guild_welcome_screen_screen_channel_dati_list_free(struct discord_guild_welcome_screen_screen_channel_dati **p) {
  ntl_free((void**)p, (vfvp)discord_guild_welcome_screen_screen_channel_dati_cleanup);
}

void discord_guild_welcome_screen_screen_channel_dati_list_from_json(char *str, size_t len, struct discord_guild_welcome_screen_screen_channel_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_welcome_screen_screen_channel_dati);
  d.init_elem = discord_guild_welcome_screen_screen_channel_dati_init_v;
  d.elem_from_buf = discord_guild_welcome_screen_screen_channel_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_welcome_screen_screen_channel_dati_list_to_json(char *str, size_t len, struct discord_guild_welcome_screen_screen_channel_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_welcome_screen_screen_channel_dati_to_json_v);
}


void discord_guild_welcome_screen_dati_from_json(char *json, size_t len, struct discord_guild_welcome_screen_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.welcome_screen.json:26:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(description):?s,"
  /* specs/guild.welcome_screen.json:27:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_screen_channel_dati", "dec":"ntl" }, "todo":false }'
  */
                "(welcome_channels):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.welcome_screen.json:26:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                &p->description,
  /* specs/guild.welcome_screen.json:27:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_screen_channel_dati", "dec":"ntl" }, "todo":false }'
  */
                struct discord_guild_welcome_screen_screen_channel_dati_list_from_json, &p->welcome_channels,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_welcome_screen_dati_use_default_inject_settings(struct discord_guild_welcome_screen_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.welcome_screen.json:26:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  p->__M.arg_switches[0] = p->description;

  /* specs/guild.welcome_screen.json:27:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_screen_channel_dati", "dec":"ntl" }, "todo":false }'
  */
  p->__M.arg_switches[1] = p->welcome_channels;

}

size_t discord_guild_welcome_screen_dati_to_json(char *json, size_t len, struct discord_guild_welcome_screen_dati *p)
{
  size_t r;
  discord_guild_welcome_screen_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.welcome_screen.json:26:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(description):s,"
  /* specs/guild.welcome_screen.json:27:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_screen_channel_dati", "dec":"ntl" }, "todo":false }'
  */
                "(welcome_channels):F,"
                "@arg_switches:b",
  /* specs/guild.welcome_screen.json:26:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                p->description,
  /* specs/guild.welcome_screen.json:27:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_screen_channel_dati", "dec":"ntl" }, "todo":false }'
  */
                struct discord_guild_welcome_screen_screen_channel_dati_list_to_json, p->welcome_channels,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_welcome_screen_dati_cleanup_v(void *p) {
  discord_guild_welcome_screen_dati_cleanup((struct discord_guild_welcome_screen_dati *)p);
}

void discord_guild_welcome_screen_dati_init_v(void *p) {
  discord_guild_welcome_screen_dati_init((struct discord_guild_welcome_screen_dati *)p);
}

void discord_guild_welcome_screen_dati_free_v(void *p) {
 discord_guild_welcome_screen_dati_free((struct discord_guild_welcome_screen_dati *)p);
};

void discord_guild_welcome_screen_dati_from_json_v(char *json, size_t len, void *p) {
 discord_guild_welcome_screen_dati_from_json(json, len, (struct discord_guild_welcome_screen_dati*)p);
}

size_t discord_guild_welcome_screen_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_welcome_screen_dati_to_json(json, len, (struct discord_guild_welcome_screen_dati*)p);
}

void discord_guild_welcome_screen_dati_list_free_v(void **p) {
  discord_guild_welcome_screen_dati_list_free((struct discord_guild_welcome_screen_dati**)p);
}

void discord_guild_welcome_screen_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_welcome_screen_dati_list_from_json(str, len, (struct discord_guild_welcome_screen_dati ***)p);
}

size_t discord_guild_welcome_screen_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_welcome_screen_dati_list_to_json(str, len, (struct discord_guild_welcome_screen_dati **)p);
}


void discord_guild_welcome_screen_dati_cleanup(struct discord_guild_welcome_screen_dati *d) {
  /* specs/guild.welcome_screen.json:26:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  if (d->description)
    free(d->description);
  /* specs/guild.welcome_screen.json:27:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_screen_channel_dati", "dec":"ntl" }, "todo":false }'
  */
  if (d->welcome_channels)
    struct discord_guild_welcome_screen_screen_channel_dati_list_free(d->welcome_channels);
}

void discord_guild_welcome_screen_dati_init(struct discord_guild_welcome_screen_dati *p) {
  memset(p, 0, sizeof(struct discord_guild_welcome_screen_dati));
  /* specs/guild.welcome_screen.json:26:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */

  /* specs/guild.welcome_screen.json:27:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_screen_channel_dati", "dec":"ntl" }, "todo":false }'
  */

}
struct discord_guild_welcome_screen_dati* discord_guild_welcome_screen_dati_alloc() {
  struct discord_guild_welcome_screen_dati *p= (struct discord_guild_welcome_screen_dati*)malloc(sizeof(struct discord_guild_welcome_screen_dati));
  discord_guild_welcome_screen_dati_init(p);
  return p;
}

void discord_guild_welcome_screen_dati_free(struct discord_guild_welcome_screen_dati *p) {
  discord_guild_welcome_screen_dati_cleanup(p);
  free(p);
}

void discord_guild_welcome_screen_dati_list_free(struct discord_guild_welcome_screen_dati **p) {
  ntl_free((void**)p, (vfvp)discord_guild_welcome_screen_dati_cleanup);
}

void discord_guild_welcome_screen_dati_list_from_json(char *str, size_t len, struct discord_guild_welcome_screen_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_welcome_screen_dati);
  d.init_elem = discord_guild_welcome_screen_dati_init_v;
  d.elem_from_buf = discord_guild_welcome_screen_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_welcome_screen_dati_list_to_json(char *str, size_t len, struct discord_guild_welcome_screen_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_welcome_screen_dati_to_json_v);
}

