/* This file is generated from specs/guild.role.create.json, Please don't edit it. */
#include "specs.h"
/*

*/
namespace discord {
namespace guild {
namespace create_guild_role {

void params_from_json(char *json, size_t len, struct params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):?s,"
  /* specs/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"discord::permissions::bitwise_flags" }, 
          "inject_if_not":0}'
  */
                "(permissions):s_as_hex_uint,"
  /* specs/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(color):d,"
  /* specs/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(hoist):b,"
  /* specs/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(memtionable):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->name,
  /* specs/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"discord::permissions::bitwise_flags" }, 
          "inject_if_not":0}'
  */
                &p->permissions,
  /* specs/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->color,
  /* specs/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->hoist,
  /* specs/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->memtionable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void params_use_default_inject_settings(struct params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[0] = p->name;

  /* specs/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"discord::permissions::bitwise_flags" }, 
          "inject_if_not":0}'
  */
  if (p->permissions != 0)
    p->__M.arg_switches[1] = &p->permissions;

  /* specs/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->color != 0)
    p->__M.arg_switches[2] = &p->color;

  /* specs/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  if (p->hoist != false)
    p->__M.arg_switches[3] = &p->hoist;

  /* specs/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  if (p->memtionable != false)
    p->__M.arg_switches[4] = &p->memtionable;

}

size_t params_to_json(char *json, size_t len, struct params *p)
{
  size_t r;
  params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):s,"
  /* specs/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"discord::permissions::bitwise_flags" }, 
          "inject_if_not":0}'
  */
                "(permissions):s_as_hex_uint,"
  /* specs/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(color):d,"
  /* specs/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(hoist):b,"
  /* specs/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(memtionable):b,"
                "@arg_switches:b",
  /* specs/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                p->name,
  /* specs/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"discord::permissions::bitwise_flags" }, 
          "inject_if_not":0}'
  */
                &p->permissions,
  /* specs/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->color,
  /* specs/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->hoist,
  /* specs/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->memtionable,
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
  /* specs/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->name)
    free(d->name);
  /* specs/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"discord::permissions::bitwise_flags" }, 
          "inject_if_not":0}'
  */
  //p->permissions is a scalar
  /* specs/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->color is a scalar
  /* specs/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  //p->hoist is a scalar
  /* specs/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  //p->memtionable is a scalar
}

void params_init(struct params *p) {
  memset(p, 0, sizeof(struct params));
  /* specs/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"discord::permissions::bitwise_flags" }, 
          "inject_if_not":0}'
  */

  /* specs/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */

  /* specs/guild.role.create.json:16:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
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
  orka_str_to_ntl(str, len, &d);
}

size_t params_list_to_json(char *str, size_t len, struct params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, params_to_json_v);
}

} // namespace create_guild_role
} // namespace guild
} // namespace discord
