#ifndef DISCORD_CACHE_H
#define DISCORD_CACHE_H

enum discord_cache_options {
    DISCORD_CACHE_MESSAGES = 1 << 0,
    DISCORD_CACHE_GUILDS = 1 << 1,
};

void discord_cache_enable(struct discord *client,
                          enum discord_cache_options options);

/**
 * @brief get a message from cache, only if locally available in RAM
 * @note you must call discord_unclaim(client, message) when done
 * 
 * @param client the client initialized with discord_init()
 * @param channel_id the channel id the message is in
 * @param message_id the id of the message
 * @return NULL if not found, or the message from the cache
 */
const struct discord_message *discord_cache_get_channel_message(
    struct discord *client, u64snowflake channel_id, u64snowflake message_id);

/**
 * @brief get a guild from cache, only if locally available in RAM
 * @note you must call discord_unclaim(client, guild) when done
 * 
 * @param client the client initialized with discord_init()
 * @param guild_id the id of the guild
 * @return NULL if not found, or the guild from the cache
 */
const struct discord_guild *discord_cache_get_guild(
    struct discord *client, u64snowflake guild_id);

#endif // !DISCORD_CACHE_H
