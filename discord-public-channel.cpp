#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include <orka-utils.h>

namespace discord {
namespace channel {
#if 0
void
dati_from_json(char *str, size_t len, void *p_channel)
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
     &user::dati_list_from_json, &channel->recipients,
     channel->icon,
     &orka_strtoull, &channel->owner_id,
     &orka_strtoull, &channel->application_id,
     &orka_strtoull, &channel->parent_id,
     &orka_iso8601_to_unix_ms, &channel->last_pin_timestamp,
     &message::dati_list_from_json, &channel->messages);

  DS_NOTOP_PUTS("Channel object loaded with API response");
}

void
dati_list_from_json(char *str, size_t len, void *p_channels)
{
  struct ntl_deserializer d;
  d.elem_size = sizeof(dati);
  d.init_elem = &dati_init;
  d.elem_from_buf = &dati_from_json;
  d.ntl_recipient_p = (void***)p_channels;
  orka_str_to_ntl(str, len, &d);
}

void
dati_init(void *p_channel) {
  memset(p_channel, 0, sizeof(dati));
}

dati*
dati_alloc()
{
  dati *new_channel = (dati*)malloc(sizeof(dati));
  dati_init((void*)new_channel);
  return new_channel;
}

void
dati_cleanup(void *p_channel) 
{
  DS_NOTOP_PUTS("Channel object fields cleared"); 
}

void
dati_free(dati *channel)
{
  dati_cleanup((void*)channel);
  free(channel);
}

void
dati_list_free(dati **channels) {
  ntl_free((void**)channels, &dati_cleanup);
}

void
dati_list_to_json(char * str, size_t len, void *p)
{
   //@todo to be replaced by generated code
}
#endif

void
get(client *client, const uint64_t channel_id, dati *p_channel)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id");
    return;
  }

  struct resp_handle resp_handle = {&dati_from_json_v, (void*)p_channel};

  user_agent::run(
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/channels/%llu", channel_id);
}

void
del(client *client, const uint64_t channel_id, dati *p_channel)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id");
    return;
  }

  struct resp_handle resp_handle = {
    .ok_cb = p_channel ? dati_from_json_v : NULL,
    .ok_obj = p_channel,
  };

  struct sized_buffer req_body = {"", 0};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    &req_body, //empty POSTFIELDS
    HTTP_DELETE,
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
dati_from_json(char *str, size_t len, dati *message)
{
  if (message->nonce) {
    free(message->nonce);
    message->nonce = NULL;
  }
  if (message->content) {
    free(message->content);
    message->content = NULL;
  }

  message->referenced_message = dati_alloc();

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
      &user::dati_from_json, message->author,
      &guild::member::dati_from_json, message->member,
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
      &dati_from_json, message->referenced_message);

  if(!message->referenced_message->id) {
    dati_free(message->referenced_message);
    message->referenced_message = NULL;
  }

  DS_NOTOP_PUTS("Message object loaded with API response"); 
}

#if 0
void
dati_list_from_json(char *str, size_t len, void *p_messages)
{
  struct ntl_deserializer d;
  d.elem_size = sizeof(dati);
  d.init_elem = &dati_init_v;
  d.elem_from_buf = &dati_from_json_v;
  d.ntl_recipient_p = (void***)p_messages;
  orka_str_to_ntl(str, len, &d);
}

void
dati_init(void *p_message)
{
  dati *message = (dati*)p_message;

  memset(message, 0, sizeof(dati));
  message->author = user::dati_alloc();
  message->member = guild::member::dati_alloc();
}

dati*
dati_alloc()
{
  dati *new_message = (dati*)malloc(sizeof(dati));
  dati_init((void*)new_message);
  return new_message;
}

void
dati_cleanup(void *p_message)
{
  dati *message = (dati*)p_message;

  if (message->nonce)
    free(message->nonce);
  if (message->content)
    free(message->content);
  if (message->author)
    user::dati_free(message->author);
  if (message->member)
    guild::member::dati_free(message->member);
  if (message->referenced_message)
    dati_free(message->referenced_message);

  DS_NOTOP_PUTS("Message object fields cleared"); 
}

