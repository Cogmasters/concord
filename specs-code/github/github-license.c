/* This file is generated from specs/github/github-license.json, Please don't edit it. */
/**
 * @file specs-code/github/github-license.c
 * @see https://docs.github.com/en/rest/reference/repos#get-a-repository
 */

#include "specs-deps.h"
#include "github.h"

void github_license_from_json(char *json, size_t len, struct github_license **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct github_license *p = *pp;
  r=json_extract(json, len, 
  /* specs/github/github-license.json:12:28
     '{ "name": "key", "type":{ "base":"char", "dec":"*"}}' */
                "(key):?s,"
  /* specs/github/github-license.json:13:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* specs/github/github-license.json:14:28
     '{ "name": "spdx_id", "type":{ "base":"char", "dec":"*"}}' */
                "(spdx_id):?s,"
  /* specs/github/github-license.json:15:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                "(node_id):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/github/github-license.json:12:28
     '{ "name": "key", "type":{ "base":"char", "dec":"*"}}' */
                &p->key,
  /* specs/github/github-license.json:13:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                &p->name,
  /* specs/github/github-license.json:14:28
     '{ "name": "spdx_id", "type":{ "base":"char", "dec":"*"}}' */
                &p->spdx_id,
  /* specs/github/github-license.json:15:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                &p->node_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void github_license_use_default_inject_settings(struct github_license *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/github/github-license.json:12:28
     '{ "name": "key", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[0] = p->key;

  /* specs/github/github-license.json:13:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[1] = p->name;

  /* specs/github/github-license.json:14:28
     '{ "name": "spdx_id", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[2] = p->spdx_id;

  /* specs/github/github-license.json:15:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[3] = p->node_id;

}

size_t github_license_to_json(char *json, size_t len, struct github_license *p)
{
  size_t r;
  github_license_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/github/github-license.json:12:28
     '{ "name": "key", "type":{ "base":"char", "dec":"*"}}' */
                "(key):s,"
  /* specs/github/github-license.json:13:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):s,"
  /* specs/github/github-license.json:14:28
     '{ "name": "spdx_id", "type":{ "base":"char", "dec":"*"}}' */
                "(spdx_id):s,"
  /* specs/github/github-license.json:15:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                "(node_id):s,"
                "@arg_switches:b",
  /* specs/github/github-license.json:12:28
     '{ "name": "key", "type":{ "base":"char", "dec":"*"}}' */
                p->key,
  /* specs/github/github-license.json:13:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                p->name,
  /* specs/github/github-license.json:14:28
     '{ "name": "spdx_id", "type":{ "base":"char", "dec":"*"}}' */
                p->spdx_id,
  /* specs/github/github-license.json:15:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
                p->node_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void github_license_cleanup_v(void *p) {
  github_license_cleanup((struct github_license *)p);
}

void github_license_init_v(void *p) {
  github_license_init((struct github_license *)p);
}

void github_license_from_json_v(char *json, size_t len, void *pp) {
 github_license_from_json(json, len, (struct github_license**)pp);
}

size_t github_license_to_json_v(char *json, size_t len, void *p) {
  return github_license_to_json(json, len, (struct github_license*)p);
}

void github_license_list_free_v(void **p) {
  github_license_list_free((struct github_license**)p);
}

void github_license_list_from_json_v(char *str, size_t len, void *p) {
  github_license_list_from_json(str, len, (struct github_license ***)p);
}

size_t github_license_list_to_json_v(char *str, size_t len, void *p){
  return github_license_list_to_json(str, len, (struct github_license **)p);
}


void github_license_cleanup(struct github_license *d) {
  /* specs/github/github-license.json:12:28
     '{ "name": "key", "type":{ "base":"char", "dec":"*"}}' */
  if (d->key)
    free(d->key);
  /* specs/github/github-license.json:13:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* specs/github/github-license.json:14:28
     '{ "name": "spdx_id", "type":{ "base":"char", "dec":"*"}}' */
  if (d->spdx_id)
    free(d->spdx_id);
  /* specs/github/github-license.json:15:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  if (d->node_id)
    free(d->node_id);
}

void github_license_init(struct github_license *p) {
  memset(p, 0, sizeof(struct github_license));
  /* specs/github/github-license.json:12:28
     '{ "name": "key", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-license.json:13:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-license.json:14:28
     '{ "name": "spdx_id", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/github/github-license.json:15:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */

}
void github_license_list_free(struct github_license **p) {
  ntl_free((void**)p, (vfvp)github_license_cleanup);
}

void github_license_list_from_json(char *str, size_t len, struct github_license ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct github_license);
  d.init_elem = NULL;
  d.elem_from_buf = github_license_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t github_license_list_to_json(char *str, size_t len, struct github_license **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, github_license_to_json_v);
}

