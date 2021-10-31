/* This file is generated from specs/discord/interaction.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/interaction.endpoints-params.c
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_edit_original_interaction_response_params_from_json(char *json, size_t len, struct discord_edit_original_interaction_response_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_edit_original_interaction_response_params *p = *pp;
  discord_edit_original_interaction_response_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/interaction.endpoints-params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                "(content):?s,"
  /* specs/discord/interaction.endpoints-params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                "(embeds):F,"
  /* specs/discord/interaction.endpoints-params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                "(payload_json):?s,"
  /* specs/discord/interaction.endpoints-params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* specs/discord/interaction.endpoints-params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* specs/discord/interaction.endpoints-params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,",
  /* specs/discord/interaction.endpoints-params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                &p->content,
  /* specs/discord/interaction.endpoints-params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                discord_embed_list_from_json, &p->embeds,
  /* specs/discord/interaction.endpoints-params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                &p->payload_json,
  /* specs/discord/interaction.endpoints-params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_from_json, &p->allowed_mentions,
  /* specs/discord/interaction.endpoints-params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_from_json, &p->attachments,
  /* specs/discord/interaction.endpoints-params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_from_json, &p->components);
  ret = r;
}

size_t discord_edit_original_interaction_response_params_to_json(char *json, size_t len, struct discord_edit_original_interaction_response_params *p)
{
  size_t r;
  void *arg_switches[6]={NULL};
  /* specs/discord/interaction.endpoints-params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  if (p->content != NULL)
    arg_switches[0] = p->content;

  /* specs/discord/interaction.endpoints-params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  if (p->embeds != NULL)
    arg_switches[1] = p->embeds;

  /* specs/discord/interaction.endpoints-params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
  if (p->payload_json != NULL)
    arg_switches[2] = p->payload_json;

  /* specs/discord/interaction.endpoints-params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (p->allowed_mentions != NULL)
    arg_switches[3] = p->allowed_mentions;

  /* specs/discord/interaction.endpoints-params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (p->attachments != NULL)
    arg_switches[4] = p->attachments;

  /* specs/discord/interaction.endpoints-params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (p->components != NULL)
    arg_switches[5] = p->components;

  r=json_inject(json, len, 
  /* specs/discord/interaction.endpoints-params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                "(content):s,"
  /* specs/discord/interaction.endpoints-params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                "(embeds):F,"
  /* specs/discord/interaction.endpoints-params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                "(payload_json):s,"
  /* specs/discord/interaction.endpoints-params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* specs/discord/interaction.endpoints-params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* specs/discord/interaction.endpoints-params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,"
                "@arg_switches:b",
  /* specs/discord/interaction.endpoints-params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                p->content,
  /* specs/discord/interaction.endpoints-params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                discord_embed_list_to_json, p->embeds,
  /* specs/discord/interaction.endpoints-params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                p->payload_json,
  /* specs/discord/interaction.endpoints-params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_to_json, p->allowed_mentions,
  /* specs/discord/interaction.endpoints-params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_to_json, p->attachments,
  /* specs/discord/interaction.endpoints-params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_to_json, p->components,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_edit_original_interaction_response_params_cleanup_v(void *p) {
  discord_edit_original_interaction_response_params_cleanup((struct discord_edit_original_interaction_response_params *)p);
}

void discord_edit_original_interaction_response_params_init_v(void *p) {
  discord_edit_original_interaction_response_params_init((struct discord_edit_original_interaction_response_params *)p);
}

void discord_edit_original_interaction_response_params_from_json_v(char *json, size_t len, void *pp) {
 discord_edit_original_interaction_response_params_from_json(json, len, (struct discord_edit_original_interaction_response_params**)pp);
}

size_t discord_edit_original_interaction_response_params_to_json_v(char *json, size_t len, void *p) {
  return discord_edit_original_interaction_response_params_to_json(json, len, (struct discord_edit_original_interaction_response_params*)p);
}

void discord_edit_original_interaction_response_params_list_free_v(void **p) {
  discord_edit_original_interaction_response_params_list_free((struct discord_edit_original_interaction_response_params**)p);
}

void discord_edit_original_interaction_response_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_edit_original_interaction_response_params_list_from_json(str, len, (struct discord_edit_original_interaction_response_params ***)p);
}

size_t discord_edit_original_interaction_response_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_edit_original_interaction_response_params_list_to_json(str, len, (struct discord_edit_original_interaction_response_params **)p);
}


void discord_edit_original_interaction_response_params_cleanup(struct discord_edit_original_interaction_response_params *d) {
  /* specs/discord/interaction.endpoints-params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  if (d->content)
    free(d->content);
  /* specs/discord/interaction.endpoints-params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  if (d->embeds)
    discord_embed_list_free(d->embeds);
  /* specs/discord/interaction.endpoints-params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
  if (d->payload_json)
    free(d->payload_json);
  /* specs/discord/interaction.endpoints-params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (d->allowed_mentions) {
    discord_allowed_mentions_cleanup(d->allowed_mentions);
    free(d->allowed_mentions);
  }
  /* specs/discord/interaction.endpoints-params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (d->attachments)
    discord_attachment_list_free(d->attachments);
  /* specs/discord/interaction.endpoints-params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (d->components)
    discord_component_list_free(d->components);
}

void discord_edit_original_interaction_response_params_init(struct discord_edit_original_interaction_response_params *p) {
  memset(p, 0, sizeof(struct discord_edit_original_interaction_response_params));
  /* specs/discord/interaction.endpoints-params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */

  /* specs/discord/interaction.endpoints-params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */

  /* specs/discord/interaction.endpoints-params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */

  /* specs/discord/interaction.endpoints-params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */

  /* specs/discord/interaction.endpoints-params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */

  /* specs/discord/interaction.endpoints-params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */

}
void discord_edit_original_interaction_response_params_list_free(struct discord_edit_original_interaction_response_params **p) {
  ntl_free((void**)p, (vfvp)discord_edit_original_interaction_response_params_cleanup);
}

