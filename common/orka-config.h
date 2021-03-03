#ifndef ORKA_CONFIG_H
#define ORKA_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ntl.h"

#include <curl/curl.h> //@todo this shouldn't be mandatory

struct orka_config {
  char *tag;

  char *fcontents; // config file contents
  size_t flen; // config file len

  FILE *f_json_dump; //default stderr
  void (*json_cb)(bool, int, struct orka_config*, char*);
  
  FILE *f_curl_dump; //default stderr
  int (*curl_cb)(CURL*, curl_infotype, char*, size_t, void*);
};

void orka_config_init(struct orka_config*, const char tag[], const char config_file[]);
void orka_config_cleanup(struct orka_config*);

char* orka_config_get_field(struct orka_config *config, char *json_field);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ORKA_CONFIG_H
