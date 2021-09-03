#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"

struct msg {
  u64_snowflake_t id;
  bool matched;
};

ORCAcode
discord_delete_messages_by_author_id(
  struct discord *client, 
  u64_snowflake_t channel_id, 
  u64_snowflake_t author_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id");
    return ORCA_MISSING_PARAMETER;
  }
  if (!author_id) {
    log_error("Missing 'author_id");
    return ORCA_MISSING_PARAMETER;
  }

  ORCAcode code;
  struct discord_get_channel_messages_params params = { .limit = 100 };

  NTL_T(struct discord_message) messages=NULL;
  code = discord_get_channel_messages(client, channel_id, &params, &messages);
  if (ORCA_OK != code) {
    log_error("Couldn't fetch channel messages");
    return code;
  }

  u64_unix_ms_t now = cee_timestamp_ms();

  NTL_T(u64_snowflake_t) list = NULL;
  int count=0;
  for (int i=0; messages[i]; ++i) {
    if (now > messages[i]->timestamp && now - messages[i]->timestamp > 1209600000)
    {
      break;
    }
    if (!author_id || author_id == messages[i]->author->id)
      ++count;
  }
  if (0 == count) {
    log_trace("Couldn't fetch messages from author");
    return ORCA_OK;
  }

  list = (NTL_T(u64_snowflake_t))ntl_calloc(count, sizeof(u64_snowflake_t));
  for (int i=0, j=0; messages[i] && j < count; ++i) {
    if (!author_id || author_id == messages[i]->author->id) {
      *list[j] = messages[i]->id;
      ++j;
    }
  }
  ntl_free((ntl_t)messages, discord_message_cleanup_v);

  if (count == 1)
    code = discord_delete_message(client, channel_id, *list[0]);
  else
    code = discord_bulk_delete_messages(client, channel_id, list);
  return code;
}

void
discord_embed_set_footer(
  struct discord_embed *embed, 
  char text[], 
  char icon_url[], 
  char proxy_icon_url[])
{
  if (IS_EMPTY_STRING(text)) {
    log_error("Missing 'text'");
    return;
  }

  if (embed->footer)
    discord_embed_footer_cleanup(embed->footer);
  else
    embed->footer = malloc(sizeof *embed->footer);
  discord_embed_footer_init(embed->footer);

  strncpy(embed->footer->text, text, DISCORD_EMBED_FOOTER_TEXT_LEN);
  if (icon_url)
    asprintf(&embed->footer->icon_url, "%s", icon_url);
  if (proxy_icon_url)
    asprintf(&embed->footer->proxy_icon_url, "%s", proxy_icon_url);
}


void 
discord_embed_set_title(struct discord_embed *embed, char format[], ...)
{
  va_list args;
  va_start(args, format);
  vsnprintf(embed->title, sizeof(embed->title), format, args);
  va_end(args);
}

void
discord_embed_set_thumbnail(
  struct discord_embed *embed, 
  char url[], 
  char proxy_url[], 
  int height, 
  int width)
{
  if (embed->thumbnail)
    discord_embed_thumbnail_cleanup(embed->thumbnail);
  else
    embed->thumbnail = malloc(sizeof *embed->thumbnail);
  discord_embed_thumbnail_init(embed->thumbnail);

  if (url)
    asprintf(&embed->thumbnail->url, "%s", url);
  if (proxy_url)
    asprintf(&embed->thumbnail->proxy_url, "%s", proxy_url);
  if (height)
    embed->thumbnail->height = height;
  if (width)
    embed->thumbnail->width = width;
}

void
discord_embed_set_image(
  struct discord_embed *embed, 
  char url[], 
  char proxy_url[], 
  int height, 
  int width)
{
  if (embed->image)
    discord_embed_image_cleanup(embed->image);
  else
    embed->image = malloc(sizeof *embed->image);
  discord_embed_image_init(embed->image);

  if (url)
    asprintf(&embed->image->url, "%s", url);
  if (proxy_url)
    asprintf(&embed->image->proxy_url, "%s", proxy_url);
  if (height)
    embed->image->height = height;
  if (width)
    embed->image->width = width;
}

void
discord_embed_set_video(
  struct discord_embed *embed, 
  char url[], 
  char proxy_url[], 
  int height, 
  int width)
{
  if (embed->video)
    discord_embed_video_cleanup(embed->video);
  else
    embed->video = malloc(sizeof *embed->video);
  discord_embed_video_init(embed->video);

  if (url)
    asprintf(&embed->video->url, "%s", url);
  if (proxy_url)
    asprintf(&embed->video->proxy_url, "%s", proxy_url);
  if (height)
    embed->video->height = height;
  if (width)
    embed->video->width = width;
}

void
discord_embed_set_provider(struct discord_embed *embed, char name[], char url[])
{
  if (embed->provider)
    discord_embed_provider_cleanup(embed->provider);
  else
    embed->provider = malloc(sizeof *embed->provider);
  discord_embed_provider_init(embed->provider);

  if (url)
    asprintf(&embed->provider->url, "%s", url);
  if (!IS_EMPTY_STRING(name))
    strncpy(embed->provider->name, name, DISCORD_EMBED_AUTHOR_NAME_LEN);
}

