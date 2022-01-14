#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h> /* offsetof() */
#include <ctype.h> /* isspace() */

#include "discord.h"
#include "discord-internal.h"

/* shorten event callback for maintainability purposes */
#define ON(event, ...) gw->cmds.cbs.on_##event(CLIENT(gw, gw), __VA_ARGS__)

static const char *
opcode_print(enum discord_gateway_opcodes opcode)
{
    const char *str = discord_gateway_opcodes_print(opcode);
    if (!str) str = "Invalid Gateway opcode";
    return str;
}

static const char *
close_opcode_print(enum discord_gateway_close_opcodes opcode)
{
    const char *str;

    str = discord_gateway_close_opcodes_print(opcode);
    if (str) return str;

    str = ws_close_opcode_print((enum ws_close_reason)opcode);
    if (str) return str;

    log_warn("Unknown WebSockets close opcode (code: %d)", opcode);
    return "Unknown WebSockets close opcode";
}

void
discord_gateway_send_presence_update(struct discord_gateway *gw)
{
    char buf[2048];
    size_t len;
    struct ws_info info = { 0 };

    if (!gw->session->is_ready) return;

    len = json_inject(buf, sizeof(buf),
                      "(op):3" /* PRESENCE UPDATE OPCODE */
                      "(d):F",
                      &discord_presence_status_to_json, gw->id.presence);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");

    ws_send_text(gw->ws, &info, buf, len);

    logconf_info(
        &gw->conf,
        ANSICOLOR(
            "SEND",
            ANSI_FG_BRIGHT_GREEN) " PRESENCE UPDATE (%d bytes) [@@@_%zu_@@@]",
        len, info.loginfo.counter + 1);
}

static void
send_resume(struct discord_gateway *gw)
{
    char buf[1024];
    size_t len;
    struct ws_info info = { 0 };

    /* reset */
    gw->session->status ^= DISCORD_SESSION_RESUMABLE;

    len = json_inject(buf, sizeof(buf),
                      "(op):6" /* RESUME OPCODE */
                      "(d):{"
                      "(token):s"
                      "(session_id):s"
                      "(seq):d"
                      "}",
                      gw->id.token, gw->session->id, &gw->payload.seq);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");

    ws_send_text(gw->ws, &info, buf, len);

    logconf_info(
        &gw->conf,
        ANSICOLOR("SEND",
                  ANSI_FG_BRIGHT_GREEN) " RESUME (%d bytes) [@@@_%zu_@@@]",
        len, info.loginfo.counter + 1);
}

static void
send_identify(struct discord_gateway *gw)
{
    char buf[1024];
    size_t len;
    struct ws_info info = { 0 };

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

    len = json_inject(buf, sizeof(buf),
                      "(op):2" /* IDENTIFY OPCODE */
                      "(d):F",
                      &discord_identify_to_json, &gw->id);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");

    ws_send_text(gw->ws, &info, buf, len);

    logconf_info(
        &gw->conf,
        ANSICOLOR("SEND",
                  ANSI_FG_BRIGHT_GREEN) " IDENTIFY (%d bytes) [@@@_%zu_@@@]",
        len, info.loginfo.counter + 1);

    /* get timestamp for this identify */
    gw->timer->identify = gw->timer->now;
}

/* send heartbeat pulse to websockets server in order
 *  to maintain connection alive */
static void
send_heartbeat(struct discord_gateway *gw)
{
    char buf[64];
    size_t len;
    struct ws_info info = { 0 };

    len = json_inject(buf, sizeof(buf), "(op):1,(d):d", &gw->payload.seq);
    ASSERT_S(len < sizeof(buf), "Out of bounds write attempt");

    ws_send_text(gw->ws, &info, buf, len);

    logconf_info(
        &gw->conf,
        ANSICOLOR("SEND",
                  ANSI_FG_BRIGHT_GREEN) " HEARTBEAT (%d bytes) [@@@_%zu_@@@]",
        len, info.loginfo.counter + 1);

    /* update heartbeat timestamp */
    gw->timer->hbeat = gw->timer->now;
}

