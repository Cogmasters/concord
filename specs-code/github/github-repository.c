/* This file is generated from specs/github/github-repository.json, Please don't edit it. */
/**
 * @file specs-code/github/github-repository.c
 * @see https://docs.github.com/en/rest/reference/repos#get-a-repository
 */

#include "specs-deps.h"
#include "github.h"

void github_repository_from_json(char *json, size_t len, struct github_repository **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct github_repository *p = *pp;
  r=json_extract(json, len, 
  /* specs/github/github-repository.json:12:28
     '{ "name": "id", "type":{ "base":"int"}}' */
                "(id):d,"
  /* specs/github/github-repository.json:13:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                "(node_id):?s,"
  /* specs/github/github-repository.json:14:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* specs/github/github-repository.json:15:28
     '{ "name": "full_name", "type":{ "base":"char", "dec":"*"}}' */
                "(full_name):?s,"
  /* specs/github/github-repository.json:16:28
     '{ "name": "private", "type":{ "base":"bool"}}' */
                "(private):b,"
  /* specs/github/github-repository.json:17:77
     '{ "type": {"base":"struct github_user", "dec":"*"}, "name":"owner"}' */
                "(owner):F,"
  /* specs/github/github-repository.json:18:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                "(html_url):?s,"
  /* specs/github/github-repository.json:19:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
                "(description):?s,"
  /* specs/github/github-repository.json:20:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                "(created_at):?s,"
  /* specs/github/github-repository.json:21:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                "(updated_at):?s,"
  /* specs/github/github-repository.json:22:28
     '{ "name": "pushed_at", "type":{ "base":"char", "dec":"*"}}' */
                "(pushed_at):?s,"
  /* specs/github/github-repository.json:23:28
     '{ "name": "homepage", "type":{ "base":"char", "dec":"*"}}' */
                "(homepage):?s,"
  /* specs/github/github-repository.json:24:28
     '{ "name": "size", "type":{ "base": "int"}}' */
                "(size):d,"
  /* specs/github/github-repository.json:25:28
     '{ "name": "stargazers_count", "type":{ "base": "int"}}' */
                "(stargazers_count):d,"
  /* specs/github/github-repository.json:26:28
     '{ "name": "watchers_count", "type":{ "base": "int"}}' */
                "(watchers_count):d,"
  /* specs/github/github-repository.json:27:28
     '{ "name": "language", "type":{ "base":"char", "dec":"*"}}' */
                "(language):?s,"
  /* specs/github/github-repository.json:28:28
     '{ "name": "has_issues", "type":{ "base":"bool"}}' */
                "(has_issues):b,"
  /* specs/github/github-repository.json:29:28
     '{ "name": "has_projects", "type":{ "base":"bool"}}' */
                "(has_projects):b,"
  /* specs/github/github-repository.json:30:28
     '{ "name": "has_downloads", "type":{ "base":"bool"}}' */
                "(has_downloads):b,"
  /* specs/github/github-repository.json:31:28
     '{ "name": "has_wiki", "type":{ "base":"bool"}}' */
                "(has_wiki):b,"
  /* specs/github/github-repository.json:32:28
     '{ "name": "has_pages", "type":{ "base":"bool"}}' */
                "(has_pages):b,"
  /* specs/github/github-repository.json:33:28
     '{ "name": "forks_count", "type":{ "base": "int"}}' */
                "(forks_count):d,"
  /* specs/github/github-repository.json:34:28
     '{ "name": "archived", "type":{ "base":"bool"}}' */
                "(archived):b,"
  /* specs/github/github-repository.json:35:28
     '{ "name": "disabled", "type":{ "base":"bool"}}' */
                "(disabled):b,"
  /* specs/github/github-repository.json:36:28
     '{ "name": "open_issues_count", "type":{ "base": "int"}}' */
                "(open_issues_count):d,"
  /* specs/github/github-repository.json:37:80
     '{ "type": {"base":"struct github_license", "dec":"*"}, "name":"license"}' */
                "(license):F,"
  /* specs/github/github-repository.json:38:28
     '{ "name": "forks", "type":{ "base": "int"}}' */
                "(forks):d,"
  /* specs/github/github-repository.json:39:28
     '{ "name": "open_issues", "type":{ "base": "int"}}' */
                "(open_issues):d,"
  /* specs/github/github-repository.json:40:28
     '{ "name": "watchers", "type":{ "base": "int"}}' */
                "(watchers):d,"
  /* specs/github/github-repository.json:41:28
     '{ "name": "default_branch", "type":{ "base":"char", "dec":"*"}}' */
                "(default_branch):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/github/github-repository.json:12:28
     '{ "name": "id", "type":{ "base":"int"}}' */
                &p->id,
  /* specs/github/github-repository.json:13:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                &p->node_id,
  /* specs/github/github-repository.json:14:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                &p->name,
  /* specs/github/github-repository.json:15:28
     '{ "name": "full_name", "type":{ "base":"char", "dec":"*"}}' */
                &p->full_name,
  /* specs/github/github-repository.json:16:28
     '{ "name": "private", "type":{ "base":"bool"}}' */
                &p->private,
  /* specs/github/github-repository.json:17:77
     '{ "type": {"base":"struct github_user", "dec":"*"}, "name":"owner"}' */
                github_user_from_json, &p->owner,
  /* specs/github/github-repository.json:18:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                &p->html_url,
  /* specs/github/github-repository.json:19:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
                &p->description,
  /* specs/github/github-repository.json:20:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                &p->created_at,
  /* specs/github/github-repository.json:21:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                &p->updated_at,
  /* specs/github/github-repository.json:22:28
     '{ "name": "pushed_at", "type":{ "base":"char", "dec":"*"}}' */
                &p->pushed_at,
  /* specs/github/github-repository.json:23:28
     '{ "name": "homepage", "type":{ "base":"char", "dec":"*"}}' */
                &p->homepage,
  /* specs/github/github-repository.json:24:28
     '{ "name": "size", "type":{ "base": "int"}}' */
                &p->size,
  /* specs/github/github-repository.json:25:28
     '{ "name": "stargazers_count", "type":{ "base": "int"}}' */
                &p->stargazers_count,
  /* specs/github/github-repository.json:26:28
     '{ "name": "watchers_count", "type":{ "base": "int"}}' */
                &p->watchers_count,
  /* specs/github/github-repository.json:27:28
     '{ "name": "language", "type":{ "base":"char", "dec":"*"}}' */
                &p->language,
  /* specs/github/github-repository.json:28:28
     '{ "name": "has_issues", "type":{ "base":"bool"}}' */
                &p->has_issues,
  /* specs/github/github-repository.json:29:28
     '{ "name": "has_projects", "type":{ "base":"bool"}}' */
                &p->has_projects,
  /* specs/github/github-repository.json:30:28
     '{ "name": "has_downloads", "type":{ "base":"bool"}}' */
                &p->has_downloads,
  /* specs/github/github-repository.json:31:28
     '{ "name": "has_wiki", "type":{ "base":"bool"}}' */
                &p->has_wiki,
  /* specs/github/github-repository.json:32:28
     '{ "name": "has_pages", "type":{ "base":"bool"}}' */
                &p->has_pages,
  /* specs/github/github-repository.json:33:28
     '{ "name": "forks_count", "type":{ "base": "int"}}' */
                &p->forks_count,
  /* specs/github/github-repository.json:34:28
     '{ "name": "archived", "type":{ "base":"bool"}}' */
                &p->archived,
  /* specs/github/github-repository.json:35:28
     '{ "name": "disabled", "type":{ "base":"bool"}}' */
                &p->disabled,
  /* specs/github/github-repository.json:36:28
     '{ "name": "open_issues_count", "type":{ "base": "int"}}' */
                &p->open_issues_count,
  /* specs/github/github-repository.json:37:80
     '{ "type": {"base":"struct github_license", "dec":"*"}, "name":"license"}' */
                github_license_from_json, &p->license,
  /* specs/github/github-repository.json:38:28
     '{ "name": "forks", "type":{ "base": "int"}}' */
                &p->forks,
  /* specs/github/github-repository.json:39:28
     '{ "name": "open_issues", "type":{ "base": "int"}}' */
                &p->open_issues,
  /* specs/github/github-repository.json:40:28
     '{ "name": "watchers", "type":{ "base": "int"}}' */
                &p->watchers,
  /* specs/github/github-repository.json:41:28
     '{ "name": "default_branch", "type":{ "base":"char", "dec":"*"}}' */
                &p->default_branch,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void github_repository_use_default_inject_settings(struct github_repository *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/github/github-repository.json:12:28
     '{ "name": "id", "type":{ "base":"int"}}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/github/github-repository.json:13:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[1] = p->node_id;

  /* specs/github/github-repository.json:14:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[2] = p->name;

  /* specs/github/github-repository.json:15:28
     '{ "name": "full_name", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[3] = p->full_name;

  /* specs/github/github-repository.json:16:28
     '{ "name": "private", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[4] = &p->private;

  /* specs/github/github-repository.json:17:77
     '{ "type": {"base":"struct github_user", "dec":"*"}, "name":"owner"}' */
  p->__M.arg_switches[5] = p->owner;

  /* specs/github/github-repository.json:18:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[6] = p->html_url;

  /* specs/github/github-repository.json:19:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[7] = p->description;

  /* specs/github/github-repository.json:20:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[8] = p->created_at;

  /* specs/github/github-repository.json:21:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[9] = p->updated_at;

  /* specs/github/github-repository.json:22:28
     '{ "name": "pushed_at", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[10] = p->pushed_at;

  /* specs/github/github-repository.json:23:28
     '{ "name": "homepage", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[11] = p->homepage;

  /* specs/github/github-repository.json:24:28
     '{ "name": "size", "type":{ "base": "int"}}' */
  p->__M.arg_switches[12] = &p->size;

  /* specs/github/github-repository.json:25:28
     '{ "name": "stargazers_count", "type":{ "base": "int"}}' */
  p->__M.arg_switches[13] = &p->stargazers_count;

  /* specs/github/github-repository.json:26:28
     '{ "name": "watchers_count", "type":{ "base": "int"}}' */
  p->__M.arg_switches[14] = &p->watchers_count;

  /* specs/github/github-repository.json:27:28
     '{ "name": "language", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[15] = p->language;

  /* specs/github/github-repository.json:28:28
     '{ "name": "has_issues", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[16] = &p->has_issues;

  /* specs/github/github-repository.json:29:28
     '{ "name": "has_projects", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[17] = &p->has_projects;

  /* specs/github/github-repository.json:30:28
     '{ "name": "has_downloads", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[18] = &p->has_downloads;

  /* specs/github/github-repository.json:31:28
     '{ "name": "has_wiki", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[19] = &p->has_wiki;

  /* specs/github/github-repository.json:32:28
     '{ "name": "has_pages", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[20] = &p->has_pages;

  /* specs/github/github-repository.json:33:28
     '{ "name": "forks_count", "type":{ "base": "int"}}' */
  p->__M.arg_switches[21] = &p->forks_count;

  /* specs/github/github-repository.json:34:28
     '{ "name": "archived", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[22] = &p->archived;

  /* specs/github/github-repository.json:35:28
     '{ "name": "disabled", "type":{ "base":"bool"}}' */
  p->__M.arg_switches[23] = &p->disabled;

  /* specs/github/github-repository.json:36:28
     '{ "name": "open_issues_count", "type":{ "base": "int"}}' */
  p->__M.arg_switches[24] = &p->open_issues_count;

  /* specs/github/github-repository.json:37:80
     '{ "type": {"base":"struct github_license", "dec":"*"}, "name":"license"}' */
  p->__M.arg_switches[25] = p->license;

  /* specs/github/github-repository.json:38:28
     '{ "name": "forks", "type":{ "base": "int"}}' */
  p->__M.arg_switches[26] = &p->forks;

  /* specs/github/github-repository.json:39:28
     '{ "name": "open_issues", "type":{ "base": "int"}}' */
  p->__M.arg_switches[27] = &p->open_issues;

  /* specs/github/github-repository.json:40:28
     '{ "name": "watchers", "type":{ "base": "int"}}' */
  p->__M.arg_switches[28] = &p->watchers;

  /* specs/github/github-repository.json:41:28
     '{ "name": "default_branch", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[29] = p->default_branch;

}

size_t github_repository_to_json(char *json, size_t len, struct github_repository *p)
{
  size_t r;
  github_repository_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/github/github-repository.json:12:28
     '{ "name": "id", "type":{ "base":"int"}}' */
                "(id):d,"
  /* specs/github/github-repository.json:13:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                "(node_id):s,"
  /* specs/github/github-repository.json:14:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):s,"
  /* specs/github/github-repository.json:15:28
     '{ "name": "full_name", "type":{ "base":"char", "dec":"*"}}' */
                "(full_name):s,"
  /* specs/github/github-repository.json:16:28
     '{ "name": "private", "type":{ "base":"bool"}}' */
                "(private):b,"
  /* specs/github/github-repository.json:17:77
     '{ "type": {"base":"struct github_user", "dec":"*"}, "name":"owner"}' */
                "(owner):F,"
  /* specs/github/github-repository.json:18:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                "(html_url):s,"
  /* specs/github/github-repository.json:19:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
                "(description):s,"
  /* specs/github/github-repository.json:20:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                "(created_at):s,"
  /* specs/github/github-repository.json:21:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                "(updated_at):s,"
  /* specs/github/github-repository.json:22:28
     '{ "name": "pushed_at", "type":{ "base":"char", "dec":"*"}}' */
                "(pushed_at):s,"
  /* specs/github/github-repository.json:23:28
     '{ "name": "homepage", "type":{ "base":"char", "dec":"*"}}' */
                "(homepage):s,"
  /* specs/github/github-repository.json:24:28
     '{ "name": "size", "type":{ "base": "int"}}' */
                "(size):d,"
  /* specs/github/github-repository.json:25:28
     '{ "name": "stargazers_count", "type":{ "base": "int"}}' */
                "(stargazers_count):d,"
  /* specs/github/github-repository.json:26:28
     '{ "name": "watchers_count", "type":{ "base": "int"}}' */
                "(watchers_count):d,"
  /* specs/github/github-repository.json:27:28
     '{ "name": "language", "type":{ "base":"char", "dec":"*"}}' */
                "(language):s,"
  /* specs/github/github-repository.json:28:28
     '{ "name": "has_issues", "type":{ "base":"bool"}}' */
                "(has_issues):b,"
  /* specs/github/github-repository.json:29:28
     '{ "name": "has_projects", "type":{ "base":"bool"}}' */
                "(has_projects):b,"
  /* specs/github/github-repository.json:30:28
     '{ "name": "has_downloads", "type":{ "base":"bool"}}' */
                "(has_downloads):b,"
  /* specs/github/github-repository.json:31:28
     '{ "name": "has_wiki", "type":{ "base":"bool"}}' */
                "(has_wiki):b,"
  /* specs/github/github-repository.json:32:28
     '{ "name": "has_pages", "type":{ "base":"bool"}}' */
                "(has_pages):b,"
  /* specs/github/github-repository.json:33:28
     '{ "name": "forks_count", "type":{ "base": "int"}}' */
                "(forks_count):d,"
  /* specs/github/github-repository.json:34:28
     '{ "name": "archived", "type":{ "base":"bool"}}' */
                "(archived):b,"
  /* specs/github/github-repository.json:35:28
     '{ "name": "disabled", "type":{ "base":"bool"}}' */
                "(disabled):b,"
  /* specs/github/github-repository.json:36:28
     '{ "name": "open_issues_count", "type":{ "base": "int"}}' */
                "(open_issues_count):d,"
  /* specs/github/github-repository.json:37:80
     '{ "type": {"base":"struct github_license", "dec":"*"}, "name":"license"}' */
                "(license):F,"
  /* specs/github/github-repository.json:38:28
     '{ "name": "forks", "type":{ "base": "int"}}' */
                "(forks):d,"
  /* specs/github/github-repository.json:39:28
     '{ "name": "open_issues", "type":{ "base": "int"}}' */
                "(open_issues):d,"
  /* specs/github/github-repository.json:40:28
     '{ "name": "watchers", "type":{ "base": "int"}}' */
                "(watchers):d,"
  /* specs/github/github-repository.json:41:28
     '{ "name": "default_branch", "type":{ "base":"char", "dec":"*"}}' */
                "(default_branch):s,"
                "@arg_switches:b",
  /* specs/github/github-repository.json:12:28
     '{ "name": "id", "type":{ "base":"int"}}' */
                &p->id,
  /* specs/github/github-repository.json:13:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                p->node_id,
  /* specs/github/github-repository.json:14:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                p->name,
  /* specs/github/github-repository.json:15:28
     '{ "name": "full_name", "type":{ "base":"char", "dec":"*"}}' */
                p->full_name,
  /* specs/github/github-repository.json:16:28
     '{ "name": "private", "type":{ "base":"bool"}}' */
                &p->private,
  /* specs/github/github-repository.json:17:77
     '{ "type": {"base":"struct github_user", "dec":"*"}, "name":"owner"}' */
                github_user_to_json, p->owner,
  /* specs/github/github-repository.json:18:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                p->html_url,
  /* specs/github/github-repository.json:19:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
                p->description,
  /* specs/github/github-repository.json:20:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                p->created_at,
  /* specs/github/github-repository.json:21:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                p->updated_at,
  /* specs/github/github-repository.json:22:28
     '{ "name": "pushed_at", "type":{ "base":"char", "dec":"*"}}' */
                p->pushed_at,
  /* specs/github/github-repository.json:23:28
     '{ "name": "homepage", "type":{ "base":"char", "dec":"*"}}' */
                p->homepage,
  /* specs/github/github-repository.json:24:28
     '{ "name": "size", "type":{ "base": "int"}}' */
                &p->size,
  /* specs/github/github-repository.json:25:28
     '{ "name": "stargazers_count", "type":{ "base": "int"}}' */
                &p->stargazers_count,
  /* specs/github/github-repository.json:26:28
     '{ "name": "watchers_count", "type":{ "base": "int"}}' */
                &p->watchers_count,
  /* specs/github/github-repository.json:27:28
     '{ "name": "language", "type":{ "base":"char", "dec":"*"}}' */
                p->language,
  /* specs/github/github-repository.json:28:28
     '{ "name": "has_issues", "type":{ "base":"bool"}}' */
                &p->has_issues,
  /* specs/github/github-repository.json:29:28
     '{ "name": "has_projects", "type":{ "base":"bool"}}' */
                &p->has_projects,
  /* specs/github/github-repository.json:30:28
     '{ "name": "has_downloads", "type":{ "base":"bool"}}' */
                &p->has_downloads,
  /* specs/github/github-repository.json:31:28
     '{ "name": "has_wiki", "type":{ "base":"bool"}}' */
                &p->has_wiki,
  /* specs/github/github-repository.json:32:28
     '{ "name": "has_pages", "type":{ "base":"bool"}}' */
                &p->has_pages,
  /* specs/github/github-repository.json:33:28
     '{ "name": "forks_count", "type":{ "base": "int"}}' */
                &p->forks_count,
  /* specs/github/github-repository.json:34:28
     '{ "name": "archived", "type":{ "base":"bool"}}' */
                &p->archived,
  /* specs/github/github-repository.json:35:28
     '{ "name": "disabled", "type":{ "base":"bool"}}' */
                &p->disabled,
  /* specs/github/github-repository.json:36:28
     '{ "name": "open_issues_count", "type":{ "base": "int"}}' */
                &p->open_issues_count,
  /* specs/github/github-repository.json:37:80
     '{ "type": {"base":"struct github_license", "dec":"*"}, "name":"license"}' */
                github_license_to_json, p->license,
  /* specs/github/github-repository.json:38:28
     '{ "name": "forks", "type":{ "base": "int"}}' */
                &p->forks,
  /* specs/github/github-repository.json:39:28
     '{ "name": "open_issues", "type":{ "base": "int"}}' */
                &p->open_issues,
  /* specs/github/github-repository.json:40:28
     '{ "name": "watchers", "type":{ "base": "int"}}' */
                &p->watchers,
  /* specs/github/github-repository.json:41:28
     '{ "name": "default_branch", "type":{ "base":"char", "dec":"*"}}' */
                p->default_branch,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void github_repository_cleanup_v(void *p) {
  github_repository_cleanup((struct github_repository *)p);
}

void github_repository_init_v(void *p) {
  github_repository_init((struct github_repository *)p);
}

void github_repository_from_json_v(char *json, size_t len, void *pp) {
 github_repository_from_json(json, len, (struct github_repository**)pp);
}

size_t github_repository_to_json_v(char *json, size_t len, void *p) {
  return github_repository_to_json(json, len, (struct github_repository*)p);
}

void github_repository_list_free_v(void **p) {
  github_repository_list_free((struct github_repository**)p);
}

void github_repository_list_from_json_v(char *str, size_t len, void *p) {
  github_repository_list_from_json(str, len, (struct github_repository ***)p);
}

size_t github_repository_list_to_json_v(char *str, size_t len, void *p){
  return github_repository_list_to_json(str, len, (struct github_repository **)p);
}


void github_repository_cleanup(struct github_repository *d) {
  /* specs/github/github-repository.json:12:28
     '{ "name": "id", "type":{ "base":"int"}}' */
  // p->id is a scalar
  /* specs/github/github-repository.json:13:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  if (d->node_id)
    free(d->node_id);
  /* specs/github/github-repository.json:14:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* specs/github/github-repository.json:15:28
     '{ "name": "full_name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->full_name)
    free(d->full_name);
  /* specs/github/github-repository.json:16:28
     '{ "name": "private", "type":{ "base":"bool"}}' */
  // p->private is a scalar
  /* specs/github/github-repository.json:17:77
     '{ "type": {"base":"struct github_user", "dec":"*"}, "name":"owner"}' */
  if (d->owner) {
    github_user_cleanup(d->owner);
    free(d->owner);
  }
  /* specs/github/github-repository.json:18:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
  if (d->html_url)
    free(d->html_url);
  /* specs/github/github-repository.json:19:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
  if (d->description)
    free(d->description);
  /* specs/github/github-repository.json:20:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
  if (d->created_at)
    free(d->created_at);
  /* specs/github/github-repository.json:21:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
  if (d->updated_at)
    free(d->updated_at);
  /* specs/github/github-repository.json:22:28
     '{ "name": "pushed_at", "type":{ "base":"char", "dec":"*"}}' */
  if (d->pushed_at)
    free(d->pushed_at);
  /* specs/github/github-repository.json:23:28
     '{ "name": "homepage", "type":{ "base":"char", "dec":"*"}}' */
  if (d->homepage)
    free(d->homepage);
  /* specs/github/github-repository.json:24:28
     '{ "name": "size", "type":{ "base": "int"}}' */
  // p->size is a scalar
  /* specs/github/github-repository.json:25:28
     '{ "name": "stargazers_count", "type":{ "base": "int"}}' */
  // p->stargazers_count is a scalar
  /* specs/github/github-repository.json:26:28
     '{ "name": "watchers_count", "type":{ "base": "int"}}' */
  // p->watchers_count is a scalar
  /* specs/github/github-repository.json:27:28
     '{ "name": "language", "type":{ "base":"char", "dec":"*"}}' */
  if (d->language)
    free(d->language);
  /* specs/github/github-repository.json:28:28
     '{ "name": "has_issues", "type":{ "base":"bool"}}' */
  // p->has_issues is a scalar
  /* specs/github/github-repository.json:29:28
     '{ "name": "has_projects", "type":{ "base":"bool"}}' */
  // p->has_projects is a scalar
  /* specs/github/github-repository.json:30:28
     '{ "name": "has_downloads", "type":{ "base":"bool"}}' */
  // p->has_downloads is a scalar
  /* specs/github/github-repository.json:31:28
     '{ "name": "has_wiki", "type":{ "base":"bool"}}' */
  // p->has_wiki is a scalar
  /* specs/github/github-repository.json:32:28
     '{ "name": "has_pages", "type":{ "base":"bool"}}' */
  // p->has_pages is a scalar
  /* specs/github/github-repository.json:33:28
     '{ "name": "forks_count", "type":{ "base": "int"}}' */
  // p->forks_count is a scalar
  /* specs/github/github-repository.json:34:28
     '{ "name": "archived", "type":{ "base":"bool"}}' */
  // p->archived is a scalar
  /* specs/github/github-repository.json:35:28
     '{ "name": "disabled", "type":{ "base":"bool"}}' */
  // p->disabled is a scalar
  /* specs/github/github-repository.json:36:28
     '{ "name": "open_issues_count", "type":{ "base": "int"}}' */
  // p->open_issues_count is a scalar
  /* specs/github/github-repository.json:37:80
     '{ "type": {"base":"struct github_license", "dec":"*"}, "name":"license"}' */
  if (d->license) {
    github_license_cleanup(d->license);
    free(d->license);
  }
  /* specs/github/github-repository.json:38:28
     '{ "name": "forks", "type":{ "base": "int"}}' */
  // p->forks is a scalar
  /* specs/github/github-repository.json:39:28
     '{ "name": "open_issues", "type":{ "base": "int"}}' */
  // p->open_issues is a scalar
  /* specs/github/github-repository.json:40:28
     '{ "name": "watchers", "type":{ "base": "int"}}' */
  // p->watchers is a scalar
  /* specs/github/github-repository.json:41:28
     '{ "name": "default_branch", "type":{ "base":"char", "dec":"*"}}' */
  if (d->default_branch)
    free(d->default_branch);
}

void github_repository_init(struct github_repository *p) {
  memset(p, 0, sizeof(struct github_repository));
  /* specs/github/github-repository.json:12:28
     '{ "name": "id", "type":{ "base":"int"}}' */

  /* specs/github/github-repository.json:13:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-repository.json:14:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-repository.json:15:28
     '{ "name": "full_name", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-repository.json:16:28
     '{ "name": "private", "type":{ "base":"bool"}}' */

  /* specs/github/github-repository.json:17:77
     '{ "type": {"base":"struct github_user", "dec":"*"}, "name":"owner"}' */
  p->owner = malloc(sizeof *p->owner);
  github_user_init(p->owner);

  /* specs/github/github-repository.json:18:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-repository.json:19:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-repository.json:20:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-repository.json:21:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-repository.json:22:28
     '{ "name": "pushed_at", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-repository.json:23:28
     '{ "name": "homepage", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-repository.json:24:28
     '{ "name": "size", "type":{ "base": "int"}}' */

  /* specs/github/github-repository.json:25:28
     '{ "name": "stargazers_count", "type":{ "base": "int"}}' */

  /* specs/github/github-repository.json:26:28
     '{ "name": "watchers_count", "type":{ "base": "int"}}' */

  /* specs/github/github-repository.json:27:28
     '{ "name": "language", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-repository.json:28:28
     '{ "name": "has_issues", "type":{ "base":"bool"}}' */

  /* specs/github/github-repository.json:29:28
     '{ "name": "has_projects", "type":{ "base":"bool"}}' */

  /* specs/github/github-repository.json:30:28
     '{ "name": "has_downloads", "type":{ "base":"bool"}}' */

  /* specs/github/github-repository.json:31:28
     '{ "name": "has_wiki", "type":{ "base":"bool"}}' */

  /* specs/github/github-repository.json:32:28
     '{ "name": "has_pages", "type":{ "base":"bool"}}' */

  /* specs/github/github-repository.json:33:28
     '{ "name": "forks_count", "type":{ "base": "int"}}' */

  /* specs/github/github-repository.json:34:28
     '{ "name": "archived", "type":{ "base":"bool"}}' */

  /* specs/github/github-repository.json:35:28
     '{ "name": "disabled", "type":{ "base":"bool"}}' */

  /* specs/github/github-repository.json:36:28
     '{ "name": "open_issues_count", "type":{ "base": "int"}}' */

  /* specs/github/github-repository.json:37:80
     '{ "type": {"base":"struct github_license", "dec":"*"}, "name":"license"}' */
  p->license = malloc(sizeof *p->license);
  github_license_init(p->license);

  /* specs/github/github-repository.json:38:28
     '{ "name": "forks", "type":{ "base": "int"}}' */

  /* specs/github/github-repository.json:39:28
     '{ "name": "open_issues", "type":{ "base": "int"}}' */

  /* specs/github/github-repository.json:40:28
     '{ "name": "watchers", "type":{ "base": "int"}}' */

  /* specs/github/github-repository.json:41:28
     '{ "name": "default_branch", "type":{ "base":"char", "dec":"*"}}' */

}
void github_repository_list_free(struct github_repository **p) {
  ntl_free((void**)p, (vfvp)github_repository_cleanup);
}

void github_repository_list_from_json(char *str, size_t len, struct github_repository ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct github_repository);
  d.init_elem = NULL;
  d.elem_from_buf = github_repository_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t github_repository_list_to_json(char *str, size_t len, struct github_repository **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, github_repository_to_json_v);
}

