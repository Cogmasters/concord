#ifndef LOGMOD_H
#define LOGMOD_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Define symbol visibility for LogMod API
 *
 * Define LOGMOD_STATIC to make all symbols static (for single-file inclusion)
 */
#ifdef LOGMOD_STATIC
#define LOGMOD_API static
#else
#define LOGMOD_API extern
#endif /* LOGMOD_STATIC */

#include <stdio.h>
#include <stdarg.h>

/**
 * @brief Format string checking attribute for printf-like functions
 *
 * This macro adds format string checking when supported by the compiler,
 * helping catch format string errors at compile time.
 *
 * @param a Format string parameter position
 * @param b First variadic argument position
 */
#if defined(__MINGW32__)                                                      \
    || (defined(__GNUC__) && __GNUC__ > 4 ? true : __GNUC_PATCHLEVEL__ >= 4)  \
    || defined(__USE_MINGW_ANSI_STDIO)
#define LOGMOD_PRINTF_LIKE(a, b) __attribute__((format(gnu_printf, a, b)))
#else
#define LOGMOD_PRINTF_LIKE(a, b)
#endif

/**
 * @brief Default application ID for the fallback logger
 *
 * Can be overridden by defining this macro before including logmod.h
 */
#ifndef LOGMOD_FALLBACK_APPLICATION_ID
#define LOGMOD_FALLBACK_APPLICATION_ID "APPLICATION"
#endif /* LOGMOD_FALLBACK_APPLICATION_ID */

/**
 * @brief Default context ID for the fallback logger
 *
 * Can be overridden by defining this macro before including logmod.h
 */
#ifndef LOGMOD_FALLBACK_CONTEXT_ID
#define LOGMOD_FALLBACK_CONTEXT_ID "GLOBAL"
#endif /* LOGMOD_FALLBACK_CONTEXT_ID */

/**
 * @brief Log levels supported by LogMod
 *
 * Built-in log levels ordered by severity (lowest to highest)
 * Custom log levels should start at LOGMOD_LEVEL_CUSTOM
 */
enum logmod_levels {
    LOGMOD_LEVEL_TRACE = 0, /**< Most detailed logging for tracing execution */
    LOGMOD_LEVEL_DEBUG, /**< Debug information */
    LOGMOD_LEVEL_INFO, /**< Informational messages */
    LOGMOD_LEVEL_WARN, /**< Warning messages */
    LOGMOD_LEVEL_ERROR, /**< Error messages */
    LOGMOD_LEVEL_FATAL, /**< Fatal errors that cause termination */
    __LOGMOD_LEVEL_MAX, /**< Internal marker for built-in level count */
    /** user defined log level must start with this value */
    LOGMOD_LEVEL_CUSTOM = __LOGMOD_LEVEL_MAX
};

/**
 * @brief Error codes returned by LogMod functions
 */
typedef enum {
    LOGMOD_ERRNO = -2, /**< System error, check errno */
    LOGMOD_BAD_PARAMETER = -1, /**< Invalid parameter passed to function */
    LOGMOD_OK = 0, /**< Success */
    LOGMOD_OK_CONTINUE, /**< Success, continue with default behavior */
    LOGMOD_OK_SKIPPED /**< Success, logger has been skipped from logging due to
                         being disabled by user */
} logmod_err;

/**
 * @brief Configuration options for a logger
 */
struct logmod_options {
    FILE *logfile; /**< File to write logs to, or NULL for no file output */
    int quiet; /**< If 1, suppress console output */
    int color; /**< If 1, enable ANSI colors on console output */
    int hide_context_id; /**< If 1, suppress context ID in log messages */
    int show_application_id; /**< If 1, show application ID in log messages */
    unsigned level; /**< Minimum level to log (suppress messages below this) */
};

/**
 * @brief Label properties for a log level
 *
 * @see @ref LOGMOD_LABEL_COLOR
 */
struct logmod_label {
    const char *const name; /**< Display name of the log level */
    const char *const color; /**< ANSI color code for this label */
    const char *const style; /**< ANSI style code for this label */
    const char *const visibility; /**< ANSI visibility code for this label */
    const int output; /**< Output stream: 0 = stdout, 1 = stderr */
};

/**
 * @brief Helper macro to define label color, style, and visibility at once
 *
 * @param _color Color name (e.g., RED, GREEN)
 * @param _style Style name (e.g., BOLD, REGULAR)
 * @param _visibility Visibility name (e.g., FOREGROUND, BACKGROUND)
 */
#define LOGMOD_LABEL_COLOR(_color, _style, _visibility)                       \
    LOGMOD_COLOR_##_color, LOGMOD_STYLE_##_style,                             \
        LOGMOD_VISIBILITY_##_visibility

/**
 * @brief Information about a log entry
 */
struct logmod_info {
    const unsigned line; /**< Source line number */
    const char *const filename; /**< Source filename */
    const unsigned level; /**< Log level */
    const struct logmod_label *const label; /**< Label for this log level */
    const struct tm
        *const time_info; /**< Time for when entry has been triggered */
};

