/**
 * @file gateway.h
 * @author Cogmasters
 * @brief Gateway public functions and datatypes
 */

#ifndef DISCORD_GATEWAY_H
#define DISCORD_GATEWAY_H

/******************************************************************************
 * Custom functions
 ******************************************************************************/

/**
 * @brief Disconnect a member from voice channel
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild the member belongs to
 * @param user_id the user to be disconnected
 * @CCORD_ret_obj{ret,guild_member}
 * @CCORD_return
 */
CCORDcode discord_disconnect_guild_member(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake user_id,
    struct discord_ret_guild_member *ret);

/******************************************************************************
 * Builder functions
 ******************************************************************************/

/**
 * @brief Helper function to add presence activities
 * @see discord_set_presence()
 *
 * This function is a wrapper over ntl_append2()
 */
void discord_presence_add_activity(struct discord_presence_update *presence,
                                   struct discord_activity *activity);

/******************************************************************************
 * Discord API functions
 ******************************************************************************/

/**
 * @brief Get a single valid WSS URL, which the client can use for connecting
 * @note This route should be cached, and only call the function again if
 *        unable to properly establishing a connection with the cached version
 * @warning This function blocks the running thread
 *
 * @param client the client created with discord_init()
 * @param ret if successful, a @ref sized_buffer containing the JSON response
 * @param ret a sized buffer containing the response JSON
 * @CCORD_return
 */
CCORDcode discord_get_gateway(struct discord *client,
                              struct sized_buffer *ret);

/**
 * @brief Get a single valid WSS URL, and additional metadata that can help
 *        during the operation of large bots.
 * @note This route should not be cached for extended periods of time as the
 *        value is not guaranteed to be the same per-call, and changes as the
 *        bot joins/leaves guilds
 * @warning This function blocks the running thread
 *
 * @param client the client created with discord_init()
 * @param ret if successful, a @ref sized_buffer containing the JSON response
 * @param ret a sized buffer containing the response JSON
 * @CCORD_return
 */
CCORDcode discord_get_gateway_bot(struct discord *client,
                                  struct sized_buffer *ret);

/******************************************************************************
 * Discord Gateway Events
 ******************************************************************************/

/**
 * @brief return value of discord_set_event_scheduler() callback
 * @see discord_set_event_scheduler()
 */
typedef enum discord_event_scheduler {
    /** this event has been handled */
    DISCORD_EVENT_IGNORE,
    /** handle this event in main thread */
    DISCORD_EVENT_MAIN_THREAD,
    /** handle this event in a worker thread */
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
    struct sized_buffer *event_data,
    enum discord_gateway_events event);

/**
 * @brief Provides the user with a fine-grained control of the Discord's
 *       event-loop
 *
 * Allows the user to specify which events should be executed from the
 *       main-thread, in parallel from a worker-thread, or completely ignored
 *
 * @param client the client created_with discord_init()
 * @param fn the function that will be executed
 * @warning The user is responsible for providing his own locking mechanism to
 *       avoid race-condition on sensitive data
 * @see @ref discord_event_scheduler, @ref discord_gateway_events
 */
void discord_set_event_scheduler(struct discord *client,
                                 discord_ev_scheduler callback);

/** @defgroup DiscordCallbackTypes
 *  @{ */

typedef void (*discord_ev_idle)(struct discord *client);
typedef void (*discord_ev_application_command)(
    struct discord *client, const struct discord_application_command *app_cmd);
typedef void (*discord_ev_channel)(struct discord *client,
                                   const struct discord_channel *channel);
typedef void (*discord_ev_channel_pins_update)(struct discord *client,
                                               u64snowflake guild_id,
                                               u64snowflake channel_id,
                                               u64unix_ms last_pin_timestamp);
typedef void (*discord_ev_guild)(struct discord *client,
                                 const struct discord_guild *guild);
typedef void (*discord_ev_guild_delete)(struct discord *client,
                                        u64snowflake guild_id);
typedef void (*discord_ev_guild_role)(struct discord *client,
                                      u64snowflake guild_id,
                                      const struct discord_role *role);
typedef void (*discord_ev_guild_role_delete)(struct discord *client,
                                             u64snowflake guild_id,
                                             u64snowflake role_id);