void
dati_free(dati *message)
{
  dati_cleanup((void*)message);
  free(message);
}

void
dati_list_free(dati **messages) {
  ntl_free((void**)messages, &dati_cleanup);
}
#endif

namespace get_list {

message::dati**
run(client *client, const uint64_t channel_id, params *params)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return NULL;
  }
  if (!params) {
    D_PUTS("Missing 'params'");
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
    {&dati_list_from_json_v, (void*)&new_messages};

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

//@todo this is a temporary solution
static curl_mime*
curl_mime_cb(CURL *ehandle, void *data) 
{
  struct params *params = (struct params*)data;

  curl_mime *mime = curl_mime_init(ehandle);
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

  return mime;
}

void
run(client *client, const uint64_t channel_id, params *params, dati *p_message)
{
  if (client->ws.status != websockets::status::CONNECTED) {
    D_PUTS("Can't perform action unless client has an active"
           " websockets connection");
    return;
  }
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!params) {
    D_PUTS("Missing 'params'");
    return;
  }

  struct resp_handle resp_handle = {
    .ok_cb = p_message ? dati_from_json_v : NULL,
    .ok_obj = p_message,
  };

  if (!params->file.name && !params->file.content)
  {  // content-type is application/json
    if (!params->embed) {
      if (IS_EMPTY_STRING(params->content)) {
        D_PUTS("Missing 'content'");
        return;
      }
      if (strlen(params->content) >= MAX_MESSAGE_LEN) {
        D_PRINT("Content length exceeds %d characters threshold (%zu)",
            MAX_MESSAGE_LEN, strlen(params->content));
        return;
      }
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
    /* @todo change current A[4] to A[5]
    if (params->allowed_mentions)
      A[4] = (void *)params->allowed_mentions;
    */
    if (params->message_reference)
      A[4] = (void *)params->message_reference;

    char payload[MAX_PAYLOAD_LEN];
    json_inject(payload, sizeof(payload),
        "(content):s"
        "(nonce):s"
        "(tts):b"
        "(embed):F"
        /* @todo
        "(allowed_mentions):F"
        */
        "(message_reference):F"
        "@arg_switches",
        params->content,
        params->nonce,
        &params->tts,
        &embed::dati_to_json, params->embed,
        /* @todo
        params->allowed_mentions,
        */
        &message::reference::dati_to_json, params->message_reference,
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
    ua_reqheader_add(&client->ua.common, "Content-Type", "multipart/form-data");

    ua_mime_setopt(&client->ua.common, params, &curl_mime_cb);

    user_agent::run( 
      &client->ua,
      &resp_handle,
      NULL,
      HTTP_MIMEPOST, "/channels/%llu/messages", channel_id);

    //set back to default
    ua_reqheader_add(&client->ua.common, "Content-Type", "application/json");
  }
}

} // namespace create

namespace edit {

void
run(client *client, const uint64_t channel_id, const uint64_t message_id, params *params, dati *p_message)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    D_PUTS("Missing 'message_id'");
    return;
  }
  if (!params) {
    D_PUTS("Missing 'params'");
    return;
  }

  struct resp_handle resp_handle = {
    .ok_cb = p_message ? dati_from_json_v : NULL,
    .ok_obj = p_message,
  };

  char payload[MAX_PAYLOAD_LEN];

  void *A[4] = {0}; // pointer availability array

  A[0] = params->content;
  A[1] = params->embed;
  A[2] = params->flags;
  // A[3] = params->allowed_mentions;

  json_inject(payload, sizeof(payload),
    "(content):s"
    "(embed):F"
    "(flags):d"
    //"(allowed_mentions):F"
    "@arg_switches",
    params->content,
    &embed::dati_to_json, params->embed,
    params->flags,
    A, sizeof(A));
    //&allowed_mentions::dati_to_json, params->allowed_mentions);

  struct sized_buffer req_body = { payload, strlen(payload) };

  user_agent::run(&client->ua,
    &resp_handle,
    &req_body,
    HTTP_PATCH,
    "/channels/%llu/messages/%llu", channel_id, message_id);
}

} // namespace edit

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
#if 0
void
dati_init(void *p_reference) 
{
  dati *reference = (dati*)p_reference;
  memset(reference, 0, sizeof(dati));
  reference->fail_if_not_exists = true; //doc defaults to true
}

