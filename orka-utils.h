#ifndef ORKA_UTILS_H
#define ORKA_UTILS_H

#include <stdbool.h>
#include <limits.h> // for PATH_MAX macro
#include <stdint.h>

#include "ntl.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

char* orka_load_whole_file(const char filename[], size_t *len);

struct _dump_s {
  char filename[PATH_MAX];
  bool enable;
};

struct orka_settings {
  struct {
    char token[512]; // set it to long enough
  } discord;
  struct {
    char username[512];
    char token[512];
  } github;
  struct {
    char filename[PATH_MAX];
    char level[128];
    struct _dump_s dump_json;
    struct _dump_s dump_curl;
  } logging;
};

void orka_settings_init (struct orka_settings*, const char filename[]);

/* can be matched to the json_scanf/printf %F specifier */
int orka_iso8601_to_unix_ms(char *timestamp, size_t len, void *p_data);
int orka_unix_ms_to_iso8601(char *str, size_t len, void *p_data);
int orka_strtoull(char *str, size_t len, void *p_data) ;

void orka_sleep_ms(const int64_t delay_ms);
uint64_t orka_timestamp_ms();
void orka_timestamp_str(char *p_str, int len);

int orka_str_to_ntl(
  char *str,
  size_t size,
  struct ntl_deserializer * deserializer);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ORKA_UTILS_H
