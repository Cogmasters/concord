/**
 * @file concord-notifier.h
 * @author Cogmasters
 * @brief Notifier fds listening to pipe, this can be used to propagate events
 */

#ifndef CONCORD_NOTIFIER_H
#define CONCORD_NOTIFIER_H

#include "concord-error.h"

/**
 * @brief Open notifier pipe
 *
 * @param pipe The pipe to open for emitting notifications
 * @return CCORDcode on success, CCORD_ERRNO on error
 */
CCORDcode ccord_notifier_open(int pipe[2]);

/**
 * @brief Close notifier pipe
 *
 * @param pipe The pipe to close
 */
void ccord_notifier_close(int pipe[2]);

/**
 * @brief Notify fds listening to pipe
 *
 * @param pipe The pipe to notify
 */
void ccord_notifier_notify(int pipe[2]);

/**
 * @brief Whether or not pipe is currently notifying fds
 *
 * @param pipe The pipe to check
 * @return 1 if notifying, 0 if not
 */
_Bool ccord_notifier_is_notifying(int pipe[2]);

/**
 * @brief Receive a listener for pipe notifications
 *
 * @param pipe The pipe to listen to
 * @return fd on success, -1 on error
 */
int ccord_notifier_listen(const int pipe[2]);

#endif /* CONCORD_NOTIFIER_H */
