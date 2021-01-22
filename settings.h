#ifndef SETTINGS_H
#define SETTINGS_H

#include <limits.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TOKEN_MAX_LEN 512

struct dump_s {
  char filename[PATH_MAX];
  bool enable;
};

struct bot_settings {
  struct {
    char token[TOKEN_MAX_LEN]; // set it to long enough
  } discord;
  struct {
    char username[TOKEN_MAX_LEN];
    char token[TOKEN_MAX_LEN];
  } github;
  struct {
    char filename[PATH_MAX];
    char level[128];
    struct dump_s dump_json;
    struct dump_s dump_curl;
  } logging;
};

extern void bot_settings_init (struct bot_settings*, const char filename[]);

#ifdef __cplusplus
}
#endif
#endif // SETTINGS_H
