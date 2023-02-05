#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"
#include "queriec.h"

/******************************************************************************
 * Custom functions
 ******************************************************************************/

struct _discord_get_channel_at_pos {
    enum discord_channel_types type;
    int position;
    struct discord_ret_channel ret;
};

/* XXX: placeholder until channel is obtained via cache at
 *      discord_get_channel_at_pos() */
static void
_done_get_channels(struct discord *client,
                   struct discord_response *resp,
                   const struct discord_channels *chs)
{
    struct _discord_get_channel_at_pos *cxt = resp->data;
    const struct discord_channel *found_ch = NULL;

    for (int i = 0, pos = 0; i < chs->size; ++i) {
        if (cxt->type == chs->array[i].type && pos++ == cxt->position) {
            found_ch = &chs->array[i];
            break;
        }
    }

    resp->data = cxt->ret.data;
    resp->keep = cxt->ret.keep;

    if (found_ch) {
        if (cxt->ret.done) cxt->ret.done(client, resp, found_ch);
    }
    else if (cxt->ret.fail) {
        resp->code = CCORD_BAD_PARAMETER;
        cxt->ret.fail(client, resp);
    }

    if (cxt->ret.keep)
        discord_refcounter_decr(&client->refcounter, (void *)cxt->ret.keep);
    if (cxt->ret.data)
        discord_refcounter_decr(&client->refcounter, cxt->ret.data);
}

CCORDcode
discord_get_channel_at_pos(struct discord *client,
                           u64snowflake guild_id,
                           enum discord_channel_types type,
                           int position,
                           struct discord_ret_channel *ret)
{
    struct _discord_get_channel_at_pos *cxt;
    struct discord_ret_channels channels_ret = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, ret != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, ret->done != NULL, CCORD_BAD_PARAMETER, "");

    cxt = malloc(sizeof *cxt);
    *cxt = (struct _discord_get_channel_at_pos){ .type = type,
                                                 .position = position,
                                                 .ret = *ret };

    channels_ret.done = &_done_get_channels;
    channels_ret.fail = ret->fail;
    channels_ret.data = cxt;

    if (ret->keep) {
        CCORDcode code =
            discord_refcounter_incr(&client->refcounter, (void *)ret->keep);
        ASSERT_S(code == CCORD_OK,
                 "'.keep' data must be a Concord callback parameter");
    }
    if (ret->data
        && CCORD_UNAVAILABLE
               == discord_refcounter_incr(&client->refcounter, ret->data))
    {
        discord_refcounter_add_client(&client->refcounter, ret->data,
                                      ret->cleanup, false);
    }

    /* TODO: fetch channel via caching, and return if results are non-existent
     */
    return discord_get_guild_channels(client, guild_id, &channels_ret);
}

/******************************************************************************
 * REST functions
 ******************************************************************************/

CCORDcode
discord_get_channel(struct discord *client,
                    u64snowflake channel_id,
                    struct discord_ret_channel *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_channel, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/channels/%" PRIu64, channel_id);
}

CCORDcode
discord_modify_channel(struct discord *client,
                       u64snowflake channel_id,
                       struct discord_modify_channel *params,
                       struct discord_ret_channel *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_channel_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_channel, ret, params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/channels/%" PRIu64, channel_id);
}

CCORDcode
discord_delete_channel(struct discord *client,
                       u64snowflake channel_id,
                       struct discord_delete_channel *params,
                       struct discord_ret_channel *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_channel, ret,
                      params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/channels/%" PRIu64, channel_id);
}

CCORDcode
discord_get_channel_messages(struct discord *client,
                             u64snowflake channel_id,
                             struct discord_get_channel_messages *params,
                             struct discord_ret_messages *ret)
{
    struct discord_attributes attr = { 0 };
    char query[1024] = "";

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    struct queriec queriec;
    queriec_init(&queriec, sizeof(query));

