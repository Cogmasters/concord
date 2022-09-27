/**
 * @file webhook.h
 * @author Cogmasters
 * @brief Webhook public functions and datatypes
 */

#ifndef DISCORD_WEBHOOK_H
#define DISCORD_WEBHOOK_H

/** @defgroup DiscordAPIWebhook Webhook
 * @ingroup DiscordAPI
 * @brief Webhook's public API supported by Concord
 *  @{ */

/**
 * @brief Create a new webhook
 * @note Requires the MANAGE_WEBHOOKS permission
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the webhook belongs to
 * @param params request parameters
 * @CCORD_ret_obj{ret,webhook}
 * @CCORD_return
 */
CCORDcode discord_create_webhook(struct discord *client,
                                 u64snowflake channel_id,
                                 struct discord_create_webhook *params,
                                 struct discord_ret_webhook *ret);

/**
 * @brief Get webhooks from a given channel
 * @note Requires the MANAGE_WEBHOOKS permission
 *
 * @param client the client created with discord_init()
 * @param channel_id the channel that the webhooks belongs to
 * @CCORD_ret_obj{ret,webhooks}
 * @CCORD_return
 */
CCORDcode discord_get_channel_webhooks(struct discord *client,
                                       u64snowflake channel_id,
                                       struct discord_ret_webhooks *ret);

/**
 * @brief Get webhooks from a given guild webhook objects
 * @note Requires the MANAGE_WEBHOOKS permission
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild that the webhooks belongs to
 * @CCORD_ret_obj{ret,webhooks}
 * @CCORD_return
 */
CCORDcode discord_get_guild_webhooks(struct discord *client,
                                     u64snowflake guild_id,
                                     struct discord_ret_webhooks *ret);

/**
 * @brief Get the new webhook object for the given id
 *
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @CCORD_ret_obj{ret,webhook}
 * @CCORD_return
 */
CCORDcode discord_get_webhook(struct discord *client,
                              u64snowflake webhook_id,
                              struct discord_ret_webhook *ret);

/**
 * Same as discord_get_webhook(), except this call does not require
 *        authentication and returns no user in the webhook object
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @CCORD_ret_obj{ret,webhook}
 * @CCORD_return
 */
CCORDcode discord_get_webhook_with_token(struct discord *client,
                                         u64snowflake webhook_id,
                                         const char webhook_token[],
                                         struct discord_ret_webhook *ret);

/**
 * @brief Modify a webhook
 * @note Requires the MANAGE_WEBHOOKS permission
 *
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param params request parameters
 * @CCORD_ret_obj{ret,webhook}
 * @CCORD_return
 */
CCORDcode discord_modify_webhook(struct discord *client,
                                 u64snowflake webhook_id,
                                 struct discord_modify_webhook *params,
                                 struct discord_ret_webhook *ret);

/**
 * Same discord_modify_webhook(), except this call does not require
 *       authentication and returns no user in the webhook object
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param params request parameters
 * @CCORD_ret_obj{ret,webhook}
 * @CCORD_return
 */
CCORDcode discord_modify_webhook_with_token(
    struct discord *client,
    u64snowflake webhook_id,
    const char webhook_token[],
    struct discord_modify_webhook_with_token *params,
    struct discord_ret_webhook *ret);

/**
 * Delete a webhook permanently. Requires the MANAGE_WEBHOOKS permission
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_webhook(struct discord *client,
                                 u64snowflake webhook_id,
                                 struct discord_delete_webhook *params,
                                 struct discord_ret *ret);

/**
 * Same discord_delete_webhook(), except this call does not require
 *       authentication
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_webhook_with_token(struct discord *client,
                                            u64snowflake webhook_id,
                                            const char webhook_token[],
                                            struct discord_ret *ret);

/**
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param params request parameters
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_execute_webhook(struct discord *client,
                                  u64snowflake webhook_id,
                                  const char webhook_token[],
                                  struct discord_execute_webhook *params,
                                  struct discord_ret *ret);

/**
 * @brief Get previously-sent webhook message from the same token
 *
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param message_id the message the webhook belongs to
 * @CCORD_ret_obj{ret,message}
 * @CCORD_return
 */
CCORDcode discord_get_webhook_message(struct discord *client,
                                      u64snowflake webhook_id,
                                      const char webhook_token[],
                                      u64snowflake message_id,
                                      struct discord_ret_message *ret);

/**
 * @brief Edits a previously-sent webhook message from the same token
 *
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param message_id the message the webhook belongs to
 * @param params request parameters
 * @CCORD_ret_obj{ret,message}
 * @CCORD_return
 */
CCORDcode discord_edit_webhook_message(
    struct discord *client,
    u64snowflake webhook_id,
    const char webhook_token[],
    u64snowflake message_id,
    struct discord_edit_webhook_message *params,
    struct discord_ret_message *ret);

/**
 * @brief Deletes a message that was created by the webhook
 *
 * @param client the client created with discord_init()
 * @param webhook_id the webhook itself
 * @param webhook_token the webhook token
 * @param message_id the message the webhook belongs to
 * @CCORD_ret{ret}
 * @CCORD_return
 */
CCORDcode discord_delete_webhook_message(struct discord *client,
                                         u64snowflake webhook_id,
                                         const char webhook_token[],
                                         u64snowflake message_id,
                                         struct discord_ret *ret);

/** @example webhook.c
 * Demonstrates a couple use cases of the Webhook API */

/** @} DiscordAPIWebhook */

#endif /* DISCORD_WEBHOOK_H */
