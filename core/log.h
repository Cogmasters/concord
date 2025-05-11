/**
 * @file log.h
 * @author Cogmasters
 * @brief Maintain support for log.c deprecated functions using logmod.h as a
 *      wrapper
 * @attention This file is deprecated and will be removed in future releases
 * @deprecated since v3.0.0
 */

#ifndef LOG_DEPRECATED_SUPPORT_H
#define LOG_DEPRECATED_SUPPORT_H

#include "logmod.h"

/**
 * @brief Backwards compatible alias for logmod_log()
 * @deprecated since v3.0.0
 */
#define log_trace(...) logmod_log(TRACE, NULL, __VA_ARGS__)
/**
 * @brief Backwards compatible alias for logmod_log()
 * @deprecated since v3.0.0
 */
#define log_debug(...) logmod_log(DEBUG, NULL, __VA_ARGS__)
/**
 * @brief Backwards compatible alias for logmod_log()
 * @deprecated since v3.0.0
 */
#define log_info(...) logmod_log(INFO, NULL, __VA_ARGS__)
/**
 * @brief Backwards compatible alias for logmod_log()
 * @deprecated since v3.0.0
 */
#define log_warn(...) logmod_log(WARN, NULL, __VA_ARGS__)
/**
 * @brief Backwards compatible alias for logmod_log()
 * @deprecated since v3.0.0
 */
#define log_error(...) logmod_log(ERROR, NULL, __VA_ARGS__)
/**
 * @brief Backwards compatible alias for logmod_log()
 * @deprecated since v3.0.0
 */
#define log_fatal(...) logmod_log(FATAL, NULL, __VA_ARGS__)

#endif /* LOG_DEPRECATED_SUPPORT_H */
