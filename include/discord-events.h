/**
 * @file discord-events.h
 * @author Cogmasters
 * @brief Listen, react and trigger Discord Gateway events
 */

#ifndef DISCORD_EVENTS_H
#define DISCORD_EVENTS_H

/** @defgroup DiscordCommands Commands
 * @ingroup DiscordClient
 * @brief Requests made by the client to the Gateway socket
 *  @{ */

/**
 * @brief Request all members for a guild or a list of guilds
 * @see
 * https://discord.com/developers/docs/topics/gateway#request-guild-members
 *
 * @param client the client created with discord_init()
 * @param request request guild members information
 */
void discord_request_guild_members(
    struct discord *client, struct discord_request_guild_members *request);

/**
 * @brief Sent when a client wants to join, move or disconnect from a voice
 *      channel
 *
 * @param client the client created with discord_init()
 * @param update request guild members information
 */
void discord_update_voice_state(struct discord *client,
                                struct discord_update_voice_state *update);

/**
 * @brief Update the client presence status
 * @see discord_presence_add_activity()
 *
 * @param client the client created with discord_init()
 * @param presence status to update the client's to
 */
void discord_update_presence(struct discord *client,
                             struct discord_presence_update *presence);

/**
 * @brief Set the client presence status
 * @deprecated since v2.0.0, use discord_update_presence() instead
 * @see discord_presence_add_activity()
 *
 * @param client the client created with discord_init()
 * @param presence status to update the client's to
 */
void discord_set_presence(struct discord *client,
                          struct discord_presence_update *presence);

/** @} DiscordCommands */

/** @defgroup DiscordEvents Events
 * @ingroup DiscordClient
 * @brief Events sent over the Gateway socket to the client
 *  @{ */

/** @brief Discord Gateway's events */
enum discord_gateway_events {
    DISCORD_EV_NONE = 0, /**< missing event */
    DISCORD_EV_READY,
    DISCORD_EV_RESUMED,
    DISCORD_EV_RECONNECT,
    DISCORD_EV_INVALID_SESSION,
    DISCORD_EV_APPLICATION_COMMAND_PERMISSIONS_UPDATE,
    DISCORD_EV_AUTO_MODERATION_RULE_CREATE,
    DISCORD_EV_AUTO_MODERATION_RULE_UPDATE,
    DISCORD_EV_AUTO_MODERATION_RULE_DELETE,
    DISCORD_EV_AUTO_MODERATION_ACTION_EXECUTION,
    DISCORD_EV_CHANNEL_CREATE,
    DISCORD_EV_CHANNEL_UPDATE,
    DISCORD_EV_CHANNEL_DELETE,
    DISCORD_EV_CHANNEL_PINS_UPDATE,
    DISCORD_EV_THREAD_CREATE,
    DISCORD_EV_THREAD_UPDATE,
    DISCORD_EV_THREAD_DELETE,
    DISCORD_EV_THREAD_LIST_SYNC,
    DISCORD_EV_THREAD_MEMBER_UPDATE,
    DISCORD_EV_THREAD_MEMBERS_UPDATE,
    DISCORD_EV_GUILD_CREATE,
    DISCORD_EV_GUILD_UPDATE,
    DISCORD_EV_GUILD_DELETE,
    DISCORD_EV_GUILD_BAN_ADD,
    DISCORD_EV_GUILD_BAN_REMOVE,
    DISCORD_EV_GUILD_EMOJIS_UPDATE,
    DISCORD_EV_GUILD_STICKERS_UPDATE,
    DISCORD_EV_GUILD_INTEGRATIONS_UPDATE,
    DISCORD_EV_GUILD_MEMBER_ADD,
    DISCORD_EV_GUILD_MEMBER_REMOVE,
    DISCORD_EV_GUILD_MEMBER_UPDATE,
    DISCORD_EV_GUILD_MEMBERS_CHUNK,
    DISCORD_EV_GUILD_ROLE_CREATE,
    DISCORD_EV_GUILD_ROLE_UPDATE,
    DISCORD_EV_GUILD_ROLE_DELETE,
    DISCORD_EV_GUILD_SCHEDULED_EVENT_CREATE,
    DISCORD_EV_GUILD_SCHEDULED_EVENT_UPDATE,
    DISCORD_EV_GUILD_SCHEDULED_EVENT_DELETE,
    DISCORD_EV_GUILD_SCHEDULED_EVENT_USER_ADD,
    DISCORD_EV_GUILD_SCHEDULED_EVENT_USER_REMOVE,
    DISCORD_EV_INTEGRATION_CREATE,
    DISCORD_EV_INTEGRATION_UPDATE,
    DISCORD_EV_INTEGRATION_DELETE,
    DISCORD_EV_INTERACTION_CREATE,
    DISCORD_EV_INVITE_CREATE,
    DISCORD_EV_INVITE_DELETE,
    DISCORD_EV_MESSAGE_CREATE,
    DISCORD_EV_MESSAGE_UPDATE,
    DISCORD_EV_MESSAGE_DELETE,
    DISCORD_EV_MESSAGE_DELETE_BULK,
    DISCORD_EV_MESSAGE_REACTION_ADD,
    DISCORD_EV_MESSAGE_REACTION_REMOVE,
    DISCORD_EV_MESSAGE_REACTION_REMOVE_ALL,
    DISCORD_EV_MESSAGE_REACTION_REMOVE_EMOJI,
    DISCORD_EV_PRESENCE_UPDATE,
    DISCORD_EV_STAGE_INSTANCE_CREATE,
    DISCORD_EV_STAGE_INSTANCE_DELETE,
    DISCORD_EV_STAGE_INSTANCE_UPDATE,
    DISCORD_EV_TYPING_START,
    DISCORD_EV_USER_UPDATE,
    DISCORD_EV_VOICE_STATE_UPDATE,
    DISCORD_EV_VOICE_SERVER_UPDATE,
    DISCORD_EV_WEBHOOKS_UPDATE,
    DISCORD_EV_MAX /**< total amount of enumerators */
};

