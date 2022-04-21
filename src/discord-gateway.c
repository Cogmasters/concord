#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h> /* offsetof() */
#include <ctype.h> /* isspace() */

#include "discord.h"
#include "discord-internal.h"

/* shorten event callback for maintainability purposes */
#define ON(event, ...) gw->cmds.cbs.on_##event(CLIENT(gw, gw), __VA_ARGS__)

/* return enumerator as string in case of a match */
#define CASE_RETURN_STR(code)                                                 \
    case code:                                                                \
        return #code

static const char *
opcode_print(enum discord_gateway_opcodes opcode)
{
    switch (opcode) {
        CASE_RETURN_STR(DISCORD_GATEWAY_DISPATCH);
        CASE_RETURN_STR(DISCORD_GATEWAY_HEARTBEAT);
        CASE_RETURN_STR(DISCORD_GATEWAY_IDENTIFY);
        CASE_RETURN_STR(DISCORD_GATEWAY_PRESENCE_UPDATE);
        CASE_RETURN_STR(DISCORD_GATEWAY_VOICE_STATE_UPDATE);
        CASE_RETURN_STR(DISCORD_GATEWAY_RESUME);
        CASE_RETURN_STR(DISCORD_GATEWAY_RECONNECT);
        CASE_RETURN_STR(DISCORD_GATEWAY_REQUEST_GUILD_MEMBERS);
        CASE_RETURN_STR(DISCORD_GATEWAY_INVALID_SESSION);
        CASE_RETURN_STR(DISCORD_GATEWAY_HELLO);
        CASE_RETURN_STR(DISCORD_GATEWAY_HEARTBEAT_ACK);
    default:
        return "INVALID_GATEWAY_OPCODE";
    }
}

static const char *
close_opcode_print(enum discord_gateway_close_opcodes opcode)
{
    switch (opcode) {
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS);
        CASE_RETURN_STR(DISCORD_GATEWAY_CLOSE_REASON_RECONNECT);
    default: {
        const char *str;

        str = ws_close_opcode_print((enum ws_close_reason)opcode);
        if (str) return str;

        log_warn("Unknown WebSockets close opcode (code: %d)", opcode);
    }
        return "UNKNOWN_WEBSOCKETS_CLOSE_OPCODE";
    }
}

void
discord_gateway_send_presence_update(struct discord_gateway *gw)
{
    struct ws_info info = { 0 };
    char buf[2048];
    jsonb b;

    if (!gw->session->is_ready) return;

    jsonb_init(&b);
    jsonb_object(&b, buf, sizeof(buf));
    {
        jsonb_key(&b, buf, sizeof(buf), "op", 2);
        jsonb_number(&b, buf, sizeof(buf), 3);
        jsonb_key(&b, buf, sizeof(buf), "d", 1);
        discord_presence_update_to_jsonb(&b, buf, sizeof(buf),
                                         gw->id.presence);
        jsonb_object_pop(&b, buf, sizeof(buf));
    }

    if (ws_send_text(gw->ws, &info, buf, b.pos)) {
        io_poller_curlm_enable_perform(CLIENT(gw, gw)->io_poller, gw->mhandle);
        logconf_info(
            &gw->conf,
            ANSICOLOR("SEND", ANSI_FG_BRIGHT_GREEN) " PRESENCE UPDATE (%d "
                                                    "bytes) [@@@_%zu_@@@]",
            b.pos, info.loginfo.counter + 1);
    }
    else {
        logconf_error(
            &gw->conf,
            ANSICOLOR("FAIL SEND", ANSI_FG_RED) " PRESENCE UPDATE (%d "
                                                "bytes) [@@@_%zu_@@@]",
            b.pos, info.loginfo.counter + 1);
    }
}

static void
send_resume(struct discord_gateway *gw)
{
    struct ws_info info = { 0 };
    char buf[1024];
    jsonb b;

    /* reset */
    gw->session->status ^= DISCORD_SESSION_RESUMABLE;

    jsonb_init(&b);
    jsonb_object(&b, buf, sizeof(buf));
    {
        jsonb_key(&b, buf, sizeof(buf), "op", 2);
        jsonb_number(&b, buf, sizeof(buf), 6);
        jsonb_key(&b, buf, sizeof(buf), "d", 1);
        jsonb_object(&b, buf, sizeof(buf));
        {
            jsonb_key(&b, buf, sizeof(buf), "token", 5);
            jsonb_string(&b, buf, sizeof(buf), gw->id.token,
                         strlen(gw->id.token));
            jsonb_key(&b, buf, sizeof(buf), "session_id", 10);
            jsonb_string(&b, buf, sizeof(buf), gw->session->id,
                         strlen(gw->session->id));
            jsonb_key(&b, buf, sizeof(buf), "seq", 3);
            jsonb_number(&b, buf, sizeof(buf), gw->payload.seq);
            jsonb_object_pop(&b, buf, sizeof(buf));
        }
        jsonb_object_pop(&b, buf, sizeof(buf));
    }

    if (ws_send_text(gw->ws, &info, buf, b.pos)) {
        io_poller_curlm_enable_perform(CLIENT(gw, gw)->io_poller, gw->mhandle);
        logconf_info(
            &gw->conf,
            ANSICOLOR("SEND",
                      ANSI_FG_BRIGHT_GREEN) " RESUME (%d bytes) [@@@_%zu_@@@]",
            b.pos, info.loginfo.counter + 1);
    }
    else {
        logconf_info(&gw->conf,
                     ANSICOLOR("FAIL SEND",
                               ANSI_FG_RED) " RESUME (%d bytes) [@@@_%zu_@@@]",
                     b.pos, info.loginfo.counter + 1);
    }
}

static void
send_identify(struct discord_gateway *gw)
{
    struct ws_info info = { 0 };
    char buf[1024];
    jsonb b;

    /* Ratelimit check */
    if (gw->timer->now - gw->timer->identify < 5) {
        ++gw->session->concurrent;
        VASSERT_S(gw->session->concurrent
                      < gw->session->start_limit.max_concurrency,
                  "Reach identify request threshold (%d every 5 seconds)",
                  gw->session->start_limit.max_concurrency);
    }
    else {
        gw->session->concurrent = 0;
    }

    jsonb_init(&b);
    jsonb_object(&b, buf, sizeof(buf));
    {
        jsonb_key(&b, buf, sizeof(buf), "op", 2);
        jsonb_number(&b, buf, sizeof(buf), 2);
        jsonb_key(&b, buf, sizeof(buf), "d", 1);
        discord_identify_to_jsonb(&b, buf, sizeof(buf), &gw->id);
        jsonb_object_pop(&b, buf, sizeof(buf));
    }

    if (ws_send_text(gw->ws, &info, buf, b.pos)) {
        io_poller_curlm_enable_perform(CLIENT(gw, gw)->io_poller, gw->mhandle);
        logconf_info(
            &gw->conf,
            ANSICOLOR(
                "SEND",
                ANSI_FG_BRIGHT_GREEN) " IDENTIFY (%d bytes) [@@@_%zu_@@@]",
            b.pos, info.loginfo.counter + 1);
        /* get timestamp for this identify */
        gw->timer->identify = gw->timer->now;
    }
    else {
        logconf_info(
            &gw->conf,
            ANSICOLOR("FAIL SEND",
                      ANSI_FG_RED) " IDENTIFY (%d bytes) [@@@_%zu_@@@]",
            b.pos, info.loginfo.counter + 1);
    }
}

