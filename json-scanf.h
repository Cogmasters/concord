#ifndef JSON_SCANF_H
#define JSON_SCANF_H

#include <stddef.h> // for size_t

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct json_token {
  char *start;
  int length;
};

typedef int (extractor)(char *, size_t, void *p);

extern int json_scanf(char *buffer, size_t buf_size, char *format, ...);
extern int json_asprintf(char **buf, char *format, ...);
extern int json_snprintf(char *str, size_t size, char *format, ...);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // JSON_SCANF_H
