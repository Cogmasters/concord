#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include <orka-utils.h>

namespace discord {
namespace channel {
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

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
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

  user_agent::run( 
    &client->ua,
    NULL,
    NULL,
    HTTP_PUT, 
    "/channels/%llu/pins/%llu", channel_id, message_id);
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

  user_agent::run( 
    &client->ua,
    NULL,
    NULL,
    HTTP_DELETE,
    "/channels/%llu/pins/%llu", channel_id, message_id);
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

} // namespace message

namespace embed {

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

void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len,
                 "(id):F,"
                   "(type):d,"
                   "(allow):s_as_u64,"
                   "(deny):s_as_u64,"
                   "@arg_switches:b"
                   "@record_defined"
                   "@record_null",
                 orka_strtoull, &p->id,
                 &p->type,
                 &p->allow,
                 &p->deny,
                 p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                 p->__M.record_defined, sizeof(p->__M.record_defined),
                 p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len,
                "(id):|F|,"
                  "(type):d,"
                  "(allow):s_as_u64,"
                  "(deny):s_as_u64,"
                  "@arg_switches:b",
                orka_ulltostr, &p->id,
                &p->type,
                &p->allow,
                &p->deny,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

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

  user_agent::run( 
    &client->ua,
    NULL,
    NULL,
    HTTP_POST, 
    "/channels/%llu/typing", channel_id);
}

} // namespace channel
} // namespace discord
