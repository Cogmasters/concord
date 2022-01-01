/* This file is generated from discord/interaction.params.json, Please don't edit it. */
/**
 * @file specs-code/discord/interaction.params.c
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

void discord_edit_original_interaction_response_params_from_json_p(char *json, size_t len, struct discord_edit_original_interaction_response_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_edit_original_interaction_response_params_from_json(json, len, *pp);
}
void discord_edit_original_interaction_response_params_from_json(char *json, size_t len, struct discord_edit_original_interaction_response_params *p)
{
  discord_edit_original_interaction_response_params_init(p);
  json_extract(json, len, 
  /* discord/interaction.params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                "(content):?s,"
  /* discord/interaction.params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                "(embeds):F,"
  /* discord/interaction.params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                "(payload_json):?s,"
  /* discord/interaction.params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* discord/interaction.params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* discord/interaction.params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,",
  /* discord/interaction.params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                &p->content,
  /* discord/interaction.params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                discord_embed_list_from_json, &p->embeds,
  /* discord/interaction.params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                &p->payload_json,
  /* discord/interaction.params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_from_json_p, &p->allowed_mentions,
  /* discord/interaction.params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_from_json, &p->attachments,
  /* discord/interaction.params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_from_json, &p->components);
}

size_t discord_edit_original_interaction_response_params_to_json(char *json, size_t len, struct discord_edit_original_interaction_response_params *p)
{
  size_t r;
  void *arg_switches[6]={NULL};
  /* discord/interaction.params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  if (p->content != NULL)
    arg_switches[0] = p->content;

  /* discord/interaction.params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  if (p->embeds != NULL)
    arg_switches[1] = p->embeds;

  /* discord/interaction.params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
  if (p->payload_json != NULL)
    arg_switches[2] = p->payload_json;

  /* discord/interaction.params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (p->allowed_mentions != NULL)
    arg_switches[3] = p->allowed_mentions;

  /* discord/interaction.params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (p->attachments != NULL)
    arg_switches[4] = p->attachments;

  /* discord/interaction.params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (p->components != NULL)
    arg_switches[5] = p->components;

  r=json_inject(json, len, 
  /* discord/interaction.params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                "(content):s,"
  /* discord/interaction.params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                "(embeds):F,"
  /* discord/interaction.params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                "(payload_json):s,"
  /* discord/interaction.params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* discord/interaction.params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* discord/interaction.params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,"
                "@arg_switches:b",
  /* discord/interaction.params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                p->content,
  /* discord/interaction.params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                discord_embed_list_to_json, p->embeds,
  /* discord/interaction.params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                p->payload_json,
  /* discord/interaction.params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_to_json, p->allowed_mentions,
  /* discord/interaction.params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_to_json, p->attachments,
  /* discord/interaction.params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_to_json, p->components,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_edit_original_interaction_response_params_cleanup_v(void *p) {
  discord_edit_original_interaction_response_params_cleanup((struct discord_edit_original_interaction_response_params *)p);
}

void discord_edit_original_interaction_response_params_init_v(void *p) {
  discord_edit_original_interaction_response_params_init((struct discord_edit_original_interaction_response_params *)p);
}

void discord_edit_original_interaction_response_params_from_json_v(char *json, size_t len, void *p) {
 discord_edit_original_interaction_response_params_from_json(json, len, (struct discord_edit_original_interaction_response_params*)p);
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
  /* discord/interaction.params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  if (d->content)
    free(d->content);
  /* discord/interaction.params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  if (d->embeds)
    discord_embed_list_free(d->embeds);
  /* discord/interaction.params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
  if (d->payload_json)
    free(d->payload_json);
  /* discord/interaction.params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (d->allowed_mentions) {
    discord_allowed_mentions_cleanup(d->allowed_mentions);
    free(d->allowed_mentions);
  }
  /* discord/interaction.params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (d->attachments)
    discord_attachment_list_free(d->attachments);
  /* discord/interaction.params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (d->components)
    discord_component_list_free(d->components);
}

void discord_edit_original_interaction_response_params_init(struct discord_edit_original_interaction_response_params *p) {
  memset(p, 0, sizeof(struct discord_edit_original_interaction_response_params));
  /* discord/interaction.params.json:12:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */

  /* discord/interaction.params.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */

  /* discord/interaction.params.json:14:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */

  /* discord/interaction.params.json:15:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */

  /* discord/interaction.params.json:16:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */

  /* discord/interaction.params.json:17:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */

}
void discord_edit_original_interaction_response_params_list_free(struct discord_edit_original_interaction_response_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_edit_original_interaction_response_params_cleanup);
}

