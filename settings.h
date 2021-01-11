#ifndef SETTINGS_H
#define SETTINGS_H
#include <linux/limits.h>
#include <stdbool.h>
#define TOKEN_MAX_LEN 512

struct bot_settings {
  struct {
    char token[TOKEN_MAX_LEN]; // set it to long enough
  } discord;
  struct {
    char filename[PATH_MAX];
    char level[128];
    struct {
        char filename[PATH_MAX];
        bool enable;
    } dump_json;
  } logging;
};

extern void bot_settings_init (char * filename, struct bot_settings *);
#endif // SETTINGS_H
