/* This file is generated from specs/github/github-user.json, Please don't edit it. */
/**
 * @file specs-code/github/github-user.c
 * @see https://docs.github.com/en/rest/reference/users#get-a-user
 */

#include "specs-deps.h"
#include "github.h"

void github_user_from_json(char *json, size_t len, struct github_user **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct github_user *p = *pp;
  r=json_extract(json, len, 
  /* specs/github/github-user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
                "(login):?s,"
  /* specs/github/github-user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
                "(id):d,"
  /* specs/github/github-user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                "(node_id):?s,"
  /* specs/github/github-user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
                "(avatar_url):?s,"
  /* specs/github/github-user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
                "(gravatar_id):?s,"
  /* specs/github/github-user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                "(html_url):?s,"
  /* specs/github/github-user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                "(type):?s,"
  /* specs/github/github-user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
                "(site_admin):b,"
  /* specs/github/github-user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* specs/github/github-user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
                "(company):?s,"
  /* specs/github/github-user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
                "(blog):?s,"
  /* specs/github/github-user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
                "(location):?s,"
  /* specs/github/github-user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
                "(email):?s,"
  /* specs/github/github-user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
                "(hireable):?s,"
  /* specs/github/github-user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
                "(bio):?s,"
  /* specs/github/github-user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
                "(public_repos):d,"
  /* specs/github/github-user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
                "(public_gists):d,"
  /* specs/github/github-user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
                "(followers):d,"
  /* specs/github/github-user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
                "(following):d,"
  /* specs/github/github-user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                "(created_at):?s,"
  /* specs/github/github-user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                "(updated_at):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/github/github-user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
                &p->login,
  /* specs/github/github-user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
                &p->id,
  /* specs/github/github-user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                &p->node_id,
  /* specs/github/github-user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
                &p->avatar_url,
  /* specs/github/github-user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
                &p->gravatar_id,
  /* specs/github/github-user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                &p->html_url,
  /* specs/github/github-user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                &p->type,
  /* specs/github/github-user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
                &p->site_admin,
  /* specs/github/github-user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                &p->name,
  /* specs/github/github-user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
                &p->company,
  /* specs/github/github-user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
                &p->blog,
  /* specs/github/github-user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
                &p->location,
  /* specs/github/github-user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
                &p->email,
  /* specs/github/github-user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
                &p->hireable,
  /* specs/github/github-user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
                &p->bio,
  /* specs/github/github-user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
                &p->public_repos,
  /* specs/github/github-user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
                &p->public_gists,
  /* specs/github/github-user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
                &p->followers,
  /* specs/github/github-user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
                &p->following,
  /* specs/github/github-user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                &p->created_at,
  /* specs/github/github-user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                &p->updated_at,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void github_user_use_default_inject_settings(struct github_user *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/github/github-user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[0] = p->login;

  /* specs/github/github-user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
  p->__M.arg_switches[1] = &p->id;

  /* specs/github/github-user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[2] = p->node_id;

  /* specs/github/github-user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[3] = p->avatar_url;

  /* specs/github/github-user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[4] = p->gravatar_id;

  /* specs/github/github-user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[5] = p->html_url;

  /* specs/github/github-user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[6] = p->type;

  /* specs/github/github-user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[7] = &p->site_admin;

  /* specs/github/github-user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[8] = p->name;

  /* specs/github/github-user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[9] = p->company;

  /* specs/github/github-user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[10] = p->blog;

  /* specs/github/github-user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[11] = p->location;

  /* specs/github/github-user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[12] = p->email;

  /* specs/github/github-user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[13] = p->hireable;

  /* specs/github/github-user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[14] = p->bio;

  /* specs/github/github-user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
  p->__M.arg_switches[15] = &p->public_repos;

  /* specs/github/github-user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
  p->__M.arg_switches[16] = &p->public_gists;

  /* specs/github/github-user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
  p->__M.arg_switches[17] = &p->followers;

  /* specs/github/github-user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
  p->__M.arg_switches[18] = &p->following;

  /* specs/github/github-user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[19] = p->created_at;

  /* specs/github/github-user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[20] = p->updated_at;

}

size_t github_user_to_json(char *json, size_t len, struct github_user *p)
{
  size_t r;
  github_user_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/github/github-user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
                "(login):s,"
  /* specs/github/github-user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
                "(id):d,"
  /* specs/github/github-user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                "(node_id):s,"
  /* specs/github/github-user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
                "(avatar_url):s,"
  /* specs/github/github-user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
                "(gravatar_id):s,"
  /* specs/github/github-user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                "(html_url):s,"
  /* specs/github/github-user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                "(type):s,"
  /* specs/github/github-user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
                "(site_admin):b,"
  /* specs/github/github-user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):s,"
  /* specs/github/github-user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
                "(company):s,"
  /* specs/github/github-user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
                "(blog):s,"
  /* specs/github/github-user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
                "(location):s,"
  /* specs/github/github-user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
                "(email):s,"
  /* specs/github/github-user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
                "(hireable):s,"
  /* specs/github/github-user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
                "(bio):s,"
  /* specs/github/github-user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
                "(public_repos):d,"
  /* specs/github/github-user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
                "(public_gists):d,"
  /* specs/github/github-user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
                "(followers):d,"
  /* specs/github/github-user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
                "(following):d,"
  /* specs/github/github-user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                "(created_at):s,"
  /* specs/github/github-user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                "(updated_at):s,"
                "@arg_switches:b",
  /* specs/github/github-user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
                p->login,
  /* specs/github/github-user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
                &p->id,
  /* specs/github/github-user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                p->node_id,
  /* specs/github/github-user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
                p->avatar_url,
  /* specs/github/github-user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
                p->gravatar_id,
  /* specs/github/github-user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                p->html_url,
  /* specs/github/github-user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                p->type,
  /* specs/github/github-user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
                &p->site_admin,
  /* specs/github/github-user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                p->name,
  /* specs/github/github-user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
                p->company,
  /* specs/github/github-user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
                p->blog,
  /* specs/github/github-user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
                p->location,
  /* specs/github/github-user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
                p->email,
  /* specs/github/github-user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
                p->hireable,
  /* specs/github/github-user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
                p->bio,
  /* specs/github/github-user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
                &p->public_repos,
  /* specs/github/github-user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
                &p->public_gists,
  /* specs/github/github-user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
                &p->followers,
  /* specs/github/github-user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
                &p->following,
  /* specs/github/github-user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                p->created_at,
  /* specs/github/github-user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                p->updated_at,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void github_user_cleanup_v(void *p) {
  github_user_cleanup((struct github_user *)p);
}

void github_user_init_v(void *p) {
  github_user_init((struct github_user *)p);
}

void github_user_from_json_v(char *json, size_t len, void *pp) {
 github_user_from_json(json, len, (struct github_user**)pp);
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
  /* specs/github/github-user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
  if (d->login)
    free(d->login);
  /* specs/github/github-user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
  // p->id is a scalar
  /* specs/github/github-user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  if (d->node_id)
    free(d->node_id);
  /* specs/github/github-user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
  if (d->avatar_url)
    free(d->avatar_url);
  /* specs/github/github-user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
  if (d->gravatar_id)
    free(d->gravatar_id);
  /* specs/github/github-user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
  if (d->html_url)
    free(d->html_url);
  /* specs/github/github-user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  if (d->type)
    free(d->type);
  /* specs/github/github-user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
  // p->site_admin is a scalar
  /* specs/github/github-user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* specs/github/github-user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
  if (d->company)
    free(d->company);
  /* specs/github/github-user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
  if (d->blog)
    free(d->blog);
  /* specs/github/github-user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
  if (d->location)
    free(d->location);
  /* specs/github/github-user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
  if (d->email)
    free(d->email);
  /* specs/github/github-user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
  if (d->hireable)
    free(d->hireable);
  /* specs/github/github-user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
  if (d->bio)
    free(d->bio);
  /* specs/github/github-user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
  // p->public_repos is a scalar
  /* specs/github/github-user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
  // p->public_gists is a scalar
  /* specs/github/github-user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
  // p->followers is a scalar
  /* specs/github/github-user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
  // p->following is a scalar
  /* specs/github/github-user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
  if (d->created_at)
    free(d->created_at);
  /* specs/github/github-user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
  if (d->updated_at)
    free(d->updated_at);
}

void github_user_init(struct github_user *p) {
  memset(p, 0, sizeof(struct github_user));
  /* specs/github/github-user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */

  /* specs/github/github-user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */

  /* specs/github/github-user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */

  /* specs/github/github-user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */

  /* specs/github/github-user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */

  /* specs/github/github-user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */

  /* specs/github/github-user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */

}
void github_user_list_free(struct github_user **p) {
  ntl_free((void**)p, (vfvp)github_user_cleanup);
}

void github_user_list_from_json(char *str, size_t len, struct github_user ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct github_user);
  d.init_elem = NULL;
  d.elem_from_buf = github_user_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t github_user_list_to_json(char *str, size_t len, struct github_user **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, github_user_to_json_v);
}

