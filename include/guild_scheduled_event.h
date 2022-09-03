/**
 * @file guild_scheduled_event.h
 * @author Cogmasters
 * @brief Guild Scheduled Event public functions and datatypes
 */

#ifndef DISCORD_GUILD_SCHEDULED_EVENT_H
#define DISCORD_GUILD_SCHEDULED_EVENT_H

/** @defgroup DiscordAPIGuildScheduledEvent Guild Scheduled Event
 * @ingroup DiscordAPI
 * @brief Guild Scheduled Event's public API supported by Concord
 *  @{ */

/**
 * @brief Get a list of scheduled events for the guild
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to fetch the scheduled events from
 * @param params request parameters
 * @CCORD_ret_obj{ret,guild_scheduled_events}
 * @CCORD_return
 */
CCORDcode discord_list_guild_scheduled_events(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_list_guild_scheduled_events *params,
    struct discord_ret_guild_scheduled_events *ret);

/**
 * @brief Create a guild scheduled event
 * @note A guild can have a maximum of 100 events with `SCHEDULED` or `ACTIVE`
 *      status at any time
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to create the scheduled event at
 * @param params request parameters
 * @CCORD_ret_obj{ret,guild_scheduled_event}
 * @CCORD_return
 */
CCORDcode discord_create_guild_scheduled_event(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_create_guild_scheduled_event *params,
    struct discord_ret_guild_scheduled_event *ret);

/**
 * @brief Get a guild scheduled event
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to fetch the scheduled event from
 * @param guild_scheduled_event_id the scheduled event to be fetched
 * @param params request parameters
 * @CCORD_ret_obj{ret,guild_scheduled_event}
 * @CCORD_return
 */
CCORDcode discord_get_guild_scheduled_event(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake guild_scheduled_event_id,
    struct discord_get_guild_scheduled_event *params,
    struct discord_ret_guild_scheduled_event *ret);

/**
 * @brief Modify a guild scheduled event
 * @note Silently discards `entity_metadata` for non-`EXTERNAL` events
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild where the scheduled event to be modified is at
 * @param guild_scheduled_event_id the scheduled event to be modified
 * @param params request parameters
 * @CCORD_ret_obj{ret,guild_scheduled_event}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_scheduled_event(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake guild_scheduled_event_id,
    struct discord_modify_guild_scheduled_event *params,
    struct discord_ret_guild_scheduled_event *ret);

/**
 * @brief Delete a guild scheduled event
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild where the scheduled event to be deleted is at
 * @param guild_scheduled_event_id the scheduled event to be deleted
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_guild_scheduled_event(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake guild_scheduled_event_id,
    struct discord_ret *ret);

/**
 * @brief Get a list of members subscribed to a guild scheduled event
 * @note Guild member data, if it exists, is included if the
 *      `params.with_member` value is set
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild with the scheduled event belongs to
 * @param guild_scheduled_event_id the scheduled event
 * @param params request parameters
 * @CCORD_ret_obj{ret,guild_scheduled_event_users}
 * @CCORD_return
 */
CCORDcode discord_get_guild_scheduled_event_users(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake guild_scheduled_event_id,
    struct discord_get_guild_scheduled_event_users *params,
    struct discord_ret_guild_scheduled_event_users *ret);

/** @} DiscordAPIGuildScheduledEvent */

#endif /* DISCORD_GUILD_SCHEDULED_EVENT_H */
