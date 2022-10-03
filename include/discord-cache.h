/**
 * @file discord-cache.h
 * @author Cogmasters
 * @brief Caching of Discord resources
 */

#ifndef DISCORD_CACHE_H
#define DISCORD_CACHE_H

/** @defgroup DiscordClientCache Caching
 * @ingroup DiscordClient
 * @brief Caching API supported by Concord
 *  @{ */

enum discord_cache_options {
    DISCORD_CACHE_MESSAGES = 1 << 0,
    DISCORD_CACHE_GUILDS = 1 << 1,
};

void discord_cache_enable(struct discord *client,
                          enum discord_cache_options options);

/**
 * @brief Get a message from cache, only if locally available in RAM
 * @note When done, discord_unclaim() must be called on the message resource
 *
 * @param client the client initialized with discord_init()
 * @param channel_id the channel id the message is in
 * @param message_id the id of the message
 * @return `NULL` if not found, or a cache'd message
 */
const struct discord_message *discord_cache_get_channel_message(
    struct discord *client, u64snowflake channel_id, u64snowflake message_id);

/**
 * @brief Get a guild from cache, only if locally available in RAM
 * @note When done, discord_unclaim() must be called on the guild resource
 *
 * @param client the client initialized with discord_init()
 * @param guild_id the id of the guild
 * @return `NULL` if not found, or a cache'd guild
 */
const struct discord_guild *discord_cache_get_guild(struct discord *client,
                                                    u64snowflake guild_id);

/** @example cache.c
 * Demonstrates cache usage */

/** @} DiscordClientCache */

#endif /* DISCORD_CACHE_H */
