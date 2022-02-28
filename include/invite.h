/**
 * @file invite.h
 * @author Cogmasters
 * @brief Invite public functions and datatypes
 */

#ifndef DISCORD_INVITE_H
#define DISCORD_INVITE_H

#include "discord-templates.h"

DISCORDT_RETURN(invite);
DISCORDT_RETURN(invites);

/**
 * @brief Get an invite for the given code
 *
 * @param client the client created with discord_init()
 * @param invite_code the invite code
 * @param params request parameters
 * @CCORD_ret_obj{ret,invite}
 * @CCORD_return
 */
CCORDcode discord_get_invite(struct discord *client,
                             char *invite_code,
                             struct discord_get_invite *params,
                             struct discord_ret_invite *ret);

/**
 * @brief Delete an invite
 * @note Requires the MANAGE_CHANNELS permission on the channel this invite
 *        belongs to, or MANAGE_GUILD to remove any invite across the guild.
 * @note Fires a `Invite Delete` event
 *
 * @param client the client created with discord_init()
 * @param invite_code the invite code
 * @CCORD_ret_obj{ret,invite}
 * @CCORD_return
 */
CCORDcode discord_delete_invite(struct discord *client,
                                char *invite_code,
                                struct discord_ret_invite *ret);

#endif /* DISCORD_INVITE_H */
