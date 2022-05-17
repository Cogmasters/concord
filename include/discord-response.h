/**
 * @file discord-response.h
 * @author Cogmasters
 * @brief Generic macros for initializing a @ref discord_response and return
 *      handles
 */

#ifndef DISCORD_RESPONSE_H
#define DISCORD_RESPONSE_H

struct discord_response {
    void *data;
    const void *keep;
    CCORDcode code;
};

/******************************************************************************
 * Templates for generating type-safe return handles for async requests
 ******************************************************************************/

#define DISCORDT_RET_DEFAULT_FIELDS                                           \
    /** optional callback to be executed on a failed request */               \
    void (*fail)(struct discord * client, struct discord_response * resp);    \
    /** user arbitrary data to be passed to `done` or `fail` callbacks */     \
    void *data;                                                               \
    /** cleanup method to be called for `data`, once its no longer            \
    being referenced */                                                       \
    void (*cleanup)(struct discord * client, void *data);                     \
    /** Concord callback parameter the client wish to keep reference */       \
    const void *keep;                                                         \
    /** if `true` then request will be prioritized over already enqueued      \
        requests */                                                           \
    bool high_p

#define DISCORDT_RETURN(_type)                                                \
    /** @brief Request's return context */                                    \
    struct discord_ret_##_type {                                              \
        /** optional callback to be executed on a successful request */       \
        void (*done)(struct discord * client,                                 \
                     struct discord_response *resp,                           \
                     const struct discord_##_type *ret);                      \
        DISCORDT_RET_DEFAULT_FIELDS;                                          \
        /** if an address is provided, then request will block the thread and \
           perform on-spot.                                                   \
           On success the response object will be written to the address,     \
           unless enabled with @ref DISCORD_SYNC_FLAG */                      \
        struct discord_##_type *sync;                                         \
    }

/** @brief Request's return context */
struct discord_ret {
    /** optional callback to be executed on a successful request */
    void (*done)(struct discord *client, struct discord_response *resp);
    DISCORDT_RET_DEFAULT_FIELDS;
    /** if `true`, request will block the thread and perform on-spot */
    bool sync;
};

/** @brief flag for enabling `sync` mode without expecting a datatype return */
#define DISCORD_SYNC_FLAG ((void *)-1)

/** @addtogroup DiscordAPIAuditLog
 *  @{ */
DISCORDT_RETURN(audit_log);
/** @} DiscordAPIAuditLog */

/** @addtogroup DiscordAPIChannel
 *  @{ */
DISCORDT_RETURN(channel);
DISCORDT_RETURN(channels);
DISCORDT_RETURN(message);
DISCORDT_RETURN(messages);
DISCORDT_RETURN(followed_channel);
DISCORDT_RETURN(thread_members);
DISCORDT_RETURN(thread_response_body);
/** @} DiscordAPIChannel */

/** @addtogroup DiscordAPIEmoji
 *  @{ */
DISCORDT_RETURN(emoji);
DISCORDT_RETURN(emojis);
/** @} DiscordAPIEmoji */

/** @addtogroup DiscordAPIGuild
 *  @{ */
DISCORDT_RETURN(guild);
DISCORDT_RETURN(guilds);
DISCORDT_RETURN(guild_preview);
DISCORDT_RETURN(guild_member);
DISCORDT_RETURN(guild_members);
DISCORDT_RETURN(ban);
DISCORDT_RETURN(bans);
DISCORDT_RETURN(role);
DISCORDT_RETURN(roles);
DISCORDT_RETURN(welcome_screen);
/** @} DiscordAPIGuild */

/** @addtogroup DiscordAPIGuildTemplate
 *  @{ */
DISCORDT_RETURN(guild_template);
/** @} DiscordAPIGuildTemplate */

/** @addtogroup DiscordAPIInvite
 *  @{ */
DISCORDT_RETURN(invite);
DISCORDT_RETURN(invites);
/** @} DiscordAPIInvite */

/** @addtogroup DiscordAPIUser
 *  @{ */
DISCORDT_RETURN(user);
DISCORDT_RETURN(users);
DISCORDT_RETURN(connections);
/** @} DiscordAPIUser */

/** @addtogroup DiscordAPIVoice
 *  @{ */
DISCORDT_RETURN(voice_regions);
/** @} DiscordAPIVoice */

/** @addtogroup DiscordAPIWebhook
 *  @{ */
DISCORDT_RETURN(webhook);
DISCORDT_RETURN(webhooks);
/** @} DiscordAPIWebhook */

/** @addtogroup DiscordAPIInteractionsApplicationCommand
 * @ingroup DiscordAPIInteractions
 *  @{ */
DISCORDT_RETURN(application_command);
DISCORDT_RETURN(application_commands);
DISCORDT_RETURN(application_command_permission);
DISCORDT_RETURN(application_command_permissions);
DISCORDT_RETURN(guild_application_command_permissions);
/** @} DiscordAPIInteractionsApplicationCommand */

/** @addtogroup DiscordAPIInteractionsReact
 * @ingroup DiscordAPIInteractions
 *  @{ */
DISCORDT_RETURN(interaction_response);
/** @} DiscordAPIInteractionsReact */

#endif /* DISCORD_RESPONSE_H */