/* forward declaration */
struct logmod_logger;
struct tm;
/**/

/**
 * @brief Lock function type for thread safety
 *
 * @param logger The logger instance
 * @param should_lock 1 to acquire lock, 0 to release
 */
typedef void (*logmod_lock)(const struct logmod_logger *logger,
                            int should_lock);

/**
 * @brief Callback function type for custom log handling
 *
 * @param logger The logger instance
 * @param info Information about the log entry
 * @param fmt Format string
 * @param args Variable arguments list
 * @return LOGMOD_OK to skip default handling, LOGMOD_OK_CONTINUE to also
 * perform default handling
 */
typedef logmod_err (*logmod_callback)(const struct logmod_logger *logger,
                                      const struct logmod_info *info,
                                      const char *fmt,
                                      va_list args);

/**
 * @brief ANSI color values
 */
#define LOGMOD_COLOR_BLACK   "0" /**< Black color */
#define LOGMOD_COLOR_RED     "1" /**< Red color */
#define LOGMOD_COLOR_GREEN   "2" /**< Green color */
#define LOGMOD_COLOR_YELLOW  "3" /**< Yellow color */
#define LOGMOD_COLOR_BLUE    "4" /**< Blue color */
#define LOGMOD_COLOR_MAGENTA "5" /**< Magenta color */
#define LOGMOD_COLOR_CYAN    "6" /**< Cyan color */
#define LOGMOD_COLOR_WHITE   "7" /**< White color */

/**
 * @brief ANSI text style values
 */
#define LOGMOD_STYLE_REGULAR       "0" /**< Regular text style */
#define LOGMOD_STYLE_BOLD          "1" /**< Bold text style */
#define LOGMOD_STYLE_UNDERLINE     "4" /**< Underlined text style */
#define LOGMOD_STYLE_STRIKETHROUGH "9" /**< Strikethrough text style */

/**
 * @brief ANSI text visibility mode values
 */
#define LOGMOD_VISIBILITY_FOREGROUND "3" /**< Foreground color */
#define LOGMOD_VISIBILITY_BACKGROUND "4" /**< Background color */
#define LOGMOD_VISIBILITY_INTENSITY  "9" /**< Intensity (bright) foreground */
#define LOGMOD_VISIBILITY_BACKGROUND_INTENSITY                                \
    "10" /**< Intensity (bright) background */

/**
 * @brief Internal macro for defining logger attributes
 *
 * Used to define both const and non-const versions of the logger structure
 * with the same fields.
 *
 * @param _qualifier Qualifier to apply to mutable fields (const or empty)
 */
#define __LOGMOD_LOGGER_ATTRS(_qualifier)                                     \
    const char *context_id;                                                   \
    _qualifier struct logmod_options options;                                 \
    const long *counter;                                                      \
    _qualifier logmod_callback callback;                                      \
    _qualifier void *user_data;                                               \
    const struct logmod_label *_qualifier custom_labels;                      \
    _qualifier size_t num_custom_labels;                                      \
    _qualifier int disabled

#define __BLANK
/**
 * @brief Mutable version of the logger structure
 *
 * This version allows modification of the logger properties
 */
struct logmod_mut_logger {
    __LOGMOD_LOGGER_ATTRS(__BLANK);
};
#undef __BLANK

/**
 * @brief Immutable logger structure
 *
 * This is the public-facing version of the logger with const-qualified fields
 */
struct logmod_logger {
    __LOGMOD_LOGGER_ATTRS(const);
};

#undef __LOGMOD_LOGGER_ATTRS

/**
 * @brief Main logging context structure
 *
 * Contains the global state for a logging context
 */
struct logmod {
    const char *application_id; /**< Application identifier */
    const struct logmod_logger *loggers; /**< Array of loggers */
    const size_t length; /**< Current number of loggers */
    const size_t real_length; /**< Maximum capacity of loggers array */
    long counter; /**< Global log message counter */
    const struct logmod_options
        default_options; /**< Default options for new loggers */
    logmod_lock lock; /**< Lock function for thread safety */
};

/**
 * @brief Initialize the logging context
 *
 * @param logmod Pointer to the logging context structure
 * @param application_id Application identifier string
 * @param table Array to store loggers (must be pre-allocated)
 * @param length Capacity of the table array
 * @return LOGMOD_OK on success, error code on failure
 */
LOGMOD_API logmod_err logmod_init(struct logmod *logmod,
                                  const char *const application_id,
                                  struct logmod_logger table[],
                                  unsigned length);

/**
 * @brief Clean up the logging context
 *
 * @param logmod Pointer to the logging context structure
 * @return LOGMOD_OK on success
 */
LOGMOD_API logmod_err logmod_cleanup(struct logmod *logmod);

/**
 * @brief Set the lock function for thread safety
 *
 * @param logmod Pointer to the logging context structure
 * @param lock Lock function to use
 * @return LOGMOD_OK on success, error code on failure
 */
LOGMOD_API logmod_err logmod_set_lock(struct logmod *logmod, logmod_lock lock);