/**
 * @brief return value of discord_set_event_scheduler() callback
 * @see discord_set_event_scheduler()
 */
typedef enum discord_event_scheduler {
    /** this event has been handled */
    DISCORD_EVENT_IGNORE,
    /** handle this event in main thread */
    DISCORD_EVENT_MAIN_THREAD,
    /**
     * handle this event in a worker thread
     * @deprecated functionality will be removed in the future
     */
    DISCORD_EVENT_WORKER_THREAD
} discord_event_scheduler_t;

/**
 * @brief Event Handling Mode callback
 *
 * A very important callback that enables the user with a fine-grained control
 *        of how each event is handled: blocking, non-blocking or ignored
 * @see discord_set_event_scheduler(), @ref discord_gateway_events
 */
typedef enum discord_event_scheduler (*discord_ev_scheduler)(
    struct discord *client,
    const char data[],
    size_t size,
    enum discord_gateway_events event);

/**
 * @brief Provides control over Discord event's callback scheduler
 * @see @ref discord_event_scheduler, @ref discord_gateway_events
 *
 * Allows the user to scan the preliminary raw JSON event payload, and control
 *      whether it should trigger callbacks
 * @param client the client created_with discord_init()
 * @param fn the function that will be executed
 * @warning The user is responsible for providing their own locking mechanism
 *      to avoid race-condition on sensitive data
 */
void discord_set_event_scheduler(struct discord *client,
                                 discord_ev_scheduler callback);

/**
 * @brief Subscribe to Discord Events
 *
 * @param client the client created with discord_init()
 * @param code the intents opcode, can be set as a bitmask operation
 */
void discord_add_intents(struct discord *client, uint64_t code);

/**
 * @brief Unsubscribe from Discord Events
 *
 * @param client the client created with discord_init()
 * @param code the intents opcode, can be set as bitmask operation
 *        Ex: 1 << 0 | 1 << 1 | 1 << 4
 */
void discord_remove_intents(struct discord *client, uint64_t code);