    if (params) {
        int res;

        char buf[32];
        if (params->limit) {
            res = queriec_snprintf_add(&queriec, query, "limit", sizeof("limit"),
                                       buf, sizeof(buf), "%" PRIu64, params->limit);
            ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
        }
        if (params->around) {
            res = queriec_snprintf_add(&queriec, query, "around", sizeof("around"),
                                       buf, sizeof(buf), "%" PRIu64, params->around);
            ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
        }
        if (params->before) {
            res = queriec_snprintf_add(&queriec, query, "before", sizeof("before"),
                                       buf, sizeof(buf), "%" PRIu64, params->before);
            ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
        }
        if (params->after) {
            res = queriec_snprintf_add(&queriec, query, "after", sizeof("after"),
                                       buf, sizeof(buf), "%" PRIu64, params->after);
            ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
        }
    }

    DISCORD_ATTR_LIST_INIT(attr, discord_messages, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/channels/%" PRIu64 "/messages%s", channel_id,
                            query);
}

CCORDcode
discord_get_channel_message(struct discord *client,
                            u64snowflake channel_id,
                            u64snowflake message_id,
                            struct discord_ret_message *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_message, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/channels/%" PRIu64 "/messages/%" PRIu64,
                            channel_id, message_id);
}

CCORDcode
discord_create_message(struct discord *client,
                       u64snowflake channel_id,
                       struct discord_create_message *params,
                       struct discord_ret_message *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    enum http_method method;
    char buf[16384]; /**< @todo dynamic buffer */

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    if (params->attachments) {
        method = HTTP_MIMEPOST;
        DISCORD_ATTACHMENTS_IDS_INIT(params->attachments);
        attr.attachments = *params->attachments;
    }
    else {
        method = HTTP_POST;
    }

    body.size = discord_create_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_message, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, method,
                            "/channels/%" PRIu64 "/messages", channel_id);
}

CCORDcode
discord_crosspost_message(struct discord *client,
                          u64snowflake channel_id,
                          u64snowflake message_id,
                          struct discord_ret_message *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_message, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_POST,
                            "/channels/%" PRIu64 "/messages/%" PRIu64
                            "/crosspost",
                            channel_id, message_id);
}

CCORDcode
discord_create_reaction(struct discord *client,
                        u64snowflake channel_id,
                        u64snowflake message_id,
                        u64snowflake emoji_id,
                        const char emoji_name[],
                        struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    char *pct_emoji_name;
    char emoji_endpoint[256];
    CCORDcode code;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    pct_emoji_name =
        emoji_name ? curl_escape(emoji_name, (int)strlen(emoji_name)) : NULL;

    if (emoji_id)
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
                 pct_emoji_name, emoji_id);
    else
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    code = discord_rest_run(&client->rest, &attr, NULL, HTTP_PUT,
                            "/channels/%" PRIu64 "/messages/%" PRIu64
                            "/reactions/%s/@me",
                            channel_id, message_id, emoji_endpoint);

    curl_free(pct_emoji_name);

    return code;
}

CCORDcode
discord_delete_own_reaction(struct discord *client,
                            u64snowflake channel_id,
                            u64snowflake message_id,
                            u64snowflake emoji_id,
                            const char emoji_name[],
                            struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    char *pct_emoji_name;
    char emoji_endpoint[256];
    CCORDcode code;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    pct_emoji_name =
        emoji_name ? curl_escape(emoji_name, (int)strlen(emoji_name)) : NULL;

    if (emoji_id)
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
                 pct_emoji_name, emoji_id);
    else
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    code = discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/channels/%" PRIu64 "/messages/%" PRIu64
                            "/reactions/%s/@me",
                            channel_id, message_id, emoji_endpoint);

    curl_free(pct_emoji_name);

    return code;
}

CCORDcode
discord_delete_user_reaction(struct discord *client,
                             u64snowflake channel_id,
                             u64snowflake message_id,
                             u64snowflake user_id,
                             u64snowflake emoji_id,
                             const char emoji_name[],
                             struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    char *pct_emoji_name;
    char emoji_endpoint[256];
    CCORDcode code;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    pct_emoji_name =
        emoji_name ? curl_escape(emoji_name, (int)strlen(emoji_name)) : NULL;

    if (emoji_id)
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
                 pct_emoji_name, emoji_id);
    else
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    code = discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/channels/%" PRIu64 "/messages/%" PRIu64
                            "/reactions/%s/%" PRIu64,
                            channel_id, message_id, emoji_endpoint, user_id);

    curl_free(pct_emoji_name);

    return code;
}

