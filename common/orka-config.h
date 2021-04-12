#ifndef ORKA_CONFIG_H
#define ORKA_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ntl.h" /* struct sized_buffer */


struct orka_config {
  char tag[64];

  char fname[PATH_MAX]; // config file name
  char *fcontents;      // config file contents
  size_t flen;          // config file len

  FILE *f_http_dump; //default stderr
  void (*http_dump_cb)(
      struct orka_config* config, 
      char url[], 
      struct sized_buffer body,
      char header_fmt[], ...);
};

void orka_config_init(struct orka_config*, const char tag[], const char config_file[]);
void orka_config_cleanup(struct orka_config*);

struct sized_buffer orka_config_get_field(struct orka_config *config, char *json_field);
char* orka_config_get_fname(struct orka_config *config);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ORKA_CONFIG_H
