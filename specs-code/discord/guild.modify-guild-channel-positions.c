/* This file is generated from specs/discord/guild.modify-guild-channel-positions.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_modify_guild_channel_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.modify-guild-channel-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"channel id"}'
  */
                "(id):F,"
  /* specs/discord/guild.modify-guild-channel-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}'
  */
                "(position):d,"
  /* specs/discord/guild.modify-guild-channel-positions.json:15:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}'
  */
                "(lock_permissions):b,"
  /* specs/discord/guild.modify-guild-channel-positions.json:17:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}'
  */
                "(parent_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.modify-guild-channel-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"channel id"}'
  */
                orka_strtoull, &p->id,
  /* specs/discord/guild.modify-guild-channel-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}'
  */
                &p->position,
  /* specs/discord/guild.modify-guild-channel-positions.json:15:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}'
  */
                &p->lock_permissions,
  /* specs/discord/guild.modify-guild-channel-positions.json:17:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}'
  */
                orka_strtoull, &p->parent_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_modify_guild_channel_positions_params_use_default_inject_settings(struct discord_modify_guild_channel_positions_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.modify-guild-channel-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"channel id"}'
  */
  if (p->id != 0)
    p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.modify-guild-channel-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}'
  */
  if (p->position != 0)
    p->__M.arg_switches[1] = &p->position;

  /* specs/discord/guild.modify-guild-channel-positions.json:15:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}'
  */
  if (p->lock_permissions != false)
    p->__M.arg_switches[2] = &p->lock_permissions;

  /* specs/discord/guild.modify-guild-channel-positions.json:17:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}'
  */
  if (p->parent_id != 0)
    p->__M.arg_switches[3] = &p->parent_id;

}

size_t discord_modify_guild_channel_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params *p)
{
  size_t r;
  discord_modify_guild_channel_positions_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.modify-guild-channel-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"channel id"}'
  */
                "(id):|F|,"
  /* specs/discord/guild.modify-guild-channel-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}'
  */
                "(position):d,"
  /* specs/discord/guild.modify-guild-channel-positions.json:15:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}'
  */
                "(lock_permissions):b,"
  /* specs/discord/guild.modify-guild-channel-positions.json:17:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}'
  */
                "(parent_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/guild.modify-guild-channel-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"channel id"}'
  */
                orka_ulltostr, &p->id,
  /* specs/discord/guild.modify-guild-channel-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}'
  */
                &p->position,
  /* specs/discord/guild.modify-guild-channel-positions.json:15:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}'
  */
                &p->lock_permissions,
  /* specs/discord/guild.modify-guild-channel-positions.json:17:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}'
  */
                orka_ulltostr, &p->parent_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_guild_channel_positions_params_cleanup_v(void *p) {
  discord_modify_guild_channel_positions_params_cleanup((struct discord_modify_guild_channel_positions_params *)p);
}

void discord_modify_guild_channel_positions_params_init_v(void *p) {
  discord_modify_guild_channel_positions_params_init((struct discord_modify_guild_channel_positions_params *)p);
}

void discord_modify_guild_channel_positions_params_free_v(void *p) {
 discord_modify_guild_channel_positions_params_free((struct discord_modify_guild_channel_positions_params *)p);
};

void discord_modify_guild_channel_positions_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_guild_channel_positions_params_from_json(json, len, (struct discord_modify_guild_channel_positions_params*)p);
}

size_t discord_modify_guild_channel_positions_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_guild_channel_positions_params_to_json(json, len, (struct discord_modify_guild_channel_positions_params*)p);
}

void discord_modify_guild_channel_positions_params_list_free_v(void **p) {
  discord_modify_guild_channel_positions_params_list_free((struct discord_modify_guild_channel_positions_params**)p);
}

void discord_modify_guild_channel_positions_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_guild_channel_positions_params_list_from_json(str, len, (struct discord_modify_guild_channel_positions_params ***)p);
}

size_t discord_modify_guild_channel_positions_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_guild_channel_positions_params_list_to_json(str, len, (struct discord_modify_guild_channel_positions_params **)p);
}


void discord_modify_guild_channel_positions_params_cleanup(struct discord_modify_guild_channel_positions_params *d) {
  /* specs/discord/guild.modify-guild-channel-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"channel id"}'
  */
  //p->id is a scalar
  /* specs/discord/guild.modify-guild-channel-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}'
  */
  //p->position is a scalar
  /* specs/discord/guild.modify-guild-channel-positions.json:15:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}'
  */
  //p->lock_permissions is a scalar
  /* specs/discord/guild.modify-guild-channel-positions.json:17:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}'
  */
  //p->parent_id is a scalar
}

void discord_modify_guild_channel_positions_params_init(struct discord_modify_guild_channel_positions_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_channel_positions_params));
  /* specs/discord/guild.modify-guild-channel-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"channel id"}'
  */

  /* specs/discord/guild.modify-guild-channel-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}'
  */

  /* specs/discord/guild.modify-guild-channel-positions.json:15:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}'
  */

  /* specs/discord/guild.modify-guild-channel-positions.json:17:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}'
  */

}
struct discord_modify_guild_channel_positions_params* discord_modify_guild_channel_positions_params_alloc() {
  struct discord_modify_guild_channel_positions_params *p= (struct discord_modify_guild_channel_positions_params*)malloc(sizeof(struct discord_modify_guild_channel_positions_params));
  discord_modify_guild_channel_positions_params_init(p);
  return p;
}

void discord_modify_guild_channel_positions_params_free(struct discord_modify_guild_channel_positions_params *p) {
  discord_modify_guild_channel_positions_params_cleanup(p);
  free(p);
}

void discord_modify_guild_channel_positions_params_list_free(struct discord_modify_guild_channel_positions_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_guild_channel_positions_params_cleanup);
}

void discord_modify_guild_channel_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_channel_positions_params);
  d.init_elem = discord_modify_guild_channel_positions_params_init_v;
  d.elem_from_buf = discord_modify_guild_channel_positions_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_modify_guild_channel_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_guild_channel_positions_params_to_json_v);
}