CCORDcode
discord_get_reactions(struct discord *client,
                      u64snowflake channel_id,
                      u64snowflake message_id,
                      u64snowflake emoji_id,
                      const char emoji_name[],
                      struct discord_get_reactions *params,
                      struct discord_ret_users *ret)
{
    struct discord_attributes attr = { 0 };
    char emoji_endpoint[256];
    char query[1024] = "";
    char *pct_emoji_name;
    CCORDcode code;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    struct queriec queriec;
    queriec_init(&queriec, sizeof(query));

    if (params) {
        int res;

        char buf[32];
        if (params->after) {
            CCORD_EXPECT(client, params->after != 0, CCORD_BAD_PARAMETER, "");

            res = queriec_snprintf_add(&queriec, query, "after", sizeof("after"),
                                       buf, sizeof(buf), "%" PRIu64, params->after);
            ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
        }
        if (params->limit) {
            CCORD_EXPECT(client, params->limit > 0 && params->limit <= 100,
                         CCORD_BAD_PARAMETER, "");

            res = queriec_snprintf_add(&queriec, query, "limit", sizeof("limit"),
                                       buf, sizeof(buf), "%d", params->limit);
            ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
        }
    }

    pct_emoji_name =
        emoji_name ? curl_escape(emoji_name, (int)strlen(emoji_name)) : NULL;

    if (emoji_id)
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
                 pct_emoji_name, emoji_id);
    else
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

    DISCORD_ATTR_LIST_INIT(attr, discord_users, ret, NULL);

    code = discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/channels/%" PRIu64 "/messages/%" PRIu64
                            "/reactions/%s%s",
                            channel_id, message_id, emoji_endpoint, query);

    curl_free(pct_emoji_name);

    return code;
}

CCORDcode
discord_delete_all_reactions(struct discord *client,
                             u64snowflake channel_id,
                             u64snowflake message_id,
                             struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/channels/%" PRIu64 "/messages/%" PRIu64
                            "/reactions",
                            channel_id, message_id);
}

CCORDcode
discord_delete_all_reactions_for_emoji(struct discord *client,
                                       u64snowflake channel_id,
                                       u64snowflake message_id,
                                       u64snowflake emoji_id,
                                       const char emoji_name[],
                                       struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    char *pct_emoji_name;
    char emoji_endpoint[256];
    CCORDcode code;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    pct_emoji_name =
        emoji_name ? curl_escape(emoji_name, (int)strlen(emoji_name)) : NULL;

    if (emoji_id)
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
                 pct_emoji_name, emoji_id);
    else
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    code = discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/channels/%" PRIu64 "/messages/%" PRIu64
                            "/reactions/%s",
                            channel_id, message_id, emoji_endpoint);

    curl_free(pct_emoji_name);

    return code;
}

CCORDcode
discord_edit_message(struct discord *client,
                     u64snowflake channel_id,
                     u64snowflake message_id,
                     struct discord_edit_message *params,
                     struct discord_ret_message *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[16384]; /**< @todo dynamic buffer */

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_edit_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_message, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/channels/%" PRIu64 "/messages/%" PRIu64,
                            channel_id, message_id);
}

CCORDcode
discord_delete_message(struct discord *client,
                       u64snowflake channel_id,
                       u64snowflake message_id,
                       struct discord_delete_message *params,
                       struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/channels/%" PRIu64 "/messages/%" PRIu64,
                            channel_id, message_id);
}

/** @todo add duplicated ID verification */
CCORDcode
discord_bulk_delete_messages(struct discord *client,
                             u64snowflake channel_id,
                             struct discord_bulk_delete_messages *params,
                             struct discord_ret *ret)
{
    const u64unix_ms now = discord_timestamp(client);
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[4096] = "";

    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->messages != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client,
                 params->messages->size >= 2 && params->messages->size <= 100,
                 CCORD_BAD_PARAMETER, "");

    for (int i = 0; i < params->messages->size; ++i) {
        u64unix_ms tstamp = (params->messages->array[i] >> 22) + 1420070400000;

        CCORD_EXPECT(client, now <= tstamp || now - tstamp <= 1209600000,
                     CCORD_BAD_PARAMETER,
                     "Messages should not be older than 2 weeks.");
    }

    body.size = discord_bulk_delete_messages_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_BLANK_INIT(attr, ret, params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/channels/%" PRIu64 "/messages/bulk-delete",
                            channel_id);
}

