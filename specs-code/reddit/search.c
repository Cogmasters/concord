/* This file is generated from specs/reddit/search.json, Please don't edit it. */
/**
 * @file specs-code/reddit/search.c
 * @see 
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "reddit.h"

void reddit_search_params_from_json(char *json, size_t len, struct reddit_search_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct reddit_search_params *p = *pp;
  reddit_search_params_init(p);
  r=json_extract(json, len, 
  /* specs/reddit/search.json:13:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
                "(after):?s,"
  /* specs/reddit/search.json:14:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
                "(before):?s,"
  /* specs/reddit/search.json:15:20
     '{ "name": "category", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 5 character"}' */
                "(category):?s,"
  /* specs/reddit/search.json:16:20
     '{ "name": "count", "type":{ "base":"int" }, "comment":"a positive integer (default: 0)"}' */
                "(count):d,"
  /* specs/reddit/search.json:17:20
     '{ "name": "include_facets", "type":{ "base":"bool" }, "comment":"boolean value"}' */
                "(include_facets):b,"
  /* specs/reddit/search.json:18:20
     '{ "name": "limit", "type":{ "base":"int" }, "comment":"the maximum number of items desired (default: 25, maximum: 100)"}' */
                "(limit):d,"
  /* specs/reddit/search.json:19:20
     '{ "name": "q", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 512 characters"}' */
                "(q):?s,"
  /* specs/reddit/search.json:20:20
     '{ "name": "restrict_sr", "type":{ "base":"bool" }, "comment":"boolean value"}' */
                "(restrict_sr):b,"
  /* specs/reddit/search.json:21:20
     '{ "name": "show", "type":{ "base":"char", "dec":"*" }, "comment":"(optional)the string all"}' */
                "(show):?s,"
  /* specs/reddit/search.json:22:20
     '{ "name": "sort", "type":{ "base":"char", "dec":"*" }, "comment":"one of(relevance, hot, top, new, comments)"}' */
                "(sort):?s,"
  /* specs/reddit/search.json:23:20
     '{ "name": "sr_detail", "type":{ "base":"char", "dec":"*" }, "comment":"expand subreddits"}' */
                "(sr_detail):?s,"
  /* specs/reddit/search.json:24:20
     '{ "name": "t", "type":{ "base":"char", "dec":"*" }, "comment":"one of(hour, day, week, month, year, all)"}' */
                "(t):?s,"
  /* specs/reddit/search.json:25:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"(optional) comma-delimited list of result types (sr, link, user)"}' */
                "(type):?s,",
  /* specs/reddit/search.json:13:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
                &p->after,
  /* specs/reddit/search.json:14:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
                &p->before,
  /* specs/reddit/search.json:15:20
     '{ "name": "category", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 5 character"}' */
                &p->category,
  /* specs/reddit/search.json:16:20
     '{ "name": "count", "type":{ "base":"int" }, "comment":"a positive integer (default: 0)"}' */
                &p->count,
  /* specs/reddit/search.json:17:20
     '{ "name": "include_facets", "type":{ "base":"bool" }, "comment":"boolean value"}' */
                &p->include_facets,
  /* specs/reddit/search.json:18:20
     '{ "name": "limit", "type":{ "base":"int" }, "comment":"the maximum number of items desired (default: 25, maximum: 100)"}' */
                &p->limit,
  /* specs/reddit/search.json:19:20
     '{ "name": "q", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 512 characters"}' */
                &p->q,
  /* specs/reddit/search.json:20:20
     '{ "name": "restrict_sr", "type":{ "base":"bool" }, "comment":"boolean value"}' */
                &p->restrict_sr,
  /* specs/reddit/search.json:21:20
     '{ "name": "show", "type":{ "base":"char", "dec":"*" }, "comment":"(optional)the string all"}' */
                &p->show,
  /* specs/reddit/search.json:22:20
     '{ "name": "sort", "type":{ "base":"char", "dec":"*" }, "comment":"one of(relevance, hot, top, new, comments)"}' */
                &p->sort,
  /* specs/reddit/search.json:23:20
     '{ "name": "sr_detail", "type":{ "base":"char", "dec":"*" }, "comment":"expand subreddits"}' */
                &p->sr_detail,
  /* specs/reddit/search.json:24:20
     '{ "name": "t", "type":{ "base":"char", "dec":"*" }, "comment":"one of(hour, day, week, month, year, all)"}' */
                &p->t,
  /* specs/reddit/search.json:25:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"(optional) comma-delimited list of result types (sr, link, user)"}' */
                &p->type);
  ret = r;
}

