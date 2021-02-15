#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include <orka-utils.h>

namespace discord {
namespace channel {

void
from_json(char *str, size_t len, void *p_channel)
{
  dati *channel = (dati*)p_channel;

  json_scanf(str, len,
     "[id]%F"
     "[type]%d"
     "[guild_id]%F"
     "[position]%d"
     "[name]%s"
     "[topic]%s"
     "[nfsw]%b"
     "[last_message_id]%F"
     "[bitrate]%d"
     "[user_limit]%d"
     "[rate_limit_per_user]%d"
     "[recipients]%F"
     "[icon]%s"
     "[owner_id]%F"
     "[application_id]%F"
     "[parent_id]%F"
     "[last_pin_timestamp]%F"
     "[messages]%F",
     &orka_strtoull, &channel->id,
     &channel->type,
     &orka_strtoull, &channel->guild_id,
     &channel->position,
     channel->name,
     channel->topic,
     &channel->nsfw,
     &orka_strtoull, &channel->last_message_id,
     &channel->bitrate,
     &channel->user_limit,
     &channel->rate_limit_per_user,
     &user::from_json_list, &channel->recipients,
     channel->icon,
     &orka_strtoull, &channel->owner_id,
     &orka_strtoull, &channel->application_id,
     &orka_strtoull, &channel->parent_id,
     &orka_iso8601_to_unix_ms, &channel->last_pin_timestamp,
     &message::from_json_list, &channel->messages);

  DS_NOTOP_PUTS("Channel object loaded with API response");
}

void
from_json_list(char *str, size_t len, void *p_channels)
{
  struct ntl_deserializer deserializer = {
    .elem_size = sizeof(dati),
    .init_elem = &init_dati,
    .elem_from_buf = &from_json,
    .ntl_recipient_p = (void***)p_channels
  };
  orka_str_to_ntl(str, len, &deserializer);
}

void
init_dati(void *p_channel) {
  memset(p_channel, 0, sizeof(dati));
}

dati*
alloc_dati()
{
  dati *new_channel = (dati*)malloc(sizeof(dati));
  init_dati((void*)new_channel);
  return new_channel;
}

void
cleanup_dati(void *p_channel) 
{
  DS_NOTOP_PUTS("Channel object free'd"); 
}

void
free_dati(dati *channel)
{
  cleanup_dati((void*)channel);
  free(channel);
}

void
free_list(dati **channels) {
  ntl_free((void**)channels, &cleanup_dati);
}

void
get(client *client, const uint64_t channel_id, dati *p_channel)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id");
    return;
  }

  struct resp_handle resp_handle = {&from_json, (void*)p_channel};

  user_agent::run(
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/channels/%llu", channel_id);
}

void
pin_message(client *client, const uint64_t channel_id, const uint64_t message_id)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    D_PUTS("Missing 'message_id'");
    return;
  }

  struct sized_buffer req_body = {"", 0};

  user_agent::run( 
    &client->ua,
    NULL,
    &req_body, //empty POSTFIELDS
    HTTP_PUT, 
    "channels/%llu/pins/%llu", channel_id, message_id);
}

void
unpin_message(client *client, const uint64_t channel_id, const uint64_t message_id)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    D_PUTS("Missing 'message_id'");
    return;
  }

  struct sized_buffer req_body = {"", 0};

  user_agent::run( 
    &client->ua,
    NULL,
    &req_body, //empty POSTFIELDS
    HTTP_DELETE,
    "channels/%llu/pins/%llu", channel_id, message_id);
}