/* send heartbeat pulse to websockets server in order
 *  to maintain connection alive */
static void
send_heartbeat(struct discord_gateway *gw)
{
    struct ws_info info = { 0 };
    char buf[64];
    jsonb b;

    jsonb_init(&b);
    jsonb_object(&b, buf, sizeof(buf));
    {
        jsonb_key(&b, buf, sizeof(buf), "op", 2);
        jsonb_number(&b, buf, sizeof(buf), 1);
        jsonb_key(&b, buf, sizeof(buf), "d", 1);
        jsonb_number(&b, buf, sizeof(buf), gw->payload.seq);
        jsonb_object_pop(&b, buf, sizeof(buf));
    }

    if (ws_send_text(gw->ws, &info, buf, b.pos)) {
        io_poller_curlm_enable_perform(CLIENT(gw, gw)->io_poller, gw->mhandle);
        logconf_info(
            &gw->conf,
            ANSICOLOR(
                "SEND",
                ANSI_FG_BRIGHT_GREEN) " HEARTBEAT (%d bytes) [@@@_%zu_@@@]",
            b.pos, info.loginfo.counter + 1);
        /* update heartbeat timestamp */
        gw->timer->hbeat = gw->timer->now;
    }
    else {
        logconf_info(
            &gw->conf,
            ANSICOLOR("FAIL SEND",
                      ANSI_FG_RED) " HEARTBEAT (%d bytes) [@@@_%zu_@@@]",
            b.pos, info.loginfo.counter + 1);
    }
}

static void
on_hello(struct discord_gateway *gw)
{
    jsmnf_pair *f;

    gw->timer->interval = 0;
    gw->timer->hbeat = gw->timer->now;

    if ((f = jsmnf_find(gw->payload._data, "heartbeat_interval", 18)))
        gw->timer->interval = strtoull(f->value.contents, NULL, 10);
    else
        abort();

    if (gw->session->status & DISCORD_SESSION_RESUMABLE)
        send_resume(gw);
    else
        send_identify(gw);
}

static enum discord_gateway_events
get_dispatch_event(char name[])
{
#define RETURN_IF_MATCH(event, str)                                           \
    if (!strcmp(#event, str)) return DISCORD_GATEWAY_EVENTS_##event

    RETURN_IF_MATCH(READY, name);
    RETURN_IF_MATCH(RESUMED, name);
    RETURN_IF_MATCH(APPLICATION_COMMAND_CREATE, name);
    RETURN_IF_MATCH(APPLICATION_COMMAND_UPDATE, name);
    RETURN_IF_MATCH(APPLICATION_COMMAND_DELETE, name);
    RETURN_IF_MATCH(CHANNEL_CREATE, name);
    RETURN_IF_MATCH(CHANNEL_UPDATE, name);
    RETURN_IF_MATCH(CHANNEL_DELETE, name);
    RETURN_IF_MATCH(CHANNEL_PINS_UPDATE, name);
    RETURN_IF_MATCH(THREAD_CREATE, name);
    RETURN_IF_MATCH(THREAD_UPDATE, name);
    RETURN_IF_MATCH(THREAD_DELETE, name);
    RETURN_IF_MATCH(THREAD_LIST_SYNC, name);
    RETURN_IF_MATCH(THREAD_MEMBER_UPDATE, name);
    RETURN_IF_MATCH(THREAD_MEMBERS_UPDATE, name);
    RETURN_IF_MATCH(GUILD_CREATE, name);
    RETURN_IF_MATCH(GUILD_UPDATE, name);
    RETURN_IF_MATCH(GUILD_DELETE, name);
    RETURN_IF_MATCH(GUILD_BAN_ADD, name);
    RETURN_IF_MATCH(GUILD_BAN_REMOVE, name);
    RETURN_IF_MATCH(GUILD_EMOJIS_UPDATE, name);
    RETURN_IF_MATCH(GUILD_STICKERS_UPDATE, name);
    RETURN_IF_MATCH(GUILD_INTEGRATIONS_UPDATE, name);
    RETURN_IF_MATCH(GUILD_MEMBER_ADD, name);
    RETURN_IF_MATCH(GUILD_MEMBER_UPDATE, name);
    RETURN_IF_MATCH(GUILD_MEMBER_REMOVE, name);
    RETURN_IF_MATCH(GUILD_MEMBERS_CHUNK, name);
    RETURN_IF_MATCH(GUILD_ROLE_CREATE, name);
    RETURN_IF_MATCH(GUILD_ROLE_UPDATE, name);
    RETURN_IF_MATCH(GUILD_ROLE_DELETE, name);
    RETURN_IF_MATCH(INTEGRATION_CREATE, name);
    RETURN_IF_MATCH(INTEGRATION_UPDATE, name);
    RETURN_IF_MATCH(INTEGRATION_DELETE, name);
    RETURN_IF_MATCH(INTERACTION_CREATE, name);
    RETURN_IF_MATCH(INVITE_CREATE, name);
    RETURN_IF_MATCH(INVITE_DELETE, name);
    RETURN_IF_MATCH(MESSAGE_CREATE, name);
    RETURN_IF_MATCH(MESSAGE_UPDATE, name);
    RETURN_IF_MATCH(MESSAGE_DELETE, name);
    RETURN_IF_MATCH(MESSAGE_DELETE_BULK, name);
    RETURN_IF_MATCH(MESSAGE_REACTION_ADD, name);
    RETURN_IF_MATCH(MESSAGE_REACTION_REMOVE, name);
    RETURN_IF_MATCH(MESSAGE_REACTION_REMOVE_ALL, name);
    RETURN_IF_MATCH(MESSAGE_REACTION_REMOVE_EMOJI, name);
    RETURN_IF_MATCH(PRESENCE_UPDATE, name);
    RETURN_IF_MATCH(STAGE_INSTANCE_CREATE, name);
    RETURN_IF_MATCH(STAGE_INSTANCE_DELETE, name);
    RETURN_IF_MATCH(STAGE_INSTANCE_UPDATE, name);
    RETURN_IF_MATCH(TYPING_START, name);
    RETURN_IF_MATCH(USER_UPDATE, name);
    RETURN_IF_MATCH(VOICE_STATE_UPDATE, name);
    RETURN_IF_MATCH(VOICE_SERVER_UPDATE, name);
    RETURN_IF_MATCH(WEBHOOKS_UPDATE, name);
    return DISCORD_GATEWAY_EVENTS_NONE;

#undef RETURN_IF_MATCH
}

static void
on_guild_create(struct discord_gateway *gw)
{
    struct discord_guild guild = { 0 };

    discord_guild_from_jsmnf(gw->payload._data, &guild);

    ON(guild_create, &guild);

    discord_guild_cleanup(&guild);
}

static void
on_guild_update(struct discord_gateway *gw)
{
    struct discord_guild guild = { 0 };

    discord_guild_from_jsmnf(gw->payload._data, &guild);

    ON(guild_update, &guild);

    discord_guild_cleanup(&guild);
}

static void
on_guild_delete(struct discord_gateway *gw)
{
    u64snowflake guild_id = 0;
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "id", 2)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);

    ON(guild_delete, guild_id);
}

