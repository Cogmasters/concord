#include "orca.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "libjscon.h"

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

void bot_settings_init(char * filename, struct orca_settings * settings) {
  char * str = load_whole_file(filename);
  
  printf ("%p\n", str);
  jscon_scanf(str,
              "%s[discord][token] %s[logging][filename] %s[logging][level]",
              settings->discord.token,
              settings->logging.filename, 
              settings->logging.level);
  free(str);
  return;
}
