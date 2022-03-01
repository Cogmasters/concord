/**
 * @file concord-once.h
 * @author Cogmasters
 * @brief Initialized once
 */

#ifndef CONCORD_ONCE_H

/**
 * @brief Initialize global shared-resources not API-specific
 *
 * @return CCORD_OK on success, CCORD_GLOBAL_INIT on error
 */
CCORDcode ccord_global_init();

/** @brief Cleanup global shared-resources */
void ccord_global_cleanup();

#endif /* CONCORD_ONCE_H */
