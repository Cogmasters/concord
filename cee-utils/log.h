/**
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

#define LOG_VERSION "0.1.0"

typedef struct {
  va_list ap;
  const char *fmt;
  const char *file;
  struct tm *time;
  void *udata;
  int line;
  int level;
} log_Event;

typedef void (*log_LogFn)(log_Event *ev);
typedef void (*log_LockFn)(bool lock, void *udata);

#define LOG_MAX_CALLBACKS 32

typedef struct {
  log_LogFn fn;
  void *udata;
  int level;
} log_Callback;

typedef struct {
  void *udata;
  log_LockFn lock;
  int level;
  bool quiet;
  log_Callback callbacks[LOG_MAX_CALLBACKS];
} log_Logger;

enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

#define log_trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  log_log(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  log_log(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

const char* log_level_string(int level);
#define log_set_lock(fn, udata) _log_set_lock(&L, fn, udata);
#define log_set_level(level) _log_set_level(&L, level);
#define log_set_quiet(enable) _log_set_quiet(&L, enable)
#define log_add_callback(fn, udata, level) _log_add_callback(&L, fn, udata, level)
#define log_add_fp(fn, level) _log_add_fp(&L, fn, level)
#define log_log(level, file, line, ...) _log_log(&L, level, file, line, __VA_ARGS__)

void _log_set_lock(log_Logger *L, log_LockFn fn, void *udata);
void _log_set_level(log_Logger *L, int level);
void _log_set_quiet(log_Logger *L, bool enable);
int _log_add_callback(log_Logger *L, log_LogFn fn, void *udata, int level);
int _log_add_fp(log_Logger *L, FILE *fp, int level);
void _log_log(log_Logger *L, int level, const char *file, int line, const char *fmt, ...);

extern const char *level_strings[];
extern const char *level_colors[];
extern log_Logger L;

#endif
