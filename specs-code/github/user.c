/* This file is generated from github/user.json, Please don't edit it. */
/**
 * @file specs-code/github/user.c
 * @see https://docs.github.com/en/rest/reference/users#get-a-user
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "github.h"

void github_user_from_json_p(char *json, size_t len, struct github_user **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  github_user_from_json(json, len, *pp);
}
void github_user_from_json(char *json, size_t len, struct github_user *p)
{
  github_user_init(p);
  json_extract(json, len, 
  /* github/user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
                "(login):?s,"
  /* github/user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
                "(id):d,"
  /* github/user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                "(node_id):?s,"
  /* github/user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
                "(avatar_url):?s,"
  /* github/user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
                "(gravatar_id):?s,"
  /* github/user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                "(html_url):?s,"
  /* github/user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                "(type):?s,"
  /* github/user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
                "(site_admin):b,"
  /* github/user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* github/user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
                "(company):?s,"
  /* github/user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
                "(blog):?s,"
  /* github/user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
                "(location):?s,"
  /* github/user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
                "(email):?s,"
  /* github/user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
                "(hireable):?s,"
  /* github/user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
                "(bio):?s,"
  /* github/user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
                "(public_repos):d,"
  /* github/user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
                "(public_gists):d,"
  /* github/user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
                "(followers):d,"
  /* github/user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
                "(following):d,"
  /* github/user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                "(created_at):?s,"
  /* github/user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                "(updated_at):?s,",
  /* github/user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
                &p->login,
  /* github/user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
                &p->id,
  /* github/user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                &p->node_id,
  /* github/user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
                &p->avatar_url,
  /* github/user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
                &p->gravatar_id,
  /* github/user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                &p->html_url,
  /* github/user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                &p->type,
  /* github/user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
                &p->site_admin,
  /* github/user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                &p->name,
  /* github/user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
                &p->company,
  /* github/user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
                &p->blog,
  /* github/user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
                &p->location,
  /* github/user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
                &p->email,
  /* github/user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
                &p->hireable,
  /* github/user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
                &p->bio,
  /* github/user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
                &p->public_repos,
  /* github/user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
                &p->public_gists,
  /* github/user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
                &p->followers,
  /* github/user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
                &p->following,
  /* github/user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                &p->created_at,
  /* github/user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                &p->updated_at);
}

size_t github_user_to_json(char *json, size_t len, struct github_user *p)
{
  size_t r;
  void *arg_switches[21]={NULL};
  /* github/user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[0] = p->login;

  /* github/user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
  arg_switches[1] = &p->id;

  /* github/user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[2] = p->node_id;

  /* github/user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[3] = p->avatar_url;

  /* github/user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[4] = p->gravatar_id;

  /* github/user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[5] = p->html_url;

  /* github/user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[6] = p->type;

  /* github/user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
  arg_switches[7] = &p->site_admin;

  /* github/user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[8] = p->name;

  /* github/user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[9] = p->company;

  /* github/user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[10] = p->blog;

  /* github/user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[11] = p->location;

  /* github/user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[12] = p->email;

  /* github/user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[13] = p->hireable;

  /* github/user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[14] = p->bio;

  /* github/user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
  arg_switches[15] = &p->public_repos;

  /* github/user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
  arg_switches[16] = &p->public_gists;

  /* github/user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
  arg_switches[17] = &p->followers;

  /* github/user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
  arg_switches[18] = &p->following;

  /* github/user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[19] = p->created_at;

  /* github/user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[20] = p->updated_at;

  r=json_inject(json, len, 
  /* github/user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
                "(login):s,"
  /* github/user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
                "(id):d,"
  /* github/user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                "(node_id):s,"
  /* github/user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
                "(avatar_url):s,"
  /* github/user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
                "(gravatar_id):s,"
  /* github/user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                "(html_url):s,"
  /* github/user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                "(type):s,"
  /* github/user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
                "(site_admin):b,"
  /* github/user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):s,"
  /* github/user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
                "(company):s,"
  /* github/user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
                "(blog):s,"
  /* github/user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
                "(location):s,"
  /* github/user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
                "(email):s,"
  /* github/user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
                "(hireable):s,"
  /* github/user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
                "(bio):s,"
  /* github/user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
                "(public_repos):d,"
  /* github/user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
                "(public_gists):d,"
  /* github/user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
                "(followers):d,"
  /* github/user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
                "(following):d,"
  /* github/user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                "(created_at):s,"
  /* github/user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                "(updated_at):s,"
                "@arg_switches:b",
  /* github/user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
                p->login,
  /* github/user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
                &p->id,
  /* github/user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                p->node_id,
  /* github/user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
                p->avatar_url,
  /* github/user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
                p->gravatar_id,
  /* github/user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                p->html_url,
  /* github/user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                p->type,
  /* github/user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
                &p->site_admin,
  /* github/user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                p->name,
  /* github/user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
                p->company,
  /* github/user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
                p->blog,
  /* github/user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
                p->location,
  /* github/user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
                p->email,
  /* github/user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
                p->hireable,
  /* github/user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
                p->bio,
  /* github/user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
                &p->public_repos,
  /* github/user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
                &p->public_gists,
  /* github/user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
                &p->followers,
  /* github/user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
                &p->following,
  /* github/user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                p->created_at,
  /* github/user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                p->updated_at,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void github_user_cleanup_v(void *p) {
  github_user_cleanup((struct github_user *)p);
}

void github_user_init_v(void *p) {
  github_user_init((struct github_user *)p);
}

void github_user_from_json_v(char *json, size_t len, void *p) {
 github_user_from_json(json, len, (struct github_user*)p);
}

size_t github_user_to_json_v(char *json, size_t len, void *p) {
  return github_user_to_json(json, len, (struct github_user*)p);
}

void github_user_list_free_v(void **p) {
  github_user_list_free((struct github_user**)p);
}

void github_user_list_from_json_v(char *str, size_t len, void *p) {
  github_user_list_from_json(str, len, (struct github_user ***)p);
}

size_t github_user_list_to_json_v(char *str, size_t len, void *p){
  return github_user_list_to_json(str, len, (struct github_user **)p);
}


void github_user_cleanup(struct github_user *d) {
  /* github/user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
  if (d->login)
    free(d->login);
  /* github/user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
  (void)d->id;
  /* github/user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  if (d->node_id)
    free(d->node_id);
  /* github/user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
  if (d->avatar_url)
    free(d->avatar_url);
  /* github/user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
  if (d->gravatar_id)
    free(d->gravatar_id);
  /* github/user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
  if (d->html_url)
    free(d->html_url);
  /* github/user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  if (d->type)
    free(d->type);
  /* github/user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
  (void)d->site_admin;
  /* github/user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* github/user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
  if (d->company)
    free(d->company);
  /* github/user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
  if (d->blog)
    free(d->blog);
  /* github/user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
  if (d->location)
    free(d->location);
  /* github/user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
  if (d->email)
    free(d->email);
  /* github/user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
  if (d->hireable)
    free(d->hireable);
  /* github/user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
  if (d->bio)
    free(d->bio);
  /* github/user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
  (void)d->public_repos;
  /* github/user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
  (void)d->public_gists;
  /* github/user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
  (void)d->followers;
  /* github/user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
  (void)d->following;
  /* github/user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
  if (d->created_at)
    free(d->created_at);
  /* github/user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
  if (d->updated_at)
    free(d->updated_at);
}

void github_user_init(struct github_user *p) {
  memset(p, 0, sizeof(struct github_user));
  /* github/user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */

  /* github/user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */

  /* github/user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */

  /* github/user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */

  /* github/user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */

  /* github/user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */

  /* github/user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */

  /* github/user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */

}
void github_user_list_free(struct github_user **p) {
  ntl_free((void**)p, (void(*)(void*))github_user_cleanup);
}

void github_user_list_from_json(char *str, size_t len, struct github_user ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct github_user);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))github_user_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t github_user_list_to_json(char *str, size_t len, struct github_user **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))github_user_to_json);
}

