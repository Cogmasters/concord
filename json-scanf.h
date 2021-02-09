#ifndef JSON_SCANF_H
#define JSON_SCANF_H

#include <stddef.h> // for size_t
#include "ntl.h"


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef int (extractor)(char *, size_t, void *p);

extern int json_scanf(char *buffer, size_t buf_size, char *format, ...);
extern int json_asprintf(char **buf, char *format, ...);
extern int json_snprintf(char *str, size_t size, char *format, ...);
extern char * json_escape_string(size_t * new_size, char * str, size_t old_size);

extern int json_unescape_string(char ** new_str, size_t * new_size,
                                char * str, size_t old_size);

#define IS_DEFINED(p, field)   (ntl_is_a_member((p)->E, &((p)->field)))


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // JSON_SCANF_H
