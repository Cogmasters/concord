/**
 * @file guild_template.h
 * @author Cogmasters
 * @brief Guild Template public functions and datatypes
 */

#ifndef DISCORD_GUILD_TEMPLATE_H
#define DISCORD_GUILD_TEMPLATE_H

/** @defgroup DiscordAPIGuildTemplate Guild Template
 * @ingroup DiscordAPI
 * @brief Guild Template's public API supported by Concord
 *  @{ */

/**
 * @brief Get a guild template for the given code
 *
 * @param client the client created with discord_init()
 * @param template_code the guild template code
 * @CCORD_ret_obj{ret,guild_template}
 * @CCORD_return
 */
CCORDcode discord_get_guild_template(struct discord *client,
                                     const char template_code[],
                                     struct discord_ret_guild_template *ret);

/**
 * @brief Create a new guild based on a template
 * @note This endpoint can be used only by bots in less than 10 guilds
 * 
 * @param client the client created with discord_init()
 * @param template_code the guild template code
 * @param params the request parameters
 * @CCORD_ret_obj{ret,guild}
 * @CCORD_return
 */
CCORDcode discord_create_guild_from_guild_template(
    struct discord *client,
    const char template_code[],
    struct discord_create_guild_from_guild_template *params,
    struct discord_ret_guild *ret);

/**
 * @brief Returns @ref discord_guild_templates from a guild
 * @note Requires the `MANAGE_GUILD` permission
 * 
 * @param client the client created with discord_init()
 * @param guild_id the guild to fetch the templates from
 * @CCORD_ret_obj{ret,guild_templates}
 * @CCORD_return
 */
CCORDcode discord_get_guild_templates(struct discord *client,
                                      u64snowflake guild_id,
                                      struct discord_ret_guild_templates *ret);

/**
 * @brief Creates a template for the guild
 * @note Requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to create a template from
 * @param params the request parameters
 * @CCORD_ret_obj{ret,guild_template}
 * @CCORD_return
 */
CCORDcode discord_create_guild_template(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_create_guild_template *params,
    struct discord_ret_guild_template *ret);

/**
 * @brief Syncs the template to the guild's current state
 * @note Requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to sync the template from
 * @param template_code the guild template code
 * @CCORD_ret_obj{ret,guild_template}
 * @CCORD_return
 */
CCORDcode discord_sync_guild_template(struct discord *client,
                                      u64snowflake guild_id,
                                      const char template_code[],
                                      struct discord_ret_guild_template *ret);

/**
 * @brief Modifies the template's metadata
 * @note Requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to modify the template at
 * @param template_code the guild template code
 * @param params the request parameters
 * @CCORD_ret_obj{ret,guild_template}
 * @CCORD_return
 */
CCORDcode discord_modify_guild_template(
    struct discord *client,
    u64snowflake guild_id,
    const char template_code[],
    struct discord_modify_guild_template *params,
    struct discord_ret_guild_template *ret);

/**
 * @brief Deletes the guild template
 * @note Requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to delete the template at
 * @param template_code the guild template code
 * @CCORD_ret_obj{ret,guild_template}
 * @CCORD_return
 */
CCORDcode discord_delete_guild_template(
    struct discord *client,
    u64snowflake guild_id,
    const char template_code[],
    struct discord_ret_guild_template *ret);

/** @example guild-template.c
 * Demonstrates a couple use cases of the Guild Template API */

/** @} DiscordAPIGuildTemplate */

#endif /* DISCORD_GUILD_TEMPLATE_H */