static void
on_guild_role_create(struct discord_gateway *gw)
{
    struct discord_role role = { 0 };
    u64snowflake guild_id = 0;
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);
    if ((f = jsmnf_find(gw->payload._data, "role", 4)))
        discord_role_from_jsmnf(f, &role);

    ON(guild_role_create, guild_id, &role);

    discord_role_cleanup(&role);
}

static void
on_guild_role_update(struct discord_gateway *gw)
{
    struct discord_role role = { 0 };
    u64snowflake guild_id = 0;
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);
    if ((f = jsmnf_find(gw->payload._data, "role", 4)))
        discord_role_from_jsmnf(f, &role);

    ON(guild_role_update, guild_id, &role);

    discord_role_cleanup(&role);
}

static void
on_guild_role_delete(struct discord_gateway *gw)
{
    u64snowflake guild_id = 0, role_id = 0;
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);
    if ((f = jsmnf_find(gw->payload._data, "role_id", 7)))
        sscanf(f->value.contents, "%" SCNu64, &role_id);

    ON(guild_role_delete, guild_id, role_id);
}

static void
on_guild_member_add(struct discord_gateway *gw)
{
    struct discord_guild_member member = { 0 };
    u64snowflake guild_id = 0;
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);
    discord_guild_member_from_jsmnf(gw->payload._data, &member);

    ON(guild_member_add, guild_id, &member);

    discord_guild_member_cleanup(&member);
}

static void
on_guild_member_update(struct discord_gateway *gw)
{
    struct discord_guild_member member = { 0 };
    u64snowflake guild_id = 0;
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);
    discord_guild_member_from_jsmnf(gw->payload._data, &member);

    ON(guild_member_update, guild_id, &member);

    discord_guild_member_cleanup(&member);
}

static void
on_guild_member_remove(struct discord_gateway *gw)
{
    u64snowflake guild_id = 0;
    struct discord_user user = { 0 };
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);
    if ((f = jsmnf_find(gw->payload._data, "user", 4)))
        discord_user_from_jsmnf(f, &user);

    ON(guild_member_remove, guild_id, &user);

    discord_user_cleanup(&user);
}

static void
on_guild_ban_add(struct discord_gateway *gw)
{
    u64snowflake guild_id = 0;
    struct discord_user user = { 0 };
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);
    if ((f = jsmnf_find(gw->payload._data, "user", 4)))
        discord_user_from_jsmnf(f, &user);

    ON(guild_ban_add, guild_id, &user);

    discord_user_cleanup(&user);
}

static void
on_guild_ban_remove(struct discord_gateway *gw)
{
    u64snowflake guild_id = 0;
    struct discord_user user = { 0 };
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);
    if ((f = jsmnf_find(gw->payload._data, "user", 4)))
        discord_user_from_jsmnf(f, &user);

    ON(guild_ban_remove, guild_id, &user);

    discord_user_cleanup(&user);
}

static void
on_application_command_create(struct discord_gateway *gw)
{
    struct discord_application_command cmd = { 0 };

    discord_application_command_from_jsmnf(gw->payload._data, &cmd);

    ON(application_command_create, &cmd);

    discord_application_command_cleanup(&cmd);
}

static void
on_application_command_update(struct discord_gateway *gw)
{
    struct discord_application_command cmd = { 0 };

    discord_application_command_from_jsmnf(gw->payload._data, &cmd);

    ON(application_command_update, &cmd);

    discord_application_command_cleanup(&cmd);
}

static void
on_application_command_delete(struct discord_gateway *gw)
{
    struct discord_application_command cmd = { 0 };

    discord_application_command_from_jsmnf(gw->payload._data, &cmd);

    ON(application_command_delete, &cmd);

    discord_application_command_cleanup(&cmd);
}

static void
on_channel_create(struct discord_gateway *gw)
{
    struct discord_channel channel = { 0 };

    discord_channel_from_jsmnf(gw->payload._data, &channel);

    ON(channel_create, &channel);

    discord_channel_cleanup(&channel);
}

static void
on_channel_update(struct discord_gateway *gw)
{
    struct discord_channel channel = { 0 };

    discord_channel_from_jsmnf(gw->payload._data, &channel);

    ON(channel_update, &channel);

    discord_channel_cleanup(&channel);
}

static void
on_channel_delete(struct discord_gateway *gw)
{
    struct discord_channel channel = { 0 };

    discord_channel_from_jsmnf(gw->payload._data, &channel);

    ON(channel_delete, &channel);

    discord_channel_cleanup(&channel);
}

static void
on_channel_pins_update(struct discord_gateway *gw)
{
    u64snowflake guild_id = 0, channel_id = 0;
    u64unix_ms last_pin_timestamp = 0;
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);
    if ((f = jsmnf_find(gw->payload._data, "channel_id", 10)))
        sscanf(f->value.contents, "%" SCNu64, &channel_id);
    if ((f = jsmnf_find(gw->payload._data, "last_pin_timestamp", 18)))
        cog_iso8601_to_unix_ms(f->value.contents, (size_t)(f->value.length),
                               &last_pin_timestamp);

    ON(channel_pins_update, guild_id, channel_id, last_pin_timestamp);
}

static void
on_thread_create(struct discord_gateway *gw)
{
    struct discord_channel thread = { 0 };

    discord_channel_from_jsmnf(gw->payload._data, &thread);

    ON(thread_create, &thread);

    discord_channel_cleanup(&thread);
}

static void
on_thread_update(struct discord_gateway *gw)
{
    struct discord_channel thread = { 0 };

    discord_channel_from_jsmnf(gw->payload._data, &thread);

    ON(thread_update, &thread);

    discord_channel_cleanup(&thread);
}

static void
on_thread_delete(struct discord_gateway *gw)
{
    struct discord_channel thread = { 0 };

    discord_channel_from_jsmnf(gw->payload._data, &thread);

    ON(thread_delete, &thread);

    discord_channel_cleanup(&thread);
}

static void
on_interaction_create(struct discord_gateway *gw)
{
    struct discord_interaction interaction = { 0 };

    discord_interaction_from_jsmnf(gw->payload._data, &interaction);

    ON(interaction_create, &interaction);

    discord_interaction_cleanup(&interaction);
}

