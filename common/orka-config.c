#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <pthread.h> /* pthread_self() */
#include <string.h>
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

  static struct sized_buffer empty_body = {"empty", 5};
  if (0 == body.size) {
    body = empty_body;
  }

  char header[512];
  int ret = vsnprintf(header, sizeof(header), header_fmt, args);
  ASSERT_S(ret < sizeof(header), "Out of bounds write attempt");

  char timestr[64];
  fprintf(config->f_http_dump, 
    "%s [%s #TID%zu] - %s - %s\r\r\r\r\n%.*s\n",
    header,
    config->tag, 
    (size_t)pthread_self(),
    orka_timestamp_str(timestr, sizeof(timestr)), 
    url,
    (int)body.size, body.start);

  fflush(config->f_http_dump);

  va_end(args);
}

static void // see http_dump for parameter definitions
noop_http_dump(struct orka_config *a, char b[], struct sized_buffer c, char d[], ...) { return; }

void
orka_config_init(
  struct orka_config *config, 
  const char tag[], 
  const char config_file[])
{
  if (IS_EMPTY_STRING(tag)) 
    tag = "USER AGENT"; // default tag
  if (IS_EMPTY_STRING(config->tag) || !STREQ(config->tag, tag)) {
    snprintf(config->tag, sizeof(config->tag), "%s", tag);
  }
  if (IS_EMPTY_STRING(config_file)) {
    config->http_dump_cb = &noop_http_dump;
    config->f_http_dump = stderr;
    return; /* EARLY RETURN */
  }

  // save file name for possible references
  int ret = snprintf(config->fname, sizeof(config->fname), "%s", config_file);
  ASSERT_S(ret < sizeof(config->fname), "Out of bounds write attempt");

  struct _dump_s {
    char filename[PATH_MAX];
    bool enable;
  };

  struct _logging_s {
    char filename[PATH_MAX];
    char level[128];
    struct _dump_s http_dump;
  }; 

  struct _logging_s *logging = calloc(1, sizeof *logging);


  if (config->fcontents) {
    free(config->fcontents);
    config->flen = 0;
  }

  config->fcontents = orka_load_whole_file(config_file, &config->flen);
  json_extract(config->fcontents, config->flen,
             "(logging.filename):s"
             "(logging.level):s"
             "(logging.http_dump.enable):b"
             "(logging.http_dump.filename):s",
             logging->filename,
             logging->level,
             &logging->http_dump.enable,
             logging->http_dump.filename);

  if (true == logging->http_dump.enable) {
    if (*logging->http_dump.filename) {
      if (g_first_run == true) {
        remove(logging->http_dump.filename);
      }
      config->f_http_dump = fopen(logging->http_dump.filename, "a+");
      ASSERT_S(NULL != config->f_http_dump, "Could not create dump file");
    }
    config->http_dump_cb = &http_dump;
  }

  if (g_first_run == true) {
    g_first_run = false;
  }
}

void
orka_config_cleanup(struct orka_config *config)
{
  if (config->fcontents)
    free(config->fcontents);
  if (config->f_http_dump)
    fclose(config->f_http_dump);
}

struct sized_buffer
orka_config_get_field(struct orka_config *config, char *json_field)
{
  struct sized_buffer field = {0};
  if (NULL == json_field) return field; // empty field

  char fmt[512];
  int ret = snprintf(fmt, sizeof(fmt), "(%s):T", json_field);
  ASSERT_S(ret < sizeof(fmt), "Out of bounds write attempt");

  json_extract(config->fcontents, config->flen, fmt, &field);

  return field;
}

char*
orka_config_get_fname(struct orka_config *config) {
  return config->fname;
}
