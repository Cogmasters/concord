#ifndef ORKA_CONFIG_H
#define ORKA_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ntl.h" /* struct sized_buffer */


struct orka_config {
  char tag[16];         // a unique name to identify

  char fname[PATH_MAX]; // config file name
  char *contents;      // config file contents
  size_t len;          // config file len

  struct { /* the bot.log file */
    FILE *f;
  } logger;

  struct { /* the dump.json file */
    FILE *f;
    void (*cb)(
        struct orka_config* config, 
        char url[], 
        struct sized_buffer body,
        char header_fmt[], ...);
  } http_dump;
};

void orka_config_init(struct orka_config*, const char tag[], const char config_file[]);
void orka_config_cleanup(struct orka_config*);

struct sized_buffer orka_config_get_field(struct orka_config *config, char *json_field);
char* orka_config_get_fname(struct orka_config *config);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ORKA_CONFIG_H