static void
on_message_create(struct discord_gateway *gw)
{
    struct discord_message msg = { 0 };

    discord_message_from_jsmnf(gw->payload._data, &msg);

    if (gw->cmds.pool
        && !strncmp(gw->cmds.prefix.start, msg.content, gw->cmds.prefix.size))
    {
        char *cmd_start = msg.content + gw->cmds.prefix.size;
        size_t cmd_len = strcspn(cmd_start, " \n\t\r");
        discord_ev_message cmd_cb = NULL;

        char *tmp = msg.content; /* hold original ptr */
        size_t i;

        /* match command to its callback */
        for (i = 0; i < gw->cmds.amt; ++i) {
            if (cmd_len == gw->cmds.pool[i].size
                && 0 == strncmp(gw->cmds.pool[i].start, cmd_start, cmd_len))
            {

                cmd_cb = gw->cmds.pool[i].cb;
                break;
            }
        }

        /* couldn't match command to callback, get fallback if available */
        if (!cmd_cb && gw->cmds.prefix.size) {
            cmd_len = 0; /* no command specified */
            cmd_cb = gw->cmds.fallback.cb ? gw->cmds.fallback.cb
                                          : gw->cmds.cbs.on_message_create;
        }

        if (cmd_cb) {
            /* skip blank characters after command */
            if (msg.content) {
                msg.content = cmd_start + cmd_len;
                while (*msg.content && isspace((int)msg.content[0]))
                    ++msg.content;
            }

            cmd_cb(CLIENT(gw, gw), &msg);
        }

        msg.content = tmp; /* retrieve original ptr */
    }
    else if (gw->cmds.cbs.on_message_create) {
        ON(message_create, &msg);
    }

    discord_message_cleanup(&msg);
}

static void
on_message_update(struct discord_gateway *gw)
{
    struct discord_message msg = { 0 };

    discord_message_from_jsmnf(gw->payload._data, &msg);

    ON(message_update, &msg);

    discord_message_cleanup(&msg);
}

static void
on_message_delete(struct discord_gateway *gw)
{
    u64snowflake message_id = 0, channel_id = 0, guild_id = 0;
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "id", 2)))
        sscanf(f->value.contents, "%" SCNu64, &message_id);
    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);
    if ((f = jsmnf_find(gw->payload._data, "channel_id", 10)))
        sscanf(f->value.contents, "%" SCNu64, &channel_id);

    ON(message_delete, message_id, channel_id, guild_id);
}

static void
on_message_delete_bulk(struct discord_gateway *gw)
{
    struct snowflakes ids = { 0 };
    u64snowflake channel_id = 0, guild_id = 0;
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "ids", 3)))
        snowflakes_from_jsmnf(f, &ids);
    if ((f = jsmnf_find(gw->payload._data, "channel_id", 10)))
        sscanf(f->value.contents, "%" SCNu64, &channel_id);
    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);

    ON(message_delete_bulk, &ids, channel_id, guild_id);

    snowflakes_cleanup(&ids);
}

static void
on_message_reaction_add(struct discord_gateway *gw)
{
    u64snowflake user_id = 0, message_id = 0, channel_id = 0, guild_id = 0;
    struct discord_guild_member member = { 0 };
    struct discord_emoji emoji = { 0 };
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "user_id", 7)))
        sscanf(f->value.contents, "%" SCNu64, &user_id);
    if ((f = jsmnf_find(gw->payload._data, "message_id", 10)))
        sscanf(f->value.contents, "%" SCNu64, &message_id);
    if ((f = jsmnf_find(gw->payload._data, "member", 6)))
        discord_guild_member_from_jsmnf(f, &member);
    if ((f = jsmnf_find(gw->payload._data, "emoji", 5)))
        discord_emoji_from_jsmnf(f, &emoji);
    if ((f = jsmnf_find(gw->payload._data, "channel_id", 10)))
        sscanf(f->value.contents, "%" SCNu64, &channel_id);
    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);

    ON(message_reaction_add, user_id, channel_id, message_id, guild_id,
       &member, &emoji);

    discord_guild_member_cleanup(&member);
    discord_emoji_cleanup(&emoji);
}

static void
on_message_reaction_remove(struct discord_gateway *gw)
{
    u64snowflake user_id = 0, message_id = 0, channel_id = 0, guild_id = 0;
    struct discord_emoji emoji = { 0 };
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "user_id", 7)))
        sscanf(f->value.contents, "%" SCNu64, &user_id);
    if ((f = jsmnf_find(gw->payload._data, "message_id", 10)))
        sscanf(f->value.contents, "%" SCNu64, &message_id);
    if ((f = jsmnf_find(gw->payload._data, "emoji", 5)))
        discord_emoji_from_jsmnf(f, &emoji);
    if ((f = jsmnf_find(gw->payload._data, "channel_id", 10)))
        sscanf(f->value.contents, "%" SCNu64, &channel_id);
    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);

    ON(message_reaction_remove, user_id, channel_id, message_id, guild_id,
       &emoji);

    discord_emoji_cleanup(&emoji);
}

static void
on_message_reaction_remove_all(struct discord_gateway *gw)
{
    u64snowflake channel_id = 0, message_id = 0, guild_id = 0;
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "channel_id", 10)))
        sscanf(f->value.contents, "%" SCNu64, &channel_id);
    if ((f = jsmnf_find(gw->payload._data, "message_id", 10)))
        sscanf(f->value.contents, "%" SCNu64, &message_id);
    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);

    ON(message_reaction_remove_all, channel_id, message_id, guild_id);
}

static void
on_message_reaction_remove_emoji(struct discord_gateway *gw)
{
    u64snowflake channel_id = 0, guild_id = 0, message_id = 0;
    struct discord_emoji emoji = { 0 };
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "channel_id", 10)))
        sscanf(f->value.contents, "%" SCNu64, &channel_id);
    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);
    if ((f = jsmnf_find(gw->payload._data, "message_id", 10)))
        sscanf(f->value.contents, "%" SCNu64, &message_id);
    if ((f = jsmnf_find(gw->payload._data, "emoji", 5)))
        discord_emoji_from_jsmnf(f, &emoji);

    ON(message_reaction_remove_emoji, channel_id, guild_id, message_id,
       &emoji);

    discord_emoji_cleanup(&emoji);
}

static void
on_voice_state_update(struct discord_gateway *gw)
{
    struct discord_voice_state vs = { 0 };

    discord_voice_state_from_jsmnf(gw->payload._data, &vs);

#ifdef HAS_DISCORD_VOICE
    if (vs.user_id == CLIENT(gw, gw)->self.id) {
        /* we only care about the voice_state_update of bot */
        _discord_on_voice_state_update(CLIENT(gw, gw), &vs);
    }
#endif /* HAS_DISCORD_VOICE */

    if (gw->cmds.cbs.on_voice_state_update) ON(voice_state_update, &vs);

    discord_voice_state_cleanup(&vs);
}

static void
on_voice_server_update(struct discord_gateway *gw)
{
    u64snowflake guild_id = 0;
    char token[512], endpoint[1024];
    jsmnf_pair *f;

    if ((f = jsmnf_find(gw->payload._data, "token", 5)))
        snprintf(token, sizeof(token), "%.*s", f->value.length,
                 f->value.contents);
    if ((f = jsmnf_find(gw->payload._data, "guild_id", 8)))
        sscanf(f->value.contents, "%" SCNu64, &guild_id);
    if ((f = jsmnf_find(gw->payload._data, "endpoint", 8)))
        snprintf(endpoint, sizeof(endpoint), "%.*s", f->value.length,
                 f->value.contents);

#ifdef HAS_DISCORD_VOICE
    /* this happens for everyone */
    _discord_on_voice_server_update(CLIENT(gw, gw), guild_id, token, endpoint);
#endif /* HAS_DISCORD_VOICE */

    if (gw->cmds.cbs.on_voice_server_update)
        ON(voice_server_update, token, guild_id, endpoint);
}