dati*
dati_alloc()
{
  dati *new_reference = (dati*)malloc(sizeof(dati));
  dati_init((void*)new_reference);
  return new_reference;
}

void
dati_free(dati *reference) {
  free(reference);
}

void
dati_from_json(char *str, size_t len, void *p_reference)
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

int
dati_to_json(char *str, size_t len, void *p_reference)
{
  if (NULL == p_reference) return snprintf(str, len, "{}");

  dati *reference = (dati*)p_reference;

  // message_id field must be set in order to reference a message
  if (!reference->message_id) 
  {
    return snprintf(str, len, "{}");
  }

  void *A[4] = {0}; // pointer availability array
  A[0] = (void *)&reference->message_id;
  if(reference->channel_id)
    A[1] = (void *)&reference->channel_id;
  if(reference->guild_id)
    A[2] = (void *)&reference->guild_id;
  if (false == reference->fail_if_not_exists) //default is true
    A[3] = (void *)&reference->fail_if_not_exists;

  int ret = json_inject(str, len, 
                        "(message_id):F"
                        "(channel_id):F"
                        "(guild_id):F"
                        "(fail_if_not_exists):b"
                        "@arg_switches",
                        &orka_ulltostr, &reference->message_id,
                        &orka_ulltostr, &reference->channel_id,
                        &orka_ulltostr, &reference->guild_id,
                        &reference->fail_if_not_exists,
                        A, sizeof(A));

  return ret;
}
#endif

}

} // namespace message

namespace embed {
#if 0
void
dati_init(void *p_embed) 
{
  dati *embed = (dati*)p_embed;
  memset(embed, 0, sizeof(dati));
  embed->footer = footer::dati_alloc();
  embed->image = image::dati_alloc();
  embed->thumbnail = thumbnail::dati_alloc();
  embed->video = video::dati_alloc();
  embed->provider = provider::dati_alloc();
  embed->author = author::dati_alloc();
}

dati*
dati_alloc()
{
  dati *embed = (dati*)malloc(sizeof(dati));
  dati_init((void*)embed);
  return embed;
}

void
dati_cleanup(void *p_embed) 
{
  dati *embed = (dati*)p_embed;
  footer::dati_free(embed->footer);
  image::dati_free(embed->image);
  thumbnail::dati_free(embed->thumbnail);
  video::dati_free(embed->video);
  provider::dati_free(embed->provider);
  author::dati_free(embed->author);
  if (embed->fields) {
    ntl_free((void**)embed->fields, &field::dati_cleanup);
  }

  DS_NOTOP_PUTS("Embed object fields cleared"); 
}

void
dati_free(dati *embed) 
{
  dati_cleanup((void*)embed);
  free(embed);
}

void
dati_from_json(char *str, size_t len, void *p_embed)
{
  dati *embed = (dati*)p_embed;

  json_scanf(str, len,
     "[title]%s"
     "[type]%s"
     "[description]%s"
     "[url]%s"
     "[timestamp]%F"
     "[color]%d"
     "[footer]%F"
     "[image]%F"
     "[thumbnail]%F"
     "[video]%F"
     "[provider]%F"
     "[author]%F"
     "[fields]%F",
     embed->title,
     embed->type,
     embed->description,
     embed->url,
     &orka_iso8601_to_unix_ms, &embed->timestamp,
     &embed->color,
     &footer::dati_from_json, embed->footer,
     &image::dati_from_json, embed->image,
     &thumbnail::dati_from_json, embed->thumbnail,
     &video::dati_from_json, embed->video,
     &provider::dati_from_json, embed->provider,
     &author::dati_from_json, embed->author,
     &field::dati_list_from_json, &embed->fields);

  DS_NOTOP_PUTS("Embed object loaded with API response");
}

int
dati_to_json(char *str, size_t len, void *p_embed)
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
    A[4] = (void *)&embed->timestamp;
  if (embed->color)
    A[5] = (void*)&embed->color;
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
  if (embed->fields)
    A[12] = (void *)&embed->fields;

