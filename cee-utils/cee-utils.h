#ifndef CEE_UTILS_H
#define CEE_UTILS_H

#include <stdint.h>

#include "debug.h"
#include "ntl.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* UTILITY MACROS */
#define STREQ(str1, str2) (0 == strcmp(str1, str2))
#define STRNEQ(str1, str2, n) (0 == strncmp(str1, str2, n))
/*check if string is empty */
#define IS_EMPTY_STRING(str) (!(str) || !*(str))
/*if case matches return token as string */
#define CASE_RETURN_STR(opcode) case opcode: return #opcode
/*if str matches enum token, return enum value */
#define STREQ_RETURN_ENUM(enum, str) if(STREQ(#enum, str))return enum


char* cee_load_whole_file_fp(FILE *fp, size_t *len);
char* cee_load_whole_file(const char filename[], size_t *len);
int cee_dati_from_fjson(
  char filename[], 
  void *p_data, 
  void (from_json_cb)(char *str, size_t len, void *p_data));

/* can be matched to the json_scanf/printf %F specifier */
int cee_iso8601_to_unix_ms(char *timestamp, size_t len, uint64_t *p_value);
int cee_unix_ms_to_iso8601(char *str, size_t len, uint64_t *p_value);
int cee_strtoull(char *str, size_t len, uint64_t *p_value);
int cee_ulltostr(char *str, size_t len, uint64_t *p_value);
int cee_strndup(char *src, size_t len, char **p_dest);

int cee_sleep_ms(const long tms);
uint64_t cee_timestamp_ms(void);
char* cee_timestamp_str(char *p_str, int len);

ssize_t cee_str_bounds_check(const char *str, const size_t threshold_len);
char* cee_join_strings(char** strings, const size_t nmemb, const char delim[], const size_t wordlen, const size_t maxlen);

void cee_gen_readlink(char *linkbuf, size_t linkbuf_size);

void cee_gen_dirname(char *linkbuf);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*CEE_UTILS_H */
