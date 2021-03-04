#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#include "orka-config.h"
#include "orka-utils.h"
#include "json-actor.h"


static bool g_first_run = true; // used to delete existent dump files

static void
noop_json_dump(
  bool is_response, 
  int httpcode, 
  struct orka_config *config, 
  char *url,
  char *json_text) {
  return; (void)json_text; (void)config; (void)json_text;
}

static void
json_dump(
  bool is_response, 
  int httpcode, 
  struct orka_config *config, 
  char *url,
  char *json_text)
{
  char timestr[64] = {0};
  orka_timestamp_str(timestr, sizeof(timestr));

  char type[128];
  if (is_response)
    snprintf(type, sizeof(type), "%d", httpcode);
  else
    snprintf(type, sizeof(type), "REQUEST");

  fprintf(config->f_json_dump, 
    "\r\r\r\r[%s (%s)] - %s - %s\n%s\n", 
    config->tag, 
    type, 
    timestr, 
    url,
    (*json_text) ? json_text : "empty request body");

  fflush(config->f_json_dump);
}

static int
curl_dump(
  CURL *ehandle,
  curl_infotype type,
  char *data,
  size_t size,
  void *p_userdata)
{
  struct orka_config *config = (struct orka_config *)p_userdata;

  FILE *f_dump = config->f_curl_dump;

  const char *text = NULL;
  switch (type) {
  case CURLINFO_TEXT:
    {
      char timestr[64] = {0};
      orka_timestamp_str(timestr, sizeof(timestr));

      fprintf(f_dump, "\r\r\r\rCURL INFO - %s\n%s\n", timestr, data);
      fflush(f_dump);
    }
  /* fallthrough */
  default:
      return 0;
  case CURLINFO_HEADER_OUT:
      text = "SEND HEADER";
      break;
  case CURLINFO_DATA_OUT:
      text = "SEND DATA";
      break;
  case CURLINFO_SSL_DATA_OUT:
      text = "SEND SSL DATA";
      break;
  case CURLINFO_HEADER_IN:
      text = "RECEIVE HEADER";
      break;
  case CURLINFO_DATA_IN:
      text = "RECEIVE DATA";
      break;
  case CURLINFO_SSL_DATA_IN:
      text = "RECEIVE SSL DATA";
      break;
  }

  const unsigned int WIDTH = 0x10;

  char timestr[64] = {0};
  orka_timestamp_str(timestr, sizeof(timestr));

  fprintf(f_dump, "\r\r\r\r%s %10.10ld bytes (0x%8.8lx) - %s\n%s\n",
          text, (long)size, (long)size, timestr, data);

  for(size_t i=0; i < size; i += WIDTH)
  {
    fprintf(f_dump, "%4.4lx: ", (long)i);

    //show hex to the left
    for(size_t c = 0; c < WIDTH; c++) {
      if(i+c < size)
        fprintf(f_dump, "%02x ", data[i+c]);
      else
        fputs("   ", f_dump);
    }

    //show data on the right
    for(size_t c = 0; (c < WIDTH) && (i+c < size); c++) {
      char x = (data[i+c] >= 0x20 && data[i+c] < 0x80) ? data[i+c] : '.';
      fputc(x, f_dump);
    }

    fputc('\n', f_dump); //newline
  }

  fflush(f_dump);

  return 0;

  (void)ehandle;
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

  if (!config_file || !*config_file) {
    config->json_cb = &noop_json_dump;
    config->f_json_dump = stderr;
    config->curl_cb = NULL;
    config->f_curl_dump = stderr;
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
    struct _dump_s dump_curl;
  } logging = {0};

  if (config->fcontents) {
    free(config->fcontents);
    config->flen = 0;
  }

  config->fcontents = orka_load_whole_file(config_file, &config->flen);
  json_extract(config->fcontents, config->flen,
             "(logging.filename):s"
             "(logging.level):s"
             "(logging.dump_curl.filename):s"
             "(logging.dump_curl.enable):b"
             "(logging.dump_json.filename):s"
             "(logging.dump_json.enable):b",
             logging.filename,
             logging.level,
             logging.dump_curl.filename,
             &logging.dump_curl.enable,
             logging.dump_json.filename,
             &logging.dump_json.enable);

  DS_PRINT(
    "logging.filename %s\n"
    "logging.level %s\n"
    "logging.dump_curl.filename %s\n"
    "logging.dump_curl.enable %d\n"
    "logging.dump_json.filename %s\n"
    "logging.dump_json.enable %d\n",
    logging.filename,
    logging.level,
    logging.dump_curl.filename,
    logging.dump_curl.enable,
    logging.dump_json.filename,
    logging.dump_json.enable);

  if (true == logging.dump_json.enable) {
    if (*logging.dump_json.filename) {
      if (g_first_run == true) {
        remove(logging.dump_json.filename);
      }
      config->f_json_dump = fopen(logging.dump_json.filename, "a+");
      ASSERT_S(NULL != config->f_json_dump, "Could not create dump file");
    }
    config->json_cb = &json_dump;
  }
#if 0
  if (true == logging.dump_curl.enable) {
    if (*logging.dump_curl.filename) {
      if (g_first_run == true) {
        remove(logging.dump_curl.filename);
      }
      config->f_curl_dump = fopen(logging.dump_curl.filename, "a+");
      ASSERT_S(NULL != config->f_curl_dump, "Could not create dump file");
    }
    else {
      config->f_curl_dump = stderr;
    }
    config->curl_cb = &curl_dump;
  } else {
    config->curl_cb = NULL;
  }
#endif

  if (g_first_run == true) {
    g_first_run = false;
  }
}

void
orka_config_cleanup(struct orka_config *config)
{
  if (config->tag)
    free(config->tag);
  if (config->f_json_dump)
    fclose(config->f_json_dump);
  if (config->f_curl_dump)
    fclose(config->f_curl_dump);
}

char*
orka_config_get_field(struct orka_config *config, char *json_field)
{
  char fmt[512];
  int ret = snprintf(fmt, sizeof(fmt), "(%s):?s", json_field);
  ASSERT_S(ret < sizeof(fmt), "Out of bounds write attempt");

  char *field = NULL;
  json_extract(config->fcontents, config->flen, fmt, &field);

  return field;
}