typedef void (*discord_ev_guild_member)(
    struct discord *client,
    u64snowflake guild_id,
    const struct discord_guild_member *member);
typedef void (*discord_ev_guild_member_remove)(
    struct discord *client,
    u64snowflake guild_id,
    const struct discord_user *user);
typedef void (*discord_ev_guild_ban)(struct discord *client,
                                     u64snowflake guild_id,
                                     const struct discord_user *user);
typedef void (*discord_ev_interaction)(
    struct discord *client, const struct discord_interaction *interaction);
typedef void (*discord_ev_message)(struct discord *client,
                                   const struct discord_message *message);
typedef void (*discord_ev_message_delete)(struct discord *client,
                                          u64snowflake id,
                                          u64snowflake channel_id,
                                          u64snowflake guild_id);
typedef void (*discord_ev_message_delete_bulk)(struct discord *client,
                                               const struct snowflakes *ids,
                                               u64snowflake channel_id,
                                               u64snowflake guild_id);
typedef void (*discord_ev_message_reaction_add)(
    struct discord *client,
    u64snowflake user_id,
    u64snowflake channel_id,
    u64snowflake message_id,
    u64snowflake guild_id,
    const struct discord_guild_member *member,
    const struct discord_emoji *emoji);
typedef void (*discord_ev_message_reaction_remove)(
    struct discord *client,
    u64snowflake user_id,
    u64snowflake channel_id,
    u64snowflake message_id,
    u64snowflake guild_id,
    const struct discord_emoji *emoji);
typedef void (*discord_ev_message_reaction_remove_all)(struct discord *client,
                                                       u64snowflake channel_id,
                                                       u64snowflake message_id,
                                                       u64snowflake guild_id);
typedef void (*discord_ev_message_reaction_remove_emoji)(
    struct discord *client,
    u64snowflake channel_id,
    u64snowflake message_id,
    u64snowflake guild_id,
    const struct discord_emoji *emoji);
typedef void (*discord_ev_voice_state_update)(
    struct discord *client, const struct discord_voice_state *voice_state);
typedef void (*discord_ev_voice_server_update)(struct discord *client,
                                               const char *token,
                                               u64snowflake guild_id,
                                               const char *endpoint);
/** @} */

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
 * @param callback the callback to be triggered on event
 * @param ... commands and a NULL terminator
 * @note The command and any subjacent empty space is left out of
 *       the message content
 */
void discord_set_on_commands(struct discord *client,
                             discord_ev_message callback,
                             ...);

/**
 * @brief Set the time for wakeup function to be called
 * @see discord_set_on_wakeup
 *
 * @param delay time to delay in milliseconds, or -1 to disable
 */
void discord_set_next_wakeup(struct discord *client, int64_t delay);

/** @defgroup DiscordCallbackSet
 * @brief Set callbacks to be triggered on event detection
 * @param client the client created with discord_init()
 * @param callback the callback to be triggered on event
 * @note the functions will automatically set the necessary intent(s) to make
 *        the callback triggerable
 *  @{ */
/** @brief Triggers when wakeup timeout reached and disables any active timer
 */
void discord_set_on_wakeup(struct discord *client, discord_ev_idle callback);
/** @brief Triggers when idle.  */
void discord_set_on_idle(struct discord *client, discord_ev_idle callback);
/** @brief Triggers once per loop cycle.  */
void discord_set_on_cycle(struct discord *client, discord_ev_idle callback);
/** @brief Triggers when the client is ready */
void discord_set_on_ready(struct discord *client, discord_ev_idle callback);
/** @brief Triggers when a application command is created */
void discord_set_on_application_command_create(
    struct discord *client, discord_ev_application_command callback);
/** @brief Triggers when a application command is updated */
void discord_set_on_application_command_update(
    struct discord *client, discord_ev_application_command callback);
/** @brief Triggers when a application command is deleted */
void discord_set_on_application_command_delete(
    struct discord *client, discord_ev_application_command callback);
/** @brief Triggers when a channel is created */
void discord_set_on_channel_create(struct discord *client,
                                   discord_ev_channel callback);
/** @brief Triggers when a channel is updated */
void discord_set_on_channel_update(struct discord *client,
                                   discord_ev_channel callback);
