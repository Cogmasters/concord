/**
 * @file user.h
 * @author Cogmasters
 * @brief User public functions and datatypes
 */

#ifndef DISCORD_USER_H
#define DISCORD_USER_H

/** @defgroup DiscordAPIUser User
 * @ingroup DiscordAPI
 * @brief User's public API supported by Concord
 *  @{ */

/**
 * @brief Get client's user
 *
 * @param client the client created with discord_init()
 * @CCORD_ret_obj{ret,user}
 * @CCORD_return
 */
CCORDcode discord_get_current_user(struct discord *client,
                                   struct discord_ret_user *ret);

/**
 * @brief Get user for a given id
 *
 * @param client the client created with discord_init()
 * @param user_id user to be fetched
 * @CCORD_ret_obj{ret,user}
 * @CCORD_return
 */
CCORDcode discord_get_user(struct discord *client,
                           u64snowflake user_id,
                           struct discord_ret_user *ret);

/**
 * @brief Modify client's user account settings
 *
 * @param client the client created with discord_init()
 * @param params request parameters
 * @CCORD_ret_obj{ret,user}
 * @CCORD_return
 */
CCORDcode discord_modify_current_user(
    struct discord *client,
    struct discord_modify_current_user *params,
    struct discord_ret_user *ret);

/**
 * @brief Get guilds client is a member of
 * @note Requires the `guilds` oauth2 scope
 *
 * @param client the client created with discord_init()
 * @CCORD_ret_obj{ret,guilds}
 * @CCORD_return
 */
CCORDcode discord_get_current_user_guilds(struct discord *client,
                                          struct discord_ret_guilds *ret);

/**
 * @brief Leave a guild
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to exit from
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_leave_guild(struct discord *client,
                              u64snowflake guild_id,
                              struct discord_ret *ret);

/**
 * @brief Create a new DM channel with a given user
 * @warning DMs should generally be initiated by a user action. If you open a
 *        significant amount of DMs too quickly, your bot may be rate limited
 *        or blocked from opening new ones
 *
 * @param client the client created with discord_init()
 * @param params the request parameters
 * @CCORD_ret_obj{ret,channel}
 * @CCORD_return
 */
CCORDcode discord_create_dm(struct discord *client,
                            struct discord_create_dm *params,
                            struct discord_ret_channel *ret);

/**
 * @brief Create a new group DM channel with multiple users
 * @note DMs created with this function will not be shown in the Discord client
 * @note Limited to 10 active group DMs
 *
 * @param client the client created with discord_init()
 * @param params the request parameters
 * @CCORD_ret_obj{ret,channel}
 * @CCORD_return
 */
CCORDcode discord_create_group_dm(struct discord *client,
                                  struct discord_create_group_dm *params,
                                  struct discord_ret_channel *ret);

/**
 * @brief Get a list of connection objects
 * @note Requires the `connections` oauth2 scope
 *
 * @param client the client created with discord_init()
 * @CCORD_ret_obj{ret,connections}
 * @CCORD_return
 */
CCORDcode discord_get_user_connections(struct discord *client,
                                       struct discord_ret_connections *ret);

/** @} DiscordAPIUser */

#endif /* DISCORD_USER_H */
