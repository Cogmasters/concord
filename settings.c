#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "settings.h"
#include "json-scanf.h"
#include "orka-debug.h"
#include "orka-utils.h"

void
bot_settings_init(struct bot_settings *settings, const char filename[])
{
  size_t len;
  char *str = orka_load_whole_file(filename, &len);

  json_scanf(str, len,
     "[discord][token]%s"
     "[github][username]%s"
     "[github][token]%s"
     "[logging][filename]%s"
     "[logging][level]%s"
     "[logging][dump_json][filename]%s"
     "[logging][dump_json][enable]%b"
     "[logging][dump_curl][filename]%s"
     "[logging][dump_curl][enable]%b",
     settings->discord.token,
     settings->github.username,
     settings->github.token,
     settings->logging.filename, 
     settings->logging.level,
     settings->logging.dump_json.filename,
     &settings->logging.dump_json.enable,
     settings->logging.dump_curl.filename,
     &settings->logging.dump_curl.enable);

  free(str);
}