void
discord_embed_set_author(
  struct discord_embed *embed, 
  char name[], 
  char url[], 
  char icon_url[], 
  char proxy_icon_url[])
{
  if (embed->author)
    discord_embed_author_cleanup(embed->author);
  else
    embed->author = malloc(sizeof *embed->author);
  discord_embed_author_init(embed->author);

  if (!IS_EMPTY_STRING(name))
    strncpy(embed->author->name, name, DISCORD_EMBED_AUTHOR_NAME_LEN);

  if (url)
    asprintf(&embed->author->url, "%s", url);
  if (icon_url)
    asprintf(&embed->author->icon_url, "%s", icon_url);
  if (proxy_icon_url)
    asprintf(&embed->author->proxy_icon_url, "%s", proxy_icon_url);
}

void
discord_embed_add_field(struct discord_embed *embed, char name[], char value[], bool Inline)
{
  if (ntl_length((ntl_t)embed->fields) >= DISCORD_EMBED_MAX_FIELDS) {
    log_error("Reach embed fields threshold (max %d)", DISCORD_EMBED_MAX_FIELDS);
    return;
  }
  if (IS_EMPTY_STRING(name)) {
    log_error("Missing 'name'");
    return;
  }
  if (IS_EMPTY_STRING(value)) {
    log_error("Missing 'value'");
    return;
  }

  struct discord_embed_field field = { .Inline = Inline };

  size_t ret;
  if (!(ret = cee_str_bounds_check(name, sizeof(field.name)))) {
    log_warn("'name' exceeds %d characters, truncation will occur", sizeof(field.name));
    snprintf(field.name, sizeof(field.name), "%.*s(...)", \
        (int)(sizeof(field.name)-6), name);
  }
  else {
    snprintf(field.name, sizeof(field.name), "%s", name);
  }

  if (!(ret = cee_str_bounds_check(value, sizeof(field.value)))) {
    log_warn("'value' exceeds %d characters, truncation will occur", sizeof(field.value));
    snprintf(field.value, sizeof(field.value), "%.*s(...)", \
        (int)(sizeof(field.value)-6), value);
  }
  else {
    snprintf(field.value, sizeof(field.value), "%s", value);
  }

  ntl_append2((ntl_t*)&embed->fields, sizeof(struct discord_embed_field), &field);
}

void
discord_overwrite_append(
  NTL_T(struct discord_channel_overwrite) *permission_overwrites, 
  u64_snowflake_t id, 
  int type, 
  enum discord_permissions_bitwise_flags allow, 
  enum discord_permissions_bitwise_flags deny)
{
  if (!id) {
    log_error("Missing 'id'");
    return;
  }
  if ( !(0 == type || 1 == type) ) {
    log_error("'type' should be 0 (role) or 1 (member)");
    return;
  }

  struct discord_channel_overwrite new_overwrite = {
    .id = id,
    .type = type,
    .allow = allow,
    .deny = deny
  };
  ntl_append2((ntl_t*)permission_overwrites, sizeof(struct discord_channel_overwrite), &new_overwrite);
}

//@todo create some manner of copying a struct, including its pointer fields
ORCAcode
discord_get_channel_at_pos(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  const enum discord_channel_types type,
  const size_t position,
  struct discord_channel *p_channel)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_channel) {
    log_error("Missing 'p_channel'");
    return ORCA_MISSING_PARAMETER;
  }

  NTL_T(struct discord_channel) channels = NULL;
  ORCAcode code;
  code = discord_get_guild_channels(client, guild_id, &channels);
  if (ORCA_OK != code) {
    log_error("Couldn't fetch channels from guild");
    return code;
  }

  size_t j=0; // calculate position
  for (size_t i=0; channels[i]; ++i) {
    if (type == channels[i]->type && j++ == position) {
      memcpy(p_channel, channels[i], sizeof(struct discord_channel));
      // avoid double freeing
      memset(channels[i], 0, sizeof(struct discord_channel));
      break; /* EARLY BREAK */
    }
  }
  discord_channel_list_free(channels);
  return code; // ORCA_OK
}

ORCAcode
discord_disconnect_guild_member(
  struct discord *client,
  const u64_snowflake_t guild_id,
  const u64_snowflake_t user_id,
  struct discord_guild_member *p_member)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[DISCORD_MAX_PAYLOAD_LEN];
  size_t ret = json_inject(payload, sizeof(payload), "(channel_id):null");

  return discord_adapter_run( 
           client->adapter,
           &(struct ua_resp_handle){
             .ok_cb = p_member ? &discord_guild_member_from_json_v : NULL,
             .ok_obj = &p_member,
           },
           &(struct sized_buffer){ payload, ret },
           HTTP_PATCH, 
           "/guilds/%"PRIu64"/members/%"PRIu64, guild_id, user_id);
}
