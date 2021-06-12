/* This file is generated from specs/discord/guild.search-guild-members.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_search_guild_members_params_from_json(char *json, size_t len, struct discord_search_guild_members_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.search-guild-members.json:11:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null
          "comment": "Query string to match username(s) and nickname(s) against." }'
  */
                "(query):?s,"
  /* specs/discord/guild.search-guild-members.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, 
          "comment": "max number of members to return (1-1000)"}'
  */
                "(limit):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.search-guild-members.json:11:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null
          "comment": "Query string to match username(s) and nickname(s) against." }'
  */
                &p->query,
  /* specs/discord/guild.search-guild-members.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, 
          "comment": "max number of members to return (1-1000)"}'
  */
                &p->limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_search_guild_members_params_use_default_inject_settings(struct discord_search_guild_members_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.search-guild-members.json:11:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null
          "comment": "Query string to match username(s) and nickname(s) against." }'
  */
  if (p->query != NULL)
    p->__M.arg_switches[0] = p->query;

  /* specs/discord/guild.search-guild-members.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, 
          "comment": "max number of members to return (1-1000)"}'
  */
  if (p->limit != 0)
    p->__M.arg_switches[1] = &p->limit;

}

size_t discord_search_guild_members_params_to_json(char *json, size_t len, struct discord_search_guild_members_params *p)
{
  size_t r;
  discord_search_guild_members_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.search-guild-members.json:11:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null
          "comment": "Query string to match username(s) and nickname(s) against." }'
  */
                "(query):s,"
  /* specs/discord/guild.search-guild-members.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, 
          "comment": "max number of members to return (1-1000)"}'
  */
                "(limit):d,"
                "@arg_switches:b",
  /* specs/discord/guild.search-guild-members.json:11:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null
          "comment": "Query string to match username(s) and nickname(s) against." }'
  */
                p->query,
  /* specs/discord/guild.search-guild-members.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, 
          "comment": "max number of members to return (1-1000)"}'
  */
                &p->limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_search_guild_members_params_cleanup_v(void *p) {
  discord_search_guild_members_params_cleanup((struct discord_search_guild_members_params *)p);
}

void discord_search_guild_members_params_init_v(void *p) {
  discord_search_guild_members_params_init((struct discord_search_guild_members_params *)p);
}

void discord_search_guild_members_params_free_v(void *p) {
 discord_search_guild_members_params_free((struct discord_search_guild_members_params *)p);
};

void discord_search_guild_members_params_from_json_v(char *json, size_t len, void *p) {
 discord_search_guild_members_params_from_json(json, len, (struct discord_search_guild_members_params*)p);
}

size_t discord_search_guild_members_params_to_json_v(char *json, size_t len, void *p) {
  return discord_search_guild_members_params_to_json(json, len, (struct discord_search_guild_members_params*)p);
}

void discord_search_guild_members_params_list_free_v(void **p) {
  discord_search_guild_members_params_list_free((struct discord_search_guild_members_params**)p);
}

void discord_search_guild_members_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_search_guild_members_params_list_from_json(str, len, (struct discord_search_guild_members_params ***)p);
}

size_t discord_search_guild_members_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_search_guild_members_params_list_to_json(str, len, (struct discord_search_guild_members_params **)p);
}


void discord_search_guild_members_params_cleanup(struct discord_search_guild_members_params *d) {
  /* specs/discord/guild.search-guild-members.json:11:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null
          "comment": "Query string to match username(s) and nickname(s) against." }'
  */
  if (d->query)
    free(d->query);
  /* specs/discord/guild.search-guild-members.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, 
          "comment": "max number of members to return (1-1000)"}'
  */
  //p->limit is a scalar
}

void discord_search_guild_members_params_init(struct discord_search_guild_members_params *p) {
  memset(p, 0, sizeof(struct discord_search_guild_members_params));
  /* specs/discord/guild.search-guild-members.json:11:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null
          "comment": "Query string to match username(s) and nickname(s) against." }'
  */

  /* specs/discord/guild.search-guild-members.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, 
          "comment": "max number of members to return (1-1000)"}'
  */

}
struct discord_search_guild_members_params* discord_search_guild_members_params_alloc() {
  struct discord_search_guild_members_params *p= (struct discord_search_guild_members_params*)malloc(sizeof(struct discord_search_guild_members_params));
  discord_search_guild_members_params_init(p);
  return p;
}

void discord_search_guild_members_params_free(struct discord_search_guild_members_params *p) {
  discord_search_guild_members_params_cleanup(p);
  free(p);
}

void discord_search_guild_members_params_list_free(struct discord_search_guild_members_params **p) {
  ntl_free((void**)p, (vfvp)discord_search_guild_members_params_cleanup);
}

void discord_search_guild_members_params_list_from_json(char *str, size_t len, struct discord_search_guild_members_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_search_guild_members_params);
  d.init_elem = discord_search_guild_members_params_init_v;
  d.elem_from_buf = discord_search_guild_members_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_search_guild_members_params_list_to_json(char *str, size_t len, struct discord_search_guild_members_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_search_guild_members_params_to_json_v);
}

