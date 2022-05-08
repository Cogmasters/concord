#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* isspace() */

#include "discord.h"
#include "discord-internal.h"

#define INIT(type, event_name)                                                \
    {                                                                         \
        sizeof(struct type),                                                  \
            (size_t(*)(jsmnf_pair *, const char *, void *))type##_from_jsmnf, \
            (void (*)(void *))type##_cleanup                                  \
    }

/** @brief Information for deserializing a Discord event */
static const struct {
    /** size of event's datatype */
    size_t size;
    /** event's payload deserializer */
    size_t (*from_jsmnf)(jsmnf_pair *, const char *, void *);
    /** event's cleanup */
    void (*cleanup)(void *);
} dispatch[] = {
    [DISCORD_EV_READY] =
        INIT(discord_ready, ready),
    [DISCORD_EV_APPLICATION_COMMAND_CREATE] =
        INIT(discord_application_command, application_command_create),
    [DISCORD_EV_APPLICATION_COMMAND_UPDATE] =
        INIT(discord_application_command, application_command_update),
    [DISCORD_EV_APPLICATION_COMMAND_DELETE] =
        INIT(discord_application_command, application_command_delete),
    [DISCORD_EV_CHANNEL_CREATE] =
        INIT(discord_channel, channel_create),
    [DISCORD_EV_CHANNEL_UPDATE] =
        INIT(discord_channel, channel_update),
    [DISCORD_EV_CHANNEL_DELETE] =
        INIT(discord_channel, channel_delete),
    [DISCORD_EV_CHANNEL_PINS_UPDATE] =
        INIT(discord_channel_pins_update, channel_pins_update),
    [DISCORD_EV_THREAD_CREATE] =
        INIT(discord_channel, thread_create),
    [DISCORD_EV_THREAD_UPDATE] =
        INIT(discord_channel, thread_update),
    [DISCORD_EV_THREAD_DELETE] =
        INIT(discord_channel, thread_delete),
    [DISCORD_EV_THREAD_LIST_SYNC] =
        INIT(discord_thread_list_sync, thread_list_sync),
    [DISCORD_EV_THREAD_MEMBER_UPDATE] =
        INIT(discord_thread_member, thread_member_update),
    [DISCORD_EV_THREAD_MEMBERS_UPDATE] =
        INIT(discord_thread_members_update, thread_members_update),
    [DISCORD_EV_GUILD_CREATE] =
        INIT(discord_guild, guild_create),
    [DISCORD_EV_GUILD_UPDATE] =
        INIT(discord_guild, guild_update),
    [DISCORD_EV_GUILD_DELETE] =
        INIT(discord_guild, guild_delete),
    [DISCORD_EV_GUILD_BAN_ADD] =
        INIT(discord_guild_ban_add, guild_ban_add),
    [DISCORD_EV_GUILD_BAN_REMOVE] =
        INIT(discord_guild_ban_remove, guild_ban_remove),
    [DISCORD_EV_GUILD_EMOJIS_UPDATE] =
        INIT(discord_guild_emojis_update, guild_emojis_update),
    [DISCORD_EV_GUILD_STICKERS_UPDATE] =
        INIT(discord_guild_stickers_update, guild_stickers_update),
    [DISCORD_EV_GUILD_INTEGRATIONS_UPDATE] =
        INIT(discord_guild_integrations_update, guild_integrations_update),
    [DISCORD_EV_GUILD_MEMBER_ADD] =
        INIT(discord_guild_member, guild_member_add),
    [DISCORD_EV_GUILD_MEMBER_UPDATE] =
        INIT(discord_guild_member_update, guild_member_update),
    [DISCORD_EV_GUILD_MEMBER_REMOVE] =
        INIT(discord_guild_member_remove, guild_member_remove),
    [DISCORD_EV_GUILD_ROLE_CREATE] =
        INIT(discord_guild_role_create, guild_role_create),
    [DISCORD_EV_GUILD_ROLE_UPDATE] =
        INIT(discord_guild_role_update, guild_role_update),
    [DISCORD_EV_GUILD_ROLE_DELETE] =
        INIT(discord_guild_role_delete, guild_role_delete),
    [DISCORD_EV_INTEGRATION_CREATE] =
        INIT(discord_integration, integration_create),
    [DISCORD_EV_INTEGRATION_UPDATE] =
        INIT(discord_integration, integration_update),
    [DISCORD_EV_INTEGRATION_DELETE] =
        INIT(discord_integration_delete, integration_delete),
    [DISCORD_EV_INTERACTION_CREATE] =
        INIT(discord_interaction, interaction_create),
    [DISCORD_EV_INVITE_CREATE] =
        INIT(discord_invite_create, invite_create),
    [DISCORD_EV_INVITE_DELETE] =
        INIT(discord_invite_delete, invite_delete),
    [DISCORD_EV_MESSAGE_CREATE] =
        INIT(discord_message, message_create),
    [DISCORD_EV_MESSAGE_UPDATE] =
        INIT(discord_message, message_update),
    [DISCORD_EV_MESSAGE_DELETE] =
        INIT(discord_message_delete, message_delete),
    [DISCORD_EV_MESSAGE_DELETE_BULK] =
        INIT(discord_message_delete_bulk, message_delete_bulk),
    [DISCORD_EV_MESSAGE_REACTION_ADD] =
        INIT(discord_message_reaction_add, message_reaction_add),
    [DISCORD_EV_MESSAGE_REACTION_REMOVE] =
        INIT(discord_message_reaction_remove, message_reaction_remove),
    [DISCORD_EV_MESSAGE_REACTION_REMOVE_ALL] =
        INIT(discord_message_reaction_remove_all, message_reaction_remove_all),
    [DISCORD_EV_MESSAGE_REACTION_REMOVE_EMOJI] =
        INIT(discord_message_reaction_remove_emoji,
                message_reaction_remove_emoji),
    [DISCORD_EV_PRESENCE_UPDATE] =
        INIT(discord_presence_update, presence_update),
    [DISCORD_EV_STAGE_INSTANCE_CREATE] =
        INIT(discord_stage_instance, stage_instance_create),
    [DISCORD_EV_STAGE_INSTANCE_UPDATE] =
        INIT(discord_stage_instance, stage_instance_update),
    [DISCORD_EV_STAGE_INSTANCE_DELETE] =
        INIT(discord_stage_instance, stage_instance_delete),
    [DISCORD_EV_TYPING_START] =
        INIT(discord_typing_start, typing_start),
    [DISCORD_EV_USER_UPDATE] =
        INIT(discord_user, user_update),
    [DISCORD_EV_VOICE_STATE_UPDATE] =
        INIT(discord_voice_state, voice_state_update),
    [DISCORD_EV_VOICE_SERVER_UPDATE] =
        INIT(discord_voice_server_update, voice_server_update),
    [DISCORD_EV_WEBHOOKS_UPDATE] =
        INIT(discord_webhooks_update, webhooks_update),
};