/**
 * @brief Set default options for all new loggers
 *
 * @param logmod Pointer to the logging context structure
 * @param options Default options to use for new loggers
 * @return LOGMOD_OK on success, error code on failure
 */
LOGMOD_API logmod_err logmod_set_options(struct logmod *logmod,
                                         struct logmod_options options);

/**
 * @brief Toggle a specific logger from logging (default is true)
 *
 * @param logmod Pointer to the logging context structure
 * @param context_id The context id of the logger to be enabled or disabled
 * @return LOGMOD_OK on success, error code on failure
 */
LOGMOD_API logmod_err logmod_toggle_logger(struct logmod *logmod,
                                           const char *const context_id);

/**
 * @brief Set user data for a logger
 *
 * @param logger Pointer to the logger
 * @param user_data Pointer to user-defined data
 * @return LOGMOD_OK on success, error code on failure
 */
LOGMOD_API logmod_err logmod_logger_set_data(struct logmod_logger *logger,
                                             void *user_data);

/**
 * @brief Set callback function and custom labels for a logger
 *
 * @param logger Pointer to the logger
 * @param custom_labels Array of custom log level labels or NULL
 * @param num_custom_labels Number of custom labels in the array
 * @param callback Callback function for log processing
 * @return LOGMOD_OK on success, error code on failure
 */
LOGMOD_API logmod_err
logmod_logger_set_callback(struct logmod_logger *logger,
                           const struct logmod_label *const custom_labels,
                           const size_t num_custom_labels,
                           logmod_callback callback);

/**
 * @brief Set all options for a logger at once
 *
 * @param logger Pointer to the logger
 * @param options Options structure
 * @return LOGMOD_OK on success, error code on failure
 */
LOGMOD_API logmod_err logmod_logger_set_options(struct logmod_logger *logger,
                                                struct logmod_options options);

/**
 * @brief Set visibility of application ID and context ID in log messages
 *
 * @param logger Pointer to the logger
 * @param show_app_id 1 to show application ID, 0 to hide
 * @param show_context_id 1 to show context ID, 0 to hide
 * @return LOGMOD_OK on success, error code on failure
 */
LOGMOD_API logmod_err logmod_logger_set_id_visibility(
    struct logmod_logger *logger, int show_app_id, int show_context_id);

/**
 * @brief Set quiet mode for a logger
 *
 * @param logger Pointer to the logger
 * @param quiet 1 to enable quiet mode (suppress console output), 0 to disable
 * @return LOGMOD_OK on success, error code on failure
 */
LOGMOD_API logmod_err logmod_logger_set_quiet(struct logmod_logger *logger,
                                              int quiet);

/**
 * @brief Set color mode for a logger
 *
 * @param logger Pointer to the logger
 * @param color 1 to enable colored output, 0 to disable
 * @return LOGMOD_OK on success, error code on failure
 */
LOGMOD_API logmod_err logmod_logger_set_color(struct logmod_logger *logger,
                                              int color);

/**
 * @brief Set minimum log level for a logger
 *
 * @param logger Pointer to the logger
 * @param level Minimum level to log (messages below this will be suppressed)
 * @return LOGMOD_OK on success, error code on failure
 */
LOGMOD_API logmod_err logmod_logger_set_level(struct logmod_logger *logger,
                                              unsigned level);

/**
 * @brief Set logfile for a logger
 *
 * @param logger Pointer to the logger
 * @param logfile File pointer to write logs to, or NULL to disable
 * @return LOGMOD_OK on success, error code on failure
 */
LOGMOD_API logmod_err logmod_logger_set_logfile(struct logmod_logger *logger,
                                                FILE *logfile);

/**
 * @brief Get or create a logger by context ID
 *
 * @param logmod Pointer to the logging context
 * @param context_id Context identifier string
 * @return Pointer to the logger, or NULL if the table is full
 */
LOGMOD_API struct logmod_logger *logmod_get_logger(
    struct logmod *logmod, const char *const context_id);

/**
 * @brief Get the label for a specific log level
 *
 * @param logger Pointer to the logger
 * @param level Log level to get the label for
 * @return Pointer to the label structure, or NULL if invalid
 */
LOGMOD_API const struct logmod_label *logmod_logger_get_label(
    const struct logmod_logger *logger, const unsigned level);

/**
 * @brief Get the level value for a label name
 *
 * @param logger Pointer to the logger
 * @param label Label name to look up
 * @return Level value, or LOGMOD_BAD_PARAMETER if invalid
 */
LOGMOD_API long logmod_logger_get_level(const struct logmod_logger *logger,
                                        const char *const label);

/**
 * @brief Get the global message counter for a logger
 *
 * @param logger Pointer to the logger
 * @return Current counter value, or -1 if logger is NULL
 */
LOGMOD_API long logmod_logger_get_counter(const struct logmod_logger *logger);

/**
 * @brief Log a message (C89 compatible version)
 *
 * @param _level Log level (without LOGMOD_LEVEL_ prefix)
 * @param _logger Logger to use, or NULL for default
 * @param _parenthesized_params Format and arguments in parentheses
 * @param num_params Number of arguments in the format string
 */