void discord_edit_original_interaction_response_params_list_from_json(char *str, size_t len, struct discord_edit_original_interaction_response_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_edit_original_interaction_response_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_edit_original_interaction_response_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_edit_original_interaction_response_params_list_to_json(char *str, size_t len, struct discord_edit_original_interaction_response_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_edit_original_interaction_response_params_to_json_v);
}


void discord_create_followup_message_params_from_json(char *json, size_t len, struct discord_create_followup_message_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_create_followup_message_params *p = *pp;
  discord_create_followup_message_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/interaction.endpoints-params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
                "(content):?s,"
  /* specs/discord/interaction.endpoints-params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
                "(username):?s,"
  /* specs/discord/interaction.endpoints-params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
                "(avatar_url):?s,"
  /* specs/discord/interaction.endpoints-params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                "(tts):b,"
  /* specs/discord/interaction.endpoints-params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* specs/discord/interaction.endpoints-params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
                "(embeds):F,"
  /* specs/discord/interaction.endpoints-params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
                "(payload_json):?s,"
  /* specs/discord/interaction.endpoints-params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
                "(allowed_mentions):F,"
  /* specs/discord/interaction.endpoints-params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
                "(components):F,"
  /* specs/discord/interaction.endpoints-params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
                "(flags):d,",
  /* specs/discord/interaction.endpoints-params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
                &p->content,
  /* specs/discord/interaction.endpoints-params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
                &p->username,
  /* specs/discord/interaction.endpoints-params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
                &p->avatar_url,
  /* specs/discord/interaction.endpoints-params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                &p->tts,
  /* specs/discord/interaction.endpoints-params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_from_json, &p->attachments,
  /* specs/discord/interaction.endpoints-params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
                discord_embed_from_json, &p->embeds,
  /* specs/discord/interaction.endpoints-params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
                &p->payload_json,
  /* specs/discord/interaction.endpoints-params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
                discord_allowed_mentions_from_json, &p->allowed_mentions,
  /* specs/discord/interaction.endpoints-params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
                discord_component_list_from_json, &p->components,
  /* specs/discord/interaction.endpoints-params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
                &p->flags);
  ret = r;
}

size_t discord_create_followup_message_params_to_json(char *json, size_t len, struct discord_create_followup_message_params *p)
{
  size_t r;
  void *arg_switches[12]={NULL};
  /* specs/discord/interaction.endpoints-params.json:27:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)", "default_value":true }' */
  arg_switches[0] = &p->wait;

  /* specs/discord/interaction.endpoints-params.json:28:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */
  if (p->thread_id != 0)
    arg_switches[1] = &p->thread_id;

  /* specs/discord/interaction.endpoints-params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
  if (p->content != NULL)
    arg_switches[2] = p->content;

  /* specs/discord/interaction.endpoints-params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
  if (p->username != NULL)
    arg_switches[3] = p->username;

  /* specs/discord/interaction.endpoints-params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
  if (p->avatar_url != NULL)
    arg_switches[4] = p->avatar_url;

  /* specs/discord/interaction.endpoints-params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  if (p->tts != false)
    arg_switches[5] = &p->tts;

  /* specs/discord/interaction.endpoints-params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (p->attachments != NULL)
    arg_switches[6] = p->attachments;

  /* specs/discord/interaction.endpoints-params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
  if (p->embeds != NULL)
    arg_switches[7] = p->embeds;

  /* specs/discord/interaction.endpoints-params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
  if (p->payload_json != NULL)
    arg_switches[8] = p->payload_json;

  /* specs/discord/interaction.endpoints-params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
  if (p->allowed_mentions != NULL)
    arg_switches[9] = p->allowed_mentions;

  /* specs/discord/interaction.endpoints-params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
  if (p->components != NULL)
    arg_switches[10] = p->components;

  /* specs/discord/interaction.endpoints-params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
  if (p->flags != 0)
    arg_switches[11] = &p->flags;

  r=json_inject(json, len, 
  /* specs/discord/interaction.endpoints-params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
                "(content):s,"
  /* specs/discord/interaction.endpoints-params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
                "(username):s,"
  /* specs/discord/interaction.endpoints-params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
                "(avatar_url):s,"
  /* specs/discord/interaction.endpoints-params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                "(tts):b,"
  /* specs/discord/interaction.endpoints-params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* specs/discord/interaction.endpoints-params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
                "(embeds):F,"
  /* specs/discord/interaction.endpoints-params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
                "(payload_json):s,"
  /* specs/discord/interaction.endpoints-params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
                "(allowed_mentions):F,"
  /* specs/discord/interaction.endpoints-params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
                "(components):F,"
  /* specs/discord/interaction.endpoints-params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
                "(flags):d,"
                "@arg_switches:b",
  /* specs/discord/interaction.endpoints-params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
                p->content,
  /* specs/discord/interaction.endpoints-params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
                p->username,
  /* specs/discord/interaction.endpoints-params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
                p->avatar_url,
  /* specs/discord/interaction.endpoints-params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                &p->tts,
  /* specs/discord/interaction.endpoints-params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_to_json, p->attachments,
  /* specs/discord/interaction.endpoints-params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
                discord_embed_to_json, p->embeds,
  /* specs/discord/interaction.endpoints-params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
                p->payload_json,
  /* specs/discord/interaction.endpoints-params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
                discord_allowed_mentions_to_json, p->allowed_mentions,
  /* specs/discord/interaction.endpoints-params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
                discord_component_list_to_json, p->components,
  /* specs/discord/interaction.endpoints-params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
                &p->flags,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_followup_message_params_cleanup_v(void *p) {
  discord_create_followup_message_params_cleanup((struct discord_create_followup_message_params *)p);
}

void discord_create_followup_message_params_init_v(void *p) {
  discord_create_followup_message_params_init((struct discord_create_followup_message_params *)p);
}

void discord_create_followup_message_params_from_json_v(char *json, size_t len, void *pp) {
 discord_create_followup_message_params_from_json(json, len, (struct discord_create_followup_message_params**)pp);
}

size_t discord_create_followup_message_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_followup_message_params_to_json(json, len, (struct discord_create_followup_message_params*)p);
}

void discord_create_followup_message_params_list_free_v(void **p) {
  discord_create_followup_message_params_list_free((struct discord_create_followup_message_params**)p);
}

void discord_create_followup_message_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_followup_message_params_list_from_json(str, len, (struct discord_create_followup_message_params ***)p);
}

size_t discord_create_followup_message_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_followup_message_params_list_to_json(str, len, (struct discord_create_followup_message_params **)p);
}


void discord_create_followup_message_params_cleanup(struct discord_create_followup_message_params *d) {
  /* specs/discord/interaction.endpoints-params.json:27:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)", "default_value":true }' */
  /* p->wait is a scalar */
  /* specs/discord/interaction.endpoints-params.json:28:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */
  /* p->thread_id is a scalar */
  /* specs/discord/interaction.endpoints-params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
  if (d->content)
    free(d->content);
  /* specs/discord/interaction.endpoints-params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
  if (d->username)
    free(d->username);
  /* specs/discord/interaction.endpoints-params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
  if (d->avatar_url)
    free(d->avatar_url);
  /* specs/discord/interaction.endpoints-params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  /* p->tts is a scalar */
  /* specs/discord/interaction.endpoints-params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (d->attachments)
    discord_attachment_list_free(d->attachments);
  /* specs/discord/interaction.endpoints-params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
  if (d->embeds) {
    discord_embed_cleanup(d->embeds);
    free(d->embeds);
  }
  /* specs/discord/interaction.endpoints-params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
  if (d->payload_json)
    free(d->payload_json);
  /* specs/discord/interaction.endpoints-params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
  if (d->allowed_mentions) {
    discord_allowed_mentions_cleanup(d->allowed_mentions);
    free(d->allowed_mentions);
  }
  /* specs/discord/interaction.endpoints-params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
  if (d->components)
    discord_component_list_free(d->components);
  /* specs/discord/interaction.endpoints-params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
  /* p->flags is a scalar */
}