/**
 * @brief Set a mandatory prefix before commands
 * @see discord_set_on_command()
 *
 * Example: If @a 'help' is a command and @a '!' prefix is set, the command
 *       will only be validated if @a '!help' is sent
 * @param client the client created with discord_init()
 * @param prefix the mandatory command prefix
 */
void discord_set_prefix(struct discord *client, const char prefix[]);

/** @defgroup DiscordEventsCallbacks Events callbacks
 * @brief Callback types for Discord events
 *  @{ */

/** @brief Idle callback */
typedef void (*discord_ev_idle)(struct discord *client);

/** @brief Ready callback */
typedef void (*discord_ev_ready)(struct discord *client,
                                 const struct discord_ready *event);

/** @brief Application Command Permissions callback */
typedef void (*discord_ev_application_command_permissions)(
    struct discord *client,
    const struct discord_application_command_permissions *event);

/** @brief Auto Moderation Rule callback */
typedef void (*discord_ev_auto_moderation_rule)(
    struct discord *client, const struct discord_auto_moderation_rule *event);
/** @brief Auto Moderation Action Execution callback */
typedef void (*discord_ev_auto_moderation_action_execution)(
    struct discord *client,
    const struct discord_auto_moderation_action_execution *event);

/** @brief Channel callback */
typedef void (*discord_ev_channel)(struct discord *client,
                                   const struct discord_channel *event);
/** @brief Thread List Sync callback */
typedef void (*discord_ev_thread_list_sync)(
    struct discord *client, const struct discord_thread_list_sync *event);
/** @brief Thread Member Update callback */
typedef void (*discord_ev_thread_member)(
    struct discord *client, const struct discord_thread_member *event);
/** @brief Thread Members Update callback */
typedef void (*discord_ev_thread_members_update)(
    struct discord *client, const struct discord_thread_members_update *event);
/** @brief Channel Pins Update callback */
typedef void (*discord_ev_channel_pins_update)(
    struct discord *client, const struct discord_channel_pins_update *event);

/** @brief Guild Ban Add callback */
typedef void (*discord_ev_guild_ban_add)(
    struct discord *client, const struct discord_guild_ban_add *event);
/** @brief Guild Ban Remove callback */
typedef void (*discord_ev_guild_ban_remove)(
    struct discord *client, const struct discord_guild_ban_remove *event);

/** @brief Guild callback */
typedef void (*discord_ev_guild)(struct discord *client,
                                 const struct discord_guild *event);
/** @brief Guild Emojis Update callback */
typedef void (*discord_ev_guild_emojis_update)(
    struct discord *client, const struct discord_guild_emojis_update *event);
/** @brief Guild Stickers Update callback */
typedef void (*discord_ev_guild_stickers_update)(
    struct discord *client, const struct discord_guild_stickers_update *event);
/** @brief Guild Integrations Update callback */
typedef void (*discord_ev_guild_integrations_update)(
    struct discord *client,
    const struct discord_guild_integrations_update *event);
/** @brief Guild Member Add callback */
typedef void (*discord_ev_guild_member)(
    struct discord *client, const struct discord_guild_member *event);
/** @brief Guild Member Remove callback */
typedef void (*discord_ev_guild_member_remove)(
    struct discord *client, const struct discord_guild_member_remove *event);
/** @brief Guild Member Update callback */
typedef void (*discord_ev_guild_member_update)(
    struct discord *client, const struct discord_guild_member_update *event);
/** @brief Guild Members Chunk callback */
typedef void (*discord_ev_guild_members_chunk)(
    struct discord *client, const struct discord_guild_members_chunk *event);
/** @brief Guild Role Create callback */
typedef void (*discord_ev_guild_role_create)(
    struct discord *client, const struct discord_guild_role_create *event);
/** @brief Guild Role Update callback */
typedef void (*discord_ev_guild_role_update)(
    struct discord *client, const struct discord_guild_role_update *event);
/** @brief Guild Role Delete callback */
typedef void (*discord_ev_guild_role_delete)(
    struct discord *client, const struct discord_guild_role_delete *event);