#define logmod_nlog(_level, _logger, _parenthesized_params, num_params)       \
    _logmod_log(_logger, __LINE__, __FILE__, LOGMOD_LEVEL_##_level,           \
                LOGMOD_SPREAD_TUPLE_##num_params _parenthesized_params)

#if __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
/**
 * @brief Internal helper macro for C99 variable arguments processing
 *
 * @param _level The log level
 * @param _logger The logger instance
 * @param _line Source line number
 * @param _file Source file path
 * @param _fmt Format string
 * @param ... Additional format arguments
 */
#define _logmod_log_permissive(_level, _logger, _line, _file, _fmt, ...)      \
    _logmod_log(_logger, _line, _file, _level, _fmt "%s", __VA_ARGS__)

/**
 * @brief Log a message with specified level (C99 version with variadic macro
 * support)
 *
 * @param _level Log level (e.g., INFO, DEBUG, ERROR)
 * @param _logger The logger instance or NULL for default logger
 * @param ... Format string followed by format arguments
 */
#define logmod_log(_level, _logger, ...)                                      \
    _logmod_log_permissive(LOGMOD_LEVEL_##_level, _logger, __LINE__,          \
                           __FILE__, __VA_ARGS__, "")
#else
/**
 * @brief Alias to logmod_nlog for C89 compatibility
 */
#define logmod_log logmod_nlog
#endif /* __STDC_VERSION__ */

/**
 * @brief Internal logging implementation function
 *
 * @param logger The logger instance
 * @param line Source line number
 * @param filename Source file path
 * @param level Log level
 * @param fmt Format string
 * @param ... Format arguments
 * @return logmod_err LOGMOD_OK on success, or error code on failure
 */
LOGMOD_API logmod_err _logmod_log(const struct logmod_logger *logger,
                                  const unsigned line,
                                  const char *const filename,
                                  const unsigned level,
                                  const char *fmt,
                                  ...) LOGMOD_PRINTF_LIKE(5, 6);

/**
 * @brief Encodes text with ANSI colors and styles
 *
 * @param buf Text buffer to encode
 * @param _color Color code (LOGMOD_COLOR_* macros)
 * @param _style Style code (LOGMOD_STYLE_* macros)
 * @param _visibility Visibility code (LOGMOD_VISIBILITY_* macros)
 */
#define LOGMOD_ENCODE(buf, _color, _style, _visibility)                       \
    "\x1b[" _style ";" _visibility _color "m" buf "\x1b[0m"

/**
 * @brief Static encoding of text with ANSI colors (compile-time)
 *
 * @param buf The text to encode
 * @param _color Color name (e.g., RED, GREEN)
 * @param _style Style name (e.g., BOLD, REGULAR)
 * @param _visibility Visibility name (e.g., FOREGROUND, BACKGROUND)
 */
#define LOGMOD_ENCODE_STATIC(buf, _color, _style, _visibility)                \
    LOGMOD_ENCODE(buf, LOGMOD_COLOR_##_color, LOGMOD_STYLE_##_style,          \
                  LOGMOD_VISIBILITY_##_visibility)

/**
 * @brief Dynamic encoding of text with ANSI colors (respects toggle)
 *
 * @param _toggle Toggle to enable or disable color encoding
 * @param buf The text to encode
 * @param _color Color name (e.g., RED, GREEN)
 * @param _style Style name (e.g., BOLD, REGULAR)
 * @param _visibility Visibility name (e.g., FOREGROUND, BACKGROUND)
 * @return Colored text if toggle is enabled, or original text otherwise
 */
#define LOGMOD_ENCODE_TOGGLE(_toggle, buf, _color, _style, _visibility)       \
    ((_toggle)                                                                \
         ? LOGMOD_ENCODE(buf, LOGMOD_COLOR_##_color, LOGMOD_STYLE_##_style,   \
                         LOGMOD_VISIBILITY_##_visibility)                     \
         : buf)

/**
 * @brief Dynamic encoding of text with ANSI colors (respects logger color
 * setting)
 *
 * @param _logger The logger instance to check for color enabled setting
 * @param buf The text to encode
 * @param _color Color name (e.g., RED, GREEN)
 * @param _style Style name (e.g., BOLD, REGULAR)
 * @param _visibility Visibility name (e.g., FOREGROUND, BACKGROUND)
 * @return Colored text if colors enabled, or original text otherwise
 */
#define LOGMOD_ENCODE_LOGGER(_logger, buf, _color, _style, _visibility)       \
    LOGMOD_ENCODE_TOGGLE((_logger)->options.color, buf, _color, _style,       \
                         _visibility)

/** @brief Shorthand for LOGMOD_ENCODE_STATIC */
#define LMS LOGMOD_ENCODE_STATIC
/** @brief Shorthand for LOGMOD_ENCODE_TOGGLE */
#define LMT LOGMOD_ENCODE_TOGGLE
/** @brief Shorthand for LOGMOD_ENCODE_LOGGER */
#define LML LOGMOD_ENCODE_LOGGER
/** @brief Shorthand for LOGMOD_ENCODE */
#define LME LOGMOD_ENCODE

#define LOGMOD_SPREAD_TUPLE_0(_fmt)                 _fmt
#define LOGMOD_SPREAD_TUPLE_1(_fmt, _1)             _fmt, _1
#define LOGMOD_SPREAD_TUPLE_2(_fmt, _1, _2)         _fmt, _1, _2
#define LOGMOD_SPREAD_TUPLE_3(_fmt, _1, _2, _3)     _fmt, _1, _2, _3
#define LOGMOD_SPREAD_TUPLE_4(_fmt, _1, _2, _3, _4) _fmt, _2, _3, _4
#define LOGMOD_SPREAD_TUPLE_5(_fmt, _1, _2, _3, _4, _5)                       \
    _fmt, _1, _2, _3, _4, _5
#define LOGMOD_SPREAD_TUPLE_6(_fmt, _1, _2, _3, _4, _5, _6)                   \
    _fmt, _1, _2, _3, _4, _6
#define LOGMOD_SPREAD_TUPLE_7(_fmt, _1, _2, _3, _4, _5, _6, _7)               \
    _fmt, _1, _2, _3, _4, _5, _6, _7
#define LOGMOD_SPREAD_TUPLE_8(_fmt, _1, _2, _3, _4, _5, _6, _7, _8)           \
    _fmt, _1, _2, _3, _4, _5, _6, _7, _8
#define LOGMOD_SPREAD_TUPLE_9(_fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9)       \
    _fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9
#define LOGMOD_SPREAD_TUPLE_10(_fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    _fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10
#define LOGMOD_SPREAD_TUPLE_11(_fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
                               _11)                                           \
    _fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11
#define LOGMOD_SPREAD_TUPLE_12(_fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
                               _11, _12)                                      \
    _fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12
#define LOGMOD_SPREAD_TUPLE_13(_fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
                               _11, _12, _13)                                 \
    _fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13
