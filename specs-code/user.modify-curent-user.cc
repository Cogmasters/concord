/* This file is generated from specs/user.modify-curent-user.json, Please don't edit it. */
#include "specs.h"
/*

*/
namespace discord {
namespace user {
namespace modify_current_user {

void params_from_json(char *json, size_t len, struct params *p)
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

size_t params_to_json(char *json, size_t len, struct params *p)
{
  size_t r;
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

void params_use_default_inject_settings(struct params *p)
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

void params_init(struct params *p) {
  memset(p, 0, sizeof(struct params));
  /* specs/user.modify-curent-user.json:11:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/user.modify-curent-user.json:12:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}'
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

} // namespace modify_current_user
} // namespace user
} // namespace discord