CCORDcode
discord_edit_channel_permissions(
    struct discord *client,
    u64snowflake channel_id,
    u64snowflake overwrite_id,
    struct discord_edit_channel_permissions *params,
    struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, overwrite_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_edit_channel_permissions_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_BLANK_INIT(attr, ret, params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PUT,
                            "/channels/%" PRIu64 "/permissions/%" PRIu64,
                            channel_id, overwrite_id);
}

CCORDcode
discord_get_channel_invites(struct discord *client,
                            u64snowflake channel_id,
                            struct discord_ret_invites *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_invites, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/channels/%" PRIu64 "/invites", channel_id);
}

CCORDcode
discord_create_channel_invite(struct discord *client,
                              u64snowflake channel_id,
                              struct discord_create_channel_invite *params,
                              struct discord_ret_invite *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_create_channel_invite_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_invite, ret,
                      params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/channels/%" PRIu64 "/invites", channel_id);
}

CCORDcode
discord_delete_channel_permission(
    struct discord *client,
    u64snowflake channel_id,
    u64snowflake overwrite_id,
    struct discord_delete_channel_permission *params,
    struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, overwrite_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/channels/%" PRIu64 "/permissions/%" PRIu64,
                            channel_id, overwrite_id);
}

CCORDcode
discord_follow_news_channel(struct discord *client,
                            u64snowflake channel_id,
                            struct discord_follow_news_channel *params,
                            struct discord_ret_followed_channel *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[256]; /* should be more than enough for this */

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->webhook_channel_id != 0, CCORD_BAD_PARAMETER,
                 "");

    body.size = discord_follow_news_channel_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_channel, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/channels/%" PRIu64 "/followers", channel_id);
}

CCORDcode
discord_trigger_typing_indicator(struct discord *client,
                                 u64snowflake channel_id,
                                 struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_POST,
                            "/channels/%" PRIu64 "/typing", channel_id);
}

CCORDcode
discord_get_pinned_messages(struct discord *client,
                            u64snowflake channel_id,
                            struct discord_ret_messages *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_messages, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/channels/%" PRIu64 "/pins", channel_id);
}

CCORDcode
discord_pin_message(struct discord *client,
                    u64snowflake channel_id,
                    u64snowflake message_id,
                    struct discord_pin_message *params,
                    struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_PUT,
                            "/channels/%" PRIu64 "/pins/%" PRIu64, channel_id,
                            message_id);
}

CCORDcode
discord_unpin_message(struct discord *client,
                      u64snowflake channel_id,
                      u64snowflake message_id,
                      struct discord_unpin_message *params,
                      struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/channels/%" PRIu64 "/pins/%" PRIu64, channel_id,
                            message_id);
}

CCORDcode
discord_group_dm_add_recipient(struct discord *client,
                               u64snowflake channel_id,
                               u64snowflake user_id,
                               struct discord_group_dm_add_recipient *params,
                               struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_group_dm_add_recipient_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PUT,
                            "/channels/%" PRIu64 "/recipients/%" PRIu64,
                            channel_id, user_id);
}

CCORDcode
discord_group_dm_remove_recipient(struct discord *client,
                                  u64snowflake channel_id,
                                  u64snowflake user_id,
                                  struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/channels/%" PRIu64 "/recipients/%" PRIu64,
                            channel_id, user_id);
}

CCORDcode
discord_start_thread_with_message(
    struct discord *client,
    u64snowflake channel_id,
    u64snowflake message_id,
    struct discord_start_thread_with_message *params,
    struct discord_ret_channel *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_start_thread_with_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_channel, ret, params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/channels/%" PRIu64 "/messages/%" PRIu64
                            "/threads",
                            channel_id, message_id);
}

CCORDcode
discord_start_thread_without_message(
    struct discord *client,
    u64snowflake channel_id,
    struct discord_start_thread_without_message *params,
    struct discord_ret_channel *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_start_thread_without_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_channel, ret, params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/channels/%" PRIu64 "/threads", channel_id);
}

