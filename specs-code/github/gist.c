/* This file is generated from specs/github/gist.json, Please don't edit it. */
/**
 * @file specs-code/github/gist.c
 * @see https://docs.github.com/en/rest/reference/gists#create-a-gist
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "github.h"

void github_gist_from_json(char *json, size_t len, struct github_gist **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct github_gist *p = *pp;
  github_gist_init(p);
  r=json_extract(json, len, 
  /* specs/github/gist.json:12:28
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}}' */
                "(url):?s,"
  /* specs/github/gist.json:13:28
     '{ "name": "id", "type":{ "base":"char", "dec":"*"}}' */
                "(id):?s,"
  /* specs/github/gist.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                "(node_id):?s,"
  /* specs/github/gist.json:15:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                "(html_url):?s,"
  /* specs/github/gist.json:16:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                "(created_at):?s,"
  /* specs/github/gist.json:17:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                "(updated_at):?s,"
  /* specs/github/gist.json:18:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
                "(description):?s,"
  /* specs/github/gist.json:19:28
     '{ "name": "comments", "type":{ "base":"int"}}' */
                "(comments):d,",
  /* specs/github/gist.json:12:28
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}}' */
                &p->url,
  /* specs/github/gist.json:13:28
     '{ "name": "id", "type":{ "base":"char", "dec":"*"}}' */
                &p->id,
  /* specs/github/gist.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                &p->node_id,
  /* specs/github/gist.json:15:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                &p->html_url,
  /* specs/github/gist.json:16:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                &p->created_at,
  /* specs/github/gist.json:17:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                &p->updated_at,
  /* specs/github/gist.json:18:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
                &p->description,
  /* specs/github/gist.json:19:28
     '{ "name": "comments", "type":{ "base":"int"}}' */
                &p->comments);
  ret = r;
}

size_t github_gist_to_json(char *json, size_t len, struct github_gist *p)
{
  size_t r;
  void *arg_switches[8]={NULL};
  /* specs/github/gist.json:12:28
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[0] = p->url;

  /* specs/github/gist.json:13:28
     '{ "name": "id", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[1] = p->id;

  /* specs/github/gist.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[2] = p->node_id;

  /* specs/github/gist.json:15:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[3] = p->html_url;

  /* specs/github/gist.json:16:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[4] = p->created_at;

  /* specs/github/gist.json:17:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[5] = p->updated_at;

  /* specs/github/gist.json:18:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[6] = p->description;

  /* specs/github/gist.json:19:28
     '{ "name": "comments", "type":{ "base":"int"}}' */
  arg_switches[7] = &p->comments;

  r=json_inject(json, len, 
  /* specs/github/gist.json:12:28
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}}' */
                "(url):s,"
  /* specs/github/gist.json:13:28
     '{ "name": "id", "type":{ "base":"char", "dec":"*"}}' */
                "(id):s,"
  /* specs/github/gist.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                "(node_id):s,"
  /* specs/github/gist.json:15:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                "(html_url):s,"
  /* specs/github/gist.json:16:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                "(created_at):s,"
  /* specs/github/gist.json:17:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                "(updated_at):s,"
  /* specs/github/gist.json:18:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
                "(description):s,"
  /* specs/github/gist.json:19:28
     '{ "name": "comments", "type":{ "base":"int"}}' */
                "(comments):d,"
                "@arg_switches:b",
  /* specs/github/gist.json:12:28
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}}' */
                p->url,
  /* specs/github/gist.json:13:28
     '{ "name": "id", "type":{ "base":"char", "dec":"*"}}' */
                p->id,
  /* specs/github/gist.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                p->node_id,
  /* specs/github/gist.json:15:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
                p->html_url,
  /* specs/github/gist.json:16:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
                p->created_at,
  /* specs/github/gist.json:17:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
                p->updated_at,
  /* specs/github/gist.json:18:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
                p->description,
  /* specs/github/gist.json:19:28
     '{ "name": "comments", "type":{ "base":"int"}}' */
                &p->comments,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void github_gist_cleanup_v(void *p) {
  github_gist_cleanup((struct github_gist *)p);
}

void github_gist_init_v(void *p) {
  github_gist_init((struct github_gist *)p);
}

void github_gist_from_json_v(char *json, size_t len, void *pp) {
 github_gist_from_json(json, len, (struct github_gist**)pp);
}

size_t github_gist_to_json_v(char *json, size_t len, void *p) {
  return github_gist_to_json(json, len, (struct github_gist*)p);
}

void github_gist_list_free_v(void **p) {
  github_gist_list_free((struct github_gist**)p);
}

void github_gist_list_from_json_v(char *str, size_t len, void *p) {
  github_gist_list_from_json(str, len, (struct github_gist ***)p);
}

size_t github_gist_list_to_json_v(char *str, size_t len, void *p){
  return github_gist_list_to_json(str, len, (struct github_gist **)p);
}


void github_gist_cleanup(struct github_gist *d) {
  /* specs/github/gist.json:12:28
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}}' */
  if (d->url)
    free(d->url);
  /* specs/github/gist.json:13:28
     '{ "name": "id", "type":{ "base":"char", "dec":"*"}}' */
  if (d->id)
    free(d->id);
  /* specs/github/gist.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  if (d->node_id)
    free(d->node_id);
  /* specs/github/gist.json:15:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
  if (d->html_url)
    free(d->html_url);
  /* specs/github/gist.json:16:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
  if (d->created_at)
    free(d->created_at);
  /* specs/github/gist.json:17:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
  if (d->updated_at)
    free(d->updated_at);
  /* specs/github/gist.json:18:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
  if (d->description)
    free(d->description);
  /* specs/github/gist.json:19:28
     '{ "name": "comments", "type":{ "base":"int"}}' */
  /* p->comments is a scalar */
}

void github_gist_init(struct github_gist *p) {
  memset(p, 0, sizeof(struct github_gist));
  /* specs/github/gist.json:12:28
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/gist.json:13:28
     '{ "name": "id", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/gist.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/gist.json:15:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/gist.json:16:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/gist.json:17:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/gist.json:18:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/gist.json:19:28
     '{ "name": "comments", "type":{ "base":"int"}}' */

}
void github_gist_list_free(struct github_gist **p) {
  ntl_free((void**)p, (vfvp)github_gist_cleanup);
}

void github_gist_list_from_json(char *str, size_t len, struct github_gist ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct github_gist);
  d.init_elem = NULL;
  d.elem_from_buf = github_gist_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t github_gist_list_to_json(char *str, size_t len, struct github_gist **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, github_gist_to_json_v);
}