static void
on_ready(struct discord_gateway *gw)
{
    gw->cmds.cbs.on_ready(CLIENT(gw, gw));
}

static void
dispatch_run(void *p_cxt)
{
    struct discord_event *cxt = p_cxt;
    struct discord *client = CLIENT(cxt->gw, gw);

    logconf_info(&cxt->gw->conf,
                 "Thread " ANSICOLOR("starts", ANSI_FG_RED) " to serve %s",
                 cxt->name);

    cxt->on_event(cxt->gw);

    logconf_info(&cxt->gw->conf,
                 "Thread " ANSICOLOR("exits", ANSI_FG_RED) " from serving %s",
                 cxt->name);

    /* TODO: move to _discord_event_cleanup() */
    free(cxt->name);
    free(cxt->data.start);
    discord_cleanup(client);
    free(cxt);
}

static void
on_dispatch(struct discord_gateway *gw)
{
    struct discord *client = CLIENT(gw, gw);

    /* event-callback selector */
    void (*on_event)(struct discord_gateway *) = NULL;
    /* get dispatch event opcode */
    enum discord_gateway_events event;
    enum discord_event_scheduler mode;

    /* XXX: this should only apply for user dispatched payloads? */
#if 0
  /* Ratelimit check */
  if (gw->timer->now - gw->timer->event < 60000) {
    ++gw->session->event_count;
    ASSERT_S(gw->session->event_count < 120,
             "Reach event dispatch threshold (120 every 60 seconds)");
  }
  else {
    gw->timer->event = gw->timer->now;
    gw->session->event_count = 0;
  }
#endif

    switch (event = get_dispatch_event(gw->payload.name)) {
    case DISCORD_GATEWAY_EVENTS_READY: {
        jsmnf_pair *f;

        logconf_info(&gw->conf, "Succesfully started a Discord session!");

        if ((f = jsmnf_find(gw->payload._data, "session_id", 10)))
            snprintf(gw->session->id, sizeof(gw->session->id), "%.*s",
                     f->value.length, f->value.contents);
        ASSERT_S(*gw->session->id, "Missing session_id from READY event");

        gw->session->is_ready = true;
        gw->session->retry.attempt = 0;

        if (gw->cmds.cbs.on_ready) on_event = &on_ready;

        send_heartbeat(gw);
    } break;
    case DISCORD_GATEWAY_EVENTS_RESUMED:
        logconf_info(&gw->conf, "Succesfully resumed a Discord session!");

        gw->session->is_ready = true;
        gw->session->retry.attempt = 0;

        send_heartbeat(gw);

        break;
    case DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_CREATE:
        if (gw->cmds.cbs.on_application_command_create)
            on_event = on_application_command_create;
        break;
    case DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_UPDATE:
        if (gw->cmds.cbs.on_application_command_update)
            on_event = on_application_command_update;
        break;
    case DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_DELETE:
        if (gw->cmds.cbs.on_application_command_delete)
            on_event = on_application_command_delete;
        break;
    case DISCORD_GATEWAY_EVENTS_CHANNEL_CREATE:
        if (gw->cmds.cbs.on_channel_create) on_event = on_channel_create;
        break;
    case DISCORD_GATEWAY_EVENTS_CHANNEL_UPDATE:
        if (gw->cmds.cbs.on_channel_update) on_event = on_channel_update;
        break;
    case DISCORD_GATEWAY_EVENTS_CHANNEL_DELETE:
        if (gw->cmds.cbs.on_channel_delete) on_event = on_channel_delete;
        break;
    case DISCORD_GATEWAY_EVENTS_CHANNEL_PINS_UPDATE:
        if (gw->cmds.cbs.on_channel_pins_update)
            on_event = on_channel_pins_update;
        break;
    case DISCORD_GATEWAY_EVENTS_THREAD_CREATE:
        if (gw->cmds.cbs.on_thread_create) on_event = on_thread_create;
        break;
    case DISCORD_GATEWAY_EVENTS_THREAD_UPDATE:
        if (gw->cmds.cbs.on_thread_update) on_event = on_thread_update;
        break;
    case DISCORD_GATEWAY_EVENTS_THREAD_DELETE:
        if (gw->cmds.cbs.on_thread_delete) on_event = on_thread_delete;
        break;
    case DISCORD_GATEWAY_EVENTS_THREAD_LIST_SYNC:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_THREAD_MEMBER_UPDATE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_THREAD_MEMBERS_UPDATE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_CREATE:
        if (gw->cmds.cbs.on_guild_create) on_event = on_guild_create;
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_UPDATE:
        if (gw->cmds.cbs.on_guild_update) on_event = on_guild_update;
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_DELETE:
        if (gw->cmds.cbs.on_guild_delete) on_event = on_guild_delete;
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_BAN_ADD:
        if (gw->cmds.cbs.on_guild_ban_add) on_event = on_guild_ban_add;
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_BAN_REMOVE:
        if (gw->cmds.cbs.on_guild_ban_remove) on_event = on_guild_ban_remove;
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_EMOJIS_UPDATE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_STICKERS_UPDATE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_INTEGRATIONS_UPDATE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_ADD:
        if (gw->cmds.cbs.on_guild_member_add) on_event = on_guild_member_add;
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_UPDATE:
        if (gw->cmds.cbs.on_guild_member_update)
            on_event = on_guild_member_update;
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_REMOVE:
        if (gw->cmds.cbs.on_guild_member_remove)
            on_event = on_guild_member_remove;
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_ROLE_CREATE:
        if (gw->cmds.cbs.on_guild_role_create) on_event = on_guild_role_create;
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_ROLE_UPDATE:
        if (gw->cmds.cbs.on_guild_role_update) on_event = on_guild_role_update;
        break;
    case DISCORD_GATEWAY_EVENTS_GUILD_ROLE_DELETE:
        if (gw->cmds.cbs.on_guild_role_delete) on_event = on_guild_role_delete;
        break;
    case DISCORD_GATEWAY_EVENTS_INTEGRATION_CREATE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_INTEGRATION_UPDATE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_INTEGRATION_DELETE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_INTERACTION_CREATE:
        if (gw->cmds.cbs.on_interaction_create)
            on_event = on_interaction_create;
        break;
    case DISCORD_GATEWAY_EVENTS_INVITE_CREATE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_INVITE_DELETE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE:
        if (gw->cmds.pool || gw->cmds.cbs.on_message_create)
            on_event = &on_message_create;
        break;
    case DISCORD_GATEWAY_EVENTS_MESSAGE_UPDATE:
        if (gw->cmds.cbs.on_message_update) on_event = on_message_update;
        break;
    case DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE:
        if (gw->cmds.cbs.on_message_delete) on_event = on_message_delete;
        break;
    case DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE_BULK:
        if (gw->cmds.cbs.on_message_delete_bulk)
            on_event = on_message_delete_bulk;
        break;
    case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_ADD:
        if (gw->cmds.cbs.on_message_reaction_add)
            on_event = on_message_reaction_add;
        break;
    case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE:
        if (gw->cmds.cbs.on_message_reaction_remove)
            on_event = on_message_reaction_remove;
        break;
    case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_ALL:
        if (gw->cmds.cbs.on_message_reaction_remove_all)
            on_event = on_message_reaction_remove_all;
        break;
    case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_EMOJI:
        if (gw->cmds.cbs.on_message_reaction_remove_emoji)
            on_event = on_message_reaction_remove_emoji;
        break;
    case DISCORD_GATEWAY_EVENTS_PRESENCE_UPDATE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_CREATE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_DELETE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_UPDATE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_TYPING_START:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_USER_UPDATE:
        /** @todo implement */
        break;
    case DISCORD_GATEWAY_EVENTS_VOICE_STATE_UPDATE:
        if (gw->cmds.cbs.on_voice_state_update)
            on_event = on_voice_state_update;
        break;
    case DISCORD_GATEWAY_EVENTS_VOICE_SERVER_UPDATE:
        if (gw->cmds.cbs.on_voice_server_update)
            on_event = on_voice_server_update;
        break;
    case DISCORD_GATEWAY_EVENTS_WEBHOOKS_UPDATE:
        /** @todo implement */
        break;
    default:
        logconf_warn(
            &gw->conf,
            "Expected unimplemented GATEWAY_DISPATCH event (code: %d)", event);
        break;
    }

    mode = gw->cmds.scheduler(client, &gw->payload.data, event);
    if (!on_event) return;

    /* user subscribed to event */
    switch (mode) {
    case DISCORD_EVENT_IGNORE:
        break;
    case DISCORD_EVENT_MAIN_THREAD:
        on_event(gw);
        break;
    case DISCORD_EVENT_WORKER_THREAD: {
        struct discord_event *cxt = malloc(sizeof *cxt);
        int ret;

        cxt->name = strdup(gw->payload.name);
        cxt->gw = &(discord_clone(client)->gw);
        cxt->data.size = cog_strndup(gw->payload.data.start,
                                     gw->payload.data.size, &cxt->data.start);
        cxt->event = event;
        cxt->on_event = on_event;

        ret = work_run(&dispatch_run, cxt);
        VASSERT_S(0 == ret, "Couldn't create task (code %d)", ret);
    } break;
    default:
        ERR("Unknown event handling mode (code: %d)", mode);
    }
}

