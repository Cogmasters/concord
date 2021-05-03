#ifndef ORKA_UTILS_H
#define ORKA_UTILS_H

#include <stdint.h>

#include "debug.h"
#include "ntl.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/* UTILITY MACROS */
#define STREQ(str1, str2) (0 == strcmp(str1, str2))
#define STRNEQ(str1, str2, n) (0 == strncmp(str1, str2, n))
//check if string is empty
#define IS_EMPTY_STRING(str) (!(str) || !*(str))
//if case matches return token as string
#define CASE_RETURN_STR(opcode) case opcode: return #opcode
//if str matches enum token, return enum value
#define STREQ_RETURN_ENUM(enum, str) if(STREQ(#enum, str))return enum


char* orka_load_whole_file(const char filename[], size_t *len);
int orka_dati_from_fjson(
  char filename[], 
  void *p_data, 
  void (from_json_cb)(char *str, size_t len, void *p_data));

/* can be matched to the json_scanf/printf %F specifier */
int orka_iso8601_to_unix_ms(char *timestamp, size_t len, void *p_data);
int orka_unix_ms_to_iso8601(char *str, size_t len, void *p_data);
int orka_strtoull(char *str, size_t len, void *p_data);
int orka_ulltostr(char *str, size_t len, void *p_data);

void orka_sleep_ms(const int64_t delay_ms);
uint64_t orka_timestamp_ms();
char* orka_timestamp_str(char *p_str, int len);

size_t orka_str_to_ntl(char *str, size_t size, struct ntl_deserializer*);
ssize_t orka_str_bounds_check(const char *str, const size_t threshold_len);
char* orka_join_strings(char** strings, const size_t nmemb, const char delim[], const size_t wordlen, const size_t maxlen);

void gen_readlink(char *linkbuf, size_t linkbuf_size);

void gen_dirname (char *linkbuf);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ORKA_UTILS_H
