/**
 * @file guild.h
 * @author Cogmasters
 * @brief Guild public functions and datatypes
 */

#ifndef DISCORD_GUILD_H
#define DISCORD_GUILD_H

/** @defgroup DiscordAPIGuild Guild
 * @ingroup DiscordAPI
 * @brief Guild's public API supported by Concord
 *  @{ */

/**
 * @brief Create a new guild
 * @note Fires a `Guild Create` event
 *
 * @param client the client created with discord_init()
 * @param params request parameters
 * @CCORD_ret_obj{ret,guild}
 * @CCORD_return
 */
CCORDcode discord_create_guild(struct discord *client,
                               struct discord_create_guild *params,
                               struct discord_ret_guild *ret);

/**
 * @brief Get the guild with given id
 * @todo missing query parameters
 * @note If with_counts is set to true, this endpoint will also return
 *        approximate_member_count and approximate_presence_count for the
 *        guild
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to retrieve
 * @CCORD_ret_obj{ret,guild}
 * @CCORD_return
 */
CCORDcode discord_get_guild(struct discord *client,
                            u64snowflake guild_id,
                            struct discord_ret_guild *ret);

/**
 * @brief Get the preview for the given guild
 * @note If the user is not in the guild, then the guild must be lurkable
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to get preview from
 * @CCORD_ret_obj{ret,guild_preview}
 * @CCORD_return
 */
CCORDcode discord_get_guild_preview(struct discord *client,
                                    u64snowflake guild_id,
                                    struct discord_ret_guild_preview *ret);

/**
 * @brief Modify a guild's settings
 * @note Requires the MANAGE_GUILD permission
 * @note Fires a `Guild Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to modify
 * @param params request parameters
 * @CCORD_ret_obj{ret,guild}
 * @CCORD_return
 */
CCORDcode discord_modify_guild(struct discord *client,
                               u64snowflake guild_id,
                               struct discord_modify_guild *params,
                               struct discord_ret_guild *ret);

/**
 * @brief Delete a guild permanently, user must be owner
 * @note Fires a `Guild Delete` event
 *
 * @param client the client created with discord_init()
 * @param guild_id id of guild to delete
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_guild(struct discord *client,
                               u64snowflake guild_id,
                               struct discord_ret *ret);

/**
 * @brief Fetch channels from given guild. Does not include threads
 *
 * @param client the client created with discord_init()
 * @param guild_id id of guild to fetch channels from
 * @CCORD_ret_obj{ret,channels}
 * @CCORD_return
 */
CCORDcode discord_get_guild_channels(struct discord *client,
                                     u64snowflake guild_id,
                                     struct discord_ret_channels *ret);

/**
 * @brief Create a new guild channel
 * @note Requires the MANAGE_CHANNELS permission
 * @note If setting permission overwrites, only permissions your
 *       bot has in the guild can be allowed/denied. Setting MANAGE_ROLES
 *       permission in channels is only possible for guild administrators
 * @note Fires a `Channel Create` event
 *
 * @param client the client created with discord_init()
 * @param guild_id id of the guild to create a channel at
 * @param params request parameters
 * @CCORD_ret_obj{ret,channel}
 * @CCORD_return
 */
CCORDcode discord_create_guild_channel(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_create_guild_channel *params,
    struct discord_ret_channel *ret);

/**
 * @brief Modify guild channel positions
 * @note Requires MANAGE_CHANNELS permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to change the positions of the
 *       channels in
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_channel_positions(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_guild_channel_positions *params,
    struct discord_ret *ret);

/**
 * @brief Get guild member of a guild from given user id
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the member belongs to
 * @param user_id unique user id of member
 * @CCORD_ret_obj{ret,guild_member}
 * @CCORD_return
 */
CCORDcode discord_get_guild_member(struct discord *client,
                                   u64snowflake guild_id,
                                   u64snowflake user_id,
                                   struct discord_ret_guild_member *ret);

/**
 * @brief Get guild members of a guild
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the members belongs to
 * @param request parameters
 * @CCORD_ret_obj{ret,guild_members}
 * @CCORD_return
 */
