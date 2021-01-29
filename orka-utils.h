#ifndef ORKA_UTILS_H
#define ORKA_UTILS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern char *
orka_load_whole_file(const char filename[], size_t *len);

int orka_iso8601_to_unix_ms(char *timestamp, size_t s, void *p);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ORKA_UTILS_H
