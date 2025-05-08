/**
 * @file concord-once.h
 * @author Cogmasters
 * @brief Initialized once
 */

#ifndef CONCORD_ONCE_H
#define CONCORD_ONCE_H

#include "concord-error.h"

/** Callback function type for user initialization */
typedef CCORDcode (*ccord_once_cb)(long flags);

/**
 * @brief Register a user callback for initialization
 *
 * This callback will be executed exactly once during initialization
 * after all internal initializations have been performed.
 * Multiple callbacks can be registered from different modules, and they will
 * be executed in the order they were registered.
 *
 * @param callback The function to call during initialization
 * @param flags Flag to pass to the callback, that will be passed to the
 *      callback function
 * @return CCORD_OK on success, CCORD_BAD_PARAMETER if callback is NULL,
 *         CCORD_OUT_OF_MEMORY if memory allocation fails
 */
CCORDcode ccord_once_set_callback(ccord_once_cb callback, long flags);

/** @brief Asynchronously shutdown all client(s) from their on-going sessions
 */
void ccord_shutdown_async(void);

/**
 * @brief Whether or not concord is currently shutting down
 *
 * If true, clients will then attempt to perform a clean disconnect, rather
 * than just letting the program end abruptly (e.g. in the case of a SIGINT).
 * @note client shall only attempt to disconnect if there aren't any active
 *    events waiting to be listened or reacted to
 */
int ccord_shutting_down(void);

/** @brief dup shutdown fd to listen for ccord_shutdown_async() */
int ccord_dup_shutdown_fd(void);

/**
 * @brief Initialize context once
 *
 * @param once Pointer to a static boolean flag that will be set to true if the
 *      initialization was successful. This flag should be used to ensure that
 *      the initialization is only performed once.
 * @return CCORD_OK on success, CCORD_GLOBAL_INIT on error
 */
CCORDcode ccord_once(_Bool *once);

/** @brief Cleanup global shared-resources */
void ccord_once_cleanup(void);

#endif /* CONCORD_ONCE_H */
