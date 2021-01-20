#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "settings.h"
#include "json-scanf.h"


static char*
load_whole_file(const char filename[], size_t *len) {
  FILE *f = fopen(filename,"rb"); 
  if (!f) {
    char *s = strerror(errno);
    fprintf (stderr, "%s '%s'\n", s, filename);
    exit(1); 
  }
  
  fseek(f, 0, SEEK_END);
  *len = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *string = malloc(*len);
  fread(string, 1, *len, f);
  fclose(f);

  return string;
}

void
bot_settings_init(struct bot_settings *settings, const char filename[])
{
  size_t len;
  char *str = load_whole_file(filename, &len);

  json_scanf(str, len,
             "[discord][token]%s"
             "[logging][filename]%s"
             "[logging][level]%s"
             "[logging][dump_json][filename]%s"
             "[logging][dump_json][enable]%b"
             "[logging][dump_curl][filename]%s"
             "[logging][dump_curl][enable]%b",
             settings->discord.token,
             settings->logging.filename, 
             settings->logging.level,
             settings->logging.dump_json.filename,
             &settings->logging.dump_json.enable,
             settings->logging.dump_curl.filename,
             &settings->logging.dump_curl.enable);

  printf("discord.token %s\n", settings->discord.token);
  printf("logging.filename %s\n", settings->logging.filename);
  printf("logging.level %s\n", settings->logging.level);
  printf("logging.dump_json.filename %s\n", settings->logging.dump_json.filename);
  printf("logging.dump_json.enable %d\n", settings->logging.dump_json.enable);
  printf("logging.dump_curl.filename %s\n", settings->logging.dump_curl.filename);
  printf("logging.dump_curl.enable %d\n", settings->logging.dump_curl.enable);

  free(str);

  return;
}