void discord_create_followup_message_params_init(struct discord_create_followup_message_params *p) {
  memset(p, 0, sizeof(struct discord_create_followup_message_params));
  /* specs/discord/interaction.endpoints-params.json:27:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)", "default_value":true }' */

  /* specs/discord/interaction.endpoints-params.json:28:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */

  /* specs/discord/interaction.endpoints-params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */

  /* specs/discord/interaction.endpoints-params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */

  /* specs/discord/interaction.endpoints-params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */

  /* specs/discord/interaction.endpoints-params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */

  /* specs/discord/interaction.endpoints-params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */

  /* specs/discord/interaction.endpoints-params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */

  /* specs/discord/interaction.endpoints-params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */

  /* specs/discord/interaction.endpoints-params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */

  /* specs/discord/interaction.endpoints-params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */

  /* specs/discord/interaction.endpoints-params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */

}
void discord_create_followup_message_params_list_free(struct discord_create_followup_message_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_followup_message_params_cleanup);
}

void discord_create_followup_message_params_list_from_json(char *str, size_t len, struct discord_create_followup_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_followup_message_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_create_followup_message_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_followup_message_params_list_to_json(char *str, size_t len, struct discord_create_followup_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_create_followup_message_params_to_json_v);
}