#define LOGMOD_SPREAD_TUPLE_14(_fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
                               _11, _12, _13, _14)                            \
    _fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14
#define LOGMOD_SPREAD_TUPLE_15(_fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
                               _11, _12, _13, _14, _15)                       \
    _fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15
#define LOGMOD_SPREAD_TUPLE_16(_fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
                               _11, _12, _13, _14, _15, _16)                  \
    _fmt, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16

#ifndef LOGMOD_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

#include "logmod.h"

static const struct logmod_label default_labels[__LOGMOD_LEVEL_MAX] = {
    /*[LOGMOD_LEVEL_TRACE]:*/
    { "TRACE", LOGMOD_LABEL_COLOR(BLUE, REGULAR, BACKGROUND_INTENSITY), 0 },
    /*[LOGMOD_LEVEL_DEBUG]:*/
    { "DEBUG", LOGMOD_LABEL_COLOR(CYAN, REGULAR, BACKGROUND), 0 },
    /*[LOGMOD_LEVEL_INFO]: */
    { "INFO", LOGMOD_LABEL_COLOR(GREEN, REGULAR, BACKGROUND), 0 },
    /*[LOGMOD_LEVEL_WARN]: */
    { "WARN", LOGMOD_LABEL_COLOR(YELLOW, REGULAR, BACKGROUND), 1 },
    /*[LOGMOD_LEVEL_ERROR]:*/
    { "ERROR", LOGMOD_LABEL_COLOR(RED, REGULAR, BACKGROUND), 1 },
    /*[LOGMOD_LEVEL_FATAL]:*/
    { "FATAL", LOGMOD_LABEL_COLOR(MAGENTA, REGULAR, BACKGROUND), 1 },
};

/** @brief Get @ref logmod from any @ref logmod_logger */
#define LOGMOD_FROM_LOGGER(_ctx)                                              \
    ((struct logmod *)((char *)(_ctx)->counter                                \
                       - offsetof(struct logmod, counter)))