namespace message {

void
from_json(char *str, size_t len, void *p_message)
{
  dati *message = (dati*)p_message;

  if (message->nonce) {
    free(message->nonce);
    message->nonce = NULL;
  }
  if (message->content) {
    free(message->content);
    message->content = NULL;
  }

  message->referenced_message = alloc_dati();

  json_scanf(str, len,
     "[id]%F"
     "[channel_id]%F"
     "[guild_id]%F"
     "[author]%F"
     "[member]%F"
     "[content]%?s"
     "[timestamp]%F"
     "[edited_timestamp]%F"
     "[tts]%b"
     "[mention_everyone]%b"
     //"[mentions]%F"
     "[nonce]%?s"
     "[pinned]%b"
     "[webhook_id]%F"
     "[type]%d"
     "[flags]%d"
     "[referenced_message]%F",
      &orka_strtoull, &message->id,
      &orka_strtoull, &message->channel_id,
      &orka_strtoull, &message->guild_id,
      &user::from_json, message->author,
      &guild::member::from_json, message->member,
      &message->content,
      &orka_iso8601_to_unix_ms, &message->timestamp,
      &orka_iso8601_to_unix_ms, &message->edited_timestamp,
      &message->tts,
      &message->mention_everyone,
      &message->nonce,
      &message->pinned,
      &orka_strtoull, &message->webhook_id,
      &message->type,
      &message->flags,
      &from_json, message->referenced_message);

  if(!message->referenced_message->id) {
    free_dati(message->referenced_message);
    message->referenced_message = NULL;
  }

  DS_NOTOP_PUTS("Message object loaded with API response"); 
}

void
from_json_list(char *str, size_t len, void *p_messages)
{
  struct ntl_deserializer deserializer = {
    .elem_size = sizeof(dati),
    .init_elem = &init_dati,
    .elem_from_buf = &from_json,
    .ntl_recipient_p = (void***)p_messages
  };
  orka_str_to_ntl(str, len, &deserializer);
}

void
init_dati(void *p_message)
{
  dati *message = (dati*)p_message;

  memset(message, 0, sizeof(dati));
  message->author = user::alloc_dati();
  message->member = guild::member::alloc_dati();
}

dati*
alloc_dati()
{
  dati *new_message = (dati*)malloc(sizeof(dati));
  init_dati((void*)new_message);
  return new_message;
}

void
cleanup_dati(void *p_message)
{
  dati *message = (dati*)p_message;

  if (message->nonce)
    free(message->nonce);
  if (message->content)
    free(message->content);
  if (message->author)
    user::free_dati(message->author);
  if (message->member)
    guild::member::free_dati(message->member);
  if (message->referenced_message)
    free_dati(message->referenced_message);

  DS_NOTOP_PUTS("Message object free'd"); 
}

void
free_dati(dati *message)
{
  cleanup_dati((void*)message);
  free(message);
}

void
free_list(dati **messages) {
  ntl_free((void**)messages, &cleanup_dati);
}

namespace get_list {

message::dati**
run(client *client, const uint64_t channel_id, params *params)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return NULL;
  }
  if (params->limit < 1 || params->limit > 100) {
    D_PUTS("'limit' value should be in an interval of (1-100)");
    return NULL;
  }

  char limit_query[64];
  snprintf(limit_query, sizeof(limit_query),
      "?limit=%d", params->limit);

  char around_query[64] = "";
  if (params->around) {
    snprintf(around_query, sizeof(around_query),
        "&around=%" PRIu64 , params->around);
  }

  char before_query[64] = "";
  if (params->before) {
    snprintf(before_query, sizeof(before_query),
        "&before=%" PRIu64 , params->before);
  }

  char after_query[64] = "";
  if (params->after) {
    snprintf(after_query, sizeof(after_query),
        "&after=%" PRIu64 , params->after);
  }

  dati **new_messages = NULL;

  struct resp_handle resp_handle = 
    {&from_json_list, (void*)&new_messages};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/channels/%llu/messages%s%s%s", 
    channel_id, limit_query, around_query, before_query, after_query);

  return new_messages;
}

} // namespace get_list

namespace create {

void
run(client *client, const uint64_t channel_id, params *params, dati *p_message)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }

  struct resp_handle resp_handle = {
    .ok_cb = p_message ? from_json : NULL,
    .ok_obj = p_message,
  };

  if (!params->file.name && !params->file.content)
  {  // content-type is application/json
    if (IS_EMPTY_STRING(params->content)) {
      D_PUTS("Missing 'content'");
      return;
    }
    if (strlen(params->content) >= MAX_MESSAGE_LEN) {
      D_PRINT("Content length exceeds %d characters threshold (%zu)",
          MAX_MESSAGE_LEN, strlen(params->content));
      return;
    }

    void *A[6] = {0}; // pointer availability array
    if (params->content)
      A[0] = (void *)params->content;
    if (params->nonce)
      A[1] = (void *)params->nonce;
    if (true == params->tts)
      A[2] = (void *)&params->tts;
    if (params->embed)
      A[3] = (void *)params->embed;
    /*
    if (params->allowed_mentions)
      A[4] = (void *)params->allowed_mentions;
    if (params->message_reference)
      A[5] = (void *)params->message_reference;
      */

    char payload[MAX_PAYLOAD_LEN];
    json_inject(payload, sizeof(payload),
        "(content):s"
        "(nonce):s"
        "(tts):b"
        "(embed):F"
        /*
        "(allowed_mentions):F" //@todo
        "(message_reference):F" //@todo
        */
        "@",
        params->content,
        params->nonce,
        &params->tts,
        &embed::to_json, params->embed,
        /*
        params->allowed_mentions,
        params->message_reference,
        */
        A, sizeof(A));

    struct sized_buffer req_body = {payload, strlen(payload)};

    user_agent::run( 
      &client->ua,
      &resp_handle,
      &req_body,
      HTTP_POST, 
      "/channels/%llu/messages", channel_id);
  }
  else 
  { // content-type is multipart/form-data
    edit_reqheader_pair(&client->ua.reqheader, // change content-type
        "Content-Type", "multipart/form-data");

    /* @todo mime functions should be integrated to http-common.c 
     *  to facilitate usage */
    curl_mime *mime = curl_mime_init(client->ua.ehandle);
    curl_mimepart *part = curl_mime_addpart(mime);

    if (params->file.content) {
      if (!params->file.name) { // set a default name
        params->file.name = "a.out";
      }
      curl_mime_data(part, params->file.content, params->file.size);
      curl_mime_filename(part, params->file.name);
      curl_mime_type(part, "application/octet-stream");
    }
    else { //params->filename exists 
      curl_mime_filedata(part, params->file.name);
    }

    curl_mime_name(part, "file");

    //@todo find better solution than passing mime as req_body field
    struct sized_buffer req_body = {(char*)mime};

    user_agent::run( 
      &client->ua,
      &resp_handle,
      &req_body,
      HTTP_MIMEPOST, 
      "/channels/%llu/messages", channel_id);

    curl_mime_free(mime);

    edit_reqheader_pair(&client->ua.reqheader, // set back to default
        "Content-Type", "application/json");
  }
}

} // namespace create

