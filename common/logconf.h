#ifndef LOGCONF_H
#define LOGCONF_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ntl.h" /* struct sized_buffer */
#include "debug.h"

#define MAX_LOGCONF_IDS 32

struct logconf_ids {
  void *addr;
  char tag[16];
};

struct logconf {
  struct logconf_ids ids[MAX_LOGCONF_IDS];
  char *contents; // config file contents
  size_t len; // config file len

  struct { /* the bot.log file */
    FILE *f;
  } logger;
  struct { /* the dump.json file */
    FILE *f;
  } http;
};

void logconf_add_id(struct logconf *config, void *addr, const char tag[]);
void logconf_setup(struct logconf*, const char config_file[]);
void logconf_cleanup(struct logconf*);
struct sized_buffer logconf_get_field(struct logconf *config, char *json_field);

void log_http(
  struct logconf *config, 
  void *addr_id,
  char url[],
  struct sized_buffer body,
  char header_fmt[], ...);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LOGCONF_H