static void
on_invalid_session(struct discord_gateway *gw)
{
    enum ws_close_reason opcode;
    const char *reason;

    gw->session->status = DISCORD_SESSION_SHUTDOWN;
    if (0 != strncmp(gw->payload.data.start, "false", gw->payload.data.size)) {
        gw->session->status |= DISCORD_SESSION_RESUMABLE;
        reason = "Invalid session, will attempt to resume";
        opcode = (enum ws_close_reason)DISCORD_GATEWAY_CLOSE_REASON_RECONNECT;
    }
    else {
        reason = "Invalid session, can't resume";
        opcode = WS_CLOSE_REASON_NORMAL;
    }
    gw->session->retry.enable = true;

    ws_close(gw->ws, opcode, reason, SIZE_MAX);
}

static void
on_reconnect(struct discord_gateway *gw)
{
    const char reason[] = "Discord expects client to reconnect";

    gw->session->status = DISCORD_SESSION_RESUMABLE | DISCORD_SESSION_SHUTDOWN;
    gw->session->retry.enable = true;

    ws_close(gw->ws,
             (enum ws_close_reason)DISCORD_GATEWAY_CLOSE_REASON_RECONNECT,
             reason, sizeof(reason));
}

static void
on_heartbeat_ack(struct discord_gateway *gw)
{
    /* get request / response interval in milliseconds */
    pthread_rwlock_wrlock(&gw->timer->rwlock);
    gw->timer->ping_ms = (int)(gw->timer->now - gw->timer->hbeat);
    pthread_rwlock_unlock(&gw->timer->rwlock);

    logconf_trace(&gw->conf, "PING: %d ms", gw->timer->ping_ms);
}

static void
on_connect_cb(void *p_gw,
              struct websockets *ws,
              struct ws_info *info,
              const char *ws_protocols)
{
    (void)ws;
    (void)info;
    struct discord_gateway *gw = p_gw;

    logconf_info(&gw->conf, "Connected, WS-Protocols: '%s'", ws_protocols);
}

static void
on_close_cb(void *p_gw,
            struct websockets *ws,
            struct ws_info *info,
            enum ws_close_reason wscode,
            const char *reason,
            size_t len)
{
    (void)ws;
    (void)info;
    struct discord_gateway *gw = p_gw;
    enum discord_gateway_close_opcodes opcode =
        (enum discord_gateway_close_opcodes)wscode;

    logconf_warn(
        &gw->conf,
        ANSICOLOR("CLOSE %s", ANSI_FG_RED) " (code: %4d, %zu bytes): '%.*s'",
        close_opcode_print(opcode), opcode, len, (int)len, reason);

    /* user-triggered shutdown */
    if (gw->session->status & DISCORD_SESSION_SHUTDOWN) return;

    /* mark as in the process of being shutdown */
    gw->session->status |= DISCORD_SESSION_SHUTDOWN;

    switch (opcode) {
    default: /* websocket/clouflare opcodes */
        if (WS_CLOSE_REASON_NORMAL == (enum ws_close_reason)opcode) {
            gw->session->status |= DISCORD_SESSION_RESUMABLE;
            gw->session->retry.enable = false;
            break;
        }
        /* fall-through */
    case DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE:
    case DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT:
        logconf_warn(
            &gw->conf,
            "Gateway will attempt to reconnect and start a new session");
        gw->session->status &= ~DISCORD_SESSION_RESUMABLE;
        gw->session->retry.enable = true;
        break;
    case DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED:
    case DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED:
    case DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION:
    case DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS:
    case DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD:
    case DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS:
        logconf_warn(&gw->conf, "Gateway will not attempt to reconnect");
        gw->session->status &= ~DISCORD_SESSION_RESUMABLE;
        gw->session->retry.enable = false;
        break;
    case DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR:
    case DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE:
    case DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR:
    case DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED:
    case DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED:
    case DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED:
        logconf_warn(
            &gw->conf,
            "Gateway will attempt to reconnect and resume current session");
        gw->session->status |= DISCORD_SESSION_RESUMABLE;
        gw->session->retry.enable = true;
        break;
    }
}

