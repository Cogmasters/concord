/* This file is generated from specs/user.modify-curent-user.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_user_modify_current_user_params_from_json(char *json, size_t len, struct discord_user_modify_current_user_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/user.modify-curent-user.json:11:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}'
  */
                "(username):?s,"
  /* specs/user.modify-curent-user.json:12:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}'
  */
                "(avatar):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/user.modify-curent-user.json:11:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->username,
  /* specs/user.modify-curent-user.json:12:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}'
  */
                &p->avatar,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_user_modify_current_user_params_use_default_inject_settings(struct discord_user_modify_current_user_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/user.modify-curent-user.json:11:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[0] = p->username;

  /* specs/user.modify-curent-user.json:12:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}'
  */
  p->__M.arg_switches[1] = p->avatar;

}

size_t discord_user_modify_current_user_params_to_json(char *json, size_t len, struct discord_user_modify_current_user_params *p)
{
  size_t r;
  discord_user_modify_current_user_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/user.modify-curent-user.json:11:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}'
  */
                "(username):s,"
  /* specs/user.modify-curent-user.json:12:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}'
  */
                "(avatar):s,"
                "@arg_switches:b",
  /* specs/user.modify-curent-user.json:11:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}'
  */
                p->username,
  /* specs/user.modify-curent-user.json:12:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}'
  */
                p->avatar,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_user_modify_current_user_params_cleanup_v(void *p) {
  discord_user_modify_current_user_params_cleanup((struct discord_user_modify_current_user_params *)p);
}

void discord_user_modify_current_user_params_init_v(void *p) {
  discord_user_modify_current_user_params_init((struct discord_user_modify_current_user_params *)p);
}

void discord_user_modify_current_user_params_free_v(void *p) {
 discord_user_modify_current_user_params_free((struct discord_user_modify_current_user_params *)p);
};

void discord_user_modify_current_user_params_from_json_v(char *json, size_t len, void *p) {
 discord_user_modify_current_user_params_from_json(json, len, (struct discord_user_modify_current_user_params*)p);
}

size_t discord_user_modify_current_user_params_to_json_v(char *json, size_t len, void *p) {
  return discord_user_modify_current_user_params_to_json(json, len, (struct discord_user_modify_current_user_params*)p);
}

void discord_user_modify_current_user_params_list_free_v(void **p) {
  discord_user_modify_current_user_params_list_free((struct discord_user_modify_current_user_params**)p);
}

void discord_user_modify_current_user_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_user_modify_current_user_params_list_from_json(str, len, (struct discord_user_modify_current_user_params ***)p);
}

size_t discord_user_modify_current_user_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_user_modify_current_user_params_list_to_json(str, len, (struct discord_user_modify_current_user_params **)p);
}


void discord_user_modify_current_user_params_cleanup(struct discord_user_modify_current_user_params *d) {
  /* specs/user.modify-curent-user.json:11:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->username)
    free(d->username);
  /* specs/user.modify-curent-user.json:12:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}'
  */
  if (d->avatar)
    free(d->avatar);
}

void discord_user_modify_current_user_params_init(struct discord_user_modify_current_user_params *p) {
  memset(p, 0, sizeof(struct discord_user_modify_current_user_params));
  /* specs/user.modify-curent-user.json:11:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/user.modify-curent-user.json:12:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}'
  */

}
struct discord_user_modify_current_user_params* discord_user_modify_current_user_params_alloc() {
  struct discord_user_modify_current_user_params *p= (struct discord_user_modify_current_user_params*)malloc(sizeof(struct discord_user_modify_current_user_params));
  discord_user_modify_current_user_params_init(p);
  return p;
}

void discord_user_modify_current_user_params_free(struct discord_user_modify_current_user_params *p) {
  discord_user_modify_current_user_params_cleanup(p);
  free(p);
}

void discord_user_modify_current_user_params_list_free(struct discord_user_modify_current_user_params **p) {
  ntl_free((void**)p, (vfvp)discord_user_modify_current_user_params_cleanup);
}

void discord_user_modify_current_user_params_list_from_json(char *str, size_t len, struct discord_user_modify_current_user_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_user_modify_current_user_params);
  d.init_elem = discord_user_modify_current_user_params_init_v;
  d.elem_from_buf = discord_user_modify_current_user_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_user_modify_current_user_params_list_to_json(char *str, size_t len, struct discord_user_modify_current_user_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_user_modify_current_user_params_to_json_v);
}