  int ret = json_inject(str, len, 
                        "(title):s"
                        "(type):s"
                        "(description):s"
                        "(url):s"
                        "(timestamp):|F|"
                        "(color):d"
                        "(footer):F"
                        "(image):F"
                        "(thumbnail):F"
                        "(video):F"
                        "(provider):F"
                        "(author):F"
                        "(fields):F"
                        "@arg_switches",
                        embed->title,
                        embed->type,
                        embed->description,
                        embed->url,
                        &orka_unix_ms_to_iso8601, &embed->timestamp,
                        &embed->color,
                        &footer::dati_to_json, embed->footer,
                        &image::dati_to_json, embed->image,
                        &thumbnail::dati_to_json, embed->thumbnail,
                        &video::dati_to_json, embed->video,
                        &provider::dati_to_json, embed->provider,
                        &author::dati_to_json, embed->author,
                        &field::dati_list_to_json, &embed->fields,
                        A, sizeof(A));
  return ret;
}
#endif

namespace thumbnail {
#if 0
void
dati_init(void *p_thumbnail) 
{
  dati *thumbnail = (dati*)p_thumbnail;
  memset(thumbnail, 0, sizeof(dati));
}

dati*
dati_alloc()
{
  dati *thumbnail = (dati*)malloc(sizeof(dati));
  dati_init((void*)thumbnail);
  return thumbnail;
}

void
dati_cleanup(void *p_thumbnail) {
  DS_NOTOP_PUTS("Thumbnail/Video/Image object fields cleared"); 
}

void
dati_free(dati *thumbnail) 
{
  dati_cleanup((void*)thumbnail);
  free(thumbnail);
}

void
dati_from_json(char *str, size_t len, void *p_thumbnail)
{
  dati *thumbnail = (dati*)p_thumbnail;

  json_scanf(str, len,
     "[url]%s"
     "[proxy_url]%s"
     "[height]%d"
     "[width]%d",
     thumbnail->url,
     thumbnail->proxy_url,
     &thumbnail->height,
     &thumbnail->width);

  DS_NOTOP_PUTS("Thumbnail/Video/Image object loaded with API response");
}

int
dati_to_json(char *str, size_t len, void *p_thumbnail)
{
  if (NULL == p_thumbnail) return snprintf(str, len, "{}");

  dati *thumbnail = (dati*)p_thumbnail;
  void *A[4] = {0}; // pointer availability array
  if (!IS_EMPTY_STRING(thumbnail->url))
    A[0] = (void *)thumbnail->url;
  if (!IS_EMPTY_STRING(thumbnail->proxy_url))
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
                        "@arg_switches",
                        thumbnail->url,
                        thumbnail->proxy_url,
                        &thumbnail->height,
                        &thumbnail->width,
                        A, sizeof(A));
  return ret;
}
#endif

} // namespace thumbnail

namespace provider {
#if 0
void
dati_init(void *p_provider) 
{
  dati *provider = (dati*)p_provider;
  memset(provider, 0, sizeof(dati));
}

dati*
dati_alloc()
{
  dati *provider = (dati*)malloc(sizeof(dati));
  dati_init((void*)provider);
  return provider;
}

void
dati_cleanup(void *p_provider) {
  DS_NOTOP_PUTS("Provider object fields cleared"); 
}

void
dati_free(dati *provider) 
{
  dati_cleanup((void*)provider);
  free(provider);
}

void
dati_from_json(char *str, size_t len, void *p_provider)
{
  dati *provider = (dati*)p_provider;

  json_scanf(str, len,
     "[name]%s"
     "[url]%s",
     provider->name,
     provider->url);

  DS_NOTOP_PUTS("Provider object loaded with API response");
}


int
dati_to_json(char *str, size_t len, void *p_provider)
{
  if (NULL == p_provider) return snprintf(str, len, "{}");

  dati *provider = (dati*)p_provider;
  void *A[2] = {0}; // pointer availability array
  if (!IS_EMPTY_STRING(provider->name))
    A[0] = (void *)provider->name;
  if (!IS_EMPTY_STRING(provider->url))
    A[1] = (void *)provider->url;

  int ret = json_inject(str, len, 
                        "(name):s"
                        "(url):s"
                        "@arg_switches",
                        provider->name,
                        provider->url,
                        A, sizeof(A));
  return ret;
}
#endif

} // namespace provider

