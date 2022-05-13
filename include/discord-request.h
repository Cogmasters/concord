/**
 * @file discord-request.h
 * @ingroup DiscordInternal
 * @author Cogmasters
 * @brief Generic macros for initializing a @ref discord_request
 */

#ifndef DISCORD_REQUEST_H
#define DISCORD_REQUEST_H

#define _RET_SAFECOPY_TYPED(dest, src)                                        \
    do {                                                                      \
        (dest).has_type = true;                                               \
        (dest).done.typed =                                                   \
            (void (*)(struct discord *, void *, const void *))(src).done;     \
        (dest).fail = (src).fail;                                             \
        (dest).data = (src).data;                                             \
        (dest).cleanup = (src).cleanup;                                       \
        (dest).high_p = (src).high_p;                                         \
        (dest).sync = (src).sync;                                             \
    } while (0)

#define _RET_SAFECOPY_TYPELESS(dest, src)                                     \
    do {                                                                      \
        (dest).has_type = false;                                              \
        (dest).done.typeless = (src).done;                                    \
        (dest).fail = (src).fail;                                             \
        (dest).data = (src).data;                                             \
        (dest).cleanup = (src).cleanup;                                       \
        (dest).high_p = (src).high_p;                                         \
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
        (req).response.init = (void (*)(void *))type##_init;                  \
        (req).response.from_json =                                            \
            (size_t(*)(const char *, size_t, void *))type##_from_json;        \
        (req).response.cleanup = (void (*)(void *))type##_cleanup;            \
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
        (req).response.from_json =                                            \
            (size_t(*)(const char *, size_t, void *))type##_from_json;        \
        (req).response.cleanup = (void (*)(void *))type##_cleanup;            \
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
