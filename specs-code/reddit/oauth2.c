/* This file is generated from reddit/oauth2.json, Please don't edit it. */
/**
 * @file specs-code/reddit/oauth2.c
 * @see https://github.com/reddit-archive/reddit/wiki/OAuth2-Quick-Start-Example
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "reddit.h"

void reddit_access_token_params_from_json_p(char *json, size_t len, struct reddit_access_token_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  reddit_access_token_params_from_json(json, len, *pp);
}
void reddit_access_token_params_from_json(char *json, size_t len, struct reddit_access_token_params *p)
{
  reddit_access_token_params_init(p);
  json_extract(json, len, 
  /* reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
                "(grant_type):?s,"
  /* reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
                "(username):?s,"
  /* reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
                "(password):?s,"
  /* reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
                "(code):?s,"
  /* reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
                "(redirect_uri):?s,",
  /* reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
                &p->grant_type,
  /* reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
                &p->username,
  /* reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
                &p->password,
  /* reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
                &p->code,
  /* reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
                &p->redirect_uri);
}

size_t reddit_access_token_params_to_json(char *json, size_t len, struct reddit_access_token_params *p)
{
  size_t r;
  void *arg_switches[5]={NULL};
  /* reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
  arg_switches[0] = p->grant_type;

  /* reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
  arg_switches[1] = p->username;

  /* reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
  arg_switches[2] = p->password;

  /* reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
  arg_switches[3] = p->code;

  /* reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
  arg_switches[4] = p->redirect_uri;

  r=json_inject(json, len, 
  /* reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
                "(grant_type):s,"
  /* reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
                "(username):s,"
  /* reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
                "(password):s,"
  /* reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
                "(code):s,"
  /* reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
                "(redirect_uri):s,"
                "@arg_switches:b",
  /* reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
                p->grant_type,
  /* reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
                p->username,
  /* reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
                p->password,
  /* reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
                p->code,
  /* reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
                p->redirect_uri,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void reddit_access_token_params_cleanup_v(void *p) {
  reddit_access_token_params_cleanup((struct reddit_access_token_params *)p);
}

void reddit_access_token_params_init_v(void *p) {
  reddit_access_token_params_init((struct reddit_access_token_params *)p);
}

void reddit_access_token_params_from_json_v(char *json, size_t len, void *p) {
 reddit_access_token_params_from_json(json, len, (struct reddit_access_token_params*)p);
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
  /* reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
  if (d->grant_type)
    free(d->grant_type);
  /* reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
  if (d->username)
    free(d->username);
  /* reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
  if (d->password)
    free(d->password);
  /* reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
  if (d->code)
    free(d->code);
  /* reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
  if (d->redirect_uri)
    free(d->redirect_uri);
}

void reddit_access_token_params_init(struct reddit_access_token_params *p) {
  memset(p, 0, sizeof(struct reddit_access_token_params));
  /* reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */

  /* reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */

  /* reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */

  /* reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */

  /* reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */

}
void reddit_access_token_params_list_free(struct reddit_access_token_params **p) {
  ntl_free((void**)p, (void(*)(void*))reddit_access_token_params_cleanup);
}

void reddit_access_token_params_list_from_json(char *str, size_t len, struct reddit_access_token_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct reddit_access_token_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))reddit_access_token_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t reddit_access_token_params_list_to_json(char *str, size_t len, struct reddit_access_token_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))reddit_access_token_params_to_json);
}

