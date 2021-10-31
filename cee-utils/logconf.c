#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h> /* strcasecmp() */
#include <stdarg.h>
#include <pthread.h> /* pthread_self() */
#include <unistd.h> /* getpid() */

#include "logconf.h"

#include "cee-utils.h"
#include "json-actor.h"
#include "json-actor-boxed.h" /* ja_str */


static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static size_t g_counter;


static int
get_log_level(char level[])
{
  if (0 == strcasecmp(level, "TRACE")) return LOG_TRACE;
  if (0 == strcasecmp(level, "DEBUG")) return LOG_DEBUG;
  if (0 == strcasecmp(level, "INFO"))  return LOG_INFO;
  if (0 == strcasecmp(level, "WARN"))  return LOG_WARN;
  if (0 == strcasecmp(level, "ERROR")) return LOG_ERROR;
  if (0 == strcasecmp(level, "FATAL")) return LOG_FATAL;
  ERR("Log level doesn't exist: %s", level);
  return 0;/* make compiler happy */
}

static void
log_nocolor_cb(log_Event *ev)
{
  char buf[16];
  buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] = '\0';

  fprintf(
    ev->udata, "%s|%010u %-5s %s:%d: ",
    buf, (unsigned)pthread_self(), level_strings[ev->level], ev->file, ev->line);

  vfprintf(ev->udata, ev->fmt, ev->ap);
  fprintf(ev->udata, "\n");
  fflush(ev->udata);
}

static void 
log_color_cb(log_Event *ev)
{
  char buf[16];
  buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] = '\0';

  fprintf(
    ev->udata, "%s|\x1b[90m%010u\x1b[0m %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
    buf, (unsigned)pthread_self(), level_colors[ev->level], level_strings[ev->level],
    ev->file, ev->line);

  vfprintf(ev->udata, ev->fmt, ev->ap);
  fprintf(ev->udata, "\n");
  fflush(ev->udata);
}

/** @todo this doesn't disable `logconf_http()` logging */
static bool
module_is_disabled(struct logconf *conf)
{
  int i;
  if (!conf->disable_modules) return false;

  for (i=0; conf->disable_modules[i]; ++i) {
    if (0 == strcmp(conf->id, conf->disable_modules[i]->value)) {
      /* reset presets (if any) */
      memset(&conf->L, 0, sizeof conf->L);
      /* silence output */
      _log_set_quiet(&conf->L, true);
      /* make sure fatal still prints to stderr */
      _log_add_callback(&conf->L, &log_nocolor_cb, stderr, LOG_FATAL);
      return true; /* EARLY RETURN */
    }
  }
  return false;
}

void
logconf_http(
  struct logconf *conf, 
  struct loginfo *p_info,
  char url[],
  struct sized_buffer header,
  struct sized_buffer body,
  char label_fmt[], ...)
{
  pthread_mutex_lock(&g_lock);
  size_t counter = ++g_counter;
  pthread_mutex_unlock(&g_lock);
  uint64_t tstamp_ms = cee_timestamp_ms();

  if (!conf || !conf->http || !conf->http->f) 
    goto _end;

  /* Build 'label' string */
  char label[512];
  va_list label_args;
  va_start(label_args, label_fmt);
  size_t ret = vsnprintf(label, sizeof(label), label_fmt, label_args);
  ASSERT_S(ret < sizeof(label), "Out of bounds write attempt");
  va_end(label_args);

  /* Get timestamp string */
  char timestr[64];
  cee_unix_ms_to_iso8601(timestr, sizeof(timestr), &tstamp_ms);

  /* Print to output */
  fprintf(conf->http->f, 
    "%s [%s #TID%u] - %s - %s\n"
    "%.*s%s%.*s\n"
    "@@@_%zu_@@@\n",
/* 1st LINE ARGS */
    label, 
    conf->id, 
    (unsigned)pthread_self(), 
    timestr, 
    url,
/* 2nd LINE ARGS */
    (int)header.size, header.start,
    header.size ? "\n" : "",
    (int)body.size, body.start,
/* 3rd LINE ARGS */
    counter);

  fflush(conf->http->f);

_end:
  /* extract logging info if requested */
  if (p_info) {
    *p_info = (struct loginfo){
      .counter = counter,
      .tstamp_ms = tstamp_ms
    };
  }
}

