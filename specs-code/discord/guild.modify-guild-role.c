/* This file is generated from specs/discord/guild.modify-guild-role.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_modify_guild_role_params_from_json(char *json, size_t len, struct discord_modify_guild_role_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.modify-guild-role.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"name of the role"}'
  */
                "(name):?s,"
  /* specs/discord/guild.modify-guild-role.json:13:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}'
  */
                "(permissions):s_as_hex_uint,"
  /* specs/discord/guild.modify-guild-role.json:15:20
     '{ "name": "color", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"RGB color value"}'
  */
                "(color):d,"
  /* specs/discord/guild.modify-guild-role.json:17:20
     '{ "name": "hoist", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}'
  */
                "(hoist):b,"
  /* specs/discord/guild.modify-guild-role.json:19:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}'
  */
                "(mentionable):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.modify-guild-role.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"name of the role"}'
  */
                &p->name,
  /* specs/discord/guild.modify-guild-role.json:13:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}'
  */
                &p->permissions,
  /* specs/discord/guild.modify-guild-role.json:15:20
     '{ "name": "color", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"RGB color value"}'
  */
                &p->color,
  /* specs/discord/guild.modify-guild-role.json:17:20
     '{ "name": "hoist", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}'
  */
                &p->hoist,
  /* specs/discord/guild.modify-guild-role.json:19:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}'
  */
                &p->mentionable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_modify_guild_role_params_use_default_inject_settings(struct discord_modify_guild_role_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.modify-guild-role.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"name of the role"}'
  */
  if (p->name != NULL)
    p->__M.arg_switches[0] = p->name;

  /* specs/discord/guild.modify-guild-role.json:13:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}'
  */
  if (p->permissions != 0)
    p->__M.arg_switches[1] = &p->permissions;

  /* specs/discord/guild.modify-guild-role.json:15:20
     '{ "name": "color", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"RGB color value"}'
  */
  if (p->color != 0)
    p->__M.arg_switches[2] = &p->color;

  /* specs/discord/guild.modify-guild-role.json:17:20
     '{ "name": "hoist", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}'
  */
  if (p->hoist != false)
    p->__M.arg_switches[3] = &p->hoist;

  /* specs/discord/guild.modify-guild-role.json:19:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}'
  */
  if (p->mentionable != false)
    p->__M.arg_switches[4] = &p->mentionable;

}

size_t discord_modify_guild_role_params_to_json(char *json, size_t len, struct discord_modify_guild_role_params *p)
{
  size_t r;
  discord_modify_guild_role_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.modify-guild-role.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"name of the role"}'
  */
                "(name):s,"
  /* specs/discord/guild.modify-guild-role.json:13:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}'
  */
                "(permissions):s_as_hex_uint,"
  /* specs/discord/guild.modify-guild-role.json:15:20
     '{ "name": "color", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"RGB color value"}'
  */
                "(color):d,"
  /* specs/discord/guild.modify-guild-role.json:17:20
     '{ "name": "hoist", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}'
  */
                "(hoist):b,"
  /* specs/discord/guild.modify-guild-role.json:19:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}'
  */
                "(mentionable):b,"
                "@arg_switches:b",
  /* specs/discord/guild.modify-guild-role.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"name of the role"}'
  */
                p->name,
  /* specs/discord/guild.modify-guild-role.json:13:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}'
  */
                &p->permissions,
  /* specs/discord/guild.modify-guild-role.json:15:20
     '{ "name": "color", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"RGB color value"}'
  */
                &p->color,
  /* specs/discord/guild.modify-guild-role.json:17:20
     '{ "name": "hoist", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}'
  */
                &p->hoist,
  /* specs/discord/guild.modify-guild-role.json:19:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}'
  */
                &p->mentionable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_guild_role_params_cleanup_v(void *p) {
  discord_modify_guild_role_params_cleanup((struct discord_modify_guild_role_params *)p);
}

void discord_modify_guild_role_params_init_v(void *p) {
  discord_modify_guild_role_params_init((struct discord_modify_guild_role_params *)p);
}

void discord_modify_guild_role_params_free_v(void *p) {
 discord_modify_guild_role_params_free((struct discord_modify_guild_role_params *)p);
};

void discord_modify_guild_role_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_guild_role_params_from_json(json, len, (struct discord_modify_guild_role_params*)p);
}

size_t discord_modify_guild_role_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_guild_role_params_to_json(json, len, (struct discord_modify_guild_role_params*)p);
}

void discord_modify_guild_role_params_list_free_v(void **p) {
  discord_modify_guild_role_params_list_free((struct discord_modify_guild_role_params**)p);
}

void discord_modify_guild_role_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_guild_role_params_list_from_json(str, len, (struct discord_modify_guild_role_params ***)p);
}

size_t discord_modify_guild_role_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_guild_role_params_list_to_json(str, len, (struct discord_modify_guild_role_params **)p);
}


void discord_modify_guild_role_params_cleanup(struct discord_modify_guild_role_params *d) {
  /* specs/discord/guild.modify-guild-role.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"name of the role"}'
  */
  if (d->name)
    free(d->name);
  /* specs/discord/guild.modify-guild-role.json:13:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}'
  */
  //p->permissions is a scalar
  /* specs/discord/guild.modify-guild-role.json:15:20
     '{ "name": "color", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"RGB color value"}'
  */
  //p->color is a scalar
  /* specs/discord/guild.modify-guild-role.json:17:20
     '{ "name": "hoist", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}'
  */
  //p->hoist is a scalar
  /* specs/discord/guild.modify-guild-role.json:19:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}'
  */
  //p->mentionable is a scalar
}

void discord_modify_guild_role_params_init(struct discord_modify_guild_role_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_role_params));
  /* specs/discord/guild.modify-guild-role.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"name of the role"}'
  */

  /* specs/discord/guild.modify-guild-role.json:13:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}'
  */

  /* specs/discord/guild.modify-guild-role.json:15:20
     '{ "name": "color", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"RGB color value"}'
  */

  /* specs/discord/guild.modify-guild-role.json:17:20
     '{ "name": "hoist", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}'
  */

  /* specs/discord/guild.modify-guild-role.json:19:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}'
  */

}
struct discord_modify_guild_role_params* discord_modify_guild_role_params_alloc() {
  struct discord_modify_guild_role_params *p= (struct discord_modify_guild_role_params*)malloc(sizeof(struct discord_modify_guild_role_params));
  discord_modify_guild_role_params_init(p);
  return p;
}

void discord_modify_guild_role_params_free(struct discord_modify_guild_role_params *p) {
  discord_modify_guild_role_params_cleanup(p);
  free(p);
}

void discord_modify_guild_role_params_list_free(struct discord_modify_guild_role_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_guild_role_params_cleanup);
}

void discord_modify_guild_role_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_role_params);
  d.init_elem = discord_modify_guild_role_params_init_v;
  d.elem_from_buf = discord_modify_guild_role_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_modify_guild_role_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_guild_role_params_to_json_v);
}

