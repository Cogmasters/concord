/**
 * @file discord-worker.h
 * @author Cogmasters
 * @brief Global threadpool
 */

#ifndef DISCORD_WORKER_H
#define DISCORD_WORKER_H

#include "error.h"

/* forward declaration */
struct discord;
/**/

/** @defgroup DiscordInternalWorker Global threadpool
 * @ingroup DiscordInternal
 * @brief A global threadpool for worker-threads handling
 *  @{ */

/**
 * @brief Initialize global threadpool and priority queue
 * @return `0` on success, `1` if it has already been initialized
 */
int discord_worker_global_init(void);

/** @brief Cleanup global threadpool and priority queue */
void discord_worker_global_cleanup(void);

/**
 * @brief Run a callback from a worker thread
 *
 * @param client the client that will be using the worker thread
 * @param callback user callback to be executed
 * @param data user data to be passed to callback
 * @CCORD_return
 */
CCORDcode discord_worker_add(struct discord *client,
                             void (*callback)(void *data),
                             void *data);

/**
 * @brief Wait until worker-threads being used by `client` have been joined
 *
 * @param client the client currently using a worker thread
 * @CCORD_return
 */
CCORDcode discord_worker_join(struct discord *client);

/** @} DiscordInternalWorker */

#endif /* DISCORD_WORKER_H */