static void
_discord_message_cleanup_v(void *message)
{
    discord_message_cleanup(message);
    free(message);
}

/** return true in case user command has been triggered */
static bool
_discord_gateway_try_command(struct discord_gateway *gw)
{
    jsmnf_pair *f = jsmnf_find(gw->payload.data, gw->json, "content", 7);

    if (gw->pool
        && !strncmp(gw->prefix.start, gw->json + f->v.pos, gw->prefix.size))
    {
        struct discord_message *event = calloc(1, sizeof *event);
        struct discord *client = CLIENT(gw, gw);
        discord_ev_message callback = NULL;
        char *cmd_start;
        size_t cmd_len;
        char *tmp;

        discord_message_from_jsmnf(gw->payload.data, gw->json, event);

        cmd_start = event->content + gw->prefix.size;
        cmd_len = strcspn(cmd_start, " \n\t\r");

        tmp = event->content;

        /* match command to its callback */
        for (size_t i = 0; i < gw->amt; ++i) {
            if (cmd_len == gw->pool[i].size
                && 0 == strncmp(gw->pool[i].start, cmd_start, cmd_len))
            {

                callback = gw->pool[i].cb;
                break;
            }
        }

        /* couldn't match command to callback, get fallback if available */
        if (!callback) {
            if (!gw->prefix.size) {
                free(event);
                return false;
            }

            cmd_len = 0;
            callback = gw->fallback.cb;
        }

        /* skip blank characters after command */
        if (event->content) {
            event->content = cmd_start + cmd_len;
            while (*event->content && isspace((int)event->content[0]))
                ++event->content;
        }

        discord_refcounter_incr(client->refcounter, event,
                                _discord_message_cleanup_v, false);
        callback(client, event);
        event->content = tmp; /* retrieve original ptr */
        discord_refcounter_decr(client->refcounter, event);

        return true;
    }

    return false;
}

void
discord_gateway_dispatch(struct discord_gateway *gw,
                         enum discord_gateway_events event)
{
    switch (event) {
    case DISCORD_EV_MESSAGE_CREATE:
        if (_discord_gateway_try_command(gw)) return;
    /* fall-through */
    default: {
        if (gw->cbs[event]) {
            struct discord *client = CLIENT(gw, gw);
            void *data = calloc(1, dispatch[event].size);

            dispatch[event].from_jsmnf(gw->payload.data, gw->json, data);

            discord_refcounter_incr(client->refcounter, data,
                                    dispatch[event].cleanup, true);
            gw->cbs[event](client, data);
            discord_refcounter_decr(client->refcounter, data);
        }
    } break;
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