namespace author {
#if 0
void
dati_init(void *p_author) 
{
  dati *author = (dati*)p_author;
  memset(author, 0, sizeof(dati));
}

dati*
dati_alloc()
{
  dati *author = (dati*)malloc(sizeof(dati));
  dati_init((void*)author);
  return author;
}

void
dati_cleanup(void *p_author) {
  DS_NOTOP_PUTS("Author object fields cleared"); 
}

void
dati_free(dati *author) 
{
  dati_cleanup((void*)author);
  free(author);
}

void
dati_from_json(char *str, size_t len, void *p_author)
{
  dati *author = (dati*)p_author;

  json_scanf(str, len,
     "[name]%s"
     "[url]%s"
     "[icon_url]%s"
     "[proxy_icon_url]%s",
     author->name,
     author->url,
     author->icon_url,
     author->proxy_icon_url);

  DS_NOTOP_PUTS("Author object loaded with API response");
}

int
dati_to_json(char *str, size_t len, void *p_author)
{
  if (NULL == p_author) return snprintf(str, len, "{}");

  dati *author = (dati*)p_author;
  void *A[4] = {0}; // pointer availability array
  if (!IS_EMPTY_STRING(author->name))
    A[0] = (void *)author->name;
  if (!IS_EMPTY_STRING(author->url))
    A[1] = (void *)author->url;
  if (!IS_EMPTY_STRING(author->icon_url))
    A[2] = (void *)author->icon_url;
  if (!IS_EMPTY_STRING(author->proxy_icon_url))
    A[3] = (void *)author->proxy_icon_url;

  int ret = json_inject(str, len, 
                        "(name):s"
                        "(url):s"
                        "(icon_url):s"
                        "(proxy_icon_url):s"
                        "@arg_switches",
                        author->name,
                        author->url,
                        author->icon_url,
                        author->proxy_icon_url,
                        A, sizeof(A));
  return ret;
}
#endif
} // namespace author

#if 0
namespace footer {
void
dati_init(void *p_footer) 
{
  dati *footer = (dati*)p_footer;
  memset(footer, 0, sizeof(dati));
}

dati*
dati_alloc()
{
  dati *footer = (dati*)malloc(sizeof(dati));
  dati_init((void*)footer);
  return footer;
}

void
dati_cleanup(void *p_footer) {
  DS_NOTOP_PUTS("Footer object fields cleared"); 
}

void
dati_free(dati *footer) 
{
  dati_cleanup((void*)footer);
  free(footer);
}

void
dati_from_json(char *str, size_t len, void *p_footer)
{
  dati *footer = (dati*)p_footer;

  json_scanf(str, len,
     "[text]%s"
     "[icon_url]%s"
     "[proxy_icon_url]%s",
     footer->text,
     footer->icon_url,
     footer->proxy_icon_url);

  DS_NOTOP_PUTS("Footer object loaded with API response");
}

int
dati_to_json(char *str, size_t len, void *p_footer)
{
  if (NULL == p_footer) return snprintf(str, len, "{}");

  dati *footer = (dati*)p_footer;
  void *A[3] = {0}; // pointer availability array
  if (!IS_EMPTY_STRING(footer->text))
    A[0] = (void *)footer->text;
  if (!IS_EMPTY_STRING(footer->icon_url))
    A[1] = (void *)footer->icon_url;
  if (!IS_EMPTY_STRING(footer->proxy_icon_url))
    A[2] = (void *)footer->proxy_icon_url;

  int ret = json_inject(str, len, 
                        "(text):s"
                        "(icon_url):s"
                        "(proxy_icon_url):s"
                        "@arg_switches",
                        footer->text,
                        footer->icon_url,
                        footer->proxy_icon_url,
                        A, sizeof(A));
  return ret;
}
} // namespace footer
#endif


