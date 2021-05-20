#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h> /* strcasecmp() */
#include <stdarg.h>
#include <pthread.h> /* pthread_self() */
#include <limits.h> /* PATH_MAX */

#include "logconf.h"

#include "orka-utils.h"
#include "json-actor.h"


static bool use_color;

static int
get_log_level(char level[])
{
  if (0 == strcasecmp(level, "TRACE")) return LOG_TRACE;
  if (0 == strcasecmp(level, "DEBUG")) return LOG_DEBUG;
  if (0 == strcasecmp(level, "INFO")) return LOG_INFO;
  if (0 == strcasecmp(level, "WARN")) return LOG_WARN;
  if (0 == strcasecmp(level, "ERROR")) return LOG_ERROR;
  if (0 == strcasecmp(level, "FATAL")) return LOG_FATAL;
  ERR("Log level doesn't exist: %s", level);
  return 0;// make compiler happy
}

void
logconf_add_id(struct logconf *config, void *addr, const char tag[])
{
  if (!config || !addr || IS_EMPTY_STRING(tag)) 
    return; /* EARLY RETURN */

  for (size_t i=0; i < MAX_LOGCONF_IDS; ++i) {
    if ( (NULL == config->ids[i].addr) || (addr == config->ids[i].addr) ) {
      config->ids[i].addr = addr;
      snprintf(config->ids[i].tag, sizeof(config->ids[i].tag), "%s", tag);
      return; /* EARLY RETURN */
    }
  }
  ERR("Reach maximum logconf_ids threshold (%d)", MAX_LOGCONF_IDS);
}

char*
logconf_tag(struct logconf *config, void *addr)
{
  for (size_t i=0; i < MAX_LOGCONF_IDS; ++i) {
    if (addr == config->ids[i].addr) {
      return config->ids[i].tag;
    }
  }
  return "NO_TAG";
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

  int tid_color;
  if (main_tid == pthread_self())
    tid_color = 31;
  else
    tid_color = 90;

  fprintf(
    ev->udata, "%s|\x1b[%dm%010u\x1b[0m %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
    buf, tid_color, (unsigned)pthread_self(), level_colors[ev->level], level_strings[ev->level],
    ev->file, ev->line);

  vfprintf(ev->udata, ev->fmt, ev->ap);
  fprintf(ev->udata, "\n");
  fflush(ev->udata);
}

void
log_http(
  struct logconf *config, 
  void *addr_id,
  char url[],
  struct sized_buffer body,
  char label_fmt[], ...)
{
  static struct sized_buffer empty_body = {"empty body", 10};

  if (!config) return;

  va_list args;
  va_start(args, label_fmt);

  if (0 == body.size)
    body = empty_body;

  char label[512];
  int ret = vsnprintf(label, sizeof(label), label_fmt, args);
  ASSERT_S(ret < sizeof(label), "Out of bounds write attempt");

  char timestr[64];
  fprintf(config->http.f, 
    "%s [%s #TID%u] - %s - %s\r\r\r\r\n%.*s\n",
    label,
    logconf_tag(config, addr_id), 
    (unsigned)pthread_self(),
    orka_timestamp_str(timestr, sizeof(timestr)), 
    url,
    (int)body.size, body.start);

  fflush(config->http.f);

  va_end(args);
}

void
logconf_setup(struct logconf *config, const char config_file[])
{
  ASSERT_S(NULL != config, "Missing 'struct logconf'");

  static bool first_run = true; // delete existent dump files if overwrite == true

  if (IS_EMPTY_STRING(config_file)) {
    config->http.f = stderr;
    return; /* EARLY RETURN */
  }

  struct {
    char level[16];
    char filename[PATH_MAX];
    bool quiet;
    bool overwrite;
    struct {
      bool enable;
      char filename[PATH_MAX];
    } http;
  } logging = {0};


  if (config->contents) {
    free(config->contents);
    config->len = 0;
  }

  config->contents = orka_load_whole_file(config_file, &config->len);
  json_extract(config->contents, config->len,
             "(logging.level):s"
             "(logging.filename):s"
             "(logging.quiet):b"
             "(logging.use_color):b"
             "(logging.overwrite):b"
             "(logging.http_dump.enable):b"
             "(logging.http_dump.filename):s",
             logging.level,
             logging.filename,
             &logging.quiet,
             &use_color,
             &logging.overwrite,
             &logging.http.enable,
             logging.http.filename);

  /* SET LOGGER CONFIGS */
  if (!IS_EMPTY_STRING(logging.filename)) {
    if (first_run && logging.overwrite)
      config->logger.f = fopen(logging.filename, "w+");
    else
      config->logger.f = fopen(logging.filename, "a+");
    log_add_callback(
        use_color ? &log_color_cb : &log_nocolor_cb, 
        config->logger.f, 
        get_log_level(logging.level));
    ASSERT_S(NULL != config->logger.f, "Could not create logger file");
  }

  /* SET HTTP DUMP CONFIGS */
  if (logging.http.enable && !IS_EMPTY_STRING(logging.http.filename)) {
    if (first_run && logging.overwrite)
      config->http.f = fopen(logging.http.filename, "w+");
    else
      config->http.f = fopen(logging.http.filename, "a+");
    ASSERT_S(NULL != config->http.f, "Could not create dump file");
  }

  if (first_run) {
    log_set_quiet(true); // disable default log.c callbacks
    if (logging.quiet) // make sure fatal still prints to stderr
      log_add_callback(
          use_color ? &log_color_cb : &log_nocolor_cb, 
          stderr, 
          LOG_FATAL);
    else
      log_add_callback(
          use_color ? &log_color_cb : &log_nocolor_cb, 
          stderr, 
          get_log_level(logging.level));

    first_run = false;
  }
}

void
logconf_cleanup(struct logconf *config)
{
  if (config->contents)
    free(config->contents);
  if (config->logger.f)
    fclose(config->logger.f);
  if (config->http.f)
    fclose(config->http.f);
}

struct sized_buffer
logconf_get_field(struct logconf *config, char *json_field)
{
  struct sized_buffer field = {0};
  if (!config || !json_field) return field; // empty field

  char fmt[512];
  int ret = snprintf(fmt, sizeof(fmt), "(%s):T", json_field);
  ASSERT_S(ret < sizeof(fmt), "Out of bounds write attempt");

  json_extract(config->contents, config->len, fmt, &field);

  return field;
}
