/**
 * @file discord-templates.h
 * @author Cogmasters
 * @brief File containing datatypes generated via macro templates
 */

#ifndef DISCORD_TEMPLATES_H
#define DISCORD_TEMPLATES_H

/** @brief flag for enabling `sync` mode without expecting a datatype return */
#define DISCORD_SYNC_FLAG ((void *)-1)

/******************************************************************************
 * Templates specific to Discord's response datatypes
 ******************************************************************************/

#define DISCORDT_RET_CALLBACK(type)                                           \
    /** @brief Triggers on a succesful request */                             \
    typedef void (*discord_on_##type)(struct discord * client, void *data,    \
                                      const struct discord_##type *ret)

#define DISCORDT_RET_CALLBACK_LIST(type)                                      \
    /** @brief Triggers on a succesful request */                             \
    typedef void (*discord_on_##type##s)(struct discord * client, void *data, \
                                         const struct discord_##type **ret)

#define DISCORDT_RET_DEFAULT_FIELDS                                           \
    /** optional callback to be executed on a failed request */               \
    discord_on_fail fail;                                                     \
    /** user arbitrary data to be retrieved at `done` or `fail` callbacks */  \
    void *data;                                                               \
    /** cleanup for when `data` is no longer needed                           \
        @note this only has to be defined once, it shall be called once       \
       `data` is no longer referenced by any callback */                      \
    void (*cleanup)(void *data);                                              \
    /** if `true` then request will take priority over already enqueued       \
        requests */                                                           \
    bool high_p

#define DISCORDT_RET(type)                                                    \
    /** @brief Request's return context */                                    \
    struct discord_ret_##type {                                               \
        /** optional callback to be executed on a successful request */       \
        discord_on_##type done;                                               \
        DISCORDT_RET_DEFAULT_FIELDS;                                          \
        /** if an address is provided, then request will block the thread and \
           perform on-spot.                                                   \
           On success the response object will be written to the address,     \
           unless enabled with @ref DISCORD_SYNC_FLAG */                      \
        struct discord_##type *sync;                                          \
    }

#define DISCORDT_RET_LIST(type)                                               \
    /** @brief Request's return context */                                    \
    struct discord_ret_##type##s {                                            \
        /** optional callback to be executed on a successful request */       \
        discord_on_##type##s done;                                            \
        DISCORDT_RET_DEFAULT_FIELDS;                                          \
        /** if an address is provided, then request will block the thread and \
           perform on-spot.                                                   \
           On success the response object will be written to the address,     \
           unless enabled with @ref DISCORD_SYNC_FLAG. */                     \
        struct discord_##type ***sync;                                        \
    }

#define DISCORDT_RETURN(type)                                                 \
    DISCORDT_RET_CALLBACK(type);                                              \
                                                                              \
    DISCORDT_RET(type)

#define DISCORDT_RETURN_LIST(type)                                            \
    DISCORDT_RET_CALLBACK_LIST(type);                                         \
                                                                              \
    DISCORDT_RET_LIST(type)

/******************************************************************************
 * Public return datatypes declaration
 ******************************************************************************/

/** @brief Triggers on a successful request */
typedef void (*discord_on_done)(struct discord *client, void *data);

/** @brief Triggers on a failed request */
typedef void (*discord_on_fail)(struct discord *client,
                                CCORDcode code,
                                void *data);

/** @brief Request's return context */
struct discord_ret {
    /** optional callback to be executed on a successful request */
    discord_on_done done;
    DISCORDT_RET_DEFAULT_FIELDS;
    /** if `true`, request will block the thread and perform on-spot */
    bool sync;
};

DISCORDT_RETURN(application_command);
DISCORDT_RETURN_LIST(application_command);
DISCORDT_RETURN(application_command_permission);
DISCORDT_RETURN_LIST(application_command_permission);
DISCORDT_RETURN_LIST(guild_application_command_permission);
DISCORDT_RETURN(interaction_response);

DISCORDT_RETURN(audit_log);

DISCORDT_RETURN(channel);
DISCORDT_RETURN_LIST(channel);
DISCORDT_RETURN(message);
DISCORDT_RETURN_LIST(message);
DISCORDT_RETURN(followed_channel);

DISCORDT_RETURN(user);
DISCORDT_RETURN_LIST(user);

DISCORDT_RETURN(invite);
DISCORDT_RETURN_LIST(invite);

DISCORDT_RETURN_LIST(thread_member);
DISCORDT_RETURN(thread_response_body);

DISCORDT_RETURN(emoji);
DISCORDT_RETURN_LIST(emoji);

DISCORDT_RETURN(guild);
DISCORDT_RETURN_LIST(guild);
DISCORDT_RETURN(guild_preview);
DISCORDT_RETURN(guild_member);
DISCORDT_RETURN_LIST(guild_member);
DISCORDT_RETURN(ban);
DISCORDT_RETURN_LIST(ban);
DISCORDT_RETURN(role);
DISCORDT_RETURN_LIST(role);
DISCORDT_RETURN(welcome_screen);

DISCORDT_RETURN(guild_template);

DISCORDT_RETURN_LIST(connection);
DISCORDT_RETURN_LIST(voice_region);

DISCORDT_RETURN(webhook);
DISCORDT_RETURN_LIST(webhook);

#endif /* DISCORD_TEMPLATES_H */