static void
on_text_cb(void *p_gw,
           struct websockets *ws,
           struct ws_info *info,
           const char *text,
           size_t len)
{
    (void)ws;
    struct discord_gateway *gw = p_gw;
    jsmn_parser parser;

    jsmn_init(&parser);
    if (0 < jsmn_parse_auto(&parser, text, len, &gw->parse.tokens,
                            &gw->parse.ntokens))
    {
        jsmnf_loader loader;

        jsmnf_init(&loader);
        if (0 < jsmnf_load_auto(&loader, text, gw->parse.tokens,
                                parser.toknext, &gw->parse.pairs,
                                &gw->parse.npairs))
        {
            jsmnf_pair *f;

            if ((f = jsmnf_find(gw->parse.pairs, "t", 1))) {
                if (JSMN_STRING == f->type)
                    snprintf(gw->payload.name, sizeof(gw->payload.name),
                             "%.*s", f->value.length, f->value.contents);
                else
                    *gw->payload.name = '\0';
            }
            if ((f = jsmnf_find(gw->parse.pairs, "s", 1))) {
                int seq = (int)strtol(f->value.contents, NULL, 10);
                if (seq) gw->payload.seq = seq;
            }
            if ((f = jsmnf_find(gw->parse.pairs, "op", 2)))
                gw->payload.opcode = (int)strtol(f->value.contents, NULL, 10);
            if ((gw->payload._data = jsmnf_find(gw->parse.pairs, "d", 1))) {
                gw->payload.data.start =
                    (char *)gw->payload._data->value.contents;
                gw->payload.data.size =
                    (size_t)gw->payload._data->value.length;
            }
        }
    }

    logconf_trace(
        &gw->conf,
        ANSICOLOR("RCV",
                  ANSI_FG_BRIGHT_YELLOW) " %s%s%s (%zu bytes) [@@@_%zu_@@@]",
        opcode_print(gw->payload.opcode), *gw->payload.name ? " -> " : "",
        gw->payload.name, len, info->loginfo.counter);

    switch (gw->payload.opcode) {
    case DISCORD_GATEWAY_DISPATCH:
        on_dispatch(gw);
        break;
    case DISCORD_GATEWAY_INVALID_SESSION:
        on_invalid_session(gw);
        break;
    case DISCORD_GATEWAY_RECONNECT:
        on_reconnect(gw);
        break;
    case DISCORD_GATEWAY_HELLO:
        on_hello(gw);
        break;
    case DISCORD_GATEWAY_HEARTBEAT_ACK:
        on_heartbeat_ack(gw);
        break;
    default:
        logconf_error(&gw->conf,
                      "Not yet implemented Gateway Event (code: %d)",
                      gw->payload.opcode);
        break;
    }
}

static discord_event_scheduler_t
default_scheduler_cb(struct discord *a,
                     struct sized_buffer *b,
                     enum discord_gateway_events c)
{
    (void)a;
    (void)b;
    (void)c;
    return DISCORD_EVENT_MAIN_THREAD;
}

static int
on_io_poller_curl(struct io_poller *io, CURLM *mhandle, void *user_data)
{
    (void)io;
    (void)mhandle;
    return discord_gateway_perform(user_data);
}

void
discord_gateway_init(struct discord_gateway *gw,
                     struct logconf *conf,
                     struct sized_buffer *token)
{
    struct discord *client = CLIENT(gw, gw);
    /* Web-Sockets callbacks */
    struct ws_callbacks cbs = { 0 };
    /* Web-Sockets custom attributes */
    struct ws_attr attr = { 0 };
    /* Bot default presence update */
    struct discord_presence_update presence = { 0 };
    struct sized_buffer buf;
    /* prefix directive */
    char *path[] = { "discord", "default_prefix" };

    cbs.data = gw;
    cbs.on_connect = &on_connect_cb;
    cbs.on_text = &on_text_cb;
    cbs.on_close = &on_close_cb;

    attr.conf = conf;

    /* Web-Sockets handler */
    gw->mhandle = curl_multi_init();
    io_poller_curlm_add(client->io_poller, gw->mhandle, on_io_poller_curl, gw);
    gw->ws = ws_init(&cbs, gw->mhandle, &attr);
    logconf_branch(&gw->conf, conf, "DISCORD_GATEWAY");

    gw->timer = calloc(1, sizeof *gw->timer);
    if (pthread_rwlock_init(&gw->timer->rwlock, NULL))
        ERR("Couldn't initialize pthread rwlock");

    /* client connection status */
    gw->session = calloc(1, sizeof *gw->session);
    gw->session->retry.enable = true;
    gw->session->retry.limit = 5; /**< hard limit for now */

    /* connection identify token */
    cog_strndup(token->start, token->size, &gw->id.token);

    /* connection identify properties */
    gw->id.properties = calloc(1, sizeof *gw->id.properties);
    gw->id.properties->os = "POSIX";
    gw->id.properties->browser = "concord";
    gw->id.properties->device = "concord";

    /* the bot initial presence */
    gw->id.presence = calloc(1, sizeof *gw->id.presence);
    presence.status = "online";
    presence.since = cog_timestamp_ms();
    discord_set_presence(client, &presence);

    /* default callbacks */
    gw->cmds.scheduler = default_scheduler_cb;

    /* check for default prefix in config file */
    buf = logconf_get_field(conf, path, sizeof(path) / sizeof *path);
    if (buf.size) {
        jsmn_parser parser;
        jsmntok_t tokens[16];

        jsmn_init(&parser);
        if (0 < jsmn_parse(&parser, buf.start, buf.size, tokens,
                           sizeof(tokens) / sizeof *tokens))
        {
            jsmnf_loader loader;
            jsmnf_pair pairs[16];

            jsmnf_init(&loader);
            if (0 < jsmnf_load(&loader, buf.start, tokens, parser.toknext,
                               pairs, sizeof(pairs) / sizeof *pairs))
            {
                bool enable_prefix = false;
                jsmnf_pair *f;

                if ((f = jsmnf_find(pairs, "enable", 6)))
                    enable_prefix = (*f->value.contents == 't');

                if (enable_prefix && (f = jsmnf_find(pairs, "prefix", 6))) {
                    char prefix[64] = "";

                    snprintf(prefix, sizeof(prefix), "%.*s", f->value.length,
                             f->value.contents);
                    discord_set_prefix(CLIENT(gw, gw), prefix);
                }
            }
        }
    }
}

void
discord_gateway_cleanup(struct discord_gateway *gw)
{
    /* cleanup WebSockets handle */
    io_poller_curlm_del(CLIENT(gw, gw)->io_poller, gw->mhandle);
    curl_multi_cleanup(gw->mhandle);
    ws_cleanup(gw->ws);
    /* cleanup timers */
    pthread_rwlock_destroy(&gw->timer->rwlock);
    free(gw->timer);
    /* cleanup bot identification */
    if (gw->id.token) free(gw->id.token);
    free(gw->id.properties);
    free(gw->id.presence);
    /* cleanup client session */
    free(gw->session);
    /* cleanup user commands */
    if (gw->cmds.pool) {
        for (size_t i = 0; i < gw->cmds.amt; i++)
            free(gw->cmds.pool[i].start);
        free(gw->cmds.pool);
    }
    if (gw->cmds.prefix.start) free(gw->cmds.prefix.start);
    if (gw->parse.pairs) free(gw->parse.pairs);
    if (gw->parse.tokens) free(gw->parse.tokens);
}

#ifdef CCORD_DEBUG_WEBSOCKETS
static void
_ws_curl_debug_dump(const char *text,
                    FILE *stream,
                    unsigned char *ptr,
                    size_t size)
{
    unsigned int width = 0x10;
    size_t i;
    size_t c;

    fprintf(stream, "%s, %10.10lu bytes (0x%8.8lx)\n", text,
            (unsigned long)size, (unsigned long)size);

    for (i = 0; i < size; i += width) {

        fprintf(stream, "%4.4lx: ", (unsigned long)i);

        for (c = 0; c < width; c++)
            if (i + c < size)
                fprintf(stream, "%02x ", ptr[i + c]);
            else
                fputs("   ", stream);

        for (c = 0; (c < width) && (i + c < size); c++) {
            /* check for 0D0A; if found, skip past and start a new line of
             * output */
            if ((i + c + 1 < size) && ptr[i + c] == 0x0D
                && ptr[i + c + 1] == 0x0A) {
                i += (c + 2 - width);
                break;
            }
            fprintf(stream, "%c",
                    (ptr[i + c] >= 0x20) && (ptr[i + c] < 0x80) ? ptr[i + c]
                                                                : '.');
            /* check again for 0D0A, to avoid an extra \n if it's at width */
            if ((i + c + 2 < size) && ptr[i + c + 1] == 0x0D
                && ptr[i + c + 2] == 0x0A) {
                i += (c + 3 - width);
                break;
            }
        }
        fputc('\n', stream); /* newline */
    }
    fflush(stream);
}

