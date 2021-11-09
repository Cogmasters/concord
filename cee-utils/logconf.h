#ifndef LOGCONF_H
#define LOGCONF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h> /* uint64_t */
#include "ntl.h" /* struct sized_buffer */
#include "debug.h"

/**
 * @brief Log level trace
 *
 * @param conf the `struct logconf` module
 * @param ... the printf-like format string and successive arguments
 */
#define logconf_trace(conf, ...)                                              \
  logconf_log(conf, LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
/**
 * @brief Log level debug
 *
 * @param conf the `struct logconf` module
 * @param ... the printf-like format string and successive arguments
 */
#define logconf_debug(conf, ...)                                              \
  logconf_log(conf, LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
/**
 * @brief Log level info
 *
 * @param conf the `struct logconf` module
 * @param ... the printf-like format string and successive arguments
 */
#define logconf_info(conf, ...)                                               \
  logconf_log(conf, LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
/**
 * @brief Log level warn
 *
 * @param conf the `struct logconf` module
 * @param ... the printf-like format string and successive arguments
 */
#define logconf_warn(conf, ...)                                               \
  logconf_log(conf, LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
/**
 * @brief Log level error
 *
 * @param conf the `struct logconf` module
 * @param ... the printf-like format string and successive arguments
 */
#define logconf_error(conf, ...)                                              \
  logconf_log(conf, LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
/**
 * @brief Log level fatal
 *
 * @param conf the `struct logconf` module
 * @param ... the printf-like format string and successive arguments
 */
#define logconf_fatal(conf, ...)                                              \
  logconf_log(conf, LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

/* helper function for logconf_log() */
#define __logconf_log(conf, level, file, line, fmt, ...)                      \
  _log_log(&(conf)->L, level, file, line, "[%s] " fmt "%s", (conf)->id,       \
           __VA_ARGS__)
/**
 * @brief Run-time configurable log level
 *
 * @param conf the `struct logconf` module
 * @param level the log level enumerator from `log.c`
 * @param file the origin file name
 * @param line the origin file line
 * @param ... the printf-like format string and successive arguments
 */
#define logconf_log(conf, level, file, line, ...)                             \
  __logconf_log(conf, level, file, line, __VA_ARGS__, "")

/** Maximum length for module id */
#define LOGCONF_ID_LEN 64 + 1
/** Maximum length for the output file path */
#define LOGCONF_PATH_MAX 4096

/**
 * @brief A stackful and modularized wrapper over the popular 'log.c'
 * facilities
 *
 * Provides a way to split logging into individual modules, that can be
 * configured separately from one another, or have their resources shared via
 * branching.
 */
struct logconf {
  /** logging module id */
  char id[LOGCONF_ID_LEN];
  /** log.c main structure */
  log_Logger L;
  /** the id of the process where this module was created */
  unsigned pid;
  /** if true then logconf_cleanup() won't cleanup shared resources */
  _Bool is_branch;
  /** config file conents */
  struct sized_buffer file;
  /** logging output */
  struct {
    /** name of logging output file */
    char fname[LOGCONF_PATH_MAX];
    /** pointer to logging output file */
    FILE *f;
  } * logger, *http;
  /** list of 'id' that should be ignored */
  NTL_T(struct ja_str) disable_modules;
};

/** @brief Store logging information from log_http() */
struct loginfo {
  /** log count */
  size_t counter;
  /** log timestamp */
  uint64_t tstamp_ms;
};

/**
 * @brief Initialize a `struct logconf` module
 *
 * @param conf pointer to the `struct logconf` structure to be initialized
 * @param id the `struct logconf` module id
 * @param fp the configuration file pointer that will fill `struct logconf`
 * fields
 */
void logconf_setup(struct logconf *conf, const char id[], FILE *fp);

/**
 * @brief Branch and link a `struct logconf` module to a existing one
 *
 * Initialize a `branch` logging module thats expected to share common
 * resources with its parent parent module `orig`. The common resources
 * include: config file directives, logging output and disabled modules list.
 * @param branch pointer to the `struct logconf` structure to be initialized as
 * `orig` branch
 * @param orig pointer to the `struct logconf` structure that holds the parent
 * module
 * @param id the `branch` module id
 */
void logconf_branch(struct logconf *branch,
                    struct logconf *orig,
                    const char id[]);

/**
 * @brief Cleanup a `struct logconf` module
 *
 * @param conf the `struct logconf` structure to be cleaned
 */
void logconf_cleanup(struct logconf *conf);

/**
 * @brief Get the value from a given `json_field`
 *
 * @param conf the `struct logconf` module
 * @param json_field the field to fetch the value of
 * @return a read-only sized buffer containing the field's value
 */
struct sized_buffer logconf_get_field(struct logconf *conf, char *json_field);

/**
 * @brief Log HTTP transfers
 *
 * @param conf the `struct logconf` module
 * @param info retrieve information on this logging
 * @param url the transfer URL
 * @param header the transfer header
 * @param body the transfer body
 * @param label_fmt a `printf()` like formatting string
 *        to provide additional logging description, such as the
 *        transfer's HTTP method, or HTTP response code.
 * @param ... subsequent arguments that are converted for output
 */
void logconf_http(struct logconf *conf,
                  struct loginfo *info,
                  char url[],
                  struct sized_buffer header,
                  struct sized_buffer body,
                  char label_fmt[],
                  ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LOGCONF_H */