CCORDcode
discord_join_thread(struct discord *client,
                    u64snowflake channel_id,
                    struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_PUT,
                            "/channels/%" PRIu64 "/thread-members/@me",
                            channel_id);
}

CCORDcode
discord_add_thread_member(struct discord *client,
                          u64snowflake channel_id,
                          u64snowflake user_id,
                          struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_PUT,
                            "/channels/%" PRIu64 "/thread-members/" PRIu64,
                            channel_id, user_id);
}

CCORDcode
discord_leave_thread(struct discord *client,
                     u64snowflake channel_id,
                     struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/channels/%" PRIu64 "/thread-members/@me",
                            channel_id);
}

CCORDcode
discord_remove_thread_member(struct discord *client,
                             u64snowflake channel_id,
                             u64snowflake user_id,
                             struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/channels/%" PRIu64 "/thread-members/" PRIu64,
                            channel_id, user_id);
}

CCORDcode
discord_list_thread_members(struct discord *client,
                            u64snowflake channel_id,
                            struct discord_ret_thread_members *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_thread_members, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/channels/%" PRIu64 "/thread-members",
                            channel_id);
}

CCORDcode
discord_list_active_threads(struct discord *client,
                            u64snowflake channel_id,
                            struct discord_ret_thread_response_body *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_thread_response_body, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/channels/%" PRIu64 "/threads/active",
                            channel_id);
}

CCORDcode
discord_list_public_archived_threads(
    struct discord *client,
    u64snowflake channel_id,
    u64unix_ms before,
    int limit,
    struct discord_ret_thread_response_body *ret)
{
    struct discord_attributes attr = { 0 };
    char query[1024] = "";
    char buf[32];
    int res;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    struct queriec queriec;
    queriec_init(&queriec, sizeof(query));

    if (before) {
        res = queriec_snprintf_add(&queriec, query, "before", sizeof("before"),
                                   buf, sizeof(buf), "%" PRIu64, before);
        ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt"); 
    }
    if (limit) {
        res = queriec_snprintf_add(&queriec, query, "limit", sizeof("limit"),
                                   buf, sizeof(buf), "%d", limit);
        ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
    }

    DISCORD_ATTR_INIT(attr, discord_thread_response_body, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/channels/%" PRIu64
                            "/threads/archived/public%s%s",
                            channel_id, query);
}

CCORDcode
discord_list_private_archived_threads(
    struct discord *client,
    u64snowflake channel_id,
    u64unix_ms before,
    int limit,
    struct discord_ret_thread_response_body *ret)
{
    struct discord_attributes attr = { 0 };
    char query[1024] = "";
    char buf[32];
    int res;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    struct queriec queriec;
    queriec_init(&queriec, sizeof(query));

    if (before) {
        res = queriec_snprintf_add(&queriec, query, "before", sizeof("before"),
                                   buf, sizeof(buf), "%" PRIu64, before);
        ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
    }
    if (limit) {
        res = queriec_snprintf_add(&queriec, query, "limit", sizeof("limit"),
                                   buf, sizeof(buf), "%d", limit);
        ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
    }

    DISCORD_ATTR_INIT(attr, discord_thread_response_body, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/channels/%" PRIu64
                            "/threads/archived/private%s%s",
                            channel_id, query);
}

CCORDcode
discord_list_joined_private_archived_threads(
    struct discord *client,
    u64snowflake channel_id,
    u64unix_ms before,
    int limit,
    struct discord_ret_thread_response_body *ret)
{
    struct discord_attributes attr = { 0 };
    char query[1024] = "";
    char buf[32];
    int res;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    struct queriec queriec;
    queriec_init(&queriec, sizeof(query));

    if (before) {
        res = queriec_snprintf_add(&queriec, query, "before", sizeof("before"),
                                   buf, sizeof(buf), "%" PRIu64, before);
        ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
    }
    if (limit) {
        res = queriec_snprintf_add(&queriec, query, "limit", sizeof("limit"),
                                   buf, sizeof(buf), "%d", limit);
        ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
    }

    DISCORD_ATTR_INIT(attr, discord_thread_response_body, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/channels/%" PRIu64
                            "/users/@me/threads/archived/private%s%s",
                            channel_id, query);
}
