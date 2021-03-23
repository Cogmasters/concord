#ifndef ORKA_CONFIG_H
#define ORKA_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdbool.h>
#include "ntl.h"


/* UTILITY MACROS */
#define STREQ(str1, str2) (0 == strcmp(str1, str2))
#define STRNEQ(str1, str2, n) (0 == strncmp(str1, str2, n))
//check if string is empty
#define IS_EMPTY_STRING(str) (!(str) || !*(str))
//if case matches return token as string
#define CASE_RETURN_STR(opcode) case opcode: return #opcode
//if str matches enum token, return enum value
#define STREQ_RETURN_ENUM(enum, str) if(STREQ(#enum, str))return enum


struct orka_config {
  char *tag;

  char *fcontents; // config file contents
  size_t flen; // config file len

  FILE *f_json_dump; //default stderr
  void (*json_cb)(
      bool is_response, 
      int code, char *meaning, // related code and its meaning
      struct orka_config*, 
      char *url, 
      char *body);
#if 0  
  FILE *f_curl_dump; //default stderr
  int (*curl_cb)(CURL*, curl_infotype, char*, size_t, void*);
#endif
};

void orka_config_init(struct orka_config*, const char tag[], const char config_file[]);
void orka_config_cleanup(struct orka_config*);

char* orka_config_get_field(struct orka_config *config, char *json_field);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ORKA_CONFIG_H
