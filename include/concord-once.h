/**
 * @file concord-once.h
 * @author Cogmasters
 * @brief Initialized once
 */

#ifndef CONCORD_ONCE_H

/**
 * @brief If `SIGINT` is detected client(s) will be disconnected from their
 *      on-going session
 *
 * This global shall be set if a `SIGINT` is detected, running clients will
 *      then attempt to perform a clean disconnect, rather then just letting
 *      the program end abruptly.
 * @note client shall only attempt to disconnect if there aren't any active
 *      events waiting to be listened or reacted to
 */
extern int ccord_has_sigint;

/**
 * @brief Initialize global shared-resources not API-specific
 *
 * @return CCORD_OK on success, CCORD_GLOBAL_INIT on error
 */
CCORDcode ccord_global_init();

/** @brief Cleanup global shared-resources */
void ccord_global_cleanup();

#endif /* CONCORD_ONCE_H */