void discord_edit_followup_message_params_from_json(char *json, size_t len, struct discord_edit_followup_message_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_edit_followup_message_params *p = *pp;
  discord_edit_followup_message_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/interaction.endpoints-params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                "(content):?s,"
  /* specs/discord/interaction.endpoints-params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                "(embeds):F,"
  /* specs/discord/interaction.endpoints-params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                "(payload_json):?s,"
  /* specs/discord/interaction.endpoints-params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* specs/discord/interaction.endpoints-params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* specs/discord/interaction.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,",
  /* specs/discord/interaction.endpoints-params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                &p->content,
  /* specs/discord/interaction.endpoints-params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                discord_embed_list_from_json, &p->embeds,
  /* specs/discord/interaction.endpoints-params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                &p->payload_json,
  /* specs/discord/interaction.endpoints-params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_from_json, &p->allowed_mentions,
  /* specs/discord/interaction.endpoints-params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_from_json, &p->attachments,
  /* specs/discord/interaction.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_from_json, &p->components);
  ret = r;
}

size_t discord_edit_followup_message_params_to_json(char *json, size_t len, struct discord_edit_followup_message_params *p)
{
  size_t r;
  void *arg_switches[6]={NULL};
  /* specs/discord/interaction.endpoints-params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  if (p->content != NULL)
    arg_switches[0] = p->content;

  /* specs/discord/interaction.endpoints-params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  if (p->embeds != NULL)
    arg_switches[1] = p->embeds;

  /* specs/discord/interaction.endpoints-params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
  if (p->payload_json != NULL)
    arg_switches[2] = p->payload_json;

  /* specs/discord/interaction.endpoints-params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (p->allowed_mentions != NULL)
    arg_switches[3] = p->allowed_mentions;

  /* specs/discord/interaction.endpoints-params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (p->attachments != NULL)
    arg_switches[4] = p->attachments;

  /* specs/discord/interaction.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (p->components != NULL)
    arg_switches[5] = p->components;

  r=json_inject(json, len, 
  /* specs/discord/interaction.endpoints-params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                "(content):s,"
  /* specs/discord/interaction.endpoints-params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                "(embeds):F,"
  /* specs/discord/interaction.endpoints-params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                "(payload_json):s,"
  /* specs/discord/interaction.endpoints-params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* specs/discord/interaction.endpoints-params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* specs/discord/interaction.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,"
                "@arg_switches:b",
  /* specs/discord/interaction.endpoints-params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                p->content,
  /* specs/discord/interaction.endpoints-params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                discord_embed_list_to_json, p->embeds,
  /* specs/discord/interaction.endpoints-params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                p->payload_json,
  /* specs/discord/interaction.endpoints-params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_to_json, p->allowed_mentions,
  /* specs/discord/interaction.endpoints-params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_to_json, p->attachments,
  /* specs/discord/interaction.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_to_json, p->components,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_edit_followup_message_params_cleanup_v(void *p) {
  discord_edit_followup_message_params_cleanup((struct discord_edit_followup_message_params *)p);
}

void discord_edit_followup_message_params_init_v(void *p) {
  discord_edit_followup_message_params_init((struct discord_edit_followup_message_params *)p);
}

void discord_edit_followup_message_params_from_json_v(char *json, size_t len, void *pp) {
 discord_edit_followup_message_params_from_json(json, len, (struct discord_edit_followup_message_params**)pp);
}

size_t discord_edit_followup_message_params_to_json_v(char *json, size_t len, void *p) {
  return discord_edit_followup_message_params_to_json(json, len, (struct discord_edit_followup_message_params*)p);
}

void discord_edit_followup_message_params_list_free_v(void **p) {
  discord_edit_followup_message_params_list_free((struct discord_edit_followup_message_params**)p);
}

void discord_edit_followup_message_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_edit_followup_message_params_list_from_json(str, len, (struct discord_edit_followup_message_params ***)p);
}

size_t discord_edit_followup_message_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_edit_followup_message_params_list_to_json(str, len, (struct discord_edit_followup_message_params **)p);
}


void discord_edit_followup_message_params_cleanup(struct discord_edit_followup_message_params *d) {
  /* specs/discord/interaction.endpoints-params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  if (d->content)
    free(d->content);
  /* specs/discord/interaction.endpoints-params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  if (d->embeds)
    discord_embed_list_free(d->embeds);
  /* specs/discord/interaction.endpoints-params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
  if (d->payload_json)
    free(d->payload_json);
  /* specs/discord/interaction.endpoints-params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (d->allowed_mentions) {
    discord_allowed_mentions_cleanup(d->allowed_mentions);
    free(d->allowed_mentions);
  }
  /* specs/discord/interaction.endpoints-params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (d->attachments)
    discord_attachment_list_free(d->attachments);
  /* specs/discord/interaction.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (d->components)
    discord_component_list_free(d->components);
}

void discord_edit_followup_message_params_init(struct discord_edit_followup_message_params *p) {
  memset(p, 0, sizeof(struct discord_edit_followup_message_params));
  /* specs/discord/interaction.endpoints-params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */

  /* specs/discord/interaction.endpoints-params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */

  /* specs/discord/interaction.endpoints-params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */

  /* specs/discord/interaction.endpoints-params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */

  /* specs/discord/interaction.endpoints-params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */

  /* specs/discord/interaction.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */

}
void discord_edit_followup_message_params_list_free(struct discord_edit_followup_message_params **p) {
  ntl_free((void**)p, (vfvp)discord_edit_followup_message_params_cleanup);
}

void discord_edit_followup_message_params_list_from_json(char *str, size_t len, struct discord_edit_followup_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_edit_followup_message_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_edit_followup_message_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_edit_followup_message_params_list_to_json(char *str, size_t len, struct discord_edit_followup_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_edit_followup_message_params_to_json_v);
}

