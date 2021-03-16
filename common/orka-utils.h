#ifndef ORKA_UTILS_H
#define ORKA_UTILS_H

#include <stdbool.h>
#include <limits.h> // for PATH_MAX macro
#include <stdint.h>

#include "orka-debug.h"
#include "ntl.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

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
void orka_timestamp_str(char *p_str, int len);

size_t orka_str_to_ntl(char *str, size_t size, struct ntl_deserializer*);
bool orka_str_bounds_check(const char *str, const size_t threshold_len);

void gen_readlink(char *linkbuf, ssize_t linkbuf_size);

void gen_dirname (char *linkbuf);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ORKA_UTILS_H
