/**
 * @file concord-once.h
 * @author Cogmasters
 * @brief Initialized once
 */

#ifndef CONCORD_ONCE_H

/** @brief Asynchronously shutdown all client(s) from their on-going sessions */
void ccord_shutdown_async();

/**
 * @brief Whether or not concord is currently shutting down
 *
 * If true, clients will then attempt to perform a clean disconnect, rather than
 *    just letting the program end abruptly (e.g. in the case of a SIGINT).
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

/** @brief Cleanup global shared-resources */
void ccord_global_cleanup();

#endif /* CONCORD_ONCE_H */
