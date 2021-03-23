/* This file is generated from specs/guild.ban.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#ban-object
*/

void discord_guild_ban_dati_from_json(char *json, size_t len, struct discord_guild_ban_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
                "(reason):s,"
  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
                "(user):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
                p->reason,
  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
                discord_user_dati_from_json, p->user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_ban_dati_use_default_inject_settings(struct discord_guild_ban_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
  p->__M.arg_switches[0] = p->reason;

  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
  p->__M.arg_switches[1] = p->user;

}

size_t discord_guild_ban_dati_to_json(char *json, size_t len, struct discord_guild_ban_dati *p)
{
  size_t r;
  discord_guild_ban_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
                "(reason):s,"
  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
                "(user):F,"
                "@arg_switches:b",
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
                p->reason,
  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
                discord_user_dati_to_json, p->user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_ban_dati_cleanup_v(void *p) {
  discord_guild_ban_dati_cleanup((struct discord_guild_ban_dati *)p);
}

void discord_guild_ban_dati_init_v(void *p) {
  discord_guild_ban_dati_init((struct discord_guild_ban_dati *)p);
}

void discord_guild_ban_dati_free_v(void *p) {
 discord_guild_ban_dati_free((struct discord_guild_ban_dati *)p);
};

void discord_guild_ban_dati_from_json_v(char *json, size_t len, void *p) {
 discord_guild_ban_dati_from_json(json, len, (struct discord_guild_ban_dati*)p);
}

size_t discord_guild_ban_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_ban_dati_to_json(json, len, (struct discord_guild_ban_dati*)p);
}

void discord_guild_ban_dati_list_free_v(void **p) {
  discord_guild_ban_dati_list_free((struct discord_guild_ban_dati**)p);
}

void discord_guild_ban_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_ban_dati_list_from_json(str, len, (struct discord_guild_ban_dati ***)p);
}

size_t discord_guild_ban_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_ban_dati_list_to_json(str, len, (struct discord_guild_ban_dati **)p);
}


void discord_guild_ban_dati_cleanup(struct discord_guild_ban_dati *d) {
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
  //p->reason is a scalar
  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
  if (d->user)
    discord_user_dati_free(d->user);
}

void discord_guild_ban_dati_init(struct discord_guild_ban_dati *p) {
  memset(p, 0, sizeof(struct discord_guild_ban_dati));
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */

  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
  p->user = discord_user_dati_alloc();

}
struct discord_guild_ban_dati* discord_guild_ban_dati_alloc() {
  struct discord_guild_ban_dati *p= (struct discord_guild_ban_dati*)malloc(sizeof(struct discord_guild_ban_dati));
  discord_guild_ban_dati_init(p);
  return p;
}

void discord_guild_ban_dati_free(struct discord_guild_ban_dati *p) {
  discord_guild_ban_dati_cleanup(p);
  free(p);
}

void discord_guild_ban_dati_list_free(struct discord_guild_ban_dati **p) {
  ntl_free((void**)p, (vfvp)discord_guild_ban_dati_cleanup);
}

void discord_guild_ban_dati_list_from_json(char *str, size_t len, struct discord_guild_ban_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_ban_dati);
  d.init_elem = discord_guild_ban_dati_init_v;
  d.elem_from_buf = discord_guild_ban_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_ban_dati_list_to_json(char *str, size_t len, struct discord_guild_ban_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_ban_dati_to_json_v);
}