#if 0
namespace field {
void
dati_init(void *p_field) 
{
  dati *field = (dati*)p_field;
  memset(field, 0, sizeof(dati));
}

dati*
dati_alloc()
{
  dati *field = (dati*)malloc(sizeof(dati));
  dati_init((void*)field);
  return field;
}

void
dati_cleanup(void *p_field) {
  DS_NOTOP_PUTS("Field object fields cleared"); 
}

void
dati_free(dati *field) 
{
  dati_cleanup((void*)field);
  free(field);
}

void
dati_from_json(char *str, size_t len, void *p_field)
{
  dati *field = (dati*)p_field;

  json_scanf(str, len,
     "[name]%s"
     "[value]%s"
     "[inline]%b",
     field->name,
     field->value,
     &field->Inline);

  DS_NOTOP_PUTS("Field object loaded with API response");
}

void
dati_list_from_json(char *str, size_t len, void *p_fields)
{
  struct ntl_deserializer d;
  d.elem_size = sizeof(dati);
  d.init_elem = &dati_init;
  d.elem_from_buf = &dati_from_json;
  d.ntl_recipient_p = (void***)p_fields;
  orka_str_to_ntl(str, len, &d);
}

size_t
dati_to_json(char *str, size_t len, void *p_field)
{
  if (NULL == p_field) return snprintf(str, len, "{}");

  dati *field = (dati*)p_field;
  void *A[3] = {0}; // pointer availability array
  if (!IS_EMPTY_STRING(field->name))
    A[0] = (void *)field->name;
  if (!IS_EMPTY_STRING(field->value))
    A[1] = (void *)field->value;

  A[2] = (void *)&field->Inline;

  size_t ret = json_inject(str, len,
                        "(name):s"
                        "(value):s"
                        "(inline):b"
                        "@arg_switches",
                        field->name,
                        field->value,
                        &field->Inline,
                        A, sizeof(A));
  return ret;
}

int
dati_list_to_json(char *str, size_t len, void *p_fields)
{
  dati **fields = *(dati ***)p_fields;
  return ntl_to_buf(str, len, (void**)fields, NULL, &dati_to_json);
}

} // namespace field
#endif

void
change_footer(dati *embed, char text[], char icon_url[], char proxy_icon_url[])
{
  if (IS_EMPTY_STRING(text)) {
    D_PUTS("Missing 'text'");
    return;
  }

  if (embed->footer) {
    free(embed->footer);
  }

  embed::footer::dati *new_footer = embed::footer::dati_alloc();
  strncpy(new_footer->text, text, EMBED_FOOTER_TEXT_LEN);
  if (!IS_EMPTY_STRING(icon_url))
    strncpy(new_footer->icon_url, icon_url, MAX_URL_LEN);
  if (!IS_EMPTY_STRING(proxy_icon_url))
    strncpy(new_footer->proxy_icon_url, proxy_icon_url, MAX_URL_LEN);

  embed->footer = new_footer;
}

void
change_thumbnail(dati *embed, char url[], char proxy_url[], int height, int width)
{
  if (embed->thumbnail) {
    free(embed->thumbnail);
  }

  embed::thumbnail::dati *new_thumbnail = embed::thumbnail::dati_alloc();
  if (!IS_EMPTY_STRING(url))
    strncpy(new_thumbnail->url, url, MAX_URL_LEN);
  if (!IS_EMPTY_STRING(proxy_url))
    strncpy(new_thumbnail->proxy_url, proxy_url, MAX_URL_LEN);
  if (height)
    new_thumbnail->height = height;
  if (width)
    new_thumbnail->width = width;

  embed->thumbnail = new_thumbnail;
}

void
change_image(dati *embed, char url[], char proxy_url[], int height, int width)
{
  if (embed->image) {
    free(embed->image);
  }

  embed::image::dati *new_image = embed::image::dati_alloc();
  if (!IS_EMPTY_STRING(url))
    strncpy(new_image->url, url, MAX_URL_LEN);
  if (!IS_EMPTY_STRING(proxy_url))
    strncpy(new_image->proxy_url, proxy_url, MAX_URL_LEN);
  if (height)
    new_image->height = height;
  if (width)
    new_image->width = width;

  embed->image = new_image;
}

