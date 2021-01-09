#ifndef ORCA_H
#define ORCA_H
#include <linux/limits.h>
#define TOKEN_MAX_LEN 512

struct bot_settings {
  struct {
    char token[TOKEN_MAX_LEN]; // set it to long enough
  } discord;
  struct {
    char filename[PATH_MAX];
    char level[128];
  } logging;
};

extern void bot_settings_init (char * filename, struct orca_settings *);
#endif // ORCA_H
