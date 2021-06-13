/* This file is generated from specs/discord/guild.modify-guild-role-positions.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_modify_guild_role_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_role_positions_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.modify-guild-role-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"role"}'
  */
                "(id):F,"
  /* specs/discord/guild.modify-guild-role-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the role"}'
  */
                "(position):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.modify-guild-role-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"role"}'
  */
                orka_strtoull, &p->id,
  /* specs/discord/guild.modify-guild-role-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the role"}'
  */
                &p->position,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_modify_guild_role_positions_params_use_default_inject_settings(struct discord_modify_guild_role_positions_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.modify-guild-role-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"role"}'
  */
  if (p->id != 0)
    p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.modify-guild-role-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the role"}'
  */
  if (p->position != 0)
    p->__M.arg_switches[1] = &p->position;

}

size_t discord_modify_guild_role_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_role_positions_params *p)
{
  size_t r;
  discord_modify_guild_role_positions_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.modify-guild-role-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"role"}'
  */
                "(id):|F|,"
  /* specs/discord/guild.modify-guild-role-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the role"}'
  */
                "(position):d,"
                "@arg_switches:b",
  /* specs/discord/guild.modify-guild-role-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"role"}'
  */
                orka_ulltostr, &p->id,
  /* specs/discord/guild.modify-guild-role-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the role"}'
  */
                &p->position,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_guild_role_positions_params_cleanup_v(void *p) {
  discord_modify_guild_role_positions_params_cleanup((struct discord_modify_guild_role_positions_params *)p);
}

void discord_modify_guild_role_positions_params_init_v(void *p) {
  discord_modify_guild_role_positions_params_init((struct discord_modify_guild_role_positions_params *)p);
}

void discord_modify_guild_role_positions_params_free_v(void *p) {
 discord_modify_guild_role_positions_params_free((struct discord_modify_guild_role_positions_params *)p);
};

void discord_modify_guild_role_positions_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_guild_role_positions_params_from_json(json, len, (struct discord_modify_guild_role_positions_params*)p);
}

size_t discord_modify_guild_role_positions_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_guild_role_positions_params_to_json(json, len, (struct discord_modify_guild_role_positions_params*)p);
}

void discord_modify_guild_role_positions_params_list_free_v(void **p) {
  discord_modify_guild_role_positions_params_list_free((struct discord_modify_guild_role_positions_params**)p);
}

void discord_modify_guild_role_positions_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_guild_role_positions_params_list_from_json(str, len, (struct discord_modify_guild_role_positions_params ***)p);
}

size_t discord_modify_guild_role_positions_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_guild_role_positions_params_list_to_json(str, len, (struct discord_modify_guild_role_positions_params **)p);
}


void discord_modify_guild_role_positions_params_cleanup(struct discord_modify_guild_role_positions_params *d) {
  /* specs/discord/guild.modify-guild-role-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"role"}'
  */
  //p->id is a scalar
  /* specs/discord/guild.modify-guild-role-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the role"}'
  */
  //p->position is a scalar
}

void discord_modify_guild_role_positions_params_init(struct discord_modify_guild_role_positions_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_role_positions_params));
  /* specs/discord/guild.modify-guild-role-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"role"}'
  */

  /* specs/discord/guild.modify-guild-role-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the role"}'
  */

}
struct discord_modify_guild_role_positions_params* discord_modify_guild_role_positions_params_alloc() {
  struct discord_modify_guild_role_positions_params *p= (struct discord_modify_guild_role_positions_params*)malloc(sizeof(struct discord_modify_guild_role_positions_params));
  discord_modify_guild_role_positions_params_init(p);
  return p;
}

void discord_modify_guild_role_positions_params_free(struct discord_modify_guild_role_positions_params *p) {
  discord_modify_guild_role_positions_params_cleanup(p);
  free(p);
}

void discord_modify_guild_role_positions_params_list_free(struct discord_modify_guild_role_positions_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_guild_role_positions_params_cleanup);
}

void discord_modify_guild_role_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_positions_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_role_positions_params);
  d.init_elem = discord_modify_guild_role_positions_params_init_v;
  d.elem_from_buf = discord_modify_guild_role_positions_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_modify_guild_role_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_positions_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_guild_role_positions_params_to_json_v);
}

