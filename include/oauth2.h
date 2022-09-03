/**
 * @file oauth2.h
 * @author Cogmasters
 * @brief OAuth2 public functions and datatypes
 */

#ifndef DISCORD_OAUTH2_H
#define DISCORD_OAUTH2_H

/** @defgroup DiscordAPIOAuth2 OAuth2
 * @ingroup DiscordAPI
 * @brief OAuth2's public API supported by Concord
 *  @{ */

/**
 * @brief Returns the bot's application object
 *
 * @param client the client created with discord_init()
 * @CCORD_ret_obj{ret,application}
 * @CCORD_return
 */
CCORDcode discord_get_current_bot_application_information(
    struct discord *client, struct discord_ret_application *ret);

/**
 * @brief Returns info about the current authorization
 * @note Requires authentication with a bearer token
 *
 * @param client the client created with discord_init()
 * @CCORD_ret_obj{ret,auth_response}
 * @CCORD_return
 */
CCORDcode discord_get_current_authorization_information(
    struct discord *client, struct discord_ret_auth_response *ret);

/** @} DiscordAPIOAuth2 */

#endif /* DISCORD_OAUTH2_H */
