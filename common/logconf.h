#ifndef LOGCONF_H
#define LOGCONF_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ntl.h" /* struct sized_buffer */
#include "debug.h"

/**
 * @todo add more error codes and a strerror()
 * @todo move to a file easier to find
 */
typedef int ORCAcode;
#define ORCA_OK                  0
#define ORCA_NO_RESPONSE        -1
#define ORCA_UNUSUAL_HTTP_CODE  -2
#define ORCA_MISSING_PARAMETER  -3
#define ORCA_BAD_PARAMETER      -4
#define ORCA_BAD_JSON           -5


#define MAX_LOGCONF_IDS 32

struct logconf_ids {
  void *addr;
  char tag[32];
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
char* logconf_tag(struct logconf *config, void *addr);
void logconf_setup(struct logconf*, const char config_file[]);
void logconf_cleanup(struct logconf*);
struct sized_buffer logconf_get_field(struct logconf *config, char *json_field);

void log_http(
  struct logconf *config, 
  void *addr_id,
  char url[],
  struct sized_buffer body,
  char label_fmt[], ...);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LOGCONF_H
