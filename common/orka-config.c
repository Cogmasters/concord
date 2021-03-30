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
resp_dump(
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

  fprintf(config->f_resp_dump, 
    "%s [%s #TID%p] - %s - %s\r\r\r\r\n%s\n",
    header,
    config->tag, 
    pthread_self(),
    timestr, 
    url,
    IS_EMPTY_STRING(body) ? "empty body" : body);

  fflush(config->f_resp_dump);
}

static void // see resp_dump for parameter definitions
noop_resp_dump(bool a, int b, char *c, struct orka_config *d, char *e, char *f) { return; (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
}

void
orka_config_init(
  struct orka_config *config, 
  const char tag[], 
  const char config_file[])
{
  if (config->tag) {
    free(config->tag);
  }
  config->tag = (tag) ? strdup(tag) : strdup("USER AGENT");

  if (IS_EMPTY_STRING(config_file)) {
    config->resp_dump_cb = &noop_resp_dump;
    config->f_resp_dump = stderr;
    return; /* EARLY RETURN */
  }

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
      config->f_resp_dump = fopen(logging.dump_json.filename, "a+");
      ASSERT_S(NULL != config->f_resp_dump, "Could not create dump file");
    }
    config->resp_dump_cb = &resp_dump;
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
  if (config->tag)
    free(config->tag);
  if (config->f_resp_dump)
    fclose(config->f_resp_dump);
}

char*
orka_config_get_field(struct orka_config *config, char *json_field)
{
  if (NULL == json_field) return NULL;

  char fmt[512];
  int ret = snprintf(fmt, sizeof(fmt), "(%s):?s", json_field);
  ASSERT_S(ret < sizeof(fmt), "Out of bounds write attempt");

  char *field = NULL;
  json_extract(config->fcontents, config->flen, fmt, &field);

  return field;
}
