/**
 * @file discord-request.h
 * @ingroup DiscordInternalREST
 * @author Cogmasters
 * @brief Generic macros for initializing a @ref discord_attributes
 */

#ifndef DISCORD_REQUEST_H
#define DISCORD_REQUEST_H

/* helper typedefs for casting */
typedef void (*cast_done_typed)(struct discord *,
                                struct discord_response *,
                                const void *);
typedef struct reflectc_wrap *(*cast_init)(struct reflectc *,
                                           void *,
                                           struct reflectc_wrap *);

/* helper typedef for getting sizeof of `struct discord_ret` common fields */
typedef struct {
    DISCORD_RET_DEFAULT_FIELDS;
} discord_ret_default_fields;

#define _RET_COPY_TYPED(_dest, _src)                                          \
    do {                                                                      \
        memcpy(&(_dest), &(_src), sizeof(discord_ret_default_fields));        \
        (_dest).has_type = true;                                              \
        (_dest).done.typed = (cast_done_typed)(_src).done;                    \
        (_dest).sync = (_src).sync;                                           \
    } while (0)

#define _RET_COPY_TYPELESS(_dest, _src)                                       \
    do {                                                                      \
        memcpy(&(_dest), &(_src), sizeof(discord_ret_default_fields));        \
        (_dest).has_type = false;                                             \
        (_dest).done.typeless = (_src).done;                                  \
        (_dest).sync = (void *)(_src).sync;                                   \
    } while (0)

/**
 * @brief Helper for setting attributes for a specs-generated return struct
 *
 * @param[out] _attr @ref discord_attributes handler to be initialized
 * @param[in] _type datatype of the struct
 * @param[in] _ret dispatch attributes
 * @param[in] _reason reason for request (if available)
 */
#define DISCORD_ATTR_INIT(_attr, _type, _ret, _reason)                        \
    do {                                                                      \
        (_attr).response.size = sizeof(struct _type);                         \
        (_attr).response.init = (cast_init)reflectc_from_##_type;             \
        (_attr).reason = _reason;                                             \
        if (_ret) _RET_COPY_TYPED((_attr).dispatch, *(_ret));                 \
    } while (0)

/**
 * @brief Helper for setting attributes for attributes that don't have a
 *      response object
 *
 * @param[out] _attr @ref discord_attributes handler to be initialized
 * @param[in] _ret dispatch attributes
 * @param[in] _reason reason for request (if available)
 */
#define DISCORD_ATTR_BLANK_INIT(_attr, _ret, _reason)                         \
    do {                                                                      \
        (_attr).reason = _reason;                                             \
        if (_ret) _RET_COPY_TYPELESS((_attr).dispatch, *(_ret));              \
    } while (0)

/**
 * @brief Helper for initializing attachments ids
 *
 * @param[in,out] attchs a @ref discord_attachments to have its IDs initialized
 */
#define DISCORD_ATTACHMENTS_IDS_INIT(_attchs)                                 \
    do {                                                                      \
        for (int i = 0; i < (_attchs)->size; ++i) {                           \
            (_attchs)->array[i].id = (u64snowflake)i;                         \
        }                                                                     \
    } while (0)

#endif /* DISCORD_REQUEST_H */
