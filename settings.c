#include "settings.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "json-scanf.h"

static char * load_whole_file(char * filename) {
  FILE *f = fopen(filename,"rb"); 
  if (!f) {
    char * s = strerror(errno);
    fprintf (stderr, "%s '%s'\n", s, filename);
    exit(1); 
  }
  
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *string = malloc(fsize + 1);
  fread(string, 1, fsize, f);
  fclose(f);
  return string;
}

void bot_settings_init(char * filename, struct bot_settings * settings) {
  char * str = load_whole_file(filename);
  json_scanf2(str,
             "[discord][token]%s"
             "[logging][filename]%s"
             "[logging][level]%s"
             "[logging][dump_json][filename]%s"
             "[logging][dump_json][enable]%b"
             "",
             settings->discord.token,
             settings->logging.filename, 
             settings->logging.level,
             settings->logging.dump_json.filename,
             &(settings->logging.dump_json.enable));
  printf(" discord.token %s\n", settings->discord.token);
  printf(" logging.filename %s\n", settings->logging.filename);
  printf(" logging.level %s\n", settings->logging.level);
  printf(" logging.dump_json.filename %s\n", settings->logging.dump_json.filename);
  printf(" logging.dump_json.enable %d\n", settings->logging.dump_json.enable);

  free(str);
  return;
}
