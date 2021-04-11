#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <pthread.h>
#include <string.h>
#include <limits.h> // for PATH_MAX

#include "orka-config.h"
#include "orka-utils.h"
#include "json-actor.h"


static bool g_first_run = true; // used to delete existent dump files

static void
http_dump(
  bool show_code, // if false code is ignored
  int code, 
  char *code_reason,
  struct orka_config *config, 
  char *url,
  char *body)
{
  char timestr[64] = {0};
  orka_timestamp_str(timestr, sizeof(timestr));

  char header[256];
  if (true == show_code)
    snprintf(header, sizeof(header), "RESPONSE %s(%d)", code_reason, code);
  else
    snprintf(header, sizeof(header), "REQUEST %s", code_reason);

  fprintf(config->f_http_dump, 
    "%s [%s #TID%zu] - %s - %s\r\r\r\r\n%s\n",
    header,
    config->tag, 
    (size_t)pthread_self(),
    timestr, 
    url,
    IS_EMPTY_STRING(body) ? "empty body" : body);

  fflush(config->f_http_dump);
}

static void // see http_dump for parameter definitions
noop_http_dump(bool a, int b, char *c, struct orka_config *d, char *e, char *f) { return; (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
}

void
orka_config_init(
  struct orka_config *config, 
  const char tag[], 
  const char config_file[])
{
  if (IS_EMPTY_STRING(tag)) 
    tag = "USER AGENT"; // default tag
  if (IS_EMPTY_STRING(config->tag) || !STREQ(config->tag, tag)) {
    int ret = snprintf(config->tag, sizeof(config->tag), "%s", tag);
    ASSERT_S(ret < sizeof(config->tag), "Out of bounds write attempt");
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

  struct {
    char filename[PATH_MAX];
    char level[128];
    struct _dump_s dump_json;
  } logging = {{0}};

  if (config->fcontents) {
    free(config->fcontents);
    config->flen = 0;
  }

  //@todo rename dump_json to http_dump
  config->fcontents = orka_load_whole_file(config_file, &config->flen);
  json_extract(config->fcontents, config->flen,
             "(logging.filename):s"
             "(logging.level):s"
             "(logging.dump_json.filename):s"
             "(logging.dump_json.enable):b",
             logging.filename,
             logging.level,
             logging.dump_json.filename,
             &logging.dump_json.enable);

  DS_PRINT(
    "logging.filename %s\n"
    "logging.level %s\n"
    "logging.dump_json.filename %s\n"
    "logging.dump_json.enable %d\n",
    logging.filename,
    logging.level,
    logging.dump_json.filename,
    logging.dump_json.enable);

  if (true == logging.dump_json.enable) {
    if (*logging.dump_json.filename) {
      if (g_first_run == true) {
        remove(logging.dump_json.filename);
      }
      config->f_http_dump = fopen(logging.dump_json.filename, "a+");
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