void
change_video(dati *embed, char url[], char proxy_url[], int height, int width)
{
  if (embed->video) {
    free(embed->video);
  }

  embed::video::dati *new_video = embed::video::dati_alloc();
  if (!IS_EMPTY_STRING(url))
    strncpy(new_video->url, url, MAX_URL_LEN);
  if (!IS_EMPTY_STRING(proxy_url))
    strncpy(new_video->proxy_url, proxy_url, MAX_URL_LEN);
  if (height)
    new_video->height = height;
  if (width)
    new_video->width = width;

  embed->video = new_video;
}

void
change_provider(dati *embed, char name[], char url[])
{
  if (embed->provider) {
    free(embed->provider);
  }

  embed::provider::dati *new_provider = embed::provider::dati_alloc();
  if (!IS_EMPTY_STRING(url))
    strncpy(new_provider->url, url, MAX_URL_LEN);
  if (!IS_EMPTY_STRING(name))
    strncpy(new_provider->name, name, EMBED_AUTHOR_NAME_LEN);

  embed->provider = new_provider;
}

void
change_author(dati *embed, char name[], char url[], char icon_url[], char proxy_icon_url[])
{
  if (embed->author) {
    free(embed->author);
  }

  embed::author::dati *new_author = embed::author::dati_alloc();
  if (!IS_EMPTY_STRING(name))
    strncpy(new_author->name, name, EMBED_AUTHOR_NAME_LEN);
  if (!IS_EMPTY_STRING(url))
    strncpy(new_author->url, url, MAX_URL_LEN);
  if (!IS_EMPTY_STRING(icon_url))
    strncpy(new_author->icon_url, icon_url, MAX_URL_LEN);
  if (!IS_EMPTY_STRING(proxy_icon_url))
    strncpy(new_author->proxy_icon_url, proxy_icon_url, MAX_URL_LEN);

  embed->author = new_author;
}

void
add_field(dati *embed, char name[], char value[], bool Inline)
{
  if (IS_EMPTY_STRING(name)) {
    D_PUTS("Missing 'name'");
    return;
  }
  if (IS_EMPTY_STRING(value)) {
    D_PUTS("Missing 'value'");
    return;
  }
  if (embed->fields 
      && ntl_length((void**)embed->fields) >= EMBED_MAX_FIELDS)
  {
    D_PRINT("Reach embed fields threshold (max %d)", EMBED_MAX_FIELDS);
    return;
  }

  field::dati new_field;
  field::dati_init(&new_field);
  strncpy(new_field.name, name, EMBED_FIELD_NAME_LEN);
  strncpy(new_field.value, value, EMBED_FIELD_VALUE_LEN);
  new_field.Inline = Inline;

  embed->fields = (field::dati**)ntl_append(
                        (void**)embed->fields, 
                        sizeof(field::dati), &new_field);
}

} // namespace embed

namespace overwrite {

void
append(
  dati ***permission_overwrites, 
  uint64_t id, 
  int type, 
  uint64_t allow, uint64_t deny)
{
  if (!id) {
    D_PUTS("Missing 'id'");
    return;
  }
  if ( !(0 == type || 1 == type) ) {
    D_PUTS("'type' should be 0 (role) or 1 (member)");
    return;
  }

  overwrite::dati new_overwrite;
  new_overwrite.id = id;
  new_overwrite.type = type;
  new_overwrite.allow = allow;
  new_overwrite.deny = deny;

  *permission_overwrites = (overwrite::dati**)ntl_append(
                            (void**)*permission_overwrites, 
                            sizeof(overwrite::dati), &new_overwrite);
}

} // namespace overwrite

void
trigger_typing(client* client, uint64_t channel_id)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id");
    return;
  }

  struct sized_buffer req_body = {"", 0};

  user_agent::run( 
    &client->ua,
    NULL,
    &req_body, //empty POSTFIELDS
    HTTP_POST, 
    "/channels/%llu/typing", channel_id);
}

} // namespace channel
} // namespace discord
