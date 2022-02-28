#ifndef DISCORD_GUILD_TEMPLATE_H
#define DISCORD_GUILD_TEMPLATE_H

/**
 * @brief Get a guild template for the given code
 *
 * @param client the client created with discord_init()
 * @param code the guild template code
 * @CCORD_ret_obj{ret,guild_template}
 * @CCORD_return
 */
CCORDcode discord_get_guild_template(struct discord *client,
                                     char *code,
                                     struct discord_ret_guild_template *ret);

/**
 * @brief Creates a template for the guild
 * @note Requires the MANAGE_GUILD permission
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
 * @note Requires the MANAGE_GUILD permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to sync the template from
 * @param code the guild template code
 * @CCORD_ret_obj{ret,guild_template}
 * @CCORD_return
 */
CCORDcode discord_sync_guild_template(struct discord *client,
                                      u64snowflake guild_id,
                                      char *code,
                                      struct discord_ret_guild_template *ret);

#endif /* DISCORD_GUILD_TEMPLATE_H */