/**
 * @file discord-events.h
 * @author Cogmasters
 * @brief Listen and react to Discord events
 */

#ifndef DISCORD_EVENTS_H
#define DISCORD_EVENTS_H

/** @defgroup DiscordEvent Events
 *  @ingroup Discord
 * @brief The Discord public Events API supported by Concord
 *  @{ */

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
 *
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

/** @defgroup DiscordEventCallbackTypes Callback types
 * @brief Callback types for Discord events
 *  @{ */

/** @brief Idle callback */
typedef void (*discord_ev_idle)(struct discord *client);

/** @brief Ready callback */
typedef void (*discord_ev_ready)(struct discord *client,
                                 const struct discord_ready *event);

/** @brief Application Command callback */
typedef void (*discord_ev_application_command)(
    struct discord *client, const struct discord_application_command *event);

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

/** @} DiscordEventCallbackTypes */

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
 * @brief Triggers when the client is ready
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_ready(struct discord *client, discord_ev_ready callback);

/**
 * @brief Triggers when a application command is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_application_command_create(
    struct discord *client, discord_ev_application_command callback);

/**
 * @brief Triggers when a application command is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_application_command_update(
    struct discord *client, discord_ev_application_command callback);

/**
 * @brief Triggers when a application command is deleted
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_application_command_delete(
    struct discord *client, discord_ev_application_command callback);

/**
 * @brief Triggers when a channel is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_channel_create(struct discord *client,
                                   discord_ev_channel callback);

/**
 * @brief Triggers when a channel is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_channel_update(struct discord *client,
                                   discord_ev_channel callback);

/**
 * @brief Triggers when a channel is deleted
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_channel_delete(struct discord *client,
                                   discord_ev_channel callback);

/**
 * @brief Triggers when a channel pin is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_channel_pins_update(
    struct discord *client, discord_ev_channel_pins_update callback);

/**
 * @brief Triggers when a thread is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_thread_create(struct discord *client,
                                  discord_ev_channel callback);

/**
 * @brief Triggers when a thread is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_thread_update(struct discord *client,
                                  discord_ev_channel callback);

/**
 * @brief Triggers when a thread is deleted
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_thread_delete(struct discord *client,
                                  discord_ev_channel callback);

/**
 * @brief Triggers when a guild is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_create(struct discord *client,
                                 discord_ev_guild callback);

/**
 * @brief Triggers when a guild is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_update(struct discord *client,
                                 discord_ev_guild callback);

/**
 * @brief Triggers when a guild is deleted
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_delete(struct discord *client,
                                 discord_ev_guild callback);

/**
 * @brief Triggers when a guild role is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_role_create(struct discord *client,
                                      discord_ev_guild_role_create callback);

/**
 * @brief Triggers when a guild role is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_role_update(struct discord *client,
                                      discord_ev_guild_role_update callback);

/**
 * @brief Triggers when a guild role is deleted
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_role_delete(struct discord *client,
                                      discord_ev_guild_role_delete callback);

/**
 * @brief Triggers when a guild member is added
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_member_add(struct discord *client,
                                     discord_ev_guild_member callback);

/**
 * @brief Triggers when a guild member is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_member_update(
    struct discord *client, discord_ev_guild_member_update callback);

/**
 * @brief Triggers when a guild member is removed
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_member_remove(
    struct discord *client, discord_ev_guild_member_remove callback);

/**
 * @brief Triggers when a guild ban is added
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_ban_add(struct discord *client,
                                  discord_ev_guild_ban_add callback);

/**
 * @brief Triggers when a guild ban is removed
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_guild_ban_remove(struct discord *client,
                                     discord_ev_guild_ban_remove callback);

/**
 * @brief Triggers when a interaction is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_interaction_create(struct discord *client,
                                       discord_ev_interaction callback);

/**
 * @brief Triggers when a message is created
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_create(struct discord *client,
                                   discord_ev_message callback);

/**
 * @brief Triggers when a message is updated
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_update(struct discord *client,
                                   discord_ev_message callback);

/**
 * @brief Triggers when a message is deleted
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_delete(struct discord *client,
                                   discord_ev_message_delete callback);

/**
 * @brief Triggers when messages are deleted in bulk
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_delete_bulk(
    struct discord *client, discord_ev_message_delete_bulk callback);

/**
 * @brief Triggers when a message reaction is added
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_reaction_add(
    struct discord *client, discord_ev_message_reaction_add callback);

/**
 * @brief Triggers when a message reaction is removed
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_reaction_remove(
    struct discord *client, discord_ev_message_reaction_remove callback);

/**
 * @brief Triggers when all message reactions are removed
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
 *
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 */
void discord_set_on_message_reaction_remove_emoji(
    struct discord *client, discord_ev_message_reaction_remove_emoji callback);

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

/** @} DiscordEvent */

#endif /* DISCORD_EVENTS_H */