static void
on_hello(struct discord_gateway *gw)
{
    gw->timer->interval = 0;
    gw->timer->hbeat = gw->timer->now;

    json_extract(gw->payload.data.start, gw->payload.data.size,
                 "(heartbeat_interval):ld", &gw->timer->interval);

    if (gw->session->status & DISCORD_SESSION_RESUMABLE)
        send_resume(gw);
    else
        send_identify(gw);
}

static enum discord_gateway_events
get_dispatch_event(char name[])
{
#define RETURN_IF_MATCH(event, str)                                           \
    if (STREQ(#event, str)) return DISCORD_GATEWAY_EVENTS_##event

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
on_guild_create(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_guild guild = { 0 };
    discord_guild_from_json(data->start, data->size, &guild);

    ON(guild_create, &guild);

    discord_guild_cleanup(&guild);
}

static void
on_guild_update(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_guild guild = { 0 };
    discord_guild_from_json(data->start, data->size, &guild);

    ON(guild_update, &guild);

    discord_guild_cleanup(&guild);
}

static void
on_guild_delete(struct discord_gateway *gw, struct sized_buffer *data)
{
    u64_snowflake_t guild_id = 0;
    json_extract(data->start, data->size, "(id):s_as_u64", &guild_id);
    ON(guild_delete, guild_id);
}

static void
on_guild_role_create(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_role role;
    u64_snowflake_t guild_id = 0;

    json_extract(data->start, data->size,
                 "(guild_id):s_as_u64"
                 "(role):F",
                 &guild_id, &discord_role_from_json, &role);

    ON(guild_role_create, guild_id, &role);

    discord_role_cleanup(&role);
}

static void
on_guild_role_update(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_role role;
    u64_snowflake_t guild_id = 0;

    json_extract(data->start, data->size,
                 "(guild_id):s_as_u64"
                 "(role):F",
                 &guild_id, &discord_role_from_json, &role);

    ON(guild_role_update, guild_id, &role);

    discord_role_cleanup(&role);
}

static void
on_guild_role_delete(struct discord_gateway *gw, struct sized_buffer *data)
{
    u64_snowflake_t guild_id = 0, role_id = 0;

    json_extract(data->start, data->size,
                 "(guild_id):s_as_u64"
                 "(role_id):s_as_u64",
                 &guild_id, &role_id);

    ON(guild_role_delete, guild_id, role_id);
}

static void
on_guild_member_add(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_guild_member member;
    u64_snowflake_t guild_id = 0;

    discord_guild_member_from_json(data->start, data->size, &member);

    json_extract(data->start, data->size, "(guild_id):s_as_u64", &guild_id);

    ON(guild_member_add, guild_id, &member);

    discord_guild_member_cleanup(&member);
}

static void
on_guild_member_update(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_guild_member member;
    u64_snowflake_t guild_id = 0;

    discord_guild_member_from_json(data->start, data->size, &member);

    json_extract(data->start, data->size, "(guild_id):s_as_u64", &guild_id);

    ON(guild_member_update, guild_id, &member);

    discord_guild_member_cleanup(&member);
}

static void
on_guild_member_remove(struct discord_gateway *gw, struct sized_buffer *data)
{
    u64_snowflake_t guild_id = 0;
    struct discord_user user;

    json_extract(data->start, data->size,
                 "(guild_id):s_as_u64"
                 "(user):F",
                 &guild_id, &discord_user_from_json, &user);

    ON(guild_member_remove, guild_id, &user);

    discord_user_cleanup(&user);
}

static void
on_guild_ban_add(struct discord_gateway *gw, struct sized_buffer *data)
{
    u64_snowflake_t guild_id = 0;
    struct discord_user user;

    json_extract(data->start, data->size,
                 "(guild_id):s_as_u64"
                 "(user):F",
                 &guild_id, &discord_user_from_json, &user);

    ON(guild_ban_add, guild_id, &user);

    discord_user_cleanup(&user);
}

static void
on_guild_ban_remove(struct discord_gateway *gw, struct sized_buffer *data)
{
    u64_snowflake_t guild_id = 0;
    struct discord_user user;

    json_extract(data->start, data->size,
                 "(guild_id):s_as_u64"
                 "(user):F",
                 &guild_id, &discord_user_from_json, &user);

    ON(guild_ban_remove, guild_id, &user);

    discord_user_cleanup(&user);
}

static void
on_application_command_create(struct discord_gateway *gw,
                              struct sized_buffer *data)
{
    struct discord_application_command cmd;

    discord_application_command_from_json(data->start, data->size, &cmd);

    ON(application_command_create, &cmd);

    discord_application_command_cleanup(&cmd);
}

static void
on_application_command_update(struct discord_gateway *gw,
                              struct sized_buffer *data)
{
    struct discord_application_command cmd;

    discord_application_command_from_json(data->start, data->size, &cmd);

    ON(application_command_update, &cmd);

    discord_application_command_cleanup(&cmd);
}

static void
on_application_command_delete(struct discord_gateway *gw,
                              struct sized_buffer *data)
{
    struct discord_application_command cmd;

    discord_application_command_from_json(data->start, data->size, &cmd);
    ON(application_command_delete, &cmd);

    discord_application_command_cleanup(&cmd);
}

static void
on_channel_create(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_channel channel;

    discord_channel_from_json(data->start, data->size, &channel);

    ON(channel_create, &channel);

    discord_channel_cleanup(&channel);
}

static void
on_channel_update(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_channel channel;

    discord_channel_from_json(data->start, data->size, &channel);

    ON(channel_update, &channel);

    discord_channel_cleanup(&channel);
}

static void
on_channel_delete(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_channel channel;

    discord_channel_from_json(data->start, data->size, &channel);

    ON(channel_delete, &channel);

    discord_channel_cleanup(&channel);
}

static void
on_channel_pins_update(struct discord_gateway *gw, struct sized_buffer *data)
{
    u64_snowflake_t guild_id = 0, channel_id = 0;
    u64_unix_ms_t last_pin_timestamp = 0;

    json_extract(data->start, data->size,
                 "(guild_id):s_as_u64"
                 "(channel_id):s_as_u64"
                 "(last_pin_timestamp):F",
                 &guild_id, &channel_id, &cog_iso8601_to_unix_ms,
                 &last_pin_timestamp);

    ON(channel_pins_update, guild_id, channel_id, last_pin_timestamp);
}

static void
on_thread_create(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_channel thread;

    discord_channel_from_json(data->start, data->size, &thread);

    ON(thread_create, &thread);

    discord_channel_cleanup(&thread);
}

static void
on_thread_update(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_channel thread;

    discord_channel_from_json(data->start, data->size, &thread);

    ON(thread_update, &thread);

    discord_channel_cleanup(&thread);
}

static void
on_thread_delete(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_channel thread;

    discord_channel_from_json(data->start, data->size, &thread);

    ON(thread_delete, &thread);

    discord_channel_cleanup(&thread);
}

static void
on_interaction_create(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_interaction interaction;

    discord_interaction_from_json(data->start, data->size, &interaction);

    ON(interaction_create, &interaction);

    discord_interaction_cleanup(&interaction);
}

static void
on_message_create(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_message msg;

    discord_message_from_json(data->start, data->size, &msg);

    if (gw->cmds.pool
        && STRNEQ(gw->cmds.prefix.start, msg.content, gw->cmds.prefix.size))
    {
        struct discord_gateway_cmd_cbs *cmd = NULL;
        size_t i;

        for (i = 0; i < gw->cmds.amt; ++i) {
            /* check if command from channel matches set command */
            if (STRNEQ(gw->cmds.pool[i].start,
                       msg.content + gw->cmds.prefix.size,
                       gw->cmds.pool[i].size))
            {
                cmd = &gw->cmds.pool[i];
            }
        }
        if (!cmd && gw->cmds.prefix.size) {
            cmd = &gw->cmds.on_default;
        }

        if (cmd && cmd->cb) {
            struct discord *client = CLIENT(gw, gw);
            char *tmp = msg.content; /* hold original ptr */

            /* skip blank characters */
            msg.content += (ptrdiff_t)(gw->cmds.prefix.size + cmd->size);
            while (isspace(*msg.content)) {
                ++msg.content;
            }

            cmd->cb(client, &msg);

            msg.content = tmp; /* retrieve original ptr */
        }
    }
    else if (gw->cmds.cbs.on_message_create) {
        ON(message_create, &msg);
    }

    discord_message_cleanup(&msg);
}

static void
on_message_update(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_message msg;

    discord_message_from_json(data->start, data->size, &msg);

    ON(message_update, &msg);

    discord_message_cleanup(&msg);
}

static void
on_message_delete(struct discord_gateway *gw, struct sized_buffer *data)
{
    u64_snowflake_t message_id = 0, channel_id = 0, guild_id = 0;

    json_extract(data->start, data->size,
                 "(id):s_as_u64"
                 "(channel_id):s_as_u64"
                 "(guild_id):s_as_u64",
                 &message_id, &channel_id, &guild_id);

    ON(message_delete, message_id, channel_id, guild_id);
}

static void
on_message_delete_bulk(struct discord_gateway *gw, struct sized_buffer *data)
{
    u64_snowflake_t **ids = NULL;
    u64_snowflake_t channel_id = 0, guild_id = 0;

    json_extract(data->start, data->size,
                 "(ids):F"
                 "(channel_id):s_as_u64"
                 "(guild_id):s_as_u64",
                 &ja_u64_list_from_json, &ids, &channel_id, &guild_id);

    ON(message_delete_bulk, (const u64_snowflake_t **)ids, channel_id,
       guild_id);

    free(ids);
}

static void
on_message_reaction_add(struct discord_gateway *gw, struct sized_buffer *data)
{
    u64_snowflake_t user_id = 0, message_id = 0, channel_id = 0, guild_id = 0;
    struct discord_guild_member member;
    struct discord_emoji emoji;

    json_extract(data->start, data->size,
                 "(user_id):s_as_u64"
                 "(message_id):s_as_u64"
                 "(member):F"
                 "(emoji):F"
                 "(channel_id):s_as_u64"
                 "(guild_id):s_as_u64",
                 &user_id, &message_id, &discord_guild_member_from_json,
                 &member, &discord_emoji_from_json, &emoji, &channel_id,
                 &guild_id);

    ON(message_reaction_add, user_id, channel_id, message_id, guild_id,
       &member, &emoji);

    discord_guild_member_cleanup(&member);
    discord_emoji_cleanup(&emoji);
}

static void
on_message_reaction_remove(struct discord_gateway *gw,
                           struct sized_buffer *data)
{
    u64_snowflake_t user_id = 0, message_id = 0, channel_id = 0, guild_id = 0;
    struct discord_emoji emoji;

    json_extract(data->start, data->size,
                 "(user_id):s_as_u64"
                 "(message_id):s_as_u64"
                 "(emoji):F"
                 "(channel_id):s_as_u64"
                 "(guild_id):s_as_u64",
                 &user_id, &message_id, &discord_emoji_from_json, &emoji,
                 &channel_id, &guild_id);

    ON(message_reaction_remove, user_id, channel_id, message_id, guild_id,
       &emoji);

    discord_emoji_cleanup(&emoji);
}

static void
on_message_reaction_remove_all(struct discord_gateway *gw,
                               struct sized_buffer *data)
{
    u64_snowflake_t channel_id = 0, message_id = 0, guild_id = 0;

    json_extract(data->start, data->size,
                 "(channel_id):s_as_u64"
                 "(message_id):s_as_u64"
                 "(channel_id):s_as_u64",
                 &channel_id, &message_id, &guild_id);

    ON(message_reaction_remove_all, channel_id, message_id, guild_id);
}

static void
on_message_reaction_remove_emoji(struct discord_gateway *gw,
                                 struct sized_buffer *data)
{
    u64_snowflake_t channel_id = 0, guild_id = 0, message_id = 0;
    struct discord_emoji emoji;

    json_extract(data->start, data->size,
                 "(channel_id):s_as_u64"
                 "(guild_id):s_as_u64"
                 "(message_id):s_as_u64"
                 "(emoji):F",
                 &channel_id, &guild_id, &message_id, &discord_emoji_from_json,
                 &emoji);

    ON(message_reaction_remove_emoji, channel_id, guild_id, message_id,
       &emoji);

    discord_emoji_cleanup(&emoji);
}

static void
on_voice_state_update(struct discord_gateway *gw, struct sized_buffer *data)
{
    struct discord_voice_state vs;

    discord_voice_state_from_json(data->start, data->size, &vs);

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
on_voice_server_update(struct discord_gateway *gw, struct sized_buffer *data)
{
    u64_snowflake_t guild_id = 0;
    char token[512], endpoint[1024];

    json_extract(data->start, data->size,
                 "(token):s"
                 "(guild_id):s_as_u64"
                 "(endpoint):s",
                 &token, &guild_id, &endpoint);

#ifdef HAS_DISCORD_VOICE
    /* this happens for everyone */
    _discord_on_voice_server_update(CLIENT(gw, gw), guild_id, token, endpoint);
#endif /* HAS_DISCORD_VOICE */

    if (gw->cmds.cbs.on_voice_server_update)
        ON(voice_server_update, token, guild_id, endpoint);
}

static void
on_ready(struct discord_gateway *gw, struct sized_buffer *data)
{
    (void)data;
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

    cxt->on_event(cxt->gw, &cxt->data);

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
    void (*on_event)(struct discord_gateway *, struct sized_buffer *) = NULL;
    /* get dispatch event opcode */
    enum discord_gateway_events event;
    enum discord_event_scheduler mode;

    /* TODO: this should only apply for user dispatched payloads? */
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
    case DISCORD_GATEWAY_EVENTS_READY:
        logconf_info(&gw->conf, "Succesfully started a Discord session!");

        json_extract(gw->payload.data.start, gw->payload.data.size,
                     "(session_id):s", gw->session->id);
        ASSERT_S(!IS_EMPTY_STRING(gw->session->id),
                 "Missing session_id from READY event");

        gw->session->is_ready = true;
        gw->session->retry.attempt = 0;

        if (gw->cmds.cbs.on_ready) on_event = &on_ready;

        send_heartbeat(gw);

        break;
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
        on_event(gw, &gw->payload.data);
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
    gw->timer->ping_ms = gw->timer->now - gw->timer->hbeat;
    pthread_rwlock_unlock(&gw->timer->rwlock);

    logconf_trace(&gw->conf, "PING: %d ms", gw->timer->ping_ms);
}

static void
on_connect_cb(void *p_gw,
              struct websockets *ws,
              struct ws_info *info,
              const char *ws_protocols)
{
    struct discord_gateway *gw = p_gw;
    (void)ws;
    (void)info;

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
    struct discord_gateway *gw = p_gw;
    enum discord_gateway_close_opcodes opcode =
        (enum discord_gateway_close_opcodes)wscode;
    (void)ws;
    (void)info;

    logconf_warn(
        &gw->conf,
        ANSICOLOR("CLOSE %s", ANSI_FG_RED) " (code: %4d, %zu bytes): '%.*s'",
        close_opcode_print(opcode), opcode, len, (int)len, reason);

    /* user-triggered shutdown */
    if (gw->session->status & DISCORD_SESSION_SHUTDOWN) return;

    /* mark as in the process of being shutdown */
    gw->session->status |= DISCORD_SESSION_SHUTDOWN;

    switch (opcode) {
    case DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR:
    case DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE:
    case DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE:
    case DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR:
    case DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED:
    case DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED:
    case DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED:
    case DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED:
    case DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED:
    case DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION:
    case DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS:
    case DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD:
    case DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS:
        gw->session->status &= ~DISCORD_SESSION_RESUMABLE;
        gw->session->retry.enable = false;
        break;
    default: /*websocket/clouflare opcodes */
        if (WS_CLOSE_REASON_NORMAL == (enum ws_close_reason)opcode) {
            gw->session->status |= DISCORD_SESSION_RESUMABLE;
            gw->session->retry.enable = false;
        }
        else {
            logconf_warn(
                &gw->conf,
                "Gateway will attempt to reconnect and start a new session");
            gw->session->status &= ~DISCORD_SESSION_RESUMABLE;
            gw->session->retry.enable = true;
        }
        break;
    case DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT:
        logconf_warn(
            &gw->conf,
            "Gateway will attempt to reconnect and resume current session");
        gw->session->status &= ~DISCORD_SESSION_RESUMABLE;
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
    struct discord_gateway *gw = p_gw;
    /* check sequence value first, then assign */
    int seq = 0;
    (void)ws;

    json_extract((char *)text, len, "(t):s (s):d (op):d (d):T",
                 gw->payload.name, &seq, &gw->payload.opcode,
                 &gw->payload.data);

    if (seq) gw->payload.seq = seq;

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

static void
on_io_poller_curl(CURLM *multi, void *user_data)
{
    (void)multi;
    discord_gateway_perform(user_data);
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
    /* Bot default presence status */
    struct discord_presence_status presence = { 0 };
    struct sized_buffer buf;

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
    buf = logconf_get_field(conf, "discord.default_prefix");
    if (buf.size) {
        bool enable_prefix = false;
        json_extract(buf.start, buf.size, "(enable):b", &enable_prefix);

        if (enable_prefix) {
            char *prefix = NULL;
            json_extract(buf.start, buf.size, "(prefix):?s", &prefix);

            gw->cmds.prefix.start = prefix;
            gw->cmds.prefix.size = prefix ? strlen(prefix) : 0;
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
    if (gw->cmds.pool) free(gw->cmds.pool);
    if (gw->cmds.prefix.start) free(gw->cmds.prefix.start);
}

CCORDcode
discord_gateway_start(struct discord_gateway *gw)
{
    struct discord *client = CLIENT(gw, gw);
    /* get gateway bot info */
    struct sized_buffer json = { 0 };
    /* build URL that will be used to connect to Discord */
    char *base_url, url[1024];
    /* snprintf() OOB check */
    size_t len;

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

    json_extract(json.start, json.size,
                 "(url):?s,(shards):d,(session_start_limit):F", &base_url,
                 &gw->session->shards, &discord_session_start_limit_from_json,
                 &gw->session->start_limit);

    len =
        snprintf(url, sizeof(url), "%s%s" DISCORD_GATEWAY_URL_SUFFIX, base_url,
                 ('/' == base_url[strlen(base_url) - 1]) ? "" : "/");
    ASSERT_S(len < sizeof(url), "Out of bounds write attempt");

    free(json.start);
    free(base_url);

    if (!gw->session->start_limit.remaining) {
        logconf_fatal(&gw->conf,
                      "Reach sessions threshold (%d),"
                      "Please wait %d seconds and try again",
                      gw->session->start_limit.total,
                      gw->session->start_limit.reset_after / 1000);

        return CCORD_DISCORD_RATELIMIT;
    }

    ws_set_url(gw->ws, url, NULL);
    ws_start(gw->ws);

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
    if (gw->timer->interval < gw->timer->now - gw->timer->hbeat)
        send_heartbeat(gw);

        /* XXX: moved to discord_run() */
#if 0
    if (gw->cmds.cbs.on_idle) gw->cmds.cbs.on_idle(CLIENT(gw, gw));
#endif

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