void discord_edit_original_interaction_response_params_list_from_json(char *str, size_t len, struct discord_edit_original_interaction_response_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_edit_original_interaction_response_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_edit_original_interaction_response_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_edit_original_interaction_response_params_list_to_json(char *str, size_t len, struct discord_edit_original_interaction_response_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_edit_original_interaction_response_params_to_json);
}


void discord_create_followup_message_params_from_json_p(char *json, size_t len, struct discord_create_followup_message_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_create_followup_message_params_from_json(json, len, *pp);
}
void discord_create_followup_message_params_from_json(char *json, size_t len, struct discord_create_followup_message_params *p)
{
  discord_create_followup_message_params_init(p);
  json_extract(json, len, 
  /* discord/interaction.params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
                "(content):?s,"
  /* discord/interaction.params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
                "(username):?s,"
  /* discord/interaction.params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
                "(avatar_url):?s,"
  /* discord/interaction.params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                "(tts):b,"
  /* discord/interaction.params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* discord/interaction.params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
                "(embeds):F,"
  /* discord/interaction.params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
                "(payload_json):?s,"
  /* discord/interaction.params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
                "(allowed_mentions):F,"
  /* discord/interaction.params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
                "(components):F,"
  /* discord/interaction.params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
                "(flags):d,",
  /* discord/interaction.params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
                &p->content,
  /* discord/interaction.params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
                &p->username,
  /* discord/interaction.params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
                &p->avatar_url,
  /* discord/interaction.params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                &p->tts,
  /* discord/interaction.params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_from_json, &p->attachments,
  /* discord/interaction.params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
                discord_embed_from_json_p, &p->embeds,
  /* discord/interaction.params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
                &p->payload_json,
  /* discord/interaction.params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
                discord_allowed_mentions_from_json_p, &p->allowed_mentions,
  /* discord/interaction.params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
                discord_component_list_from_json, &p->components,
  /* discord/interaction.params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
                &p->flags);
}

size_t discord_create_followup_message_params_to_json(char *json, size_t len, struct discord_create_followup_message_params *p)
{
  size_t r;
  void *arg_switches[12]={NULL};
  /* discord/interaction.params.json:27:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)", "default_value":true }' */
  arg_switches[0] = &p->wait;

  /* discord/interaction.params.json:28:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */
  if (p->thread_id != 0)
    arg_switches[1] = &p->thread_id;

  /* discord/interaction.params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
  if (p->content != NULL)
    arg_switches[2] = p->content;

  /* discord/interaction.params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
  if (p->username != NULL)
    arg_switches[3] = p->username;

  /* discord/interaction.params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
  if (p->avatar_url != NULL)
    arg_switches[4] = p->avatar_url;

  /* discord/interaction.params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  if (p->tts != false)
    arg_switches[5] = &p->tts;

  /* discord/interaction.params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (p->attachments != NULL)
    arg_switches[6] = p->attachments;

  /* discord/interaction.params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
  if (p->embeds != NULL)
    arg_switches[7] = p->embeds;

  /* discord/interaction.params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
  if (p->payload_json != NULL)
    arg_switches[8] = p->payload_json;

  /* discord/interaction.params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
  if (p->allowed_mentions != NULL)
    arg_switches[9] = p->allowed_mentions;

  /* discord/interaction.params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
  if (p->components != NULL)
    arg_switches[10] = p->components;

  /* discord/interaction.params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
  if (p->flags != 0)
    arg_switches[11] = &p->flags;

  r=json_inject(json, len, 
  /* discord/interaction.params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
                "(content):s,"
  /* discord/interaction.params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
                "(username):s,"
  /* discord/interaction.params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
                "(avatar_url):s,"
  /* discord/interaction.params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                "(tts):b,"
  /* discord/interaction.params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* discord/interaction.params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
                "(embeds):F,"
  /* discord/interaction.params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
                "(payload_json):s,"
  /* discord/interaction.params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
                "(allowed_mentions):F,"
  /* discord/interaction.params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
                "(components):F,"
  /* discord/interaction.params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
                "(flags):d,"
                "@arg_switches:b",
  /* discord/interaction.params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
                p->content,
  /* discord/interaction.params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
                p->username,
  /* discord/interaction.params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
                p->avatar_url,
  /* discord/interaction.params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                &p->tts,
  /* discord/interaction.params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_to_json, p->attachments,
  /* discord/interaction.params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
                discord_embed_to_json, p->embeds,
  /* discord/interaction.params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
                p->payload_json,
  /* discord/interaction.params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
                discord_allowed_mentions_to_json, p->allowed_mentions,
  /* discord/interaction.params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
                discord_component_list_to_json, p->components,
  /* discord/interaction.params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
                &p->flags,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_create_followup_message_params_cleanup_v(void *p) {
  discord_create_followup_message_params_cleanup((struct discord_create_followup_message_params *)p);
}

void discord_create_followup_message_params_init_v(void *p) {
  discord_create_followup_message_params_init((struct discord_create_followup_message_params *)p);
}

void discord_create_followup_message_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_followup_message_params_from_json(json, len, (struct discord_create_followup_message_params*)p);
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
  /* discord/interaction.params.json:27:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)", "default_value":true }' */
  (void)d->wait;
  /* discord/interaction.params.json:28:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */
  (void)d->thread_id;
  /* discord/interaction.params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
  if (d->content)
    free(d->content);
  /* discord/interaction.params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
  if (d->username)
    free(d->username);
  /* discord/interaction.params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
  if (d->avatar_url)
    free(d->avatar_url);
  /* discord/interaction.params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  (void)d->tts;
  /* discord/interaction.params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (d->attachments)
    discord_attachment_list_free(d->attachments);
  /* discord/interaction.params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
  if (d->embeds) {
    discord_embed_cleanup(d->embeds);
    free(d->embeds);
  }
  /* discord/interaction.params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */
  if (d->payload_json)
    free(d->payload_json);
  /* discord/interaction.params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
  if (d->allowed_mentions) {
    discord_allowed_mentions_cleanup(d->allowed_mentions);
    free(d->allowed_mentions);
  }
  /* discord/interaction.params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
  if (d->components)
    discord_component_list_free(d->components);
  /* discord/interaction.params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */
  (void)d->flags;
}

void discord_create_followup_message_params_init(struct discord_create_followup_message_params *p) {
  memset(p, 0, sizeof(struct discord_create_followup_message_params));
  /* discord/interaction.params.json:27:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)", "default_value":true }' */

  /* discord/interaction.params.json:28:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */

  /* discord/interaction.params.json:29:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */

  /* discord/interaction.params.json:30:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */

  /* discord/interaction.params.json:31:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */

  /* discord/interaction.params.json:32:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */

  /* discord/interaction.params.json:33:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */

  /* discord/interaction.params.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */

  /* discord/interaction.params.json:35:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params", "inject_if_not": null }' */

  /* discord/interaction.params.json:36:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */

  /* discord/interaction.params.json:37:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */

  /* discord/interaction.params.json:38:20
     '{ "name": "flags", "type":{ "base":"int" }, "comment":"can be set to 64 to send a ephemeral message", "inject_if_not": 0 }' */

}
void discord_create_followup_message_params_list_free(struct discord_create_followup_message_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_create_followup_message_params_cleanup);
}

