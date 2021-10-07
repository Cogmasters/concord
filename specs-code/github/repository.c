/* This file is generated from specs/github/repository.json, Please don't edit it. */
/**
 * @file specs-code/github/repository.c
 * @see https://docs.github.com/en/rest/reference/repos#get-all-repository-topics
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "github.h"

void github_topic_from_json(char *json, size_t len, struct github_topic **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct github_topic *p = *pp;
  github_topic_init(p);
  r=json_extract(json, len, 
  /* specs/github/repository.json:12:28
     '{ "name": "names", "type":{ "base":"ja_str", "dec":"ntl"}}' */
                "(names):F,",
  /* specs/github/repository.json:12:28
     '{ "name": "names", "type":{ "base":"ja_str", "dec":"ntl"}}' */
                ja_str_list_from_json, &p->names);
  ret = r;
}

size_t github_topic_to_json(char *json, size_t len, struct github_topic *p)
{
  size_t r;
  void *arg_switches[1]={NULL};
  /* specs/github/repository.json:12:28
     '{ "name": "names", "type":{ "base":"ja_str", "dec":"ntl"}}' */
  arg_switches[0] = p->names;

  r=json_inject(json, len, 
  /* specs/github/repository.json:12:28
     '{ "name": "names", "type":{ "base":"ja_str", "dec":"ntl"}}' */
                "(names):F,"
                "@arg_switches:b",
  /* specs/github/repository.json:12:28
     '{ "name": "names", "type":{ "base":"ja_str", "dec":"ntl"}}' */
                ja_str_list_to_json, p->names,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void github_topic_cleanup_v(void *p) {
  github_topic_cleanup((struct github_topic *)p);
}

void github_topic_init_v(void *p) {
  github_topic_init((struct github_topic *)p);
}

void github_topic_from_json_v(char *json, size_t len, void *pp) {
 github_topic_from_json(json, len, (struct github_topic**)pp);
}

size_t github_topic_to_json_v(char *json, size_t len, void *p) {
  return github_topic_to_json(json, len, (struct github_topic*)p);
}

void github_topic_list_free_v(void **p) {
  github_topic_list_free((struct github_topic**)p);
}

void github_topic_list_from_json_v(char *str, size_t len, void *p) {
  github_topic_list_from_json(str, len, (struct github_topic ***)p);
}

size_t github_topic_list_to_json_v(char *str, size_t len, void *p){
  return github_topic_list_to_json(str, len, (struct github_topic **)p);
}


void github_topic_cleanup(struct github_topic *d) {
  /* specs/github/repository.json:12:28
     '{ "name": "names", "type":{ "base":"ja_str", "dec":"ntl"}}' */
  if (d->names)
    ja_str_list_free(d->names);
}

void github_topic_init(struct github_topic *p) {
  memset(p, 0, sizeof(struct github_topic));
  /* specs/github/repository.json:12:28
     '{ "name": "names", "type":{ "base":"ja_str", "dec":"ntl"}}' */

}
void github_topic_list_free(struct github_topic **p) {
  ntl_free((void**)p, (vfvp)github_topic_cleanup);
}

void github_topic_list_from_json(char *str, size_t len, struct github_topic ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct github_topic);
  d.init_elem = NULL;
  d.elem_from_buf = github_topic_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t github_topic_list_to_json(char *str, size_t len, struct github_topic **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, github_topic_to_json_v);
}

