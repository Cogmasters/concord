#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cog-utils.h"

struct msg {
    u64_snowflake_t id;
    bool matched;
};

CCORDcode
discord_delete_messages_by_author_id(struct discord *client,
                                     u64_snowflake_t channel_id,
                                     u64_snowflake_t author_id)
{
    struct discord_get_channel_messages_params params = { 0 };
    struct discord_message **messages = NULL;
    CCORDcode code;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, author_id != 0, CCORD_BAD_PARAMETER, "");

    params.limit = 100;
    code =
        discord_get_channel_messages(client, channel_id, &params, &messages);

    if (code != CCORD_OK) {
        logconf_error(&client->conf, "Couldn't fetch channel messages");
    }
    else {
        u64_unix_ms_t now = discord_timestamp(client);
        u64_snowflake_t **list = NULL;
        int count = 0;
        int i, j;

        for (i = 0; messages[i]; ++i) {
            if (now > messages[i]->timestamp
                && now - messages[i]->timestamp > 1209600000) {
                break;
            }
            if (!author_id || author_id == messages[i]->author->id) ++count;
        }

        if (0 == count) {
            logconf_trace(&client->conf,
                          "Couldn't fetch messages from author");
            return CCORD_OK;
        }

        list = (u64_snowflake_t **)ntl_calloc(count, sizeof(u64_snowflake_t));
        for (i = 0, j = 0; messages[i] && j < count; ++i) {
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
    }

    return code;
}

void
discord_embed_set_footer(struct discord_embed *embed,
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

    if (text) cog_strndup(text, strlen(text), &embed->footer->text);
    if (icon_url)
        cog_strndup(icon_url, strlen(icon_url), &embed->footer->icon_url);
    if (proxy_icon_url)
        cog_strndup(proxy_icon_url, strlen(proxy_icon_url),
                    &embed->footer->proxy_icon_url);
}

void
discord_embed_set_title(struct discord_embed *embed, char format[], ...)
{
    char buf[2048];
    size_t len;
    va_list args;

    va_start(args, format);

    len = vsnprintf(buf, sizeof(buf), format, args);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");

    if (embed->title) free(embed->title);
    cog_strndup(buf, len, &embed->title);

    va_end(args);
}

void
discord_embed_set_description(struct discord_embed *embed, char format[], ...)
{
    char buf[2048];
    size_t len;
    va_list args;

    va_start(args, format);

    len = vsnprintf(buf, sizeof(buf), format, args);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");

    if (embed->description) free(embed->description);
    cog_strndup(buf, len, &embed->description);

    va_end(args);
}

void
discord_embed_set_url(struct discord_embed *embed, char format[], ...)
{
    char buf[2048];
    size_t len;
    va_list args;

    va_start(args, format);

    len = vsnprintf(buf, sizeof(buf), format, args);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");

    if (embed->url) free(embed->url);
    cog_strndup(buf, len, &embed->url);

    va_end(args);
}

void
discord_embed_set_thumbnail(struct discord_embed *embed,
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

    if (url) cog_strndup(url, strlen(url), &embed->thumbnail->url);
    if (proxy_url)
        cog_strndup(proxy_url, strlen(proxy_url),
                    &embed->thumbnail->proxy_url);
    if (height) embed->thumbnail->height = height;
    if (width) embed->thumbnail->width = width;
}

void
discord_embed_set_image(struct discord_embed *embed,
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

    if (url) cog_strndup(url, strlen(url), &embed->image->url);
    if (proxy_url)
        cog_strndup(proxy_url, strlen(proxy_url), &embed->image->proxy_url);
    if (height) embed->image->height = height;
    if (width) embed->image->width = width;
}

void
discord_embed_set_video(struct discord_embed *embed,
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

    if (url) cog_strndup(url, strlen(url), &embed->video->url);
    if (proxy_url)
        cog_strndup(proxy_url, strlen(proxy_url), &embed->video->proxy_url);
    if (height) embed->video->height = height;
    if (width) embed->video->width = width;
}

void
discord_embed_set_provider(struct discord_embed *embed,
                           char name[],
                           char url[])
{
    if (embed->provider)
        discord_embed_provider_cleanup(embed->provider);
    else
        embed->provider = malloc(sizeof *embed->provider);
    discord_embed_provider_init(embed->provider);

    if (name) cog_strndup(name, strlen(name), &embed->provider->name);
    if (url) cog_strndup(url, strlen(url), &embed->provider->url);
}

void
discord_embed_set_author(struct discord_embed *embed,
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

    if (name) cog_strndup(name, strlen(name), &embed->author->name);
    if (url) cog_strndup(url, strlen(url), &embed->author->url);
    if (icon_url)
        cog_strndup(icon_url, strlen(icon_url), &embed->author->icon_url);
    if (proxy_icon_url)
        cog_strndup(proxy_icon_url, strlen(proxy_icon_url),
                    &embed->author->proxy_icon_url);
}

void
discord_embed_add_field(struct discord_embed *embed,
                        char name[],
                        char value[],
                        bool Inline)
{
    struct discord_embed_field field = { 0 };

    field.Inline = Inline;

    if (name) cog_strndup(name, strlen(name), &field.name);
    if (value) cog_strndup(value, strlen(value), &field.value);

    ntl_append2((ntl_t *)&embed->fields, sizeof(struct discord_embed_field),
                &field);
}

void
discord_overwrite_append(struct discord_overwrite ***permission_overwrites,
                         u64_snowflake_t id,
                         int type,
                         u64_bitmask_t allow,
                         u64_bitmask_t deny)
{
    struct discord_overwrite new_overwrite = { 0 };

    new_overwrite.id = id;
    new_overwrite.type = type;
    new_overwrite.allow = allow;
    new_overwrite.deny = deny;

    ntl_append2((ntl_t *)permission_overwrites,
                sizeof(struct discord_overwrite), &new_overwrite);
}

/* @todo create some manner of copying a struct, including its pointer fields
 */
CCORDcode
discord_get_channel_at_pos(struct discord *client,
                           const u64_snowflake_t guild_id,
                           const enum discord_channel_types type,
                           const size_t position,
                           struct discord_channel *ret)
{
    struct discord_channel **channels = NULL;
    CCORDcode code;

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, ret != NULL, CCORD_BAD_PARAMETER, "");

    code = discord_get_guild_channels(client, guild_id, &channels);

    if (CCORD_OK != code) {
        logconf_error(&client->conf, "Couldn't fetch channels from guild");
        memset(ret, 0, sizeof(struct discord_channel));
    }
    else {
        struct discord_channel *channel = NULL;
        size_t i, pos; /* calculate position */

        for (i = 0, pos = 0; channels[i]; ++i) {
            if (type == channels[i]->type && pos++ == position) {
                channel = channels[i];
                break;
            }
        }

        if (channel) {
            memcpy(ret, channel, sizeof(struct discord_channel));
            memset(channel, 0, sizeof(struct discord_channel));
        }
        else {
            memset(ret, 0, sizeof(struct discord_channel));
        }

        discord_channel_list_free(channels);
    }

    return code;
}

void
discord_presence_add_activity(struct discord_presence_status *presence,
                              struct discord_activity *activity)
{
    ntl_append2((ntl_t *)&presence->activities,
                sizeof(struct discord_activity), activity);
}