/** @brief Guild Scheduled Event callback */
typedef void (*discord_ev_guild_scheduled_event)(
    struct discord *client, const struct discord_guild_scheduled_event *event);
/** @brief Guild Scheduled Event User Add callback */
typedef void (*discord_ev_guild_scheduled_event_user_add)(
    struct discord *client,
    const struct discord_guild_scheduled_event_user_add *event);
/** @brief Guild Scheduled Event User Remove callback */
typedef void (*discord_ev_guild_scheduled_event_user_remove)(
    struct discord *client,
    const struct discord_guild_scheduled_event_user_remove *event);

/** @brief Integration Create callback */
typedef void (*discord_ev_integration)(
    struct discord *client, const struct discord_integration *event);

/** @brief Integration Delete callback */
typedef void (*discord_ev_integration_delete)(
    struct discord *client, const struct discord_integration_delete *event);

/** @brief Invite Create Event callback */
typedef void (*discord_ev_invite_create)(
    struct discord *client, const struct discord_invite_create *event);
/** @brief Invite Delete Event callback */
typedef void (*discord_ev_invite_delete)(
    struct discord *client, const struct discord_invite_delete *event);

/** @brief Message callback */
typedef void (*discord_ev_message)(struct discord *client,
                                   const struct discord_message *event);
/** @brief Message Delete callback */
typedef void (*discord_ev_message_delete)(
    struct discord *client, const struct discord_message_delete *event);
/** @brief Message Delete Bulk callback */
typedef void (*discord_ev_message_delete_bulk)(
    struct discord *client, const struct discord_message_delete_bulk *event);
/** @brief Message Reaction Add callback */
typedef void (*discord_ev_message_reaction_add)(
    struct discord *client, const struct discord_message_reaction_add *member);
/** @brief Message Reaction Remove callback */
typedef void (*discord_ev_message_reaction_remove)(
    struct discord *client,
    const struct discord_message_reaction_remove *member);
/** @brief Message Reaction Remove All callback */
typedef void (*discord_ev_message_reaction_remove_all)(
    struct discord *client,
    const struct discord_message_reaction_remove_all *event);
/** @brief Message Reaction Remove callback */
typedef void (*discord_ev_message_reaction_remove_emoji)(
    struct discord *client,
    const struct discord_message_reaction_remove_emoji *event);

/** @brief Presence Update callback */
typedef void (*discord_ev_presence_update)(
    struct discord *client, const struct discord_presence_update *event);

/** @brief Stage Instance callback */
typedef void (*discord_ev_stage_instance)(
    struct discord *client, const struct discord_stage_instance *event);

/** @brief Typing Start callback */
typedef void (*discord_ev_typing_start)(
    struct discord *client, const struct discord_typing_start *event);

/** @brief User callback */
typedef void (*discord_ev_user)(struct discord *client,
                                const struct discord_user *event);

/** @brief Voice State Update callback */
typedef void (*discord_ev_voice_state_update)(
    struct discord *client, const struct discord_voice_state *event);
/** @brief Voice Server Update callback */
typedef void (*discord_ev_voice_server_update)(
    struct discord *client, const struct discord_voice_server_update *event);

/** @brief Webhooks Update callback */
typedef void (*discord_ev_webhooks_update)(
    struct discord *client, const struct discord_webhooks_update *event);

/** @brief Interaction callback */
typedef void (*discord_ev_interaction)(
    struct discord *client, const struct discord_interaction *event);

/** @} DiscordEventsCallbacks */

/**
 * @brief Set command/callback pair
 *
 * The callback is triggered when a user types the assigned command in a
 *        chat visible to the client
 * @param client the client created with discord_init()
 * @param command the command to trigger the callback
 * @param callback the callback to be triggered on event
 * @note The command and any subjacent empty space is left out of
 *       the message content
 */
void discord_set_on_command(struct discord *client,
                            char *command,
                            discord_ev_message callback);

/**
 * @brief Set a variadic series of NULL terminated commands to a callback
 *
 * The callback is triggered when a user types one of the assigned commands in
 *        a chat visble to the client
 * @param client the client created with discord_init()
 * @param commands array of commands to trigger the callback
 * @param amount amount of commands provided
 * @param callback the callback to be triggered on event
 * @note The command and any subjacent empty space is left out of
 *       the message content
 */
