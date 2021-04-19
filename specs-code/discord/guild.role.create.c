/* This file is generated from specs/discord/guild.role.create.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_create_guild_role_params_from_json(char *json, size_t len, struct discord_create_guild_role_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):?s,"
  /* specs/discord/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "inject_if_not":0}'
  */
                "(permissions):s_as_hex_uint,"
  /* specs/discord/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(color):d,"
  /* specs/discord/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(hoist):b,"
  /* specs/discord/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(memtionable):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->name,
  /* specs/discord/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "inject_if_not":0}'
  */
                &p->permissions,
  /* specs/discord/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->color,
  /* specs/discord/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->hoist,
  /* specs/discord/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->memtionable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_create_guild_role_params_use_default_inject_settings(struct discord_create_guild_role_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "inject_if_not":0}'
  */
  if (p->permissions != 0)
    p->__M.arg_switches[1] = &p->permissions;

  /* specs/discord/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->color != 0)
    p->__M.arg_switches[2] = &p->color;

  /* specs/discord/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  if (p->hoist != false)
    p->__M.arg_switches[3] = &p->hoist;

  /* specs/discord/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  if (p->memtionable != false)
    p->__M.arg_switches[4] = &p->memtionable;

}

size_t discord_create_guild_role_params_to_json(char *json, size_t len, struct discord_create_guild_role_params *p)
{
  size_t r;
  discord_create_guild_role_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):s,"
  /* specs/discord/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "inject_if_not":0}'
  */
                "(permissions):s_as_hex_uint,"
  /* specs/discord/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(color):d,"
  /* specs/discord/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(hoist):b,"
  /* specs/discord/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(memtionable):b,"
                "@arg_switches:b",
  /* specs/discord/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                p->name,
  /* specs/discord/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "inject_if_not":0}'
  */
                &p->permissions,
  /* specs/discord/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->color,
  /* specs/discord/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->hoist,
  /* specs/discord/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->memtionable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_guild_role_params_cleanup_v(void *p) {
  discord_create_guild_role_params_cleanup((struct discord_create_guild_role_params *)p);
}

void discord_create_guild_role_params_init_v(void *p) {
  discord_create_guild_role_params_init((struct discord_create_guild_role_params *)p);
}

void discord_create_guild_role_params_free_v(void *p) {
 discord_create_guild_role_params_free((struct discord_create_guild_role_params *)p);
};

void discord_create_guild_role_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_guild_role_params_from_json(json, len, (struct discord_create_guild_role_params*)p);
}

size_t discord_create_guild_role_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_guild_role_params_to_json(json, len, (struct discord_create_guild_role_params*)p);
}

void discord_create_guild_role_params_list_free_v(void **p) {
  discord_create_guild_role_params_list_free((struct discord_create_guild_role_params**)p);
}

void discord_create_guild_role_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_guild_role_params_list_from_json(str, len, (struct discord_create_guild_role_params ***)p);
}

size_t discord_create_guild_role_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_guild_role_params_list_to_json(str, len, (struct discord_create_guild_role_params **)p);
}


void discord_create_guild_role_params_cleanup(struct discord_create_guild_role_params *d) {
  /* specs/discord/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->name)
    free(d->name);
  /* specs/discord/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "inject_if_not":0}'
  */
  //p->permissions is a scalar
  /* specs/discord/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->color is a scalar
  /* specs/discord/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  //p->hoist is a scalar
  /* specs/discord/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  //p->memtionable is a scalar
}

void discord_create_guild_role_params_init(struct discord_create_guild_role_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_role_params));
  /* specs/discord/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/discord/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "inject_if_not":0}'
  */

  /* specs/discord/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/discord/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */

  /* specs/discord/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */

}
struct discord_create_guild_role_params* discord_create_guild_role_params_alloc() {
  struct discord_create_guild_role_params *p= (struct discord_create_guild_role_params*)malloc(sizeof(struct discord_create_guild_role_params));
  discord_create_guild_role_params_init(p);
  return p;
}

void discord_create_guild_role_params_free(struct discord_create_guild_role_params *p) {
  discord_create_guild_role_params_cleanup(p);
  free(p);
}

void discord_create_guild_role_params_list_free(struct discord_create_guild_role_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_guild_role_params_cleanup);
}

void discord_create_guild_role_params_list_from_json(char *str, size_t len, struct discord_create_guild_role_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_role_params);
  d.init_elem = discord_create_guild_role_params_init_v;
  d.elem_from_buf = discord_create_guild_role_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_create_guild_role_params_list_to_json(char *str, size_t len, struct discord_create_guild_role_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_create_guild_role_params_to_json_v);
}

