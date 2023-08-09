/**
 * @file concord-once.h
 * @author Cogmasters
 * @brief Initialized once
 */

#ifndef CONCORD_ONCE_H

/** @brief Asynchronously shutdown all client(s) from their on-going sessions
 */
void ccord_shutdown_async();

/**
 * @brief Whether or not concord is currently shutting down
 *
 * If true, clients will then attempt to perform a clean disconnect, rather
 * than just letting the program end abruptly (e.g. in the case of a SIGINT).
 * @note client shall only attempt to disconnect if there aren't any active
 *    events waiting to be listened or reacted to
 */
int ccord_shutting_down();

/**
 * @brief Initialize global shared-resources not API-specific
 *
 * @return CCORD_OK on success, CCORD_GLOBAL_INIT on error
 */
CCORDcode ccord_global_init();


/**
 * @brief Initialize global shared-resources and set memory functions
 *
 * @note This function is for advanced use cases. Most users will want
 * to use @ref ccord_global_init.
 *
 * @return CCORD_OK on success, CCORD_GLOBAL_INIT on error
 */
CCORDcode ccord_global_init_memory(malloc_fn_t malloc_fn,
                                   calloc_fn_t calloc_fn,
                                   realloc_fn_t realloc_fn,
                                   free_fn_t free_fn,
                                   strdup_fn_t strdup_fn);

/**
 * @brief Initialize global shared-resources and set custom memory
 * functions.
 *
 * @note This is an API for advanced use cases. Most users
 * should use `ccord_global_init`.
 *
 * @sa ccord_global_init
 */

/** @brief Cleanup global shared-resources */
void ccord_global_cleanup();

#endif /* CONCORD_ONCE_H */