CCORDcode discord_list_guild_members(struct discord *client,
                                     u64snowflake guild_id,
                                     struct discord_list_guild_members *params,
                                     struct discord_ret_guild_members *ret);

/**
 * @brief Get guild members whose username or nickname starts with a provided
 *        string
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the members belongs to
 * @param request parameters
 * @CCORD_ret_obj{ret,guild_members}
 * @CCORD_return
 */
CCORDcode discord_search_guild_members(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_search_guild_members *params,
    struct discord_ret_guild_members *ret);

/**
 * @brief Adds a user to the guild
 * @note Requires valid oauth2 access token for the user with `guilds.join`
 *       scope
 * @note Fires a `Guild Member Add` event
 * @note The bot must be a member of the guild with CREATE_INSTANT_INVITE
 *       permission
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to add the member to
 * @param user_id the user to be added
 * @param request parameters
 * @CCORD_ret_obj{ret,guild_member}
 * @CCORD_return
 */
CCORDcode discord_add_guild_member(struct discord *client,
                                   u64snowflake guild_id,
                                   u64snowflake user_id,
                                   struct discord_add_guild_member *params,
                                   struct discord_ret_guild_member *ret);

/**
 * @brief Modify retibutes of a guild member
 * @note Fires a `Guild Member Update` event
 * @see discord_disconnect_guild_member()
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the member belongs to
 * @param user_id the user id of member
 * @param request parameters
 * @CCORD_ret_obj{ret,guild_member}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_member(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake user_id,
    struct discord_modify_guild_member *params,
    struct discord_ret_guild_member *ret);

/**
 * @brief Modifies the current member in the guild
 * @note Fires a `Guild Member Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild where the member exists
 * @param params request parameters
 * @CCORD_ret_obj{ret,guild_member}
 * @CCORD_return
 */
CCORDcode discord_modify_current_member(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_current_member *params,
    struct discord_ret_guild_member *ret);

/**
 * @deprecated use discord_modify_current_member() instead
 * @brief Modify the nickname of the current user in a guild
 * @note Fires a `Guild Member Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the member belongs to
 * @param params request parameters
 * @CCORD_ret_obj{ret,guild_member}
 * @CCORD_return
 */
CCORDcode discord_modify_current_user_nick(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_current_user_nick *params,
    struct discord_ret_guild_member *ret);

/**
 * @brief Adds a role to a guild member
 * @note Fires a `Guild Member Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild where the member exists
 * @param user_id the unique id of the user
 * @param role_id the unique id of the role to be added
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_add_guild_member_role(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake user_id,
    u64snowflake role_id,
    struct discord_add_guild_member_role *params,
    struct discord_ret *ret);

/**
 * @brief Removes a role from a guild member
 * @note Requires the MANAGE_ROLES permission
 * @note Fires a `Guild Member Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild where the member exists
 * @param user_id the unique id of the user
 * @param role_id the unique id of the role to be removed
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_remove_guild_member_role(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake user_id,
    u64snowflake role_id,
    struct discord_remove_guild_member_role *params,
    struct discord_ret *ret);

/**
 * @brief Remove a member from a guild
 * @note Requires the KICK_MEMBERS permission
 * @note Fires a `Guild Member Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to remove the member from
 * @param user_id the user to be removed
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_remove_guild_member(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake user_id,
    struct discord_remove_guild_member *params,
    struct discord_ret *ret);

/**
 * @brief Fetch banned users for given guild
 * @note Requires the BAN_MEMBERS permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to get the list from
 * @CCORD_ret_obj{ret,bans}
 * @CCORD_return
 */
CCORDcode discord_get_guild_bans(struct discord *client,
                                 u64snowflake guild_id,
                                 struct discord_ret_bans *ret);

/**
 * @brief Fetch banned user from given guild
 * @note Requires the BAN_MEMBERS permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to return the ban from
 * @param user_id the user that is banned
 * @CCORD_ret_obj{ret,ban}
 * @CCORD_return
 */
CCORDcode discord_get_guild_ban(struct discord *client,
                                u64snowflake guild_id,
                                u64snowflake user_id,
                                struct discord_ret_ban *ret);