void discord_set_on_commands(struct discord *client,
                             char *const commands[],
                             int amount,
                             discord_ev_message callback);

/**
 * @brief Set the time for wakeup function to be called
 * @see discord_set_on_wakeup
 *
 * @param delay time to delay in milliseconds, or -1 to disable
 */
void discord_set_next_wakeup(struct discord *client, int64_t delay);

/**
 * @brief Triggered at a arbitrary interval value set at
 *      discord_set_next_wakeup()
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_wakeup(struct discord *client, discord_ev_idle callback);

/**
 * @brief Triggers when idle
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_idle(struct discord *client, discord_ev_idle callback);

/**
 * @brief Triggers once per event-loop cycle
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_cycle(struct discord *client, discord_ev_idle callback);

/**
 * @brief Triggers when the client session is ready
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_ready(struct discord *client, discord_ev_ready callback);

/**
 * @brief Triggers when an application command permission is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_application_command_permissions_update(
    struct discord *client,
    discord_ev_application_command_permissions callback);

/**
 * @brief Triggers when an auto moderation rule is created
 * @note This implicitly sets
 *      @ref DISCORD_GATEWAY_AUTO_MODERATION_CONFIGURATION intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_auto_moderation_rule_create(
    struct discord *client, discord_ev_auto_moderation_rule callback);

/**
 * @brief Triggers when an auto moderation rule is updated
 * @note This implicitly sets
 *      @ref DISCORD_GATEWAY_AUTO_MODERATION_CONFIGURATION intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_auto_moderation_rule_update(
    struct discord *client, discord_ev_auto_moderation_rule callback);

/**
 * @brief Triggers when an auto moderation rule is deleted
 * @note This implicitly sets
 *      @ref DISCORD_GATEWAY_AUTO_MODERATION_CONFIGURATION intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_auto_moderation_rule_delete(
    struct discord *client, discord_ev_auto_moderation_rule callback);

/**
 * @brief Triggers when an auto moderation rule is triggered and an execution
 *      is executed (e.g a message was blocked)
 * @note This implicitly sets @ref DISCORD_GATEWAY_AUTO_MODERATION_EXECUTION
 *      intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_auto_moderation_action_execution(
    struct discord *client,
    discord_ev_auto_moderation_action_execution callback);

/**
 * @brief Triggers when a channel is created
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_channel_create(struct discord *client,
                                   discord_ev_channel callback);

/**
 * @brief Triggers when a channel is updated
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_channel_update(struct discord *client,
                                   discord_ev_channel callback);

/**
 * @brief Triggers when a channel is deleted
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_channel_delete(struct discord *client,
                                   discord_ev_channel callback);

/**
 * @brief Triggers when a channel pin is updated
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS and
 *      @ref DISCORD_GATEWAY_DIRECT_MESSAGES intents
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_channel_pins_update(
    struct discord *client, discord_ev_channel_pins_update callback);

/**
 * @brief Triggers when a thread is created
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_thread_create(struct discord *client,
                                  discord_ev_channel callback);

/**
 * @brief Triggers when a thread is updated
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_thread_update(struct discord *client,
                                  discord_ev_channel callback);

/**
 * @brief Triggers when a thread is deleted
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_thread_delete(struct discord *client,
                                  discord_ev_channel callback);

/**
 * @brief Triggers when the current user gains access to a channel
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_thread_list_sync(struct discord *client,
                                     discord_ev_thread_list_sync callback);

/**
 * @brief Triggers when a thread the bot is in gets updated
 * @note For bots, this event largely is just a signal that you are a member of
 *      the thread
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_thread_member_update(struct discord *client,
                                         discord_ev_thread_member callback);

/**
 * @brief Triggers when someone is added or removed from a thread
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS and
 *      @ref DISCORD_GATEWAY_GUILD_MEMBERS intents
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_thread_members_update(
    struct discord *client, discord_ev_thread_members_update callback);

/**
 * @brief Triggers when a guild is created
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_create(struct discord *client,
                                 discord_ev_guild callback);

/**
 * @brief Triggers when a guild is updated
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_update(struct discord *client,
                                 discord_ev_guild callback);

/**
 * @brief Triggers when a guild is deleted
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_delete(struct discord *client,
                                 discord_ev_guild callback);

/**
 * @brief Triggers when a user is banned from a guild
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_BANS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_ban_add(struct discord *client,
                                  discord_ev_guild_ban_add callback);

/**
 * @brief Triggers when a user is unbanned from a guild
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_BANS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_ban_remove(struct discord *client,
                                     discord_ev_guild_ban_remove callback);

/**
 * @brief Triggers when a guild emojis are updated
 * @note This implicitly sets
 *      @ref DISCORD_GATEWAY_GUILD_EMOJIS_AND_STICKERS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_emojis_update(
    struct discord *client, discord_ev_guild_emojis_update callback);

/**
 * @brief Triggers when a guild stickers are updated
 * @note This implicitly sets
 *      @ref DISCORD_GATEWAY_GUILD_EMOJIS_AND_STICKERS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_stickers_update(
    struct discord *client, discord_ev_guild_stickers_update callback);

/**
 * @brief Triggers when a guild integrations are updated
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_INTEGRATIONS
 *      intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_integrations_update(
    struct discord *client, discord_ev_guild_integrations_update callback);

/**
 * @brief Triggers when a guild member is added
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_MEMBERS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_member_add(struct discord *client,
                                     discord_ev_guild_member callback);

/**
 * @brief Triggers when a guild member is updated
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_MEMBERS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_member_update(
    struct discord *client, discord_ev_guild_member_update callback);

/**
 * @brief Triggers when a guild member is removed
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_MEMBERS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_member_remove(
    struct discord *client, discord_ev_guild_member_remove callback);

/**
 * @brief Triggers in response to discord_request_guild_members()
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_members_chunk(
    struct discord *client, discord_ev_guild_members_chunk callback);

/**
 * @brief Triggers when a guild role is created
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_role_create(struct discord *client,
                                      discord_ev_guild_role_create callback);

/**
 * @brief Triggers when a guild role is updated
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_role_update(struct discord *client,
                                      discord_ev_guild_role_update callback);

/**
 * @brief Triggers when a guild role is deleted
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_role_delete(struct discord *client,
                                      discord_ev_guild_role_delete callback);

/**
 * @brief Triggers when a guild scheduled event is created
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_SCHEDULED_EVENTS
 * intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_scheduled_event_create(
    struct discord *client, discord_ev_guild_scheduled_event callback);

/**
 * @brief Triggers when a guild scheduled event is updated
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_SCHEDULED_EVENTS
 * intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_scheduled_event_update(
    struct discord *client, discord_ev_guild_scheduled_event callback);

/**
 * @brief Triggers when a guild scheduled event is deleted
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_SCHEDULED_EVENTS
 * intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_scheduled_event_delete(
    struct discord *client, discord_ev_guild_scheduled_event callback);

/**
 * @brief Triggers when a user subscribes to a guild scheduled event
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_SCHEDULED_EVENTS
 * intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_scheduled_event_user_add(
    struct discord *client,
    discord_ev_guild_scheduled_event_user_add callback);

/**
 * @brief Triggers when a user unsubscribes from a guild scheduled event
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_SCHEDULED_EVENTS
 * intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_scheduled_event_user_remove(
    struct discord *client,
    discord_ev_guild_scheduled_event_user_remove callback);

/**
 * @brief Triggers when a guild integration is created
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_INTEGRATIONS
 * intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_integration_create(struct discord *client,
                                       discord_ev_integration callback);

/**
 * @brief Triggers when a guild integration is updated
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_INTEGRATIONS
 * intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_integration_update(struct discord *client,
                                       discord_ev_integration callback);

/**
 * @brief Triggers when a guild integration is deleted
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_INTEGRATIONS
 *      intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_integration_delete(struct discord *client,
                                       discord_ev_integration_delete callback);

/**
 * @brief Triggers when user has used an interaction, such as an application
 *      command
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_interaction_create(struct discord *client,
                                       discord_ev_interaction callback);

/**
 * @brief Triggers when an invite to a channel has been created
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_INVITES intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_invite_create(struct discord *client,
                                  discord_ev_invite_create callback);

/**
 * @brief Triggers when an invite to a channel has been deleted
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_INVITES intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_invite_delete(struct discord *client,
                                  discord_ev_invite_delete callback);

/**
 * @brief Triggers when a message is created
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_MESSAGES and
 *      @ref DISCORD_GATEWAY_DIRECT_MESSAGES intents
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_create(struct discord *client,
                                   discord_ev_message callback);

/**
 * @brief Triggers when a message is updated
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_MESSAGES and
 *      @ref DISCORD_GATEWAY_DIRECT_MESSAGES intents
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_update(struct discord *client,
                                   discord_ev_message callback);

/**
 * @brief Triggers when a message is deleted
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_MESSAGES and
 *      @ref DISCORD_GATEWAY_DIRECT_MESSAGES intents
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_delete(struct discord *client,
                                   discord_ev_message_delete callback);

/**
 * @brief Triggers when messages are deleted in bulk
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_MESSAGES
 *      intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_delete_bulk(
    struct discord *client, discord_ev_message_delete_bulk callback);

/**
 * @brief Triggers when a message reaction is added
 * @note This implicitly sets
 *      @ref DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS and
 *      @ref DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS intents
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_reaction_add(
    struct discord *client, discord_ev_message_reaction_add callback);

/**
 * @brief Triggers when a message reaction is removed
 * @note This implicitly sets
 *      @ref DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS and
 *      @ref DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS intents
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_reaction_remove(
    struct discord *client, discord_ev_message_reaction_remove callback);

/**
 * @brief Triggers when all message reactions are removed
 * @note This implicitly sets
 *      @ref DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS and
 *      @ref DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS intents
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_reaction_remove_all(
    struct discord *client, discord_ev_message_reaction_remove_all callback);
/** @brief Triggers when all instances of a particular reaction from some
 *        message is removed */

