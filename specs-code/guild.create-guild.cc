/* This file is generated from specs/guild.create-guild.json, Please don't edit it. */
#include "specs.h"
/*

*/
namespace discord {
namespace guild {
namespace create_guild {

void params_from_json(char *json, size_t len, struct params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.create-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[200+1]" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
                "(name):s,"
  /* specs/guild.create-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
                "(region):?s,"
  /* specs/guild.create-guild.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
                "(icon):?s,"
  /* specs/guild.create-guild.json:17:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
                "(verification_level):d,"
  /* specs/guild.create-guild.json:19:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
                "(default_message_notifications):d,"
  /* specs/guild.create-guild.json:21:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
                "(explicit_content_filter):d,"
  /* specs/guild.create-guild.json:23:20
     '{ "name": "roles", "type":{ "base":"int" }, 
          "todo":true, "comment":"new guild roles" }'
  */
  /* specs/guild.create-guild.json:25:20
     '{ "name": "channels", "type":{ "base":"discord::channel::dati", "dec":"ntl" }, 
          "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}'
  */
                "(channels):F,"
  /* specs/guild.create-guild.json:27:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
                "(afk_channel_id):F,"
  /* specs/guild.create-guild.json:29:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
                "(afk_timeout):d,"
  /* specs/guild.create-guild.json:31:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, 
          "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
                "(system_channel_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.create-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[200+1]" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
                p->name,
  /* specs/guild.create-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
                &p->region,
  /* specs/guild.create-guild.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
                &p->icon,
  /* specs/guild.create-guild.json:17:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
                &p->verification_level,
  /* specs/guild.create-guild.json:19:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
                &p->default_message_notifications,
  /* specs/guild.create-guild.json:21:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
                &p->explicit_content_filter,
  /* specs/guild.create-guild.json:23:20
     '{ "name": "roles", "type":{ "base":"int" }, 
          "todo":true, "comment":"new guild roles" }'
  */
  /* specs/guild.create-guild.json:25:20
     '{ "name": "channels", "type":{ "base":"discord::channel::dati", "dec":"ntl" }, 
          "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}'
  */
                discord::channel::dati_list_from_json, &p->channels,
  /* specs/guild.create-guild.json:27:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
                orka_strtoull, &p->afk_channel_id,
  /* specs/guild.create-guild.json:29:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
                &p->afk_timeout,
  /* specs/guild.create-guild.json:31:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, 
          "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
                orka_strtoull, &p->system_channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void params_use_default_inject_settings(struct params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.create-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[200+1]" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
  p->__M.arg_switches[0] = p->name;

  /* specs/guild.create-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
  if (p->region != NULL)
    p->__M.arg_switches[1] = p->region;

  /* specs/guild.create-guild.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
  if (p->icon != NULL)
    p->__M.arg_switches[2] = p->icon;

  /* specs/guild.create-guild.json:17:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
  if (p->verification_level != 0)
    p->__M.arg_switches[3] = &p->verification_level;

  /* specs/guild.create-guild.json:19:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
  if (p->default_message_notifications != 0)
    p->__M.arg_switches[4] = &p->default_message_notifications;

  /* specs/guild.create-guild.json:21:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
  if (p->explicit_content_filter != 0)
    p->__M.arg_switches[5] = &p->explicit_content_filter;

  /* specs/guild.create-guild.json:23:20
     '{ "name": "roles", "type":{ "base":"int" }, 
          "todo":true, "comment":"new guild roles" }'
  */

  /* specs/guild.create-guild.json:25:20
     '{ "name": "channels", "type":{ "base":"discord::channel::dati", "dec":"ntl" }, 
          "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}'
  */
  if (p->channels != NULL)
    p->__M.arg_switches[7] = p->channels;

  /* specs/guild.create-guild.json:27:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
  if (p->afk_channel_id != 0)
    p->__M.arg_switches[8] = &p->afk_channel_id;

  /* specs/guild.create-guild.json:29:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
  if (p->afk_timeout != 0)
    p->__M.arg_switches[9] = &p->afk_timeout;

  /* specs/guild.create-guild.json:31:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, 
          "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
  if (p->system_channel_id != 0)
    p->__M.arg_switches[10] = &p->system_channel_id;

}

size_t params_to_json(char *json, size_t len, struct params *p)
{
  size_t r;
  params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.create-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[200+1]" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
                "(name):s,"
  /* specs/guild.create-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
                "(region):s,"
  /* specs/guild.create-guild.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
                "(icon):s,"
  /* specs/guild.create-guild.json:17:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
                "(verification_level):d,"
  /* specs/guild.create-guild.json:19:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
                "(default_message_notifications):d,"
  /* specs/guild.create-guild.json:21:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
                "(explicit_content_filter):d,"
  /* specs/guild.create-guild.json:23:20
     '{ "name": "roles", "type":{ "base":"int" }, 
          "todo":true, "comment":"new guild roles" }'
  */
  /* specs/guild.create-guild.json:25:20
     '{ "name": "channels", "type":{ "base":"discord::channel::dati", "dec":"ntl" }, 
          "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}'
  */
                "(channels):F,"
  /* specs/guild.create-guild.json:27:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
                "(afk_channel_id):|F|,"
  /* specs/guild.create-guild.json:29:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
                "(afk_timeout):d,"
  /* specs/guild.create-guild.json:31:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, 
          "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
                "(system_channel_id):|F|,"
                "@arg_switches:b",
  /* specs/guild.create-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[200+1]" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
                p->name,
  /* specs/guild.create-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
                p->region,
  /* specs/guild.create-guild.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
                p->icon,
  /* specs/guild.create-guild.json:17:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
                &p->verification_level,
  /* specs/guild.create-guild.json:19:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
                &p->default_message_notifications,
  /* specs/guild.create-guild.json:21:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
                &p->explicit_content_filter,
  /* specs/guild.create-guild.json:23:20
     '{ "name": "roles", "type":{ "base":"int" }, 
          "todo":true, "comment":"new guild roles" }'
  */
  /* specs/guild.create-guild.json:25:20
     '{ "name": "channels", "type":{ "base":"discord::channel::dati", "dec":"ntl" }, 
          "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}'
  */
                discord::channel::dati_list_to_json, p->channels,
  /* specs/guild.create-guild.json:27:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
                orka_ulltostr, &p->afk_channel_id,
  /* specs/guild.create-guild.json:29:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
                &p->afk_timeout,
  /* specs/guild.create-guild.json:31:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, 
          "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
                orka_ulltostr, &p->system_channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void params_cleanup_v(void *p) {
  params_cleanup((struct params *)p);
}

void params_init_v(void *p) {
  params_init((struct params *)p);
}

void params_free_v(void *p) {
 params_free((struct params *)p);
};

void params_from_json_v(char *json, size_t len, void *p) {
 params_from_json(json, len, (struct params*)p);
}

size_t params_to_json_v(char *json, size_t len, void *p) {
  return params_to_json(json, len, (struct params*)p);
}

void params_list_free_v(void **p) {
  params_list_free((struct params**)p);
}

void params_list_from_json_v(char *str, size_t len, void *p) {
  params_list_from_json(str, len, (struct params ***)p);
}

size_t params_list_to_json_v(char *str, size_t len, void *p){
  return params_list_to_json(str, len, (struct params **)p);
}


void params_cleanup(struct params *d) {
  /* specs/guild.create-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[200+1]" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
  //p->name is a scalar
  /* specs/guild.create-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
  if (d->region)
    free(d->region);
  /* specs/guild.create-guild.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
  if (d->icon)
    free(d->icon);
  /* specs/guild.create-guild.json:17:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
  //p->verification_level is a scalar
  /* specs/guild.create-guild.json:19:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
  //p->default_message_notifications is a scalar
  /* specs/guild.create-guild.json:21:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
  //p->explicit_content_filter is a scalar
  /* specs/guild.create-guild.json:23:20
     '{ "name": "roles", "type":{ "base":"int" }, 
          "todo":true, "comment":"new guild roles" }'
  */
  //@todo p->(null)
  /* specs/guild.create-guild.json:25:20
     '{ "name": "channels", "type":{ "base":"discord::channel::dati", "dec":"ntl" }, 
          "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}'
  */
  if (d->channels)
    discord::channel::dati_list_free(d->channels);
  /* specs/guild.create-guild.json:27:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
  //p->afk_channel_id is a scalar
  /* specs/guild.create-guild.json:29:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
  //p->afk_timeout is a scalar
  /* specs/guild.create-guild.json:31:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, 
          "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
  //p->system_channel_id is a scalar
}

void params_init(struct params *p) {
  memset(p, 0, sizeof(struct params));
  /* specs/guild.create-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[200+1]" }, 
          "comment":"name of the guild (2-100) characters"}'
  */

  /* specs/guild.create-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */

  /* specs/guild.create-guild.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */

  /* specs/guild.create-guild.json:17:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */

  /* specs/guild.create-guild.json:19:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */

  /* specs/guild.create-guild.json:21:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */

  /* specs/guild.create-guild.json:23:20
     '{ "name": "roles", "type":{ "base":"int" }, 
          "todo":true, "comment":"new guild roles" }'
  */

  /* specs/guild.create-guild.json:25:20
     '{ "name": "channels", "type":{ "base":"discord::channel::dati", "dec":"ntl" }, 
          "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}'
  */

  /* specs/guild.create-guild.json:27:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */

  /* specs/guild.create-guild.json:29:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */

  /* specs/guild.create-guild.json:31:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, 
          "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */

}
struct params* params_alloc() {
  struct params *p= (struct params*)malloc(sizeof(struct params));
  params_init(p);
  return p;
}

void params_free(struct params *p) {
  params_cleanup(p);
  free(p);
}

void params_list_free(struct params **p) {
  ntl_free((void**)p, (vfvp)params_cleanup);
}

void params_list_from_json(char *str, size_t len, struct params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct params);
  d.init_elem = params_init_v;
  d.elem_from_buf = params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t params_list_to_json(char *str, size_t len, struct params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, params_to_json_v);
}

} // namespace create_guild
} // namespace guild
} // namespace discord
