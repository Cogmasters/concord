#ifndef ORKA_UTILS_H
#define ORKA_UTILS_H

#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#if defined(__ANDROID__)
#define ORKA_OS "android"
#else
#define ORKA_OS "linux"
#endif // __ANDROID__

#elif defined(_WIN32)
#ifdef _WIN64
#define ORKA_OS "windows 64-bit"
#else
#define ORKA_OS "windows 32-bit"
#endif // _WIN64

#elif defined(__APPLE__)
#include "TargetConditionals.h"
#if defined(TARGET_OS_MAC)
#define ORKA_OS "macOS"
#elif defined(TARGET_OS_IPHONE)
#if defined(TARGET_IPHONE_SIMULATOR)
#define ORKA_OS "iPhone simulator"
#else
#define ORKA_OS "iPhone"
#endif // TARGET_IPHONE_SIMULATOR
#else
#define ORKA_OS "apple"
#endif // TARGET_OS_MAC

#elif defined(__sun)
#define ORKA_OS "solaris"

#elif defined(__hpux)
#define ORKA_OS "HP-UX"

#elif defined(BSD)
#if defined(__DragonFly__)
#define ORKA_OS "DragonFly BSD"
#elif defined(__FreeBSD__)
#define ORKA_OS "FreeBSD"
#elif defined(__NetBSD__)
#define ORKA_OS "NetBSD"
#elif defined(__OpenBSD__)
#define ORKA_OS "OpenBSD"
#endif // __DragonFly__

#endif // __linux__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

char* orka_load_whole_file(const char filename[], size_t *len);

int orka_iso8601_to_unix_ms(char *timestamp, size_t len, void *p_data);
void orka_sleep_ms(const long long delay_ms);
int64_t orka_timestamp_ms();
void orka_timestamp_str(char *p_str, int len);
void orka_strtoull(char *str, size_t len, void *p_data) ;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //ORKA_UTILS_H
