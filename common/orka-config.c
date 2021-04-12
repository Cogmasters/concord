#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h> /* strcasecmp() */
#include <stdarg.h>
#include <pthread.h> /* pthread_self() */
#include <limits.h> /* PATH_MAX */

#include "orka-config.h"
#include "orka-utils.h"
#include "json-actor.h"


static bool g_first_run = true; // used to delete existent dump files

static void
http_dump(
  struct orka_config *config, 
  char url[],
  struct sized_buffer body,
  char header_fmt[], ...)
{
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
  fprintf(config->http_dump.f, 
    "%s [%s #TID%zu] - %s - %s\r\r\r\r\n%.*s\n",
    header,
    config->tag, 
    (size_t)pthread_self(),
    orka_timestamp_str(timestr, sizeof(timestr)), 
    url,
    (int)body.size, body.start);

  fflush(config->http_dump.f);

  va_end(args);
}

static void // see http_dump for parameter definitions
noop_http_dump(struct orka_config *a, char b[], struct sized_buffer c, char d[], ...) 
{ return; }

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
orka_config_init(struct orka_config *config, const char tag[], const char config_file[])
{
  const char DEFAULT_TAG[] = "USER AGENT";
  if (IS_EMPTY_STRING(tag)) 
    tag = DEFAULT_TAG;
  if (IS_EMPTY_STRING(config->tag) || !STREQ(config->tag, tag))
    snprintf(config->tag, sizeof(config->tag), "%s", tag);
  if (IS_EMPTY_STRING(config_file)) {
    config->http_dump.cb = &noop_http_dump;
    config->http_dump.f = stderr;
    return; /* EARLY RETURN */
  }

  // save file name for possible references
  int ret = snprintf(config->fname, sizeof(config->fname), "%s", config_file);
  ASSERT_S(ret < sizeof(config->fname), "Out of bounds write attempt");

  struct {
    char level[128];
    char filename[PATH_MAX];
    bool quiet;
    struct {
      char filename[PATH_MAX];
      bool enable;
    } http_dump;
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
             "(logging.http_dump.enable):b"
             "(logging.http_dump.filename):s",
             logging->level,
             logging->filename,
             &logging->quiet,
             &logging->http_dump.enable,
             logging->http_dump.filename);

  /* SET LOGGER CONFIGS */
  log_set_level(get_log_level(logging->level));
  log_set_quiet(logging->quiet);
  if (!IS_EMPTY_STRING(logging->filename)) {
    if (true == g_first_run) { // delete file if already exists
      remove(logging->filename);
    }
    config->logger.f = fopen(logging->filename, "a+");
    ASSERT_S(NULL != config->logger.f, "Could not create logger file");
    log_add_fp(config->logger.f, get_log_level(logging->level));
  }

  /* SET HTTP DUMP CONFIGS */
  if (true == logging->http_dump.enable) {
    if (!IS_EMPTY_STRING(logging->http_dump.filename)) {
      if (true == g_first_run) { // delete file if already exists
        remove(logging->http_dump.filename);
      }
      config->http_dump.f = fopen(logging->http_dump.filename, "a+");
      ASSERT_S(NULL != config->http_dump.f, "Could not create dump file");
    }
    config->http_dump.cb = &http_dump;
  }

  if (true == g_first_run) {
    g_first_run = false;
  }

  free(logging);
}

void
orka_config_cleanup(struct orka_config *config)
{
  if (config->contents)
    free(config->contents);
  if (config->logger.f)
    fclose(config->logger.f);
  if (config->http_dump.f)
    fclose(config->http_dump.f);
}

struct sized_buffer
orka_config_get_field(struct orka_config *config, char *json_field)
{
  struct sized_buffer field = {0};
  if (NULL == json_field) return field; // empty field

  char fmt[512];
  int ret = snprintf(fmt, sizeof(fmt), "(%s):T", json_field);
  ASSERT_S(ret < sizeof(fmt), "Out of bounds write attempt");

  json_extract(config->contents, config->len, fmt, &field);

  return field;
}

char*
orka_config_get_fname(struct orka_config *config) {
  return config->fname;
}
