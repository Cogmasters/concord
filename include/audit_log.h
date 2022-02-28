/**
 * @file audit_log.h
 * @author Cogmasters
 * @brief Audit Log public functions and datatypes
 */

#ifndef DISCORD_AUDIT_LOG
#define DISCORD_AUDIT_LOG

/**
 * @brief Get audit log for a given guild
 *
 * @note Requires the 'VIEW_AUDIT_LOG' permission
 * @param client the client created with discord_init()
 * @param guild_id the guild to retrieve the audit log from
 * @param params request parameters
 * @CCORD_ret_obj{ret,audit_log}
 * @CCORD_return
 */
CCORDcode discord_get_guild_audit_log(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_get_guild_audit_log *params,
    struct discord_ret_audit_log *ret);

#endif /* DISCORD_AUDIT_LOG */
