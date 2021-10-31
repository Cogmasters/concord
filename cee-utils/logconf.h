#ifndef LOGCONF_H
#define LOGCONF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h> /* uint64_t */
#include "ntl.h"    /* struct sized_buffer */
#include "debug.h"

#define logconf_trace(conf, ...) logconf_log(conf, LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define logconf_debug(conf, ...) logconf_log(conf, LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define logconf_info(conf, ...)  logconf_log(conf, LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define logconf_warn(conf, ...)  logconf_log(conf, LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define logconf_error(conf, ...) logconf_log(conf, LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define logconf_fatal(conf, ...) logconf_log(conf, LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

#define __logconf_log(conf, level, file, line, fmt, ...) _log_log(&(conf)->L, level, file, line, "[%s] "fmt"%s", (conf)->id, __VA_ARGS__)
#define logconf_log(conf, level, file, line, ...) __logconf_log(conf, level, file, line, __VA_ARGS__, "")

#define LOGCONF_ID_LEN   64 + 1
#define LOGCONF_PATH_MAX 4096

struct logconf {
  char id[LOGCONF_ID_LEN]; /*< the logging module identifier*/
  log_Logger L;            /*< log.c main structure*/
  unsigned pid;            /*< the id of the process where this module was created */

/* SHARED RESOURCES BELOW */
  _Bool is_branch;          /*< if true then logconf_cleanup() won't cleanup shared resources */
			      struct sized_buffer file; /*< config file contents*/
  struct {
    char fname[LOGCONF_PATH_MAX];
    FILE *f;
  } *logger, *http; /* 'log_xxx()' and 'log_http()' outputs */
  NTL_T(struct ja_str) disable_modules;
};

struct loginfo {
  size_t counter;
  uint64_t tstamp_ms;
};

void logconf_setup(struct logconf*, const char id[], FILE *fp);
void logconf_branch(struct logconf *branch, struct logconf *orig, const char id[]);
void logconf_cleanup(struct logconf*);
struct sized_buffer logconf_get_field(struct logconf *conf, char *json_field);

void logconf_http(struct logconf*, struct loginfo*, char url[], struct sized_buffer header, struct sized_buffer body, char label_fmt[], ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LOGCONF_H */
