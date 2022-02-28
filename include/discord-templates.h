/**
 * @file discord-templates.h
 * @author Cogmasters
 * @brief Macro template for generating type-safe return handles for async
 *      requests
 */

#ifndef DISCORD_TEMPLATES_H
#define DISCORD_TEMPLATES_H

/******************************************************************************
 * Templates for generating type-safe return handles for async requests
 ******************************************************************************/

#define DISCORDT_RET_DEFAULT_FIELDS                                           \
    /** optional callback to be executed on a failed request */               \
    void (*fail)(struct discord * client, CCORDcode code, void *data);        \
    /** user arbitrary data to be retrieved at `done` or `fail` callbacks */  \
    void *data;                                                               \
    /** cleanup for when `data` is no longer needed                           \
        @note this only has to be defined once, it shall be called once       \
       `data` is no longer referenced by any callback */                      \
    void (*cleanup)(void *data);                                              \
    /** if `true` then request will take priority over already enqueued       \
        requests */                                                           \
    bool high_p

#define DISCORDT_RETURN(_type)                                                \
    /** @brief Request's return context */                                    \
    struct discord_ret_##_type {                                              \
        /** optional callback to be executed on a successful request */       \
        void (*done)(struct discord * client,                                 \
                     void *data,                                              \
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
    void (*done)(struct discord *client, void *data);
    DISCORDT_RET_DEFAULT_FIELDS;
    /** if `true`, request will block the thread and perform on-spot */
    bool sync;
};

/** @brief flag for enabling `sync` mode without expecting a datatype return */
#define DISCORD_SYNC_FLAG ((void *)-1)

/** @defgroup DiscordRetApplicationCommand
 *  @{ */
DISCORDT_RETURN(application_command);
DISCORDT_RETURN(application_commands);
DISCORDT_RETURN(application_command_permission);
DISCORDT_RETURN(application_command_permissions);
DISCORDT_RETURN(guild_application_command_permissions);
/** @} DiscordRetApplicationCommand */

/** @defgroup DiscordRetInteraction
 *  @{ */
DISCORDT_RETURN(interaction_response);
/** @} DiscordRetInteraction */

/** @defgroup DiscordRetAuditLog
 *  @{ */
DISCORDT_RETURN(audit_log);
/** @} DiscordRetAuditLog */

/** @defgroup DiscordRetChannel
 *  @{ */
DISCORDT_RETURN(channel);
DISCORDT_RETURN(channels);
DISCORDT_RETURN(message);
DISCORDT_RETURN(messages);
DISCORDT_RETURN(followed_channel);
DISCORDT_RETURN(thread_members);
DISCORDT_RETURN(thread_response_body);
/** @} DiscordRetChannel */

/** @defgroup DiscordRetEmoji
 *  @{ */
DISCORDT_RETURN(emoji);
DISCORDT_RETURN(emojis);
/** @} DiscordRetEmoji */

/** @defgroup DiscordRetGuild
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
/** @} DiscordRetGuild */

/** @defgroup DiscordRetGuildTemplate
 *  @{ */
DISCORDT_RETURN(guild_template);
/** @} DiscordRetGuildTemplate */

/** @defgroup DiscordRetInvite
 *  @{ */
DISCORDT_RETURN(invite);
DISCORDT_RETURN(invites);
/** @} DiscordRetInvite */

/** @defgroup DiscordRetUser
 *  @{ */
DISCORDT_RETURN(user);
DISCORDT_RETURN(users);
DISCORDT_RETURN(connections);
/** @} DiscordRetUser */

/** @defgroup DiscordRetWebhook
 *  @{ */
DISCORDT_RETURN(webhook);
DISCORDT_RETURN(webhooks);
/** @} DiscordRetWebhook */

/** @defgroup DiscordRetVoice
 *  @{ */
DISCORDT_RETURN(voice_regions);
/** @} DiscordRetVoice */

#endif /* DISCORD_TEMPLATES_H */
