/* This file is generated from specs/reddit/oauth2.json, Please don't edit it. */
/**
 * @file specs-code/reddit/oauth2.c
 * @see https://github.com/reddit-archive/reddit/wiki/OAuth2-Quick-Start-Example
 */

#include "specs-deps.h"
#include "reddit.h"

void reddit_access_token_params_from_json(char *json, size_t len, struct reddit_access_token_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct reddit_access_token_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
                "(grant_type):?s,"
  /* specs/reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
                "(username):?s,"
  /* specs/reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
                "(password):?s,"
  /* specs/reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
                "(code):?s,"
  /* specs/reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
                "(redirect_uri):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
                &p->grant_type,
  /* specs/reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
                &p->username,
  /* specs/reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
                &p->password,
  /* specs/reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
                &p->code,
  /* specs/reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
                &p->redirect_uri,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void reddit_access_token_params_use_default_inject_settings(struct reddit_access_token_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
  p->__M.arg_switches[0] = p->grant_type;

  /* specs/reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
  p->__M.arg_switches[1] = p->username;

  /* specs/reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
  p->__M.arg_switches[2] = p->password;

  /* specs/reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
  p->__M.arg_switches[3] = p->code;

  /* specs/reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
  p->__M.arg_switches[4] = p->redirect_uri;

}

size_t reddit_access_token_params_to_json(char *json, size_t len, struct reddit_access_token_params *p)
{
  size_t r;
  reddit_access_token_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
                "(grant_type):s,"
  /* specs/reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
                "(username):s,"
  /* specs/reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
                "(password):s,"
  /* specs/reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
                "(code):s,"
  /* specs/reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
                "(redirect_uri):s,"
                "@arg_switches:b",
  /* specs/reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
                p->grant_type,
  /* specs/reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
                p->username,
  /* specs/reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
                p->password,
  /* specs/reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
                p->code,
  /* specs/reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
                p->redirect_uri,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void reddit_access_token_params_cleanup_v(void *p) {
  reddit_access_token_params_cleanup((struct reddit_access_token_params *)p);
}

void reddit_access_token_params_init_v(void *p) {
  reddit_access_token_params_init((struct reddit_access_token_params *)p);
}

void reddit_access_token_params_from_json_v(char *json, size_t len, void *pp) {
 reddit_access_token_params_from_json(json, len, (struct reddit_access_token_params**)pp);
}

size_t reddit_access_token_params_to_json_v(char *json, size_t len, void *p) {
  return reddit_access_token_params_to_json(json, len, (struct reddit_access_token_params*)p);
}

void reddit_access_token_params_list_free_v(void **p) {
  reddit_access_token_params_list_free((struct reddit_access_token_params**)p);
}

void reddit_access_token_params_list_from_json_v(char *str, size_t len, void *p) {
  reddit_access_token_params_list_from_json(str, len, (struct reddit_access_token_params ***)p);
}

size_t reddit_access_token_params_list_to_json_v(char *str, size_t len, void *p){
  return reddit_access_token_params_list_to_json(str, len, (struct reddit_access_token_params **)p);
}


void reddit_access_token_params_cleanup(struct reddit_access_token_params *d) {
  /* specs/reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
  if (d->grant_type)
    free(d->grant_type);
  /* specs/reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
  if (d->username)
    free(d->username);
  /* specs/reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
  if (d->password)
    free(d->password);
  /* specs/reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
  if (d->code)
    free(d->code);
  /* specs/reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
  if (d->redirect_uri)
    free(d->redirect_uri);
}

void reddit_access_token_params_init(struct reddit_access_token_params *p) {
  memset(p, 0, sizeof(struct reddit_access_token_params));
  /* specs/reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */

  /* specs/reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */

  /* specs/reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */

  /* specs/reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */

  /* specs/reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */

}
void reddit_access_token_params_list_free(struct reddit_access_token_params **p) {
  ntl_free((void**)p, (vfvp)reddit_access_token_params_cleanup);
}

void reddit_access_token_params_list_from_json(char *str, size_t len, struct reddit_access_token_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct reddit_access_token_params);
  d.init_elem = NULL;
  d.elem_from_buf = reddit_access_token_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t reddit_access_token_params_list_to_json(char *str, size_t len, struct reddit_access_token_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, reddit_access_token_params_to_json_v);
}

