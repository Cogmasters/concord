/* This file is generated from specs/discord/guild.add-guild-member.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_add_guild_member_params_from_json(char *json, size_t len, struct discord_add_guild_member_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.add-guild-member.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                "(access_token):?s,"
  /* specs/discord/guild.add-guild-member.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                "(nick):?s,"
  /* specs/discord/guild.add-guild-member.json:13:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
                "(roles):F,"
  /* specs/discord/guild.add-guild-member.json:14:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(mute):b,"
  /* specs/discord/guild.add-guild-member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(deaf):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.add-guild-member.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                &p->access_token,
  /* specs/discord/guild.add-guild-member.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                &p->nick,
  /* specs/discord/guild.add-guild-member.json:13:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
                ja_u64_list_from_json, &p->roles,
  /* specs/discord/guild.add-guild-member.json:14:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->mute,
  /* specs/discord/guild.add-guild-member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->deaf,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_add_guild_member_params_use_default_inject_settings(struct discord_add_guild_member_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.add-guild-member.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  if (p->access_token != NULL)
    p->__M.arg_switches[0] = p->access_token;

  /* specs/discord/guild.add-guild-member.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  if (p->nick != NULL)
    p->__M.arg_switches[1] = p->nick;

  /* specs/discord/guild.add-guild-member.json:13:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
  if (p->roles != NULL)
    p->__M.arg_switches[2] = p->roles;

  /* specs/discord/guild.add-guild-member.json:14:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  if (p->mute != false)
    p->__M.arg_switches[3] = &p->mute;

  /* specs/discord/guild.add-guild-member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  if (p->deaf != false)
    p->__M.arg_switches[4] = &p->deaf;

}

size_t discord_add_guild_member_params_to_json(char *json, size_t len, struct discord_add_guild_member_params *p)
{
  size_t r;
  discord_add_guild_member_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.add-guild-member.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                "(access_token):s,"
  /* specs/discord/guild.add-guild-member.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                "(nick):s,"
  /* specs/discord/guild.add-guild-member.json:13:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
                "(roles):F,"
  /* specs/discord/guild.add-guild-member.json:14:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(mute):b,"
  /* specs/discord/guild.add-guild-member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(deaf):b,"
                "@arg_switches:b",
  /* specs/discord/guild.add-guild-member.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                p->access_token,
  /* specs/discord/guild.add-guild-member.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                p->nick,
  /* specs/discord/guild.add-guild-member.json:13:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
                ja_u64_list_to_json, p->roles,
  /* specs/discord/guild.add-guild-member.json:14:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->mute,
  /* specs/discord/guild.add-guild-member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->deaf,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_add_guild_member_params_cleanup_v(void *p) {
  discord_add_guild_member_params_cleanup((struct discord_add_guild_member_params *)p);
}

void discord_add_guild_member_params_init_v(void *p) {
  discord_add_guild_member_params_init((struct discord_add_guild_member_params *)p);
}

void discord_add_guild_member_params_free_v(void *p) {
 discord_add_guild_member_params_free((struct discord_add_guild_member_params *)p);
};

void discord_add_guild_member_params_from_json_v(char *json, size_t len, void *p) {
 discord_add_guild_member_params_from_json(json, len, (struct discord_add_guild_member_params*)p);
}

size_t discord_add_guild_member_params_to_json_v(char *json, size_t len, void *p) {
  return discord_add_guild_member_params_to_json(json, len, (struct discord_add_guild_member_params*)p);
}

void discord_add_guild_member_params_list_free_v(void **p) {
  discord_add_guild_member_params_list_free((struct discord_add_guild_member_params**)p);
}

void discord_add_guild_member_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_add_guild_member_params_list_from_json(str, len, (struct discord_add_guild_member_params ***)p);
}

size_t discord_add_guild_member_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_add_guild_member_params_list_to_json(str, len, (struct discord_add_guild_member_params **)p);
}


void discord_add_guild_member_params_cleanup(struct discord_add_guild_member_params *d) {
  /* specs/discord/guild.add-guild-member.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  if (d->access_token)
    free(d->access_token);
  /* specs/discord/guild.add-guild-member.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  if (d->nick)
    free(d->nick);
  /* specs/discord/guild.add-guild-member.json:13:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* specs/discord/guild.add-guild-member.json:14:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  //p->mute is a scalar
  /* specs/discord/guild.add-guild-member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  //p->deaf is a scalar
}

void discord_add_guild_member_params_init(struct discord_add_guild_member_params *p) {
  memset(p, 0, sizeof(struct discord_add_guild_member_params));
  /* specs/discord/guild.add-guild-member.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */

  /* specs/discord/guild.add-guild-member.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */

  /* specs/discord/guild.add-guild-member.json:13:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */

  /* specs/discord/guild.add-guild-member.json:14:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */

  /* specs/discord/guild.add-guild-member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */

}
struct discord_add_guild_member_params* discord_add_guild_member_params_alloc() {
  struct discord_add_guild_member_params *p= (struct discord_add_guild_member_params*)malloc(sizeof(struct discord_add_guild_member_params));
  discord_add_guild_member_params_init(p);
  return p;
}

void discord_add_guild_member_params_free(struct discord_add_guild_member_params *p) {
  discord_add_guild_member_params_cleanup(p);
  free(p);
}

void discord_add_guild_member_params_list_free(struct discord_add_guild_member_params **p) {
  ntl_free((void**)p, (vfvp)discord_add_guild_member_params_cleanup);
}

void discord_add_guild_member_params_list_from_json(char *str, size_t len, struct discord_add_guild_member_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_add_guild_member_params);
  d.init_elem = discord_add_guild_member_params_init_v;
  d.elem_from_buf = discord_add_guild_member_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_add_guild_member_params_list_to_json(char *str, size_t len, struct discord_add_guild_member_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_add_guild_member_params_to_json_v);
}