/**
 * @brief Bans user from a given guild
 * @note Requires the BAN_MEMBERS permission
 * @note Fires a `Guild Ban Add` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the user belongs to
 * @param user_id the user to be banned
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_create_guild_ban(struct discord *client,
                                   u64snowflake guild_id,
                                   u64snowflake user_id,
                                   struct discord_create_guild_ban *params,
                                   struct discord_ret *ret);

/**
 * @brief Remove the ban for a user
 * @note Requires the BAN_MEMBERS permission
 * @note Fires a `Guild Ban Remove` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild the user belonged to
 * @param user_id the user to have its ban revoked
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_remove_guild_ban(struct discord *client,
                                   u64snowflake guild_id,
                                   u64snowflake user_id,
                                   struct discord_remove_guild_ban *params,
                                   struct discord_ret *ret);

/**
 * @brief Get guild roles
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to get roles from
 * @CCORD_ret_obj{ret,roles}
 * @CCORD_return
 */
CCORDcode discord_get_guild_roles(struct discord *client,
                                  u64snowflake guild_id,
                                  struct discord_ret_roles *ret);

/**
 * @brief Create a new guild role
 * @note Requires MANAGE_ROLES permission
 * @note Fires a `Guild Role Create` event
 *
 * @param client the client created with discord_init()
 * @param guild_id guild to add a role to
 * @param params request parameters
 * @CCORD_ret_obj{ret,role}
 * @CCORD_return
 */
CCORDcode discord_create_guild_role(struct discord *client,
                                    u64snowflake guild_id,
                                    struct discord_create_guild_role *params,
                                    struct discord_ret_role *ret);

/**
 * @brief Returns the number of members that would be removed in a prune
 *      operation
 * @note Requires the KICK_MEMBERS permission
 * @note By default will not remove users with roles. You can include specific
 *      roles in your prune by providing the `params.include_roles` value
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to be checked
 * @param params request parameters
 * @CCORD_ret_obj{ret,prune_count}
 * @CCORD_return
 */
CCORDcode discord_get_guild_prune_count(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_get_guild_prune_count *params,
    struct discord_ret_prune_count *ret);

/**
 * @brief Begin guild prune operation
 * @note Discord recommends for larger servers to set "compute_prune_count" to
 *       false
 * @note Requires the KICK_MEMBERS permission
 * @note Fires multiple `Guild Member Remove` events
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to start the prune
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_begin_guild_prune(struct discord *client,
                                    u64snowflake guild_id,
                                    struct discord_begin_guild_prune *params,
                                    struct discord_ret *ret);

/**
 * @brief Get voice regions (includes VIP servers when the guild is
 *      VIP-enabled)
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get voice regions from
 * @CCORD_ret_obj{ret,voice_regions}
 * @CCORD_return
 */
CCORDcode discord_get_guild_voice_regions(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_ret_voice_regions *ret);

/**
 * @brief Get guild invites
 * @note requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get invites from
 * @CCORD_ret_obj{ret,invites}
 * @CCORD_return
 */
CCORDcode discord_get_guild_invites(struct discord *client,
                                    u64snowflake guild_id,
                                    struct discord_ret_invites *ret);

/**
 * @brief Get guild integrations
 * @note requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get integrations from
 * @CCORD_ret_obj{ret,integrations}
 * @CCORD_return
 */
CCORDcode discord_get_guild_integrations(struct discord *client,
                                         u64snowflake guild_id,
                                         struct discord_ret_integrations *ret);

/**
 * @brief Deletes the integration for the guild. It will also delete any
 * associated webhooks and bots
 * @note Requires the MANAGE_GUILD permission
 * @note Fires a `Guild Integrations Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to delete the integrations from
 * @param integration_id the id of the integration to delete
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_guild_integrations(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake integration_id,
    struct discord_delete_guild_integrations *params,
    struct discord_ret *ret);

/**
 * @brief Get a guild widget settings
 * @note requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get widget settings from
 * @CCORD_ret_obj{ret,guild_widget_settings}
 * @CCORD_return
 */
CCORDcode discord_get_guild_widget_settings(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_ret_guild_widget_settings *ret);

