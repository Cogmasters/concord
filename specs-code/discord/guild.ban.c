/* This file is generated from specs/discord/guild.ban.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#ban-object
*/

void discord_guild_ban_from_json(char *json, size_t len, struct discord_guild_ban *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.ban.json:10:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
                "(reason):s,"
  /* specs/discord/guild.ban.json:11:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}'
  */
                "(user):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.ban.json:10:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
                p->reason,
  /* specs/discord/guild.ban.json:11:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}'
  */
                discord_user_from_json, p->user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_ban_use_default_inject_settings(struct discord_guild_ban *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.ban.json:10:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
  p->__M.arg_switches[0] = p->reason;

  /* specs/discord/guild.ban.json:11:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}'
  */
  p->__M.arg_switches[1] = p->user;

}

size_t discord_guild_ban_to_json(char *json, size_t len, struct discord_guild_ban *p)
{
  size_t r;
  discord_guild_ban_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.ban.json:10:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
                "(reason):s,"
  /* specs/discord/guild.ban.json:11:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}'
  */
                "(user):F,"
                "@arg_switches:b",
  /* specs/discord/guild.ban.json:10:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
                p->reason,
  /* specs/discord/guild.ban.json:11:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}'
  */
                discord_user_to_json, p->user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_ban_cleanup_v(void *p) {
  discord_guild_ban_cleanup((struct discord_guild_ban *)p);
}

void discord_guild_ban_init_v(void *p) {
  discord_guild_ban_init((struct discord_guild_ban *)p);
}

void discord_guild_ban_free_v(void *p) {
 discord_guild_ban_free((struct discord_guild_ban *)p);
};

void discord_guild_ban_from_json_v(char *json, size_t len, void *p) {
 discord_guild_ban_from_json(json, len, (struct discord_guild_ban*)p);
}

size_t discord_guild_ban_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_ban_to_json(json, len, (struct discord_guild_ban*)p);
}

void discord_guild_ban_list_free_v(void **p) {
  discord_guild_ban_list_free((struct discord_guild_ban**)p);
}

void discord_guild_ban_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_ban_list_from_json(str, len, (struct discord_guild_ban ***)p);
}

size_t discord_guild_ban_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_ban_list_to_json(str, len, (struct discord_guild_ban **)p);
}


void discord_guild_ban_cleanup(struct discord_guild_ban *d) {
  /* specs/discord/guild.ban.json:10:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
  //p->reason is a scalar
  /* specs/discord/guild.ban.json:11:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}'
  */
  if (d->user)
    discord_user_free(d->user);
}

void discord_guild_ban_init(struct discord_guild_ban *p) {
  memset(p, 0, sizeof(struct discord_guild_ban));
  /* specs/discord/guild.ban.json:10:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */

  /* specs/discord/guild.ban.json:11:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}'
  */
  p->user = discord_user_alloc();

}
struct discord_guild_ban* discord_guild_ban_alloc() {
  struct discord_guild_ban *p= (struct discord_guild_ban*)malloc(sizeof(struct discord_guild_ban));
  discord_guild_ban_init(p);
  return p;
}

void discord_guild_ban_free(struct discord_guild_ban *p) {
  discord_guild_ban_cleanup(p);
  free(p);
}

void discord_guild_ban_list_free(struct discord_guild_ban **p) {
  ntl_free((void**)p, (vfvp)discord_guild_ban_cleanup);
}

void discord_guild_ban_list_from_json(char *str, size_t len, struct discord_guild_ban ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_ban);
  d.init_elem = discord_guild_ban_init_v;
  d.elem_from_buf = discord_guild_ban_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_ban_list_to_json(char *str, size_t len, struct discord_guild_ban **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_ban_to_json_v);
}