/** @brief Triggers when a channel is deleted */
void discord_set_on_channel_delete(struct discord *client,
                                   discord_ev_channel callback);
/** @brief Triggers when some channel pins are updated */
void discord_set_on_channel_pins_update(
    struct discord *client, discord_ev_channel_pins_update callback);
/** @brief Triggers when a thread is created */
void discord_set_on_thread_create(struct discord *client,
                                  discord_ev_channel callback);
/** @brief Triggers when a thread is updated */
void discord_set_on_thread_update(struct discord *client,
                                  discord_ev_channel callback);
/** @brief Triggers when a thread is deleted */
void discord_set_on_thread_delete(struct discord *client,
                                  discord_ev_channel callback);
/** @brief Triggers when guild information becomes available */
void discord_set_on_guild_create(struct discord *client,
                                 discord_ev_guild callback);
/** @brief Triggers when a guild's information becomes updated */
void discord_set_on_guild_update(struct discord *client,
                                 discord_ev_guild callback);
/** @brief Triggers when removed from a guild */
void discord_set_on_guild_delete(struct discord *client,
                                 discord_ev_guild_delete callback);
/** @brief Triggers when a guild role is created */
void discord_set_on_guild_role_create(struct discord *client,
                                      discord_ev_guild_role callback);
/** @brief Triggers when a guild role is updated */
void discord_set_on_guild_role_update(struct discord *client,
                                      discord_ev_guild_role callback);
/** @brief Triggers when a guild role is deleted */
void discord_set_on_guild_role_delete(struct discord *client,
                                      discord_ev_guild_role_delete callback);
/** @brief Triggers when a guild member is added */
void discord_set_on_guild_member_add(struct discord *client,
                                     discord_ev_guild_member callback);
/** @brief Triggers when a guild member is updated */
void discord_set_on_guild_member_update(struct discord *client,
                                        discord_ev_guild_member callback);
/** @brief Triggers when a guild member is removed */
void discord_set_on_guild_member_remove(
    struct discord *client, discord_ev_guild_member_remove callback);
/** @brief Triggers when a guild ban is added */
void discord_set_on_guild_ban_add(struct discord *client,
                                  discord_ev_guild_ban callback);
/** @brief Triggers when a guild ban is removed */
void discord_set_on_guild_ban_remove(struct discord *client,
                                     discord_ev_guild_ban callback);
/** @brief Triggers when a interaction is created */
void discord_set_on_interaction_create(struct discord *client,
                                       discord_ev_interaction callback);
/** @brief Triggers when a message is created */
void discord_set_on_message_create(struct discord *client,
                                   discord_ev_message callback);
/** @brief Triggers when a message is updated */
void discord_set_on_message_update(struct discord *client,
                                   discord_ev_message callback);
/** @brief Triggers when a message is deleted */
void discord_set_on_message_delete(struct discord *client,
                                   discord_ev_message_delete callback);
/** @brief Triggers when a bulk of messages are deleted */
void discord_set_on_message_delete_bulk(
    struct discord *client, discord_ev_message_delete_bulk callback);
/** @brief Triggers when a message reaction is added */
void discord_set_on_message_reaction_add(
    struct discord *client, discord_ev_message_reaction_add callback);
/** @brief Triggers when a message reaction is removed */
void discord_set_on_message_reaction_remove(
    struct discord *client, discord_ev_message_reaction_remove callback);
/** @brief Triggers when all reaction from some message is removed
 */
void discord_set_on_message_reaction_remove_all(
    struct discord *client, discord_ev_message_reaction_remove_all callback);
/** @brief Triggers when all instances of a particular reaction from some
 *        message is removed */
void discord_set_on_message_reaction_remove_emoji(
    struct discord *client, discord_ev_message_reaction_remove_emoji callback);
/** @brief Triggers when a voice state is updated */
void discord_set_on_voice_state_update(struct discord *client,
                                       discord_ev_voice_state_update callback);
/** @brief Triggers when a voice server is updated */
void discord_set_on_voice_server_update(
    struct discord *client, discord_ev_voice_server_update callback);

/** @} */

#endif /* DISCORD_GATEWAY_H */