/**
 * @brief Triggers when all instances of a particular reaction is removed from
 *      a message
 * @note This implicitly sets
 *      @ref DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS and
 *      @ref DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS intents
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_reaction_remove_emoji(
    struct discord *client, discord_ev_message_reaction_remove_emoji callback);

/**
 * @brief Triggers when user presence is updated
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_PRESENCES intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_presence_update(struct discord *client,
                                    discord_ev_presence_update callback);

/**
 * @brief Triggers when a stage instance is created
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_stage_instance_create(struct discord *client,
                                          discord_ev_stage_instance callback);

/**
 * @brief Triggers when a stage instance is updated
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_stage_instance_update(struct discord *client,
                                          discord_ev_stage_instance callback);

/**
 * @brief Triggers when a stage instance is deleted
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILDS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_stage_instance_delete(struct discord *client,
                                          discord_ev_stage_instance callback);

/**
 * @brief Triggers when user starts typing in a channel
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_MESSAGE_TYPING and
 *      @ref DISCORD_GATEWAY_DIRECT_MESSAGE_TYPING intents
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_typing_start(struct discord *client,
                                 discord_ev_typing_start callback);

/**
 * @brief Triggers when properties about a user changed
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_user_update(struct discord *client,
                                discord_ev_user callback);

/**
 * @brief Triggers when a voice state is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_voice_state_update(struct discord *client,
                                       discord_ev_voice_state_update callback);

/**
 * @brief Triggers when voice server is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_voice_server_update(
    struct discord *client, discord_ev_voice_server_update callback);

/**
 * @brief Triggers when guild channel has been created, updated or deleted
 * @note This implicitly sets @ref DISCORD_GATEWAY_GUILD_WEBHOOKS intent
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_webhooks_update(struct discord *client,
                                    discord_ev_webhooks_update callback);

/** @} DiscordEvents */

#endif /* DISCORD_EVENTS_H */
