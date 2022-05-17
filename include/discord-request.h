/**
 * @file discord-request.h
 * @ingroup DiscordInternal
 * @author Cogmasters
 * @brief Generic macros for initializing a @ref discord_request
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

#define _RET_SAFECOPY_TYPED(dest, src)                                        \
    do {                                                                      \
        memcpy(&(dest), &(src), sizeof(discord_ret_default_fields));          \
        (dest).has_type = true;                                               \
        (dest).done.typed = (cast_done_typed)(src).done;                      \
        (dest).sync = (src).sync;                                             \
    } while (0)

#define _RET_SAFECOPY_TYPELESS(dest, src)                                     \
    do {                                                                      \
        memcpy(&(dest), &(src), sizeof(discord_ret_default_fields));          \
        (dest).has_type = false;                                              \
        (dest).done.typeless = (src).done;                                    \
        (dest).sync = (void *)(src).sync;                                     \
    } while (0)

/**
 * @brief Helper for setting attributes for a specs-generated return struct
 *
 * @param req request handler to be initialized
 * @param type datatype of the struct
 * @param ret request attributes
 */
#define DISCORD_REQ_INIT(req, type, ret)                                      \
    do {                                                                      \
        (req).response.size = sizeof(struct type);                            \
        (req).response.init = (cast_init)type##_init;                         \
        (req).response.from_json = (cast_from_json)type##_from_json;          \
        (req).response.cleanup = (cast_cleanup)type##_cleanup;                \
        if (ret) _RET_SAFECOPY_TYPED(req.dispatch, *ret);                     \
    } while (0)

/**
 * @brief Helper for setting attributes for a specs-generated list
 *
 * @param req request handler to be initialized
 * @param type datatype of the list
 * @param ret request attributes
 */
#define DISCORD_REQ_LIST_INIT(req, type, ret)                                 \
    do {                                                                      \
        (req).response.size = sizeof(struct type);                            \
        (req).response.from_json = (cast_from_json)type##_from_json;          \
        (req).response.cleanup = (cast_cleanup)type##_cleanup;                \
        if (ret) _RET_SAFECOPY_TYPED(req.dispatch, *ret);                     \
    } while (0)

/**
 * @brief Helper for setting request attributes expecting no response
 *
 * @param req request handler to be initialized
 * @param ret request attributes
 */
#define DISCORD_REQ_BLANK_INIT(req, ret)                                      \
    if (ret) _RET_SAFECOPY_TYPELESS(req.dispatch, *ret)

#endif /* DISCORD_REQUEST_H */