size_t reddit_search_params_to_json(char *json, size_t len, struct reddit_search_params *p)
{
  size_t r;
  void *arg_switches[13]={NULL};
  /* specs/reddit/search.json:13:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
  arg_switches[0] = p->after;

  /* specs/reddit/search.json:14:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
  arg_switches[1] = p->before;

  /* specs/reddit/search.json:15:20
     '{ "name": "category", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 5 character"}' */
  arg_switches[2] = p->category;

  /* specs/reddit/search.json:16:20
     '{ "name": "count", "type":{ "base":"int" }, "comment":"a positive integer (default: 0)"}' */
  arg_switches[3] = &p->count;

  /* specs/reddit/search.json:17:20
     '{ "name": "include_facets", "type":{ "base":"bool" }, "comment":"boolean value"}' */
  arg_switches[4] = &p->include_facets;

  /* specs/reddit/search.json:18:20
     '{ "name": "limit", "type":{ "base":"int" }, "comment":"the maximum number of items desired (default: 25, maximum: 100)"}' */
  arg_switches[5] = &p->limit;

  /* specs/reddit/search.json:19:20
     '{ "name": "q", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 512 characters"}' */
  arg_switches[6] = p->q;

  /* specs/reddit/search.json:20:20
     '{ "name": "restrict_sr", "type":{ "base":"bool" }, "comment":"boolean value"}' */
  arg_switches[7] = &p->restrict_sr;

  /* specs/reddit/search.json:21:20
     '{ "name": "show", "type":{ "base":"char", "dec":"*" }, "comment":"(optional)the string all"}' */
  arg_switches[8] = p->show;

  /* specs/reddit/search.json:22:20
     '{ "name": "sort", "type":{ "base":"char", "dec":"*" }, "comment":"one of(relevance, hot, top, new, comments)"}' */
  arg_switches[9] = p->sort;

  /* specs/reddit/search.json:23:20
     '{ "name": "sr_detail", "type":{ "base":"char", "dec":"*" }, "comment":"expand subreddits"}' */
  arg_switches[10] = p->sr_detail;

  /* specs/reddit/search.json:24:20
     '{ "name": "t", "type":{ "base":"char", "dec":"*" }, "comment":"one of(hour, day, week, month, year, all)"}' */
  arg_switches[11] = p->t;

  /* specs/reddit/search.json:25:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"(optional) comma-delimited list of result types (sr, link, user)"}' */
  arg_switches[12] = p->type;

  r=json_inject(json, len, 
  /* specs/reddit/search.json:13:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
                "(after):s,"
  /* specs/reddit/search.json:14:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
                "(before):s,"
  /* specs/reddit/search.json:15:20
     '{ "name": "category", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 5 character"}' */
                "(category):s,"
  /* specs/reddit/search.json:16:20
     '{ "name": "count", "type":{ "base":"int" }, "comment":"a positive integer (default: 0)"}' */
                "(count):d,"
  /* specs/reddit/search.json:17:20
     '{ "name": "include_facets", "type":{ "base":"bool" }, "comment":"boolean value"}' */
                "(include_facets):b,"
  /* specs/reddit/search.json:18:20
     '{ "name": "limit", "type":{ "base":"int" }, "comment":"the maximum number of items desired (default: 25, maximum: 100)"}' */
                "(limit):d,"
  /* specs/reddit/search.json:19:20
     '{ "name": "q", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 512 characters"}' */
                "(q):s,"
  /* specs/reddit/search.json:20:20
     '{ "name": "restrict_sr", "type":{ "base":"bool" }, "comment":"boolean value"}' */
                "(restrict_sr):b,"
  /* specs/reddit/search.json:21:20
     '{ "name": "show", "type":{ "base":"char", "dec":"*" }, "comment":"(optional)the string all"}' */
                "(show):s,"
  /* specs/reddit/search.json:22:20
     '{ "name": "sort", "type":{ "base":"char", "dec":"*" }, "comment":"one of(relevance, hot, top, new, comments)"}' */
                "(sort):s,"
  /* specs/reddit/search.json:23:20
     '{ "name": "sr_detail", "type":{ "base":"char", "dec":"*" }, "comment":"expand subreddits"}' */
                "(sr_detail):s,"
  /* specs/reddit/search.json:24:20
     '{ "name": "t", "type":{ "base":"char", "dec":"*" }, "comment":"one of(hour, day, week, month, year, all)"}' */
                "(t):s,"
  /* specs/reddit/search.json:25:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"(optional) comma-delimited list of result types (sr, link, user)"}' */
                "(type):s,"
                "@arg_switches:b",
  /* specs/reddit/search.json:13:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
                p->after,
  /* specs/reddit/search.json:14:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
                p->before,
  /* specs/reddit/search.json:15:20
     '{ "name": "category", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 5 character"}' */
                p->category,
  /* specs/reddit/search.json:16:20
     '{ "name": "count", "type":{ "base":"int" }, "comment":"a positive integer (default: 0)"}' */
                &p->count,
  /* specs/reddit/search.json:17:20
     '{ "name": "include_facets", "type":{ "base":"bool" }, "comment":"boolean value"}' */
                &p->include_facets,
  /* specs/reddit/search.json:18:20
     '{ "name": "limit", "type":{ "base":"int" }, "comment":"the maximum number of items desired (default: 25, maximum: 100)"}' */
                &p->limit,
  /* specs/reddit/search.json:19:20
     '{ "name": "q", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 512 characters"}' */
                p->q,
  /* specs/reddit/search.json:20:20
     '{ "name": "restrict_sr", "type":{ "base":"bool" }, "comment":"boolean value"}' */
                &p->restrict_sr,
  /* specs/reddit/search.json:21:20
     '{ "name": "show", "type":{ "base":"char", "dec":"*" }, "comment":"(optional)the string all"}' */
                p->show,
  /* specs/reddit/search.json:22:20
     '{ "name": "sort", "type":{ "base":"char", "dec":"*" }, "comment":"one of(relevance, hot, top, new, comments)"}' */
                p->sort,
  /* specs/reddit/search.json:23:20
     '{ "name": "sr_detail", "type":{ "base":"char", "dec":"*" }, "comment":"expand subreddits"}' */
                p->sr_detail,
  /* specs/reddit/search.json:24:20
     '{ "name": "t", "type":{ "base":"char", "dec":"*" }, "comment":"one of(hour, day, week, month, year, all)"}' */
                p->t,
  /* specs/reddit/search.json:25:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"(optional) comma-delimited list of result types (sr, link, user)"}' */
                p->type,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void reddit_search_params_cleanup_v(void *p) {
  reddit_search_params_cleanup((struct reddit_search_params *)p);
}

void reddit_search_params_init_v(void *p) {
  reddit_search_params_init((struct reddit_search_params *)p);
}

void reddit_search_params_from_json_v(char *json, size_t len, void *pp) {
 reddit_search_params_from_json(json, len, (struct reddit_search_params**)pp);
}

size_t reddit_search_params_to_json_v(char *json, size_t len, void *p) {
  return reddit_search_params_to_json(json, len, (struct reddit_search_params*)p);
}

void reddit_search_params_list_free_v(void **p) {
  reddit_search_params_list_free((struct reddit_search_params**)p);
}

void reddit_search_params_list_from_json_v(char *str, size_t len, void *p) {
  reddit_search_params_list_from_json(str, len, (struct reddit_search_params ***)p);
}

size_t reddit_search_params_list_to_json_v(char *str, size_t len, void *p){
  return reddit_search_params_list_to_json(str, len, (struct reddit_search_params **)p);
}


void reddit_search_params_cleanup(struct reddit_search_params *d) {
  /* specs/reddit/search.json:13:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
  if (d->after)
    free(d->after);
  /* specs/reddit/search.json:14:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
  if (d->before)
    free(d->before);
  /* specs/reddit/search.json:15:20
     '{ "name": "category", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 5 character"}' */
  if (d->category)
    free(d->category);
  /* specs/reddit/search.json:16:20
     '{ "name": "count", "type":{ "base":"int" }, "comment":"a positive integer (default: 0)"}' */
  /* p->count is a scalar */
  /* specs/reddit/search.json:17:20
     '{ "name": "include_facets", "type":{ "base":"bool" }, "comment":"boolean value"}' */
  /* p->include_facets is a scalar */
  /* specs/reddit/search.json:18:20
     '{ "name": "limit", "type":{ "base":"int" }, "comment":"the maximum number of items desired (default: 25, maximum: 100)"}' */
  /* p->limit is a scalar */
  /* specs/reddit/search.json:19:20
     '{ "name": "q", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 512 characters"}' */
  if (d->q)
    free(d->q);
  /* specs/reddit/search.json:20:20
     '{ "name": "restrict_sr", "type":{ "base":"bool" }, "comment":"boolean value"}' */
  /* p->restrict_sr is a scalar */
  /* specs/reddit/search.json:21:20
     '{ "name": "show", "type":{ "base":"char", "dec":"*" }, "comment":"(optional)the string all"}' */
  if (d->show)
    free(d->show);
  /* specs/reddit/search.json:22:20
     '{ "name": "sort", "type":{ "base":"char", "dec":"*" }, "comment":"one of(relevance, hot, top, new, comments)"}' */
  if (d->sort)
    free(d->sort);
  /* specs/reddit/search.json:23:20
     '{ "name": "sr_detail", "type":{ "base":"char", "dec":"*" }, "comment":"expand subreddits"}' */
  if (d->sr_detail)
    free(d->sr_detail);
  /* specs/reddit/search.json:24:20
     '{ "name": "t", "type":{ "base":"char", "dec":"*" }, "comment":"one of(hour, day, week, month, year, all)"}' */
  if (d->t)
    free(d->t);
  /* specs/reddit/search.json:25:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"(optional) comma-delimited list of result types (sr, link, user)"}' */
  if (d->type)
    free(d->type);
}

void reddit_search_params_init(struct reddit_search_params *p) {
  memset(p, 0, sizeof(struct reddit_search_params));
  /* specs/reddit/search.json:13:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */

  /* specs/reddit/search.json:14:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */

  /* specs/reddit/search.json:15:20
     '{ "name": "category", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 5 character"}' */

  /* specs/reddit/search.json:16:20
     '{ "name": "count", "type":{ "base":"int" }, "comment":"a positive integer (default: 0)"}' */

  /* specs/reddit/search.json:17:20
     '{ "name": "include_facets", "type":{ "base":"bool" }, "comment":"boolean value"}' */

  /* specs/reddit/search.json:18:20
     '{ "name": "limit", "type":{ "base":"int" }, "comment":"the maximum number of items desired (default: 25, maximum: 100)"}' */

  /* specs/reddit/search.json:19:20
     '{ "name": "q", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 512 characters"}' */

  /* specs/reddit/search.json:20:20
     '{ "name": "restrict_sr", "type":{ "base":"bool" }, "comment":"boolean value"}' */

  /* specs/reddit/search.json:21:20
     '{ "name": "show", "type":{ "base":"char", "dec":"*" }, "comment":"(optional)the string all"}' */

  /* specs/reddit/search.json:22:20
     '{ "name": "sort", "type":{ "base":"char", "dec":"*" }, "comment":"one of(relevance, hot, top, new, comments)"}' */

  /* specs/reddit/search.json:23:20
     '{ "name": "sr_detail", "type":{ "base":"char", "dec":"*" }, "comment":"expand subreddits"}' */

  /* specs/reddit/search.json:24:20
     '{ "name": "t", "type":{ "base":"char", "dec":"*" }, "comment":"one of(hour, day, week, month, year, all)"}' */

  /* specs/reddit/search.json:25:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"(optional) comma-delimited list of result types (sr, link, user)"}' */

}
void reddit_search_params_list_free(struct reddit_search_params **p) {
  ntl_free((void**)p, (vfvp)reddit_search_params_cleanup);
}

void reddit_search_params_list_from_json(char *str, size_t len, struct reddit_search_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct reddit_search_params);
  d.init_elem = NULL;
  d.elem_from_buf = reddit_search_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t reddit_search_params_list_to_json(char *str, size_t len, struct reddit_search_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, reddit_search_params_to_json_v);
}

