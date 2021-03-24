/* This file is generated from specs/guild.member.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#guild-member-object
*/

void discord_guild_member_from_json(char *json, size_t len, struct discord_guild_member *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.member.json:10:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
                "(user):F,"
  /* specs/guild.member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}, "option":true}'
  */
                "(nick):s,"
  /* specs/guild.member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}'
  */
                "(roles):F,"
  /* specs/guild.member.json:13:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(joined_at):F,"
  /* specs/guild.member.json:14:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(premium_since):F,"
  /* specs/guild.member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
                "(deaf):b,"
  /* specs/guild.member.json:16:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
                "(mute):b,"
  /* specs/guild.member.json:17:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}'
  */
                "(pending):b,"
  /* specs/guild.member.json:18:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}'
  */
                "(permissions):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.member.json:10:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
                discord_user_from_json, p->user,
  /* specs/guild.member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}, "option":true}'
  */
                p->nick,
  /* specs/guild.member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}'
  */
                ja_u64_list_from_json, &p->roles,
  /* specs/guild.member.json:13:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_iso8601_to_unix_ms, &p->joined_at,
  /* specs/guild.member.json:14:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_iso8601_to_unix_ms, &p->premium_since,
  /* specs/guild.member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
                &p->deaf,
  /* specs/guild.member.json:16:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
                &p->mute,
  /* specs/guild.member.json:17:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}'
  */
                &p->pending,
  /* specs/guild.member.json:18:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}'
  */
                &p->permissions,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_member_use_default_inject_settings(struct discord_guild_member *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.member.json:10:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
  p->__M.arg_switches[0] = p->user;

  /* specs/guild.member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}, "option":true}'
  */
  p->__M.arg_switches[1] = p->nick;

  /* specs/guild.member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}'
  */
  p->__M.arg_switches[2] = p->roles;

  /* specs/guild.member.json:13:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  p->__M.arg_switches[3] = &p->joined_at;

  /* specs/guild.member.json:14:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  p->__M.arg_switches[4] = &p->premium_since;

  /* specs/guild.member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[5] = &p->deaf;

  /* specs/guild.member.json:16:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[6] = &p->mute;

  /* specs/guild.member.json:17:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}'
  */
  p->__M.arg_switches[7] = &p->pending;

  /* specs/guild.member.json:18:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}'
  */
  p->__M.arg_switches[8] = p->permissions;

}

size_t discord_guild_member_to_json(char *json, size_t len, struct discord_guild_member *p)
{
  size_t r;
  discord_guild_member_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.member.json:10:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
                "(user):F,"
  /* specs/guild.member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}, "option":true}'
  */
                "(nick):s,"
  /* specs/guild.member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}'
  */
                "(roles):F,"
  /* specs/guild.member.json:13:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(joined_at):|F|,"
  /* specs/guild.member.json:14:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(premium_since):|F|,"
  /* specs/guild.member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
                "(deaf):b,"
  /* specs/guild.member.json:16:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
                "(mute):b,"
  /* specs/guild.member.json:17:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}'
  */
                "(pending):b,"
  /* specs/guild.member.json:18:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}'
  */
                "(permissions):s,"
                "@arg_switches:b",
  /* specs/guild.member.json:10:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
                discord_user_to_json, p->user,
  /* specs/guild.member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}, "option":true}'
  */
                p->nick,
  /* specs/guild.member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}'
  */
                ja_u64_list_to_json, p->roles,
  /* specs/guild.member.json:13:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_unix_ms_to_iso8601, &p->joined_at,
  /* specs/guild.member.json:14:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_unix_ms_to_iso8601, &p->premium_since,
  /* specs/guild.member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
                &p->deaf,
  /* specs/guild.member.json:16:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
                &p->mute,
  /* specs/guild.member.json:17:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}'
  */
                &p->pending,
  /* specs/guild.member.json:18:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}'
  */
                p->permissions,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_member_cleanup_v(void *p) {
  discord_guild_member_cleanup((struct discord_guild_member *)p);
}

void discord_guild_member_init_v(void *p) {
  discord_guild_member_init((struct discord_guild_member *)p);
}

void discord_guild_member_free_v(void *p) {
 discord_guild_member_free((struct discord_guild_member *)p);
};

void discord_guild_member_from_json_v(char *json, size_t len, void *p) {
 discord_guild_member_from_json(json, len, (struct discord_guild_member*)p);
}

size_t discord_guild_member_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_member_to_json(json, len, (struct discord_guild_member*)p);
}

void discord_guild_member_list_free_v(void **p) {
  discord_guild_member_list_free((struct discord_guild_member**)p);
}

void discord_guild_member_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_member_list_from_json(str, len, (struct discord_guild_member ***)p);
}

size_t discord_guild_member_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_member_list_to_json(str, len, (struct discord_guild_member **)p);
}


void discord_guild_member_cleanup(struct discord_guild_member *d) {
  /* specs/guild.member.json:10:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
  if (d->user)
    discord_user_free(d->user);
  /* specs/guild.member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}, "option":true}'
  */
  //p->nick is a scalar
  /* specs/guild.member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}'
  */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* specs/guild.member.json:13:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  //p->joined_at is a scalar
  /* specs/guild.member.json:14:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  //p->premium_since is a scalar
  /* specs/guild.member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
  //p->deaf is a scalar
  /* specs/guild.member.json:16:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
  //p->mute is a scalar
  /* specs/guild.member.json:17:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}'
  */
  //p->pending is a scalar
  /* specs/guild.member.json:18:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}'
  */
  if (d->permissions)
    free(d->permissions);
}

void discord_guild_member_init(struct discord_guild_member *p) {
  memset(p, 0, sizeof(struct discord_guild_member));
  /* specs/guild.member.json:10:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
  p->user = discord_user_alloc();

  /* specs/guild.member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}, "option":true}'
  */

  /* specs/guild.member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}'
  */

  /* specs/guild.member.json:13:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */

  /* specs/guild.member.json:14:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */

  /* specs/guild.member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */

  /* specs/guild.member.json:16:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */

  /* specs/guild.member.json:17:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}'
  */

  /* specs/guild.member.json:18:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}'
  */

}
struct discord_guild_member* discord_guild_member_alloc() {
  struct discord_guild_member *p= (struct discord_guild_member*)malloc(sizeof(struct discord_guild_member));
  discord_guild_member_init(p);
  return p;
}

void discord_guild_member_free(struct discord_guild_member *p) {
  discord_guild_member_cleanup(p);
  free(p);
}

void discord_guild_member_list_free(struct discord_guild_member **p) {
  ntl_free((void**)p, (vfvp)discord_guild_member_cleanup);
}

void discord_guild_member_list_from_json(char *str, size_t len, struct discord_guild_member ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_member);
  d.init_elem = discord_guild_member_init_v;
  d.elem_from_buf = discord_guild_member_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_member_list_to_json(char *str, size_t len, struct discord_guild_member **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_member_to_json_v);
}

