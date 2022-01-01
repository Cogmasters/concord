#ifndef JSON_SCANF_H
#define JSON_SCANF_H

#include <stddef.h> /* for size_t */
#include "ntl.h"


#ifdef __cplusplus
extern "C" {
#endif /*_cplusplus */

typedef int (extractor)(char *, size_t, void *p);

extern int json_scanf(char *buffer, size_t buf_size, char *format, ...);
extern int json_asprintf(char **buf, char *format, ...);
extern int json_snprintf(char *str, size_t size, char *format, ...);

#define IS_DEFINED(p, field)   (ntl_is_a_member((p)->E, &((p)->field)))


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* JSON_SCANF_H */