void
del(client *client, const uint64_t channel_id, const uint64_t message_id)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    D_PUTS("Missing 'message_id'");
    return;
  }

  user_agent::run(
    &client->ua,
    NULL,
    NULL,
    HTTP_DELETE,
    "/channels/%llu/messages/%llu", channel_id, message_id);
}

namespace reference {

void
init_dati(void *p_reference) 
{
  dati *reference = (dati*)p_reference;
  memset(reference, 0, sizeof(dati));
  reference->fail_if_not_exists = true; //doc defaults to true
}

dati*
alloc_dati()
{
  dati *new_reference = (dati*)malloc(sizeof(dati));
  init_dati((void*)new_reference);
  return new_reference;
}

void
free_dati(dati *reference) {
  free(reference);
}

void
from_json(char *str, size_t len, void *p_reference)
{
  dati *reference = (dati*)p_reference;

  json_scanf(str, len,
     "[message_id]%F"
     "[channel_id]%F"
     "[guild_id]%F",
      &orka_strtoull, &reference->message_id,
      &orka_strtoull, &reference->channel_id,
      &orka_strtoull, &reference->guild_id);
}

}

} // namespace message

namespace embed {

int
to_json(char *str, size_t len, void *p_embed)
{
  if (NULL == p_embed) return snprintf(str, len, "{}");

  dati *embed = (dati*)p_embed;
  void *A[13] = {0}; // pointer availability array
  if (*embed->title)
    A[0] = (void *)embed->title;
  if (*embed->type)
    A[1] = (void *)embed->type;
  if (*embed->description)
    A[2] = (void *)embed->description;
  if (*embed->url)
    A[3] = (void *)embed->url;
  if (embed->timestamp)
    A[5] = (void *)&embed->timestamp;
  if (embed->color)
    A[5] = (void *)&embed->color;
  if (embed->footer)
    A[6] = (void *)embed->footer;
  if (embed->image)
    A[7] = (void *)embed->image;
  if (embed->thumbnail)
    A[8] = (void *)embed->thumbnail;
  if (embed->video)
    A[9] = (void *)embed->video;
  if (embed->provider)
    A[10] = (void *)embed->provider;
  if (embed->author)
    A[11] = (void *)embed->author;
  if (*embed->fields)
    A[12] = (void *)embed->fields;

  int ret = json_inject(str, len, 
                        "(title):s"
                        "(type):s"
                        "(description):s"
                        "(url):s"
                        //"(timestamp):s" @todo
                        "(color):d"
                        "(footer):F"
                        "(image):F"
                        "(thumbnail):F"
                        "(video):F"
                        "(provider):F"
                        "(author):F"
                        "(fields):F"
                        "@",
                        embed->title,
                        embed->type,
                        embed->description,
                        embed->url,
                        //embed->timestamp, @todo
                        embed->color,
                        &footer::to_json, embed->footer,
                        &image::to_json, embed->image,
                        &thumbnail::to_json, embed->thumbnail,
                        &video::to_json, embed->video,
                        &provider::to_json, embed->provider,
                        &author::to_json, embed->author,
                        &field::to_json_list, &embed->fields,
                        A, sizeof(A));
  return ret;
}

namespace thumbnail {

int
to_json(char *str, size_t len, void *p_thumbnail)
{
  if (NULL == p_thumbnail) return snprintf(str, len, "{}");

  dati *thumbnail = (dati*)p_thumbnail;
  void *A[4] = {0}; // pointer availability array
  if (*thumbnail->url)
    A[0] = (void *)thumbnail->url;
  if (*thumbnail->proxy_url)
    A[1] = (void *)thumbnail->proxy_url;
  if (thumbnail->height)
    A[2] = (void *)&thumbnail->height;
  if (thumbnail->width)
    A[3] = (void *)&thumbnail->width;

  int ret = json_inject(str, len, 
                        "(url):s"
                        "(proxy_url):s"
                        "(height):d"
                        "(width):d"
                        "@",
                        thumbnail->url,
                        thumbnail->proxy_url,
                        &thumbnail->height,
                        &thumbnail->width,
                        A, sizeof(A));
  return ret;
}

} // namespace thumbnail

namespace provider {

int
to_json(char *str, size_t len, void *p_provider)
{
  if (NULL == p_provider) return snprintf(str, len, "{}");

  dati *provider = (dati*)p_provider;
  void *A[2] = {0}; // pointer availability array
  if (*provider->name)
    A[0] = (void *)provider->name;
  if (*provider->url)
    A[1] = (void *)provider->url;

  int ret = json_inject(str, len, 
                        "(name):s"
                        "(url):s"
                        "@",
                        provider->name,
                        provider->url,
                        A, sizeof(A));
  return ret;
}

} // namespace provider

namespace author {

int
to_json(char *str, size_t len, void *p_author)
{
  if (NULL == p_author) return snprintf(str, len, "{}");

  dati *author = (dati*)p_author;
  void *A[4] = {0}; // pointer availability array
  if (*author->name)
    A[0] = (void *)author->name;
  if (*author->url)
    A[1] = (void *)author->url;
  if (*author->icon_url)
    A[2] = (void *)author->icon_url;
  if (*author->proxy_icon_url)
    A[3] = (void *)author->proxy_icon_url;

  int ret = json_inject(str, len, 
                        "(name):s"
                        "(url):s"
                        "(icon_url):s"
                        "(proxy_icon_url):s"
                        "@",
                        author->name,
                        author->url,
                        author->icon_url,
                        author->proxy_icon_url,
                        A, sizeof(A));
  return ret;
}

} // namespace author

namespace footer {

int
to_json(char *str, size_t len, void *p_footer)
{
  if (NULL == p_footer) return snprintf(str, len, "{}");

  dati *footer = (dati*)p_footer;
  void *A[3] = {0}; // pointer availability array
  if (*footer->text)
    A[0] = (void *)footer->text;
  if (*footer->icon_url)
    A[1] = (void *)footer->icon_url;
  if (*footer->proxy_icon_url)
    A[2] = (void *)footer->proxy_icon_url;

  int ret = json_inject(str, len, 
                        "(text):s"
                        "(icon_url):s"
                        "(proxy_icon_url):s"
                        "@",
                        footer->text,
                        footer->icon_url,
                        footer->proxy_icon_url,
                        A, sizeof(A));
  return ret;
}

} // namespace footer

namespace field {

int
to_json(char *str, size_t len, void *p_field)
{
  if (NULL == p_field) return snprintf(str, len, "{}");

  dati *field = (dati*)p_field;
  void *A[3] = {0}; // pointer availability array
  if (*field->name)
    A[0] = (void *)field->name;
  if (*field->value)
    A[1] = (void *)field->value;

  A[2] = (void *)&field->Inline;

  int ret = json_inject(str, len, 
                        "(name):s"
                        "(value):s"
                        "(inline):b"
                        "@",
                        field->name,
                        field->value,
                        &field->Inline,
                        A, sizeof(A));
  return ret;
}

/* @todo this needs to be tested */
int
to_json_list(char *str, size_t len, void *p_field)
{
  dati **fields = *(dati ***)p_field;
  size_t size = ntl_length((void**)fields);
  if (0 == size) return snprintf(str, len, "[]");

  char fmt[256] = "["; 
  for (size_t i=0; i < size; ++i) {
    strncat(fmt, "F ", sizeof(fmt)-1);
  }
  strncat(fmt, "]", sizeof(fmt)-1);
  ERR("%s", fmt);
}

} // namespace field

} // namespace embed

} // namespace channel
} // namespace discord
