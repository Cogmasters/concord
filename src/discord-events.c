#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"

void
discord_shutdown(struct discord *client)
{
    if (client->gw.session->status != DISCORD_SESSION_SHUTDOWN)
        discord_gateway_shutdown(&client->gw);
}

void
discord_reconnect(struct discord *client, bool resume)
{
    discord_gateway_reconnect(&client->gw, resume);
}

void
discord_request_guild_members(struct discord *client,
                              struct discord_request_guild_members *request)
{
    ASSERT_S(client->gw.cbs[DISCORD_EV_GUILD_MEMBERS_CHUNK] != NULL,
             "Missing callback for discord_set_on_guild_members_chunk()");
    discord_gateway_send_request_guild_members(&client->gw, request);
}

void
discord_update_voice_state(struct discord *client,
                           struct discord_update_voice_state *update)
{
    discord_gateway_send_update_voice_state(&client->gw, update);
}

void
discord_update_presence(struct discord *client,
                        struct discord_presence_update *presence)
{
    discord_gateway_send_presence_update(&client->gw, presence);
}

/* deprecated, use discord_update_presence() instead */
void
discord_set_presence(struct discord *client,
                     struct discord_presence_update *presence)
{
    discord_update_presence(client, presence);
}

void
discord_add_intents(struct discord *client, uint64_t code)
{
    if (WS_CONNECTED == ws_get_status(client->gw.ws)) {
        logconf_error(&client->conf, "Can't set intents to a running client.");
        return;
    }

    client->gw.id.intents |= code;
}

void
discord_remove_intents(struct discord *client, uint64_t code)
{
    if (WS_CONNECTED == ws_get_status(client->gw.ws)) {
        logconf_error(&client->conf,
                      "Can't remove intents from a running client.");
        return;
    }

    client->gw.id.intents &= ~code;
}

void
discord_set_prefix(struct discord *client, const char prefix[])
{
    if (!prefix || !*prefix) return;

    discord_message_commands_set_prefix(&client->commands, prefix,
                                        strlen(prefix));
}

