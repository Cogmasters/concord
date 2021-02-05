#ifndef ORKA_UTILS_H
#define ORKA_UTILS_H

#include <stddef.h>
#include <stdint.h>
#include "ntl.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

char* orka_load_whole_file(const char filename[], size_t *len);

int orka_iso8601_to_unix_ms(char *timestamp, size_t len, void *p_data);
void orka_sleep_ms(const long long delay_ms);
int64_t orka_timestamp_ms();
void orka_timestamp_str(char *p_str, int len);
void orka_strtoull(char *str, size_t len, void *p_data) ;


int orka_str_to_ntl(
  char *str,
  size_t size,
  struct ntl_deserializer * deserializer);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ORKA_UTILS_H
