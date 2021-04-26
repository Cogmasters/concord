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
      char filename[PATH_MAX];
      bool enable;
    } http;
  } *logging = calloc(1, sizeof *logging); 


  if (config->contents) {
    free(config->contents);
    config->len = 0;
  }

  config->contents = orka_load_whole_file(config_file, &config->len);
  json_extract(config->contents, config->len,
             "(logging.level):s"
             "(logging.filename):s"
             "(logging.quiet):b"
             "(logging.overwrite):b"
             "(logging.http_dump.enable):b"
             "(logging.http_dump.filename):s",
             logging->level,
             logging->filename,
             &logging->quiet,
             &logging->overwrite,
             &logging->http.enable,
             logging->http.filename);

  /* SET LOGGER CONFIGS */
  if (!IS_EMPTY_STRING(logging->filename)) {
    if (first_run && logging->overwrite)
      config->logger.f = fopen(logging->filename, "w+");
    else
      config->logger.f = fopen(logging->filename, "a+");
    log_add_fp(config->logger.f, get_log_level(logging->level));
    ASSERT_S(NULL != config->logger.f, "Could not create logger file");
  }

  if (true == logging->quiet) { // make sure fatal still prints to stderr
    log_add_fp(stderr, LOG_FATAL);
  }
  log_set_level(get_log_level(logging->level));
  log_set_quiet(logging->quiet);

  /* SET HTTP DUMP CONFIGS */
  if (true == logging->http.enable) {
    if (!IS_EMPTY_STRING(logging->http.filename)) {
      if (first_run && logging->overwrite)
        config->http.f = fopen(logging->http.filename, "w+");
      else
        config->http.f = fopen(logging->http.filename, "a+");
      ASSERT_S(NULL != config->http.f, "Could not create dump file");
    }
  }

  if (first_run)
    first_run = false;

  free(logging);
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

void
log_http(
  struct logconf *config, 
  void *addr_id,
  char url[],
  struct sized_buffer body,
  char header_fmt[], ...)
{
  if (!config) return;

  va_list args;
  va_start(args, header_fmt);

  static struct sized_buffer empty_body = {"empty body", 10};
  if (0 == body.size) {
    body = empty_body;
  }

  char header[512];
  int ret = vsnprintf(header, sizeof(header), header_fmt, args);
  ASSERT_S(ret < sizeof(header), "Out of bounds write attempt");

  char timestr[64];
  fprintf(config->http.f, 
    "%s [%s #TID%zu] - %s - %s\r\r\r\r\n%.*s\n",
    header,
    logconf_tag(config, addr_id), 
    (size_t)pthread_self(),
    orka_timestamp_str(timestr, sizeof(timestr)), 
    url,
    (int)body.size, body.start);

  fflush(config->http.f);

  va_end(args);
}