void
discord_set_on_command(struct discord *client,
                       char command[],
                       discord_ev_message callback)
{
    size_t length = (!command || !*command) ? 0 : strlen(command);

    discord_message_commands_append(&client->commands, command, length,
                                    callback);
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_commands(struct discord *client,
                        char *const commands[],
                        int amount,
                        discord_ev_message callback)
{
    for (int i = 0; i < amount; ++i)
        discord_set_on_command(client, commands[i], callback);
}

void
discord_set_event_scheduler(struct discord *client,
                            discord_ev_scheduler callback)
{
    client->gw.scheduler = callback;
}

void
discord_set_on_ready(struct discord *client, discord_ev_ready callback)
{
    client->gw.cbs[DISCORD_EV_READY] = (discord_ev)callback;
}

void
discord_set_on_application_command_permissions_update(
    struct discord *client,
    discord_ev_application_command_permissions callback)
{
    client->gw.cbs[DISCORD_EV_APPLICATION_COMMAND_PERMISSIONS_UPDATE] =
        (discord_ev)callback;
}

void
discord_set_on_channel_create(struct discord *client,
                              discord_ev_channel callback)
{
    client->gw.cbs[DISCORD_EV_CHANNEL_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_channel_update(struct discord *client,
                              discord_ev_channel callback)
{
    client->gw.cbs[DISCORD_EV_CHANNEL_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_channel_delete(struct discord *client,
                              discord_ev_channel callback)
{
    client->gw.cbs[DISCORD_EV_CHANNEL_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_channel_pins_update(struct discord *client,
                                   discord_ev_channel_pins_update callback)
{
    client->gw.cbs[DISCORD_EV_CHANNEL_PINS_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_thread_create(struct discord *client,
                             discord_ev_channel callback)
{
    client->gw.cbs[DISCORD_EV_THREAD_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_update(struct discord *client,
                             discord_ev_channel callback)
{
    client->gw.cbs[DISCORD_EV_THREAD_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_delete(struct discord *client,
                             discord_ev_channel callback)
{
    client->gw.cbs[DISCORD_EV_THREAD_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_list_sync(struct discord *client,
                                discord_ev_thread_list_sync callback)
{
    client->gw.cbs[DISCORD_EV_THREAD_LIST_SYNC] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_member_update(struct discord *client,
                                    discord_ev_thread_member callback)
{
    client->gw.cbs[DISCORD_EV_THREAD_MEMBER_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_members_update(struct discord *client,
                                     discord_ev_thread_members_update callback)
{
    client->gw.cbs[DISCORD_EV_THREAD_MEMBERS_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS
                                    | DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_create(struct discord *client, discord_ev_guild callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_update(struct discord *client, discord_ev_guild callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_delete(struct discord *client, discord_ev_guild callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_ban_add(struct discord *client,
                             discord_ev_guild_ban_add callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_BAN_ADD] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_BANS);
}

void
discord_set_on_guild_ban_remove(struct discord *client,
                                discord_ev_guild_ban_remove callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_BAN_REMOVE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_BANS);
}

void
discord_set_on_guild_emojis_update(struct discord *client,
                                   discord_ev_guild_emojis_update callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_EMOJIS_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_EMOJIS_AND_STICKERS);
}

void
discord_set_on_guild_stickers_update(struct discord *client,
                                     discord_ev_guild_stickers_update callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_STICKERS_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_EMOJIS_AND_STICKERS);
}

void
discord_set_on_guild_integrations_update(
    struct discord *client, discord_ev_guild_integrations_update callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_INTEGRATIONS_UPDATE] =
        (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_INTEGRATIONS);
}

void
discord_set_on_guild_member_add(struct discord *client,
                                discord_ev_guild_member callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_MEMBER_ADD] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_member_update(struct discord *client,
                                   discord_ev_guild_member_update callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_MEMBER_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_member_remove(struct discord *client,
                                   discord_ev_guild_member_remove callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_MEMBER_REMOVE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_members_chunk(struct discord *client,
                                   discord_ev_guild_members_chunk callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_MEMBERS_CHUNK] = (discord_ev)callback;
}

void
discord_set_on_guild_role_create(struct discord *client,
                                 discord_ev_guild_role_create callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_ROLE_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_role_update(struct discord *client,
                                 discord_ev_guild_role_update callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_ROLE_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_role_delete(struct discord *client,
                                 discord_ev_guild_role_delete callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_ROLE_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_scheduled_event_create(
    struct discord *client, discord_ev_guild_scheduled_event callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_SCHEDULED_EVENT_CREATE] =
        (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_SCHEDULED_EVENTS);
}

void
discord_set_on_guild_scheduled_event_update(
    struct discord *client, discord_ev_guild_scheduled_event callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_SCHEDULED_EVENT_UPDATE] =
        (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_SCHEDULED_EVENTS);
}

void
discord_set_on_guild_scheduled_event_delete(
    struct discord *client, discord_ev_guild_scheduled_event callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_SCHEDULED_EVENT_DELETE] =
        (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_SCHEDULED_EVENTS);
}

void
discord_set_on_guild_scheduled_event_user_add(
    struct discord *client, discord_ev_guild_scheduled_event_user_add callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_SCHEDULED_EVENT_USER_ADD] =
        (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_SCHEDULED_EVENTS);
}

void
discord_set_on_guild_scheduled_event_user_remove(
    struct discord *client,
    discord_ev_guild_scheduled_event_user_remove callback)
{
    client->gw.cbs[DISCORD_EV_GUILD_SCHEDULED_EVENT_USER_REMOVE] =
        (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_SCHEDULED_EVENTS);
}

void
discord_set_on_integration_create(struct discord *client,
                                  discord_ev_integration callback)
{
    client->gw.cbs[DISCORD_EV_INTEGRATION_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_INTEGRATIONS);
}

void
discord_set_on_integration_update(struct discord *client,
                                  discord_ev_integration callback)
{
    client->gw.cbs[DISCORD_EV_INTEGRATION_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_INTEGRATIONS);
}

void
discord_set_on_integration_delete(struct discord *client,
                                  discord_ev_integration_delete callback)
{
    client->gw.cbs[DISCORD_EV_INTEGRATION_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_INTEGRATIONS);
}

void
discord_set_on_interaction_create(struct discord *client,
                                  discord_ev_interaction callback)
{
    client->gw.cbs[DISCORD_EV_INTERACTION_CREATE] = (discord_ev)callback;
}

void
discord_set_on_invite_create(struct discord *client,
                             discord_ev_invite_create callback)
{
    client->gw.cbs[DISCORD_EV_INVITE_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_INVITES);
}

void
discord_set_on_invite_delete(struct discord *client,
                             discord_ev_invite_delete callback)
{
    client->gw.cbs[DISCORD_EV_INVITE_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_INVITES);
}

void
discord_set_on_message_create(struct discord *client,
                              discord_ev_message callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_update(struct discord *client,
                              discord_ev_message callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_delete(struct discord *client,
                              discord_ev_message_delete callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                    | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_delete_bulk(struct discord *client,
                                   discord_ev_message_delete_bulk callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_DELETE_BULK] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES);
}

void
discord_set_on_message_reaction_add(struct discord *client,
                                    discord_ev_message_reaction_add callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_REACTION_ADD] = (discord_ev)callback;
    discord_add_intents(client,
                        DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                            | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove(
    struct discord *client, discord_ev_message_reaction_remove callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_REACTION_REMOVE] = (discord_ev)callback;
    discord_add_intents(client,
                        DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                            | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove_all(
    struct discord *client, discord_ev_message_reaction_remove_all callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_REACTION_REMOVE_ALL] =
        (discord_ev)callback;
    discord_add_intents(client,
                        DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                            | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove_emoji(
    struct discord *client, discord_ev_message_reaction_remove_emoji callback)
{
    client->gw.cbs[DISCORD_EV_MESSAGE_REACTION_REMOVE_EMOJI] =
        (discord_ev)callback;
    discord_add_intents(client,
                        DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                            | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_presence_update(struct discord *client,
                               discord_ev_presence_update callback)
{
    client->gw.cbs[DISCORD_EV_PRESENCE_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_PRESENCES);
}

void
discord_set_on_stage_instance_create(struct discord *client,
                                     discord_ev_stage_instance callback)
{
    client->gw.cbs[DISCORD_EV_STAGE_INSTANCE_CREATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_stage_instance_update(struct discord *client,
                                     discord_ev_stage_instance callback)
{
    client->gw.cbs[DISCORD_EV_STAGE_INSTANCE_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_stage_instance_delete(struct discord *client,
                                     discord_ev_stage_instance callback)
{
    client->gw.cbs[DISCORD_EV_STAGE_INSTANCE_DELETE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_typing_start(struct discord *client,
                            discord_ev_typing_start callback)
{
    client->gw.cbs[DISCORD_EV_TYPING_START] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_TYPING
                                    | DISCORD_GATEWAY_DIRECT_MESSAGE_TYPING);
}

void
discord_set_on_user_update(struct discord *client, discord_ev_user callback)
{
    client->gw.cbs[DISCORD_EV_USER_UPDATE] = (discord_ev)callback;
}

void
discord_set_on_voice_state_update(struct discord *client,
                                  discord_ev_voice_state_update callback)
{
    client->gw.cbs[DISCORD_EV_VOICE_STATE_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

void
discord_set_on_voice_server_update(struct discord *client,
                                   discord_ev_voice_server_update callback)
{
    client->gw.cbs[DISCORD_EV_VOICE_SERVER_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

void
discord_set_on_webhooks_update(struct discord *client,
                               discord_ev_webhooks_update callback)
{
    client->gw.cbs[DISCORD_EV_WEBHOOKS_UPDATE] = (discord_ev)callback;
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_WEBHOOKS);
}