/**
 * @brief Modify a guild widget settings
 * @note requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to modify the widget settings
 *      from
 * @param param request parameters
 * @CCORD_ret_obj{ret,guild_widget_settings}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_widget(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_guild_widget_settings *params,
    struct discord_ret_guild_widget_settings *ret);

/**
 * @brief Get the widget for the guild
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get the widget from
 * @CCORD_ret_obj{ret,guild_widget}
 * @CCORD_return
 */
CCORDcode discord_get_guild_widget(struct discord *client,
                                   u64snowflake guild_id,
                                   struct discord_ret_guild_widget *ret);

/**
 * @brief Get invite from a given guild
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get vanity url from
 * @CCORD_ret_obj{ret,invite}
 * @CCORD_return
 */
CCORDcode discord_get_guild_vanity_url(struct discord *client,
                                       u64snowflake guild_id,
                                       struct discord_ret_invite *ret);

/* TODO: handle ContentType: image/png and add 'struct discord_png' */
#if 0
/**
 * @brief Get a PNG image widget for the guild
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get a PNG widget image from
 * @param params request parameters
 * @CCORD_ret_obj{ret,png}
 * @CCORD_return
 */
CCORDcode discord_get_guild_widget_image(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_get_guild_widget_image *params,
    struct discord_ret_png *ret);
#endif

/**
 * @brief Get the Welcome Screen for the guild
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get welcome screen of
 * @CCORD_ret_obj{ret,welcome_screen}
 * @CCORD_return
 */
CCORDcode discord_get_guild_welcome_screen(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_ret_welcome_screen *ret);

/**
 * @brief Modify the Welcome Screen for the guild
 * @note requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to modify welcome screen of
 * @param params request parameters
 * @CCORD_ret_obj{ret,welcome_screen}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_welcome_screen(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_guild_welcome_screen *params,
    struct discord_ret_welcome_screen *ret);

/**
 * @brief Updates the current user's voice state
 * @see Caveats
 * https://discord.com/developers/docs/resources/guild#modify-current-user-voice-state-caveats
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to modify the current user's
 *      voice state
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_modify_current_user_voice_state(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_current_user_voice_state *params,
    struct discord_ret *ret);

/**
 * @brief Updates user's voice state
 * @see Caveats
 * https://discord.com/developers/docs/resources/guild#modify-user-voice-state-caveats
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to modify the user's voice state
 * @param user_id the unique id of user to have its voice state modified
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_modify_user_voice_state(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake user_id,
    struct discord_modify_user_voice_state *params,
    struct discord_ret *ret);

/**
 * @brief Modify the positions of a given role list for the guild
 * @note Requires the MANAGE_ROLES permission
 * @note Fires multiple `Guild Role Update` events
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild to get welcome screen of
 * @param params request parameters
 * @CCORD_ret_obj{ret,roles}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_role_positions(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_guild_role_positions *params,
    struct discord_ret_roles *ret);

/**
 * @brief Modify a guild role
 * @note Requires the MANAGE_ROLES permission
 * @note Fires a `Guild Role Update` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild that the role belongs to
 * @param role_id the unique id of the role to modify
 * @param params request parameters
 * @CCORD_ret_obj{ret,role}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_role(struct discord *client,
                                    u64snowflake guild_id,
                                    u64snowflake role_id,
                                    struct discord_modify_guild_role *params,
                                    struct discord_ret_role *ret);

/**
 * @brief Delete a guild role
 * @note Requires the MANAGE_ROLES permission
 * @note Fires a `Guild Role Delete` event
 *
 * @param client the client created with discord_init()
 * @param guild_id the unique id of the guild that the role belongs to
 * @param role_id the unique id of the role to delete
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_guild_role(struct discord *client,
                                    u64snowflake guild_id,
                                    u64snowflake role_id,
                                    struct discord_delete_guild_role *params,
                                    struct discord_ret *ret);

/** @example guild.c
 * Demonstrates a couple use cases of the Guild API */
/** @example ban.c
 * Demonstrates banning and unbanning members */

/** @} DiscordAPIGuild */

#endif /* DISCORD_GUILD_H */
