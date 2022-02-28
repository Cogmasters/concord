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

#endif /* DISCORD_TEMPLATES_H */
