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
 * @CCORD_return
 */
CCORDcode ccord_once_set_callback(ccord_once_cb callback, long flags);

/**
 * @brief Initialize context once
 *
 * @param once Pointer to a static boolean flag that will be set to true if the
 *      initialization was successful. This flag should be used to ensure that
 *      the initialization is only performed once.
 * @CCORD_return
 */
CCORDcode ccord_once(_Bool *once);

/**
 * @brief Cleanup once context
 *
 * This function will be called to cleanup the once context.
 * It will be called when the program is exiting, and it will
 * cleanup all registered callbacks.
 */
void ccord_once_cleanup(void);

#endif /* CONCORD_ONCE_H */