void
logconf_setup(struct logconf *conf, const char id[], FILE* fp)
{
  memset(conf, 0, sizeof *conf);

  int ret = snprintf(conf->id, LOGCONF_ID_LEN, "%s", id);
  ASSERT_S(ret < LOGCONF_ID_LEN, "Out of bounds write attempt");
  conf->pid  = getpid();

  if (!fp) return; /* EARLY RETURN */

  conf->logger = calloc(1, sizeof *conf->logger);
  conf->http = calloc(1, sizeof *conf->http);

  struct {
    char level[16];
    char filename[LOGCONF_PATH_MAX];
    bool quiet, use_color, overwrite;
    struct {
      bool enable;
      char filename[LOGCONF_PATH_MAX];
    } http;
  } l={0};

  conf->file.start = cee_load_whole_file_fp(fp, &conf->file.size);
  json_extract(conf->file.start, conf->file.size,
             "(logging):{"
               "(level):.*s,"
               "(filename):.*s,"
               "(quiet):b,"
               "(use_color):b,"
               "(overwrite):b,"
               "(http):{"
                 "(enable):b,"
                 "(filename):.*s,"
               "},"
               "(http_dump):{" /* deprecated */
                 "(enable):b,"
                 "(filename):.*s,"
               "},"
               "(disable_modules):F"
             "}",
             sizeof(l.level), l.level,
             sizeof(l.filename), l.filename,
             &l.quiet,
             &l.use_color,
             &l.overwrite,
             &l.http.enable,
             sizeof(l.http.filename), l.http.filename,
             &l.http.enable,
             sizeof(l.http.filename), l.http.filename,
             &ja_str_list_from_json, &conf->disable_modules);

  /* skip everything else if this module is disabled */
  if (module_is_disabled(conf)) return;

  /* SET LOGGER CONFIGS */
  if (!IS_EMPTY_STRING(l.filename)) {
    memcpy(conf->logger->fname, l.filename, LOGCONF_PATH_MAX);
    conf->logger->f = fopen(conf->logger->fname, l.overwrite ? "w+" : "a+");
    ASSERT_S(NULL != conf->logger->f, "Could not create logger file");

    _log_add_callback(&conf->L,
        l.use_color ? &log_color_cb : &log_nocolor_cb, 
        conf->logger->f, 
        get_log_level(l.level));
  }

  /* SET HTTP DUMP CONFIGS */
  if (l.http.enable && !IS_EMPTY_STRING(l.http.filename)) {
    memcpy(conf->http->fname, l.http.filename, LOGCONF_PATH_MAX);
    conf->http->f = fopen(conf->http->fname, l.overwrite ? "w+" : "a+");
    ASSERT_S(NULL != conf->http->f, "Could not create http logger file");
  }

  /* disable default log.c callbacks */
  _log_set_quiet(&conf->L, true);

  /* make sure fatal still prints to stderr */
  _log_add_callback(&conf->L,
      l.use_color ? &log_color_cb : &log_nocolor_cb, 
      stderr, 
      l.quiet ? LOG_FATAL : get_log_level(l.level));
}

void
logconf_branch(struct logconf *branch, struct logconf *orig, const char id[]) 
{
  if (!orig) {
    logconf_setup(branch, id, NULL);
    return; /* EARLY RETURN */
  }

  pthread_mutex_lock(&g_lock);
  memcpy(branch, orig, sizeof(struct logconf));
  pthread_mutex_unlock(&g_lock);

  branch->is_branch = true;
  if (id) {
    int ret = snprintf(branch->id, LOGCONF_ID_LEN, "%s", id);
    ASSERT_S(ret < LOGCONF_ID_LEN, "Out of bounds write attempt");
  }
  branch->pid = getpid();

  if (module_is_disabled(branch)) return;

  /* To avoid overwritting, child processes files must be unique,
   *    this will append the unique PID to the end of file names */
  /** @todo this actually doesn't do anything, it creates the filename
   * but never create the files */
  if (branch->pid != orig->pid) {
    size_t len;

    len = strlen(orig->logger->fname);
    snprintf(branch->logger->fname + len, sizeof(branch->logger->fname) - len, "%ld", (long)branch->pid);

    len = strlen(orig->http->fname);
    snprintf(branch->http->fname + len, sizeof(branch->http->fname) - len, "%ld", (long)branch->pid);
  }
}

void
logconf_cleanup(struct logconf *conf)
{
  if (!conf->is_branch) {
    if (conf->file.start) {
      free(conf->file.start);
    }
    if (conf->logger) {
      if (conf->logger->f) {
        fclose(conf->logger->f);
      }
      free(conf->logger);
    }
    if (conf->http) {
      if (conf->http->f) {
        fclose(conf->http->f);
      }
      free(conf->http);
    }
    if (conf->disable_modules) {
      ja_str_list_free(conf->disable_modules);
    }
  }
  memset(conf, 0, sizeof *conf);
}

struct sized_buffer
logconf_get_field(struct logconf *conf, char *json_field)
{
  struct sized_buffer field={0};
  if (!conf->file.size) return field; /* empty field */

  char fmt[512];
  int ret = snprintf(fmt, sizeof(fmt), "(%s):T", json_field);
  ASSERT_S(ret < sizeof(fmt), "Out of bounds write attempt");

  json_extract(conf->file.start, conf->file.size, fmt, &field);

  return field;
}