void discord_create_followup_message_params_list_from_json(char *str, size_t len, struct discord_create_followup_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_followup_message_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_create_followup_message_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_followup_message_params_list_to_json(char *str, size_t len, struct discord_create_followup_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_create_followup_message_params_to_json);
}


void discord_edit_followup_message_params_from_json_p(char *json, size_t len, struct discord_edit_followup_message_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_edit_followup_message_params_from_json(json, len, *pp);
}
void discord_edit_followup_message_params_from_json(char *json, size_t len, struct discord_edit_followup_message_params *p)
{
  discord_edit_followup_message_params_init(p);
  json_extract(json, len, 
  /* discord/interaction.params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                "(content):?s,"
  /* discord/interaction.params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                "(embeds):F,"
  /* discord/interaction.params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                "(payload_json):?s,"
  /* discord/interaction.params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* discord/interaction.params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* discord/interaction.params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,",
  /* discord/interaction.params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                &p->content,
  /* discord/interaction.params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                discord_embed_list_from_json, &p->embeds,
  /* discord/interaction.params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                &p->payload_json,
  /* discord/interaction.params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_from_json_p, &p->allowed_mentions,
  /* discord/interaction.params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_from_json, &p->attachments,
  /* discord/interaction.params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_from_json, &p->components);
}

size_t discord_edit_followup_message_params_to_json(char *json, size_t len, struct discord_edit_followup_message_params *p)
{
  size_t r;
  void *arg_switches[6]={NULL};
  /* discord/interaction.params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  if (p->content != NULL)
    arg_switches[0] = p->content;

  /* discord/interaction.params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  if (p->embeds != NULL)
    arg_switches[1] = p->embeds;

  /* discord/interaction.params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
  if (p->payload_json != NULL)
    arg_switches[2] = p->payload_json;

  /* discord/interaction.params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (p->allowed_mentions != NULL)
    arg_switches[3] = p->allowed_mentions;

  /* discord/interaction.params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (p->attachments != NULL)
    arg_switches[4] = p->attachments;

  /* discord/interaction.params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (p->components != NULL)
    arg_switches[5] = p->components;

  r=json_inject(json, len, 
  /* discord/interaction.params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                "(content):s,"
  /* discord/interaction.params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                "(embeds):F,"
  /* discord/interaction.params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                "(payload_json):s,"
  /* discord/interaction.params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* discord/interaction.params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* discord/interaction.params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,"
                "@arg_switches:b",
  /* discord/interaction.params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                p->content,
  /* discord/interaction.params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                discord_embed_list_to_json, p->embeds,
  /* discord/interaction.params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
                p->payload_json,
  /* discord/interaction.params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_to_json, p->allowed_mentions,
  /* discord/interaction.params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_to_json, p->attachments,
  /* discord/interaction.params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_to_json, p->components,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_edit_followup_message_params_cleanup_v(void *p) {
  discord_edit_followup_message_params_cleanup((struct discord_edit_followup_message_params *)p);
}

void discord_edit_followup_message_params_init_v(void *p) {
  discord_edit_followup_message_params_init((struct discord_edit_followup_message_params *)p);
}

void discord_edit_followup_message_params_from_json_v(char *json, size_t len, void *p) {
 discord_edit_followup_message_params_from_json(json, len, (struct discord_edit_followup_message_params*)p);
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
  /* discord/interaction.params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  if (d->content)
    free(d->content);
  /* discord/interaction.params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  if (d->embeds)
    discord_embed_list_free(d->embeds);
  /* discord/interaction.params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */
  if (d->payload_json)
    free(d->payload_json);
  /* discord/interaction.params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (d->allowed_mentions) {
    discord_allowed_mentions_cleanup(d->allowed_mentions);
    free(d->allowed_mentions);
  }
  /* discord/interaction.params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (d->attachments)
    discord_attachment_list_free(d->attachments);
  /* discord/interaction.params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (d->components)
    discord_component_list_free(d->components);
}

void discord_edit_followup_message_params_init(struct discord_edit_followup_message_params *p) {
  memset(p, 0, sizeof(struct discord_edit_followup_message_params));
  /* discord/interaction.params.json:47:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */

  /* discord/interaction.params.json:48:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */

  /* discord/interaction.params.json:49:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON encoded body of non-file params (multipart/form-data only)", "inject_if_not":null }' */

  /* discord/interaction.params.json:50:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */

  /* discord/interaction.params.json:51:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */

  /* discord/interaction.params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */

}
void discord_edit_followup_message_params_list_free(struct discord_edit_followup_message_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_edit_followup_message_params_cleanup);
}

void discord_edit_followup_message_params_list_from_json(char *str, size_t len, struct discord_edit_followup_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_edit_followup_message_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_edit_followup_message_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_edit_followup_message_params_list_to_json(char *str, size_t len, struct discord_edit_followup_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_edit_followup_message_params_to_json);
}

