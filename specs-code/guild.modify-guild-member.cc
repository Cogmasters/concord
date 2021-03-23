/* This file is generated from specs/guild.modify-guild-member.json, Please don't edit it. */
#include "specs.h"
/*

*/
namespace discord {
namespace guild {
namespace modify_guild_member {

void params_from_json(char *json, size_t len, struct params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.modify-guild-member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}'
  */
                "(nick):?s,"
  /* specs/guild.modify-guild-member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
                "(roles):F,"
  /* specs/guild.modify-guild-member.json:13:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(mute):b,"
  /* specs/guild.modify-guild-member.json:14:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(deaf):b,"
  /* specs/guild.modify-guild-member.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
                "(channel_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.modify-guild-member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->nick,
  /* specs/guild.modify-guild-member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
                ja_u64_list_from_json, &p->roles,
  /* specs/guild.modify-guild-member.json:13:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->mute,
  /* specs/guild.modify-guild-member.json:14:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->deaf,
  /* specs/guild.modify-guild-member.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
                orka_strtoull, &p->channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void params_use_default_inject_settings(struct params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.modify-guild-member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[0] = p->nick;

  /* specs/guild.modify-guild-member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
  if (p->roles != NULL)
    p->__M.arg_switches[1] = p->roles;

  /* specs/guild.modify-guild-member.json:13:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  if (p->mute != false)
    p->__M.arg_switches[2] = &p->mute;

  /* specs/guild.modify-guild-member.json:14:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  if (p->deaf != false)
    p->__M.arg_switches[3] = &p->deaf;

  /* specs/guild.modify-guild-member.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
  if (p->channel_id != 0)
    p->__M.arg_switches[4] = &p->channel_id;

}

size_t params_to_json(char *json, size_t len, struct params *p)
{
  size_t r;
  params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.modify-guild-member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}'
  */
                "(nick):s,"
  /* specs/guild.modify-guild-member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
                "(roles):F,"
  /* specs/guild.modify-guild-member.json:13:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(mute):b,"
  /* specs/guild.modify-guild-member.json:14:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(deaf):b,"
  /* specs/guild.modify-guild-member.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
                "(channel_id):|F|,"
                "@arg_switches:b",
  /* specs/guild.modify-guild-member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}'
  */
                p->nick,
  /* specs/guild.modify-guild-member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
                ja_u64_list_to_json, p->roles,
  /* specs/guild.modify-guild-member.json:13:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->mute,
  /* specs/guild.modify-guild-member.json:14:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->deaf,
  /* specs/guild.modify-guild-member.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
                orka_ulltostr, &p->channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void params_cleanup_v(void *p) {
  params_cleanup((struct params *)p);
}

void params_init_v(void *p) {
  params_init((struct params *)p);
}

void params_free_v(void *p) {
 params_free((struct params *)p);
};

void params_from_json_v(char *json, size_t len, void *p) {
 params_from_json(json, len, (struct params*)p);
}

size_t params_to_json_v(char *json, size_t len, void *p) {
  return params_to_json(json, len, (struct params*)p);
}

void params_list_free_v(void **p) {
  params_list_free((struct params**)p);
}

void params_list_from_json_v(char *str, size_t len, void *p) {
  params_list_from_json(str, len, (struct params ***)p);
}

size_t params_list_to_json_v(char *str, size_t len, void *p){
  return params_list_to_json(str, len, (struct params **)p);
}


void params_cleanup(struct params *d) {
  /* specs/guild.modify-guild-member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->nick)
    free(d->nick);
  /* specs/guild.modify-guild-member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* specs/guild.modify-guild-member.json:13:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  //p->mute is a scalar
  /* specs/guild.modify-guild-member.json:14:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  //p->deaf is a scalar
  /* specs/guild.modify-guild-member.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
  //p->channel_id is a scalar
}

void params_init(struct params *p) {
  memset(p, 0, sizeof(struct params));
  /* specs/guild.modify-guild-member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/guild.modify-guild-member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */

  /* specs/guild.modify-guild-member.json:13:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */

  /* specs/guild.modify-guild-member.json:14:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */

  /* specs/guild.modify-guild-member.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */

}
struct params* params_alloc() {
  struct params *p= (struct params*)malloc(sizeof(struct params));
  params_init(p);
  return p;
}

void params_free(struct params *p) {
  params_cleanup(p);
  free(p);
}

void params_list_free(struct params **p) {
  ntl_free((void**)p, (vfvp)params_cleanup);
}

void params_list_from_json(char *str, size_t len, struct params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct params);
  d.init_elem = params_init_v;
  d.elem_from_buf = params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t params_list_to_json(char *str, size_t len, struct params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, params_to_json_v);
}

} // namespace modify_guild_member
} // namespace guild
} // namespace discord