static int
_ws_curl_debug_trace(
    CURL *handle, curl_infotype type, char *data, size_t size, void *userp)
{
    const char *text;
    (void)handle;
    (void)userp;

    switch (type) {
    case CURLINFO_TEXT:
        fprintf(stderr, "== Info: %s", data);
        /* FALLTHROUGH */
    default:
        return 0;

    case CURLINFO_HEADER_OUT:
        text = "=> Send header";
        break;
    case CURLINFO_DATA_OUT:
        text = "=> Send data";
        break;
    case CURLINFO_SSL_DATA_OUT:
        text = "=> Send SSL data";
        break;
    case CURLINFO_HEADER_IN:
        text = "<= Recv header";
        break;
    case CURLINFO_DATA_IN:
        text = "<= Recv data";
        break;
    case CURLINFO_SSL_DATA_IN:
        text = "<= Recv SSL data";
        break;
    }

    _ws_curl_debug_dump(text, stderr, (unsigned char *)data, size);
    return 0;
}
#endif /* CCORD_DEBUG_WEBSOCKETS */

CCORDcode
discord_gateway_start(struct discord_gateway *gw)
{
    struct discord *client = CLIENT(gw, gw);
    struct sized_buffer json = { 0 };
    char url[1024];
    CURL *ehandle;

    if (gw->session->retry.attempt >= gw->session->retry.limit) {
        logconf_fatal(&gw->conf,
                      "Failed reconnecting to Discord after %d tries",
                      gw->session->retry.limit);

        return CCORD_DISCORD_CONNECTION;
    }
    else if (CCORD_OK != discord_get_gateway_bot(client, &json)) {
        logconf_fatal(&gw->conf, "Couldn't retrieve Gateway Bot information");

        return CCORD_DISCORD_BAD_AUTH;
    }
    else {
        jsmn_parser parser;
        jsmntok_t tokens[32];

        jsmn_init(&parser);
        if (0 < jsmn_parse(&parser, json.start, json.size, tokens,
                           sizeof(tokens) / sizeof *tokens))
        {
            jsmnf_loader loader;
            jsmnf_pair pairs[32];

            jsmnf_init(&loader);
            if (0 < jsmnf_load(&loader, json.start, tokens, parser.toknext,
                               pairs, sizeof(pairs) / sizeof *pairs))
            {
                jsmnf_pair *f;

                if ((f = jsmnf_find(pairs, "url", 3))) {
                    const char *base_url = f->value.contents;
                    const int base_url_len = f->value.length;
                    int len;

                    len = snprintf(
                        url, sizeof(url), "%.*s%s" DISCORD_GATEWAY_URL_SUFFIX,
                        base_url_len, base_url,
                        ('/' == base_url[base_url_len - 1]) ? "" : "/");
                    ASSERT_NOT_OOB(len, sizeof(url));
                }
                if ((f = jsmnf_find(pairs, "shards", 6)))
                    gw->session->shards =
                        (int)strtol(f->value.contents, NULL, 10);
                if ((f = jsmnf_find(pairs, "session_start_limit", 19)))
                    discord_session_start_limit_from_jsmnf(
                        f, &gw->session->start_limit);
            }
            else
                abort();
        }
        else
            abort();
    }

    free(json.start);

    if (!gw->session->start_limit.remaining) {
        logconf_fatal(&gw->conf,
                      "Reach sessions threshold (%d),"
                      "Please wait %d seconds and try again",
                      gw->session->start_limit.total,
                      gw->session->start_limit.reset_after / 1000);

        return CCORD_DISCORD_RATELIMIT;
    }

    ws_set_url(gw->ws, url, NULL);
    ehandle = ws_start(gw->ws);

#ifdef CCORD_DEBUG_WEBSOCKETS
    curl_easy_setopt(ehandle, CURLOPT_DEBUGFUNCTION, _ws_curl_debug_trace);
    curl_easy_setopt(ehandle, CURLOPT_VERBOSE, 1L);
#else
    (void)ehandle;
#endif /* CCORD_DEBUG_WEBSOCKETS */

    return CCORD_OK;
}

bool
discord_gateway_end(struct discord_gateway *gw)
{
    ws_end(gw->ws);

    /* keep only resumable information */
    gw->session->status &= DISCORD_SESSION_RESUMABLE;
    gw->session->is_ready = false;

    if (!gw->session->retry.enable) {
        logconf_warn(&gw->conf, "Discord Gateway Shutdown");

        /* reset for next run */
        gw->session->status = DISCORD_SESSION_OFFLINE;
        gw->session->is_ready = false;
        gw->session->retry.enable = false;
        gw->session->retry.attempt = 0;

        return true;
    }

    ++gw->session->retry.attempt;

    logconf_info(&gw->conf, "Reconnect attempt #%d",
                 gw->session->retry.attempt);

    return false;
}

CCORDcode
discord_gateway_perform(struct discord_gateway *gw)
{
    /* check for pending transfer, exit on failure */
    if (!ws_multi_socket_run(gw->ws, &gw->timer->now))
        return CCORD_DISCORD_CONNECTION;

    /* client is in the process of shutting down */
    if (gw->session->status & DISCORD_SESSION_SHUTDOWN) return CCORD_OK;

    /* client is in the process of connecting */
    if (!gw->session->is_ready) return CCORD_OK;

    /* check if timespan since first pulse is greater than
     * minimum heartbeat interval required */
    if (gw->timer->interval < gw->timer->now - gw->timer->hbeat) {
        send_heartbeat(gw);
    }

    return CCORD_OK;
}

void
discord_gateway_shutdown(struct discord_gateway *gw)
{
    const char reason[] = "Client triggered shutdown";

    /* TODO: MT-Unsafe section */
    gw->session->retry.enable = false;
    gw->session->status = DISCORD_SESSION_SHUTDOWN;

    ws_close(gw->ws, WS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
}

void
discord_gateway_reconnect(struct discord_gateway *gw, bool resume)
{
    const char reason[] = "Client triggered reconnect";
    enum ws_close_reason opcode;

    /* TODO: MT-Unsafe section */
    gw->session->retry.enable = true;
    gw->session->status = DISCORD_SESSION_SHUTDOWN;
    if (resume) {
        gw->session->status |= DISCORD_SESSION_RESUMABLE;
        opcode = (enum ws_close_reason)DISCORD_GATEWAY_CLOSE_REASON_RECONNECT;
    }
    else {
        opcode = WS_CLOSE_REASON_NORMAL;
    }

    ws_close(gw->ws, opcode, reason, sizeof(reason));
}
