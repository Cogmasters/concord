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
typedef void (*cast_init)(void *);
typedef void (*cast_cleanup)(void *);
typedef size_t (*cast_from_json)(const char *, size_t, void *);

/* helper typedef for getting sizeof of `struct discord_ret` common fields */
typedef struct {
    DISCORD_RET_DEFAULT_FIELDS;
} discord_ret_default_fields;

#define _RET_COPY_TYPED(dest, src)                                            \
    do {                                                                      \
        memcpy(&(dest), &(src), sizeof(discord_ret_default_fields));          \
        (dest).has_type = true;                                               \
        (dest).done.typed = (cast_done_typed)(src).done;                      \
        (dest).sync = (src).sync;                                             \
    } while (0)

#define _RET_COPY_TYPELESS(dest, src)                                         \
    do {                                                                      \
        memcpy(&(dest), &(src), sizeof(discord_ret_default_fields));          \
        (dest).has_type = false;                                              \
        (dest).done.typeless = (src).done;                                    \
        (dest).sync = (void *)(src).sync;                                     \
    } while (0)

/**
 * @brief Helper for setting attributes for a specs-generated return struct
 *
 * @param attr attributes handler to be initialized
 * @param type datatype of the struct
 * @param ret dispatch attributes
 */
#define DISCORD_ATTR_INIT(attr, type, ret)                                    \
    do {                                                                      \
        (attr).response.size = sizeof(struct type);                           \
        (attr).response.init = (cast_init)type##_init;                        \
        (attr).response.from_json = (cast_from_json)type##_from_json;         \
        (attr).response.cleanup = (cast_cleanup)type##_cleanup;               \
        if (ret) _RET_COPY_TYPED(attr.dispatch, *ret);                        \
    } while (0)

/**
 * @brief Helper for setting attributes for a specs-generated list
 *
 * @param attr attributes handler to be initialized
 * @param type datatype of the list
 * @param ret dispatch attributes
 */
#define DISCORD_ATTR_LIST_INIT(attr, type, ret)                               \
    do {                                                                      \
        (attr).response.size = sizeof(struct type);                           \
        (attr).response.from_json = (cast_from_json)type##_from_json;         \
        (attr).response.cleanup = (cast_cleanup)type##_cleanup;               \
        if (ret) _RET_COPY_TYPED(attr.dispatch, *ret);                        \
    } while (0)

/**
 * @brief Helper for setting attributes for attruests that doensn't expect a
 *      response object
 *
 * @param attr attributes handler to be initialized
 * @param ret dispatch attributes
 */
#define DISCORD_ATTR_BLANK_INIT(attr, ret)                                    \
    if (ret) _RET_COPY_TYPELESS(attr.dispatch, *ret)

#endif /* DISCORD_REQUEST_H */
