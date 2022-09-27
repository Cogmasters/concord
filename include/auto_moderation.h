/**
 * @file auto_moderation.h
 * @author Cogmasters
 * @brief Auto Moderation public functions and datatypes
 */

#ifndef DISCORD_AUTO_MODERATION_H
#define DISCORD_AUTO_MODERATION_H

/** @defgroup DiscordAPIAutoModeration Auto Moderation
 * @ingroup DiscordAPI
 * @brief Auto Moderation public API supported by Concord
 *  @{ */

/**
 * @brief Get a list of all rules currently configured for the guild
 * @note Requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to fetch the rules from
 * @CCORD_ret_obj{ret,auto_moderation_rules}
 * @CCORD_return
 */
CCORDcode discord_list_auto_moderation_rules_for_guild(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_ret_auto_moderation_rules *ret);

/**
 * @brief Get a single rule
 * @note Requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to fetch the rule from
 * @param auto_moderation_rule_id the rule to be fetched
 * @CCORD_ret_obj{ret,auto_moderation_rule}
 * @CCORD_return
 */
CCORDcode discord_get_auto_moderation_rule(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake auto_moderation_rule_id,
    struct discord_ret_auto_moderation_rule *ret);

/**
 * @brief Create a new rule
 * @note Requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild to create the rule in
 * @param params request parameters
 * @CCORD_ret_obj{ret,auto_moderation_rule}
 * @CCORD_return
 */
CCORDcode discord_create_auto_moderation_rule(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_create_auto_moderation_rule *params,
    struct discord_ret_auto_moderation_rule *ret);

/**
 * @brief Modify an existing rule
 * @note Requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild where the rule to be modified is at
 * @param auto_moderation_rule_id the rule to be modified
 * @param params request parameters
 * @CCORD_ret_obj{ret,auto_moderation_rule}
 * @CCORD_return
 */
CCORDcode discord_modify_auto_moderation_rule(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake auto_moderation_rule_id,
    struct discord_modify_auto_moderation_rule *params,
    struct discord_ret_auto_moderation_rule *ret);

/**
 * @brief Delete a rule
 * @note Requires the `MANAGE_GUILD` permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild where the rule to be deleted is at
 * @param auto_moderation_rule_id the rule to be deleted
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_auto_moderation_rule(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake auto_moderation_rule_id,
    struct discord_delete_auto_moderation_rule *params,
    struct discord_ret *ret);

/** @} DiscordAPIAutoModeration */

#endif /* DISCORD_AUTO_MODERATION_H */
