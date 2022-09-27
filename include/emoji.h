/**
 * @file emoji.h
 * @author Cogmasters
 * @brief Emoji public functions and datatypes
 */

#ifndef DISCORD_EMOJI_H
#define DISCORD_EMOJI_H

/** @defgroup DiscordAPIEmoji Emoji
 * @ingroup DiscordAPI
 * @brief Emoji's public API supported by Concord
 *  @{ */

/**
 * @brief Get emojis of a given guild
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to get emojis from
 * @CCORD_ret_obj{ret,emojis}
 * @CCORD_return
 */
CCORDcode discord_list_guild_emojis(struct discord *client,
                                    u64snowflake guild_id,
                                    struct discord_ret_emojis *ret);

/**
 * @brief Get a specific emoji from a guild
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the emoji belongs to
 * @param emoji_id the emoji to be fetched
 * @CCORD_ret_obj{ret,emoji}
 * @CCORD_return
 */
CCORDcode discord_get_guild_emoji(struct discord *client,
                                  u64snowflake guild_id,
                                  u64snowflake emoji_id,
                                  struct discord_ret_emoji *ret);

/**
 * @brief Create a new emoji for the guild
 * @note Fires a `Guild Emojis Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to add the new emoji to
 * @param params request parameters
 * @CCORD_ret_obj{ret,emoji}
 * @CCORD_return
 */
CCORDcode discord_create_guild_emoji(struct discord *client,
                                     u64snowflake guild_id,
                                     struct discord_create_guild_emoji *params,
                                     struct discord_ret_emoji *ret);

/**
 * @brief Modify the given emoji
 * @note Fires a `Guild Emojis Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the emoji belongs to
 * @param emoji_id the emoji to be modified
 * @param params request parameters
 * @CCORD_ret_obj{ret,emoji}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_emoji(struct discord *client,
                                     u64snowflake guild_id,
                                     u64snowflake emoji_id,
                                     struct discord_modify_guild_emoji *params,
                                     struct discord_ret_emoji *ret);

/**
 * @brief Deletes the given emoji
 * @note Fires a `Guild Emojis Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the emoji belongs to
 * @param emoji_id the emoji to be deleted
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_guild_emoji(struct discord *client,
                                     u64snowflake guild_id,
                                     u64snowflake emoji_id,
                                     struct discord_delete_guild_emoji *params,
                                     struct discord_ret *ret);

/** @example emoji.c
 * Demonstrates a couple use cases of the Emoji API */

/** @} DiscordAPIEmoji */

#endif /* DISCORD_EMOJI_H */