#define _LOGMOD_EXPECT(_cond, _error, _return)                                \
    do {                                                                      \
        if (!(_cond)) {                                                       \
            switch ((_error)) {                                               \
            case LOGMOD_BAD_PARAMETER:                                        \
                logmod_nlog(ERROR, NULL, ("Bad parameter: %s", #_cond), 1);   \
                break;                                                        \
            case LOGMOD_ERRNO:                                                \
                logmod_nlog(ERROR, NULL,                                      \
                            ("System error (check errno): %s", #_cond), 1);   \
                break;                                                        \
            default:                                                          \
                logmod_nlog(ERROR, NULL, ("Unknown error: %s", #_cond), 1);   \
                break;                                                        \
            }                                                                 \
            return (_return);                                                 \
        }                                                                     \
    } while (0)

/**
 * @brief Check if a condition is met and log an error message if not
 *
 * @param _cond Condition to check
 * @param _error Error code to return if the condition is false
 */
#define LOGMOD_EXPECT(_cond, _error) _LOGMOD_EXPECT(_cond, _error, _error)

static void
_logmod_lock_noop(const struct logmod_logger *_, int __)
{
    (void)_;
    (void)__;
}

LOGMOD_API logmod_err
logmod_init(struct logmod *logmod,
            const char *const application_id,
            struct logmod_logger table[],
            unsigned length)
{
    size_t *mut_real_length = (size_t *)&logmod->real_length;
    LOGMOD_EXPECT(logmod != NULL, LOGMOD_BAD_PARAMETER);
    LOGMOD_EXPECT(application_id && *application_id, LOGMOD_BAD_PARAMETER);
    LOGMOD_EXPECT(table != NULL, LOGMOD_BAD_PARAMETER);
    LOGMOD_EXPECT(length > 0, LOGMOD_BAD_PARAMETER);
    memset(logmod, 0, sizeof *logmod);
    memset(table, 0, length * sizeof *table);
    logmod->application_id = application_id;
    logmod->loggers = table;
    *mut_real_length = length;
    logmod->lock = _logmod_lock_noop;
    return LOGMOD_OK;
}

LOGMOD_API logmod_err
logmod_cleanup(struct logmod *logmod)
{
    memset((void *)logmod->loggers, 0,
           logmod->real_length * sizeof *logmod->loggers);
    memset(logmod, 0, sizeof *logmod);
    return LOGMOD_OK;
}

LOGMOD_API logmod_err
logmod_set_lock(struct logmod *logmod, logmod_lock lock)
{
    LOGMOD_EXPECT(logmod != NULL, LOGMOD_BAD_PARAMETER);
    logmod->lock = lock;
    return LOGMOD_OK;
}

LOGMOD_API logmod_err
logmod_set_options(struct logmod *logmod, struct logmod_options options)
{
    struct logmod_options *mut_default_options =
        (struct logmod_options *)&logmod->default_options;
    LOGMOD_EXPECT(logmod != NULL, LOGMOD_BAD_PARAMETER);
    *mut_default_options = options;
    return LOGMOD_OK;
}

LOGMOD_API logmod_err
logmod_toggle_logger(struct logmod *logmod, const char *const context_id)
{
    struct logmod_mut_logger *mut_logger;
    logmod->lock(NULL, 1);
    mut_logger =
        (struct logmod_mut_logger *)logmod_get_logger(logmod, context_id);
    logmod->lock(NULL, 0);
    LOGMOD_EXPECT(mut_logger != NULL, LOGMOD_BAD_PARAMETER);
    mut_logger->disabled = !mut_logger->disabled;
    return LOGMOD_OK;
}

LOGMOD_API logmod_err
logmod_logger_set_id_visibility(struct logmod_logger *logger,
                                int show_app_id,
                                int show_context_id)
{
    struct logmod_mut_logger *mut_logger = (struct logmod_mut_logger *)logger;
    LOGMOD_EXPECT(logger != NULL, LOGMOD_BAD_PARAMETER);
    mut_logger->options.show_application_id = show_app_id;
    mut_logger->options.hide_context_id = !show_context_id;
    return LOGMOD_OK;
}

LOGMOD_API logmod_err
logmod_logger_set_data(struct logmod_logger *logger, void *user_data)
{
    struct logmod_mut_logger *mut_logger = (struct logmod_mut_logger *)logger;
    LOGMOD_EXPECT(logger != NULL, LOGMOD_BAD_PARAMETER);
    mut_logger->user_data = user_data;
    return LOGMOD_OK;
}

LOGMOD_API logmod_err
logmod_logger_set_callback(struct logmod_logger *logger,
                           const struct logmod_label *const custom_labels,
                           const size_t num_custom_labels,
                           logmod_callback callback)
{
    struct logmod_mut_logger *mut_logger = (struct logmod_mut_logger *)logger;
    LOGMOD_EXPECT(logger != NULL, LOGMOD_BAD_PARAMETER);
    mut_logger->callback = callback;
    if (custom_labels != NULL) {
        LOGMOD_EXPECT(callback != NULL, LOGMOD_BAD_PARAMETER);
        LOGMOD_EXPECT(num_custom_labels > 0, LOGMOD_BAD_PARAMETER);
        mut_logger->custom_labels = custom_labels;
        mut_logger->num_custom_labels = num_custom_labels;
    }
    return LOGMOD_OK;
}

LOGMOD_API logmod_err
logmod_logger_set_options(struct logmod_logger *logger,
                          struct logmod_options options)
{
    struct logmod_mut_logger *mut_logger = (struct logmod_mut_logger *)logger;
    LOGMOD_EXPECT(logger != NULL, LOGMOD_BAD_PARAMETER);
    mut_logger->options = options;
    return LOGMOD_OK;
}

LOGMOD_API logmod_err
logmod_logger_set_quiet(struct logmod_logger *logger, int quiet)
{
    struct logmod_mut_logger *mut_logger = (struct logmod_mut_logger *)logger;
    LOGMOD_EXPECT(logger != NULL, LOGMOD_BAD_PARAMETER);
    mut_logger->options.quiet = quiet;
    return LOGMOD_OK;
}

LOGMOD_API logmod_err
logmod_logger_set_color(struct logmod_logger *logger, int color)
{
    struct logmod_mut_logger *mut_logger = (struct logmod_mut_logger *)logger;
    LOGMOD_EXPECT(logger != NULL, LOGMOD_BAD_PARAMETER);
    mut_logger->options.color = color;
    return LOGMOD_OK;
}

LOGMOD_API logmod_err
logmod_logger_set_level(struct logmod_logger *logger, unsigned level)
{
    struct logmod_mut_logger *mut_logger = (struct logmod_mut_logger *)logger;
    LOGMOD_EXPECT(logger != NULL, LOGMOD_BAD_PARAMETER);
    mut_logger->options.level = level;
    return LOGMOD_OK;
}

LOGMOD_API logmod_err
logmod_logger_set_logfile(struct logmod_logger *logger, FILE *logfile)
{
    struct logmod_mut_logger *mut_logger = (struct logmod_mut_logger *)logger;
    LOGMOD_EXPECT(logger != NULL, LOGMOD_BAD_PARAMETER);
    mut_logger->options.logfile = logfile;
    return LOGMOD_OK;
}

LOGMOD_API const struct logmod_label *
logmod_logger_get_label(const struct logmod_logger *logger,
                        const unsigned level)
{
    if (level < LOGMOD_LEVEL_CUSTOM) {
        return &default_labels[level];
    }
    if (logger && level >= LOGMOD_LEVEL_CUSTOM
        && level < (LOGMOD_LEVEL_CUSTOM + logger->num_custom_labels))
    {
        return &logger->custom_labels[level - LOGMOD_LEVEL_CUSTOM];
    }
    return NULL;
}

LOGMOD_API long
logmod_logger_get_level(const struct logmod_logger *logger,
                        const char *const label)
{
    size_t i;
    LOGMOD_EXPECT(logger != NULL, LOGMOD_BAD_PARAMETER);
    LOGMOD_EXPECT(label != NULL, LOGMOD_BAD_PARAMETER);
    for (i = 0; i < __LOGMOD_LEVEL_MAX; ++i) {
        if (strcmp(label, default_labels[i].name) == 0) {
            return (long)i;
        }
    }
    for (i = 0; i < logger->num_custom_labels; ++i) {
        if (strcmp(label, logger->custom_labels[i].name) == 0) {
            return (long)(i + LOGMOD_LEVEL_CUSTOM);
        }
    }
    return LOGMOD_BAD_PARAMETER;
}

LOGMOD_API long
logmod_logger_get_counter(const struct logmod_logger *logger)
{
    struct logmod *logmod = LOGMOD_FROM_LOGGER(logger);
    long counter;
    LOGMOD_EXPECT(logmod != NULL, LOGMOD_BAD_PARAMETER);
    logmod->lock(logger, 1);
    counter = logmod->counter;
    logmod->lock(logger, 0);
    return counter;
}

LOGMOD_API struct logmod_logger *
logmod_get_logger(struct logmod *logmod, const char *const context_id)
{
    size_t i;
    _LOGMOD_EXPECT(logmod != NULL, LOGMOD_BAD_PARAMETER, NULL);
    _LOGMOD_EXPECT(logmod->loggers != NULL, LOGMOD_BAD_PARAMETER, NULL);
    _LOGMOD_EXPECT(context_id != NULL, LOGMOD_BAD_PARAMETER, NULL);
    logmod->lock(NULL, 1);
    for (i = 0; i < logmod->length; ++i) {
        if (0 == strcmp(logmod->loggers[i].context_id, context_id)) {
            struct logmod_logger *logger =
                (struct logmod_logger *)&logmod->loggers[i];
            logmod->lock(logger, 0);
            return logger;
        }
    }
    if (logmod->length < logmod->real_length) {
        size_t *mut_length = (size_t *)&logmod->length;
        struct logmod_mut_logger *mut_logger =
            (struct logmod_mut_logger *)&logmod->loggers[logmod->length];
        memset(mut_logger, 0, sizeof *mut_logger);
        mut_logger->context_id = context_id;
        mut_logger->counter = &logmod->counter;
        mut_logger->options = logmod->default_options;
        ++*mut_length;
        logmod->lock((struct logmod_logger *)mut_logger, 0);
        return (struct logmod_logger *)mut_logger;
    }
    logmod->lock(NULL, 0);
    return NULL;
}

static logmod_err
_logmod_print(const struct logmod_logger *logger,
              const struct logmod_info *info,
              const char *fmt,
              va_list args,
              const int color,
              FILE *output)
{
    const int show_apid = logger->options.show_application_id,
              show_ctid = !logger->options.hide_context_id;
    LOGMOD_EXPECT(
        fprintf(output,
                LMT(color, "%02d:%02d:%02d", BLACK, REGULAR, BACKGROUND),
                info->time_info->tm_hour, info->time_info->tm_min,
                info->time_info->tm_sec)
            >= 0,
        LOGMOD_ERRNO);
    if (show_apid) {
        const struct logmod *logmod = LOGMOD_FROM_LOGGER(logger);
        LOGMOD_EXPECT(fprintf(output,
                              LMT(color, " %s »", WHITE, REGULAR, FOREGROUND),
                              logmod->application_id)
                          >= 0,
                      LOGMOD_ERRNO);
    }
    if (show_ctid) {
        LOGMOD_EXPECT(fprintf(output,
                              LMT(color, " %s »", WHITE, REGULAR, FOREGROUND),
                              logger->context_id)
                          >= 0,
                      LOGMOD_ERRNO);
    }
    if (color) {
        LOGMOD_EXPECT(
            fprintf(output,
                    LME(" %s", "%s", LOGMOD_STYLE_REGULAR,
                        LOGMOD_VISIBILITY_FOREGROUND)
                        LMS(" %s:%d", YELLOW, REGULAR, FOREGROUND) ": ",
                    info->label->color, info->label->name, info->filename,
                    info->line)
                >= 0,
            LOGMOD_ERRNO);
    }
    else {
        LOGMOD_EXPECT(fprintf(output, " %s %s:%d: ", info->label->name,
                              info->filename, info->line)
                          >= 0,
                      LOGMOD_ERRNO);
    }
    LOGMOD_EXPECT(vfprintf(output, fmt, args) >= 0, LOGMOD_ERRNO);
    LOGMOD_EXPECT(putc('\n', output) != EOF, LOGMOD_ERRNO);
    LOGMOD_EXPECT(fflush(output) != EOF, LOGMOD_ERRNO);
    return LOGMOD_OK;
}

static struct logmod g_logmod;

/** global logger used as a fallback */
static struct logmod_logger g_loggers[] = {
    {
        LOGMOD_FALLBACK_CONTEXT_ID,
        { NULL, 0, 1, LOGMOD_LEVEL_TRACE },
        &g_logmod.counter,
        NULL,
        NULL,
        default_labels,
        0,
    },
};
/** global logmod used as a fallback */
static struct logmod g_logmod = {
    LOGMOD_FALLBACK_APPLICATION_ID,
    g_loggers,
    sizeof(g_loggers) / sizeof *g_loggers,
    sizeof(g_loggers) / sizeof *g_loggers,
    0,
    { NULL, 0, 1, LOGMOD_LEVEL_TRACE },
    _logmod_lock_noop,
};

static struct logmod_info
_logmod_info_populate(const struct logmod_logger *logger,
                      const unsigned line,
                      const char *const filename,
                      const unsigned level)
{
    const struct logmod *logmod = LOGMOD_FROM_LOGGER(logger);
    const time_t time_raw = time(NULL);
    struct logmod_info info;
    unsigned *mut_line = (unsigned *)&info.line;
    const char **mut_filename = (const char **)&info.filename;
    unsigned *mut_level = (unsigned *)&info.level;
    const struct logmod_label **mut_label =
        (const struct logmod_label **)&info.label;
    const struct tm **mut_time_info = (const struct tm **)&info.time_info;
    *mut_line = line;
    *mut_filename = filename;
    *mut_level = level;
    *mut_label = logmod_logger_get_label(logger, level);
    logmod->lock(logger, 1);
    *mut_time_info = localtime(&time_raw);
    logmod->lock(logger, 0);
    return info;
}

LOGMOD_API logmod_err
_logmod_log(const struct logmod_logger *logger,
            const unsigned line,
            const char *const filename,
            const unsigned level,
            const char *fmt,
            ...)
{
    struct logmod *logmod =
        LOGMOD_FROM_LOGGER(!logger ? (logger = &g_loggers[0]) : logger);
    logmod_err code = LOGMOD_OK_SKIPPED;
    if (!logger->disabled) {
        const struct logmod_info info =
            _logmod_info_populate(logger, line, filename, level);
        va_list args;
        code = LOGMOD_OK_CONTINUE;
        if (logger->callback) {
            va_start(args, fmt);
            if ((code = logger->callback(logger, &info, fmt, args))
                < LOGMOD_OK)
            {
                goto _end;
            }
            va_end(args);
        }
        if (level >= logger->options.level && code == LOGMOD_OK_CONTINUE) {
            if (!logger->options.quiet || level == LOGMOD_LEVEL_FATAL) {
                va_start(args, fmt);
                if ((code = _logmod_print(
                         logger, &info, fmt, args, logger->options.color,
                         info.label->output == 0 ? stdout : stderr))
                    != LOGMOD_OK)
                {
                    goto _end;
                }
                va_end(args);
            }
            if (logger->options.logfile) {
                va_start(args, fmt);
                code = _logmod_print(logger, &info, fmt, args, 0,
                                     logger->options.logfile);
            }
        }
    _end:
        logmod->lock(logger, 1);
        ++logmod->counter;
        logmod->lock(logger, 0);
        va_end(args);
    }
    return code;
}

#undef LOGMOD_EXPECT

#endif /* LOGMOD_HEADER */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LOGMOD_H */
